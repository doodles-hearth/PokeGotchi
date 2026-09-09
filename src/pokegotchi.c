#include "global.h"
#include "event_data.h"
#include "pokegotchi.h"
#include "pokemon.h"
#include "random.h"
#include "rtc.h"

#define POKEGOTCHI_STATS_VERSION 1
#define POKEGOTCHI_STARTING_STAT 210
#define POKEGOTCHI_STARTING_FOOD_COUNT 10
#define POKEGOTCHI_SESSION_WOKEN_DURING_SLEEP (1 << 0)
#define POKEGOTCHI_SESSION_SLEEP_DECAY_PENDING (1 << 1)
#define POKEGOTCHI_DAILY_EVENT_BITS 2
#define POKEGOTCHI_DAILY_EVENT_MASK ((1 << POKEGOTCHI_DAILY_EVENT_BITS) - 1)
#define POKEGOTCHI_DAILY_EVENT_SATURATED_COUNT 2
#define POKEGOTCHI_CLEAN_HAPPY_PER_POOP 20

STATIC_ASSERT(POKEGOTCHI_DAILY_EVENT_COUNT * POKEGOTCHI_DAILY_EVENT_BITS == 8,
              PokegotchiDailyEventsFitInOneByte);

static EWRAM_DATA bool8 sPokegotchiSessionStarted = FALSE;
static EWRAM_DATA struct Time sPokegotchiSessionStart = {0};
static EWRAM_DATA u8 sPokegotchiSessionFlags = 0;
static EWRAM_DATA bool8 sPokegotchiUseTestTime = FALSE;
static EWRAM_DATA struct Time sPokegotchiTestTime = {0};

static void GetCurrentTime(struct Time *time);
static s32 CompareTimes(const struct Time *left, const struct Time *right);
static u32 GetMinutesBetween(const struct Time *start, const struct Time *end);
static bool8 IsTimeInSleepWindow(const struct Time *time);
static u32 GetSleepMinutesBefore(const struct Time *time);
static u32 GetSleepMinutesBetween(const struct Time *start, const struct Time *end);
static u32 GetActiveSleepDecay(const struct Time *start, const struct Time *end, u32 sleepMinutes);
static u16 ClampStatValue(s32 value);
static void ApplyDecay(u32 statDecayAmount, u32 poopDecayMinutes);
static void RestampLastUpdated(const struct Time *time);
static u8 *GetMutableFoodCountByKey(u8 foodKey);
static bool8 GetStatField(enum PokegotchiStat stat, u16 **value);
static struct PokegotchiStats *GetMutableStats(void);
static void CommitRuntimeState(void);
static void UpdateDailyFlagsForTime(const struct Time *time);

void Pokegotchi_BeginSession(void)
{
    GetCurrentTime(&sPokegotchiSessionStart);
    UpdateDailyFlagsForTime(&sPokegotchiSessionStart);
    sPokegotchiSessionStarted = TRUE;
    sPokegotchiSessionFlags = 0;
}

void Pokegotchi_UpdateDailyFlags(void)
{
    struct Time now;

    GetCurrentTime(&now);
    UpdateDailyFlagsForTime(&now);
}

void Pokegotchi_EnsureInitialized(void)
{
    struct PokegotchiRuntimeState *runtime = PokegotchiSave_GetRuntimeMutable();
    struct PokegotchiStats *stats = &runtime->stats;

    if (stats->version == POKEGOTCHI_STATS_VERSION)
    {
        if (stats->poopsOnScreen > POKEGOTCHI_MAX_POOPS)
        {
            stats->poopsOnScreen = POKEGOTCHI_MAX_POOPS;
            CommitRuntimeState();
        }
        return;
    }

    GetCurrentTime(&stats->lastUpdated);
    stats->version = POKEGOTCHI_STATS_VERSION;
    stats->food = POKEGOTCHI_STARTING_STAT;
    stats->fun = POKEGOTCHI_STARTING_STAT;
    stats->happy = POKEGOTCHI_STARTING_STAT;
    stats->poop = POKEGOTCHI_STAT_MAX;
    stats->poopsOnScreen = 0;

    runtime->food.leaf = POKEGOTCHI_STARTING_FOOD_COUNT;
    runtime->food.hotDog = 0;
    runtime->food.pokeblock = 0;
    runtime->food.egg = 0;
    runtime->food.pecha = POKEGOTCHI_STARTING_FOOD_COUNT;
    runtime->food.iceCream = 0;
    runtime->food.donut = 0;
    runtime->food.juice = 0;
    CommitRuntimeState();
}

void Pokegotchi_Sync(void)
{
    struct PokegotchiStats *stats = GetMutableStats();
    struct Time now;
    struct Time activeStart;
    u32 activeMinutes = 0;
    u32 offlineMinutes = 0;
    u32 activeSleepMinutes = 0;
    u32 offlineSleepMinutes = 0;
    u32 activeAwakeMinutes;
    u32 offlineAwakeMinutes;
    u32 statDecayAmount;
    u32 poopDecayMinutes;

    Pokegotchi_EnsureInitialized();

    if (!sPokegotchiSessionStarted)
        Pokegotchi_BeginSession();

    GetCurrentTime(&now);
    UpdateDailyFlagsForTime(&now);

    if (CompareTimes(&now, &stats->lastUpdated) < 0)
    {
        RestampLastUpdated(&now);
        sPokegotchiSessionStart = now;
        sPokegotchiSessionFlags = 0;
        CommitRuntimeState();
        return;
    }

    if (CompareTimes(&now, &sPokegotchiSessionStart) < 0)
        sPokegotchiSessionStart = now;

    if (CompareTimes(&stats->lastUpdated, &sPokegotchiSessionStart) < 0)
    {
        offlineMinutes = GetMinutesBetween(&stats->lastUpdated, &sPokegotchiSessionStart);
        offlineSleepMinutes = GetSleepMinutesBetween(&stats->lastUpdated, &sPokegotchiSessionStart);
        activeStart = sPokegotchiSessionStart;
        activeMinutes = GetMinutesBetween(&sPokegotchiSessionStart, &now);
    }
    else
    {
        activeStart = stats->lastUpdated;
        activeMinutes = GetMinutesBetween(&stats->lastUpdated, &now);
    }

    if (activeMinutes + offlineMinutes == 0)
        return;

    if (!(sPokegotchiSessionFlags & POKEGOTCHI_SESSION_WOKEN_DURING_SLEEP))
        activeSleepMinutes = GetSleepMinutesBetween(&activeStart, &now);

    activeSleepMinutes = min(activeSleepMinutes, activeMinutes);
    offlineSleepMinutes = min(offlineSleepMinutes, offlineMinutes);
    activeAwakeMinutes = activeMinutes - activeSleepMinutes;
    offlineAwakeMinutes = offlineMinutes - offlineSleepMinutes;

    statDecayAmount = activeAwakeMinutes * POKEGOTCHI_STAT_DECAY_PER_MINUTE;
    statDecayAmount += ((offlineAwakeMinutes * POKEGOTCHI_OFFLINE_DECAY_PERCENT) / 100)
                     * POKEGOTCHI_STAT_DECAY_PER_MINUTE;
    statDecayAmount += offlineSleepMinutes / 2;
    if (!(sPokegotchiSessionFlags & POKEGOTCHI_SESSION_WOKEN_DURING_SLEEP))
        statDecayAmount += GetActiveSleepDecay(&activeStart, &now, activeSleepMinutes);

    poopDecayMinutes = activeAwakeMinutes;
    poopDecayMinutes += (offlineAwakeMinutes * POKEGOTCHI_OFFLINE_DECAY_PERCENT) / 100;

    ApplyDecay(statDecayAmount, poopDecayMinutes);
    RestampLastUpdated(&now);

    if (!IsTimeInSleepWindow(&now))
    {
        sPokegotchiSessionFlags = 0;
    }
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

bool8 Pokegotchi_IsSleeping(void)
{
    struct Time now;

    GetCurrentTime(&now);
    return IsTimeInSleepWindow(&now)
        && !(sPokegotchiSessionFlags & POKEGOTCHI_SESSION_WOKEN_DURING_SLEEP);
}

bool8 Pokegotchi_WakeForActivity(void)
{
    struct Time now;

    // Account for time before the interaction at the sleeping rate. Setting the
    // flag first would retroactively charge that time at the active-awake rate.
    Pokegotchi_Sync();
    GetCurrentTime(&now);
    if (!IsTimeInSleepWindow(&now))
        return FALSE;

    sPokegotchiSessionFlags |= POKEGOTCHI_SESSION_WOKEN_DURING_SLEEP;
    sPokegotchiSessionFlags &= ~POKEGOTCHI_SESSION_SLEEP_DECAY_PENDING;
    return TRUE;
}

enum PokegotchiInteractionReaction Pokegotchi_GetInteractionReaction(const struct PokegotchiStats *stats)
{
    if (stats->food == 0 && stats->fun == 0 && stats->happy == 0)
        return POKEGOTCHI_REACTION_SULKING;
    if (stats->happy > 150 && (stats->food <= 100 || stats->fun <= 100))
        return POKEGOTCHI_REACTION_HAPPY_ONCE;
    if (stats->happy > 150)
        return POKEGOTCHI_REACTION_HAPPY_TWICE_SUN;
    if (stats->food == 0 && stats->fun > 0)
        return POKEGOTCHI_REACTION_ANGRY_TWICE;
    if (stats->fun == 0 && (stats->food > 0 || stats->happy > 0))
        return POKEGOTCHI_REACTION_SAD_TWICE;
    if (stats->food > 150 && stats->fun > 150)
        return POKEGOTCHI_REACTION_HAPPY_TWICE;
    if (stats->food > 100 && stats->fun > 100)
        return POKEGOTCHI_REACTION_HAPPY_ONCE;
    if (stats->food <= 100 && stats->fun > 100)
        return POKEGOTCHI_REACTION_ANGRY_ONCE;
    if (stats->fun <= 100 && stats->food > 100)
        return POKEGOTCHI_REACTION_SAD_ONCE;

    return POKEGOTCHI_REACTION_SAD_TWICE;
}

bool8 Pokegotchi_AddFoodByKey(u8 foodKey, u16 amount)
{
    u8 *count;
    u32 total;

    Pokegotchi_EnsureInitialized();
    count = GetMutableFoodCountByKey(foodKey);
    if (count == NULL)
        return FALSE;

    total = *count + amount;
    if (total > UINT8_MAX)
        total = UINT8_MAX;
    if (total == *count)
        return TRUE;

    *count = total;
    CommitRuntimeState();
    return TRUE;
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

bool8 Pokegotchi_ApplyDailyPetInteractionReward(void)
{
    struct PokegotchiStats *stats;

    Pokegotchi_Sync();
    if (FlagGet(POKEGOTCHI_DAILY_FLAG_INTERACTED_WITH_PET))
        return FALSE;

    stats = GetMutableStats();
    stats->happy = ClampStatValue(stats->happy + 40);
    FlagSet(POKEGOTCHI_DAILY_FLAG_INTERACTED_WITH_PET);
    CommitRuntimeState();
    return TRUE;
}

bool8 Pokegotchi_ApplyDailyEventReward(enum PokegotchiDailyEvent event)
{
    return Pokegotchi_ApplyDailyEventRewardWithTier(event) != POKEGOTCHI_DAILY_REWARD_NONE;
}

enum PokegotchiDailyRewardTier Pokegotchi_ApplyDailyEventRewardWithTier(enum PokegotchiDailyEvent event)
{
    struct PokegotchiRuntimeState *runtime;
    struct PokegotchiStats *stats;
    u8 shift;
    u8 count;
    u8 happyIncrease = 0;
    u8 funIncrease = 0;
    u16 oldHappy;
    u16 oldFun;
    enum PokegotchiDailyRewardTier rewardTier;

    if ((u32)event >= POKEGOTCHI_DAILY_EVENT_COUNT)
        return POKEGOTCHI_DAILY_REWARD_NONE;

    Pokegotchi_UpdateDailyFlags();
    runtime = PokegotchiSave_GetRuntimeMutable();
    stats = &runtime->stats;
    shift = event * POKEGOTCHI_DAILY_EVENT_BITS;
    count = (runtime->dailyEventCounts >> shift) & POKEGOTCHI_DAILY_EVENT_MASK;
    count = min(count, POKEGOTCHI_DAILY_EVENT_SATURATED_COUNT);
    if (count == 0)
        rewardTier = POKEGOTCHI_DAILY_REWARD_FIRST;
    else if (count == 1)
        rewardTier = POKEGOTCHI_DAILY_REWARD_SECOND;
    else
        rewardTier = POKEGOTCHI_DAILY_REWARD_REPEAT;

    if (event == POKEGOTCHI_DAILY_EVENT_MEAL || event == POKEGOTCHI_DAILY_EVENT_SNACK)
    {
        if (count == 0)
            happyIncrease = 30;
        else if (count == 1)
            happyIncrease = 20;
    }
    else
    {
        if (count == 0)
        {
            happyIncrease = 50;
            funIncrease = 50;
        }
        else if (count == 1)
        {
            happyIncrease = 25;
            funIncrease = 25;
        }
        else
        {
            happyIncrease = 10;
            funIncrease = 20;
        }
    }

    oldHappy = stats->happy;
    oldFun = stats->fun;
    stats->happy = ClampStatValue(stats->happy + happyIncrease);
    stats->fun = ClampStatValue(stats->fun + funIncrease);
    if (stats->happy == oldHappy && stats->fun == oldFun)
        return POKEGOTCHI_DAILY_REWARD_NONE;

    if (count < POKEGOTCHI_DAILY_EVENT_SATURATED_COUNT)
        count++;
    runtime->dailyEventCounts &= ~(POKEGOTCHI_DAILY_EVENT_MASK << shift);
    runtime->dailyEventCounts |= count << shift;
    return rewardTier;
}

static const u8 sPokegotchiPoopsToHappiness[POKEGOTCHI_MAX_POOPS + 1] =
{
    [0] = 0,
    [1] = 25,
    [2] = 40,
    [3] = 55,
    [4] = 60,
};

void Pokegotchi_ClearPoops(void)
{
    struct PokegotchiStats *stats;

    Pokegotchi_Sync();
    stats = GetMutableStats();
    if (stats->poopsOnScreen > 0)
        stats->happy = ClampStatValue(stats->happy + sPokegotchiPoopsToHappiness[stats->poopsOnScreen]);
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
    sPokegotchiSessionFlags = 0;
    sPokegotchiUseTestTime = FALSE;
    memset(&sPokegotchiTestTime, 0, sizeof(sPokegotchiTestTime));
}

#if TESTING
void Pokegotchi_SetWokenDuringSleepForTest(bool8 woken)
{
    // This hook bypasses the production wake function so tests can set either
    // session state directly without advancing or synchronizing the clock.
    if (woken)
    {
        sPokegotchiSessionFlags |= POKEGOTCHI_SESSION_WOKEN_DURING_SLEEP;
        sPokegotchiSessionFlags &= ~POKEGOTCHI_SESSION_SLEEP_DECAY_PENDING;
    }
    else
    {
        sPokegotchiSessionFlags &= ~POKEGOTCHI_SESSION_WOKEN_DURING_SLEEP;
    }
}

u32 Pokegotchi_GetSleepMinutesBetweenForTest(const struct Time *start, const struct Time *end)
{
    return GetSleepMinutesBetween(start, end);
}
#endif

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

static bool8 IsTimeInSleepWindow(const struct Time *time)
{
    return time->hours >= POKEGOTCHI_SLEEP_START_HOUR
        || time->hours < POKEGOTCHI_SLEEP_END_HOUR;
}

static u32 GetSleepMinutesBefore(const struct Time *time)
{
    u32 days = max(0, time->days);
    u32 minuteOfDay = time->hours * MINUTES_PER_HOUR + time->minutes;
    u32 sleepMinutes = days * 8 * MINUTES_PER_HOUR;

    if (minuteOfDay < POKEGOTCHI_SLEEP_END_HOUR * MINUTES_PER_HOUR)
        sleepMinutes += minuteOfDay;
    else if (minuteOfDay < POKEGOTCHI_SLEEP_START_HOUR * MINUTES_PER_HOUR)
        sleepMinutes += POKEGOTCHI_SLEEP_END_HOUR * MINUTES_PER_HOUR;
    else
        sleepMinutes += POKEGOTCHI_SLEEP_END_HOUR * MINUTES_PER_HOUR
                      + minuteOfDay - POKEGOTCHI_SLEEP_START_HOUR * MINUTES_PER_HOUR;

    return sleepMinutes;
}

static u32 GetSleepMinutesBetween(const struct Time *start, const struct Time *end)
{
    u32 startSleepMinutes;
    u32 endSleepMinutes;
    u32 totalMinutes;

    if (CompareTimes(start, end) >= 0)
        return 0;

    totalMinutes = GetMinutesBetween(start, end);
    startSleepMinutes = GetSleepMinutesBefore(start);
    endSleepMinutes = GetSleepMinutesBefore(end);
    if (endSleepMinutes <= startSleepMinutes)
        return 0;

    return min(totalMinutes, endSleepMinutes - startSleepMinutes);
}

static u32 GetMinutesUntilSleepEnds(const struct Time *time)
{
    u32 minuteOfDay = time->hours * MINUTES_PER_HOUR + time->minutes;

    if (time->hours < POKEGOTCHI_SLEEP_END_HOUR)
        return POKEGOTCHI_SLEEP_END_HOUR * MINUTES_PER_HOUR - minuteOfDay;

    return HOURS_PER_DAY * MINUTES_PER_HOUR - minuteOfDay
         + POKEGOTCHI_SLEEP_END_HOUR * MINUTES_PER_HOUR;
}

static u32 GetMinutesSinceSleepStarted(const struct Time *time)
{
    u32 minuteOfDay = time->hours * MINUTES_PER_HOUR + time->minutes;

    if (time->hours >= POKEGOTCHI_SLEEP_START_HOUR)
        return minuteOfDay - POKEGOTCHI_SLEEP_START_HOUR * MINUTES_PER_HOUR;

    return (HOURS_PER_DAY - POKEGOTCHI_SLEEP_START_HOUR) * MINUTES_PER_HOUR + minuteOfDay;
}

static u32 GetActiveSleepDecay(const struct Time *start, const struct Time *end, u32 sleepMinutes)
{
    u32 firstSegmentMinutes = 0;
    u32 lastSegmentMinutes = 0;
    u32 middleMinutes;
    u32 decayAmount = 0;
    u32 pairedMinutes;

    if (sleepMinutes == 0)
    {
        if (GetMinutesBetween(start, end) != 0)
            sPokegotchiSessionFlags &= ~POKEGOTCHI_SESSION_SLEEP_DECAY_PENDING;
        return 0;
    }

    if (IsTimeInSleepWindow(start))
    {
        firstSegmentMinutes = min(sleepMinutes, GetMinutesUntilSleepEnds(start));
        pairedMinutes = firstSegmentMinutes
                      + !!(sPokegotchiSessionFlags & POKEGOTCHI_SESSION_SLEEP_DECAY_PENDING);
        decayAmount += pairedMinutes / 2;

        if (firstSegmentMinutes == sleepMinutes && IsTimeInSleepWindow(end))
        {
            if (pairedMinutes & 1)
                sPokegotchiSessionFlags |= POKEGOTCHI_SESSION_SLEEP_DECAY_PENDING;
            else
                sPokegotchiSessionFlags &= ~POKEGOTCHI_SESSION_SLEEP_DECAY_PENDING;
            return decayAmount;
        }

        sPokegotchiSessionFlags &= ~POKEGOTCHI_SESSION_SLEEP_DECAY_PENDING;
    }

    if (IsTimeInSleepWindow(end))
    {
        lastSegmentMinutes = min(sleepMinutes - firstSegmentMinutes, GetMinutesSinceSleepStarted(end));
        decayAmount += lastSegmentMinutes / 2;
        if (lastSegmentMinutes & 1)
            sPokegotchiSessionFlags |= POKEGOTCHI_SESSION_SLEEP_DECAY_PENDING;
        else
            sPokegotchiSessionFlags &= ~POKEGOTCHI_SESSION_SLEEP_DECAY_PENDING;
    }
    else
    {
        sPokegotchiSessionFlags &= ~POKEGOTCHI_SESSION_SLEEP_DECAY_PENDING;
    }

    middleMinutes = sleepMinutes - firstSegmentMinutes - lastSegmentMinutes;
    decayAmount += middleMinutes / 2;
    return decayAmount;
}

static u16 ClampStatValue(s32 value)
{
    if (value < 0)
        return 0;
    if (value > POKEGOTCHI_STAT_MAX)
        return POKEGOTCHI_STAT_MAX;
    return value;
}

static void ApplyDecay(u32 statDecayAmount, u32 poopDecayMinutes)
{
    struct PokegotchiStats *stats = GetMutableStats();
    u32 i;

    stats->food = ClampStatValue(stats->food - statDecayAmount);
    stats->fun = ClampStatValue(stats->fun - statDecayAmount);
    stats->happy = ClampStatValue(stats->happy - statDecayAmount);

    if (stats->poopsOnScreen >= POKEGOTCHI_MAX_POOPS)
    {
        stats->poopsOnScreen = POKEGOTCHI_MAX_POOPS;
        stats->poop = ClampStatValue(stats->poop - poopDecayMinutes * POKEGOTCHI_STAT_DECAY_PER_MINUTE);
        return;
    }

    for (i = 0; i < poopDecayMinutes; i++)
    {
        stats->poop = ClampStatValue(stats->poop - POKEGOTCHI_STAT_DECAY_PER_MINUTE);
        if (stats->poop < POKEGOTCHI_POOP_THRESHOLD
         && RandomUniform(RNG_POKEGOTCHI_POOP, 0, 99) < min(100, POKEGOTCHI_POOP_THRESHOLD - stats->poop))
        {
            stats->poop = POKEGOTCHI_STAT_MAX;
            stats->poopsOnScreen++;
            if (stats->poopsOnScreen == POKEGOTCHI_MAX_POOPS)
            {
                i++;
                break;
            }
        }
    }

    if (i < poopDecayMinutes)
        stats->poop = ClampStatValue(stats->poop - (poopDecayMinutes - i) * POKEGOTCHI_STAT_DECAY_PER_MINUTE);
}

static void RestampLastUpdated(const struct Time *time)
{
    GetMutableStats()->lastUpdated = *time;
}

static u8 *GetMutableFoodCountByKey(u8 foodKey)
{
    struct PokegotchiFood *food = &PokegotchiSave_GetRuntimeMutable()->food;

    switch (foodKey)
    {
    case FEED_FOOD_KEY_LEAF:
        return &food->leaf;
    case FEED_FOOD_KEY_HOT_DOG:
        return &food->hotDog;
    case FEED_FOOD_KEY_POKEBLOCK:
        return &food->pokeblock;
    case FEED_FOOD_KEY_EGG:
        return &food->egg;
    case FEED_FOOD_KEY_PECHA:
        return &food->pecha;
    case FEED_FOOD_KEY_ICE_CREAM:
        return &food->iceCream;
    case FEED_FOOD_KEY_DONUT:
        return &food->donut;
    case FEED_FOOD_KEY_JUICE:
        return &food->juice;
    case FEED_FOOD_KEY_NONE:
    default:
        return NULL;
    }
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

static void UpdateDailyFlagsForTime(const struct Time *time)
{
    struct PokegotchiRuntimeState *runtime = PokegotchiSave_GetRuntimeMutable();

    if (!runtime->dailyFlagsInitialized)
    {
        memset(runtime->dailyFlags, 0, sizeof(runtime->dailyFlags));
        runtime->dailyEventCounts = 0;
        runtime->dailyFlagsDay = time->days;
        runtime->dailyFlagsInitialized = TRUE;
        CommitRuntimeState();
    }
    else if (runtime->dailyFlagsDay != time->days && runtime->dailyFlagsDay <= time->days)
    {
        memset(runtime->dailyFlags, 0, sizeof(runtime->dailyFlags));
        runtime->dailyEventCounts = 0;
        runtime->dailyFlagsDay = time->days;
        CommitRuntimeState();
    }
}

static void CommitRuntimeState(void)
{
    PokegotchiSave_Commit();
}
