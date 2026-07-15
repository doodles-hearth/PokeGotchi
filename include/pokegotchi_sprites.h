#ifndef GUARD_POKEGOTCHI_SPRITES_H
#define GUARD_POKEGOTCHI_SPRITES_H

#include "global.h"
#include "constants/species.h"

enum PokegotchiEmotion
{
    POKEGOTCHI_EMOTION_IDLE,
    POKEGOTCHI_EMOTION_HAPPY,
    POKEGOTCHI_EMOTION_SAD,
    POKEGOTCHI_EMOTION_ANGRY,
    POKEGOTCHI_EMOTION_EATING,
    POKEGOTCHI_EMOTION_SLEEPING,
    POKEGOTCHI_EMOTION_COUNT,
};

bool32 HasPokegotchiSprite(enum Species species, u8 emotion);
u8 CreatePokegotchiSprite(enum Species species, u8 emotion, s16 x, s16 y, u8 subpriority);
void DestroyPokegotchiSprite(u8 spriteId);

#endif // GUARD_POKEGOTCHI_SPRITES_H
