#include "global.h"
#include "pokegotchi_feed.h"
#include "pokegotchi.h"
#include "pokegotchi_house.h"
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
#include "pokegotchi_sprites.h"
#include "scanline_effect.h"
#include "sound.h"
#include "string_util.h"
#include "task.h"
#include "text_window.h"
#include "constants/rgb.h"
#include "constants/songs.h"

#define FEED_TEXT_NICKNAME_Y 12
#define FEED_TEXT_CATEGORY_Y 56
#define FEED_TEXT_MEAL_CENTER_X 72
#define FEED_TEXT_SNACK_CENTER_X 168
#define FEED_CURSOR_COLUMNS 4
#define FEED_CURSOR_ROWS 2
#define FEED_CURSOR_START_SLOT 0
#define FEED_CURSOR_OFFSET_X 8
#define FEED_CURSOR_OFFSET_Y 8
#define FEED_QUANTITY_RIGHT_EDGE_OFFSET 6
#define FEED_QUANTITY_OFFSET_Y 6

struct MenuResources
{
    MainCallback savedCallback;
    u8 gfxLoadState;
    u8 petSpriteId;
    u8 cursorSpriteId;
    u8 selectedSlot;
    u8 foodSpriteIds[FEED_FOOD_SLOT_COUNT];
};

struct PokegotchiFoodEffect
{
    u8 inventoryKey;
    u8 food;
    u8 fun;
};

enum WindowIds
{
    MAIN_WINDOW,
};

static EWRAM_DATA struct MenuResources *sMenuDataPtr = NULL;
static EWRAM_DATA u8 *sBg1TilemapBuffer = NULL;
static EWRAM_DATA MainCallback sFeedMenuExitCallback = NULL;
static EWRAM_DATA u8 sPendingConsumedFoodKey = FEED_FOOD_KEY_NONE;

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
static void Menu_LoadFoodSprites(void);
static bool8 Menu_LoadCursorSpriteSheet(void);
static bool8 Menu_LoadCursorSpritePalette(void);
static void Menu_CreateCursorSprite(void);
static void Menu_UpdateCursorSprite(void);
static bool8 Menu_MoveFeedCursor(s8 dx, s8 dy);
static const struct PokegotchiFoodEffect *Menu_GetFoodEffect(u8 inventoryKey);
static const struct PokegotchiFeedFoodItem *Menu_GetFoodItemForVisualSlot(u8 visualSlot);
static u16 Menu_AddStatIncrease(u16 current, u8 increase);
static bool8 Menu_ConsumeFoodByKey(u8 inventoryKey);
static u8 Menu_GetFoodCount(u8 inventoryKey);
static u8 Menu_GetFoodCountForVisualSlot(u8 visualSlot);
static bool8 Menu_SelectedSlotHasFood(void);
static bool8 Menu_LoadFoodSpriteSheet(const struct PokegotchiFeedFoodItem *foodItem);
static bool8 Menu_LoadFoodSpritePalette(const struct PokegotchiFeedFoodItem *foodItem);
static void Menu_DestroyFoodSprites(void);
static void Menu_DestroyCursorSprite(void);
static void Task_MenuWaitFadeIn(u8 taskId);
static void Task_MenuMain(u8 taskId);
static bool8 TryGetFeedNickname(u8 *dest);
static void CB2_OpenPokegotchiHouseEatingSceneFromFeed(void);
static void CB2_ReturnToConsumedFoodFeedMenu(void);

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

static const u32 sMenuTiles[] = INCBIN_U32("graphics/pokegotchi_feed_ui/room_tiles.4bpp.lz");
static const u32 sMenuTilemap[] = INCBIN_U32("graphics/pokegotchi_feed_ui/room_tilemap.bin.lz");
static const u16 sMenuPalette[] = INCGFX_U16("graphics/pokegotchi_feed_ui/room_tiles.png", ".gbapal");
static const u16 sMenuTextPalette[] = INCGFX_U16("graphics/pokegotchi_feed_ui/feed_text.pal", ".gbapal");
static const u8 sText_FeedMeal[] = _("Meal");
static const u8 sText_FeedSnack[] = _("Snack");
static const u8 sText_FeedCursorGfx[] = INCGFX_U8("graphics/pokegotchi_feed_ui/cursor.png", ".4bpp");
static const u16 sText_FeedCursorPal[] = INCGFX_U16("graphics/pokegotchi_feed_ui/cursor.png", ".gbapal");

const u8 gPokegotchiFeedFoodLeafSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_feed_ui/food/meals/leaf.png", ".4bpp");
const u8 gPokegotchiFeedFoodHotDogSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_feed_ui/food/meals/hot_dog.png", ".4bpp");
const u8 gPokegotchiFeedFoodPokeblockSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_feed_ui/food/meals/pokeblock.png", ".4bpp");
const u8 gPokegotchiFeedFoodEggSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_feed_ui/food/meals/egg.png", ".4bpp");
const u8 gPokegotchiFeedFoodPechaSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_feed_ui/food/snacks/pecha.png", ".4bpp");
const u8 gPokegotchiFeedFoodIceCreamSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_feed_ui/food/snacks/ice_cream.png", ".4bpp");
const u8 gPokegotchiFeedFoodDonutSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_feed_ui/food/snacks/donut.png", ".4bpp");
// TODO
const u8 gPokegotchiFeedFoodSnack4SpriteGfx[] = INCGFX_U8("graphics/pokegotchi_feed_ui/food/snacks/pecha.png", ".4bpp");
const u16 gPokegotchiPalette[] = INCGFX_U16("graphics/pokegotchi_feed_ui/food/snacks/pecha.png", ".gbapal");

const struct PokegotchiFeedFoodItem gPokegotchiFeedFoodItems[FEED_FOOD_SLOT_COUNT] =
{
    {
        .category = FEED_FOOD_CATEGORY_MEAL,
        .slot = 0,
        .inventoryKey = FEED_FOOD_KEY_LEAF,
        .tileTag = FEED_FOOD_TILE_TAG_LEAF,
        .paletteTag = FEED_FOOD_PAL_TAG,
        .spriteTiles = gPokegotchiFeedFoodLeafSpriteGfx,
        .palette = gPokegotchiPalette,
    },
    {
        .category = FEED_FOOD_CATEGORY_MEAL,
        .slot = 1,
        .inventoryKey = FEED_FOOD_KEY_HOT_DOG,
        .tileTag = FEED_FOOD_TILE_TAG_HOT_DOG,
        .paletteTag = FEED_FOOD_PAL_TAG,
        .spriteTiles = gPokegotchiFeedFoodHotDogSpriteGfx,
        .palette = gPokegotchiPalette,
    },
    {
        .category = FEED_FOOD_CATEGORY_MEAL,
        .slot = 2,
        .inventoryKey = FEED_FOOD_KEY_POKEBLOCK,
        .tileTag = FEED_FOOD_TILE_TAG_POKEBLOCK,
        .paletteTag = FEED_FOOD_PAL_TAG,
        .spriteTiles = gPokegotchiFeedFoodPokeblockSpriteGfx,
        .palette = gPokegotchiPalette,
    },
    {
        .category = FEED_FOOD_CATEGORY_MEAL,
        .slot = 3,
        .inventoryKey = FEED_FOOD_KEY_EGG,
        .tileTag = FEED_FOOD_TILE_TAG_EGG,
        .paletteTag = FEED_FOOD_PAL_TAG,
        .spriteTiles = gPokegotchiFeedFoodEggSpriteGfx,
        .palette = gPokegotchiPalette,
    },
    {
        .category = FEED_FOOD_CATEGORY_SNACK,
        .slot = 0,
        .inventoryKey = FEED_FOOD_KEY_PECHA,
        .tileTag = FEED_FOOD_TILE_TAG_PECHA,
        .paletteTag = FEED_FOOD_PAL_TAG,
        .spriteTiles = gPokegotchiFeedFoodPechaSpriteGfx,
        .palette = gPokegotchiPalette,
    },
    {
        .category = FEED_FOOD_CATEGORY_SNACK,
        .slot = 0,
        .inventoryKey = FEED_FOOD_KEY_DONUT,
        .tileTag = FEED_FOOD_TILE_TAG_DONUT,
        .paletteTag = FEED_FOOD_PAL_TAG,
        .spriteTiles = gPokegotchiFeedFoodDonutSpriteGfx,
        .palette = gPokegotchiPalette,
    },
    {
        .category = FEED_FOOD_CATEGORY_SNACK,
        .slot = 0,
        .inventoryKey = FEED_FOOD_KEY_ICE_CREAM,
        .tileTag = FEED_FOOD_TILE_TAG_ICE_CREAM,
        .paletteTag = FEED_FOOD_PAL_TAG,
        .spriteTiles = gPokegotchiFeedFoodIceCreamSpriteGfx,
        .palette = gPokegotchiPalette,
    },
    {
        .category = FEED_FOOD_CATEGORY_SNACK,
        .slot = 0,
        .inventoryKey = FEED_FOOD_KEY_SNACK_4,
        .tileTag = FEED_FOOD_TILE_TAG_SNACK_4,
        .paletteTag = FEED_FOOD_PAL_TAG,
        .spriteTiles = gPokegotchiFeedFoodSnack4SpriteGfx,
        .palette = gPokegotchiPalette,
    },
};

static const struct PokegotchiFoodEffect sPokegotchiFoodEffects[] =
{
    {
        .inventoryKey = FEED_FOOD_KEY_LEAF,
        .food = 40,
        .fun = 10,
    },
    {
        .inventoryKey = FEED_FOOD_KEY_HOT_DOG,
        .food = 30,
        .fun = 20,
    },
    {
        .inventoryKey = FEED_FOOD_KEY_POKEBLOCK,
        .food = 45,
        .fun = 10,
    },
    {
        .inventoryKey = FEED_FOOD_KEY_EGG,
        .food = 50,
        .fun = 15,
    },

    {
        .inventoryKey = FEED_FOOD_KEY_PECHA,
        .food = 20,
        .fun = 30,
    },
    {
        .inventoryKey = FEED_FOOD_KEY_ICE_CREAM,
        .food = 20,
        .fun = 35,
    },
    {
        .inventoryKey = FEED_FOOD_KEY_DONUT,
        .food = 10,
        .fun = 40,
    },
    {
        .inventoryKey = FEED_FOOD_KEY_SNACK_4,
        .food = 20,
        .fun = 30,
    },
};

static const s16 sFoodSlotCoords[FEED_FOOD_CATEGORY_COUNT][FEED_FOOD_SLOTS_PER_CATEGORY][2] =
{
    [FEED_FOOD_CATEGORY_MEAL] =
    {
        {52, 92},
        {92, 92},
        {52, 132},
        {92, 132},
    },
    [FEED_FOOD_CATEGORY_SNACK] =
    {
        {148, 92},
        {188, 92},
        {148, 132},
        {188, 132},
    },
};

enum
{
    FEED_CURSOR_TILE_TAG = 7300,
    FEED_CURSOR_PAL_TAG = 7400,
    FEED_CURSOR_SPRITESHEET_SIZE = (16 * 32) / 2,
};

struct FeedVisualSlot
{
    u8 category;
    u8 slot;
};

static const struct FeedVisualSlot sVisualSlots[FEED_FOOD_SLOT_COUNT] =
{
    {FEED_FOOD_CATEGORY_MEAL, 0},
    {FEED_FOOD_CATEGORY_MEAL, 1},
    {FEED_FOOD_CATEGORY_SNACK, 0},
    {FEED_FOOD_CATEGORY_SNACK, 1},
    {FEED_FOOD_CATEGORY_MEAL, 2},
    {FEED_FOOD_CATEGORY_MEAL, 3},
    {FEED_FOOD_CATEGORY_SNACK, 2},
    {FEED_FOOD_CATEGORY_SNACK, 3},
};

static const union AnimCmd sAnim_FoodFrame0[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END,
};

static const union AnimCmd *const sFoodSpriteAnims[] =
{
    sAnim_FoodFrame0,
};

static const struct OamData sFoodSpriteOamData =
{
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 0,
    .bpp = ST_OAM_4BPP,
};

static const struct SpriteTemplate sFoodSpriteTemplate =
{
    .tileTag = TAG_NONE,
    .paletteTag = TAG_NONE,
    .oam = &sFoodSpriteOamData,
    .anims = sFoodSpriteAnims,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const union AnimCmd sAnim_CursorEmpty[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_CursorFilled[] =
{
    ANIMCMD_FRAME(4, 0),
    ANIMCMD_END,
};

static const union AnimCmd *const sCursorSpriteAnims[] =
{
    sAnim_CursorEmpty,
    sAnim_CursorFilled,
};

static const struct OamData sCursorSpriteOamData =
{
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 0,
    .bpp = ST_OAM_4BPP,
};

static const struct SpriteTemplate sCursorSpriteTemplate =
{
    .tileTag = FEED_CURSOR_TILE_TAG,
    .paletteTag = FEED_CURSOR_PAL_TAG,
    .oam = &sCursorSpriteOamData,
    .anims = sCursorSpriteAnims,
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

void OpenPokegotchiFeedMenu(MainCallback exitCallback)
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
    sMenuDataPtr->cursorSpriteId = SPRITE_NONE;
    sMenuDataPtr->selectedSlot = FEED_CURSOR_START_SLOT;
    for (i = 0; i < ARRAY_COUNT(sMenuDataPtr->foodSpriteIds); i++)
        sMenuDataPtr->foodSpriteIds[i] = SPRITE_NONE;

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
        Menu_LoadFoodSprites();
        Menu_CreateCursorSprite();
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
    Menu_DestroyCursorSprite();
    Menu_DestroyFoodSprites();

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
    u8 quantityText[4];
    u8 x;
    u32 i;

    FillWindowPixelBuffer(MAIN_WINDOW, PIXEL_FILL(0));

    if (TryGetFeedNickname(nickname))
    {
        x = GetStringCenterAlignXOffset(FONT_NORMAL, nickname, DISPLAY_WIDTH);
        AddTextPrinterParameterized3(MAIN_WINDOW,
                                     FONT_NORMAL,
                                     x,
                                     FEED_TEXT_NICKNAME_Y,
                                     sMenuWindowFontColors[FONT_BLACK],
                                     TEXT_SKIP_DRAW,
                                     nickname);
    }

    x = FEED_TEXT_MEAL_CENTER_X - GetStringWidth(FONT_NORMAL, sText_FeedMeal, 0) / 2;
    AddTextPrinterParameterized3(MAIN_WINDOW,
                                 FONT_NORMAL,
                                 x,
                                 FEED_TEXT_CATEGORY_Y,
                                 sMenuWindowFontColors[FONT_BLACK],
                                 TEXT_SKIP_DRAW,
                                 sText_FeedMeal);

    x = FEED_TEXT_SNACK_CENTER_X - GetStringWidth(FONT_NORMAL, sText_FeedSnack, 0) / 2;
    AddTextPrinterParameterized3(MAIN_WINDOW,
                                 FONT_NORMAL,
                                 x,
                                 FEED_TEXT_CATEGORY_Y,
                                 sMenuWindowFontColors[FONT_BLACK],
                                 TEXT_SKIP_DRAW,
                                 sText_FeedSnack);

    for (i = 0; i < ARRAY_COUNT(sVisualSlots); i++)
    {
        u8 count = Menu_GetFoodCountForVisualSlot(i);
        s16 textX;
        s16 textY;

        if (count == 0)
            continue;

        ConvertIntToDecimalStringN(quantityText, count, STR_CONV_MODE_LEFT_ALIGN, 3);
        textX = GetStringRightAlignXOffset(FONT_SMALL,
                                           quantityText,
                                           sFoodSlotCoords[sVisualSlots[i].category][sVisualSlots[i].slot][0] - FEED_QUANTITY_RIGHT_EDGE_OFFSET);
        textY = sFoodSlotCoords[sVisualSlots[i].category][sVisualSlots[i].slot][1] + FEED_QUANTITY_OFFSET_Y;
        AddTextPrinterParameterized3(MAIN_WINDOW,
                                     FONT_SMALL,
                                     textX,
                                     textY,
                                     sMenuWindowFontColors[FONT_BLACK],
                                     TEXT_SKIP_DRAW,
                                     quantityText);
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

static bool8 TryGetFeedNickname(u8 *dest)
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

static u8 Menu_GetFoodCount(u8 inventoryKey)
{
    const struct PokegotchiRuntimeState *runtime = PokegotchiSave_GetRuntime();

    switch (inventoryKey)
    {
    case FEED_FOOD_KEY_LEAF:
        return runtime->food.leaf;
    case FEED_FOOD_KEY_PECHA:
        return runtime->food.pecha;
    case FEED_FOOD_KEY_NONE:
    default:
        return 0;
    }
}

static const struct PokegotchiFoodEffect *Menu_GetFoodEffect(u8 inventoryKey)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sPokegotchiFoodEffects); i++)
    {
        if (sPokegotchiFoodEffects[i].inventoryKey == inventoryKey)
            return &sPokegotchiFoodEffects[i];
    }

    return NULL;
}

static const struct PokegotchiFeedFoodItem *Menu_GetFoodItemForVisualSlot(u8 visualSlot)
{
    u32 i;

    if (visualSlot >= ARRAY_COUNT(sVisualSlots))
        return NULL;

    for (i = 0; i < ARRAY_COUNT(gPokegotchiFeedFoodItems); i++)
    {
        const struct PokegotchiFeedFoodItem *foodItem = &gPokegotchiFeedFoodItems[i];

        if (foodItem->category == sVisualSlots[visualSlot].category
         && foodItem->slot == sVisualSlots[visualSlot].slot)
            return foodItem;
    }

    return NULL;
}

static u8 Menu_GetFoodCountForVisualSlot(u8 visualSlot)
{
    const struct PokegotchiFeedFoodItem *foodItem = Menu_GetFoodItemForVisualSlot(visualSlot);

    if (foodItem == NULL)
        return 0;

    return Menu_GetFoodCount(foodItem->inventoryKey);
}

static bool8 Menu_SelectedSlotHasFood(void)
{
    return Menu_GetFoodCountForVisualSlot(sMenuDataPtr->selectedSlot) != 0;
}

static u16 Menu_AddStatIncrease(u16 current, u8 increase)
{
    u32 total = current + increase;

    if (total > POKEGOTCHI_STAT_MAX)
        total = POKEGOTCHI_STAT_MAX;

    return total;
}

static bool8 Menu_ConsumeFoodByKey(u8 inventoryKey)
{
    struct PokegotchiRuntimeState *runtime = PokegotchiSave_GetRuntimeMutable();
    const struct PokegotchiFoodEffect *foodEffect = Menu_GetFoodEffect(inventoryKey);
    u8 *count = NULL;

    switch (inventoryKey)
    {
    case FEED_FOOD_KEY_LEAF:
        count = &runtime->food.leaf;
        break;
    case FEED_FOOD_KEY_PECHA:
        count = &runtime->food.pecha;
        break;
    case FEED_FOOD_KEY_NONE:
    default:
        return FALSE;
    }

    if (*count == 0)
        return FALSE;

    (*count)--;
    if (foodEffect != NULL)
    {
        runtime->stats.food = Menu_AddStatIncrease(runtime->stats.food, foodEffect->food);
        runtime->stats.fun = Menu_AddStatIncrease(runtime->stats.fun, foodEffect->fun);
    }

    PokegotchiSave_Commit();
    return TRUE;
}

static bool8 Menu_LoadFoodSpriteSheet(const struct PokegotchiFeedFoodItem *foodItem)
{
    struct SpriteSheet spriteSheet;

    if (foodItem->spriteTiles == NULL || GetSpriteTileStartByTag(foodItem->tileTag) != 0xFFFF)
        return TRUE;

    spriteSheet.data = foodItem->spriteTiles;
    spriteSheet.size = FEED_FOOD_SPRITESHEET_SIZE;
    spriteSheet.tag = foodItem->tileTag;

    LoadSpriteSheet(&spriteSheet);
    return GetSpriteTileStartByTag(foodItem->tileTag) != 0xFFFF;
}

static bool8 Menu_LoadCursorSpriteSheet(void)
{
    struct SpriteSheet spriteSheet;

    if (GetSpriteTileStartByTag(FEED_CURSOR_TILE_TAG) != 0xFFFF)
        return TRUE;

    spriteSheet.data = sText_FeedCursorGfx;
    spriteSheet.size = FEED_CURSOR_SPRITESHEET_SIZE;
    spriteSheet.tag = FEED_CURSOR_TILE_TAG;

    LoadSpriteSheet(&spriteSheet);
    return GetSpriteTileStartByTag(FEED_CURSOR_TILE_TAG) != 0xFFFF;
}

static bool8 Menu_LoadFoodSpritePalette(const struct PokegotchiFeedFoodItem *foodItem)
{
    struct SpritePalette spritePalette;

    if (foodItem->palette == NULL || IndexOfSpritePaletteTag(foodItem->paletteTag) != 0xFF)
        return TRUE;

    spritePalette.data = foodItem->palette;
    spritePalette.tag = foodItem->paletteTag;

    return LoadSpritePalette(&spritePalette) != 0xFF;
}

static bool8 Menu_LoadCursorSpritePalette(void)
{
    struct SpritePalette spritePalette;

    if (IndexOfSpritePaletteTag(FEED_CURSOR_PAL_TAG) != 0xFF)
        return TRUE;

    spritePalette.data = sText_FeedCursorPal;
    spritePalette.tag = FEED_CURSOR_PAL_TAG;

    return LoadSpritePalette(&spritePalette) != 0xFF;
}

static void Menu_LoadFoodSprites(void)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(gPokegotchiFeedFoodItems); i++)
    {
        const struct PokegotchiFeedFoodItem *foodItem = &gPokegotchiFeedFoodItems[i];
        struct SpriteTemplate spriteTemplate;
        u8 spriteId;

        if (foodItem->spriteTiles == NULL || Menu_GetFoodCount(foodItem->inventoryKey) == 0)
            continue;

        if (!Menu_LoadFoodSpriteSheet(foodItem) || !Menu_LoadFoodSpritePalette(foodItem))
            continue;

        spriteTemplate = sFoodSpriteTemplate;
        spriteTemplate.tileTag = foodItem->tileTag;
        spriteTemplate.paletteTag = foodItem->paletteTag;

        spriteId = CreateSprite(&spriteTemplate,
                                sFoodSlotCoords[foodItem->category][foodItem->slot][0],
                                sFoodSlotCoords[foodItem->category][foodItem->slot][1],
                                0);
        if (spriteId == MAX_SPRITES)
            continue;

        sMenuDataPtr->foodSpriteIds[i] = spriteId;
    }
}

static void Menu_CreateCursorSprite(void)
{
    s16 x;
    s16 y;
    u8 spriteId;

    if (!Menu_LoadCursorSpriteSheet() || !Menu_LoadCursorSpritePalette())
        return;

    x = sFoodSlotCoords[sVisualSlots[sMenuDataPtr->selectedSlot].category][sVisualSlots[sMenuDataPtr->selectedSlot].slot][0];
    y = sFoodSlotCoords[sVisualSlots[sMenuDataPtr->selectedSlot].category][sVisualSlots[sMenuDataPtr->selectedSlot].slot][1];
    spriteId = CreateSpriteAtEnd(&sCursorSpriteTemplate, x + FEED_CURSOR_OFFSET_X, y + FEED_CURSOR_OFFSET_Y, 0);
    if (spriteId == MAX_SPRITES)
        return;

    sMenuDataPtr->cursorSpriteId = spriteId;
    Menu_UpdateCursorSprite();
}

static void Menu_UpdateCursorSprite(void)
{
    struct Sprite *sprite;

    if (sMenuDataPtr == NULL || sMenuDataPtr->cursorSpriteId == SPRITE_NONE)
        return;

    sprite = &gSprites[sMenuDataPtr->cursorSpriteId];
    sprite->x = sFoodSlotCoords[sVisualSlots[sMenuDataPtr->selectedSlot].category][sVisualSlots[sMenuDataPtr->selectedSlot].slot][0] + FEED_CURSOR_OFFSET_X;
    sprite->y = sFoodSlotCoords[sVisualSlots[sMenuDataPtr->selectedSlot].category][sVisualSlots[sMenuDataPtr->selectedSlot].slot][1] + FEED_CURSOR_OFFSET_Y;
    StartSpriteAnim(sprite, Menu_SelectedSlotHasFood());
}

static bool8 Menu_MoveFeedCursor(s8 dx, s8 dy)
{
    s8 row;
    s8 column;
    s8 newRow;
    s8 newColumn;
    u8 newSlot;

    row = sMenuDataPtr->selectedSlot / FEED_CURSOR_COLUMNS;
    column = sMenuDataPtr->selectedSlot % FEED_CURSOR_COLUMNS;
    newRow = row + dy;
    newColumn = column + dx;

    if (newRow < 0 || newRow >= FEED_CURSOR_ROWS || newColumn < 0 || newColumn >= FEED_CURSOR_COLUMNS)
        return FALSE;

    newSlot = newRow * FEED_CURSOR_COLUMNS + newColumn;
    if (newSlot == sMenuDataPtr->selectedSlot)
        return FALSE;

    sMenuDataPtr->selectedSlot = newSlot;
    Menu_UpdateCursorSprite();
    return TRUE;
}

static void Menu_DestroyFoodSprites(void)
{
    u32 i;

    if (sMenuDataPtr != NULL)
    {
        for (i = 0; i < ARRAY_COUNT(sMenuDataPtr->foodSpriteIds); i++)
        {
            u8 spriteId = sMenuDataPtr->foodSpriteIds[i];

            if (spriteId != SPRITE_NONE && spriteId < MAX_SPRITES && gSprites[spriteId].inUse)
                DestroySprite(&gSprites[spriteId]);

            sMenuDataPtr->foodSpriteIds[i] = SPRITE_NONE;
        }
    }

    for (i = 0; i < ARRAY_COUNT(gPokegotchiFeedFoodItems); i++)
    {
        const struct PokegotchiFeedFoodItem *foodItem = &gPokegotchiFeedFoodItems[i];

        if (foodItem->spriteTiles == NULL)
            continue;

        if (GetSpriteTileStartByTag(foodItem->tileTag) != 0xFFFF)
            FreeSpriteTilesByTag(foodItem->tileTag);

        if (IndexOfSpritePaletteTag(foodItem->paletteTag) != 0xFF)
            FreeSpritePaletteByTag(foodItem->paletteTag);
    }
}

static void Menu_DestroyCursorSprite(void)
{
    if (sMenuDataPtr != NULL
     && sMenuDataPtr->cursorSpriteId != SPRITE_NONE
     && sMenuDataPtr->cursorSpriteId < MAX_SPRITES
     && gSprites[sMenuDataPtr->cursorSpriteId].inUse)
    {
        DestroySprite(&gSprites[sMenuDataPtr->cursorSpriteId]);
        sMenuDataPtr->cursorSpriteId = SPRITE_NONE;
    }

    if (GetSpriteTileStartByTag(FEED_CURSOR_TILE_TAG) != 0xFFFF)
        FreeSpriteTilesByTag(FEED_CURSOR_TILE_TAG);

    if (IndexOfSpritePaletteTag(FEED_CURSOR_PAL_TAG) != 0xFF)
        FreeSpritePaletteByTag(FEED_CURSOR_PAL_TAG);
}

static void Task_MenuWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_MenuMain;
}

static void Task_MenuMain(u8 taskId)
{
    if (JOY_NEW(A_BUTTON))
    {
        const struct PokegotchiFeedFoodItem *foodItem = Menu_GetFoodItemForVisualSlot(sMenuDataPtr->selectedSlot);

        if (foodItem != NULL
         && Menu_GetFoodCount(foodItem->inventoryKey) > 0
         && Menu_ConsumeFoodByKey(foodItem->inventoryKey))
        {
            sPendingConsumedFoodKey = foodItem->inventoryKey;
            sFeedMenuExitCallback = sMenuDataPtr->savedCallback;
            sMenuDataPtr->savedCallback = CB2_OpenPokegotchiHouseEatingSceneFromFeed;
            PlaySE(SE_SELECT);
            Menu_FadeAndBail();
            DestroyTask(taskId);
            return;
        }

        if (!IsSEPlaying())
            PlaySE(SE_FAILURE);
    }

    if (JOY_NEW(DPAD_LEFT))
    {
        if (Menu_MoveFeedCursor(-1, 0))
            PlaySE(SE_SELECT);
    }
    else if (JOY_NEW(DPAD_RIGHT))
    {
        if (Menu_MoveFeedCursor(1, 0))
            PlaySE(SE_SELECT);
    }
    else if (JOY_NEW(DPAD_UP))
    {
        if (Menu_MoveFeedCursor(0, -1))
            PlaySE(SE_SELECT);
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        if (Menu_MoveFeedCursor(0, 1))
            PlaySE(SE_SELECT);
    }

    if (JOY_NEW(B_BUTTON) && !gPaletteFade.active)
    {
        PlaySE(SE_SELECT);
        Menu_FadeAndBail();
        DestroyTask(taskId);
    }
}

static void CB2_OpenPokegotchiHouseEatingSceneFromFeed(void)
{
    OpenPokegotchiHouseEatingScene(sPendingConsumedFoodKey, CB2_ReturnToConsumedFoodFeedMenu);
}

static void CB2_ReturnToConsumedFoodFeedMenu(void)
{
    OpenPokegotchiFeedMenu(sFeedMenuExitCallback);
}
