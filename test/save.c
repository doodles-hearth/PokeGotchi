#include "global.h"
#include "constants/flags.h"
#include "event_data.h"
#include "fake_rtc.h"
#include "load_save.h"
#include "pokegotchi.h"
#include "pokegotchi_save.h"
#include "save.h"
#include "test/overworld_script.h"
#include "test/test.h"

// If you would like to ensure save compatibility, update the values below with those for your hack. You can find these through the debug menu.
// Please note that this simple check is not 100% foolproof, but should be able to catch most unintended shifts.
#define T_POKEGOTCHI_SAVE_DATA_SIZE 668
#define T_POKEGOTCHI_STAGED_WRITE_BYTES (sizeof(struct PokegotchiPersistedSave) - sizeof(((struct PokegotchiPersistedSave *)0)->magic))

static void ExpectPokegotchiFlagsCleared(void)
{
    EXPECT_EQ(PokegotchiSave_GetRuntime()->flags[0], 0);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->flags[1], 0);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->flags[2], 0);
}

static void ResetSaveTestStateWithBackend(bool32 flashPresent)
{
    gFlashMemoryPresent = flashPresent;
    SetSaveBlocksPointers(0);
    PokegotchiSave_ClearForTest();
    FakeRtc_Reset();
    Save_ResetSaveCounters();
    Pokegotchi_ResetStateForTest();
}

static void ResetSaveTestState(void)
{
    ResetSaveTestStateWithBackend(FALSE);
}

TEST("(Pokegotchi) Save data size is expected")
{
    EXPECT_EQ(sizeof(struct PokegotchiPersistedSave), T_POKEGOTCHI_SAVE_DATA_SIZE);
}

TEST("(Pokegotchi) Blank SRAM boot initializes defaults")
{
    const struct PokegotchiRuntimeState *runtime;

    ResetSaveTestState();

    EXPECT_EQ(PokegotchiSave_InitOrLoad(), FALSE);
    EXPECT_EQ(gSaveFileStatus, SAVE_STATUS_EMPTY);

    Pokegotchi_EnsureInitialized();
    runtime = PokegotchiSave_GetRuntime();

    EXPECT_EQ(runtime->food.leaf, 10);
    EXPECT_EQ(runtime->food.hotDog, 0);
    EXPECT_EQ(runtime->food.pokeblock, 0);
    EXPECT_EQ(runtime->food.egg, 0);
    EXPECT_EQ(runtime->food.pecha, 10);
    EXPECT_EQ(runtime->food.iceCream, 0);
    EXPECT_EQ(runtime->food.donut, 0);
    EXPECT_EQ(runtime->food.snack4, 0);
    EXPECT_EQ(runtime->stats.version, 1);
    EXPECT_EQ(runtime->playerPartyCount, 1);
    EXPECT_EQ((u32)runtime->optionsSound, OPTIONS_SOUND_MONO);
    ExpectPokegotchiFlagsCleared();
}

TEST("(Pokegotchi) Blank flash boot initializes defaults")
{
    const struct PokegotchiRuntimeState *runtime;

    ResetSaveTestStateWithBackend(TRUE);

    EXPECT_EQ(PokegotchiSave_InitOrLoad(), FALSE);
    EXPECT_EQ(gSaveFileStatus, SAVE_STATUS_EMPTY);

    Pokegotchi_EnsureInitialized();
    runtime = PokegotchiSave_GetRuntime();

    EXPECT_EQ(runtime->food.leaf, 10);
    EXPECT_EQ(runtime->food.hotDog, 0);
    EXPECT_EQ(runtime->food.pokeblock, 0);
    EXPECT_EQ(runtime->food.egg, 0);
    EXPECT_EQ(runtime->food.pecha, 10);
    EXPECT_EQ(runtime->food.iceCream, 0);
    EXPECT_EQ(runtime->food.donut, 0);
    EXPECT_EQ(runtime->food.snack4, 0);
    EXPECT_EQ(runtime->stats.version, 1);
    EXPECT_EQ(runtime->playerPartyCount, 1);
    EXPECT_EQ((u32)runtime->optionsSound, OPTIONS_SOUND_MONO);
    ExpectPokegotchiFlagsCleared();
}

TEST("(Pokegotchi) SRAM save round-trip preserves runtime payload")
{
    struct PokegotchiRuntimeState *runtime;
    const struct PokegotchiRuntimeState *loaded;
    struct Pokemon mon = {0};
    struct Pokemon loadedMon;

    ResetSaveTestState();
    runtime = PokegotchiSave_GetRuntimeMutable();

    runtime->playerPartyCount = 1;
    runtime->food.leaf = 17;
    runtime->food.hotDog = 16;
    runtime->food.pokeblock = 15;
    runtime->food.egg = 14;
    runtime->food.pecha = 9;
    runtime->food.iceCream = 8;
    runtime->food.donut = 7;
    runtime->food.snack4 = 6;
    runtime->stats.version = 7;
    runtime->stats.food = 111;
    runtime->stats.fun = 112;
    runtime->stats.happy = 113;
    runtime->stats.poop = 114;
    runtime->stats.poopsOnScreen = 3;
    runtime->stats.lastUpdated.days = 4;
    runtime->stats.lastUpdated.hours = 5;
    runtime->stats.lastUpdated.minutes = 6;
    runtime->stats.lastUpdated.seconds = 7;
    runtime->playerTrainerId[0] = 0x12;
    runtime->playerTrainerId[1] = 0x34;
    runtime->playerTrainerId[2] = 0x56;
    runtime->playerTrainerId[3] = 0x78;
    runtime->playerName[0] = 0x11;
    runtime->playerName[1] = 0x22;
    runtime->playerName[2] = 0;
    runtime->playerGender = FEMALE;
    runtime->optionsSound = OPTIONS_SOUND_STEREO;
    runtime->flags[0] = (1 << 0) | (1 << 5);
    runtime->flags[1] = (1 << 1);
    runtime->flags[2] = (1 << 7);

    SetMonData(&mon, MON_DATA_SPECIES, &(u16){SPECIES_BULBASAUR});
    SetMonData(&mon, MON_DATA_LEVEL, &(u8){12});
    runtime->playerParty[0] = mon;

    EXPECT_EQ(PokegotchiSave_Commit(), SAVE_STATUS_OK);

    Pokegotchi_ResetStateForTest();

    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    loaded = PokegotchiSave_GetRuntime();
    loadedMon = loaded->playerParty[0];

    EXPECT_EQ(loaded->playerPartyCount, 1);
    EXPECT_EQ(loaded->food.leaf, 17);
    EXPECT_EQ(loaded->food.hotDog, 16);
    EXPECT_EQ(loaded->food.pokeblock, 15);
    EXPECT_EQ(loaded->food.egg, 14);
    EXPECT_EQ(loaded->food.pecha, 9);
    EXPECT_EQ(loaded->food.iceCream, 8);
    EXPECT_EQ(loaded->food.donut, 7);
    EXPECT_EQ(loaded->food.snack4, 6);
    EXPECT_EQ(loaded->stats.version, 7);
    EXPECT_EQ(loaded->stats.food, 111);
    EXPECT_EQ(loaded->stats.fun, 112);
    EXPECT_EQ(loaded->stats.happy, 113);
    EXPECT_EQ(loaded->stats.poop, 114);
    EXPECT_EQ(loaded->stats.poopsOnScreen, 3);
    EXPECT_EQ(loaded->stats.lastUpdated.days, 4);
    EXPECT_EQ(loaded->stats.lastUpdated.hours, 5);
    EXPECT_EQ(loaded->stats.lastUpdated.minutes, 6);
    EXPECT_EQ(loaded->stats.lastUpdated.seconds, 7);
    EXPECT_EQ(loaded->playerTrainerId[0], 0x12);
    EXPECT_EQ(loaded->playerTrainerId[1], 0x34);
    EXPECT_EQ(loaded->playerTrainerId[2], 0x56);
    EXPECT_EQ(loaded->playerTrainerId[3], 0x78);
    EXPECT_EQ(loaded->playerName[0], 0x11);
    EXPECT_EQ(loaded->playerName[1], 0x22);
    EXPECT_EQ(loaded->playerGender, FEMALE);
    EXPECT_EQ(loaded->optionsSound, OPTIONS_SOUND_STEREO);
    EXPECT_EQ(loaded->flags[0], (1 << 0) | (1 << 5));
    EXPECT_EQ(loaded->flags[1], (1 << 1));
    EXPECT_EQ(loaded->flags[2], (1 << 7));
    EXPECT_EQ(GetMonData(&loadedMon, MON_DATA_SPECIES), SPECIES_BULBASAUR);
    EXPECT_EQ(GetMonData(&loadedMon, MON_DATA_LEVEL), 12);
}

TEST("(Pokegotchi) Flash save round-trip preserves runtime payload")
{
    struct PokegotchiRuntimeState *runtime;
    const struct PokegotchiRuntimeState *loaded;
    struct Pokemon mon = {0};
    struct Pokemon loadedMon;

    ResetSaveTestStateWithBackend(TRUE);
    runtime = PokegotchiSave_GetRuntimeMutable();

    runtime->playerPartyCount = 1;
    runtime->food.leaf = 37;
    runtime->food.hotDog = 36;
    runtime->food.pokeblock = 35;
    runtime->food.egg = 34;
    runtime->food.pecha = 19;
    runtime->food.iceCream = 18;
    runtime->food.donut = 17;
    runtime->food.snack4 = 16;
    runtime->stats.version = 12;
    runtime->stats.food = 211;
    runtime->stats.fun = 212;
    runtime->stats.happy = 213;
    runtime->stats.poop = 214;
    runtime->stats.poopsOnScreen = 2;
    runtime->stats.lastUpdated.days = 8;
    runtime->stats.lastUpdated.hours = 9;
    runtime->stats.lastUpdated.minutes = 10;
    runtime->stats.lastUpdated.seconds = 11;
    runtime->playerTrainerId[0] = 0x9A;
    runtime->playerTrainerId[1] = 0xBC;
    runtime->playerTrainerId[2] = 0xDE;
    runtime->playerTrainerId[3] = 0xF0;
    runtime->playerName[0] = 0x44;
    runtime->playerName[1] = 0x55;
    runtime->playerName[2] = 0;
    runtime->playerGender = MALE;
    runtime->optionsSound = OPTIONS_SOUND_STEREO;
    runtime->flags[0] = (1 << 2);
    runtime->flags[1] = (1 << 4) | (1 << 7);
    runtime->flags[2] = (1 << 3);

    SetMonData(&mon, MON_DATA_SPECIES, &(u16){SPECIES_CHARMANDER});
    SetMonData(&mon, MON_DATA_LEVEL, &(u8){16});
    runtime->playerParty[0] = mon;

    EXPECT_EQ(PokegotchiSave_Commit(), SAVE_STATUS_OK);

    Pokegotchi_ResetStateForTest();

    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    loaded = PokegotchiSave_GetRuntime();
    loadedMon = loaded->playerParty[0];

    EXPECT_EQ(loaded->playerPartyCount, 1);
    EXPECT_EQ(loaded->food.leaf, 37);
    EXPECT_EQ(loaded->food.hotDog, 36);
    EXPECT_EQ(loaded->food.pokeblock, 35);
    EXPECT_EQ(loaded->food.egg, 34);
    EXPECT_EQ(loaded->food.pecha, 19);
    EXPECT_EQ(loaded->food.iceCream, 18);
    EXPECT_EQ(loaded->food.donut, 17);
    EXPECT_EQ(loaded->food.snack4, 16);
    EXPECT_EQ(loaded->stats.version, 12);
    EXPECT_EQ(loaded->stats.food, 211);
    EXPECT_EQ(loaded->stats.fun, 212);
    EXPECT_EQ(loaded->stats.happy, 213);
    EXPECT_EQ(loaded->stats.poop, 214);
    EXPECT_EQ(loaded->stats.poopsOnScreen, 2);
    EXPECT_EQ(loaded->stats.lastUpdated.days, 8);
    EXPECT_EQ(loaded->stats.lastUpdated.hours, 9);
    EXPECT_EQ(loaded->stats.lastUpdated.minutes, 10);
    EXPECT_EQ(loaded->stats.lastUpdated.seconds, 11);
    EXPECT_EQ(loaded->playerTrainerId[0], 0x9A);
    EXPECT_EQ(loaded->playerTrainerId[1], 0xBC);
    EXPECT_EQ(loaded->playerTrainerId[2], 0xDE);
    EXPECT_EQ(loaded->playerTrainerId[3], 0xF0);
    EXPECT_EQ(loaded->playerName[0], 0x44);
    EXPECT_EQ(loaded->playerName[1], 0x55);
    EXPECT_EQ(loaded->playerGender, MALE);
    EXPECT_EQ(loaded->optionsSound, OPTIONS_SOUND_STEREO);
    EXPECT_EQ(loaded->flags[0], (1 << 2));
    EXPECT_EQ(loaded->flags[1], (1 << 4) | (1 << 7));
    EXPECT_EQ(loaded->flags[2], (1 << 3));
    EXPECT_EQ(GetMonData(&loadedMon, MON_DATA_SPECIES), SPECIES_CHARMANDER);
    EXPECT_EQ(GetMonData(&loadedMon, MON_DATA_LEVEL), 16);
}

TEST("(Pokegotchi) SRAM picks the newest valid slot and falls back on corruption")
{
    struct PokegotchiRuntimeState *runtime;

    ResetSaveTestState();
    runtime = PokegotchiSave_GetRuntimeMutable();

    runtime->food.leaf = 11;
    PokegotchiSave_Commit();

    runtime->food.leaf = 22;
    PokegotchiSave_Commit();

    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->food.leaf, 22);

    PokegotchiSave_CorruptSlotForTest(0);
    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->food.leaf, 11);
}

TEST("(Pokegotchi) Flash picks the newest valid slot and falls back on corruption")
{
    struct PokegotchiRuntimeState *runtime;

    ResetSaveTestStateWithBackend(TRUE);
    runtime = PokegotchiSave_GetRuntimeMutable();

    runtime->food.leaf = 71;
    PokegotchiSave_Commit();

    runtime->food.leaf = 82;
    PokegotchiSave_Commit();

    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->food.leaf, 82);

    PokegotchiSave_CorruptSlotForTest(0);
    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->food.leaf, 71);
}

TEST("(Pokegotchi) SRAM ignores torn writes that stop before final magic")
{
    struct PokegotchiRuntimeState *runtime;

    ResetSaveTestState();
    runtime = PokegotchiSave_GetRuntimeMutable();

    runtime->food.leaf = 11;
    EXPECT_EQ(PokegotchiSave_Commit(), SAVE_STATUS_OK);

    runtime->food.leaf = 22;
    PokegotchiSave_PartialCommitForTest(T_POKEGOTCHI_STAGED_WRITE_BYTES);

    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->food.leaf, 11);
}

TEST("(Pokegotchi) SRAM keeps older slot after interruption immediately after invalidation")
{
    struct PokegotchiRuntimeState *runtime;

    ResetSaveTestState();
    runtime = PokegotchiSave_GetRuntimeMutable();

    runtime->food.leaf = 11;
    EXPECT_EQ(PokegotchiSave_Commit(), SAVE_STATUS_OK);

    runtime->food.leaf = 22;
    PokegotchiSave_PartialCommitForTest(0);

    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->food.leaf, 11);
}

TEST("(Pokegotchi) SRAM replaces an interrupted slot with a later successful commit")
{
    struct PokegotchiRuntimeState *runtime;

    ResetSaveTestState();
    runtime = PokegotchiSave_GetRuntimeMutable();

    runtime->food.leaf = 11;
    EXPECT_EQ(PokegotchiSave_Commit(), SAVE_STATUS_OK);

    runtime->food.leaf = 22;
    PokegotchiSave_PartialCommitForTest(T_POKEGOTCHI_STAGED_WRITE_BYTES);

    runtime->food.leaf = 33;
    EXPECT_EQ(PokegotchiSave_Commit(), SAVE_STATUS_OK);

    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->food.leaf, 33);
}

TEST("(Pokegotchi) SRAM defaults when both slots are invalid")
{
    struct PokegotchiRuntimeState *runtime;

    ResetSaveTestState();
    runtime = PokegotchiSave_GetRuntimeMutable();
    runtime->food.leaf = 33;
    PokegotchiSave_Commit();
    runtime->food.leaf = 44;
    PokegotchiSave_Commit();

    PokegotchiSave_CorruptSlotForTest(0);
    PokegotchiSave_CorruptSlotForTest(1);
    EXPECT_EQ(PokegotchiSave_InitOrLoad(), FALSE);
    EXPECT_EQ(gSaveFileStatus, SAVE_STATUS_CORRUPT);

    Pokegotchi_EnsureInitialized();
    EXPECT_EQ(PokegotchiSave_GetRuntime()->food.leaf, 10);
}

TEST("(Pokegotchi) Flash defaults when both slots are invalid")
{
    struct PokegotchiRuntimeState *runtime;

    ResetSaveTestStateWithBackend(TRUE);
    runtime = PokegotchiSave_GetRuntimeMutable();
    runtime->food.leaf = 93;
    PokegotchiSave_Commit();
    runtime->food.leaf = 104;
    PokegotchiSave_Commit();

    PokegotchiSave_CorruptSlotForTest(0);
    PokegotchiSave_CorruptSlotForTest(1);
    EXPECT_EQ(PokegotchiSave_InitOrLoad(), FALSE);
    EXPECT_EQ(gSaveFileStatus, SAVE_STATUS_CORRUPT);

    Pokegotchi_EnsureInitialized();
    EXPECT_EQ(PokegotchiSave_GetRuntime()->food.leaf, 10);
}

TEST("(Pokegotchi) Flash presence takes precedence over SRAM contents")
{
    struct PokegotchiRuntimeState *runtime;

    ResetSaveTestStateWithBackend(FALSE);
    runtime = PokegotchiSave_GetRuntimeMutable();
    runtime->food.leaf = 15;
    EXPECT_EQ(PokegotchiSave_Commit(), SAVE_STATUS_OK);

    gFlashMemoryPresent = TRUE;
    runtime = PokegotchiSave_GetRuntimeMutable();
    runtime->food.leaf = 88;
    EXPECT_EQ(PokegotchiSave_Commit(), SAVE_STATUS_OK);

    Pokegotchi_ResetStateForTest();
    gFlashMemoryPresent = TRUE;
    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->food.leaf, 88);

    Pokegotchi_ResetStateForTest();
    gFlashMemoryPresent = FALSE;
    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->food.leaf, 15);
}

TEST("(Pokegotchi) Flag functions route reserved IDs into Pokegotchi saves")
{
    struct PokegotchiRuntimeState *runtime;

    ResetSaveTestState();
    runtime = PokegotchiSave_GetRuntimeMutable();

    EXPECT_EQ(gSaveBlock1Ptr->flags[POKEGOTCHI_FLAGS_START / 8], 0);
    FlagSet(POKEGOTCHI_FLAG_01);
    FlagSet(POKEGOTCHI_FLAG_10);
    FlagSet(POKEGOTCHI_FLAG_24);

    EXPECT(FlagGet(POKEGOTCHI_FLAG_01));
    EXPECT(FlagGet(POKEGOTCHI_FLAG_10));
    EXPECT(FlagGet(POKEGOTCHI_FLAG_24));
    EXPECT_EQ(runtime->flags[0], 1 << 0);
    EXPECT_EQ(runtime->flags[1], 1 << 1);
    EXPECT_EQ(runtime->flags[2], 1 << 7);
    EXPECT_EQ(gSaveBlock1Ptr->flags[POKEGOTCHI_FLAGS_START / 8], 0);

    FlagToggle(POKEGOTCHI_FLAG_10);
    EXPECT(!FlagGet(POKEGOTCHI_FLAG_10));
    EXPECT_EQ(runtime->flags[1], 0);

    FlagClear(POKEGOTCHI_FLAG_24);
    EXPECT(!FlagGet(POKEGOTCHI_FLAG_24));
    EXPECT_EQ(runtime->flags[2], 0);
}

TEST("(Pokegotchi) Script flag commands use Pokegotchi storage")
{
    ResetSaveTestState();
    VarSet(VAR_TEMP_0, 0);
    VarSet(VAR_TEMP_1, 0);

    RUN_OVERWORLD_SCRIPT(
        setflag POKEGOTCHI_FLAG_03;
        checkflag POKEGOTCHI_FLAG_03;
        goto_if_eq FlagWasSet;
        setvar VAR_TEMP_0, 1;
        end;

      FlagWasSet:
        setvar VAR_TEMP_0, 2;
        clearflag POKEGOTCHI_FLAG_03;
        checkflag POKEGOTCHI_FLAG_03;
        goto_if_eq FlagStillSet;
        setvar VAR_TEMP_1, 3;
        end;

      FlagStillSet:
        setvar VAR_TEMP_1, 4;
        end;
    );

    EXPECT_EQ(VarGet(VAR_TEMP_0), 2);
    EXPECT_EQ(VarGet(VAR_TEMP_1), 3);
    EXPECT(!FlagGet(POKEGOTCHI_FLAG_03));
    ExpectPokegotchiFlagsCleared();
}

TEST("(Pokegotchi) SRAM persists Pokegotchi flags and keeps the older slot on corruption")
{
    struct PokegotchiRuntimeState *runtime;

    ResetSaveTestState();
    runtime = PokegotchiSave_GetRuntimeMutable();

    FlagSet(POKEGOTCHI_FLAG_01);
    FlagSet(POKEGOTCHI_FLAG_17);
    EXPECT_EQ(PokegotchiSave_Commit(), SAVE_STATUS_OK);

    FlagClear(POKEGOTCHI_FLAG_01);
    FlagSet(POKEGOTCHI_FLAG_24);
    EXPECT_EQ(PokegotchiSave_Commit(), SAVE_STATUS_OK);

    Pokegotchi_ResetStateForTest();
    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    runtime = PokegotchiSave_GetRuntimeMutable();
    EXPECT(!FlagGet(POKEGOTCHI_FLAG_01));
    EXPECT(FlagGet(POKEGOTCHI_FLAG_17));
    EXPECT(FlagGet(POKEGOTCHI_FLAG_24));
    EXPECT_EQ(runtime->flags[0], 0);
    EXPECT_EQ(runtime->flags[1], 0);
    EXPECT_EQ(runtime->flags[2], (1 << 0) | (1 << 7));

    PokegotchiSave_CorruptSlotForTest(0);
    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    EXPECT(FlagGet(POKEGOTCHI_FLAG_01));
    EXPECT(FlagGet(POKEGOTCHI_FLAG_17));
    EXPECT(!FlagGet(POKEGOTCHI_FLAG_24));
}

TEST("(Pokegotchi) Flash persists Pokegotchi flags and keeps the older slot on corruption")
{
    struct PokegotchiRuntimeState *runtime;

    ResetSaveTestStateWithBackend(TRUE);
    runtime = PokegotchiSave_GetRuntimeMutable();

    FlagSet(POKEGOTCHI_FLAG_02);
    FlagSet(POKEGOTCHI_FLAG_18);
    EXPECT_EQ(PokegotchiSave_Commit(), SAVE_STATUS_OK);

    FlagClear(POKEGOTCHI_FLAG_02);
    FlagSet(POKEGOTCHI_FLAG_23);
    EXPECT_EQ(PokegotchiSave_Commit(), SAVE_STATUS_OK);

    Pokegotchi_ResetStateForTest();
    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    runtime = PokegotchiSave_GetRuntimeMutable();
    EXPECT(!FlagGet(POKEGOTCHI_FLAG_02));
    EXPECT(FlagGet(POKEGOTCHI_FLAG_18));
    EXPECT(FlagGet(POKEGOTCHI_FLAG_23));
    EXPECT_EQ(runtime->flags[0], 0);
    EXPECT_EQ(runtime->flags[1], 0);
    EXPECT_EQ(runtime->flags[2], (1 << 1) | (1 << 6));

    PokegotchiSave_CorruptSlotForTest(0);
    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    EXPECT(FlagGet(POKEGOTCHI_FLAG_02));
    EXPECT(FlagGet(POKEGOTCHI_FLAG_18));
    EXPECT(!FlagGet(POKEGOTCHI_FLAG_23));
}

TEST("(Pokegotchi) Committing runtime fields persists")
{
    struct PokegotchiRuntimeState *runtime;

    ResetSaveTestState();

    runtime = PokegotchiSave_GetRuntimeMutable();
    runtime->playerPartyCount = 1;
    SetMonData(&runtime->playerParty[0], MON_DATA_SPECIES, &(u16){SPECIES_SQUIRTLE});
    runtime->playerTrainerId[0] = 1;
    runtime->playerTrainerId[1] = 2;
    runtime->playerTrainerId[2] = 3;
    runtime->playerTrainerId[3] = 4;
    runtime->playerName[0] = 0x33;
    runtime->playerName[1] = 0;
    runtime->playerGender = MALE;
    runtime->optionsSound = OPTIONS_SOUND_STEREO;

    EXPECT_EQ(PokegotchiSave_Commit(), SAVE_STATUS_OK);

    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);

    EXPECT_EQ(PokegotchiSave_GetRuntime()->playerPartyCount, 1);
    {
        struct Pokemon loadedMon = PokegotchiSave_GetRuntime()->playerParty[0];
        EXPECT_EQ(GetMonData(&loadedMon, MON_DATA_SPECIES), SPECIES_SQUIRTLE);
    }
    EXPECT_EQ(PokegotchiSave_GetRuntime()->playerTrainerId[0], 1);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->playerTrainerId[3], 4);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->playerName[0], 0x33);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->playerGender, MALE);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->optionsSound, OPTIONS_SOUND_STEREO);
}

#undef T_POKEGOTCHI_SAVE_DATA_SIZE
#undef T_POKEGOTCHI_STAGED_WRITE_BYTES
