#include "global.h"
#include "pokegotchi_house.h"
#include "pokegotchi.h"
#include "pokegotchi_feed.h"
#include "pokegotchi_intro.h"
#include "pokegotchi_status.h"
#include "strings.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "field_weather.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "item.h"
#include "item_menu.h"
#include "item_menu_icons.h"
#include "list_menu.h"
#include "item_icon.h"
#include "item_use.h"
#include "international_string_util.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "palette.h"
#include "party_menu.h"
#include "pokemon.h"
#include "pokegotchi_sprites.h"
#include "scanline_effect.h"
#include "script.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text_window.h"
#include "overworld.h"
#include "field_screen_effect.h"
#include "field_specials.h"
#include "event_data.h"
#include "constants/items.h"
#include "constants/field_weather.h"
#include "constants/maps.h"
#include "constants/songs.h"
#include "constants/rgb.h"

/*
 * 
 */
 
//==========DEFINES==========//
#define MENU_ICONS 4

struct MenuResources
{
    MainCallback savedCallback; // determines callback to run when we exit. e.g. where do we want to go after closing the menu
    u8 gfxLoadState;
    u8 menuIconIds[MENU_ICONS];
    u8 petSpriteId;
    u8 syncTaskId;
};

enum WindowIds
{
    ICONS_WINDOW,
    POKEMON_WINDOW,
};

//==========EWRAM==========//
static EWRAM_DATA struct MenuResources *sMenuDataPtr = NULL;
static EWRAM_DATA u8 *sBg1TilemapBuffer = NULL;
static EWRAM_DATA MainCallback sHouseMenuExitCallback = NULL;

//==========STATIC=DEFINES==========//
static void Menu_Init(MainCallback callback);
static void Menu_RunSetup(void);
static bool8 Menu_DoGfxSetup(void);
static bool8 Menu_InitBgs(void);
static void Menu_FadeAndBail(void);
static bool8 Menu_LoadGraphics(void);
static void Menu_InitWindows(void);
static void Menu_LoadTopIcons(void);
static void Menu_LoadPetSprite(void);
static void Menu_SetSelectedTopIcon(u8 selectedIcon);
static void Task_MenuWaitFadeIn(u8 taskId);
static void Task_MenuMain(u8 taskId);
static void Task_MenuSyncPokegotchi(u8 taskId);
static void CB2_ReturnToPokegotchiHouseMenu(void);
static void CB2_OpenPokegotchiFeedMenuFromHouse(void);
static void CB2_OpenPokegotchiStatusMenuFromHouse(void);
static void CB2_ExitToTamatownFromHouse(void);

//==========CONST=DATA==========//
static const struct BgTemplate sMenuBgTemplates[] =
{
    {
        .bg = 0,    // windows, etc
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
    [ICONS_WINDOW] =
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 240,
        .height = 4,
        .paletteNum = 14,
        .baseBlock = 20,
    },
    DUMMY_WIN_TEMPLATE,
};

static const u32 sMenuTiles[]   = INCBIN_U32("graphics/pokegotchi_house_ui/room_tiles.4bpp.lz");
static const u32 sMenuTilemap[] = INCBIN_U32("graphics/pokegotchi_house_ui/room_tilemap.bin.lz");
static const u16 sMenuPalette[] = INCGFX_U16("graphics/pokegotchi_house_ui/room_tiles.png", ".gbapal");

enum Colors
{
    FONT_BLACK,
    FONT_WHITE,
    FONT_RED,
    FONT_BLUE,
};
static const u8 sMenuWindowFontColors[][3] = 
{
    [FONT_BLACK] = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_DARK_GRAY,  TEXT_COLOR_LIGHT_GRAY},
    [FONT_WHITE] = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_WHITE,      TEXT_COLOR_DARK_GRAY},
    [FONT_RED]   = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_RED,        TEXT_COLOR_LIGHT_GRAY},
    [FONT_BLUE]  = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_BLUE,       TEXT_COLOR_LIGHT_GRAY},
};

#define ICON_1_SPRITE_TAG 5521
#define ICON_2_SPRITE_TAG 5522
#define ICON_3_SPRITE_TAG 5523
#define ICON_4_SPRITE_TAG 5524
#define ICON_SPRITES_PAL_TAG 5525

#define SPRITE_SELECTED 0
#define SPRITE_UNSELECTED 1

#define STATUS_ICON 0
#define FOOD_ICON 1
#define CLEAN_ICON 2
#define TOWN_ICON 3
#define HOUSE_SYNC_INTERVAL_FRAMES (3 * 60 * 60) // Update stats every 3 minutes

static const u8 sMenuIconStatusSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_house_ui/menu_status.png", ".4bpp");
static const u8 sMenuIconFoodSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_house_ui/menu_food.png", ".4bpp");
static const u8 sMenuIconCleanSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_house_ui/menu_clean.png", ".4bpp");
static const u8 sMenuIconTownSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_house_ui/menu_town.png", ".4bpp");
static const u16 sMenuIconSpritesPalette[] = INCGFX_U16("graphics/pokegotchi_house_ui/menu_status.png", ".gbapal");

static const struct SpriteSheet sMenuIconsSpriteSheets[] =
{
    {sMenuIconStatusSpriteGfx, sizeof(sMenuIconStatusSpriteGfx), ICON_1_SPRITE_TAG},
    {sMenuIconFoodSpriteGfx,   sizeof(sMenuIconFoodSpriteGfx),   ICON_2_SPRITE_TAG},
    {sMenuIconCleanSpriteGfx,  sizeof(sMenuIconCleanSpriteGfx),  ICON_3_SPRITE_TAG},
    {sMenuIconTownSpriteGfx,   sizeof(sMenuIconTownSpriteGfx),   ICON_4_SPRITE_TAG},
};

static const s16 sMenuIconsSpriteCoords[MENU_ICONS][2] =
{
    {30,  16},
    {90,  16},
    {150, 16},
    {210, 16},
};

static const struct SpritePalette sMenuIconsPalette =
{
    .data = sMenuIconSpritesPalette,
    .tag = ICON_SPRITES_PAL_TAG,
};

static const union AnimCmd sAnim_UnselectedIcon[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END
};
static const union AnimCmd sAnim_SelectedIcon[] =
{
    ANIMCMD_FRAME(16, 0),
    ANIMCMD_END
};

static const union AnimCmd *const sMenuIconSpriteAnims[] =
{
    [SPRITE_UNSELECTED] = sAnim_UnselectedIcon,
    [SPRITE_SELECTED] = sAnim_SelectedIcon,
};

static const struct OamData sMenuIconsSpriteOamData =
{
    .x = 0,
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = 0,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 1,
    .affineParam = 0,
};

static const struct SpriteTemplate sMenuIconsSprites[MENU_ICONS] =
{
    [STATUS_ICON] =
    {
        .tileTag = ICON_1_SPRITE_TAG,
        .paletteTag = ICON_SPRITES_PAL_TAG,
        .anims = sMenuIconSpriteAnims,
        .oam = &sMenuIconsSpriteOamData,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy,
    },
    [FOOD_ICON] =
    {
        .tileTag = ICON_2_SPRITE_TAG,
        .paletteTag = ICON_SPRITES_PAL_TAG,
        .anims = sMenuIconSpriteAnims,
        .oam = &sMenuIconsSpriteOamData,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy,
    },
    [CLEAN_ICON] =
    {
        .tileTag = ICON_3_SPRITE_TAG,
        .paletteTag = ICON_SPRITES_PAL_TAG,
        .anims = sMenuIconSpriteAnims,
        .oam = &sMenuIconsSpriteOamData,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy,
    },
    [TOWN_ICON] =
    {
        .tileTag = ICON_4_SPRITE_TAG,
        .paletteTag = ICON_SPRITES_PAL_TAG,
        .anims = sMenuIconSpriteAnims,
        .oam = &sMenuIconsSpriteOamData,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy,
    },
};

//==========FUNCTIONS==========//
void OpenPokegotchiHouseMenu(MainCallback callback)
{
    Menu_Init(callback);
}

// UI loader template
void MainCB2_InitPokegotchiHouseMenu(void)
{
    OpenPokegotchiHouseMenu(CB2_InitPokegotchiBootup);
}

// This is our main initialization function if you want to call the menu from elsewhere
static void Menu_Init(MainCallback callback)
{
    u8 i;

    if ((sMenuDataPtr = AllocZeroed(sizeof(struct MenuResources))) == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    Pokegotchi_SyncAndSave();

    // initialize stuff
    sMenuDataPtr->gfxLoadState = 0;
    sMenuDataPtr->savedCallback = callback;
    for (i = 0; i < MENU_ICONS; i++)
        sMenuDataPtr->menuIconIds[i] = MAX_SPRITES;
    sMenuDataPtr->petSpriteId = SPRITE_NONE;
    sMenuDataPtr->syncTaskId = TASK_NONE;

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
        {
            gMain.state++;
        }
        break;
    case 4:
        Menu_InitWindows();
        gMain.state++;
        break;
    case 5:
        Menu_LoadTopIcons();
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

#define try_free(ptr) ({        \
    void ** ptr__ = (void **)&(ptr);   \
    if (*ptr__ != NULL)                \
        Free(*ptr__);                  \
})

static void Menu_FreeResources(void)
{
    u8 i;

    if (sMenuDataPtr != NULL)
    {
        for (i = 0; i < MENU_ICONS; i++)
        {
            if (sMenuDataPtr->menuIconIds[i] != MAX_SPRITES)
            {
                DestroySprite(&gSprites[sMenuDataPtr->menuIconIds[i]]);
                sMenuDataPtr->menuIconIds[i] = MAX_SPRITES;
            }
        }

        if (sMenuDataPtr->petSpriteId != SPRITE_NONE)
        {
            DestroyPokegotchiSprite(sMenuDataPtr->petSpriteId);
            sMenuDataPtr->petSpriteId = SPRITE_NONE;
        }

        if (sMenuDataPtr->syncTaskId != TASK_NONE && FuncIsActiveTask(Task_MenuSyncPokegotchi))
        {
            DestroyTask(sMenuDataPtr->syncTaskId);
            sMenuDataPtr->syncTaskId = TASK_NONE;
        }
    }

    FreeSpriteTilesByTag(ICON_1_SPRITE_TAG);
    FreeSpriteTilesByTag(ICON_2_SPRITE_TAG);
    FreeSpriteTilesByTag(ICON_3_SPRITE_TAG);
    FreeSpriteTilesByTag(ICON_4_SPRITE_TAG);
    FreeSpritePaletteByTag(ICON_SPRITES_PAL_TAG);
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
    
    FillWindowPixelBuffer(ICONS_WINDOW, 0);
    PutWindowTilemap(ICONS_WINDOW);
    CopyWindowToVram(ICONS_WINDOW, 3);
    
    ScheduleBgCopyTilemapToVram(2);
}

static void Menu_LoadTopIcons(void)
{
    u8 i;

    for (i = 0; i < MENU_ICONS; i++)
    {
        LoadSpriteSheet(&sMenuIconsSpriteSheets[i]);
    }
    LoadSpritePalette(&sMenuIconsPalette);

    for (i = 0; i < MENU_ICONS; i++)
    {
        sMenuDataPtr->menuIconIds[i] = CreateSprite(&sMenuIconsSprites[i],
                                                    sMenuIconsSpriteCoords[i][0],
                                                    sMenuIconsSpriteCoords[i][1],
                                                    0);
    }

    Menu_SetSelectedTopIcon(STATUS_ICON);
}

static void Menu_LoadPetSprite(void)
{
    enum Species species;

    // species = GetMonData(&gParties[B_TRAINER_PLAYER][GetLeadMonIndex()], MON_DATA_SPECIES_OR_EGG);
    species = SPECIES_FOMANTIS; // hardcode fomantis for now
    if (species == SPECIES_NONE || species == SPECIES_EGG)
        return;
    if (!HasPokegotchiSprite(species, POKEGOTCHI_EMOTION_IDLE))
        return;

    sMenuDataPtr->petSpriteId = CreatePokegotchiSprite(species, POKEGOTCHI_EMOTION_IDLE, 120, 88, 0);
}

static void Menu_SetSelectedTopIcon(u8 selectedIcon)
{
    u8 i;

    for (i = 0; i < MENU_ICONS; i++)
    {
        if (sMenuDataPtr->menuIconIds[i] != MAX_SPRITES)
        {
            StartSpriteAnimIfDifferent(&gSprites[sMenuDataPtr->menuIconIds[i]],
                                       (i == selectedIcon ? SPRITE_SELECTED : SPRITE_UNSELECTED));
        }
    }
}

static void Task_MenuWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        gTasks[taskId].data[0] = STATUS_ICON;
        sMenuDataPtr->syncTaskId = CreateTask(Task_MenuSyncPokegotchi, 1);
        gTasks[taskId].func = Task_MenuMain;
    }
}

static void Task_MenuSyncPokegotchi(u8 taskId)
{
    if (++gTasks[taskId].data[0] >= HOUSE_SYNC_INTERVAL_FRAMES)
    {
        gTasks[taskId].data[0] = 0;
        Pokegotchi_SyncAndSave();
    }
}

static void CB2_ReturnToPokegotchiHouseMenu(void)
{
    OpenPokegotchiHouseMenu(sHouseMenuExitCallback);
}

static void CB2_OpenPokegotchiFeedMenuFromHouse(void)
{
    OpenPokegotchiFeedMenu(CB2_ReturnToPokegotchiHouseMenu);
}

static void CB2_OpenPokegotchiStatusMenuFromHouse(void)
{
    OpenPokegotchiStatusMenu(CB2_ReturnToPokegotchiHouseMenu);
}

static void CB2_ExitToTamatownFromHouse(void)
{
    Pokegotchi_SyncAndSave();
    SetWarpDestination(MAP_GROUP(MAP_TAMATOWN), MAP_NUM(MAP_TAMATOWN), WARP_ID_NONE, 30, 17);
    gFieldCallback = FieldCB_DefaultWarpExit;
    WarpIntoMap();
    ResetInitialPlayerAvatarState();
    SetMainCallback2(CB2_LoadMap);
}

static UNUSED void Task_MenuLeave(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sMenuDataPtr->savedCallback);
        Menu_FreeResources();
        DestroyTask(taskId);
    }
}


/* This is the meat of the UI. This is where you wait for player inputs and can branch to other tasks accordingly */
static void Task_MenuMain(u8 taskId)
{
    s16 newSelection = gTasks[taskId].data[0];

    if (JOY_NEW(DPAD_LEFT) && newSelection > STATUS_ICON)
        newSelection--;
    else if (JOY_NEW(DPAD_RIGHT) && newSelection < TOWN_ICON)
        newSelection++;

    if (newSelection != gTasks[taskId].data[0])
    {
        gTasks[taskId].data[0] = newSelection;
        Menu_SetSelectedTopIcon(newSelection);
        PlaySE(SE_SELECT);
    }

    if (JOY_NEW(A_BUTTON))
    {
        switch (gTasks[taskId].data[0])
        {
        case STATUS_ICON:
            sHouseMenuExitCallback = sMenuDataPtr->savedCallback;
            sMenuDataPtr->savedCallback = CB2_OpenPokegotchiStatusMenuFromHouse;
            PlaySE(SE_SELECT);
            Menu_FadeAndBail();
            DestroyTask(taskId);
            return;
        case FOOD_ICON:
            sHouseMenuExitCallback = sMenuDataPtr->savedCallback;
            sMenuDataPtr->savedCallback = CB2_OpenPokegotchiFeedMenuFromHouse;
            PlaySE(SE_SELECT);
            Menu_FadeAndBail();
            DestroyTask(taskId);
            return;
        case CLEAN_ICON:
            if (!IsSEPlaying())
                PlaySE(SE_FAILURE);
            break;
        case TOWN_ICON:
            sMenuDataPtr->savedCallback = CB2_ExitToTamatownFromHouse;
            PlaySE(SE_SELECT);
            Menu_FadeAndBail();
            DestroyTask(taskId);
            return;
        default:
            if (!IsSEPlaying())
                PlaySE(SE_FAILURE);
            break;
        }
    }

    if (JOY_NEW(B_BUTTON) && !IsSEPlaying())
    {
        PlaySE(SE_FAILURE);
    }
}
