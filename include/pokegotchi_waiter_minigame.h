#ifndef GUARD_POKEGOTCHI_WAITER_MINIGAME_H
#define GUARD_POKEGOTCHI_WAITER_MINIGAME_H

#include "main.h"

enum PokegotchiWaiterMinigameDifficulty
{
    POKEGOTCHI_WAITER_MINIGAME_EASY,
    POKEGOTCHI_WAITER_MINIGAME_HARD,
};

void PlayPokegotchiWaiterMinigameEasy(void);
void PlayPokegotchiWaiterMinigameHard(void);
void OpenPokegotchiWaiterMinigame(MainCallback exitCallback, enum PokegotchiWaiterMinigameDifficulty difficulty);
void MainCB2_InitPokegotchiWaiterMinigame(void);

#endif // GUARD_POKEGOTCHI_WAITER_MINIGAME_H
