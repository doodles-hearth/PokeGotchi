#include "global.h"
#include "pokegotchi_save.h"
#include "gba/defines.h"
#include "random.h"
#include "save.h"

#define POKEGOTCHI_SRAM_SIZE 0x8000

STATIC_ASSERT(sizeof(struct PokegotchiPersistedSave) * POKEGOTCHI_SAVE_SLOT_COUNT <= POKEGOTCHI_SRAM_SIZE,
              PokegotchiPersistedSaveFitsInSram);

static EWRAM_DATA struct PokegotchiRuntimeState sPokegotchiRuntimeState = {0};
static EWRAM_DATA u32 sPokegotchiSaveCounter = 0;

#if TESTING
static EWRAM_DATA u8 sPokegotchiTestSram[POKEGOTCHI_SRAM_SIZE] = {0};
#endif

static bool8 IsSlotBlank(const struct PokegotchiPersistedSave *save);
static bool8 IsSaveValid(const struct PokegotchiPersistedSave *save);
static const struct PokegotchiPersistedSave *GetPersistedSaveSlot(u32 slot);
static struct PokegotchiPersistedSave *GetPersistedSaveSlotMutable(u32 slot);
static void SetSramWaitstates(void);
ARM_FUNC __attribute__((section(".iwram.code"))) NOINLINE static void SramReadBytes(u8 *dst, const volatile u8 *src, u32 size);
ARM_FUNC __attribute__((section(".iwram.code"))) NOINLINE static void SramWriteBytes(volatile u8 *dst, const u8 *src, u32 size);
static void ReadPersistedSave(struct PokegotchiPersistedSave *dst, u32 slot);
static void WritePersistedSave(u32 slot, const struct PokegotchiPersistedSave *src);
#if TESTING
static void WritePersistedSavePartial(u32 slot, const struct PokegotchiPersistedSave *src, u32 bytesToWrite);
#endif
static void SerializeRuntimeState(struct PokegotchiPersistedSave *dst, u32 saveCounter);
static void DeserializeRuntimeState(const struct PokegotchiPersistedSave *src);
static volatile u8 *GetSaveMemoryBase(void);
static void WritePersistedSaveBytes(volatile u8 *dst, const struct PokegotchiPersistedSave *src, u32 bytesToWrite, bool8 writeMagic);

const struct PokegotchiRuntimeState *PokegotchiSave_GetRuntime(void)
{
    return &sPokegotchiRuntimeState;
}

struct PokegotchiRuntimeState *PokegotchiSave_GetRuntimeMutable(void)
{
    return &sPokegotchiRuntimeState;
}

bool8 PokegotchiSave_InitOrLoad(void)
{
    struct PokegotchiPersistedSave slots[POKEGOTCHI_SAVE_SLOT_COUNT];
    s32 bestSlot = -1;
    bool8 anyBlank = FALSE;
    bool8 anyCorrupt = FALSE;
    u32 i;

    for (i = 0; i < POKEGOTCHI_SAVE_SLOT_COUNT; i++)
    {
        ReadPersistedSave(&slots[i], i);
        if (IsSaveValid(&slots[i]))
        {
            if (bestSlot < 0 || slots[i].saveCounter > slots[bestSlot].saveCounter)
                bestSlot = i;
        }
        else if (IsSlotBlank(&slots[i]))
        {
            anyBlank = TRUE;
        }
        else
        {
            anyCorrupt = TRUE;
        }
    }

    if (bestSlot >= 0)
    {
        DeserializeRuntimeState(&slots[bestSlot]);
        sPokegotchiSaveCounter = slots[bestSlot].saveCounter;
        gSaveFileStatus = SAVE_STATUS_OK;
        return TRUE;
    }

    PokegotchiSave_ResetToDefaults();
    sPokegotchiSaveCounter = 0;
    gSaveFileStatus = anyCorrupt && !anyBlank ? SAVE_STATUS_CORRUPT : SAVE_STATUS_EMPTY;
    return FALSE;
}

u8 PokegotchiSave_Commit(void)
{
    struct PokegotchiPersistedSave save;
    u32 nextCounter;
    u32 slot;

    nextCounter = sPokegotchiSaveCounter + 1;
    slot = nextCounter % POKEGOTCHI_SAVE_SLOT_COUNT;
    SerializeRuntimeState(&save, nextCounter);
    WritePersistedSave(slot, &save);

    sPokegotchiSaveCounter = nextCounter;
    gSaveFileStatus = SAVE_STATUS_OK;
    return SAVE_STATUS_OK;
}

void PokegotchiSave_ResetToDefaults(void)
{
    CpuFill16(0, &sPokegotchiRuntimeState, sizeof(sPokegotchiRuntimeState));
    sPokegotchiRuntimeState.optionsSound = OPTIONS_SOUND_MONO;
    sPokegotchiSaveCounter = 0;
}

void PokegotchiSave_ClearRuntimeState(void)
{
    CpuFill16(0, &sPokegotchiRuntimeState, sizeof(sPokegotchiRuntimeState));
    sPokegotchiSaveCounter = 0;
}

void PokegotchiSave_ClearStorage(void)
{
    u32 i;
    volatile u8 *saveMemory = GetSaveMemoryBase();

    SetSramWaitstates();
    for (i = 0; i < POKEGOTCHI_SRAM_SIZE; i++)
        saveMemory[i] = 0xFF;
}

#if TESTING
void PokegotchiSave_ClearForTest(void)
{
    PokegotchiSave_ClearRuntimeState();
    PokegotchiSave_ClearStorage();
}

void PokegotchiSave_CorruptSlotForTest(u32 slot)
{
    struct PokegotchiPersistedSave save;

    if (slot >= POKEGOTCHI_SAVE_SLOT_COUNT)
        return;

    ReadPersistedSave(&save, slot);
    save.checksum ^= 0xFFFFFFFF;
    WritePersistedSave(slot, &save);
}

void PokegotchiSave_PartialCommitForTest(u32 bytesToWrite)
{
    struct PokegotchiPersistedSave save;
    u32 nextCounter = sPokegotchiSaveCounter + 1;
    u32 slot = nextCounter % POKEGOTCHI_SAVE_SLOT_COUNT;

    SerializeRuntimeState(&save, nextCounter);
    WritePersistedSavePartial(slot, &save, bytesToWrite);
}
#endif

static bool8 IsSlotBlank(const struct PokegotchiPersistedSave *save)
{
    const u8 *bytes = (const u8 *)save;
    bool8 allZero = TRUE;
    bool8 allFF = TRUE;
    u32 i;

    for (i = 0; i < sizeof(*save); i++)
    {
        if (bytes[i] != 0)
            allZero = FALSE;
        if (bytes[i] != 0xFF)
            allFF = FALSE;
    }

    return allZero || allFF;
}

static bool8 IsSaveValid(const struct PokegotchiPersistedSave *save)
{
    if (save->magic != POKEGOTCHI_SAVE_MAGIC)
        return FALSE;
    if (save->version != POKEGOTCHI_SAVE_VERSION)
        return FALSE;
    if (save->payloadSize != sizeof(save->payload))
        return FALSE;
    if (save->checksum != Crc32B((const u8 *)&save->payload, sizeof(save->payload)))
        return FALSE;

    return TRUE;
}

static const struct PokegotchiPersistedSave *GetPersistedSaveSlot(u32 slot)
{
    return (const struct PokegotchiPersistedSave *)(GetSaveMemoryBase() + sizeof(struct PokegotchiPersistedSave) * slot);
}

static struct PokegotchiPersistedSave *GetPersistedSaveSlotMutable(u32 slot)
{
    return (struct PokegotchiPersistedSave *)(GetSaveMemoryBase() + sizeof(struct PokegotchiPersistedSave) * slot);
}

static void SetSramWaitstates(void)
{
    // Use the conservative 8-cycle setting for raw save-chip access, matching the
    // existing flash path and the usual GBA guidance for SRAM/FRAM reads and writes.
    REG_WAITCNT = (REG_WAITCNT & ~WAITCNT_SRAM_MASK) | WAITCNT_SRAM_8;
}

// Game Pak SRAM is byte-addressable only, and hardware reads should use a WRAM-resident
// routine rather than relying on a ROM-side memcpy implementation.
ARM_FUNC __attribute__((section(".iwram.code"))) NOINLINE static void SramReadBytes(u8 *dst, const volatile u8 *src, u32 size)
{
    while (size-- != 0)
        *dst++ = *src++;
}

ARM_FUNC __attribute__((section(".iwram.code"))) NOINLINE static void SramWriteBytes(volatile u8 *dst, const u8 *src, u32 size)
{
    while (size-- != 0)
        *dst++ = *src++;
}

static void ReadPersistedSave(struct PokegotchiPersistedSave *dst, u32 slot)
{
    SetSramWaitstates();
    SramReadBytes((u8 *)dst, (const volatile u8 *)GetPersistedSaveSlot(slot), sizeof(*dst));
}

static void WritePersistedSave(u32 slot, const struct PokegotchiPersistedSave *src)
{
    volatile u8 *dst = (volatile u8 *)GetPersistedSaveSlotMutable(slot);

    SetSramWaitstates();
    WritePersistedSaveBytes(dst, src, sizeof(*src) - sizeof(src->magic), TRUE);
}

#if TESTING
static void WritePersistedSavePartial(u32 slot, const struct PokegotchiPersistedSave *src, u32 bytesToWrite)
{
    volatile u8 *dst = (volatile u8 *)GetPersistedSaveSlotMutable(slot);

    // Tests use this to emulate a power cut partway through a staged SRAM write.
    // The final magic word is intentionally omitted so the interrupted slot never
    // looks valid just because some earlier fields landed in SRAM first.
    SetSramWaitstates();
    WritePersistedSaveBytes(dst, src, bytesToWrite, FALSE);
}
#endif

static void SerializeRuntimeState(struct PokegotchiPersistedSave *dst, u32 saveCounter)
{
    CpuFill16(0, dst, sizeof(*dst));
    dst->magic = POKEGOTCHI_SAVE_MAGIC;
    dst->version = POKEGOTCHI_SAVE_VERSION;
    dst->payloadSize = sizeof(dst->payload);
    dst->saveCounter = saveCounter;
    dst->payload.playerPartyCount = sPokegotchiRuntimeState.playerPartyCount;
    memcpy(dst->payload.playerParty,
           sPokegotchiRuntimeState.playerParty,
           sizeof(dst->payload.playerParty));
    dst->payload.food = sPokegotchiRuntimeState.food;
    dst->payload.stats = sPokegotchiRuntimeState.stats;
    memcpy(dst->payload.playerTrainerId,
           sPokegotchiRuntimeState.playerTrainerId,
           sizeof(dst->payload.playerTrainerId));
    memcpy(dst->payload.playerName,
           sPokegotchiRuntimeState.playerName,
           sizeof(dst->payload.playerName));
    dst->payload.playerGender = sPokegotchiRuntimeState.playerGender;
    dst->payload.optionsSound = sPokegotchiRuntimeState.optionsSound;
    dst->checksum = Crc32B((const u8 *)&dst->payload, sizeof(dst->payload));
}

static void DeserializeRuntimeState(const struct PokegotchiPersistedSave *src)
{
    CpuFill16(0, &sPokegotchiRuntimeState, sizeof(sPokegotchiRuntimeState));
    sPokegotchiRuntimeState.playerPartyCount = src->payload.playerPartyCount;
    memcpy(sPokegotchiRuntimeState.playerParty,
           src->payload.playerParty,
           sizeof(sPokegotchiRuntimeState.playerParty));
    sPokegotchiRuntimeState.food = src->payload.food;
    sPokegotchiRuntimeState.stats = src->payload.stats;
    memcpy(sPokegotchiRuntimeState.playerTrainerId,
           src->payload.playerTrainerId,
           sizeof(sPokegotchiRuntimeState.playerTrainerId));
    memcpy(sPokegotchiRuntimeState.playerName,
           src->payload.playerName,
           sizeof(sPokegotchiRuntimeState.playerName));
    sPokegotchiRuntimeState.playerGender = src->payload.playerGender;
    sPokegotchiRuntimeState.optionsSound = src->payload.optionsSound;
}

static volatile u8 *GetSaveMemoryBase(void)
{
#if TESTING
    return sPokegotchiTestSram;
#else
    return (volatile u8 *)0x0E000000;
#endif
}

static void WritePersistedSaveBytes(volatile u8 *dst, const struct PokegotchiPersistedSave *src, u32 bytesToWrite, bool8 writeMagic)
{
    u32 zeroMagic = 0;
    u32 offset;
    u32 chunkSize;

    // Two-phase commit:
    // 1. Invalidate the slot immediately.
    // 2. Write the body fields in dependency order.
    // 3. Publish the magic last so an interrupted write cannot win newest-slot
    //    selection until the payload and checksum are already coherent.
    offset = offsetof(struct PokegotchiPersistedSave, payload);
    chunkSize = min(bytesToWrite, (u32)sizeof(src->payload));

    SramWriteBytes(dst, (const u8 *)&zeroMagic, sizeof(zeroMagic));

    if (chunkSize != 0)
        SramWriteBytes(dst + offset, (const u8 *)&src->payload, chunkSize);
    bytesToWrite -= chunkSize;

    offset = offsetof(struct PokegotchiPersistedSave, checksum);
    chunkSize = min(bytesToWrite, (u32)sizeof(src->checksum));
    if (chunkSize != 0)
        SramWriteBytes(dst + offset, (const u8 *)&src->checksum, chunkSize);
    bytesToWrite -= chunkSize;

    offset = offsetof(struct PokegotchiPersistedSave, payloadSize);
    chunkSize = min(bytesToWrite, (u32)sizeof(src->payloadSize));
    if (chunkSize != 0)
        SramWriteBytes(dst + offset, (const u8 *)&src->payloadSize, chunkSize);
    bytesToWrite -= chunkSize;

    offset = offsetof(struct PokegotchiPersistedSave, saveCounter);
    chunkSize = min(bytesToWrite, (u32)sizeof(src->saveCounter));
    if (chunkSize != 0)
        SramWriteBytes(dst + offset, (const u8 *)&src->saveCounter, chunkSize);
    bytesToWrite -= chunkSize;

    offset = offsetof(struct PokegotchiPersistedSave, version);
    chunkSize = min(bytesToWrite, (u32)sizeof(src->version));
    if (chunkSize != 0)
        SramWriteBytes(dst + offset, (const u8 *)&src->version, chunkSize);

    if (writeMagic)
        SramWriteBytes(dst + offsetof(struct PokegotchiPersistedSave, magic), (const u8 *)&src->magic, sizeof(src->magic));
}
