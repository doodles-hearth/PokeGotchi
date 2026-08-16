#include "global.h"
#include "load_save.h"
#include "pokegotchi.h"
#include "pokegotchi_save.h"
#include "save.h"
#include "test/test.h"

// If you would like to ensure save compatibility, update the values below with those for your hack. You can find these through the debug menu.
// Please note that this simple check is not 100% foolproof, but should be able to catch most unintended shifts.
#define T_POKEGOTCHI_SAVE_DATA_SIZE 660
#define T_POKEGOTCHI_STAGED_WRITE_BYTES (sizeof(struct PokegotchiPersistedSave) - sizeof(((struct PokegotchiPersistedSave *)0)->magic))

static void ResetSaveTestState(void)
{
    SetSaveBlocksPointers(0);
    PokegotchiSave_ClearForTest();
    ClearSav1();
    ClearSav2();
    ClearSav3();
    Save_ResetSaveCounters();
    Pokegotchi_ResetStateForTest();
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
    EXPECT_EQ(runtime->food.pecha, 10);
    EXPECT_EQ(runtime->stats.version, 1);
    EXPECT_EQ(runtime->playerPartyCount, 0);
    EXPECT_EQ((u32)runtime->optionsSound, OPTIONS_SOUND_MONO);
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
    runtime->food.pecha = 9;
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

    SetMonData(&mon, MON_DATA_SPECIES, &(u16){SPECIES_BULBASAUR});
    SetMonData(&mon, MON_DATA_LEVEL, &(u8){12});
    runtime->playerParty[0] = mon;

    EXPECT_EQ(PokegotchiSave_Commit(), SAVE_STATUS_OK);

    ClearSav1();
    ClearSav2();
    ClearSav3();
    Pokegotchi_ResetStateForTest();

    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    loaded = PokegotchiSave_GetRuntime();
    loadedMon = loaded->playerParty[0];

    EXPECT_EQ(loaded->playerPartyCount, 1);
    EXPECT_EQ(loaded->food.leaf, 17);
    EXPECT_EQ(loaded->food.pecha, 9);
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
    EXPECT_EQ(GetMonData(&loadedMon, MON_DATA_SPECIES), SPECIES_BULBASAUR);
    EXPECT_EQ(GetMonData(&loadedMon, MON_DATA_LEVEL), 12);
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

    ClearSav1();
    ClearSav2();
    ClearSav3();
    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->food.leaf, 22);

    PokegotchiSave_CorruptSlotForTest(0);
    ClearSav1();
    ClearSav2();
    ClearSav3();
    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->food.leaf, 11);
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

    ClearSav1();
    ClearSav2();
    ClearSav3();

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

    ClearSav1();
    ClearSav2();
    ClearSav3();

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

    ClearSav1();
    ClearSav2();
    ClearSav3();

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
    ClearSav1();
    ClearSav2();
    ClearSav3();

    EXPECT_EQ(PokegotchiSave_InitOrLoad(), FALSE);
    EXPECT_EQ(gSaveFileStatus, SAVE_STATUS_CORRUPT);

    Pokegotchi_EnsureInitialized();
    EXPECT_EQ(PokegotchiSave_GetRuntime()->food.leaf, 200);
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

    ClearSav1();
    ClearSav2();
    ClearSav3();
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

TEST("(Pokegotchi) MoveSaveBlocks_ResetHeap does not corrupt runtime saves")
{
    struct PokegotchiRuntimeState *runtime;

    ResetSaveTestState();
    runtime = PokegotchiSave_GetRuntimeMutable();
    runtime->food.leaf = 66;
    runtime->playerPartyCount = 1;
    runtime->playerTrainerId[0] = 9;
    PokegotchiSave_Commit();

    gSaveBlock2Ptr->encryptionKey = 1234;
    MoveSaveBlocks_ResetHeap();

    EXPECT_EQ(PokegotchiSave_Commit(), SAVE_STATUS_OK);

    ClearSav1();
    ClearSav2();
    ClearSav3();
    EXPECT_EQ(PokegotchiSave_InitOrLoad(), TRUE);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->food.leaf, 66);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->playerPartyCount, 1);
    EXPECT_EQ(PokegotchiSave_GetRuntime()->playerTrainerId[0], 9);
}

#undef T_POKEGOTCHI_SAVE_DATA_SIZE
#undef T_POKEGOTCHI_STAGED_WRITE_BYTES
