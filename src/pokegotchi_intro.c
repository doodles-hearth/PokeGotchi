#include "global.h"
#include "bg.h"
#include "pokegotchi_intro.h"
#include "main.h"
#include "palette.h"
#include "scanline_effect.h"
#include "task.h"
#include "title_screen.h"
#include "libgcnmultiboot.h"
#include "malloc.h"
#include "gpu_regs.h"
#include "field_weather.h"
#include "link.h"
#include "multiboot_pokemon_colosseum.h"
#include "load_save.h"
#include "save.h"
#include "new_game.h"
#include "m4a.h"
#include "random.h"
#include "decompress.h"
#include "constants/songs.h"
#include "intro_credits_graphics.h"
#include "trig.h"
#include "intro.h"
#include "graphics.h"
#include "sound.h"
#include "sprite.h"
#include "util.h"
#include "title_screen.h"
#include "constants/field_weather.h"
#include "constants/rgb.h"
#include "pokemon.h"
#include "pokegotchi.h"
#include "pokegotchi_house.h"

static void MainCB2_PokeGotchiIntro(void);
static void VBlankCB_PokeGotchiIntro(void);
static void Task_LoadIntro(u8 taskId);
static void Task_FadeInIntro(u8 taskId);
static void Task_SlideLogos(u8 taskId);
static void Task_Wait(u8 taskId);
static void Task_FadeOutIntro(u8 taskId);
static void PokegotchiIntro_InitGraphics(void);
static void PokegotchiIntro_LoadGraphics(void);
static void PokegotchiIntro_LoadLogoTiles(const struct CompressedSpriteSheet *sheet);
static void PokegotchiIntro_CreateLogos(void);
static void PokegotchiIntro_SetLogoPositions(s16 pokeX, s16 gotchiX);
static void PokegotchiIntro_StartFadeOut(u8 taskId);

enum
{
    POKEGOTCHI_INTRO_BG = 2,
};

enum
{
    TAG_POKEGOTCHI_INTRO_POKE = 30000,
    TAG_POKEGOTCHI_INTRO_GOTCHI,
    TAG_POKEGOTCHI_INTRO_PALETTE,
};

enum
{
    LOGO_POKE_LEFT,
    LOGO_POKE_RIGHT,
    LOGO_GOTCHI_LEFT,
    LOGO_GOTCHI_RIGHT,
    LOGO_COUNT,
};

#define LOGO_HALF_WIDTH 64
#define LOGO_Y 32
#define POKE_START_X -128
#define POKE_TARGET_X -10
#define GOTCHI_START_X 240
#define GOTCHI_TARGET_X 110
#define LOGO_SLIDE_SPEED 4

static const u32 sBgTiles[] = INCGFX_U32("graphics/pokegotchi_title_screen/bg_title_tiles.png", ".4bpp.smol");
static const u32 sBgTilemap[] = INCGFX_U32("graphics/pokegotchi_title_screen/bg_title_tiles.bin", ".smolTM");
static const u16 sBgPalette[] = INCGFX_U16("graphics/pokegotchi_title_screen/bg_title_tiles.png", ".gbapal");
static const u32 sPokeLogoTiles[] = INCGFX_U32("graphics/pokegotchi_title_screen/logo_poke.png", ".4bpp.smol");
static const u32 sGotchiLogoTiles[] = INCGFX_U32("graphics/pokegotchi_title_screen/logo_gotchi.png", ".4bpp.smol");
static const u16 sLogoPalette[] = INCGFX_U16("graphics/pokegotchi_title_screen/logo_poke.png", ".gbapal");

static const struct BgTemplate sBgTemplate =
{
    .bg = POKEGOTCHI_INTRO_BG,
    .charBaseIndex = 0,
    .mapBaseIndex = 30,
    .screenSize = 0,
    .paletteMode = 0,
    .priority = 2,
};

static const struct OamData sOamData_PokeLogo =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .size = SPRITE_SIZE(64x64),
    .priority = 1,
};

static const struct OamData sOamData_GotchiLogo =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .size = SPRITE_SIZE(64x64),
    .priority = 0,
};

static const union AnimCmd sAnimCmd_LogoLeft[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END,
};

static const union AnimCmd sAnimCmd_LogoRight[] =
{
    ANIMCMD_FRAME(64, 0),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_LogoLeft[] =
{
    sAnimCmd_LogoLeft,
};

static const union AnimCmd *const sAnimTable_LogoRight[] =
{
    sAnimCmd_LogoRight,
};

static const struct CompressedSpriteSheet sSpriteSheet_PokeLogo =
{
    .data = sPokeLogoTiles,
    .size = 128 * 64 / 2,
    .tag = TAG_POKEGOTCHI_INTRO_POKE,
};

static const struct CompressedSpriteSheet sSpriteSheet_GotchiLogo =
{
    .data = sGotchiLogoTiles,
    .size = 128 * 64 / 2,
    .tag = TAG_POKEGOTCHI_INTRO_GOTCHI,
};

static const struct SpritePalette sSpritePalette_Logo =
{
    .data = sLogoPalette,
    .tag = TAG_POKEGOTCHI_INTRO_PALETTE,
};

static const struct SpriteTemplate sSpriteTemplate_PokeLogoLeft =
{
    .tileTag = TAG_POKEGOTCHI_INTRO_POKE,
    .paletteTag = TAG_POKEGOTCHI_INTRO_PALETTE,
    .oam = &sOamData_PokeLogo,
    .anims = sAnimTable_LogoLeft,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_PokeLogoRight =
{
    .tileTag = TAG_POKEGOTCHI_INTRO_POKE,
    .paletteTag = TAG_POKEGOTCHI_INTRO_PALETTE,
    .oam = &sOamData_PokeLogo,
    .anims = sAnimTable_LogoRight,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_GotchiLogoLeft =
{
    .tileTag = TAG_POKEGOTCHI_INTRO_GOTCHI,
    .paletteTag = TAG_POKEGOTCHI_INTRO_PALETTE,
    .oam = &sOamData_GotchiLogo,
    .anims = sAnimTable_LogoLeft,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_GotchiLogoRight =
{
    .tileTag = TAG_POKEGOTCHI_INTRO_GOTCHI,
    .paletteTag = TAG_POKEGOTCHI_INTRO_PALETTE,
    .oam = &sOamData_GotchiLogo,
    .anims = sAnimTable_LogoRight,
    .callback = SpriteCallbackDummy,
};

static u8 sLogoSpriteIds[LOGO_COUNT];

void CB2_InitPokegotchiBootup(void)
{
    CreateTask(Task_LoadIntro, 0);
    SetVBlankCallback(VBlankCB_PokeGotchiIntro);
    SetMainCallback2(MainCB2_PokeGotchiIntro);
    SetSaveBlocksPointers(0);
    ResetMenuAndMonGlobals();
    Save_ResetSaveCounters();
    PokegotchiSave_InitOrLoad();
    Pokegotchi_EnsureInitialized();
    SetPokemonCryStereo(PokegotchiSave_GetRuntime()->optionsSound);
    InitHeap(gHeap, HEAP_SIZE);
    Pokegotchi_BeginSession();
}

static void MainCB2_PokeGotchiIntro(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB_PokeGotchiIntro(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void Task_LoadIntro(u8 taskId)
{
    PokegotchiIntro_InitGraphics();
    PokegotchiIntro_LoadGraphics();
    PokegotchiIntro_CreateLogos();
    BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
    ResetSerial();
    gTasks[taskId].func = Task_FadeInIntro;
}

static void Task_FadeInIntro(u8 taskId)
{
    if (gMain.newKeys != 0)
        PokegotchiIntro_StartFadeOut(taskId);
    else if (!gPaletteFade.active)
        gTasks[taskId].func = Task_SlideLogos;
}

static void Task_SlideLogos(u8 taskId)
{
    s16 pokeX = gSprites[sLogoSpriteIds[LOGO_POKE_LEFT]].x - LOGO_HALF_WIDTH / 2;
    s16 gotchiX = gSprites[sLogoSpriteIds[LOGO_GOTCHI_LEFT]].x - LOGO_HALF_WIDTH / 2;

    if (gMain.newKeys != 0)
    {
        PokegotchiIntro_StartFadeOut(taskId);
        return;
    }

    if (pokeX < POKE_TARGET_X)
    {
        pokeX += LOGO_SLIDE_SPEED;
        if (pokeX > POKE_TARGET_X)
            pokeX = POKE_TARGET_X;
    }
    if (gotchiX > GOTCHI_TARGET_X)
    {
        gotchiX -= LOGO_SLIDE_SPEED;
        if (gotchiX < GOTCHI_TARGET_X)
            gotchiX = GOTCHI_TARGET_X;
    }
    PokegotchiIntro_SetLogoPositions(pokeX, gotchiX);

    if (pokeX == POKE_TARGET_X && gotchiX == GOTCHI_TARGET_X)
        gTasks[taskId].func = Task_Wait;
}

static void Task_Wait(u8 taskId)
{
    if (gMain.newKeys != 0)
        PokegotchiIntro_StartFadeOut(taskId);
}

static void Task_FadeOutIntro(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        ResetSpriteData();
        FreeAllSpritePalettes();
        ResetBgsAndClearDma3BusyFlags(0);
        DestroyTask(taskId);
        SetMainCallback2(MainCB2_InitPokegotchiHouseMenu);
    }
}

static void PokegotchiIntro_InitGraphics(void)
{
    ResetSpriteData();
    FreeAllSpritePalettes();
    ResetPaletteFade();
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, &sBgTemplate, 1);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG2_ON | DISPCNT_OBJ_ON);
}

static void PokegotchiIntro_LoadGraphics(void)
{
    DecompressDataWithHeaderVram(sBgTiles, (void *)BG_CHAR_ADDR(sBgTemplate.charBaseIndex));
    DecompressDataWithHeaderVram(sBgTilemap, (void *)BG_SCREEN_ADDR(sBgTemplate.mapBaseIndex));
    LoadPalette(sBgPalette, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
    PokegotchiIntro_LoadLogoTiles(&sSpriteSheet_PokeLogo);
    PokegotchiIntro_LoadLogoTiles(&sSpriteSheet_GotchiLogo);
    LoadSpritePalette(&sSpritePalette_Logo);
    ShowBg(POKEGOTCHI_INTRO_BG);
}

static void PokegotchiIntro_LoadLogoTiles(const struct CompressedSpriteSheet *sheet)
{
    struct SpriteSheet decompressedSheet;
    u8 *buffer = Alloc(sheet->size);
    u8 *objTiles;
    u8 row;

    if (buffer == NULL)
        return;

    DecompressDataWithHeaderWram(sheet->data, buffer);
    decompressedSheet.data = buffer;
    decompressedSheet.size = sheet->size;
    decompressedSheet.tag = sheet->tag;
    objTiles = (u8 *)OBJ_VRAM0 + LoadSpriteSheet(&decompressedSheet) * TILE_SIZE_4BPP;

    // The source is 16 tiles wide; 1D OBJ mapping needs each 8-tile half stored contiguously.
    for (row = 0; row < 8; row++)
    {
        CpuCopy32(buffer + row * 16 * TILE_SIZE_4BPP,
                  objTiles + row * 8 * TILE_SIZE_4BPP,
                  8 * TILE_SIZE_4BPP);
        CpuCopy32(buffer + (row * 16 + 8) * TILE_SIZE_4BPP,
                  objTiles + (64 + row * 8) * TILE_SIZE_4BPP,
                  8 * TILE_SIZE_4BPP);
    }
    Free(buffer);
}

static void PokegotchiIntro_CreateLogos(void)
{
    sLogoSpriteIds[LOGO_POKE_LEFT] = CreateSprite(&sSpriteTemplate_PokeLogoLeft, 0, LOGO_Y, 0);
    sLogoSpriteIds[LOGO_POKE_RIGHT] = CreateSprite(&sSpriteTemplate_PokeLogoRight, 0, LOGO_Y, 0);
    sLogoSpriteIds[LOGO_GOTCHI_LEFT] = CreateSprite(&sSpriteTemplate_GotchiLogoLeft, 0, LOGO_Y, 0);
    sLogoSpriteIds[LOGO_GOTCHI_RIGHT] = CreateSprite(&sSpriteTemplate_GotchiLogoRight, 0, LOGO_Y, 0);
    PokegotchiIntro_SetLogoPositions(POKE_START_X, GOTCHI_START_X);
}

static void PokegotchiIntro_SetLogoPositions(s16 pokeX, s16 gotchiX)
{
    gSprites[sLogoSpriteIds[LOGO_POKE_LEFT]].x = pokeX + LOGO_HALF_WIDTH / 2;
    gSprites[sLogoSpriteIds[LOGO_POKE_RIGHT]].x = pokeX + LOGO_HALF_WIDTH + LOGO_HALF_WIDTH / 2;
    gSprites[sLogoSpriteIds[LOGO_GOTCHI_LEFT]].x = gotchiX + LOGO_HALF_WIDTH / 2;
    gSprites[sLogoSpriteIds[LOGO_GOTCHI_RIGHT]].x = gotchiX + LOGO_HALF_WIDTH + LOGO_HALF_WIDTH / 2;
}

static void PokegotchiIntro_StartFadeOut(u8 taskId)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Task_FadeOutIntro;
}
