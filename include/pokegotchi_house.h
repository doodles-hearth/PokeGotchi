#ifndef POKEGOTCHI_HOUSE_H
#define POKEGOTCHI_HOUSE_H

#include "main.h"

void OpenPokegotchiHouseMenu(MainCallback exitCallback);
void OpenPokegotchiHouseEatingScene(u8 foodKey, MainCallback returnCallback);
void MainCB2_InitPokegotchiHouseMenu(void);

#endif // POKEGOTCHI_HOUSE_H
