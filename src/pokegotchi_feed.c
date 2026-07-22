#include "global.h"
#include "pokegotchi_feed.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "field_weather.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "palette.h"
#include "pokegotchi_sprites.h"
#include "scanline_effect.h"
#include "sound.h"
#include "task.h"
#include "text_window.h"
#include "constants/rgb.h"
#include "constants/songs.h"

struct MenuResources
{
    MainCallback savedCallback;
    u8 gfxLoadState;
    u8 petSpriteId;
};

enum WindowIds
{
    MAIN_WINDOW,
};

static EWRAM_DATA struct MenuResources *sMenuDataPtr = NULL;
static EWRAM_DATA u8 *sBg1TilemapBuffer = NULL;

static void Menu_Init(MainCallback callback);
static void Menu_RunSetup(void);
static void Menu_MainCB(void);
static void Menu_VBlankCB(void);
static void Menu_ResetGpuRegsAndBgs(void);
static bool8 Menu_DoGfxSetup(void);
static void Menu_FreeResources(void);
static void Task_MenuWaitFadeAndBail(u8 taskId);
static void Menu_FadeAndBail(void);
static bool8 Menu_InitBgs(void);
static bool8 Menu_LoadGraphics(void);
static void Menu_InitWindows(void);
static void Menu_LoadPetSprite(void);
static void Task_MenuWaitFadeIn(u8 taskId);
static void Task_MenuMain(u8 taskId);

static const struct BgTemplate sMenuBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .priority = 1
    },
    {
        .bg = 1,
        .charBaseIndex = 3,
        .mapBaseIndex = 30,
        .priority = 2
    },
    {
        .bg = 2,
        .charBaseIndex = 0,
        .mapBaseIndex = 28,
        .priority = 0
    }
};

static const struct WindowTemplate sMenuWindowTemplates[] =
{
    [MAIN_WINDOW] =
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 4,
        .paletteNum = 14,
        .baseBlock = 20,
    },
    DUMMY_WIN_TEMPLATE,
};

static const u32 sMenuTiles[] = INCBIN_U32("graphics/pokegotchi_feed_ui/room_tiles.4bpp.lz");
static const u32 sMenuTilemap[] = INCBIN_U32("graphics/pokegotchi_feed_ui/room_tilemap.bin.lz");
static const u16 sMenuPalette[] = INCGFX_U16("graphics/pokegotchi_feed_ui/room_tiles.png", ".gbapal");

enum Colors
{
    FONT_BLACK,
    FONT_WHITE,
    FONT_RED,
    FONT_BLUE,
};

static const u8 sMenuWindowFontColors[][3] =
{
    [FONT_BLACK] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY},
    [FONT_WHITE] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY},
    [FONT_RED] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_RED, TEXT_COLOR_LIGHT_GRAY},
    [FONT_BLUE] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_BLUE, TEXT_COLOR_LIGHT_GRAY},
};

void OpenPokegotchiFeedMenu(MainCallback exitCallback)
{
    Menu_Init(exitCallback);
}

static void Menu_Init(MainCallback callback)
{
    if ((sMenuDataPtr = AllocZeroed(sizeof(struct MenuResources))) == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    sMenuDataPtr->gfxLoadState = 0;
    sMenuDataPtr->savedCallback = callback;
    sMenuDataPtr->petSpriteId = SPRITE_NONE;

    SetMainCallback2(Menu_RunSetup);
}

static void Menu_RunSetup(void)
{
    while (1)
    {
        if (Menu_DoGfxSetup() == TRUE)
            break;
    }
}

static void Menu_MainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void Menu_VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void Menu_ResetGpuRegsAndBgs(void)
{
    DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000);
}

static bool8 Menu_DoGfxSetup(void)
{
    switch (gMain.state)
    {
    case 0:
        Menu_ResetGpuRegsAndBgs();
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        gMain.state++;
        break;
    case 2:
        if (Menu_InitBgs())
        {
            sMenuDataPtr->gfxLoadState = 0;
            gMain.state++;
        }
        else
        {
            Menu_FadeAndBail();
            return TRUE;
        }
        break;
    case 3:
        if (Menu_LoadGraphics() == TRUE)
            gMain.state++;
        break;
    case 4:
        Menu_InitWindows();
        gMain.state++;
        break;
    case 5:
        Menu_LoadPetSprite();
        CreateTask(Task_MenuWaitFadeIn, 0);
        gMain.state++;
        break;
    case 6:
        SetVBlankCallback(Menu_VBlankCB);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    case 7:
        SetMainCallback2(Menu_MainCB);
        return TRUE;
    }

    return FALSE;
}

#define try_free(ptr) ({          \
    void **ptr__ = (void **)&(ptr); \
    if (*ptr__ != NULL)            \
        Free(*ptr__);              \
})

static void Menu_FreeResources(void)
{
    if (sMenuDataPtr != NULL && sMenuDataPtr->petSpriteId != SPRITE_NONE)
    {
        DestroyPokegotchiSprite(sMenuDataPtr->petSpriteId);
        sMenuDataPtr->petSpriteId = SPRITE_NONE;
    }

    try_free(sMenuDataPtr);
    try_free(sBg1TilemapBuffer);
    FreeAllWindowBuffers();
}

static void Task_MenuWaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sMenuDataPtr->savedCallback);
        Menu_FreeResources();
        DestroyTask(taskId);
    }
}

static void Menu_FadeAndBail(void)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_MenuWaitFadeAndBail, 0);
    SetVBlankCallback(Menu_VBlankCB);
    SetMainCallback2(Menu_MainCB);
}

static bool8 Menu_InitBgs(void)
{
    ResetAllBgsCoordinates();
    sBg1TilemapBuffer = AllocZeroed(BG_SCREEN_SIZE);
    if (sBg1TilemapBuffer == NULL)
        return FALSE;

    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sMenuBgTemplates, NELEMS(sMenuBgTemplates));
    SetBgTilemapBuffer(1, sBg1TilemapBuffer);
    ScheduleBgCopyTilemapToVram(1);
    ScheduleBgCopyTilemapToVram(2);

    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    return TRUE;
}

static bool8 Menu_LoadGraphics(void)
{
    switch (sMenuDataPtr->gfxLoadState)
    {
    case 0:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(1, sMenuTiles, 0, 0, 0);
        sMenuDataPtr->gfxLoadState++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            DecompressDataWithHeaderWram(sMenuTilemap, sBg1TilemapBuffer);
            sMenuDataPtr->gfxLoadState++;
        }
        break;
    case 2:
        LoadPalette(sMenuPalette, 0, 32);
        sMenuDataPtr->gfxLoadState++;
        break;
    default:
        sMenuDataPtr->gfxLoadState = 0;
        return TRUE;
    }

    return FALSE;
}

static void Menu_InitWindows(void)
{
    InitWindows(sMenuWindowTemplates);
    DeactivateAllTextPrinters();
    ScheduleBgCopyTilemapToVram(0);

    FillWindowPixelBuffer(MAIN_WINDOW, 0);
    PutWindowTilemap(MAIN_WINDOW);
    CopyWindowToVram(MAIN_WINDOW, COPYWIN_FULL);

    ScheduleBgCopyTilemapToVram(2);
}

static void Menu_LoadPetSprite(void)
{
    enum Species species;

    species = SPECIES_FOMANTIS;
    if (species == SPECIES_NONE || species == SPECIES_EGG)
        return;

    if (!HasPokegotchiSprite(species, POKEGOTCHI_EMOTION_IDLE))
        return;

    sMenuDataPtr->petSpriteId = CreatePokegotchiSprite(species, POKEGOTCHI_EMOTION_IDLE, 120, 88, 0);
}

static void Task_MenuWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_MenuMain;
}

static void Task_MenuMain(u8 taskId)
{
    if (JOY_NEW(B_BUTTON) && !gPaletteFade.active)
    {
        PlaySE(SE_SELECT);
        Menu_FadeAndBail();
        DestroyTask(taskId);
    }
}
