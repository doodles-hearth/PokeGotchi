#include "global.h"
#include "main.h"
#include "overworld.h"
#include "palette.h"
#include "pokegotchi_overworld.h"
#include "script.h"
#include "sprite.h"

#define START_HINT_TILE_TAG 6010
#define START_HINT_PAL_TAG  (6011 | BLEND_IMMUNE_FLAG)
#define START_HINT_X        16
#define START_HINT_Y        144
#define START_HINT_GFX_SIZE (32 * 32 / 2)

static void SpriteCB_StartHint(struct Sprite *sprite);

static const u8 sStartHintGfx[] = INCGFX_U8("graphics/pokegotchi_overworld/start.png", ".4bpp");
static const u16 sStartHintPalette[] = INCGFX_U16("graphics/pokegotchi_overworld/start.png", ".gbapal");

static const struct SpriteSheet sStartHintSpriteSheet =
{
    .data = sStartHintGfx,
    .size = sizeof(sStartHintGfx),
    .tag = START_HINT_TILE_TAG,
};

static const struct SpritePalette sStartHintSpritePalette =
{
    .data = sStartHintPalette,
    .tag = START_HINT_PAL_TAG,
};

static const struct OamData sStartHintOam =
{
    .shape = SPRITE_SHAPE(32x32),
    .size = SPRITE_SIZE(32x32),
    .priority = 0,
};

static const struct SpriteTemplate sStartHintSpriteTemplate =
{
    .tileTag = START_HINT_TILE_TAG,
    .paletteTag = START_HINT_PAL_TAG,
    .oam = &sStartHintOam,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_StartHint,
};

void PokegotchiOverworld_SetUpControlHint(void)
{
    u8 spriteId;

    // SetUpFieldTasks can be called more than once without resetting sprite data.
    if (GetSpriteTileStartByTag(START_HINT_TILE_TAG) != TAG_NONE
     && IndexOfSpritePaletteTag(START_HINT_PAL_TAG) != 0xFF)
        return;

    // Recover cleanly if an earlier setup was interrupted after one allocation.
    FreeSpriteTilesByTag(START_HINT_TILE_TAG);
    FreeSpritePaletteByTag(START_HINT_PAL_TAG);

    LoadSpriteSheet(&sStartHintSpriteSheet);
    if (GetSpriteTileStartByTag(START_HINT_TILE_TAG) == TAG_NONE)
        return;

    if (LoadSpritePalette(&sStartHintSpritePalette) == 0xFF)
    {
        FreeSpriteTilesByTag(START_HINT_TILE_TAG);
        return;
    }

    spriteId = CreateSpriteUnchecked(&sStartHintSpriteTemplate, START_HINT_X, START_HINT_Y, 0);
    if (spriteId == MAX_SPRITES)
    {
        FreeSpriteTilesByTag(START_HINT_TILE_TAG);
        FreeSpritePaletteByTag(START_HINT_PAL_TAG);
        return;
    }

    gSprites[spriteId].coordOffsetEnabled = FALSE;
    SpriteCB_StartHint(&gSprites[spriteId]);
}

static void SpriteCB_StartHint(struct Sprite *sprite)
{
    sprite->invisible = gPaletteFade.active
                     || ArePlayerFieldControlsLocked()
                     || gMain.callback1 != CB1_Overworld;
}
