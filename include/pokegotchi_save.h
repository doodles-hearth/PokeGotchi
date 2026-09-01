#ifndef GUARD_POKEGOTCHI_SAVE_H
#define GUARD_POKEGOTCHI_SAVE_H

#include "global.h"
#include "constants/flags.h"

#define POKEGOTCHI_SAVE_MAGIC   0x50475443
#define POKEGOTCHI_SAVE_VERSION 3
#define POKEGOTCHI_SAVE_SLOT_COUNT 2

struct PokegotchiRuntimeState
{
    u8 playerPartyCount;
    u8 filler[3];
    struct Pokemon playerParty[PARTY_SIZE];
    struct PokegotchiFood food;
    struct PokegotchiStats stats;
    u8 playerTrainerId[TRAINER_ID_LENGTH];
    u8 playerName[PLAYER_NAME_LENGTH + 1];
    u8 playerGender;
    u8 optionsSound;
    u8 flags[POKEGOTCHI_FLAG_BYTES];
};

struct PokegotchiPersistedPayload
{
    u8 playerPartyCount;
    u8 filler[3];
    struct Pokemon playerParty[PARTY_SIZE];
    struct PokegotchiFood food;
    struct PokegotchiStats stats;
    u8 playerTrainerId[TRAINER_ID_LENGTH];
    u8 playerName[PLAYER_NAME_LENGTH + 1];
    u8 playerGender;
    u8 optionsSound;
    u8 flags[POKEGOTCHI_FLAG_BYTES];
};

struct PokegotchiPersistedSave
{
    u32 magic;
    u16 version;
    u16 payloadSize;
    u32 saveCounter;
    u32 checksum;
    struct PokegotchiPersistedPayload payload;
};

const struct PokegotchiRuntimeState *PokegotchiSave_GetRuntime(void);
struct PokegotchiRuntimeState *PokegotchiSave_GetRuntimeMutable(void);
bool8 PokegotchiSave_InitOrLoad(void);
u8 PokegotchiSave_Commit(void);
void PokegotchiSave_ResetToDefaults(void);
void PokegotchiSave_ClearRuntimeState(void);
void PokegotchiSave_ClearStorage(void);

#if TESTING
void PokegotchiSave_ClearForTest(void);
void PokegotchiSave_CorruptSlotForTest(u32 slot);
void PokegotchiSave_PartialCommitForTest(u32 bytesToWrite);
void PokegotchiSave_SetSlotVersionForTest(u32 slot, u16 version);
#endif

#endif // GUARD_POKEGOTCHI_SAVE_H
