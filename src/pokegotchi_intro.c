#include "global.h"
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
#include "util.h"
#include "title_screen.h"
#include "constants/field_weather.h"
#include "constants/rgb.h"
#include "pokemon.h"
#include "pokegotchi.h"
#include "pokegotchi_house.h"

static void MainCB2_PokeGotchiIntro(void);
static void MainCB2_EndPokeGotchiIntro(void);
static void VBlankCB_PokeGotchiIntro(void);
static void Task_LoadIntro(u8 taskId);
static void Task_FadeInIntro(u8 taskId);
static void Task_Wait(u8 taskId);

COMMON_DATA s32 gPokeGotchiIntroFrameCounter = 0;

void CB2_InitPokegotchiBootup(void)
{
    CreateTask(Task_LoadIntro, 0);
    SetVBlankCallback(VBlankCB_PokeGotchiIntro);
    SetMainCallback2(MainCB2_PokeGotchiIntro);
    SetSaveBlocksPointers(GetSaveBlocksPointersBaseOffset());
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
    if (gMain.newKeys != 0 && !gPaletteFade.active)
    {
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        SetMainCallback2(MainCB2_EndPokeGotchiIntro);
    }
    else if (gPokeGotchiIntroFrameCounter != -1)
        gPokeGotchiIntroFrameCounter++;
}

static void MainCB2_EndPokeGotchiIntro(void)
{
    if (!UpdatePaletteFade())
        SetMainCallback2(MainCB2_InitPokegotchiHouseMenu);
}

static void VBlankCB_PokeGotchiIntro(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void Task_LoadIntro(u8 taskId)
{
    gTasks[taskId].func = Task_FadeInIntro;
}

static void Task_FadeInIntro(u8 taskId)
{
    gTasks[taskId].func = Task_Wait;
    gPokeGotchiIntroFrameCounter = 0;
    ResetSerial();
}

static void Task_Wait(u8 taskId)
{
}
