#ifndef GUARD_POKEGOTCHI_FEED_H
#define GUARD_POKEGOTCHI_FEED_H

#include "global.h"
#include "main.h"

enum PokegotchiFeedFoodCategory
{
    FEED_FOOD_CATEGORY_MEAL,
    FEED_FOOD_CATEGORY_SNACK,
    FEED_FOOD_CATEGORY_COUNT,
};

enum PokegotchiFeedFoodInventoryKey
{
    FEED_FOOD_KEY_NONE,
    FEED_FOOD_KEY_LEAF,
    FEED_FOOD_KEY_PECHA,
};

enum
{
    FEED_FOOD_SLOTS_PER_CATEGORY = 4,
    FEED_FOOD_SLOT_COUNT = FEED_FOOD_CATEGORY_COUNT * FEED_FOOD_SLOTS_PER_CATEGORY,
    FEED_FOOD_SPRITESHEET_SIZE = (48 * 16) / 2,
    FEED_FOOD_TILE_TAG_LEAF = 7100,
    FEED_FOOD_TILE_TAG_PECHA,
    FEED_FOOD_PAL_TAG_LEAF = 7200,
    FEED_FOOD_PAL_TAG_PECHA,
};

struct PokegotchiFeedFoodItem
{
    u8 category;
    u8 slot;
    u8 inventoryKey;
    u16 tileTag;
    u16 paletteTag;
    const u8 *spriteTiles;
    const u16 *palette;
};

extern const u8 gPokegotchiFeedFoodLeafSpriteGfx[];
extern const u16 gPokegotchiFeedFoodLeafPalette[];
extern const u8 gPokegotchiFeedFoodPechaSpriteGfx[];
extern const u16 gPokegotchiFeedFoodPechaPalette[];
extern const struct PokegotchiFeedFoodItem gPokegotchiFeedFoodItems[FEED_FOOD_SLOT_COUNT];

void OpenPokegotchiFeedMenu(MainCallback exitCallback);

#endif // GUARD_POKEGOTCHI_FEED_H
