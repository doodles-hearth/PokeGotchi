#include "global.h"
#include "pokegotchi_waiter_minigame.h"
#include "pokegotchi_intro.h"
#include "bg.h"
#include "coins.h"
#include "decompress.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "international_string_util.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "overworld.h"
#include "palette.h"
#include "random.h"
#include "scanline_effect.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "task.h"
#include "text_window.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/vars.h"

#define WAITER_SPRITE_PAL_TAG           5600
#define WAITER_CURSOR_SPRITE_TAG        5601
#define WAITER_MENU_SPRITE_TAG          5602
#define WAITER_HOT_DOG_SPRITE_TAG       5603
#define WAITER_SHUCKLE_SPRITE_TAG       5604
#define WAITER_ZUBAT_SPRITE_TAG         5605
#define WAITER_GULPIN_SPRITE_TAG        5606
#define WAITER_HAPPY_SPRITE_TAG         5607
#define WAITER_ORDERING_SPRITE_TAG      5608
#define WAITER_ANGRY_SPRITE_TAG         5609

#define WAITER_BG_TABLES                1
#define WAITER_BG_ROOM                  2
#define WAITER_ROOM_PALETTE_SLOT        0
#define WAITER_TABLES_PALETTE_SLOT      1
#define WAITER_FRAMES_PER_SECOND        60
#define WAITER_COUNTDOWN_STAGE_FRAMES   WAITER_FRAMES_PER_SECOND
#define WAITER_CUSTOMER_TASK_PRIORITY   2
#define WAITER_GAME_DURATION_SECONDS    60
#define WAITER_MS_TO_FRAMES(ms)         ((u16)(((ms) * WAITER_FRAMES_PER_SECOND) / 1000))
#define WAITER_TIMER_RIGHT_PADDING      4
#define WAITER_COINS_PER_SERVE          5
#define WAITER_END_DELAY_FRAMES         WAITER_FRAMES_PER_SECOND

enum WaiterWindowIds
{
    WAITER_TIMER_WINDOW,
    WAITER_COUNTDOWN_WINDOW,
};

enum WaiterSpriteIds
{
    WAITER_SPRITE_CURSOR,
    WAITER_SPRITE_MENU,
    WAITER_SPRITE_HOT_DOG,
    WAITER_SPRITE_SHUCKLE,
    WAITER_SPRITE_ZUBAT,
    WAITER_SPRITE_GULPIN,
    WAITER_SPRITE_HAPPY,
    WAITER_SPRITE_WANT_TO_ORDER,
    WAITER_SPRITE_ANGRY,
    WAITER_SPRITE_COUNT,
};

enum WaiterSpriteSheetIds
{
    WAITER_SHEET_CURSOR,
    WAITER_SHEET_MENU,
    WAITER_SHEET_HOT_DOG,
    WAITER_SHEET_SHUCKLE,
    WAITER_SHEET_ZUBAT,
    WAITER_SHEET_GULPIN,
    WAITER_SHEET_HAPPY,
    WAITER_SHEET_WANT_TO_ORDER,
    WAITER_SHEET_ANGRY,
    WAITER_SHEET_COUNT,
};

enum WaiterTableIds
{
    WAITER_TABLE_TOP_LEFT,
    WAITER_TABLE_TOP_MIDDLE,
    WAITER_TABLE_TOP_RIGHT,
    WAITER_TABLE_BOTTOM_LEFT,
    WAITER_TABLE_BOTTOM_MIDDLE,
    WAITER_TABLE_BOTTOM_RIGHT,
    WAITER_TABLE_COUNT,
};

enum WaiterCustomerIds
{
    WAITER_CUSTOMER_SHUCKLE,
    WAITER_CUSTOMER_ZUBAT,
    WAITER_CUSTOMER_GULPIN,
    WAITER_CUSTOMER_COUNT,
};

enum WaiterClockStates
{
    WAITER_CLOCK_STATE_COUNTDOWN,
    WAITER_CLOCK_STATE_RUNNING,
    WAITER_CLOCK_STATE_CLOSING,
    WAITER_CLOCK_STATE_STOPPED,
};

enum WaiterCountdownSteps
{
    WAITER_COUNTDOWN_STEP_THREE,
    WAITER_COUNTDOWN_STEP_TWO,
    WAITER_COUNTDOWN_STEP_ONE,
    WAITER_COUNTDOWN_STEP_START,
    WAITER_COUNTDOWN_STEP_DONE,
};

enum WaiterFontColors
{
    WAITER_FONT_BLACK,
    WAITER_FONT_WHITE,
    WAITER_FONT_RED,
    WAITER_FONT_BLUE,
};

enum WaiterCustomerPhases
{
    WAITER_CUSTOMER_PHASE_INACTIVE,
    WAITER_CUSTOMER_PHASE_MENU,
    WAITER_CUSTOMER_PHASE_ORDERING,
    WAITER_CUSTOMER_PHASE_RESULT_SUCCESS,
    WAITER_CUSTOMER_PHASE_RESULT_FAIL,
};

enum WaiterCustomerPoses
{
    WAITER_CUSTOMER_POSE_DEFAULT,
    WAITER_CUSTOMER_POSE_MAD,
    WAITER_CUSTOMER_POSE_HAPPY,
};

struct WaiterMinigameCoord
{
    s16 x;
    s16 y;
};

struct WaiterTableSpriteSpawn
{
    u8 spriteId;
    u8 sheetId;
    u8 subpriority;
    u8 tableId;
};

struct WaiterCursorSpawn
{
    u8 spriteId;
    u8 subpriority;
    u8 tableId;
};

struct WaiterCustomerResources
{
    u8 customerSpriteId;
    u8 menuSpriteId;
    u8 hotDogSpriteId;
    u8 orderingSpriteId;
    u8 happySpriteId;
    u8 angrySpriteId;
    u8 tableId;
    u8 taskId;
    u8 phase;
    u16 phaseTimer;
    bool8 serveRequested;
};

struct WaiterCustomerTemplate
{
    u8 customerSheetId;
    u8 customerSubpriority;
    u8 tableItemSubpriority;
    u8 emotionSubpriority;
};

struct WaiterMinigameResources
{
    MainCallback savedCallback;
    u8 gfxLoadState;
    u8 spriteIds[WAITER_SPRITE_COUNT];
    u8 controlTaskId;
    u8 clockTaskId;
    u8 cursorTableId;
    u8 difficulty;
    u8 clockState;
    u8 countdownStep;
    u16 countdownTimer;
    u16 arrivalTimer;
    u16 closedTimer;
    u16 endDelayTimer;
    u16 successfulServes;
    u16 elapsedFrames;
    u8 elapsedSeconds;
    bool8 firstArrivalDone;
    bool8 inputEnabled;
    bool8 pendingArrival;
    bool8 arrivalsStopped;
    bool8 exitStarted;
    bool8 windowsInitialized;
    struct WaiterCustomerResources customers[WAITER_CUSTOMER_COUNT];
};

static EWRAM_DATA struct WaiterMinigameResources *sWaiterMinigame = NULL;
static EWRAM_DATA u16 *sWaiterRoomTilemapBuffer = NULL;
static EWRAM_DATA u16 *sWaiterTablesTilemapBuffer = NULL;

static void WaiterMinigame_Init(MainCallback callback, enum PokegotchiWaiterMinigameDifficulty difficulty);
static void WaiterMinigame_RunSetup(void);
static void WaiterMinigame_MainCB(void);
static void WaiterMinigame_VBlankCB(void);
static void WaiterMinigame_ResetGpuRegsAndBgs(void);
static bool8 WaiterMinigame_DoGfxSetup(void);
static bool8 WaiterMinigame_InitBgs(void);
static bool8 WaiterMinigame_LoadGraphics(void);
static void WaiterMinigame_InitWindows(void);
static bool8 WaiterMinigame_LoadSprites(void);
static void WaiterMinigame_ApplyPaletteNum(u16 *tilemapBuffer, u32 size, u8 paletteNum);
static u8 WaiterMinigame_CreateCustomerAtTable(u8 sheetId, u8 tableId, u8 subpriority);
static u8 WaiterMinigame_CreateTableItemAtTable(u8 sheetId, u8 tableId, u8 subpriority);
static u8 WaiterMinigame_CreateEmotionAtTable(u8 sheetId, u8 tableId, u8 subpriority);
static u8 WaiterMinigame_CreateCursorAtTable(u8 tableId, u8 subpriority);
static u8 WaiterMinigame_CreateStaticSprite(const struct SpriteSheet *sheet, const struct OamData *oam, s16 x, s16 y, u8 subpriority);
static void WaiterMinigame_SetCustomerPose(u8 customerId, u8 pose);
static void WaiterMinigame_SetCursorTable(u8 tableId);
static void WaiterMinigame_SetCustomerSpriteTable(u8 spriteId, u8 tableId);
static void WaiterMinigame_SetTableItemSpriteTable(u8 spriteId, u8 tableId);
static void WaiterMinigame_SetEmotionSpriteTable(u8 spriteId, u8 tableId);
static void WaiterMinigame_SetSpriteVisibility(u8 spriteId, bool8 visible);
static void WaiterMinigame_HideAllCustomers(void);
static void WaiterMinigame_HideCustomerVisuals(u8 customerId);
static void WaiterMinigame_SetCustomerEntryTable(u8 customerId, u8 tableId);
static void WaiterMinigame_BeginCustomerMenu(u8 customerId, u8 tableId);
static void WaiterMinigame_BeginCustomerOrdering(u8 customerId);
static void WaiterMinigame_BeginCustomerSuccess(u8 customerId);
static void WaiterMinigame_BeginCustomerFailure(u8 customerId);
static void WaiterMinigame_FinishCustomer(u8 customerId, u8 taskId);
static bool8 WaiterMinigame_HasActiveCustomers(void);
static u8 WaiterMinigame_FindCustomerAtTable(u8 tableId);
static u8 WaiterMinigame_ChooseFreeCustomerId(void);
static u8 WaiterMinigame_ChooseFreeTable(void);
static u16 WaiterMinigame_ChooseRandomDuration(const u16 *durations, u32 count);
static u16 WaiterMinigame_ChooseMenuDuration(void);
static u16 WaiterMinigame_ChooseOrderingDuration(void);
static void WaiterMinigame_StartEntryCountdown(void);
static void WaiterMinigame_StartArrivalTimer(void);
static bool8 WaiterMinigame_SpawnCustomer(void);
static void WaiterMinigame_PrintTimer(void);
static void WaiterMinigame_PrintClosed(void);
static void WaiterMinigame_PrintCountdownText(const u8 *text);
static void WaiterMinigame_ClearCountdownText(void);
static void WaiterMinigame_ClearTimerText(void);
static void WaiterMinigame_UpdateCountdown(void);
static void WaiterMinigame_UpdateElapsedTimer(void);
static void WaiterMinigame_UpdateArrivals(void);
static void WaiterMinigame_UpdateEndSequence(void);
static u8 WaiterMinigame_GetAdjacentTable(u8 tableId, u16 direction);
static void WaiterMinigame_FreeResources(void);
static void WaiterMinigame_FadeAndBail(void);
static void Task_WaiterMinigameWaitFadeAndBail(u8 taskId);
static void Task_WaiterMinigameWaitFadeIn(u8 taskId);
static void Task_WaiterMinigameMain(u8 taskId);
static void Task_WaiterMinigameClock(u8 taskId);
static void Task_WaiterMinigameCustomer(u8 taskId);

static const struct BgTemplate sWaiterMinigameBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 3,
        .mapBaseIndex = 31,
        .priority = 0,
    },
    {
        .bg = WAITER_BG_TABLES,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .priority = 1,
    },
    {
        .bg = WAITER_BG_ROOM,
        .charBaseIndex = 1,
        .mapBaseIndex = 29,
        .priority = 3,
    },
};

static const struct WindowTemplate sWaiterWindowTemplates[] =
{
    [WAITER_TIMER_WINDOW] =
    {
        .bg = 0,
        .tilemapLeft = 22,
        .tilemapTop = 0,
        .width = 8,
        .height = 2,
        .paletteNum = 14,
        .baseBlock = 1,
    },
    [WAITER_COUNTDOWN_WINDOW] =
    {
        .bg = 0,
        .tilemapLeft = 11,
        .tilemapTop = 8,
        .width = 8,
        .height = 4,
        .paletteNum = 14,
        .baseBlock = 17,
    },
    DUMMY_WIN_TEMPLATE,
};

static const u32 sWaiterRoomTiles[] = INCGFX_U32("graphics/pokegotchi_waiter_minigame/bg_room_tiles.png", ".4bpp");
static const u16 sWaiterRoomTilemap[] = INCBIN_U16("graphics/pokegotchi_waiter_minigame/bg_room_tiles.bin");
static const u16 sWaiterRoomPalette[] = INCGFX_U16("graphics/pokegotchi_waiter_minigame/bg_room_tiles.png", ".gbapal");

static const u32 sWaiterTablesTiles[] = INCGFX_U32("graphics/pokegotchi_waiter_minigame/bg_tables_tiles.png", ".4bpp");
static const u16 sWaiterTablesTilemap[] = INCBIN_U16("graphics/pokegotchi_waiter_minigame/bg_tables_tiles.bin");
static const u16 sWaiterTablesPalette[] = INCGFX_U16("graphics/pokegotchi_waiter_minigame/bg_tables_tiles.png", ".gbapal");
static const u16 sWaiterTextPalette[] = INCGFX_U16("graphics/pokegotchi_feed_ui/feed_text.pal", ".gbapal");

static const u8 sWaiterCursorSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_waiter_minigame/cursor.png", ".4bpp");
static const u8 sWaiterMenuSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_waiter_minigame/menu.png", ".4bpp");
static const u8 sWaiterHotDogSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_waiter_minigame/hot_dog.png", ".4bpp");
static const u8 sWaiterShuckleSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_waiter_minigame/customers/shuckle.png", ".4bpp");
static const u8 sWaiterZubatSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_waiter_minigame/customers/zubat.png", ".4bpp");
static const u8 sWaiterGulpinSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_waiter_minigame/customers/gulpin.png", ".4bpp");
static const u8 sWaiterHappySpriteGfx[] = INCGFX_U8("graphics/pokegotchi_waiter_minigame/emotes/happy.png", ".4bpp");
static const u8 sWaiterOrderingSpriteGfx[] = INCGFX_U8("graphics/pokegotchi_waiter_minigame/emotes/want_to_order.png", ".4bpp");
static const u8 sWaiterAngrySpriteGfx[] = INCGFX_U8("graphics/pokegotchi_waiter_minigame/emotes/angry.png", ".4bpp");
static const u16 sWaiterSpritePalette[] = INCGFX_U16("graphics/pokegotchi_waiter_minigame/cursor.png", ".gbapal");

static const struct SpriteSheet sWaiterSpriteSheets[] =
{
    {sWaiterCursorSpriteGfx,    sizeof(sWaiterCursorSpriteGfx),     WAITER_CURSOR_SPRITE_TAG},
    {sWaiterMenuSpriteGfx,      sizeof(sWaiterMenuSpriteGfx),       WAITER_MENU_SPRITE_TAG},
    {sWaiterHotDogSpriteGfx,    sizeof(sWaiterHotDogSpriteGfx),     WAITER_HOT_DOG_SPRITE_TAG},
    {sWaiterShuckleSpriteGfx,   sizeof(sWaiterShuckleSpriteGfx),    WAITER_SHUCKLE_SPRITE_TAG},
    {sWaiterZubatSpriteGfx,     sizeof(sWaiterZubatSpriteGfx),      WAITER_ZUBAT_SPRITE_TAG},
    {sWaiterGulpinSpriteGfx,    sizeof(sWaiterGulpinSpriteGfx),     WAITER_GULPIN_SPRITE_TAG},
    {sWaiterHappySpriteGfx,     sizeof(sWaiterHappySpriteGfx),      WAITER_HAPPY_SPRITE_TAG},
    {sWaiterOrderingSpriteGfx,  sizeof(sWaiterOrderingSpriteGfx),   WAITER_ORDERING_SPRITE_TAG},
    {sWaiterAngrySpriteGfx,     sizeof(sWaiterAngrySpriteGfx),      WAITER_ANGRY_SPRITE_TAG},
};

static const struct WaiterMinigameCoord sWaiterCustomerCoords[WAITER_TABLE_COUNT] =
{
    [WAITER_TABLE_TOP_LEFT] = {40, 28},
    [WAITER_TABLE_TOP_MIDDLE] = {104, 28},
    [WAITER_TABLE_TOP_RIGHT] = {168, 28},
    [WAITER_TABLE_BOTTOM_LEFT] = {40, 108},
    [WAITER_TABLE_BOTTOM_MIDDLE] = {104, 108},
    [WAITER_TABLE_BOTTOM_RIGHT] = {168, 108},
};

static const struct WaiterMinigameCoord sWaiterTableItemCoords[WAITER_TABLE_COUNT] =
{
    [WAITER_TABLE_TOP_LEFT] = {40, 48},
    [WAITER_TABLE_TOP_MIDDLE] = {104, 48},
    [WAITER_TABLE_TOP_RIGHT] = {168, 48},
    [WAITER_TABLE_BOTTOM_LEFT] = {40, 128},
    [WAITER_TABLE_BOTTOM_MIDDLE] = {104, 128},
    [WAITER_TABLE_BOTTOM_RIGHT] = {168, 128},
};

static const struct WaiterMinigameCoord sWaiterCursorCoords[WAITER_TABLE_COUNT] =
{
    [WAITER_TABLE_TOP_LEFT] = {44, 48},
    [WAITER_TABLE_TOP_MIDDLE] = {108, 48},
    [WAITER_TABLE_TOP_RIGHT] = {172, 48},
    [WAITER_TABLE_BOTTOM_LEFT] = {44, 128},
    [WAITER_TABLE_BOTTOM_MIDDLE] = {108, 128},
    [WAITER_TABLE_BOTTOM_RIGHT] = {172, 128},
};

static const struct WaiterMinigameCoord sWaiterEmotionCoords[WAITER_TABLE_COUNT] =
{
    [WAITER_TABLE_TOP_LEFT] = {68, 20},
    [WAITER_TABLE_TOP_MIDDLE] = {132, 20},
    [WAITER_TABLE_TOP_RIGHT] = {196, 20},
    [WAITER_TABLE_BOTTOM_LEFT] = {68, 100},
    [WAITER_TABLE_BOTTOM_MIDDLE] = {132, 100},
    [WAITER_TABLE_BOTTOM_RIGHT] = {196, 100},
};

static const u8 sWaiterLoadedSpriteSheetIds[] =
{
    WAITER_SHEET_CURSOR,
    WAITER_SHEET_MENU,
    WAITER_SHEET_HOT_DOG,
    WAITER_SHEET_SHUCKLE,
    WAITER_SHEET_ZUBAT,
    WAITER_SHEET_GULPIN,
    WAITER_SHEET_HAPPY,
    WAITER_SHEET_WANT_TO_ORDER,
    WAITER_SHEET_ANGRY,
};

static const struct WaiterCustomerTemplate sWaiterCustomerTemplates[WAITER_CUSTOMER_COUNT] =
{
    [WAITER_CUSTOMER_SHUCKLE] =
    {
        .customerSheetId = WAITER_SHEET_SHUCKLE,
        .customerSubpriority = 0,
        .tableItemSubpriority = 1,
        .emotionSubpriority = 4,
    },
    [WAITER_CUSTOMER_ZUBAT] =
    {
        .customerSheetId = WAITER_SHEET_ZUBAT,
        .customerSubpriority = 1,
        .tableItemSubpriority = 2,
        .emotionSubpriority = 5,
    },
    [WAITER_CUSTOMER_GULPIN] =
    {
        .customerSheetId = WAITER_SHEET_GULPIN,
        .customerSubpriority = 2,
        .tableItemSubpriority = 3,
        .emotionSubpriority = 6,
    },
};

static const u8 sWaiterWindowFontColors[][3] =
{
    [WAITER_FONT_BLACK] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY},
    [WAITER_FONT_WHITE] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY},
    [WAITER_FONT_RED] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_RED, TEXT_COLOR_LIGHT_GRAY},
    [WAITER_FONT_BLUE] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_BLUE, TEXT_COLOR_LIGHT_GRAY},
};

static const u8 sText_WaiterCountdown3[] = _("3");
static const u8 sText_WaiterCountdown2[] = _("2");
static const u8 sText_WaiterCountdown1[] = _("1");
static const u8 sText_WaiterCountdownStart[] = _("Start");
static const u8 sText_WaiterClosed[] = _("Closed");

static const u16 sWaiterArrivalDurationsFirst[] =
{
    WAITER_MS_TO_FRAMES(1000),
    WAITER_MS_TO_FRAMES(1500),
    WAITER_MS_TO_FRAMES(1500),
    WAITER_MS_TO_FRAMES(2000),
    WAITER_MS_TO_FRAMES(2500),
};

// Arrival Durations
// Easy
static const u16 sWaiterEasyArrivalDurationsStandard[] =
{
    WAITER_MS_TO_FRAMES(3500),
    WAITER_MS_TO_FRAMES(4000),
    WAITER_MS_TO_FRAMES(4500),
    WAITER_MS_TO_FRAMES(5000),
};

static const u16 sWaiterEasyArrivalDurationsMid[] =
{
    WAITER_MS_TO_FRAMES(3000),
    WAITER_MS_TO_FRAMES(3500),
    WAITER_MS_TO_FRAMES(3500),
    WAITER_MS_TO_FRAMES(4000),
};

static const u16 sWaiterEasyArrivalDurationsLate[] =
{
    WAITER_MS_TO_FRAMES(2500),
    WAITER_MS_TO_FRAMES(3000),
    WAITER_MS_TO_FRAMES(3000),
    WAITER_MS_TO_FRAMES(3500),
};

// Hard
static const u16 sWaiterHardArrivalDurationsStandard[] =
{
    WAITER_MS_TO_FRAMES(3500),
    WAITER_MS_TO_FRAMES(3500),
    WAITER_MS_TO_FRAMES(4000),
    WAITER_MS_TO_FRAMES(4500),
};

static const u16 sWaiterHardArrivalDurationsMid[] =
{
    WAITER_MS_TO_FRAMES(2500),
    WAITER_MS_TO_FRAMES(3000),
    WAITER_MS_TO_FRAMES(3000),
    WAITER_MS_TO_FRAMES(3500),
};

static const u16 sWaiterHardArrivalDurationsLate[] =
{
    WAITER_MS_TO_FRAMES(2000),
    WAITER_MS_TO_FRAMES(2500),
    WAITER_MS_TO_FRAMES(2500),
    WAITER_MS_TO_FRAMES(3000),
};

// Menu Durations
// Easy
static const u16 sWaiterEasyMenuDurations[] =
{
    WAITER_MS_TO_FRAMES(2000),
    WAITER_MS_TO_FRAMES(2500),
    WAITER_MS_TO_FRAMES(2500),
    WAITER_MS_TO_FRAMES(3000),
};

// Hard
static const u16 sWaiterHardMenuDurations[] =
{
    WAITER_MS_TO_FRAMES(2000),
    WAITER_MS_TO_FRAMES(2000),
    WAITER_MS_TO_FRAMES(2500),
    WAITER_MS_TO_FRAMES(2500),
};

// Ordering Durations
// Easy
static const u16 sWaiterEasyOrderingDurations[] =
{
    WAITER_MS_TO_FRAMES(2000),
    WAITER_MS_TO_FRAMES(2000),
    WAITER_MS_TO_FRAMES(2500),
    WAITER_MS_TO_FRAMES(2500),
};

// Hard
static const u16 sWaiterHardOrderingDurations[] =
{
    WAITER_MS_TO_FRAMES(2000),
    WAITER_MS_TO_FRAMES(2000),
    WAITER_MS_TO_FRAMES(2500),
    WAITER_MS_TO_FRAMES(2500),
};

static const u16 sWaiterResultDuration = WAITER_MS_TO_FRAMES(2500);

static const struct WaiterCursorSpawn sWaiterDefaultCursorSpawn =
{
    WAITER_SPRITE_CURSOR,
    0,
    WAITER_TABLE_BOTTOM_RIGHT,
};

static const struct SpritePalette sWaiterSharedSpritePalette =
{
    .data = sWaiterSpritePalette,
    .tag = WAITER_SPRITE_PAL_TAG,
};

static const union AnimCmd sAnim_StaticFrame0[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END,
};

static const union AnimCmd sWaiterCustomerAnim_Default[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END,
};

static const union AnimCmd sWaiterCustomerAnim_Mad[] =
{
    ANIMCMD_FRAME(64, 0),
    ANIMCMD_END,
};

static const union AnimCmd sWaiterCustomerAnim_Happy[] =
{
    ANIMCMD_FRAME(128, 0),
    ANIMCMD_END,
};

static const union AnimCmd *const sStaticSpriteAnims[] =
{
    sAnim_StaticFrame0,
};

static const union AnimCmd *const sWaiterCustomerSpriteAnims[] =
{
    sWaiterCustomerAnim_Default,
    sWaiterCustomerAnim_Mad,
    sWaiterCustomerAnim_Happy,
};

static const struct OamData sWaiterCursorOam =
{
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 0,
    .bpp = ST_OAM_4BPP,
};

static const struct OamData sWaiterFrontSpriteOam =
{
    .shape = SPRITE_SHAPE(32x32),
    .size = SPRITE_SIZE(32x32),
    .priority = 0,
    .bpp = ST_OAM_4BPP,
};

static const struct OamData sWaiterCustomerSpriteOam =
{
    .shape = SPRITE_SHAPE(64x64),
    .size = SPRITE_SIZE(64x64),
    .priority = 2,
    .bpp = ST_OAM_4BPP,
};

static const struct OamData sWaiterHotDogOam =
{
    .shape = SPRITE_SHAPE(64x64),
    .size = SPRITE_SIZE(64x64),
    .priority = 0,
    .bpp = ST_OAM_4BPP,
};

void PlayPokegotchiWaiterMinigameEasy(void)
{
    VarSet(VAR_RESULT, 0);
    ScriptContext_Stop();
    OpenPokegotchiWaiterMinigame(CB2_ReturnToFieldContinueScriptPlayMapMusic, POKEGOTCHI_WAITER_MINIGAME_EASY);
}

void PlayPokegotchiWaiterMinigameHard(void)
{
    VarSet(VAR_RESULT, 0);
    ScriptContext_Stop();
    OpenPokegotchiWaiterMinigame(CB2_ReturnToFieldContinueScriptPlayMapMusic, POKEGOTCHI_WAITER_MINIGAME_HARD);
}

void OpenPokegotchiWaiterMinigame(MainCallback exitCallback, enum PokegotchiWaiterMinigameDifficulty difficulty)
{
    WaiterMinigame_Init(exitCallback, difficulty);
}

void MainCB2_InitPokegotchiWaiterMinigame(void)
{
    OpenPokegotchiWaiterMinigame(CB2_InitPokegotchiBootup, POKEGOTCHI_WAITER_MINIGAME_EASY);
}

static void WaiterMinigame_Init(MainCallback callback, enum PokegotchiWaiterMinigameDifficulty difficulty)
{
    u8 i;

    if ((sWaiterMinigame = AllocZeroed(sizeof(*sWaiterMinigame))) == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    sWaiterMinigame->savedCallback = callback;
    sWaiterMinigame->gfxLoadState = 0;
    sWaiterMinigame->controlTaskId = TASK_NONE;
    sWaiterMinigame->clockTaskId = TASK_NONE;
    sWaiterMinigame->cursorTableId = sWaiterDefaultCursorSpawn.tableId;
    sWaiterMinigame->difficulty = difficulty;
    sWaiterMinigame->clockState = WAITER_CLOCK_STATE_COUNTDOWN;
    sWaiterMinigame->countdownStep = WAITER_COUNTDOWN_STEP_THREE;
    sWaiterMinigame->countdownTimer = 0;
    sWaiterMinigame->arrivalTimer = 0;
    sWaiterMinigame->closedTimer = 0;
    sWaiterMinigame->endDelayTimer = 0;
    sWaiterMinigame->successfulServes = 0;
    sWaiterMinigame->elapsedFrames = 0;
    sWaiterMinigame->elapsedSeconds = 0;
    sWaiterMinigame->firstArrivalDone = FALSE;
    sWaiterMinigame->inputEnabled = FALSE;
    sWaiterMinigame->pendingArrival = FALSE;
    sWaiterMinigame->arrivalsStopped = FALSE;
    sWaiterMinigame->exitStarted = FALSE;
    sWaiterMinigame->windowsInitialized = FALSE;
    for (i = 0; i < WAITER_SPRITE_COUNT; i++)
        sWaiterMinigame->spriteIds[i] = MAX_SPRITES;
    for (i = 0; i < WAITER_CUSTOMER_COUNT; i++)
    {
        sWaiterMinigame->customers[i].customerSpriteId = MAX_SPRITES;
        sWaiterMinigame->customers[i].menuSpriteId = MAX_SPRITES;
        sWaiterMinigame->customers[i].hotDogSpriteId = MAX_SPRITES;
        sWaiterMinigame->customers[i].orderingSpriteId = MAX_SPRITES;
        sWaiterMinigame->customers[i].happySpriteId = MAX_SPRITES;
        sWaiterMinigame->customers[i].angrySpriteId = MAX_SPRITES;
        sWaiterMinigame->customers[i].tableId = WAITER_TABLE_COUNT;
        sWaiterMinigame->customers[i].taskId = TASK_NONE;
        sWaiterMinigame->customers[i].phase = WAITER_CUSTOMER_PHASE_INACTIVE;
        sWaiterMinigame->customers[i].phaseTimer = 0;
        sWaiterMinigame->customers[i].serveRequested = FALSE;
    }

    SetMainCallback2(WaiterMinigame_RunSetup);
}

static void WaiterMinigame_RunSetup(void)
{
    while (1)
    {
        if (WaiterMinigame_DoGfxSetup() == TRUE)
            break;
    }
}

static void WaiterMinigame_MainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void WaiterMinigame_VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void WaiterMinigame_ResetGpuRegsAndBgs(void)
{
    DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000);
}

static bool8 WaiterMinigame_DoGfxSetup(void)
{
    switch (gMain.state)
    {
    case 0:
        WaiterMinigame_ResetGpuRegsAndBgs();
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
        if (WaiterMinigame_InitBgs())
            gMain.state++;
        else
            return TRUE;
        break;
    case 3:
        if (WaiterMinigame_LoadGraphics())
            gMain.state++;
        break;
    case 4:
        WaiterMinigame_InitWindows();
        gMain.state++;
        break;
    case 5:
        if (WaiterMinigame_LoadSprites())
            gMain.state++;
        else
            return TRUE;
        break;
    case 6:
        CreateTask(Task_WaiterMinigameWaitFadeIn, 0);
        SetVBlankCallback(WaiterMinigame_VBlankCB);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    case 7:
        SetMainCallback2(WaiterMinigame_MainCB);
        return TRUE;
    }

    return FALSE;
}

static bool8 WaiterMinigame_InitBgs(void)
{
    ResetAllBgsCoordinates();
    sWaiterRoomTilemapBuffer = AllocZeroed(BG_SCREEN_SIZE);
    sWaiterTablesTilemapBuffer = AllocZeroed(BG_SCREEN_SIZE);
    if (sWaiterRoomTilemapBuffer == NULL || sWaiterTablesTilemapBuffer == NULL)
    {
        WaiterMinigame_FadeAndBail();
        return FALSE;
    }

    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sWaiterMinigameBgTemplates, ARRAY_COUNT(sWaiterMinigameBgTemplates));
    SetBgTilemapBuffer(WAITER_BG_ROOM, sWaiterRoomTilemapBuffer);
    SetBgTilemapBuffer(WAITER_BG_TABLES, sWaiterTablesTilemapBuffer);

    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);

    ShowBg(0);
    ShowBg(WAITER_BG_TABLES);
    ShowBg(WAITER_BG_ROOM);
    return TRUE;
}

static bool8 WaiterMinigame_LoadGraphics(void)
{
    switch (sWaiterMinigame->gfxLoadState)
    {
    case 0:
        LoadBgTiles(WAITER_BG_ROOM, sWaiterRoomTiles, sizeof(sWaiterRoomTiles), 0);
        sWaiterMinigame->gfxLoadState++;
        break;
    case 1:
        memcpy(sWaiterRoomTilemapBuffer, sWaiterRoomTilemap, sizeof(sWaiterRoomTilemap));
        ScheduleBgCopyTilemapToVram(WAITER_BG_ROOM);
        sWaiterMinigame->gfxLoadState++;
        break;
    case 2:
        LoadPalette(sWaiterRoomPalette, BG_PLTT_ID(WAITER_ROOM_PALETTE_SLOT), sizeof(sWaiterRoomPalette));
        sWaiterMinigame->gfxLoadState++;
        break;
    case 3:
        LoadBgTiles(WAITER_BG_TABLES, sWaiterTablesTiles, sizeof(sWaiterTablesTiles), 0);
        sWaiterMinigame->gfxLoadState++;
        break;
    case 4:
        memcpy(sWaiterTablesTilemapBuffer, sWaiterTablesTilemap, sizeof(sWaiterTablesTilemap));
        WaiterMinigame_ApplyPaletteNum(sWaiterTablesTilemapBuffer, ARRAY_COUNT(sWaiterTablesTilemap), WAITER_TABLES_PALETTE_SLOT);
        ScheduleBgCopyTilemapToVram(WAITER_BG_TABLES);
        sWaiterMinigame->gfxLoadState++;
        break;
    case 5:
        LoadPalette(sWaiterTablesPalette, BG_PLTT_ID(WAITER_TABLES_PALETTE_SLOT), sizeof(sWaiterTablesPalette));
        sWaiterMinigame->gfxLoadState++;
        break;
    case 6:
        LoadPalette(sWaiterTextPalette, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        sWaiterMinigame->gfxLoadState++;
        break;
    default:
        sWaiterMinigame->gfxLoadState = 0;
        return TRUE;
    }

    return FALSE;
}

static void WaiterMinigame_InitWindows(void)
{
    InitWindows(sWaiterWindowTemplates);
    DeactivateAllTextPrinters();
    ScheduleBgCopyTilemapToVram(0);

    FillWindowPixelBuffer(WAITER_TIMER_WINDOW, PIXEL_FILL(0));
    PutWindowTilemap(WAITER_TIMER_WINDOW);
    CopyWindowToVram(WAITER_TIMER_WINDOW, COPYWIN_FULL);

    FillWindowPixelBuffer(WAITER_COUNTDOWN_WINDOW, PIXEL_FILL(0));
    PutWindowTilemap(WAITER_COUNTDOWN_WINDOW);
    CopyWindowToVram(WAITER_COUNTDOWN_WINDOW, COPYWIN_FULL);

    sWaiterMinigame->windowsInitialized = TRUE;
}

static bool8 WaiterMinigame_LoadSprites(void)
{
    u32 i;
    u32 customerId;

    for (i = 0; i < ARRAY_COUNT(sWaiterLoadedSpriteSheetIds); i++)
    {
        if (LoadSpriteSheet(&sWaiterSpriteSheets[sWaiterLoadedSpriteSheetIds[i]]) == TAG_NONE)
        {
            WaiterMinigame_FadeAndBail();
            return FALSE;
        }
    }

    if (LoadSpritePalette(&sWaiterSharedSpritePalette) == 0xFF)
    {
        WaiterMinigame_FadeAndBail();
        return FALSE;
    }

    for (customerId = 0; customerId < WAITER_CUSTOMER_COUNT; customerId++)
    {
        const struct WaiterCustomerTemplate *template = &sWaiterCustomerTemplates[customerId];
        struct WaiterCustomerResources *customer = &sWaiterMinigame->customers[customerId];

        customer->customerSpriteId = WaiterMinigame_CreateCustomerAtTable(template->customerSheetId, WAITER_TABLE_TOP_LEFT, template->customerSubpriority);
        customer->menuSpriteId = WaiterMinigame_CreateTableItemAtTable(WAITER_SHEET_MENU, WAITER_TABLE_TOP_LEFT, template->tableItemSubpriority);
        customer->hotDogSpriteId = WaiterMinigame_CreateTableItemAtTable(WAITER_SHEET_HOT_DOG, WAITER_TABLE_TOP_LEFT, template->tableItemSubpriority);
        customer->orderingSpriteId = WaiterMinigame_CreateEmotionAtTable(WAITER_SHEET_WANT_TO_ORDER, WAITER_TABLE_TOP_LEFT, template->emotionSubpriority);
        customer->happySpriteId = WaiterMinigame_CreateEmotionAtTable(WAITER_SHEET_HAPPY, WAITER_TABLE_TOP_LEFT, template->emotionSubpriority);
        customer->angrySpriteId = WaiterMinigame_CreateEmotionAtTable(WAITER_SHEET_ANGRY, WAITER_TABLE_TOP_LEFT, template->emotionSubpriority);

        if (customer->customerSpriteId == MAX_SPRITES
         || customer->menuSpriteId == MAX_SPRITES
         || customer->hotDogSpriteId == MAX_SPRITES
         || customer->orderingSpriteId == MAX_SPRITES
         || customer->happySpriteId == MAX_SPRITES
         || customer->angrySpriteId == MAX_SPRITES)
        {
            WaiterMinigame_FadeAndBail();
            return FALSE;
        }

        WaiterMinigame_HideCustomerVisuals(customerId);
    }

    sWaiterMinigame->spriteIds[WAITER_SPRITE_CURSOR] =
        WaiterMinigame_CreateCursorAtTable(sWaiterDefaultCursorSpawn.tableId, sWaiterDefaultCursorSpawn.subpriority);
    if (sWaiterMinigame->spriteIds[WAITER_SPRITE_CURSOR] == MAX_SPRITES)
    {
        WaiterMinigame_FadeAndBail();
        return FALSE;
    }

    WaiterMinigame_SetCursorTable(sWaiterDefaultCursorSpawn.tableId);
    return TRUE;
}

static void WaiterMinigame_ApplyPaletteNum(u16 *tilemapBuffer, u32 size, u8 paletteNum)
{
    u32 i;

    for (i = 0; i < size; i++)
    {
        if (tilemapBuffer[i] != 0)
            tilemapBuffer[i] = (tilemapBuffer[i] & 0x0FFF) | (paletteNum << 12);
    }
}

static u8 WaiterMinigame_CreateCustomerAtTable(u8 sheetId, u8 tableId, u8 subpriority)
{
    const struct WaiterMinigameCoord *coords = &sWaiterCustomerCoords[tableId];
    struct SpriteTemplate spriteTemplate =
    {
        .tileTag = sWaiterSpriteSheets[sheetId].tag,
        .paletteTag = WAITER_SPRITE_PAL_TAG,
        .oam = &sWaiterCustomerSpriteOam,
        .anims = sWaiterCustomerSpriteAnims,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy,
    };

    return CreateSprite(&spriteTemplate, coords->x, coords->y, subpriority);
}

static u8 WaiterMinigame_CreateTableItemAtTable(u8 sheetId, u8 tableId, u8 subpriority)
{
    const struct WaiterMinigameCoord *coords = &sWaiterTableItemCoords[tableId];
    const struct OamData *oam = &sWaiterFrontSpriteOam;

    if (sheetId == WAITER_SHEET_HOT_DOG)
        oam = &sWaiterHotDogOam;

    return WaiterMinigame_CreateStaticSprite(&sWaiterSpriteSheets[sheetId], oam, coords->x, coords->y, subpriority);
}

static u8 WaiterMinigame_CreateEmotionAtTable(u8 sheetId, u8 tableId, u8 subpriority)
{
    const struct WaiterMinigameCoord *coords = &sWaiterEmotionCoords[tableId];

    return WaiterMinigame_CreateStaticSprite(&sWaiterSpriteSheets[sheetId], &sWaiterFrontSpriteOam, coords->x, coords->y, subpriority);
}

static u8 WaiterMinigame_CreateCursorAtTable(u8 tableId, u8 subpriority)
{
    const struct WaiterMinigameCoord *coords = &sWaiterCursorCoords[tableId];

    return WaiterMinigame_CreateStaticSprite(&sWaiterSpriteSheets[WAITER_SHEET_CURSOR], &sWaiterCursorOam, coords->x, coords->y, subpriority);
}

static u8 WaiterMinigame_CreateStaticSprite(const struct SpriteSheet *sheet, const struct OamData *oam, s16 x, s16 y, u8 subpriority)
{
    struct SpriteTemplate spriteTemplate =
    {
        .tileTag = sheet->tag,
        .paletteTag = WAITER_SPRITE_PAL_TAG,
        .oam = oam,
        .anims = sStaticSpriteAnims,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy,
    };

    return CreateSprite(&spriteTemplate, x, y, subpriority);
}

static void WaiterMinigame_SetCursorTable(u8 tableId)
{
    u8 spriteId = sWaiterMinigame->spriteIds[WAITER_SPRITE_CURSOR];
    const struct WaiterMinigameCoord *coords = &sWaiterCursorCoords[tableId];

    if (spriteId == MAX_SPRITES)
        return;

    gSprites[spriteId].x = coords->x;
    gSprites[spriteId].y = coords->y;
    sWaiterMinigame->cursorTableId = tableId;
}

static void WaiterMinigame_SetCustomerSpriteTable(u8 spriteId, u8 tableId)
{
    const struct WaiterMinigameCoord *coords = &sWaiterCustomerCoords[tableId];

    if (spriteId == MAX_SPRITES)
        return;

    gSprites[spriteId].x = coords->x;
    gSprites[spriteId].y = coords->y;
}

static void WaiterMinigame_SetTableItemSpriteTable(u8 spriteId, u8 tableId)
{
    const struct WaiterMinigameCoord *coords = &sWaiterTableItemCoords[tableId];

    if (spriteId == MAX_SPRITES)
        return;

    gSprites[spriteId].x = coords->x;
    gSprites[spriteId].y = coords->y;
}

static void WaiterMinigame_SetEmotionSpriteTable(u8 spriteId, u8 tableId)
{
    const struct WaiterMinigameCoord *coords = &sWaiterEmotionCoords[tableId];

    if (spriteId == MAX_SPRITES)
        return;

    gSprites[spriteId].x = coords->x;
    gSprites[spriteId].y = coords->y;
}

static void WaiterMinigame_SetSpriteVisibility(u8 spriteId, bool8 visible)
{
    if (spriteId == MAX_SPRITES)
        return;

    gSprites[spriteId].invisible = !visible;
}

static void WaiterMinigame_SetCustomerPose(u8 customerId, u8 pose)
{
    u8 spriteId = sWaiterMinigame->customers[customerId].customerSpriteId;

    if (spriteId == MAX_SPRITES)
        return;

    StartSpriteAnimIfDifferent(&gSprites[spriteId], pose);
}

static void WaiterMinigame_HideAllCustomers(void)
{
    u32 i;

    for (i = 0; i < WAITER_CUSTOMER_COUNT; i++)
        WaiterMinigame_HideCustomerVisuals(i);
}

static void WaiterMinigame_HideCustomerVisuals(u8 customerId)
{
    struct WaiterCustomerResources *customer = &sWaiterMinigame->customers[customerId];

    WaiterMinigame_SetSpriteVisibility(customer->customerSpriteId, FALSE);
    WaiterMinigame_SetSpriteVisibility(customer->menuSpriteId, FALSE);
    WaiterMinigame_SetSpriteVisibility(customer->hotDogSpriteId, FALSE);
    WaiterMinigame_SetSpriteVisibility(customer->orderingSpriteId, FALSE);
    WaiterMinigame_SetSpriteVisibility(customer->happySpriteId, FALSE);
    WaiterMinigame_SetSpriteVisibility(customer->angrySpriteId, FALSE);
}

static void WaiterMinigame_SetCustomerEntryTable(u8 customerId, u8 tableId)
{
    struct WaiterCustomerResources *customer = &sWaiterMinigame->customers[customerId];

    WaiterMinigame_SetCustomerSpriteTable(customer->customerSpriteId, tableId);
    WaiterMinigame_SetTableItemSpriteTable(customer->menuSpriteId, tableId);
    WaiterMinigame_SetTableItemSpriteTable(customer->hotDogSpriteId, tableId);
    WaiterMinigame_SetEmotionSpriteTable(customer->orderingSpriteId, tableId);
    WaiterMinigame_SetEmotionSpriteTable(customer->happySpriteId, tableId);
    WaiterMinigame_SetEmotionSpriteTable(customer->angrySpriteId, tableId);
    customer->tableId = tableId;
}

static void WaiterMinigame_BeginCustomerMenu(u8 customerId, u8 tableId)
{
    struct WaiterCustomerResources *customer = &sWaiterMinigame->customers[customerId];

    WaiterMinigame_SetCustomerEntryTable(customerId, tableId);
    WaiterMinigame_HideCustomerVisuals(customerId);
    WaiterMinigame_SetCustomerPose(customerId, WAITER_CUSTOMER_POSE_DEFAULT);
    WaiterMinigame_SetSpriteVisibility(customer->customerSpriteId, TRUE);
    WaiterMinigame_SetSpriteVisibility(customer->menuSpriteId, TRUE);
    customer->phase = WAITER_CUSTOMER_PHASE_MENU;
    customer->phaseTimer = WaiterMinigame_ChooseMenuDuration();
    customer->serveRequested = FALSE;
}

static void WaiterMinigame_BeginCustomerOrdering(u8 customerId)
{
    struct WaiterCustomerResources *customer = &sWaiterMinigame->customers[customerId];

    WaiterMinigame_HideCustomerVisuals(customerId);
    WaiterMinigame_SetCustomerPose(customerId, WAITER_CUSTOMER_POSE_DEFAULT);
    WaiterMinigame_SetSpriteVisibility(customer->customerSpriteId, TRUE);
    WaiterMinigame_SetSpriteVisibility(customer->orderingSpriteId, TRUE);
    customer->phase = WAITER_CUSTOMER_PHASE_ORDERING;
    customer->phaseTimer = WaiterMinigame_ChooseOrderingDuration();
    customer->serveRequested = FALSE;
}

static void WaiterMinigame_BeginCustomerSuccess(u8 customerId)
{
    struct WaiterCustomerResources *customer = &sWaiterMinigame->customers[customerId];

    WaiterMinigame_HideCustomerVisuals(customerId);
    WaiterMinigame_SetCustomerPose(customerId, WAITER_CUSTOMER_POSE_HAPPY);
    WaiterMinigame_SetSpriteVisibility(customer->customerSpriteId, TRUE);
    WaiterMinigame_SetSpriteVisibility(customer->hotDogSpriteId, TRUE);
    WaiterMinigame_SetSpriteVisibility(customer->happySpriteId, TRUE);
    customer->phase = WAITER_CUSTOMER_PHASE_RESULT_SUCCESS;
    customer->phaseTimer = sWaiterResultDuration;
    customer->serveRequested = FALSE;
    sWaiterMinigame->successfulServes++;
}

static void WaiterMinigame_BeginCustomerFailure(u8 customerId)
{
    struct WaiterCustomerResources *customer = &sWaiterMinigame->customers[customerId];

    WaiterMinigame_HideCustomerVisuals(customerId);
    WaiterMinigame_SetCustomerPose(customerId, WAITER_CUSTOMER_POSE_MAD);
    WaiterMinigame_SetSpriteVisibility(customer->customerSpriteId, TRUE);
    WaiterMinigame_SetSpriteVisibility(customer->angrySpriteId, TRUE);
    customer->phase = WAITER_CUSTOMER_PHASE_RESULT_FAIL;
    customer->phaseTimer = sWaiterResultDuration;
    customer->serveRequested = FALSE;
}

static void WaiterMinigame_FinishCustomer(u8 customerId, u8 taskId)
{
    struct WaiterCustomerResources *customer = &sWaiterMinigame->customers[customerId];

    WaiterMinigame_HideCustomerVisuals(customerId);
    customer->tableId = WAITER_TABLE_COUNT;
    customer->phase = WAITER_CUSTOMER_PHASE_INACTIVE;
    customer->phaseTimer = 0;
    customer->serveRequested = FALSE;
    customer->taskId = TASK_NONE;
    DestroyTask(taskId);

    if (sWaiterMinigame->arrivalsStopped && !WaiterMinigame_HasActiveCustomers())
        sWaiterMinigame->inputEnabled = FALSE;
}

static bool8 WaiterMinigame_HasActiveCustomers(void)
{
    u32 i;

    for (i = 0; i < WAITER_CUSTOMER_COUNT; i++)
    {
        if (sWaiterMinigame->customers[i].phase != WAITER_CUSTOMER_PHASE_INACTIVE)
            return TRUE;
    }

    return FALSE;
}

static u8 WaiterMinigame_FindCustomerAtTable(u8 tableId)
{
    u32 i;

    for (i = 0; i < WAITER_CUSTOMER_COUNT; i++)
    {
        if (sWaiterMinigame->customers[i].phase != WAITER_CUSTOMER_PHASE_INACTIVE
         && sWaiterMinigame->customers[i].tableId == tableId)
            return i;
    }

    return WAITER_CUSTOMER_COUNT;
}

static u8 WaiterMinigame_ChooseFreeCustomerId(void)
{
    u8 available[WAITER_CUSTOMER_COUNT];
    u8 count = 0;
    u8 i;

    for (i = 0; i < WAITER_CUSTOMER_COUNT; i++)
    {
        if (sWaiterMinigame->customers[i].phase == WAITER_CUSTOMER_PHASE_INACTIVE)
            available[count++] = i;
    }

    if (count == 0)
        return WAITER_CUSTOMER_COUNT;

    return available[Random() % count];
}

static u8 WaiterMinigame_ChooseFreeTable(void)
{
    u8 available[WAITER_TABLE_COUNT];
    u8 count = 0;
    u8 tableId;

    for (tableId = 0; tableId < WAITER_TABLE_COUNT; tableId++)
    {
        if (WaiterMinigame_FindCustomerAtTable(tableId) == WAITER_CUSTOMER_COUNT)
            available[count++] = tableId;
    }

    if (count == 0)
        return WAITER_TABLE_COUNT;

    return available[Random() % count];
}

static u16 WaiterMinigame_ChooseRandomDuration(const u16 *durations, u32 count)
{
    return durations[Random() % count];
}

static u16 WaiterMinigame_ChooseMenuDuration(void)
{
    if (sWaiterMinigame->difficulty == POKEGOTCHI_WAITER_MINIGAME_HARD)
        return WaiterMinigame_ChooseRandomDuration(sWaiterHardMenuDurations, ARRAY_COUNT(sWaiterHardMenuDurations));

    return WaiterMinigame_ChooseRandomDuration(sWaiterEasyMenuDurations, ARRAY_COUNT(sWaiterEasyMenuDurations));
}

static u16 WaiterMinigame_ChooseOrderingDuration(void)
{
    if (sWaiterMinigame->difficulty == POKEGOTCHI_WAITER_MINIGAME_HARD)
        return WaiterMinigame_ChooseRandomDuration(sWaiterHardOrderingDurations, ARRAY_COUNT(sWaiterHardOrderingDurations));

    return WaiterMinigame_ChooseRandomDuration(sWaiterEasyOrderingDurations, ARRAY_COUNT(sWaiterEasyOrderingDurations));
}

static void WaiterMinigame_StartEntryCountdown(void)
{
    sWaiterMinigame->clockState = WAITER_CLOCK_STATE_COUNTDOWN;
    sWaiterMinigame->countdownStep = WAITER_COUNTDOWN_STEP_THREE;
    sWaiterMinigame->countdownTimer = WAITER_COUNTDOWN_STAGE_FRAMES;
    sWaiterMinigame->arrivalTimer = 0;
    sWaiterMinigame->closedTimer = 0;
    sWaiterMinigame->endDelayTimer = 0;
    sWaiterMinigame->elapsedFrames = 0;
    sWaiterMinigame->elapsedSeconds = 0;
    sWaiterMinigame->firstArrivalDone = FALSE;
    sWaiterMinigame->inputEnabled = FALSE;
    sWaiterMinigame->pendingArrival = FALSE;
    sWaiterMinigame->arrivalsStopped = FALSE;
    sWaiterMinigame->successfulServes = 0;
    sWaiterMinigame->exitStarted = FALSE;
    WaiterMinigame_HideAllCustomers();
    WaiterMinigame_ClearTimerText();
    WaiterMinigame_PrintCountdownText(sText_WaiterCountdown3);
}

static void WaiterMinigame_StartArrivalTimer(void)
{
    if (sWaiterMinigame->arrivalsStopped)
        return;

    if (!sWaiterMinigame->firstArrivalDone)
    {
        sWaiterMinigame->arrivalTimer = WaiterMinigame_ChooseRandomDuration(sWaiterArrivalDurationsFirst, ARRAY_COUNT(sWaiterArrivalDurationsFirst));
    }
    else if (sWaiterMinigame->elapsedSeconds < 20)
    {
        if (sWaiterMinigame->difficulty == POKEGOTCHI_WAITER_MINIGAME_HARD)
            sWaiterMinigame->arrivalTimer = WaiterMinigame_ChooseRandomDuration(sWaiterHardArrivalDurationsStandard, ARRAY_COUNT(sWaiterHardArrivalDurationsStandard));
        else
            sWaiterMinigame->arrivalTimer = WaiterMinigame_ChooseRandomDuration(sWaiterEasyArrivalDurationsStandard, ARRAY_COUNT(sWaiterEasyArrivalDurationsStandard));
    }
    else if (sWaiterMinigame->elapsedSeconds < 40)
    {
        if (sWaiterMinigame->difficulty == POKEGOTCHI_WAITER_MINIGAME_HARD)
            sWaiterMinigame->arrivalTimer = WaiterMinigame_ChooseRandomDuration(sWaiterHardArrivalDurationsMid, ARRAY_COUNT(sWaiterHardArrivalDurationsMid));
        else
            sWaiterMinigame->arrivalTimer = WaiterMinigame_ChooseRandomDuration(sWaiterEasyArrivalDurationsMid, ARRAY_COUNT(sWaiterEasyArrivalDurationsMid));
    }
    else
    {
        if (sWaiterMinigame->difficulty == POKEGOTCHI_WAITER_MINIGAME_HARD)
            sWaiterMinigame->arrivalTimer = WaiterMinigame_ChooseRandomDuration(sWaiterHardArrivalDurationsLate, ARRAY_COUNT(sWaiterHardArrivalDurationsLate));
        else
            sWaiterMinigame->arrivalTimer = WaiterMinigame_ChooseRandomDuration(sWaiterEasyArrivalDurationsLate, ARRAY_COUNT(sWaiterEasyArrivalDurationsLate));
    }
}

static bool8 WaiterMinigame_SpawnCustomer(void)
{
    u8 customerId;
    u8 tableId;
    u8 taskId;

    if (sWaiterMinigame->arrivalsStopped)
        return FALSE;

    customerId = WaiterMinigame_ChooseFreeCustomerId();
    tableId = WaiterMinigame_ChooseFreeTable();
    if (customerId == WAITER_CUSTOMER_COUNT || tableId == WAITER_TABLE_COUNT)
        return FALSE;

    taskId = CreateTask(Task_WaiterMinigameCustomer, WAITER_CUSTOMER_TASK_PRIORITY);
    if (taskId == TASK_NONE)
        return FALSE;

    sWaiterMinigame->customers[customerId].taskId = taskId;
    gTasks[taskId].data[0] = customerId;
    WaiterMinigame_BeginCustomerMenu(customerId, tableId);
    sWaiterMinigame->firstArrivalDone = TRUE;
    return TRUE;
}

static void WaiterMinigame_PrintTimer(void)
{
    u8 text[8];
    u8 x;

    FillWindowPixelBuffer(WAITER_TIMER_WINDOW, PIXEL_FILL(0));
    ConvertIntToDecimalStringN(text, sWaiterMinigame->elapsedSeconds, STR_CONV_MODE_LEADING_ZEROS, 2);
    x = GetStringRightAlignXOffset(FONT_NORMAL, text, sWaiterWindowTemplates[WAITER_TIMER_WINDOW].width * 8) - WAITER_TIMER_RIGHT_PADDING;
    AddTextPrinterParameterized3(WAITER_TIMER_WINDOW,
                                 FONT_NORMAL,
                                 x,
                                 0,
                                 sWaiterWindowFontColors[WAITER_FONT_BLACK],
                                 TEXT_SKIP_DRAW,
                                 text);
    CopyWindowToVram(WAITER_TIMER_WINDOW, COPYWIN_FULL);
}

static void WaiterMinigame_PrintClosed(void)
{
    u8 x = GetStringRightAlignXOffset(FONT_NORMAL, sText_WaiterClosed, sWaiterWindowTemplates[WAITER_TIMER_WINDOW].width * 8) - WAITER_TIMER_RIGHT_PADDING;

    FillWindowPixelBuffer(WAITER_TIMER_WINDOW, PIXEL_FILL(0));
    AddTextPrinterParameterized3(WAITER_TIMER_WINDOW,
                                 FONT_NORMAL,
                                 x,
                                 0,
                                 sWaiterWindowFontColors[WAITER_FONT_BLACK],
                                 TEXT_SKIP_DRAW,
                                 sText_WaiterClosed);
    CopyWindowToVram(WAITER_TIMER_WINDOW, COPYWIN_FULL);
}

static void WaiterMinigame_PrintCountdownText(const u8 *text)
{
    u8 x = GetStringCenterAlignXOffset(FONT_NORMAL, text, sWaiterWindowTemplates[WAITER_COUNTDOWN_WINDOW].width * 8);

    FillWindowPixelBuffer(WAITER_COUNTDOWN_WINDOW, PIXEL_FILL(0));
    AddTextPrinterParameterized3(WAITER_COUNTDOWN_WINDOW,
                                 FONT_NORMAL,
                                 x,
                                 8,
                                 sWaiterWindowFontColors[WAITER_FONT_BLACK],
                                 TEXT_SKIP_DRAW,
                                 text);
    CopyWindowToVram(WAITER_COUNTDOWN_WINDOW, COPYWIN_FULL);
}

static void WaiterMinigame_ClearCountdownText(void)
{
    FillWindowPixelBuffer(WAITER_COUNTDOWN_WINDOW, PIXEL_FILL(0));
    CopyWindowToVram(WAITER_COUNTDOWN_WINDOW, COPYWIN_FULL);
}

static void WaiterMinigame_ClearTimerText(void)
{
    FillWindowPixelBuffer(WAITER_TIMER_WINDOW, PIXEL_FILL(0));
    CopyWindowToVram(WAITER_TIMER_WINDOW, COPYWIN_FULL);
}

static void WaiterMinigame_UpdateCountdown(void)
{
    if (sWaiterMinigame->countdownStep == WAITER_COUNTDOWN_STEP_DONE)
        return;

    if (sWaiterMinigame->countdownTimer > 0)
        sWaiterMinigame->countdownTimer--;

    if (sWaiterMinigame->countdownTimer != 0)
        return;

    switch (sWaiterMinigame->countdownStep)
    {
    case WAITER_COUNTDOWN_STEP_THREE:
        sWaiterMinigame->countdownStep = WAITER_COUNTDOWN_STEP_TWO;
        sWaiterMinigame->countdownTimer = WAITER_COUNTDOWN_STAGE_FRAMES;
        WaiterMinigame_PrintCountdownText(sText_WaiterCountdown2);
        break;
    case WAITER_COUNTDOWN_STEP_TWO:
        sWaiterMinigame->countdownStep = WAITER_COUNTDOWN_STEP_ONE;
        sWaiterMinigame->countdownTimer = WAITER_COUNTDOWN_STAGE_FRAMES;
        WaiterMinigame_PrintCountdownText(sText_WaiterCountdown1);
        break;
    case WAITER_COUNTDOWN_STEP_ONE:
        sWaiterMinigame->countdownStep = WAITER_COUNTDOWN_STEP_START;
        sWaiterMinigame->countdownTimer = WAITER_COUNTDOWN_STAGE_FRAMES;
        sWaiterMinigame->inputEnabled = TRUE;
        sWaiterMinigame->elapsedFrames = 0;
        sWaiterMinigame->elapsedSeconds = 0;
        WaiterMinigame_PrintCountdownText(sText_WaiterCountdownStart);
        WaiterMinigame_PrintTimer();
        sWaiterMinigame->clockState = WAITER_CLOCK_STATE_RUNNING;
        WaiterMinigame_StartArrivalTimer();
        break;
    case WAITER_COUNTDOWN_STEP_START:
        sWaiterMinigame->countdownStep = WAITER_COUNTDOWN_STEP_DONE;
        WaiterMinigame_ClearCountdownText();
        break;
    case WAITER_COUNTDOWN_STEP_DONE:
        break;
    }
}

static void WaiterMinigame_UpdateElapsedTimer(void)
{
    if (sWaiterMinigame->countdownStep < WAITER_COUNTDOWN_STEP_START)
        return;
    if (sWaiterMinigame->clockState == WAITER_CLOCK_STATE_STOPPED)
        return;
    if (sWaiterMinigame->clockState == WAITER_CLOCK_STATE_CLOSING)
    {
        if (sWaiterMinigame->closedTimer > 0)
            sWaiterMinigame->closedTimer--;
        if (sWaiterMinigame->closedTimer == 0)
        {
            WaiterMinigame_PrintClosed();
            sWaiterMinigame->clockState = WAITER_CLOCK_STATE_STOPPED;
        }
        return;
    }

    sWaiterMinigame->elapsedFrames++;
    if (sWaiterMinigame->elapsedFrames < WAITER_FRAMES_PER_SECOND)
        return;

    sWaiterMinigame->elapsedFrames = 0;
    if (sWaiterMinigame->elapsedSeconds < WAITER_GAME_DURATION_SECONDS)
        sWaiterMinigame->elapsedSeconds++;
    WaiterMinigame_PrintTimer();

    if (sWaiterMinigame->elapsedSeconds >= WAITER_GAME_DURATION_SECONDS)
    {
        sWaiterMinigame->clockState = WAITER_CLOCK_STATE_CLOSING;
        sWaiterMinigame->arrivalsStopped = TRUE;
        sWaiterMinigame->pendingArrival = FALSE;
        sWaiterMinigame->arrivalTimer = 0;
        sWaiterMinigame->closedTimer = WAITER_FRAMES_PER_SECOND;
        sWaiterMinigame->inputEnabled = WaiterMinigame_HasActiveCustomers();
    }
}

static void WaiterMinigame_UpdateArrivals(void)
{
    if (sWaiterMinigame->clockState != WAITER_CLOCK_STATE_RUNNING || sWaiterMinigame->arrivalsStopped)
        return;

    if (sWaiterMinigame->pendingArrival)
    {
        if (WaiterMinigame_SpawnCustomer())
        {
            sWaiterMinigame->pendingArrival = FALSE;
            WaiterMinigame_StartArrivalTimer();
        }
        return;
    }

    if (sWaiterMinigame->arrivalTimer > 0)
        sWaiterMinigame->arrivalTimer--;

    if (sWaiterMinigame->arrivalTimer != 0)
        return;

    if (WaiterMinigame_SpawnCustomer())
        WaiterMinigame_StartArrivalTimer();
    else
        sWaiterMinigame->pendingArrival = TRUE;
}

static void WaiterMinigame_UpdateEndSequence(void)
{
    u16 coinsToAward;

    if (sWaiterMinigame->exitStarted)
        return;
    if (sWaiterMinigame->clockState != WAITER_CLOCK_STATE_STOPPED)
        return;
    if (!sWaiterMinigame->arrivalsStopped || WaiterMinigame_HasActiveCustomers())
        return;

    if (sWaiterMinigame->endDelayTimer == 0)
    {
        sWaiterMinigame->endDelayTimer = WAITER_END_DELAY_FRAMES;
        return;
    }

    sWaiterMinigame->endDelayTimer--;
    if (sWaiterMinigame->endDelayTimer != 0)
        return;

    coinsToAward = sWaiterMinigame->successfulServes * WAITER_COINS_PER_SERVE;
    AddCoins(coinsToAward);
    VarSet(VAR_RESULT, sWaiterMinigame->successfulServes);
    sWaiterMinigame->exitStarted = TRUE;
    WaiterMinigame_FadeAndBail();
}

static u8 WaiterMinigame_GetAdjacentTable(u8 tableId, u16 direction)
{
    u8 row = tableId / 3;
    u8 column = tableId % 3;

    switch (direction)
    {
    case DPAD_LEFT:
        if (column > 0)
            tableId--;
        break;
    case DPAD_RIGHT:
        if (column < 2)
            tableId++;
        break;
    case DPAD_UP:
        if (row > 0)
            tableId -= 3;
        break;
    case DPAD_DOWN:
        if (row < 1)
            tableId += 3;
        break;
    }

    return tableId;
}

#define try_free(ptr) ({      \
    void **ptr__ = (void **)&(ptr); \
    if (*ptr__ != NULL)       \
        Free(*ptr__);         \
})

static void WaiterMinigame_FreeResources(void)
{
    u32 i;
    u32 customerId;

    if (sWaiterMinigame != NULL)
    {
        for (customerId = 0; customerId < WAITER_CUSTOMER_COUNT; customerId++)
        {
            struct WaiterCustomerResources *customer = &sWaiterMinigame->customers[customerId];

            if (customer->taskId != TASK_NONE && gTasks[customer->taskId].isActive)
                DestroyTask(customer->taskId);

            if (customer->customerSpriteId != MAX_SPRITES)
                DestroySprite(&gSprites[customer->customerSpriteId]);
            if (customer->menuSpriteId != MAX_SPRITES)
                DestroySprite(&gSprites[customer->menuSpriteId]);
            if (customer->hotDogSpriteId != MAX_SPRITES)
                DestroySprite(&gSprites[customer->hotDogSpriteId]);
            if (customer->orderingSpriteId != MAX_SPRITES)
                DestroySprite(&gSprites[customer->orderingSpriteId]);
            if (customer->happySpriteId != MAX_SPRITES)
                DestroySprite(&gSprites[customer->happySpriteId]);
            if (customer->angrySpriteId != MAX_SPRITES)
                DestroySprite(&gSprites[customer->angrySpriteId]);
        }

        for (i = 0; i < WAITER_SPRITE_COUNT; i++)
        {
            if (sWaiterMinigame->spriteIds[i] != MAX_SPRITES)
            {
                DestroySprite(&gSprites[sWaiterMinigame->spriteIds[i]]);
                sWaiterMinigame->spriteIds[i] = MAX_SPRITES;
            }
        }

        if (sWaiterMinigame->controlTaskId != TASK_NONE && FuncIsActiveTask(Task_WaiterMinigameMain))
            DestroyTask(sWaiterMinigame->controlTaskId);
        if (sWaiterMinigame->clockTaskId != TASK_NONE && FuncIsActiveTask(Task_WaiterMinigameClock))
            DestroyTask(sWaiterMinigame->clockTaskId);
        if (sWaiterMinigame->windowsInitialized)
        {
            DeactivateAllTextPrinters();
            ClearWindowTilemap(WAITER_TIMER_WINDOW);
            ClearWindowTilemap(WAITER_COUNTDOWN_WINDOW);
            RemoveWindow(WAITER_COUNTDOWN_WINDOW);
            RemoveWindow(WAITER_TIMER_WINDOW);
            FreeAllWindowBuffers();
        }
    }

    for (i = 0; i < ARRAY_COUNT(sWaiterSpriteSheets); i++)
        FreeSpriteTilesByTag(sWaiterSpriteSheets[i].tag);
    FreeSpritePaletteByTag(WAITER_SPRITE_PAL_TAG);

    try_free(sWaiterMinigame);
    try_free(sWaiterRoomTilemapBuffer);
    try_free(sWaiterTablesTilemapBuffer);
}

static void Task_WaiterMinigameWaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sWaiterMinigame->savedCallback);
        WaiterMinigame_FreeResources();
        DestroyTask(taskId);
    }
}

static void WaiterMinigame_FadeAndBail(void)
{
    if (sWaiterMinigame == NULL)
        return;

    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_WaiterMinigameWaitFadeAndBail, 0);
    SetVBlankCallback(WaiterMinigame_VBlankCB);
    SetMainCallback2(WaiterMinigame_MainCB);
}

static void Task_WaiterMinigameWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        sWaiterMinigame->controlTaskId = taskId;
        WaiterMinigame_StartEntryCountdown();
        sWaiterMinigame->clockTaskId = CreateTask(Task_WaiterMinigameClock, 1);
        gTasks[taskId].func = Task_WaiterMinigameMain;
    }
}

static void Task_WaiterMinigameMain(u8 taskId)
{
    u8 customerId;
    u8 nextTableId;

    (void)taskId;

    if (!sWaiterMinigame->inputEnabled)
        return;

    nextTableId = sWaiterMinigame->cursorTableId;
    if (JOY_NEW(DPAD_LEFT))
        nextTableId = WaiterMinigame_GetAdjacentTable(nextTableId, DPAD_LEFT);
    else if (JOY_NEW(DPAD_RIGHT))
        nextTableId = WaiterMinigame_GetAdjacentTable(nextTableId, DPAD_RIGHT);
    else if (JOY_NEW(DPAD_UP))
        nextTableId = WaiterMinigame_GetAdjacentTable(nextTableId, DPAD_UP);
    else if (JOY_NEW(DPAD_DOWN))
        nextTableId = WaiterMinigame_GetAdjacentTable(nextTableId, DPAD_DOWN);

    if (nextTableId != sWaiterMinigame->cursorTableId)
        WaiterMinigame_SetCursorTable(nextTableId);

    if (JOY_NEW(A_BUTTON))
    {
        customerId = WaiterMinigame_FindCustomerAtTable(sWaiterMinigame->cursorTableId);
        if (customerId != WAITER_CUSTOMER_COUNT)
            sWaiterMinigame->customers[customerId].serveRequested = TRUE;
    }
}

static void Task_WaiterMinigameClock(u8 taskId)
{
    (void)taskId;

    WaiterMinigame_UpdateCountdown();
    WaiterMinigame_UpdateElapsedTimer();
    WaiterMinigame_UpdateArrivals();
    WaiterMinigame_UpdateEndSequence();
}

static void Task_WaiterMinigameCustomer(u8 taskId)
{
    u8 customerId = gTasks[taskId].data[0];
    struct WaiterCustomerResources *customer = &sWaiterMinigame->customers[customerId];

    switch (customer->phase)
    {
    case WAITER_CUSTOMER_PHASE_MENU:
        if (customer->serveRequested)
        {
            WaiterMinigame_BeginCustomerFailure(customerId);
            break;
        }
        if (customer->phaseTimer > 0)
            customer->phaseTimer--;
        if (customer->phaseTimer == 0)
            WaiterMinigame_BeginCustomerOrdering(customerId);
        break;
    case WAITER_CUSTOMER_PHASE_ORDERING:
        if (customer->serveRequested)
        {
            WaiterMinigame_BeginCustomerSuccess(customerId);
            break;
        }
        if (customer->phaseTimer > 0)
            customer->phaseTimer--;
        if (customer->phaseTimer == 0)
            WaiterMinigame_BeginCustomerFailure(customerId);
        break;
    case WAITER_CUSTOMER_PHASE_RESULT_SUCCESS:
    case WAITER_CUSTOMER_PHASE_RESULT_FAIL:
        customer->serveRequested = FALSE;
        if (customer->phaseTimer > 0)
            customer->phaseTimer--;
        if (customer->phaseTimer == 0)
            WaiterMinigame_FinishCustomer(customerId, taskId);
        break;
    case WAITER_CUSTOMER_PHASE_INACTIVE:
    default:
        customer->taskId = TASK_NONE;
        DestroyTask(taskId);
        break;
    }
}
