#include "global.h"
#include "event_data.h"
#include "fake_rtc.h"
#include "load_save.h"
#include "palette.h"
#include "pokegotchi.h"
#include "pokegotchi_save.h"
#include "pokegotchi_sprites.h"
#include "script.h"
#include "sprite.h"
#include "test/overworld_script.h"
#include "test/test.h"

static const struct Time sTime_10_00 = {.days = 0, .hours = 10, .minutes = 0, .seconds = 0};
static const struct Time sTime_10_01 = {.days = 0, .hours = 10, .minutes = 1, .seconds = 0};
static const struct Time sTime_10_02 = {.days = 0, .hours = 10, .minutes = 2, .seconds = 0};
static const struct Time sTime_10_10 = {.days = 0, .hours = 10, .minutes = 10, .seconds = 0};
static const struct Time sTime_10_16 = {.days = 0, .hours = 10, .minutes = 16, .seconds = 0};
static const struct Time sTime_10_26 = {.days = 0, .hours = 10, .minutes = 26, .seconds = 0};
static const struct Time sTime_11_50 = {.days = 0, .hours = 11, .minutes = 50, .seconds = 0};
static const struct Time sTime_13_00 = {.days = 0, .hours = 13, .minutes = 0, .seconds = 0};
static const struct Time sTime_20_00 = {.days = 0, .hours = 20, .minutes = 0, .seconds = 0};
static const struct Time sTime_20_59 = {.days = 0, .hours = 20, .minutes = 59, .seconds = 0};
static const struct Time sTime_21_00 = {.days = 0, .hours = 21, .minutes = 0, .seconds = 0};
static const struct Time sTime_21_01 = {.days = 0, .hours = 21, .minutes = 1, .seconds = 0};
static const struct Time sTime_21_02 = {.days = 0, .hours = 21, .minutes = 2, .seconds = 0};
static const struct Time sTime_21_03 = {.days = 0, .hours = 21, .minutes = 3, .seconds = 0};
static const struct Time sTime_23_00 = {.days = 0, .hours = 23, .minutes = 0, .seconds = 0};
static const struct Time sTime_Day1_00_00 = {.days = 1, .hours = 0, .minutes = 0, .seconds = 0};
static const struct Time sTime_Day1_04_58 = {.days = 1, .hours = 4, .minutes = 58, .seconds = 0};
static const struct Time sTime_Day1_04_59 = {.days = 1, .hours = 4, .minutes = 59, .seconds = 0};
static const struct Time sTime_Day1_05_00 = {.days = 1, .hours = 5, .minutes = 0, .seconds = 0};
static const struct Time sTime_Day2_06_00 = {.days = 2, .hours = 6, .minutes = 0, .seconds = 0};
static const struct Time sTime_Day4_06_00 = {.days = 4, .hours = 6, .minutes = 0, .seconds = 0};
static const struct Time sTime_09_00 = {.days = 0, .hours = 9, .minutes = 0, .seconds = 0};

static void ResetPokegotchiTestState(void)
{
    SetSaveBlocksPointers(0);
    PokegotchiSave_ClearForTest();
    FakeRtc_Reset(); // Potentially using Fake RTC if RTC is not detected later
    Pokegotchi_ResetStateForTest();
}

TEST("(Pokegotchi) EnsureInitialized seeds default stats and food inventory")
{
    const struct PokegotchiStats *stats;
    const struct PokegotchiRuntimeState *runtime;

    ResetPokegotchiTestState();
    Pokegotchi_SetCurrentTimeForTest(&sTime_10_00);
    Pokegotchi_EnsureInitialized();
    stats = Pokegotchi_GetStats();
    runtime = PokegotchiSave_GetRuntime();

    EXPECT_EQ(stats->version, 1);
    EXPECT_EQ(stats->food, 250);
    EXPECT_EQ(stats->fun, 250);
    EXPECT_EQ(stats->happy, 250);
    EXPECT_EQ(stats->poop, 250);
    EXPECT_EQ(stats->poopsOnScreen, 0);
    EXPECT_EQ(stats->lastUpdated.days, sTime_10_00.days);
    EXPECT_EQ(stats->lastUpdated.hours, sTime_10_00.hours);
    EXPECT_EQ(stats->lastUpdated.minutes, sTime_10_00.minutes);
    EXPECT_EQ(runtime->food.leaf, 10);
    EXPECT_EQ(runtime->food.hotDog, 0);
    EXPECT_EQ(runtime->food.pokeblock, 0);
    EXPECT_EQ(runtime->food.egg, 0);
    EXPECT_EQ(runtime->food.pecha, 10);
    EXPECT_EQ(runtime->food.iceCream, 0);
    EXPECT_EQ(runtime->food.donut, 0);
    EXPECT_EQ(runtime->food.juice, 0);
}

TEST("(Pokegotchi) Daily flags initialize and remain set on the same day")
{
    const struct PokegotchiRuntimeState *runtime;

    ResetPokegotchiTestState();
    Pokegotchi_SetCurrentTimeForTest(&sTime_Day1_00_00);
    Pokegotchi_UpdateDailyFlags();
    runtime = PokegotchiSave_GetRuntime();

    EXPECT(runtime->dailyFlagsInitialized);
    EXPECT_EQ(runtime->dailyFlagsDay, 1);
    EXPECT_EQ(runtime->dailyFlags[0], 0);

    FlagSet(POKEGOTCHI_DAILY_FLAGS_START);
    FlagSet(POKEGOTCHI_DAILY_FLAGS_END);
    Pokegotchi_UpdateDailyFlags();

    EXPECT(FlagGet(POKEGOTCHI_DAILY_FLAGS_START));
    EXPECT(FlagGet(POKEGOTCHI_DAILY_FLAGS_END));
    EXPECT_EQ(runtime->dailyFlagsDay, 1);
}

TEST("(Pokegotchi) Daily flags reset across forward day changes and persist")
{
    const struct PokegotchiRuntimeState *runtime;

    ResetPokegotchiTestState();
    Pokegotchi_SetCurrentTimeForTest(&sTime_Day1_00_00);
    Pokegotchi_UpdateDailyFlags();
    FlagSet(POKEGOTCHI_DAILY_FLAGS_START);
    FlagSet(POKEGOTCHI_DAILY_FLAGS_END);

    Pokegotchi_SetCurrentTimeForTest(&sTime_Day2_06_00);
    Pokegotchi_UpdateDailyFlags();
    runtime = PokegotchiSave_GetRuntime();

    EXPECT_EQ(runtime->dailyFlagsDay, 2);
    EXPECT_EQ(runtime->dailyFlags[0], 0);

    FlagSet(POKEGOTCHI_DAILY_FLAGS_START + 3);
    Pokegotchi_SetCurrentTimeForTest(&sTime_Day4_06_00);
    Pokegotchi_UpdateDailyFlags();

    EXPECT_EQ(runtime->dailyFlagsDay, 4);
    EXPECT_EQ(runtime->dailyFlags[0], 0);

    PokegotchiSave_ClearRuntimeState();
    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    runtime = PokegotchiSave_GetRuntime();
    EXPECT(runtime->dailyFlagsInitialized);
    EXPECT_EQ(runtime->dailyFlagsDay, 4);
    EXPECT_EQ(runtime->dailyFlags[0], 0);
}

TEST("(Pokegotchi) One active minute reduces all four meters by two")
{
    const struct PokegotchiStats *stats;

    ResetPokegotchiTestState();
    Pokegotchi_SetCurrentTimeForTest(&sTime_10_00);
    Pokegotchi_EnsureInitialized();
    Pokegotchi_BeginSession();

    Pokegotchi_SetCurrentTimeForTest(&sTime_10_01);
    Pokegotchi_Sync();
    stats = Pokegotchi_GetStats();

    EXPECT_EQ(stats->food, 248);
    EXPECT_EQ(stats->fun, 248);
    EXPECT_EQ(stats->happy, 248);
    EXPECT_EQ(stats->poop, 248);
}

TEST("(Pokegotchi) Offline-only elapsed time uses the reduced scalar")
{
    const struct PokegotchiStats *stats;

    ResetPokegotchiTestState();
    Pokegotchi_SetCurrentTimeForTest(&sTime_10_00);
    Pokegotchi_EnsureInitialized();

    Pokegotchi_SetCurrentTimeForTest(&sTime_10_02);
    Pokegotchi_Sync();
    stats = Pokegotchi_GetStats();

    EXPECT_EQ(stats->food, 248);
    EXPECT_EQ(stats->fun, 248);
    EXPECT_EQ(stats->happy, 248);
    EXPECT_EQ(stats->poop, 248);
}

TEST("(Pokegotchi) Mixed offline and active time splits around session start")
{
    const struct PokegotchiStats *stats;

    ResetPokegotchiTestState();
    Pokegotchi_SetCurrentTimeForTest(&sTime_10_00);
    Pokegotchi_EnsureInitialized();

    Pokegotchi_SetCurrentTimeForTest(&sTime_10_10);
    Pokegotchi_BeginSession();

    Pokegotchi_SetCurrentTimeForTest(&sTime_10_16);
    Pokegotchi_Sync();
    stats = Pokegotchi_GetStats();

    EXPECT_EQ(stats->food, 228);
    EXPECT_EQ(stats->fun, 228);
    EXPECT_EQ(stats->happy, 228);
    EXPECT_EQ(stats->poop, 228);
}

TEST("(Pokegotchi) Long elapsed time clamps food, fun, and happy at zero")
{
    const struct PokegotchiStats *stats;

    ResetPokegotchiTestState();
    Pokegotchi_SetCurrentTimeForTest(&sTime_10_00);
    Pokegotchi_EnsureInitialized();
    Pokegotchi_BeginSession();

    Pokegotchi_SetCurrentTimeForTest(&sTime_13_00);
    Pokegotchi_Sync();
    stats = Pokegotchi_GetStats();

    EXPECT_EQ(stats->food, 0);
    EXPECT_EQ(stats->fun, 0);
    EXPECT_EQ(stats->happy, 0);
}

TEST("(Pokegotchi) Rigged poop RNG resets poop and increments poopsOnScreen")
{
    const struct PokegotchiStats *stats;

    ResetPokegotchiTestState();
    Pokegotchi_SetCurrentTimeForTest(&sTime_10_00);
    Pokegotchi_EnsureInitialized();
    Pokegotchi_BeginSession();
    SET_RNG(RNG_POKEGOTCHI_POOP, 0);

    Pokegotchi_SetCurrentTimeForTest(&sTime_10_26);
    Pokegotchi_Sync();
    stats = Pokegotchi_GetStats();

    EXPECT_EQ(stats->poop, 250);
    EXPECT_EQ(stats->poopsOnScreen, 1);
}

TEST("(Pokegotchi) Clock rollback restamps without underflowing stats")
{
    const struct PokegotchiStats *stats;

    ResetPokegotchiTestState();
    Pokegotchi_SetCurrentTimeForTest(&sTime_10_00);
    Pokegotchi_EnsureInitialized();
    Pokegotchi_BeginSession();

    Pokegotchi_SetCurrentTimeForTest(&sTime_09_00);
    Pokegotchi_Sync();
    stats = Pokegotchi_GetStats();

    EXPECT_EQ(stats->food, 250);
    EXPECT_EQ(stats->fun, 250);
    EXPECT_EQ(stats->happy, 250);
    EXPECT_EQ(stats->poop, 250);
    EXPECT_EQ(stats->lastUpdated.hours, 9);
    EXPECT_EQ(stats->lastUpdated.minutes, 0);
}

TEST("(Pokegotchi) Sleep starts at 21:00 and ends at 05:00")
{
    ResetPokegotchiTestState();

    Pokegotchi_SetCurrentTimeForTest(&sTime_20_59);
    EXPECT_EQ(Pokegotchi_IsSleeping(), FALSE);
    Pokegotchi_SetCurrentTimeForTest(&sTime_21_00);
    EXPECT_EQ(Pokegotchi_IsSleeping(), TRUE);
    Pokegotchi_SetCurrentTimeForTest(&sTime_Day1_00_00);
    EXPECT_EQ(Pokegotchi_IsSleeping(), TRUE);
    Pokegotchi_SetCurrentTimeForTest(&sTime_Day1_04_59);
    EXPECT_EQ(Pokegotchi_IsSleeping(), TRUE);
    Pokegotchi_SetCurrentTimeForTest(&sTime_Day1_05_00);
    EXPECT_EQ(Pokegotchi_IsSleeping(), FALSE);
}

TEST("(Pokegotchi) Sleep overlap is constant across midnight and complete days")
{
    ResetPokegotchiTestState();

    EXPECT_EQ(Pokegotchi_GetSleepMinutesBetweenForTest(&sTime_23_00, &sTime_Day1_00_00), 60);
    EXPECT_EQ(Pokegotchi_GetSleepMinutesBetweenForTest(&sTime_20_00, &sTime_Day2_06_00), 960);
}

TEST("(Pokegotchi) Active sleep skips the first minute and reduces one point on the second")
{
    const struct PokegotchiStats *stats;

    ResetPokegotchiTestState();
    Pokegotchi_SetCurrentTimeForTest(&sTime_21_00);
    Pokegotchi_EnsureInitialized();
    Pokegotchi_BeginSession();

    Pokegotchi_SetCurrentTimeForTest(&sTime_21_01);
    Pokegotchi_Sync();
    stats = Pokegotchi_GetStats();
    EXPECT_EQ(stats->food, 250);
    EXPECT_EQ(stats->poop, 250);

    Pokegotchi_SetCurrentTimeForTest(&sTime_21_02);
    Pokegotchi_Sync();
    stats = Pokegotchi_GetStats();
    EXPECT_EQ(stats->food, 249);
    EXPECT_EQ(stats->fun, 249);
    EXPECT_EQ(stats->happy, 249);
    EXPECT_EQ(stats->poop, 250);

    Pokegotchi_SetCurrentTimeForTest(&sTime_21_03);
    Pokegotchi_Sync();
    EXPECT_EQ(Pokegotchi_GetStats()->food, 249);
}

TEST("(Pokegotchi) Offline sleep drops fractional decay on reopen")
{
    ResetPokegotchiTestState();
    Pokegotchi_SetCurrentTimeForTest(&sTime_21_00);
    Pokegotchi_EnsureInitialized();

    Pokegotchi_SetCurrentTimeForTest(&sTime_21_01);
    Pokegotchi_Sync();
    EXPECT_EQ(Pokegotchi_GetStats()->food, 250);

    Pokegotchi_ResetStateForTest();
    Pokegotchi_SetCurrentTimeForTest(&sTime_21_02);
    Pokegotchi_Sync();
    EXPECT_EQ(Pokegotchi_GetStats()->food, 250);

    ResetPokegotchiTestState();
    Pokegotchi_SetCurrentTimeForTest(&sTime_21_00);
    Pokegotchi_EnsureInitialized();
    Pokegotchi_SetCurrentTimeForTest(&sTime_21_03);
    Pokegotchi_Sync();
    EXPECT_EQ(Pokegotchi_GetStats()->food, 249);
}

TEST("(Pokegotchi) Sleep freezes poop decay and generation")
{
    const struct PokegotchiStats *stats;

    ResetPokegotchiTestState();
    Pokegotchi_SetCurrentTimeForTest(&sTime_21_00);
    Pokegotchi_EnsureInitialized();
    Pokegotchi_BeginSession();
    SET_RNG(RNG_POKEGOTCHI_POOP, 0);

    Pokegotchi_SetCurrentTimeForTest(&sTime_23_00);
    Pokegotchi_Sync();
    stats = Pokegotchi_GetStats();

    EXPECT_EQ(stats->food, 190);
    EXPECT_EQ(stats->poop, 250);
    EXPECT_EQ(stats->poopsOnScreen, 0);
}

TEST("(Pokegotchi) A woken pet uses regular active decay during sleep time")
{
    const struct PokegotchiStats *stats;

    ResetPokegotchiTestState();
    Pokegotchi_SetCurrentTimeForTest(&sTime_21_00);
    Pokegotchi_EnsureInitialized();
    Pokegotchi_BeginSession();
    Pokegotchi_SetWokenDuringSleepForTest(TRUE);

    EXPECT_EQ(Pokegotchi_IsSleeping(), FALSE);
    Pokegotchi_SetCurrentTimeForTest(&sTime_21_01);
    Pokegotchi_Sync();
    stats = Pokegotchi_GetStats();

    EXPECT_EQ(stats->food, 248);
    EXPECT_EQ(stats->fun, 248);
    EXPECT_EQ(stats->happy, 248);
    EXPECT_EQ(stats->poop, 248);
}

TEST("(Pokegotchi) Interaction reactions follow stat priority and boundaries")
{
    static const struct
    {
        u16 food;
        u16 fun;
        u16 happy;
        enum PokegotchiInteractionReaction reaction;
    } cases[] =
    {
        {  0,   0,   0, POKEGOTCHI_REACTION_SULKING},
        {  0,  50, 151, POKEGOTCHI_REACTION_HAPPY_ONCE},
        {100, 151, 151, POKEGOTCHI_REACTION_HAPPY_ONCE},
        {101, 101, 151, POKEGOTCHI_REACTION_HAPPY_TWICE_SUN},
        {  0,   1,   0, POKEGOTCHI_REACTION_ANGRY_TWICE},
        {  1,   0,   0, POKEGOTCHI_REACTION_SAD_TWICE},
        {151, 151,   0, POKEGOTCHI_REACTION_HAPPY_TWICE},
        {151, 151, 150, POKEGOTCHI_REACTION_HAPPY_TWICE},
        {150, 150,   0, POKEGOTCHI_REACTION_HAPPY_ONCE},
        {100, 101,   0, POKEGOTCHI_REACTION_ANGRY_ONCE},
        {101, 100,   0, POKEGOTCHI_REACTION_SAD_ONCE},
        {100, 100,   1, POKEGOTCHI_REACTION_SAD_TWICE},
    };
    u32 i;

    for (i = 0; i < ARRAY_COUNT(cases); i++)
    {
        struct PokegotchiStats stats =
        {
            .food = cases[i].food,
            .fun = cases[i].fun,
            .happy = cases[i].happy,
        };

        EXPECT_EQ(Pokegotchi_GetInteractionReaction(&stats), cases[i].reaction);
    }
}

TEST("(Pokegotchi) Active sleep phase is cleared in the morning")
{
    ResetPokegotchiTestState();
    Pokegotchi_SetCurrentTimeForTest(&sTime_Day1_04_58);
    Pokegotchi_EnsureInitialized();
    Pokegotchi_BeginSession();

    Pokegotchi_SetCurrentTimeForTest(&sTime_Day1_04_59);
    Pokegotchi_Sync();
    EXPECT_EQ(Pokegotchi_GetStats()->food, 250);

    Pokegotchi_SetCurrentTimeForTest(&sTime_Day1_05_00);
    Pokegotchi_Sync();
    EXPECT_EQ(Pokegotchi_GetStats()->food, 249);

    Pokegotchi_SetCurrentTimeForTest(&(struct Time){.days = 1, .hours = 5, .minutes = 1});
    Pokegotchi_Sync();
    EXPECT_EQ(Pokegotchi_GetStats()->food, 247);
}

TEST("(Pokegotchi) Poop generation stops at the maximum of 4")
{
    const struct PokegotchiStats *stats;

    ResetPokegotchiTestState();
    Pokegotchi_SetCurrentTimeForTest(&sTime_10_00);
    Pokegotchi_EnsureInitialized();
    Pokegotchi_BeginSession();
    SET_RNG(RNG_POKEGOTCHI_POOP, 0);

    Pokegotchi_SetCurrentTimeForTest(&sTime_11_50);
    Pokegotchi_Sync();
    stats = Pokegotchi_GetStats();

    EXPECT_EQ(stats->poopsOnScreen, POKEGOTCHI_MAX_POOPS);
    EXPECT_EQ(stats->poop, 238);
}

TEST("(Pokegotchi) Existing excess poops are clamped and skip generation")
{
    struct PokegotchiRuntimeState *runtime;

    ResetPokegotchiTestState();
    Pokegotchi_SetCurrentTimeForTest(&sTime_10_00);
    Pokegotchi_EnsureInitialized();
    runtime = PokegotchiSave_GetRuntimeMutable();
    runtime->stats.poopsOnScreen = POKEGOTCHI_MAX_POOPS + 3;

    EXPECT_EQ(Pokegotchi_GetStats()->poopsOnScreen, POKEGOTCHI_MAX_POOPS);
    Pokegotchi_BeginSession();
    Pokegotchi_SetCurrentTimeForTest(&sTime_10_10);
    Pokegotchi_Sync();
    EXPECT_EQ(Pokegotchi_GetStats()->poopsOnScreen, POKEGOTCHI_MAX_POOPS);
    EXPECT_EQ(Pokegotchi_GetStats()->poop, 230);
}
