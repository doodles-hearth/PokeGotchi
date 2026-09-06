#ifndef GUARD_POKEGOTCHI_H
#define GUARD_POKEGOTCHI_H

#include "constants/pokegotchi.h"
#include "global.h"
#include "pokegotchi_save.h"

#define POKEGOTCHI_STAT_MAX 250
#define POKEGOTCHI_STAT_DECAY_PER_MINUTE 2
#define POKEGOTCHI_POOP_THRESHOLD 200
#define POKEGOTCHI_OFFLINE_DECAY_PERCENT 50
#define POKEGOTCHI_SLEEP_START_HOUR 21
#define POKEGOTCHI_SLEEP_END_HOUR 5
#define POKEGOTCHI_MAX_POOPS 4

enum PokegotchiStat
{
    POKEGOTCHI_STAT_FOOD,
    POKEGOTCHI_STAT_FUN,
    POKEGOTCHI_STAT_HAPPY,
    POKEGOTCHI_STAT_POOP,
};

enum PokegotchiInteractionReaction
{
    POKEGOTCHI_REACTION_SULKING,
    POKEGOTCHI_REACTION_HAPPY_ONCE,
    POKEGOTCHI_REACTION_HAPPY_TWICE,
    POKEGOTCHI_REACTION_HAPPY_TWICE_SUN,
    POKEGOTCHI_REACTION_ANGRY_ONCE,
    POKEGOTCHI_REACTION_ANGRY_TWICE,
    POKEGOTCHI_REACTION_SAD_ONCE,
    POKEGOTCHI_REACTION_SAD_TWICE,
};

void Pokegotchi_BeginSession(void);
void Pokegotchi_UpdateDailyFlags(void);
void Pokegotchi_EnsureInitialized(void);
void Pokegotchi_Sync(void);
void Pokegotchi_SyncAndSave(void);
enum Species Pokegotchi_GetPrimarySpecies(void);
const struct PokegotchiStats *Pokegotchi_GetStats(void);
bool8 Pokegotchi_IsSleeping(void);
bool8 Pokegotchi_WakeForActivity(void);
enum PokegotchiInteractionReaction Pokegotchi_GetInteractionReaction(const struct PokegotchiStats *stats);
bool8 Pokegotchi_AddFoodByKey(u8 foodKey, u16 amount);
void Pokegotchi_AddToStat(enum PokegotchiStat stat, s16 delta);
void Pokegotchi_ClearPoops(void);

void Pokegotchi_SetCurrentTimeForTest(const struct Time *time);
void Pokegotchi_ResetStateForTest(void);
#if TESTING
void Pokegotchi_SetWokenDuringSleepForTest(bool8 woken);
u32 Pokegotchi_GetSleepMinutesBetweenForTest(const struct Time *start, const struct Time *end);
#endif

#endif // GUARD_POKEGOTCHI_H
