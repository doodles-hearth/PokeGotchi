#include "global.h"
#include "pokegotchi_save.h"
#include "agb_flash.h"
#include "gba/defines.h"
#include "gba/flash_internal.h"
#include "gba/isagbprint.h"
#include "load_save.h"
#include "random.h"
#include "save.h"
#include "test_runner.h"

#define POKEGOTCHI_SRAM_SIZE 0x8000
#define POKEGOTCHI_FLASH_SECTOR_SIZE SECTOR_SIZE

STATIC_ASSERT(sizeof(struct PokegotchiPersistedSave) * POKEGOTCHI_SAVE_SLOT_COUNT <= POKEGOTCHI_SRAM_SIZE,
              PokegotchiPersistedSaveFitsInSram);
STATIC_ASSERT(sizeof(struct PokegotchiPersistedSave) <= POKEGOTCHI_FLASH_SECTOR_SIZE,
              PokegotchiPersistedSaveFitsInFlashSector);

enum PokegotchiSaveBackend
{
    POKEGOTCHI_SAVE_BACKEND_SRAM,
    POKEGOTCHI_SAVE_BACKEND_FLASH,
};

static EWRAM_DATA struct PokegotchiRuntimeState sPokegotchiRuntimeState = {0};
static EWRAM_DATA u32 sPokegotchiSaveCounter = 0;
static EWRAM_DATA u8 sPokegotchiFlashSectorBuffer[POKEGOTCHI_FLASH_SECTOR_SIZE] = {0};

#if TESTING
static EWRAM_DATA u8 sPokegotchiTestSram[POKEGOTCHI_SRAM_SIZE] = {0};
static EWRAM_DATA struct PokegotchiPersistedSave sPokegotchiTestFlash[POKEGOTCHI_SAVE_SLOT_COUNT] = {0};
#endif

static enum PokegotchiSaveBackend GetSaveBackend(void);
static void LogSaveEvent(const char *action, enum PokegotchiSaveBackend backend, const char *detail, u32 value);
static bool8 IsSlotBlank(const struct PokegotchiPersistedSave *save);
static bool8 IsSaveValid(const struct PokegotchiPersistedSave *save);
static const struct PokegotchiPersistedSave *GetSramPersistedSaveSlot(u32 slot);
static struct PokegotchiPersistedSave *GetSramPersistedSaveSlotMutable(u32 slot);
static void SetSramWaitstates(void);
ARM_FUNC __attribute__((section(".iwram.code"))) NOINLINE static void SramReadBytes(u8 *dst, const volatile u8 *src, u32 size);
ARM_FUNC __attribute__((section(".iwram.code"))) NOINLINE static void SramWriteBytes(volatile u8 *dst, const u8 *src, u32 size);
static void ReadPersistedSave(struct PokegotchiPersistedSave *dst, u32 slot);
static bool8 WritePersistedSave(u32 slot, const struct PokegotchiPersistedSave *src);
#if TESTING
static bool8 WritePersistedSavePartial(u32 slot, const struct PokegotchiPersistedSave *src, u32 bytesToWrite);
#endif
static void SerializeRuntimeState(struct PokegotchiPersistedSave *dst, u32 saveCounter);
static void DeserializeRuntimeState(const struct PokegotchiPersistedSave *src);
static volatile u8 *GetSramMemoryBase(void);
static void WriteSramPersistedSaveBytes(volatile u8 *dst, const struct PokegotchiPersistedSave *src, u32 bytesToWrite, bool8 writeMagic);
static void ClearSramStorage(void);
static void ClearFlashStorage(void);
static bool8 WriteFlashSectorImage(u32 slot, const u8 *src);
static void ReadFlashSectorImage(u32 slot, u8 *dst);

const struct PokegotchiRuntimeState *PokegotchiSave_GetRuntime(void)
{
    return &sPokegotchiRuntimeState;
}

struct PokegotchiRuntimeState *PokegotchiSave_GetRuntimeMutable(void)
{
    return &sPokegotchiRuntimeState;
}

static enum PokegotchiSaveBackend GetSaveBackend(void)
{
    return gFlashMemoryPresent == TRUE ? POKEGOTCHI_SAVE_BACKEND_FLASH : POKEGOTCHI_SAVE_BACKEND_SRAM;
}

static void LogSaveEvent(const char *action, enum PokegotchiSaveBackend backend, const char *detail, u32 value)
{
    const char *backendName = backend == POKEGOTCHI_SAVE_BACKEND_FLASH ? "FLASH" : "SRAM";
    if (gTestRunnerEnabled)
        return;

    DebugPrintfLevel(MGBA_LOG_WARN, "PokegotchiSave: %s backend=%s %s=%lu", action, backendName, detail, value);
}

bool8 PokegotchiSave_InitOrLoad(void)
{
    struct PokegotchiPersistedSave slots[POKEGOTCHI_SAVE_SLOT_COUNT];
    s32 bestSlot = -1;
    bool8 anyBlank = FALSE;
    bool8 anyCorrupt = FALSE;
    enum PokegotchiSaveBackend backend = GetSaveBackend();
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
        LogSaveEvent("load_ok", backend, "counter", sPokegotchiSaveCounter);
        return TRUE;
    }

    PokegotchiSave_ResetToDefaults();
    sPokegotchiSaveCounter = 0;
    gSaveFileStatus = anyCorrupt && !anyBlank ? SAVE_STATUS_CORRUPT : SAVE_STATUS_EMPTY;
    LogSaveEvent(gSaveFileStatus == SAVE_STATUS_CORRUPT ? "load_reset_corrupt" : "load_reset_empty", backend, "counter", 0);
    return FALSE;
}

u8 PokegotchiSave_Commit(void)
{
    struct PokegotchiPersistedSave save;
    enum PokegotchiSaveBackend backend = GetSaveBackend();
    u32 nextCounter;
    u32 slot;

    nextCounter = sPokegotchiSaveCounter + 1;
    slot = nextCounter % POKEGOTCHI_SAVE_SLOT_COUNT;
    SerializeRuntimeState(&save, nextCounter);
    if (!WritePersistedSave(slot, &save))
    {
        gSaveFileStatus = SAVE_STATUS_ERROR;
        LogSaveEvent("commit_error", backend, "slot", slot);
        return SAVE_STATUS_ERROR;
    }

    sPokegotchiSaveCounter = nextCounter;
    gSaveFileStatus = SAVE_STATUS_OK;
    LogSaveEvent("commit_ok", backend, "counter", sPokegotchiSaveCounter);
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
    if (GetSaveBackend() == POKEGOTCHI_SAVE_BACKEND_FLASH)
        ClearFlashStorage();
    else
        ClearSramStorage();
}

#if TESTING
void PokegotchiSave_ClearForTest(void)
{
    PokegotchiSave_ClearRuntimeState();
    ClearSramStorage();
    ClearFlashStorage();
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

void PokegotchiSave_SetSlotVersionForTest(u32 slot, u16 version)
{
    struct PokegotchiPersistedSave save;

    if (slot >= POKEGOTCHI_SAVE_SLOT_COUNT)
        return;

    ReadPersistedSave(&save, slot);
    save.version = version;
    WritePersistedSave(slot, &save);
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

static const struct PokegotchiPersistedSave *GetSramPersistedSaveSlot(u32 slot)
{
    return (const struct PokegotchiPersistedSave *)(GetSramMemoryBase() + sizeof(struct PokegotchiPersistedSave) * slot);
}

static struct PokegotchiPersistedSave *GetSramPersistedSaveSlotMutable(u32 slot)
{
    return (struct PokegotchiPersistedSave *)(GetSramMemoryBase() + sizeof(struct PokegotchiPersistedSave) * slot);
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
    if (GetSaveBackend() == POKEGOTCHI_SAVE_BACKEND_FLASH)
    {
        ReadFlashSectorImage(slot, sPokegotchiFlashSectorBuffer);
        memcpy(dst, sPokegotchiFlashSectorBuffer, sizeof(*dst));
    }
    else
    {
        SetSramWaitstates();
        SramReadBytes((u8 *)dst, (const volatile u8 *)GetSramPersistedSaveSlot(slot), sizeof(*dst));
    }
}

static bool8 WritePersistedSave(u32 slot, const struct PokegotchiPersistedSave *src)
{
    if (GetSaveBackend() == POKEGOTCHI_SAVE_BACKEND_FLASH)
    {
        memset(sPokegotchiFlashSectorBuffer, 0xFF, sizeof(sPokegotchiFlashSectorBuffer));
        memcpy(sPokegotchiFlashSectorBuffer, src, sizeof(*src));
        return WriteFlashSectorImage(slot, sPokegotchiFlashSectorBuffer);
    }
    else
    {
        volatile u8 *dst = (volatile u8 *)GetSramPersistedSaveSlotMutable(slot);

        SetSramWaitstates();
        WriteSramPersistedSaveBytes(dst, src, sizeof(*src) - sizeof(src->magic), TRUE);
        return TRUE;
    }
}

#if TESTING
static bool8 WritePersistedSavePartial(u32 slot, const struct PokegotchiPersistedSave *src, u32 bytesToWrite)
{
    if (GetSaveBackend() == POKEGOTCHI_SAVE_BACKEND_FLASH)
    {
        memset(sPokegotchiFlashSectorBuffer, 0xFF, sizeof(sPokegotchiFlashSectorBuffer));
        memcpy(sPokegotchiFlashSectorBuffer, src, min(bytesToWrite, (u32)sizeof(*src)));
        return WriteFlashSectorImage(slot, sPokegotchiFlashSectorBuffer);
    }
    else
    {
        volatile u8 *dst = (volatile u8 *)GetSramPersistedSaveSlotMutable(slot);

        // Tests use this to emulate a power cut partway through a staged SRAM write.
        // The final magic word is intentionally omitted so the interrupted slot never
        // looks valid just because some earlier fields landed in SRAM first.
        SetSramWaitstates();
        WriteSramPersistedSaveBytes(dst, src, bytesToWrite, FALSE);
        return TRUE;
    }
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
    memcpy(dst->payload.flags,
           sPokegotchiRuntimeState.flags,
           sizeof(dst->payload.flags));
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
    memcpy(sPokegotchiRuntimeState.flags,
           src->payload.flags,
           sizeof(sPokegotchiRuntimeState.flags));
}

static volatile u8 *GetSramMemoryBase(void)
{
#if TESTING
    return sPokegotchiTestSram;
#else
    return (volatile u8 *)0x0E000000;
#endif
}

static void WriteSramPersistedSaveBytes(volatile u8 *dst, const struct PokegotchiPersistedSave *src, u32 bytesToWrite, bool8 writeMagic)
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

static void ClearSramStorage(void)
{
    u32 i;
    volatile u8 *saveMemory = GetSramMemoryBase();

    SetSramWaitstates();
    for (i = 0; i < POKEGOTCHI_SRAM_SIZE; i++)
        saveMemory[i] = 0xFF;
}

static void ClearFlashStorage(void)
{
    u32 slot;

    memset(sPokegotchiFlashSectorBuffer, 0xFF, sizeof(sPokegotchiFlashSectorBuffer));
    for (slot = 0; slot < POKEGOTCHI_SAVE_SLOT_COUNT; slot++)
        WriteFlashSectorImage(slot, sPokegotchiFlashSectorBuffer);
}

static bool8 WriteFlashSectorImage(u32 slot, const u8 *src)
{
#if TESTING
    memcpy(&sPokegotchiTestFlash[slot], src, sizeof(sPokegotchiTestFlash[slot]));
    return TRUE;
#else
    return ProgramFlashSectorAndVerify(slot, (u8 *)src) == 0;
#endif
}

static void ReadFlashSectorImage(u32 slot, u8 *dst)
{
#if TESTING
    memset(dst, 0xFF, POKEGOTCHI_FLASH_SECTOR_SIZE);
    memcpy(dst, &sPokegotchiTestFlash[slot], sizeof(sPokegotchiTestFlash[slot]));
#else
    ReadFlash(slot, 0, dst, POKEGOTCHI_FLASH_SECTOR_SIZE);
#endif
}
