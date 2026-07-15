static const u8 sPokegotchiSpriteGfx_Fomantis_Idle[] =
    INCGFX_U8("graphics/pokegotchi_mons/fomantis/idle.png", ".4bpp");
static const u16 sPokegotchiSpritePal_Fomantis_Idle[] =
    INCGFX_U16("graphics/pokegotchi_mons/fomantis/idle.png", ".gbapal");
static const u8 sPokegotchiSpriteGfx_Fomantis_Happy[] =
    INCGFX_U8("graphics/pokegotchi_mons/fomantis/happy.png", ".4bpp");
static const u16 sPokegotchiSpritePal_Fomantis_Happy[] =
    INCGFX_U16("graphics/pokegotchi_mons/fomantis/happy.png", ".gbapal");
static const u8 sPokegotchiSpriteGfx_Fomantis_Sad[] =
    INCGFX_U8("graphics/pokegotchi_mons/fomantis/sad.png", ".4bpp");
static const u16 sPokegotchiSpritePal_Fomantis_Sad[] =
    INCGFX_U16("graphics/pokegotchi_mons/fomantis/sad.png", ".gbapal");
static const u8 sPokegotchiSpriteGfx_Fomantis_Angry[] =
    INCGFX_U8("graphics/pokegotchi_mons/fomantis/angry.png", ".4bpp");
static const u16 sPokegotchiSpritePal_Fomantis_Angry[] =
    INCGFX_U16("graphics/pokegotchi_mons/fomantis/angry.png", ".gbapal");
static const u8 sPokegotchiSpriteGfx_Fomantis_Eating[] =
    INCGFX_U8("graphics/pokegotchi_mons/fomantis/eating.png", ".4bpp");
static const u16 sPokegotchiSpritePal_Fomantis_Eating[] =
    INCGFX_U16("graphics/pokegotchi_mons/fomantis/eating.png", ".gbapal");
static const u8 sPokegotchiSpriteGfx_Fomantis_Sleeping[] =
    INCGFX_U8("graphics/pokegotchi_mons/fomantis/sleeping.png", ".4bpp");
static const u16 sPokegotchiSpritePal_Fomantis_Sleeping[] =
    INCGFX_U16("graphics/pokegotchi_mons/fomantis/sleeping.png", ".gbapal");

static const struct PokegotchiEmotionGraphics sPokegotchiEmotionGfx_Fomantis[POKEGOTCHI_EMOTION_COUNT] =
{
    [POKEGOTCHI_EMOTION_IDLE] =
    {
        .spriteTiles = sPokegotchiSpriteGfx_Fomantis_Idle,
        .palette = sPokegotchiSpritePal_Fomantis_Idle,
    },
    [POKEGOTCHI_EMOTION_HAPPY] =
    {
        .spriteTiles = sPokegotchiSpriteGfx_Fomantis_Happy,
        .palette = sPokegotchiSpritePal_Fomantis_Happy,
    },
    [POKEGOTCHI_EMOTION_SAD] =
    {
        .spriteTiles = sPokegotchiSpriteGfx_Fomantis_Sad,
        .palette = sPokegotchiSpritePal_Fomantis_Sad,
    },
    [POKEGOTCHI_EMOTION_ANGRY] =
    {
        .spriteTiles = sPokegotchiSpriteGfx_Fomantis_Angry,
        .palette = sPokegotchiSpritePal_Fomantis_Angry,
    },
    [POKEGOTCHI_EMOTION_EATING] =
    {
        .spriteTiles = sPokegotchiSpriteGfx_Fomantis_Eating,
        .palette = sPokegotchiSpritePal_Fomantis_Eating,
    },
    [POKEGOTCHI_EMOTION_SLEEPING] =
    {
        .spriteTiles = sPokegotchiSpriteGfx_Fomantis_Sleeping,
        .palette = sPokegotchiSpritePal_Fomantis_Sleeping,
    },
};

static const struct PokegotchiSpeciesGraphics sPokegotchiSpeciesGfx[] =
{
    {
        .species = SPECIES_FOMANTIS,
        .emotions = sPokegotchiEmotionGfx_Fomantis,
    },
};
