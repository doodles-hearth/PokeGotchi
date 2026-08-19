#include "global.h"
#include "pokegotchi.h"
#include "pokemon.h"
#include "random.h"
#include "rtc.h"

#define POKEGOTCHI_STATS_VERSION 1
#define POKEGOTCHI_STARTING_FOOD_COUNT 10

static EWRAM_DATA bool8 sPokegotchiSessionStarted = FALSE;
static EWRAM_DATA struct Time sPokegotchiSessionStart = {0};
static EWRAM_DATA bool8 sPokegotchiUseTestTime = FALSE;
static EWRAM_DATA struct Time sPokegotchiTestTime = {0};

static void GetCurrentTime(struct Time *time);
static s32 CompareTimes(const struct Time *left, const struct Time *right);
static u32 GetMinutesBetween(const struct Time *start, const struct Time *end);
static u16 ClampStatValue(s32 value);
static void ApplyDecay(u32 activeMinutes, u32 offlineMinutes);
static void RestampLastUpdated(const struct Time *time);
static bool8 GetStatField(enum PokegotchiStat stat, u16 **value);
static struct PokegotchiStats *GetMutableStats(void);
static void CommitRuntimeState(void);

void Pokegotchi_BeginSession(void)
{
    GetCurrentTime(&sPokegotchiSessionStart);
    sPokegotchiSessionStarted = TRUE;
}

void Pokegotchi_EnsureInitialized(void)
{
    struct PokegotchiRuntimeState *runtime = PokegotchiSave_GetRuntimeMutable();
    struct PokegotchiStats *stats = &runtime->stats;

    if (stats->version == POKEGOTCHI_STATS_VERSION)
        return;

    GetCurrentTime(&stats->lastUpdated);
    stats->version = POKEGOTCHI_STATS_VERSION;
    stats->food = POKEGOTCHI_STAT_MAX;
    stats->fun = POKEGOTCHI_STAT_MAX;
    stats->happy = POKEGOTCHI_STAT_MAX;
    stats->poop = POKEGOTCHI_STAT_MAX;
    stats->poopsOnScreen = 0;

    runtime->food.leaf = POKEGOTCHI_STARTING_FOOD_COUNT;
    runtime->food.pecha = POKEGOTCHI_STARTING_FOOD_COUNT;
    CommitRuntimeState();
}

void Pokegotchi_Sync(void)
{
    struct PokegotchiStats *stats = GetMutableStats();
    struct Time now;
    u32 activeMinutes = 0;
    u32 offlineMinutes = 0;
    u32 effectiveOfflineMinutes;

    Pokegotchi_EnsureInitialized();

    if (!sPokegotchiSessionStarted)
        Pokegotchi_BeginSession();

    GetCurrentTime(&now);

    if (CompareTimes(&now, &stats->lastUpdated) < 0)
    {
        RestampLastUpdated(&now);
        sPokegotchiSessionStart = now;
        CommitRuntimeState();
        return;
    }

    if (CompareTimes(&now, &sPokegotchiSessionStart) < 0)
        sPokegotchiSessionStart = now;

    if (CompareTimes(&stats->lastUpdated, &sPokegotchiSessionStart) < 0)
    {
        offlineMinutes = GetMinutesBetween(&stats->lastUpdated, &sPokegotchiSessionStart);
        activeMinutes = GetMinutesBetween(&sPokegotchiSessionStart, &now);
    }
    else
    {
        activeMinutes = GetMinutesBetween(&stats->lastUpdated, &now);
    }

    effectiveOfflineMinutes = (offlineMinutes * POKEGOTCHI_OFFLINE_DECAY_PERCENT) / 100;
    if (activeMinutes + effectiveOfflineMinutes == 0)
        return;

    ApplyDecay(activeMinutes, effectiveOfflineMinutes);
    RestampLastUpdated(&now);
    CommitRuntimeState();
}

void Pokegotchi_SyncAndSave(void)
{
    Pokegotchi_Sync();
    PokegotchiSave_Commit();
}

enum Species Pokegotchi_GetPrimarySpecies(void)
{
    struct PokegotchiRuntimeState *runtime = PokegotchiSave_GetRuntimeMutable();
    enum Species species;

    if (runtime->playerPartyCount == 0)
        return SPECIES_NONE;

    species = GetMonData(&runtime->playerParty[0], MON_DATA_SPECIES_OR_EGG);
    if (species == SPECIES_NONE || species == SPECIES_EGG)
        return SPECIES_NONE;

    return species;
}

const struct PokegotchiStats *Pokegotchi_GetStats(void)
{
    Pokegotchi_EnsureInitialized();
    return &PokegotchiSave_GetRuntime()->stats;
}

void Pokegotchi_AddToStat(enum PokegotchiStat stat, s16 delta)
{
    u16 *value;

    Pokegotchi_Sync();
    if (!GetStatField(stat, &value))
        return;

    *value = ClampStatValue(*value + delta);
    CommitRuntimeState();
}

void Pokegotchi_ClearPoops(void)
{
    struct PokegotchiStats *stats;

    Pokegotchi_Sync();
    stats = GetMutableStats();
    stats->poopsOnScreen = 0;
    CommitRuntimeState();
}

void Pokegotchi_SetCurrentTimeForTest(const struct Time *time)
{
    sPokegotchiTestTime = *time;
    sPokegotchiUseTestTime = TRUE;
}

void Pokegotchi_ResetStateForTest(void)
{
    sPokegotchiSessionStarted = FALSE;
    memset(&sPokegotchiSessionStart, 0, sizeof(sPokegotchiSessionStart));
    sPokegotchiUseTestTime = FALSE;
    memset(&sPokegotchiTestTime, 0, sizeof(sPokegotchiTestTime));
}

static void GetCurrentTime(struct Time *time)
{
    if (sPokegotchiUseTestTime)
    {
        *time = sPokegotchiTestTime;
        return;
    }
    {
        struct SiiRtcInfo rtc;

        RtcGetInfo(&rtc);
        time->days = RtcGetDayCount(&rtc);
        time->hours = ConvertBcdToBinary(rtc.hour);
        time->minutes = ConvertBcdToBinary(rtc.minute);
        time->seconds = ConvertBcdToBinary(rtc.second);
    }
}

static s32 CompareTimes(const struct Time *left, const struct Time *right)
{
    if (left->days != right->days)
        return left->days - right->days;
    if (left->hours != right->hours)
        return left->hours - right->hours;
    if (left->minutes != right->minutes)
        return left->minutes - right->minutes;
    return left->seconds - right->seconds;
}

static u32 GetMinutesBetween(const struct Time *start, const struct Time *end)
{
    struct Time diff;
    struct Time startCopy;
    struct Time endCopy;

    if (CompareTimes(start, end) >= 0)
        return 0;

    startCopy = *start;
    endCopy = *end;
    CalcTimeDifference(&diff, &startCopy, &endCopy);
    return diff.days * HOURS_PER_DAY * MINUTES_PER_HOUR + diff.hours * MINUTES_PER_HOUR + diff.minutes;
}

static u16 ClampStatValue(s32 value)
{
    if (value < 0)
        return 0;
    if (value > POKEGOTCHI_STAT_MAX)
        return POKEGOTCHI_STAT_MAX;
    return value;
}

static void ApplyDecay(u32 activeMinutes, u32 offlineMinutes)
{
    struct PokegotchiStats *stats = GetMutableStats();
    u32 totalMinutes = activeMinutes + offlineMinutes;
    u32 i;
    s32 decayAmount = totalMinutes * POKEGOTCHI_STAT_DECAY_PER_MINUTE;

    stats->food = ClampStatValue(stats->food - decayAmount);
    stats->fun = ClampStatValue(stats->fun - decayAmount);
    stats->happy = ClampStatValue(stats->happy - decayAmount);

    for (i = 0; i < totalMinutes; i++)
    {
        stats->poop = ClampStatValue(stats->poop - POKEGOTCHI_STAT_DECAY_PER_MINUTE);
        if (stats->poop < POKEGOTCHI_POOP_THRESHOLD
         && RandomUniform(RNG_POKEGOTCHI_POOP, 0, 99) < min(100, POKEGOTCHI_POOP_THRESHOLD - stats->poop))
        {
            stats->poop = POKEGOTCHI_STAT_MAX;
            if (stats->poopsOnScreen < UINT16_MAX)
                stats->poopsOnScreen++;
        }
    }
}

static void RestampLastUpdated(const struct Time *time)
{
    GetMutableStats()->lastUpdated = *time;
}

static bool8 GetStatField(enum PokegotchiStat stat, u16 **value)
{
    struct PokegotchiStats *stats = GetMutableStats();

    switch (stat)
    {
    case POKEGOTCHI_STAT_FOOD:
        *value = &stats->food;
        return TRUE;
    case POKEGOTCHI_STAT_FUN:
        *value = &stats->fun;
        return TRUE;
    case POKEGOTCHI_STAT_HAPPY:
        *value = &stats->happy;
        return TRUE;
    case POKEGOTCHI_STAT_POOP:
        *value = &stats->poop;
        return TRUE;
    default:
        return FALSE;
    }
}

static struct PokegotchiStats *GetMutableStats(void)
{
    return &PokegotchiSave_GetRuntimeMutable()->stats;
}

static void CommitRuntimeState(void)
{
    PokegotchiSave_Commit();
}
