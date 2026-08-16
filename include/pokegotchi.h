#ifndef GUARD_POKEGOTCHI_H
#define GUARD_POKEGOTCHI_H

#include "global.h"
#include "pokegotchi_save.h"

#define POKEGOTCHI_STAT_MAX 250
#define POKEGOTCHI_STAT_DECAY_PER_MINUTE 2
#define POKEGOTCHI_POOP_THRESHOLD 200
#define POKEGOTCHI_OFFLINE_DECAY_PERCENT 50

enum PokegotchiStat
{
    POKEGOTCHI_STAT_FOOD,
    POKEGOTCHI_STAT_FUN,
    POKEGOTCHI_STAT_HAPPY,
    POKEGOTCHI_STAT_POOP,
};

void Pokegotchi_BeginSession(void);
void Pokegotchi_EnsureInitialized(void);
void Pokegotchi_Sync(void);
void Pokegotchi_SyncAndSave(void);
const struct PokegotchiStats *Pokegotchi_GetStats(void);
void Pokegotchi_AddToStat(enum PokegotchiStat stat, s16 delta);
void Pokegotchi_ClearPoops(void);

void Pokegotchi_SetCurrentTimeForTest(const struct Time *time);
void Pokegotchi_ResetStateForTest(void);

#endif // GUARD_POKEGOTCHI_H
