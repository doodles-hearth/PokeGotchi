#include "global.h"
#include "load_save.h"
#include "pokegotchi.h"
#include "pokegotchi_save.h"
#include "test/test.h"

static const struct Time sTime_00_00 = {.days = 0, .hours = 0, .minutes = 0, .seconds = 0};
static const struct Time sTime_00_01 = {.days = 0, .hours = 0, .minutes = 1, .seconds = 0};
static const struct Time sTime_00_02 = {.days = 0, .hours = 0, .minutes = 2, .seconds = 0};
static const struct Time sTime_00_10 = {.days = 0, .hours = 0, .minutes = 10, .seconds = 0};
static const struct Time sTime_00_16 = {.days = 0, .hours = 0, .minutes = 16, .seconds = 0};
static const struct Time sTime_00_26 = {.days = 0, .hours = 0, .minutes = 26, .seconds = 0};
static const struct Time sTime_03_00 = {.days = 0, .hours = 3, .minutes = 0, .seconds = 0};
static const struct Time sTime_10_00 = {.days = 0, .hours = 10, .minutes = 0, .seconds = 0};
static const struct Time sTime_09_00 = {.days = 0, .hours = 9, .minutes = 0, .seconds = 0};

static void ResetPokegotchiTestState(void)
{
    SetSaveBlocksPointers(0);
    PokegotchiSave_ClearForTest();
    ClearSav1();
    ClearSav2();
    ClearSav3();
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
    EXPECT_EQ(runtime->food.pecha, 10);
}

TEST("(Pokegotchi) One active minute reduces all four meters by two")
{
    const struct PokegotchiStats *stats;

    ResetPokegotchiTestState();
    Pokegotchi_SetCurrentTimeForTest(&sTime_00_00);
    Pokegotchi_EnsureInitialized();
    Pokegotchi_BeginSession();

    Pokegotchi_SetCurrentTimeForTest(&sTime_00_01);
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
    Pokegotchi_SetCurrentTimeForTest(&sTime_00_00);
    Pokegotchi_EnsureInitialized();

    Pokegotchi_SetCurrentTimeForTest(&sTime_00_02);
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
    Pokegotchi_SetCurrentTimeForTest(&sTime_00_00);
    Pokegotchi_EnsureInitialized();

    Pokegotchi_SetCurrentTimeForTest(&sTime_00_10);
    Pokegotchi_BeginSession();

    Pokegotchi_SetCurrentTimeForTest(&sTime_00_16);
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
    Pokegotchi_SetCurrentTimeForTest(&sTime_00_00);
    Pokegotchi_EnsureInitialized();
    Pokegotchi_BeginSession();

    Pokegotchi_SetCurrentTimeForTest(&sTime_03_00);
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
    Pokegotchi_SetCurrentTimeForTest(&sTime_00_00);
    Pokegotchi_EnsureInitialized();
    Pokegotchi_BeginSession();
    SET_RNG(RNG_POKEGOTCHI_POOP, 0);

    Pokegotchi_SetCurrentTimeForTest(&sTime_00_26);
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
