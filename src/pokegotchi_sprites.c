#include "global.h"
#include "pokegotchi_sprites.h"
#include "graphics.h"
#include "sprite.h"

#define POKEGOTCHI_SPRITE_TILE_TAG 6000
#define POKEGOTCHI_SPRITE_PAL_TAG  6001
#define POKEGOTCHI_SPRITE_SIZE     (64 * 32 / 2)

struct PokegotchiEmotionGraphics
{
    const u8 *spriteTiles;
    const u16 *palette;
};

struct PokegotchiSpeciesGraphics
{
    enum Species species;
    const struct PokegotchiEmotionGraphics *emotions;
};

static const struct PokegotchiSpeciesGraphics *GetPokegotchiSpeciesGraphics(enum Species species);
static const struct PokegotchiEmotionGraphics *GetPokegotchiEmotionGraphics(enum Species species, u8 emotion);

static bool8 sPokegotchiSpriteActive = FALSE;
static u8 sActivePokegotchiSpriteId;

static const union AnimCmd sAnim_Pokegotchi[] =
{
    ANIMCMD_FRAME(0, 24),
    ANIMCMD_FRAME(16, 24),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sPokegotchiSpriteAnims[] =
{
    sAnim_Pokegotchi,
};

static const struct OamData sPokegotchiSpriteOamData =
{
    .shape = SPRITE_SHAPE(32x32),
    .size = SPRITE_SIZE(32x32),
    .priority = 0,
    .bpp = ST_OAM_4BPP,
};

static const struct SpriteTemplate sPokegotchiSpriteTemplate =
{
    .tileTag = POKEGOTCHI_SPRITE_TILE_TAG,
    .paletteTag = POKEGOTCHI_SPRITE_PAL_TAG,
    .oam = &sPokegotchiSpriteOamData,
    .anims = sPokegotchiSpriteAnims,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

#include "data/pokegotchi_sprites.h"

static const struct PokegotchiSpeciesGraphics *GetPokegotchiSpeciesGraphics(enum Species species)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sPokegotchiSpeciesGfx); i++)
    {
        if (sPokegotchiSpeciesGfx[i].species == species)
            return &sPokegotchiSpeciesGfx[i];
    }

    return NULL;
}

static const struct PokegotchiEmotionGraphics *GetPokegotchiEmotionGraphics(enum Species species, u8 emotion)
{
    const struct PokegotchiSpeciesGraphics *speciesGfx;

    if (emotion >= POKEGOTCHI_EMOTION_COUNT)
        return NULL;

    speciesGfx = GetPokegotchiSpeciesGraphics(species);
    if (speciesGfx == NULL || speciesGfx->emotions == NULL)
        return NULL;

    if (speciesGfx->emotions[emotion].spriteTiles == NULL || speciesGfx->emotions[emotion].palette == NULL)
        return NULL;

    return &speciesGfx->emotions[emotion];
}

bool32 HasPokegotchiSprite(enum Species species, u8 emotion)
{
    return GetPokegotchiEmotionGraphics(species, emotion) != NULL;
}

u8 CreatePokegotchiSprite(enum Species species, u8 emotion, s16 x, s16 y, u8 subpriority)
{
    u8 spriteId;
    const struct PokegotchiEmotionGraphics *emotionGfx = GetPokegotchiEmotionGraphics(species, emotion);
    struct SpriteSheet spriteSheet;
    struct SpritePalette spritePalette;

    if (emotionGfx == NULL || sPokegotchiSpriteActive)
        return SPRITE_NONE;

    spriteSheet.data = emotionGfx->spriteTiles;
    spriteSheet.size = POKEGOTCHI_SPRITE_SIZE;
    spriteSheet.tag = POKEGOTCHI_SPRITE_TILE_TAG;

    spritePalette.data = emotionGfx->palette;
    spritePalette.tag = POKEGOTCHI_SPRITE_PAL_TAG;

    if (LoadSpriteSheet(&spriteSheet) == TAG_NONE)
        return SPRITE_NONE;

    if (LoadSpritePalette(&spritePalette) == 0xFF)
    {
        FreeSpriteTilesByTag(POKEGOTCHI_SPRITE_TILE_TAG);
        return SPRITE_NONE;
    }

    spriteId = CreateSprite(&sPokegotchiSpriteTemplate, x, y, subpriority);
    if (spriteId == MAX_SPRITES)
    {
        FreeSpriteTilesByTag(POKEGOTCHI_SPRITE_TILE_TAG);
        FreeSpritePaletteByTag(POKEGOTCHI_SPRITE_PAL_TAG);
        return SPRITE_NONE;
    }

    sPokegotchiSpriteActive = TRUE;
    sActivePokegotchiSpriteId = spriteId;
    return spriteId;
}

void DestroyPokegotchiSprite(u8 spriteId)
{
    if (spriteId != SPRITE_NONE && spriteId < MAX_SPRITES && gSprites[spriteId].inUse)
        DestroySpriteAndFreeResources(&gSprites[spriteId]);
    else
    {
        FreeSpriteTilesByTag(POKEGOTCHI_SPRITE_TILE_TAG);
        FreeSpritePaletteByTag(POKEGOTCHI_SPRITE_PAL_TAG);
    }

    if (spriteId == sActivePokegotchiSpriteId || spriteId == SPRITE_NONE)
    {
        sPokegotchiSpriteActive = FALSE;
        sActivePokegotchiSpriteId = SPRITE_NONE;
    }
}
