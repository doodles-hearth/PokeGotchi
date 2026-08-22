#include "global.h"
#include "pokegotchi_status.h"
#include "pokegotchi.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "field_weather.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "international_string_util.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "palette.h"
#include "pokemon.h"
#include "pokegotchi_sprites.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "text_window.h"
#include "constants/rgb.h"
#include "constants/songs.h"

#define STATUS_HEART_TILE_TAG      6100
#define STATUS_HEART_PAL_TAG       6101
#define STATUS_HEART_SPRITE_SIZE   (16 * 16 / 2)
#define STATUS_HEART_ROWS          3
#define STATUS_HEARTS_PER_ROW      5
#define STATUS_HEART_COUNT         (STATUS_HEART_ROWS * STATUS_HEARTS_PER_ROW)
#define STATUS_TEXT_LABEL_X        56
#define STATUS_TEXT_NICKNAME_Y     12

enum StatusTextRows
{
    STATUS_TEXT_ROW_FOOD,
    STATUS_TEXT_ROW_HAPPY,
    STATUS_TEXT_ROW_FUN,
};

struct MenuResources
{
    MainCallback savedCallback;
    u8 gfxLoadState;
    u8 petSpriteId;
    u8 heartSpriteIds[STATUS_HEART_COUNT];
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
static void Menu_PrintText(void);
static void Menu_LoadPetSprite(void);
static void Menu_LoadHeartSprites(void);
static void Task_MenuWaitFadeIn(u8 taskId);
static void Task_MenuMain(u8 taskId);
static void DestroyHeartSprites(void);
static bool8 CreateHeartSprites(void);
static void UpdateHeartSprites(void);
static u8 GetHeartCountForStat(u16 stat);
static bool8 TryGetStatusNickname(u8 *dest);

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
        .height = 20,
        .paletteNum = 14,
        .baseBlock = 20,
    },
    DUMMY_WIN_TEMPLATE,
};

static const u32 sMenuTiles[] = INCBIN_U32("graphics/pokegotchi_stats_ui/room_tiles.4bpp.lz");
static const u32 sMenuTilemap[] = INCBIN_U32("graphics/pokegotchi_stats_ui/room_tilemap.bin.lz");
static const u16 sMenuPalette[] = INCGFX_U16("graphics/pokegotchi_stats_ui/room_tiles.png", ".gbapal");
static const u16 sMenuTextPalette[] = INCGFX_U16("graphics/pokegotchi_stats_ui/status_text.pal", ".gbapal");
static const u8 sHeartSpriteTiles[] = INCGFX_U8("graphics/pokegotchi_stats_ui/heart.png", ".4bpp");
static const u16 sHeartSpritePalette[] = INCGFX_U16("graphics/pokegotchi_stats_ui/heart.png", ".gbapal");
static const u8 sText_StatusFood[] = _("Food");
static const u8 sText_StatusHappy[] = _("Happy");
static const u8 sText_StatusFun[] = _("Fun");

static const s16 sHeartSpriteXCoords[STATUS_HEARTS_PER_ROW] = {104, 120, 136, 152, 168};
static const s16 sHeartSpriteYCoords[STATUS_HEART_ROWS] = {64, 96, 128};
static const u8 *const sStatusStatLabels[STATUS_HEART_ROWS] =
{
    [STATUS_TEXT_ROW_FOOD] = sText_StatusFood,
    [STATUS_TEXT_ROW_HAPPY] = sText_StatusHappy,
    [STATUS_TEXT_ROW_FUN] = sText_StatusFun,
};
static const u8 sStatusTextLabelYCoords[STATUS_HEART_ROWS] = {56, 86, 120};

static const union AnimCmd sAnim_Heart[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END,
};

static const union AnimCmd *const sHeartSpriteAnims[] =
{
    sAnim_Heart,
};

static const struct OamData sHeartSpriteOamData =
{
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 0,
    .bpp = ST_OAM_4BPP,
};

static const struct SpriteTemplate sHeartSpriteTemplate =
{
    .tileTag = STATUS_HEART_TILE_TAG,
    .paletteTag = STATUS_HEART_PAL_TAG,
    .oam = &sHeartSpriteOamData,
    .anims = sHeartSpriteAnims,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

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

void OpenPokegotchiStatusMenu(MainCallback exitCallback)
{
    Menu_Init(exitCallback);
}

static void Menu_Init(MainCallback callback)
{
    u32 i;

    if ((sMenuDataPtr = AllocZeroed(sizeof(struct MenuResources))) == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    Pokegotchi_SyncAndSave();

    sMenuDataPtr->gfxLoadState = 0;
    sMenuDataPtr->savedCallback = callback;
    sMenuDataPtr->petSpriteId = SPRITE_NONE;
    for (i = 0; i < ARRAY_COUNT(sMenuDataPtr->heartSpriteIds); i++)
        sMenuDataPtr->heartSpriteIds[i] = MAX_SPRITES;

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
        Menu_PrintText();
        gMain.state++;
        break;
    case 5:
        Menu_LoadPetSprite();
        Menu_LoadHeartSprites();
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

    DestroyHeartSprites();

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
        LoadPalette(sMenuTextPalette, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
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

    FillWindowPixelBuffer(MAIN_WINDOW, PIXEL_FILL(0));
    PutWindowTilemap(MAIN_WINDOW);
    CopyWindowToVram(MAIN_WINDOW, COPYWIN_FULL);

    ScheduleBgCopyTilemapToVram(2);
}

static void Menu_PrintText(void)
{
    u8 nickname[POKEMON_NAME_BUFFER_SIZE];
    u32 i;

    FillWindowPixelBuffer(MAIN_WINDOW, PIXEL_FILL(0));

    if (TryGetStatusNickname(nickname))
    {
        u8 x = GetStringCenterAlignXOffset(FONT_NORMAL, nickname, DISPLAY_WIDTH);

        AddTextPrinterParameterized3(MAIN_WINDOW,
                                     FONT_NORMAL,
                                     x,
                                     STATUS_TEXT_NICKNAME_Y,
                                     sMenuWindowFontColors[FONT_BLACK],
                                     TEXT_SKIP_DRAW,
                                     nickname);
    }

    for (i = 0; i < ARRAY_COUNT(sStatusStatLabels); i++)
    {
        AddTextPrinterParameterized3(MAIN_WINDOW,
                                     FONT_NORMAL,
                                     STATUS_TEXT_LABEL_X,
                                     sStatusTextLabelYCoords[i],
                                     sMenuWindowFontColors[FONT_BLACK],
                                     TEXT_SKIP_DRAW,
                                     sStatusStatLabels[i]);
    }

    CopyWindowToVram(MAIN_WINDOW, COPYWIN_FULL);
}

static void Menu_LoadPetSprite(void)
{
    enum Species species;

    species = Pokegotchi_GetPrimarySpecies();
    if (species == SPECIES_NONE)
        return;

    if (!HasPokegotchiSprite(species, POKEGOTCHI_EMOTION_IDLE))
        return;

    sMenuDataPtr->petSpriteId = CreatePokegotchiSprite(species, POKEGOTCHI_EMOTION_IDLE, 32, 26, 0);
}

static void Menu_LoadHeartSprites(void)
{
    if (!CreateHeartSprites())
        return;

    UpdateHeartSprites();
}

static void DestroyHeartSprites(void)
{
    u32 i;

    if (sMenuDataPtr == NULL)
        return;

    for (i = 0; i < ARRAY_COUNT(sMenuDataPtr->heartSpriteIds); i++)
    {
        u8 spriteId = sMenuDataPtr->heartSpriteIds[i];

        if (spriteId < MAX_SPRITES && gSprites[spriteId].inUse)
            DestroySprite(&gSprites[spriteId]);

        sMenuDataPtr->heartSpriteIds[i] = MAX_SPRITES;
    }

    FreeSpriteTilesByTag(STATUS_HEART_TILE_TAG);
    FreeSpritePaletteByTag(STATUS_HEART_PAL_TAG);
}

static bool8 CreateHeartSprites(void)
{
    struct SpriteSheet spriteSheet = {
        .data = sHeartSpriteTiles,
        .size = STATUS_HEART_SPRITE_SIZE,
        .tag = STATUS_HEART_TILE_TAG,
    };
    struct SpritePalette spritePalette = {
        .data = sHeartSpritePalette,
        .tag = STATUS_HEART_PAL_TAG,
    };
    u32 row;
    u32 column;
    u32 heartIndex = 0;

    if (LoadSpriteSheet(&spriteSheet) == TAG_NONE)
        return FALSE;

    if (LoadSpritePalette(&spritePalette) == 0xFF)
    {
        FreeSpriteTilesByTag(STATUS_HEART_TILE_TAG);
        return FALSE;
    }

    for (row = 0; row < STATUS_HEART_ROWS; row++)
    {
        for (column = 0; column < STATUS_HEARTS_PER_ROW; column++, heartIndex++)
        {
            u8 spriteId = CreateSprite(&sHeartSpriteTemplate,
                                        sHeartSpriteXCoords[column],
                                        sHeartSpriteYCoords[row],
                                        1);

            if (spriteId == MAX_SPRITES)
            {
                DestroyHeartSprites();
                return FALSE;
            }

            sMenuDataPtr->heartSpriteIds[heartIndex] = spriteId;
        }
    }

    return TRUE;
}

static void UpdateHeartSprites(void)
{
    struct PokegotchiRuntimeState *runtime = PokegotchiSave_GetRuntimeMutable();
    struct PokegotchiStats *stats = &runtime->stats;
    const u16 statValues[STATUS_HEART_ROWS] = {stats->food, stats->happy, stats->fun};
    u32 row;
    u32 column;
    u32 heartIndex = 0;

    for (row = 0; row < STATUS_HEART_ROWS; row++)
    {
        u8 heartCount = GetHeartCountForStat(statValues[row]);

        for (column = 0; column < STATUS_HEARTS_PER_ROW; column++, heartIndex++)
        {
            u8 spriteId = sMenuDataPtr->heartSpriteIds[heartIndex];

            if (spriteId < MAX_SPRITES && gSprites[spriteId].inUse)
                gSprites[spriteId].invisible = column >= heartCount;
        }
    }
}

static u8 GetHeartCountForStat(u16 stat)
{
    return min(STATUS_HEARTS_PER_ROW, (stat + 25) / 50);
}

static bool8 TryGetStatusNickname(u8 *dest)
{
    struct PokegotchiRuntimeState *runtime = PokegotchiSave_GetRuntimeMutable();
    struct Pokemon *mon;
    enum Species species;

    if (runtime->playerPartyCount == 0)
        return FALSE;

    mon = &runtime->playerParty[0];
    species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG);
    if (species == SPECIES_NONE || species == SPECIES_EGG)
        return FALSE;

    GetMonData(mon, MON_DATA_NICKNAME, dest);
    return TRUE;
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
