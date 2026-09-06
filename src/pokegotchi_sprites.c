#include "global.h"
#include "pokegotchi_sprites.h"
#include "graphics.h"
#include "sprite.h"

#define POKEGOTCHI_SPRITE_TILE_TAG 6000
#define POKEGOTCHI_SPRITE_PAL_TAG  6001
#define POKEGOTCHI_EMOTICON_TILE_TAG 6002
#define POKEGOTCHI_EMOTICON_PAL_TAG  6003
#define POKEGOTCHI_SPRITE_SIZE     (64 * 32 / 2)
#define POKEGOTCHI_EMOTICON_SIZE   (16 * 32 / 2)
#define POKEGOTCHI_IDLE_FRAME_DURATION 24
#define POKEGOTCHI_EMOTION_FRAME_DURATION 32
#define POKEGOTCHI_WAKE_EMOTICON_FRAME_DURATION 12

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
static bool8 sPokegotchiEmoticonActive = FALSE;
static u8 sActivePokegotchiEmoticonId;

static const union AnimCmd sAnim_PokegotchiIdle[] =
{
    ANIMCMD_FRAME(0, POKEGOTCHI_IDLE_FRAME_DURATION),
    ANIMCMD_FRAME(16, POKEGOTCHI_IDLE_FRAME_DURATION),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sPokegotchiIdleSpriteAnims[] =
{
    sAnim_PokegotchiIdle,
};

static const union AnimCmd sAnim_PokegotchiEmotion[] =
{
    ANIMCMD_FRAME(0, POKEGOTCHI_EMOTION_FRAME_DURATION),
    ANIMCMD_FRAME(16, POKEGOTCHI_EMOTION_FRAME_DURATION),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sPokegotchiEmotionSpriteAnims[] =
{
    sAnim_PokegotchiEmotion,
};

static const struct OamData sPokegotchiSpriteOamData =
{
    .shape = SPRITE_SHAPE(32x32),
    .size = SPRITE_SIZE(32x32),
    .priority = 0,
    .bpp = ST_OAM_4BPP,
};

static const struct SpriteTemplate sPokegotchiIdleSpriteTemplate =
{
    .tileTag = POKEGOTCHI_SPRITE_TILE_TAG,
    .paletteTag = POKEGOTCHI_SPRITE_PAL_TAG,
    .oam = &sPokegotchiSpriteOamData,
    .anims = sPokegotchiIdleSpriteAnims,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sPokegotchiEmotionSpriteTemplate =
{
    .tileTag = POKEGOTCHI_SPRITE_TILE_TAG,
    .paletteTag = POKEGOTCHI_SPRITE_PAL_TAG,
    .oam = &sPokegotchiSpriteOamData,
    .anims = sPokegotchiEmotionSpriteAnims,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const u8 sSunEmoticonSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_mons/emotions/sun.png", ".4bpp", "-mwidth 2 -mheight 2");
static const u16 sSunEmoticonSpritePalette[] = INCGFX_U16("graphics/pokegotchi_mons/emotions/sun.png", ".gbapal");
static const u8 sAngerEmoticonSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_mons/emotions/anger.png", ".4bpp", "-mwidth 2 -mheight 2");
static const u16 sAngerEmoticonSpritePalette[] = INCGFX_U16("graphics/pokegotchi_mons/emotions/anger.png", ".gbapal");

static const union AnimCmd sAnim_PokegotchiEmoticon[] =
{
    ANIMCMD_FRAME(0, POKEGOTCHI_EMOTION_FRAME_DURATION),
    ANIMCMD_FRAME(4, POKEGOTCHI_EMOTION_FRAME_DURATION),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sPokegotchiEmoticonAnims[] =
{
    sAnim_PokegotchiEmoticon,
};

static const union AnimCmd sAnim_PokegotchiWakeEmoticon[] =
{
    ANIMCMD_FRAME(0, POKEGOTCHI_WAKE_EMOTICON_FRAME_DURATION),
    ANIMCMD_FRAME(4, POKEGOTCHI_WAKE_EMOTICON_FRAME_DURATION),
    ANIMCMD_END,
};

static const union AnimCmd *const sPokegotchiWakeEmoticonAnims[] =
{
    sAnim_PokegotchiWakeEmoticon,
};

static const struct OamData sPokegotchiEmoticonOamData =
{
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 0,
    .bpp = ST_OAM_4BPP,
};

static const struct SpriteTemplate sPokegotchiEmoticonTemplate =
{
    .tileTag = POKEGOTCHI_EMOTICON_TILE_TAG,
    .paletteTag = POKEGOTCHI_EMOTICON_PAL_TAG,
    .oam = &sPokegotchiEmoticonOamData,
    .anims = sPokegotchiEmoticonAnims,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sPokegotchiWakeEmoticonTemplate =
{
    .tileTag = POKEGOTCHI_EMOTICON_TILE_TAG,
    .paletteTag = POKEGOTCHI_EMOTICON_PAL_TAG,
    .oam = &sPokegotchiEmoticonOamData,
    .anims = sPokegotchiWakeEmoticonAnims,
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
    const struct SpriteTemplate *spriteTemplate;

    if (emotionGfx == NULL || sPokegotchiSpriteActive)
        return SPRITE_NONE;

    spriteSheet.data = emotionGfx->spriteTiles;
    spriteSheet.size = POKEGOTCHI_SPRITE_SIZE;
    spriteSheet.tag = POKEGOTCHI_SPRITE_TILE_TAG;

    spritePalette.data = emotionGfx->palette;
    spritePalette.tag = POKEGOTCHI_SPRITE_PAL_TAG;

    if (emotion == POKEGOTCHI_EMOTION_IDLE)
        spriteTemplate = &sPokegotchiIdleSpriteTemplate;
    else
        spriteTemplate = &sPokegotchiEmotionSpriteTemplate;

    if (LoadSpriteSheet(&spriteSheet) == TAG_NONE)
        return SPRITE_NONE;

    if (LoadSpritePalette(&spritePalette) == 0xFF)
    {
        FreeSpriteTilesByTag(POKEGOTCHI_SPRITE_TILE_TAG);
        return SPRITE_NONE;
    }

    spriteId = CreateSprite(spriteTemplate, x, y, subpriority);
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

u8 CreatePokegotchiEmoticon(u8 emoticon, s16 x, s16 y, u8 subpriority, bool8 wakeAnimation)
{
    const u8 *tiles;
    const u16 *palette;
    const struct SpriteTemplate *spriteTemplate;
    struct SpriteSheet spriteSheet;
    struct SpritePalette spritePalette;
    u8 spriteId;

    if (emoticon == POKEGOTCHI_EMOTICON_SUN)
    {
        tiles = sSunEmoticonSpriteGfx;
        palette = sSunEmoticonSpritePalette;
    }
    else if (emoticon == POKEGOTCHI_EMOTICON_ANGER)
    {
        tiles = sAngerEmoticonSpriteGfx;
        palette = sAngerEmoticonSpritePalette;
    }
    else
    {
        return SPRITE_NONE;
    }

    if (sPokegotchiEmoticonActive)
        return SPRITE_NONE;

    spriteSheet = (struct SpriteSheet){tiles, POKEGOTCHI_EMOTICON_SIZE, POKEGOTCHI_EMOTICON_TILE_TAG};
    spritePalette = (struct SpritePalette){palette, POKEGOTCHI_EMOTICON_PAL_TAG};
    if (LoadSpriteSheet(&spriteSheet) == TAG_NONE)
        return SPRITE_NONE;
    if (LoadSpritePalette(&spritePalette) == 0xFF)
    {
        FreeSpriteTilesByTag(POKEGOTCHI_EMOTICON_TILE_TAG);
        return SPRITE_NONE;
    }

    spriteTemplate = wakeAnimation ? &sPokegotchiWakeEmoticonTemplate : &sPokegotchiEmoticonTemplate;
    spriteId = CreateSprite(spriteTemplate, x, y, subpriority);
    if (spriteId == MAX_SPRITES)
    {
        FreeSpriteTilesByTag(POKEGOTCHI_EMOTICON_TILE_TAG);
        FreeSpritePaletteByTag(POKEGOTCHI_EMOTICON_PAL_TAG);
        return SPRITE_NONE;
    }

    sPokegotchiEmoticonActive = TRUE;
    sActivePokegotchiEmoticonId = spriteId;
    return spriteId;
}

void DestroyPokegotchiEmoticon(u8 spriteId)
{
    if (spriteId != SPRITE_NONE && spriteId < MAX_SPRITES && gSprites[spriteId].inUse)
        DestroySpriteAndFreeResources(&gSprites[spriteId]);
    else
    {
        FreeSpriteTilesByTag(POKEGOTCHI_EMOTICON_TILE_TAG);
        FreeSpritePaletteByTag(POKEGOTCHI_EMOTICON_PAL_TAG);
    }

    if (spriteId == sActivePokegotchiEmoticonId || spriteId == SPRITE_NONE)
    {
        sPokegotchiEmoticonActive = FALSE;
        sActivePokegotchiEmoticonId = SPRITE_NONE;
    }
}
