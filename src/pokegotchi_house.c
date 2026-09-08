#include "global.h"
#include "pokegotchi_house.h"
#include "pokegotchi.h"
#include "pokegotchi_feed.h"
#include "pokegotchi_intro.h"
#include "pokegotchi_status.h"
#include "pokegotchi_waiter_minigame.h"
#include "strings.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
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
#include "random.h"
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
#include "constants/songs.h"
#include "m4a.h"

/*
 * 
 */
 
//==========DEFINES==========//
#define MENU_ICONS 4
#define HOUSE_FLOOR_ANCHORS 12
#define HOUSE_INITIAL_PET_ANCHOR 2
#define HOUSE_SULKING_PET_ANCHOR 2
#define HOUSE_WANDER_MIN_FRAMES (4 * 60)
#define HOUSE_WANDER_MAX_FRAMES (6 * 60)
#define HOUSE_PET_CENTER_X 120
#define HOUSE_PET_CENTER_Y 88
#define HOUSE_BED_SLEEP_X 48
#define HOUSE_BED_SLEEP_Y 96
#define HOUSE_EATING_FOOD_X 99
#define HOUSE_EATING_FOOD_Y 99
#define HOUSE_EATING_FOOD_FRAME_COUNT 3
#define HOUSE_POST_EAT_PHASE_FRAMES 48
#define HOUSE_REACTION_CYCLE_FRAMES (2 * 32)
#define HOUSE_REACTION_HOLD_FRAMES 60
#define HOUSE_WAKE_REACTION_FRAMES 24
#define HOUSE_EMOTICON_X_OFFSET 16
#define HOUSE_EMOTICON_Y_OFFSET 16

enum HouseEntryMode
{
    HOUSE_ENTRY_NORMAL,
    HOUSE_ENTRY_EATING_SCENE,
};

enum HouseEatingScenePhase
{
    HOUSE_EATING_SCENE_PHASE_EATING,
    HOUSE_EATING_SCENE_PHASE_POST_EAT,
};

enum HousePetActivity
{
    HOUSE_PET_ACTIVITY_IDLE,
    HOUSE_PET_ACTIVITY_BUSY,
    HOUSE_PET_ACTIVITY_SULKING,
};

enum HouseReactionPhase
{
    HOUSE_REACTION_PHASE_ACTIVE,
    HOUSE_REACTION_PHASE_HOLD,
    HOUSE_REACTION_PHASE_WAKE,
    HOUSE_REACTION_PHASE_EMOTICON_ONLY,
};

struct HouseReaction
{
    u8 emotion;
    u8 loopCount;
    u8 emoticon;
};

struct HouseFurniture
{
    const u16 *tilemap;
    u16 flag;
    u8 x;
    u8 y;
    u8 width;
    u8 height;
};

struct HousePoopLayout
{
    u16 anchorIds;
    u8 assignedMask;
    u8 flipMask;
};
STATIC_ASSERT(sizeof(struct HousePoopLayout) == 4, HousePoopLayoutMustUseFourBytes);

struct MenuResources
{
    MainCallback savedCallback; // determines callback to run when we exit. e.g. where do we want to go after closing the menu
    u8 gfxLoadState;
    u8 menuIconIds[MENU_ICONS];
    u8 controlHintSpriteId;
    u8 petSpriteId;
    u8 petEmotion;
    u8 petActivity;
    u8 emoticonSpriteId;
    u8 foodSpriteId;
    u8 poopSpriteIds[POKEGOTCHI_MAX_POOPS];
    u8 syncTaskId;
    u8 wanderTaskId;
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
static EWRAM_DATA MainCallback sHouseEatingSceneReturnCallback = NULL;
static EWRAM_DATA u8 sHouseWaiterMinigameDifficulty = POKEGOTCHI_WAITER_MINIGAME_EASY;
static EWRAM_DATA u8 sHouseEntryMode = HOUSE_ENTRY_NORMAL;
static EWRAM_DATA u8 sHouseEatingSceneFoodKey = FEED_FOOD_KEY_NONE;
static EWRAM_DATA enum PokegotchiDailyRewardTier sHouseEatingSceneRewardTier = POKEGOTCHI_DAILY_REWARD_NONE;
static EWRAM_DATA struct HousePoopLayout sHousePoopLayout = {0};

//==========STATIC=DEFINES==========//
static void Menu_Init(MainCallback callback);
static void Menu_RunSetup(void);
static void Menu_MainCB(void);
static void Menu_VBlankCB(void);
static void Menu_ResetGpuRegsAndBgs(void);
static bool8 Menu_DoGfxSetup(void);
static bool8 Menu_InitBgs(void);
static void Menu_FadeAndBail(void);
static bool8 Menu_LoadGraphics(void);
static void Menu_ApplyUnlockedFurniture(void);
static void Menu_InitWindows(void);
static void Menu_LoadTopIcons(void);
static void Menu_LoadControlHint(void);
static void Menu_LoadPetSprite(void);
static bool8 Menu_SetPetEmotion(u8 emotion);
static void Menu_UpdatePetSleepState(void);
static void Menu_UpdatePetConditionState(void);
static void Menu_EnterSulkingState(void);
static struct HouseReaction Menu_GetReaction(enum PokegotchiInteractionReaction reaction);
static void Menu_StartPetInteraction(u8 taskId);
static void Menu_FinishPetInteraction(u8 taskId);
static bool8 Menu_CreateEmoticon(u8 emoticon, bool8 wakeAnimation);
static void Menu_DestroyEmoticon(void);
static bool8 Menu_CanPetWander(void);
static void Menu_GetPetSpawnPosition(s16 *x, s16 *y);
static bool8 Menu_MovePetToRandomAnchor(bool8 requireDifferentAnchor);
static void Menu_RefreshPoopSprites(void);
static bool8 Menu_LoadPoopSpriteGfx(void);
static void Menu_DestroyPoopSprites(void);
static void Menu_FreePoopSpriteGfx(void);
static void Menu_ResetPoopLayout(void);
static void Menu_LoadSceneFoodSprite(void);
static const struct PokegotchiFeedFoodItem *Menu_GetFoodItemByKey(u8 inventoryKey);
static bool8 Menu_LoadFoodSpriteSheet(const struct PokegotchiFeedFoodItem *foodItem);
static bool8 Menu_LoadFoodSpritePalette(const struct PokegotchiFeedFoodItem *foodItem);
static void Menu_DestroyFoodSprite(void);
static void Menu_SetFoodBiteFrame(u8 frame);
static void Menu_SetSelectedTopIcon(u8 selectedIcon);
static struct HouseReaction Menu_GetPostEatReaction(enum PokegotchiDailyRewardTier rewardTier);
static void Task_MenuWaitFadeIn(u8 taskId);
static void Task_MenuMain(u8 taskId);
static void Task_MenuPetInteraction(u8 taskId);
static void Task_MenuEatingScene(u8 taskId);
static void Task_MenuSyncPokegotchi(u8 taskId);
static void Task_MenuWanderPet(u8 taskId);
static void Task_ReturnToPokegotchiHouse(u8 taskId);
static void CB2_ReturnToFieldAfterFailedHouseOpen(void);
static void CB2_ReturnToPokegotchiHouseMenu(void);
static void CB2_OpenPokegotchiFeedMenuFromHouse(void);
static void CB2_OpenPokegotchiStatusMenuFromHouse(void);
static UNUSED void CB2_OpenPokegotchiWaiterMinigameFromHouse(void);
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
static const u16 sMenuTreeckoPosterTilemap[] = INCBIN_U16("graphics/pokegotchi_house_ui/room_treecko.bin");
static const u16 sMenuTorchicPosterTilemap[] = INCBIN_U16("graphics/pokegotchi_house_ui/room_torchic.bin");
static const u16 sMenuMudkipPosterTilemap[] = INCBIN_U16("graphics/pokegotchi_house_ui/room_mudskip.bin");
static const u16 sMenuBedTilemap[] = INCBIN_U16("graphics/pokegotchi_house_ui/room_bed.bin");
static const u16 sMenuCarpetTilemap[] = INCBIN_U16("graphics/pokegotchi_house_ui/room_carpet.bin");
static const u16 sMenuDittoTilemap[] = INCBIN_U16("graphics/pokegotchi_house_ui/room_ditto.bin");

static const struct HouseFurniture sHouseFurniture[] =
{
    {sMenuTreeckoPosterTilemap, POKEGOTCHI_FLAG_FRNTR_POSTER_TREECKO,  9,  5,  3, 4},
    {sMenuTorchicPosterTilemap, POKEGOTCHI_FLAG_FRNTR_POSTER_TORCHIC, 12,  5,  2, 4},
    {sMenuMudkipPosterTilemap,  POKEGOTCHI_FLAG_FRNTR_POSTER_MUDKIP,  14,  5,  3, 4},
    {sMenuBedTilemap,           POKEGOTCHI_FLAG_FRNTR_BED,             4,  9,  4, 7},
    {sMenuCarpetTilemap,        POKEGOTCHI_FLAG_FRNTR_RUG,            10, 12, 10, 6},
    {sMenuDittoTilemap,         POKEGOTCHI_FLAG_FRNTR_DITTO,          22, 10,  2, 2},
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
#define POOP_SPRITE_TAG 5526
#define POOP_SPRITE_PAL_TAG 5527
#define CONTROL_HINT_SPRITE_TAG 5528

#define SPRITE_SELECTED 0
#define SPRITE_UNSELECTED 1

#define STATUS_ICON 0
#define FOOD_ICON 1
#define CLEAN_ICON 2
#define TOWN_ICON 3
#define HOUSE_SYNC_INTERVAL_FRAMES (3 * 60 * 60) // Update stats every 3 minutes
#define HOUSE_SLEEP_CHECK_INTERVAL_FRAMES 60

static const u8 sMenuIconStatusSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_house_ui/menu_status.png", ".4bpp");
static const u8 sMenuIconFoodSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_house_ui/menu_food.png", ".4bpp");
static const u8 sMenuIconCleanSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_house_ui/menu_clean.png", ".4bpp");
static const u8 sMenuIconTownSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_house_ui/menu_town.png", ".4bpp");
static const u8 sControlHintSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_house_ui/lr.png", ".4bpp");
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

static const struct SpriteSheet sControlHintSpriteSheet =
{
    .data = sControlHintSpriteGfx,
    .size = sizeof(sControlHintSpriteGfx),
    .tag = CONTROL_HINT_SPRITE_TAG,
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

static const struct SpriteTemplate sControlHintSpriteTemplate =
{
    .tileTag = CONTROL_HINT_SPRITE_TAG,
    .paletteTag = ICON_SPRITES_PAL_TAG,
    .anims = gDummySpriteAnimTable,
    .oam = &sMenuIconsSpriteOamData,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
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

static const union AnimCmd sAnim_FoodFrame0[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_FoodFrame1[] =
{
    ANIMCMD_FRAME(4, 0),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_FoodFrame2[] =
{
    ANIMCMD_FRAME(8, 0),
    ANIMCMD_END,
};

static const union AnimCmd *const sFoodSpriteAnims[] =
{
    sAnim_FoodFrame0,
    sAnim_FoodFrame1,
    sAnim_FoodFrame2,
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

static const u8 sPoopSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_house_ui/poop.png", ".4bpp");
static const u16 sPoopSpritePaletteData[] = INCGFX_U16("graphics/pokegotchi_house_ui/poop.png", ".gbapal");

static const struct SpriteSheet sPoopSpriteSheet =
{
    .data = sPoopSpriteGfx,
    .size = sizeof(sPoopSpriteGfx),
    .tag = POOP_SPRITE_TAG,
};

static const struct SpritePalette sPoopSpritePalette =
{
    .data = sPoopSpritePaletteData,
    .tag = POOP_SPRITE_PAL_TAG,
};

static const union AnimCmd sAnim_PoopVariant0[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_PoopVariant1[] =
{
    ANIMCMD_FRAME(4, 0),
    ANIMCMD_END,
};

static const union AnimCmd *const sPoopSpriteAnims[] =
{
    sAnim_PoopVariant0,
    sAnim_PoopVariant1,
};

static const struct OamData sPoopSpriteOamData =
{
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 0,
    .bpp = ST_OAM_4BPP,
};

static const struct SpriteTemplate sPoopSpriteTemplate =
{
    .tileTag = POOP_SPRITE_TAG,
    .paletteTag = POOP_SPRITE_PAL_TAG,
    .oam = &sPoopSpriteOamData,
    .anims = sPoopSpriteAnims,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const s16 sHouseFloorAnchorCoords[HOUSE_FLOOR_ANCHORS][2] =
{
    {80, 90},
    {151, 86},
    {184, 94},
    {216, 98},
    {83, 118},
    {116, 112},
    {150, 117},
    {216, 126},
    {82, 142},
    {114, 138},
    {146, 141},
    {178, 137},
};

static const u8 sHouseEatingFoodStageDurations[HOUSE_EATING_FOOD_FRAME_COUNT] =
{
    28,
    30,
    60,
};

//==========FUNCTIONS==========//
void OpenPokegotchiHouseMenu(MainCallback callback)
{
    sHouseEntryMode = HOUSE_ENTRY_NORMAL;
    sHouseEatingSceneFoodKey = FEED_FOOD_KEY_NONE;
    sHouseEatingSceneRewardTier = POKEGOTCHI_DAILY_REWARD_NONE;
    sHouseEatingSceneReturnCallback = NULL;
    Menu_Init(callback);
}

void OpenPokegotchiHouseEatingScene(u8 foodKey, enum PokegotchiDailyRewardTier rewardTier, MainCallback returnCallback)
{
    sHouseEntryMode = HOUSE_ENTRY_EATING_SCENE;
    sHouseEatingSceneFoodKey = foodKey;
    sHouseEatingSceneRewardTier = rewardTier;
    sHouseEatingSceneReturnCallback = returnCallback;
    Menu_Init(sHouseEatingSceneReturnCallback);
}

// UI loader template
void MainCB2_InitPokegotchiHouseMenu(void)
{
    OpenPokegotchiHouseMenu(CB2_InitPokegotchiBootup);
}

void ReturnToPokegotchiHouse(struct ScriptContext *ctx)
{
    if (ctx != NULL)
    {
        FlagClear(FLAG_SAFE_FOLLOWER_MOVEMENT);
        StopScript(ctx);
        ScriptContext_Stop();
        ctx->waitAfterCallNative = TRUE;
    }

    FreezeObjectEvents();
    PlayerFreeze();
    StopPlayerAvatar();
    LockPlayerFieldControls();
    FadeScreen(FADE_TO_BLACK, 0);
    CreateTask(Task_ReturnToPokegotchiHouse, 0);
}

static void Task_ReturnToPokegotchiHouse(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        PlayRainStoppingSoundEffect();
        CleanupOverworldWindowsAndTilemaps();
        DestroyTask(taskId);
        OpenPokegotchiHouseMenu(CB2_ReturnToFieldAfterFailedHouseOpen);
    }
}

static void CB2_ReturnToFieldAfterFailedHouseOpen(void)
{
    ScriptContext_Init();
    CB2_ReturnToFieldContinueScriptPlayMapMusic();
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

    if (sHouseEntryMode == HOUSE_ENTRY_NORMAL)
        Pokegotchi_SyncAndSave();

    // initialize stuff
    sMenuDataPtr->gfxLoadState = 0;
    sMenuDataPtr->savedCallback = callback;
    for (i = 0; i < MENU_ICONS; i++)
        sMenuDataPtr->menuIconIds[i] = MAX_SPRITES;
    sMenuDataPtr->controlHintSpriteId = SPRITE_NONE;
    sMenuDataPtr->petSpriteId = SPRITE_NONE;
    sMenuDataPtr->petEmotion = POKEGOTCHI_EMOTION_COUNT;
    sMenuDataPtr->petActivity = HOUSE_PET_ACTIVITY_IDLE;
    sMenuDataPtr->emoticonSpriteId = SPRITE_NONE;
    sMenuDataPtr->foodSpriteId = SPRITE_NONE;
    for (i = 0; i < POKEGOTCHI_MAX_POOPS; i++)
        sMenuDataPtr->poopSpriteIds[i] = SPRITE_NONE;
    sMenuDataPtr->syncTaskId = TASK_NONE;
    sMenuDataPtr->wanderTaskId = TASK_NONE;

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
        m4aSongNumStartOrChange(MUS_FORTREE);
        Menu_LoadTopIcons();
        Menu_LoadControlHint();
        Menu_LoadPetSprite();
        Menu_RefreshPoopSprites();
        if (sHouseEntryMode == HOUSE_ENTRY_EATING_SCENE)
            Menu_LoadSceneFoodSprite();
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

        if (sMenuDataPtr->controlHintSpriteId != SPRITE_NONE)
        {
            DestroySprite(&gSprites[sMenuDataPtr->controlHintSpriteId]);
            sMenuDataPtr->controlHintSpriteId = SPRITE_NONE;
        }

        if (sMenuDataPtr->petSpriteId != SPRITE_NONE)
        {
            DestroyPokegotchiSprite(sMenuDataPtr->petSpriteId);
            sMenuDataPtr->petSpriteId = SPRITE_NONE;
        }

        Menu_DestroyEmoticon();
        Menu_DestroyFoodSprite();
        Menu_DestroyPoopSprites();

        if (sMenuDataPtr->syncTaskId != TASK_NONE && FuncIsActiveTask(Task_MenuSyncPokegotchi))
        {
            DestroyTask(sMenuDataPtr->syncTaskId);
            sMenuDataPtr->syncTaskId = TASK_NONE;
        }

        if (sMenuDataPtr->wanderTaskId != TASK_NONE && FuncIsActiveTask(Task_MenuWanderPet))
        {
            DestroyTask(sMenuDataPtr->wanderTaskId);
            sMenuDataPtr->wanderTaskId = TASK_NONE;
        }
    }

    FreeSpriteTilesByTag(ICON_1_SPRITE_TAG);
    FreeSpriteTilesByTag(ICON_2_SPRITE_TAG);
    FreeSpriteTilesByTag(ICON_3_SPRITE_TAG);
    FreeSpriteTilesByTag(ICON_4_SPRITE_TAG);
    FreeSpriteTilesByTag(CONTROL_HINT_SPRITE_TAG);
    FreeSpritePaletteByTag(ICON_SPRITES_PAL_TAG);
    Menu_FreePoopSpriteGfx();
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
            Menu_ApplyUnlockedFurniture();
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

static void Menu_ApplyUnlockedFurniture(void)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sHouseFurniture); i++)
    {
        const struct HouseFurniture *furniture = &sHouseFurniture[i];

        if (FlagGet(furniture->flag))
        {
            CopyToBgTilemapBufferRect_ChangePalette(1,
                                                    furniture->tilemap,
                                                    furniture->x,
                                                    furniture->y,
                                                    furniture->width,
                                                    furniture->height,
                                                    0);
        }
    }
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

    Menu_SetSelectedTopIcon(sHouseEntryMode == HOUSE_ENTRY_EATING_SCENE ? FOOD_ICON : STATUS_ICON);
}

static void Menu_LoadControlHint(void)
{
    u8 spriteId;

    if (sHouseEntryMode != HOUSE_ENTRY_NORMAL
     || IndexOfSpritePaletteTag(ICON_SPRITES_PAL_TAG) == 0xFF)
        return;

    LoadSpriteSheet(&sControlHintSpriteSheet);
    if (GetSpriteTileStartByTag(CONTROL_HINT_SPRITE_TAG) == TAG_NONE)
        return;

    spriteId = CreateSpriteUnchecked(&sControlHintSpriteTemplate, 16, 144, 0);
    if (spriteId == MAX_SPRITES)
    {
        FreeSpriteTilesByTag(CONTROL_HINT_SPRITE_TAG);
        return;
    }

    sMenuDataPtr->controlHintSpriteId = spriteId;
}

static void Menu_LoadPetSprite(void)
{
    u8 emotion = POKEGOTCHI_EMOTION_IDLE;
    bool8 isSulking = Pokegotchi_GetInteractionReaction(Pokegotchi_GetStats()) == POKEGOTCHI_REACTION_SULKING;
    bool8 isSleeping = Pokegotchi_IsSleeping();

    if (sHouseEntryMode == HOUSE_ENTRY_EATING_SCENE
     && HasPokegotchiSprite(Pokegotchi_GetPrimarySpecies(), POKEGOTCHI_EMOTION_EATING))
        emotion = POKEGOTCHI_EMOTION_EATING;
    else if (isSleeping
          && HasPokegotchiSprite(Pokegotchi_GetPrimarySpecies(), POKEGOTCHI_EMOTION_SLEEPING))
        emotion = POKEGOTCHI_EMOTION_SLEEPING;

    if (!Menu_SetPetEmotion(emotion))
        Menu_SetPetEmotion(POKEGOTCHI_EMOTION_IDLE);

    if (sHouseEntryMode == HOUSE_ENTRY_NORMAL && isSulking && !isSleeping)
        Menu_EnterSulkingState();
}

static void Menu_UpdatePetSleepState(void)
{
    bool8 isSleeping;

    if (sHouseEntryMode != HOUSE_ENTRY_NORMAL
     || sMenuDataPtr == NULL
     || (sMenuDataPtr->petActivity == HOUSE_PET_ACTIVITY_BUSY
      && sMenuDataPtr->petEmotion != POKEGOTCHI_EMOTION_SLEEPING))
        return;

    isSleeping = Pokegotchi_IsSleeping();
    if (isSleeping && sMenuDataPtr->petEmotion != POKEGOTCHI_EMOTION_SLEEPING)
        Menu_SetPetEmotion(POKEGOTCHI_EMOTION_SLEEPING);
    else if (!isSleeping && sMenuDataPtr->petEmotion == POKEGOTCHI_EMOTION_SLEEPING)
        Menu_SetPetEmotion(POKEGOTCHI_EMOTION_IDLE);
}

static void Menu_UpdatePetConditionState(void)
{
    bool8 shouldSulk;

    if (sHouseEntryMode != HOUSE_ENTRY_NORMAL
     || sMenuDataPtr == NULL
     || (sMenuDataPtr->petActivity == HOUSE_PET_ACTIVITY_BUSY
      && sMenuDataPtr->petEmotion != POKEGOTCHI_EMOTION_SLEEPING))
        return;

    if (Pokegotchi_IsSleeping())
    {
        if (sMenuDataPtr->petEmotion != POKEGOTCHI_EMOTION_SLEEPING
         && !Menu_SetPetEmotion(POKEGOTCHI_EMOTION_SLEEPING))
            Menu_SetPetEmotion(POKEGOTCHI_EMOTION_IDLE);
        return;
    }

    shouldSulk = Pokegotchi_GetInteractionReaction(Pokegotchi_GetStats()) == POKEGOTCHI_REACTION_SULKING;
    if (shouldSulk)
    {
        if (sMenuDataPtr->petActivity != HOUSE_PET_ACTIVITY_SULKING)
            Menu_EnterSulkingState();
        return;
    }

    if (sMenuDataPtr->petActivity == HOUSE_PET_ACTIVITY_SULKING)
        Menu_SetPetEmotion(POKEGOTCHI_EMOTION_IDLE);
}

static void Menu_EnterSulkingState(void)
{
    struct Sprite *sprite;

    if (!Menu_SetPetEmotion(POKEGOTCHI_EMOTION_SULKING))
        return;

    sprite = &gSprites[sMenuDataPtr->petSpriteId];
    sprite->x = sHouseFloorAnchorCoords[HOUSE_SULKING_PET_ANCHOR][0];
    sprite->y = sHouseFloorAnchorCoords[HOUSE_SULKING_PET_ANCHOR][1];
    sMenuDataPtr->petActivity = HOUSE_PET_ACTIVITY_SULKING;
    Menu_RefreshPoopSprites();
}

static struct HouseReaction Menu_GetReaction(enum PokegotchiInteractionReaction reaction)
{
    static const struct HouseReaction sReactions[] =
    {
        [POKEGOTCHI_REACTION_HAPPY_ONCE] = {POKEGOTCHI_EMOTION_HAPPY, 1, POKEGOTCHI_EMOTICON_NONE},
        [POKEGOTCHI_REACTION_HAPPY_TWICE] = {POKEGOTCHI_EMOTION_HAPPY, 2, POKEGOTCHI_EMOTICON_NONE},
        [POKEGOTCHI_REACTION_HAPPY_TWICE_SUN] = {POKEGOTCHI_EMOTION_HAPPY, 2, POKEGOTCHI_EMOTICON_SUN},
        [POKEGOTCHI_REACTION_ANGRY_ONCE] = {POKEGOTCHI_EMOTION_ANGRY, 1, POKEGOTCHI_EMOTICON_NONE},
        [POKEGOTCHI_REACTION_ANGRY_TWICE] = {POKEGOTCHI_EMOTION_ANGRY, 2, POKEGOTCHI_EMOTICON_ANGER},
        [POKEGOTCHI_REACTION_SAD_ONCE] = {POKEGOTCHI_EMOTION_SAD, 1, POKEGOTCHI_EMOTICON_NONE},
        [POKEGOTCHI_REACTION_SAD_TWICE] = {POKEGOTCHI_EMOTION_SAD, 2, POKEGOTCHI_EMOTICON_NONE},
    };

    if (reaction == POKEGOTCHI_REACTION_SULKING || reaction >= ARRAY_COUNT(sReactions))
        return (struct HouseReaction){POKEGOTCHI_EMOTION_IDLE, 0, POKEGOTCHI_EMOTICON_NONE};
    return sReactions[reaction];
}

static bool8 Menu_CreateEmoticon(u8 emoticon, bool8 wakeAnimation)
{
    struct Sprite *petSprite;
    s16 x;
    s16 y;
    u8 spriteId;

    if (sMenuDataPtr == NULL
     || sMenuDataPtr->petSpriteId == SPRITE_NONE
     || sMenuDataPtr->petSpriteId >= MAX_SPRITES
     || !gSprites[sMenuDataPtr->petSpriteId].inUse)
        return FALSE;

    if (emoticon <= POKEGOTCHI_EMOTICON_NONE || emoticon >= POKEGOTCHI_EMOTICON_COUNT)
        return FALSE;

    Menu_DestroyEmoticon();
    petSprite = &gSprites[sMenuDataPtr->petSpriteId];
    x = petSprite->x + (petSprite->x > DISPLAY_WIDTH / 2 ? -HOUSE_EMOTICON_X_OFFSET : HOUSE_EMOTICON_X_OFFSET);
    y = petSprite->y - HOUSE_EMOTICON_Y_OFFSET;
    spriteId = CreatePokegotchiEmoticon(emoticon, x, y, 0, wakeAnimation);
    if (spriteId == SPRITE_NONE)
        return FALSE;

    sMenuDataPtr->emoticonSpriteId = spriteId;
    return TRUE;
}

static void Menu_DestroyEmoticon(void)
{
    if (sMenuDataPtr != NULL
     && sMenuDataPtr->emoticonSpriteId != SPRITE_NONE
     && sMenuDataPtr->emoticonSpriteId < MAX_SPRITES)
        DestroyPokegotchiEmoticon(sMenuDataPtr->emoticonSpriteId);

    if (sMenuDataPtr != NULL)
        sMenuDataPtr->emoticonSpriteId = SPRITE_NONE;
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

static bool8 Menu_SetPetEmotion(u8 emotion)
{
    enum Species species = Pokegotchi_GetPrimarySpecies();
    u8 spriteId;
    s16 x;
    s16 y;

    if (species == SPECIES_NONE || !HasPokegotchiSprite(species, emotion))
        return FALSE;

    if (sMenuDataPtr->petSpriteId != SPRITE_NONE
     && sMenuDataPtr->petSpriteId < MAX_SPRITES
     && gSprites[sMenuDataPtr->petSpriteId].inUse)
    {
        x = gSprites[sMenuDataPtr->petSpriteId].x;
        y = gSprites[sMenuDataPtr->petSpriteId].y;
        DestroyPokegotchiSprite(sMenuDataPtr->petSpriteId);
        sMenuDataPtr->petSpriteId = SPRITE_NONE;
    }
    else
    {
        Menu_GetPetSpawnPosition(&x, &y);
    }

    if (emotion == POKEGOTCHI_EMOTION_SLEEPING)
    {
        if (FlagGet(POKEGOTCHI_FLAG_FRNTR_BED))
        {
            x = HOUSE_BED_SLEEP_X;
            y = HOUSE_BED_SLEEP_Y;
        }
        else
        {
            x = HOUSE_PET_CENTER_X;
            y = HOUSE_PET_CENTER_Y;
        }
    }

    spriteId = CreatePokegotchiSprite(species, emotion, x, y, 0);
    if (spriteId == SPRITE_NONE)
        return FALSE;

    sMenuDataPtr->petSpriteId = spriteId;
    sMenuDataPtr->petEmotion = emotion;
    sMenuDataPtr->petActivity = (emotion == POKEGOTCHI_EMOTION_IDLE) ? HOUSE_PET_ACTIVITY_IDLE : HOUSE_PET_ACTIVITY_BUSY;
    return TRUE;
}

static u8 Menu_GetPoopAnchorId(u8 slot)
{
    return (sHousePoopLayout.anchorIds >> (slot * 4)) & 0xF;
}

static void Menu_SetPoopAnchorId(u8 slot, u8 anchorId)
{
    u16 shift = slot * 4;

    sHousePoopLayout.anchorIds &= ~(0xF << shift);
    sHousePoopLayout.anchorIds |= anchorId << shift;
}

static void Menu_ResetPoopLayout(void)
{
    sHousePoopLayout.anchorIds = 0;
    sHousePoopLayout.assignedMask = 0;
    sHousePoopLayout.flipMask = 0;
}

static bool8 Menu_IsPetAnchorAvailable(u8 anchorId, bool8 requireDifferentAnchor)
{
    const struct PokegotchiStats *stats = Pokegotchi_GetStats();
    u8 poopCount = min(stats->poopsOnScreen, POKEGOTCHI_MAX_POOPS);
    u8 i;

    if (requireDifferentAnchor
     && sMenuDataPtr->petSpriteId != SPRITE_NONE
     && sMenuDataPtr->petSpriteId < MAX_SPRITES
     && gSprites[sMenuDataPtr->petSpriteId].inUse
     && gSprites[sMenuDataPtr->petSpriteId].x == sHouseFloorAnchorCoords[anchorId][0]
     && gSprites[sMenuDataPtr->petSpriteId].y == sHouseFloorAnchorCoords[anchorId][1])
        return FALSE;

    for (i = 0; i < poopCount; i++)
    {
        u8 poopAnchorId;

        if (!(sHousePoopLayout.assignedMask & (1 << i)))
            continue;

        poopAnchorId = Menu_GetPoopAnchorId(i);
        if (poopAnchorId >= HOUSE_FLOOR_ANCHORS)
            continue;

        if (anchorId == poopAnchorId)
            return FALSE;
    }

    return TRUE;
}

static bool8 Menu_IsPoopAnchorAvailable(u8 anchorId, u16 usedAnchors, s16 petX, s16 petY)
{
    if (usedAnchors & (1 << anchorId)
     || (petX == sHouseFloorAnchorCoords[anchorId][0]
      && petY == sHouseFloorAnchorCoords[anchorId][1]))
        return FALSE;

    return TRUE;
}

static bool8 Menu_GetRandomPetAnchor(bool8 requireDifferentAnchor, u8 *anchorId)
{
    u8 candidates[HOUSE_FLOOR_ANCHORS];
    u8 candidateCount = 0;
    u8 i;

    for (i = 0; i < HOUSE_FLOOR_ANCHORS; i++)
    {
        if (Menu_IsPetAnchorAvailable(i, requireDifferentAnchor))
            candidates[candidateCount++] = i;
    }

    if (candidateCount == 0)
        return FALSE;

    *anchorId = candidates[RandomUniform(RNG_POKEGOTCHI_HOUSE, 0, candidateCount - 1)];
    return TRUE;
}

static void Menu_GetPetSpawnPosition(s16 *x, s16 *y)
{
    u8 anchorId = HOUSE_INITIAL_PET_ANCHOR;

    if (sHouseEntryMode != HOUSE_ENTRY_NORMAL)
    {
        *x = HOUSE_PET_CENTER_X;
        *y = HOUSE_PET_CENTER_Y;
        return;
    }

    if (!Menu_IsPetAnchorAvailable(anchorId, FALSE)
     && !Menu_GetRandomPetAnchor(FALSE, &anchorId))
    {
        *x = HOUSE_PET_CENTER_X;
        *y = HOUSE_PET_CENTER_Y;
        return;
    }

    *x = sHouseFloorAnchorCoords[anchorId][0];
    *y = sHouseFloorAnchorCoords[anchorId][1];
}

static bool8 Menu_CanPetWander(void)
{
    return sHouseEntryMode == HOUSE_ENTRY_NORMAL
        && sMenuDataPtr != NULL
        && sMenuDataPtr->petEmotion == POKEGOTCHI_EMOTION_IDLE
        && sMenuDataPtr->petActivity == HOUSE_PET_ACTIVITY_IDLE
        && sMenuDataPtr->petSpriteId != SPRITE_NONE
        && sMenuDataPtr->petSpriteId < MAX_SPRITES
        && gSprites[sMenuDataPtr->petSpriteId].inUse;
}

static bool8 Menu_MovePetToRandomAnchor(bool8 requireDifferentAnchor)
{
    u8 anchorId;

    if (!Menu_CanPetWander() || !Menu_GetRandomPetAnchor(requireDifferentAnchor, &anchorId))
        return FALSE;

    gSprites[sMenuDataPtr->petSpriteId].x = sHouseFloorAnchorCoords[anchorId][0];
    gSprites[sMenuDataPtr->petSpriteId].y = sHouseFloorAnchorCoords[anchorId][1];
    return TRUE;
}

static bool8 Menu_LoadPoopSpriteGfx(void)
{
    if (GetSpriteTileStartByTag(POOP_SPRITE_TAG) == 0xFFFF
     && LoadSpriteSheet(&sPoopSpriteSheet) == TAG_NONE)
        return FALSE;

    if (IndexOfSpritePaletteTag(POOP_SPRITE_PAL_TAG) == 0xFF
     && LoadSpritePalette(&sPoopSpritePalette) == 0xFF)
    {
        FreeSpriteTilesByTag(POOP_SPRITE_TAG);
        return FALSE;
    }

    return TRUE;
}

static void Menu_DestroyPoopSprites(void)
{
    u8 i;

    if (sMenuDataPtr == NULL)
        return;

    for (i = 0; i < POKEGOTCHI_MAX_POOPS; i++)
    {
        u8 spriteId = sMenuDataPtr->poopSpriteIds[i];

        if (spriteId != SPRITE_NONE && spriteId < MAX_SPRITES && gSprites[spriteId].inUse)
            DestroySprite(&gSprites[spriteId]);
        sMenuDataPtr->poopSpriteIds[i] = SPRITE_NONE;
    }
}

static void Menu_FreePoopSpriteGfx(void)
{
    if (GetSpriteTileStartByTag(POOP_SPRITE_TAG) != 0xFFFF)
        FreeSpriteTilesByTag(POOP_SPRITE_TAG);
    if (IndexOfSpritePaletteTag(POOP_SPRITE_PAL_TAG) != 0xFF)
        FreeSpritePaletteByTag(POOP_SPRITE_PAL_TAG);
}

static void Menu_RefreshPoopSprites(void)
{
    const struct PokegotchiStats *stats;
    u8 i;
    u8 poopCount;
    u16 usedAnchors = 0;
    s16 petX = 120;
    s16 petY = 88;

    if (sMenuDataPtr == NULL)
        return;

    stats = Pokegotchi_GetStats();
    poopCount = min(stats->poopsOnScreen, POKEGOTCHI_MAX_POOPS);
    Menu_DestroyPoopSprites();

    if (poopCount == 0)
    {
        Menu_ResetPoopLayout();
        return;
    }

    if (sMenuDataPtr->petSpriteId != SPRITE_NONE
     && sMenuDataPtr->petSpriteId < MAX_SPRITES
     && gSprites[sMenuDataPtr->petSpriteId].inUse)
    {
        petX = gSprites[sMenuDataPtr->petSpriteId].x;
        petY = gSprites[sMenuDataPtr->petSpriteId].y;
    }

    for (i = 0; i < POKEGOTCHI_MAX_POOPS; i++)
    {
        u8 anchorId;

        if (i >= poopCount)
        {
            sHousePoopLayout.assignedMask &= ~(1 << i);
            sHousePoopLayout.flipMask &= ~(1 << i);
            continue;
        }

        anchorId = Menu_GetPoopAnchorId(i);
        if (!(sHousePoopLayout.assignedMask & (1 << i))
         || anchorId >= HOUSE_FLOOR_ANCHORS
         || !Menu_IsPoopAnchorAvailable(anchorId, usedAnchors, petX, petY))
        {
            sHousePoopLayout.assignedMask &= ~(1 << i);
            continue;
        }

        usedAnchors |= 1 << anchorId;
    }

    for (i = 0; i < poopCount; i++)
    {
        u8 candidates[HOUSE_FLOOR_ANCHORS];
        u8 candidateCount = 0;
        u8 anchorId;
        u8 j;

        if (sHousePoopLayout.assignedMask & (1 << i))
            continue;

        for (j = 0; j < HOUSE_FLOOR_ANCHORS; j++)
        {
            if (Menu_IsPoopAnchorAvailable(j, usedAnchors, petX, petY))
                candidates[candidateCount++] = j;
        }

        if (candidateCount == 0)
            continue;

        anchorId = candidates[RandomUniform(RNG_POKEGOTCHI_HOUSE, 0, candidateCount - 1)];
        Menu_SetPoopAnchorId(i, anchorId);
        sHousePoopLayout.assignedMask |= 1 << i;
        if (RandomUniform(RNG_POKEGOTCHI_HOUSE, 0, 1))
            sHousePoopLayout.flipMask |= 1 << i;
        else
            sHousePoopLayout.flipMask &= ~(1 << i);
        usedAnchors |= 1 << anchorId;
    }

    if (!Menu_LoadPoopSpriteGfx())
        return;

    for (i = 0; i < poopCount; i++)
    {
        u8 anchorId;
        u8 spriteId;

        if (!(sHousePoopLayout.assignedMask & (1 << i)))
            continue;

        anchorId = Menu_GetPoopAnchorId(i);
        spriteId = CreateSprite(&sPoopSpriteTemplate, sHouseFloorAnchorCoords[anchorId][0], sHouseFloorAnchorCoords[anchorId][1], 1);

        if (spriteId == SPRITE_NONE)
            continue;

        sMenuDataPtr->poopSpriteIds[i] = spriteId;
        StartSpriteAnimIfDifferent(&gSprites[spriteId], i % 2);
        gSprites[spriteId].hFlip = (sHousePoopLayout.flipMask >> i) & 1;
    }
}

static const struct PokegotchiFeedFoodItem *Menu_GetFoodItemByKey(u8 inventoryKey)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(gPokegotchiFeedFoodItems); i++)
    {
        if (gPokegotchiFeedFoodItems[i].inventoryKey == inventoryKey)
            return &gPokegotchiFeedFoodItems[i];
    }

    return NULL;
}

static bool8 Menu_LoadFoodSpriteSheet(const struct PokegotchiFeedFoodItem *foodItem)
{
    struct SpriteSheet spriteSheet;

    if (foodItem == NULL || foodItem->spriteTiles == NULL)
        return FALSE;

    if (GetSpriteTileStartByTag(foodItem->tileTag) != 0xFFFF)
        return TRUE;

    spriteSheet.data = foodItem->spriteTiles;
    spriteSheet.size = FEED_FOOD_SPRITESHEET_SIZE;
    spriteSheet.tag = foodItem->tileTag;

    LoadSpriteSheet(&spriteSheet);
    return GetSpriteTileStartByTag(foodItem->tileTag) != 0xFFFF;
}

static bool8 Menu_LoadFoodSpritePalette(const struct PokegotchiFeedFoodItem *foodItem)
{
    struct SpritePalette spritePalette;

    if (foodItem == NULL || foodItem->palette == NULL)
        return FALSE;

    if (IndexOfSpritePaletteTag(foodItem->paletteTag) != 0xFF)
        return TRUE;

    spritePalette.data = foodItem->palette;
    spritePalette.tag = foodItem->paletteTag;

    return LoadSpritePalette(&spritePalette) != 0xFF;
}

static void Menu_LoadSceneFoodSprite(void)
{
    const struct PokegotchiFeedFoodItem *foodItem = Menu_GetFoodItemByKey(sHouseEatingSceneFoodKey);
    struct SpriteTemplate spriteTemplate;
    u8 spriteId;

    if (foodItem == NULL)
        return;

    if (!Menu_LoadFoodSpriteSheet(foodItem) || !Menu_LoadFoodSpritePalette(foodItem))
        return;

    spriteTemplate = sFoodSpriteTemplate;
    spriteTemplate.tileTag = foodItem->tileTag;
    spriteTemplate.paletteTag = foodItem->paletteTag;
    spriteId = CreateSprite(&spriteTemplate, HOUSE_EATING_FOOD_X, HOUSE_EATING_FOOD_Y, 1);
    if (spriteId == MAX_SPRITES)
        return;

    sMenuDataPtr->foodSpriteId = spriteId;
    Menu_SetFoodBiteFrame(0);
}

static void Menu_DestroyFoodSprite(void)
{
    const struct PokegotchiFeedFoodItem *foodItem = Menu_GetFoodItemByKey(sHouseEatingSceneFoodKey);

    if (sMenuDataPtr != NULL
     && sMenuDataPtr->foodSpriteId != SPRITE_NONE
     && sMenuDataPtr->foodSpriteId < MAX_SPRITES
     && gSprites[sMenuDataPtr->foodSpriteId].inUse)
    {
        DestroySprite(&gSprites[sMenuDataPtr->foodSpriteId]);
        sMenuDataPtr->foodSpriteId = SPRITE_NONE;
    }

    if (foodItem == NULL || foodItem->spriteTiles == NULL)
        return;

    if (GetSpriteTileStartByTag(foodItem->tileTag) != 0xFFFF)
        FreeSpriteTilesByTag(foodItem->tileTag);

    if (IndexOfSpritePaletteTag(foodItem->paletteTag) != 0xFF)
        FreeSpritePaletteByTag(foodItem->paletteTag);
}

static void Menu_SetFoodBiteFrame(u8 frame)
{
    if (sMenuDataPtr == NULL
     || sMenuDataPtr->foodSpriteId == SPRITE_NONE
     || sMenuDataPtr->foodSpriteId >= MAX_SPRITES
     || !gSprites[sMenuDataPtr->foodSpriteId].inUse)
        return;

    if (frame >= HOUSE_EATING_FOOD_FRAME_COUNT)
        frame = HOUSE_EATING_FOOD_FRAME_COUNT - 1;

    StartSpriteAnimIfDifferent(&gSprites[sMenuDataPtr->foodSpriteId], frame);
}

static struct HouseReaction Menu_GetPostEatReaction(enum PokegotchiDailyRewardTier rewardTier)
{
    if (rewardTier == POKEGOTCHI_DAILY_REWARD_FIRST)
        return (struct HouseReaction){POKEGOTCHI_EMOTION_HAPPY, 1, POKEGOTCHI_EMOTICON_SUN};
    if (rewardTier == POKEGOTCHI_DAILY_REWARD_SECOND)
        return (struct HouseReaction){POKEGOTCHI_EMOTION_HAPPY, 1, POKEGOTCHI_EMOTICON_NONE};
    return (struct HouseReaction){POKEGOTCHI_EMOTION_IDLE, 0, POKEGOTCHI_EMOTICON_NONE};
}

static void Menu_StartPetInteraction(u8 taskId)
{
    enum PokegotchiInteractionReaction reactionType;
    struct HouseReaction reaction;

    Pokegotchi_Sync();
    // The sleep state can coexist with the sulking state.
    // Give waking priority so sulking cannot reject waking.
    if (Pokegotchi_IsSleeping())
    {
        if (!Pokegotchi_WakeForActivity() || !Menu_SetPetEmotion(POKEGOTCHI_EMOTION_IDLE))
            return;

        gSprites[sMenuDataPtr->petSpriteId].animPaused = TRUE;
        sMenuDataPtr->petActivity = HOUSE_PET_ACTIVITY_BUSY;
        Menu_CreateEmoticon(POKEGOTCHI_EMOTICON_ANGER, TRUE);
        gTasks[taskId].data[1] = HOUSE_REACTION_PHASE_WAKE;
        gTasks[taskId].data[2] = 0;
        gTasks[taskId].data[3] = HOUSE_WAKE_REACTION_FRAMES;
        gTasks[taskId].func = Task_MenuPetInteraction;
        return;
    }

    Menu_UpdatePetConditionState();
    if (sMenuDataPtr->petActivity == HOUSE_PET_ACTIVITY_SULKING)
    {
        if (Menu_CreateEmoticon(POKEGOTCHI_EMOTICON_ANGER, FALSE))
        {
            gTasks[taskId].data[1] = HOUSE_REACTION_PHASE_EMOTICON_ONLY;
            gTasks[taskId].data[2] = 0;
            gTasks[taskId].data[3] = HOUSE_REACTION_CYCLE_FRAMES;
            gTasks[taskId].func = Task_MenuPetInteraction;
        }
        return;
    }

    reactionType = Pokegotchi_GetInteractionReaction(Pokegotchi_GetStats());
    if (reactionType == POKEGOTCHI_REACTION_SULKING)
    {
        Menu_EnterSulkingState();
        return;
    }

    reaction = Menu_GetReaction(reactionType);
    if (reaction.loopCount == 0 || !Menu_SetPetEmotion(reaction.emotion))
        return;

    Pokegotchi_ApplyDailyPetInteractionReward();
    Menu_CreateEmoticon(reaction.emoticon, FALSE);
    gTasks[taskId].data[1] = HOUSE_REACTION_PHASE_ACTIVE;
    gTasks[taskId].data[2] = 0;
    gTasks[taskId].data[3] = reaction.loopCount * HOUSE_REACTION_CYCLE_FRAMES;
    gTasks[taskId].func = Task_MenuPetInteraction;
}

static void Menu_FinishPetInteraction(u8 taskId)
{
    Menu_DestroyEmoticon();
    if (Pokegotchi_GetInteractionReaction(Pokegotchi_GetStats()) == POKEGOTCHI_REACTION_SULKING)
    {
        Menu_EnterSulkingState();
    }
    else if (Pokegotchi_IsSleeping())
    {
        if (!Menu_SetPetEmotion(POKEGOTCHI_EMOTION_SLEEPING))
            Menu_SetPetEmotion(POKEGOTCHI_EMOTION_IDLE);
    }
    else
    {
        Menu_SetPetEmotion(POKEGOTCHI_EMOTION_IDLE);
    }

    gTasks[taskId].data[1] = 0;
    gTasks[taskId].data[2] = 0;
    gTasks[taskId].data[3] = 0;
    gTasks[taskId].func = Task_MenuMain;
}

static void Task_MenuPetInteraction(u8 taskId)
{
    if (++gTasks[taskId].data[2] < gTasks[taskId].data[3])
        return;

    if (gTasks[taskId].data[1] == HOUSE_REACTION_PHASE_ACTIVE)
    {
        Menu_DestroyEmoticon();
        if (sMenuDataPtr->petSpriteId != SPRITE_NONE
         && sMenuDataPtr->petSpriteId < MAX_SPRITES
         && gSprites[sMenuDataPtr->petSpriteId].inUse)
        {
            SeekSpriteAnim(&gSprites[sMenuDataPtr->petSpriteId], 0);
            gSprites[sMenuDataPtr->petSpriteId].animPaused = TRUE;
        }
        gTasks[taskId].data[1] = HOUSE_REACTION_PHASE_HOLD;
        gTasks[taskId].data[2] = 0;
        gTasks[taskId].data[3] = HOUSE_REACTION_HOLD_FRAMES;
        return;
    }

    if (gTasks[taskId].data[1] == HOUSE_REACTION_PHASE_EMOTICON_ONLY)
    {
        Menu_DestroyEmoticon();
        gTasks[taskId].data[1] = 0;
        gTasks[taskId].data[2] = 0;
        gTasks[taskId].data[3] = 0;
        gTasks[taskId].func = Task_MenuMain;
        return;
    }

    Menu_FinishPetInteraction(taskId);
}

static void Task_MenuWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        if (sHouseEntryMode == HOUSE_ENTRY_EATING_SCENE)
        {
            gTasks[taskId].data[0] = HOUSE_EATING_SCENE_PHASE_EATING;
            gTasks[taskId].data[1] = 0;
            gTasks[taskId].data[2] = 0;
            gTasks[taskId].func = Task_MenuEatingScene;
        }
        else
        {
            gTasks[taskId].data[0] = STATUS_ICON;
            sMenuDataPtr->syncTaskId = CreateTask(Task_MenuSyncPokegotchi, 1);
            sMenuDataPtr->wanderTaskId = CreateTask(Task_MenuWanderPet, 1);
            if (sMenuDataPtr->wanderTaskId != TASK_NONE)
            {
                gTasks[sMenuDataPtr->wanderTaskId].data[0] = 0;
                gTasks[sMenuDataPtr->wanderTaskId].data[1] = RandomUniform(RNG_POKEGOTCHI_HOUSE, HOUSE_WANDER_MIN_FRAMES, HOUSE_WANDER_MAX_FRAMES);
            }
            gTasks[taskId].func = Task_MenuMain;
        }
    }
}

static void Task_MenuSyncPokegotchi(u8 taskId)
{
    if (++gTasks[taskId].data[1] >= HOUSE_SLEEP_CHECK_INTERVAL_FRAMES)
    {
        gTasks[taskId].data[1] = 0;
        Menu_UpdatePetSleepState();
    }

    if (++gTasks[taskId].data[0] >= HOUSE_SYNC_INTERVAL_FRAMES)
    {
        gTasks[taskId].data[0] = 0;
        Pokegotchi_SyncAndSave();
        Menu_UpdatePetConditionState();
        Menu_RefreshPoopSprites();
    }
}

static void Task_MenuWanderPet(u8 taskId)
{
    if (!Menu_CanPetWander())
        return;

    if (++gTasks[taskId].data[0] < gTasks[taskId].data[1])
        return;

    gTasks[taskId].data[0] = 0;
    Menu_MovePetToRandomAnchor(TRUE);
    gTasks[taskId].data[1] = RandomUniform(RNG_POKEGOTCHI_HOUSE, HOUSE_WANDER_MIN_FRAMES, HOUSE_WANDER_MAX_FRAMES);
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

static UNUSED void CB2_OpenPokegotchiWaiterMinigameFromHouse(void)
{
    OpenPokegotchiWaiterMinigame(sHouseMenuExitCallback, sHouseWaiterMinigameDifficulty);
}

static void CB2_ExitToTamatownFromHouse(void)
{
    Pokegotchi_SyncAndSave();
    SetWarpDestination(MAP_GROUP(MAP_TAMATOWN), MAP_NUM(MAP_TAMATOWN), WARP_ID_NONE, 28, 17);
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

    if (JOY_NEW(L_BUTTON | R_BUTTON))
    {
        Menu_StartPetInteraction(taskId);
        return;
    }

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
        if (gTasks[taskId].data[0] != STATUS_ICON && Pokegotchi_IsSleeping())
        {
            if (!IsSEPlaying())
                PlaySE(SE_FAILURE);
            return;
        }

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
            if (Pokegotchi_GetStats()->poopsOnScreen > 0)
            {
                Pokegotchi_ClearPoops();
                Menu_RefreshPoopSprites();
                PlaySE(SE_SELECT);
            }
            else if (!IsSEPlaying())
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

static void Task_MenuEatingScene(u8 taskId)
{
    if (gTasks[taskId].data[0] == HOUSE_EATING_SCENE_PHASE_EATING)
    {
        u8 stage = gTasks[taskId].data[2];
        u8 stageDuration = sHouseEatingFoodStageDurations[stage];

        if (++gTasks[taskId].data[1] < stageDuration)
            return;

        gTasks[taskId].data[1] = 0;
        if (gTasks[taskId].data[2] < HOUSE_EATING_FOOD_FRAME_COUNT - 1)
        {
            gTasks[taskId].data[2]++;
            Menu_SetFoodBiteFrame(gTasks[taskId].data[2]);
            return;
        }

        Menu_DestroyFoodSprite();
        gTasks[taskId].data[0] = HOUSE_EATING_SCENE_PHASE_POST_EAT;
        gTasks[taskId].data[1] = 0;
        {
            struct HouseReaction reaction = Menu_GetPostEatReaction(sHouseEatingSceneRewardTier);

            gTasks[taskId].data[2] = HOUSE_POST_EAT_PHASE_FRAMES;
            if (reaction.loopCount != 0 && Menu_SetPetEmotion(reaction.emotion))
            {
                Menu_CreateEmoticon(reaction.emoticon, FALSE);
                gTasks[taskId].data[2] = reaction.loopCount * HOUSE_REACTION_CYCLE_FRAMES;
            }
            else if (sMenuDataPtr->petEmotion != POKEGOTCHI_EMOTION_IDLE)
            {
                Menu_SetPetEmotion(POKEGOTCHI_EMOTION_IDLE);
            }
        }
        return;
    }

    if (++gTasks[taskId].data[1] < gTasks[taskId].data[2])
        return;

    Menu_FadeAndBail();
    DestroyTask(taskId);
}
