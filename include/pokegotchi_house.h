#ifndef POKEGOTCHI_HOUSE_H
#define POKEGOTCHI_HOUSE_H

#include "main.h"

struct ScriptContext;

void OpenPokegotchiHouseMenu(MainCallback exitCallback);
void OpenPokegotchiHouseEatingScene(u8 foodKey, MainCallback returnCallback);
void MainCB2_InitPokegotchiHouseMenu(void);
void ReturnToPokegotchiHouse(struct ScriptContext *ctx);

#endif // POKEGOTCHI_HOUSE_H
