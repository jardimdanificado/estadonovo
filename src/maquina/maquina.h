//MAQUINA
//AKA MQEngine

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>

//RAYLIB
#include "raylib/raylib.h"
#include "raylib/raymath.h"

//ABIN Files
#include "abin.h"

//-----------------------------------
//COLORS
//-----------------------------------

#define COR_VERMELHO CLITERAL(Color){235, 64, 52,255}
#define COR_SELECIONADO   CLITERAL(Color){202,137,109,255}
#define COR_SELECIONADO2 CLITERAL(Color){145, 39, 32,255}
#define COR_PRETO CLITERAL(Color){31, 9, 7,255}
#define COR_VAZIO   CLITERAL(Color){55,55,55,255}
#define COR_BRANCO   CLITERAL(Color){250,239,229,255}
#define COR_CINZA   CLITERAL(Color){115,105,97,255}
#define COR_LARANJA   CLITERAL(Color){202,137,109,255}

#define COR_PELE0 CLITERAL(Color){240, 199, 156,255}
#define COR_ROUPA0 CLITERAL(Color){103, 122, 137,255}
#define COR_ROUPA1 CLITERAL(Color){110, 125, 103,255}

#define MQTrue __INT_MAX__
#define MQFalse MQTrue*(-1)

#define MAXOBJ 64

unsigned int MAXANIM = 1;

#define MQEmptyVec3 (Vector3){MQTrue,MQTrue,MQTrue}
#define MQEmptyHitbox (BoundingBox){MQEmptyVec3,MQEmptyVec3}

//Necessary to MQMenu()
//If set it to true the loop will end and game will close
bool MQExit = false;

//-----------------------------------
//CONFIG
//-----------------------------------

const char* MQTitle = "Estado Novo";
const char* MQSubTitle = "Uma obra por Jardel Torres";
int MQScreenX = 600;
int MQScreenY = 400;
bool MQMSAAX4 = false;
bool MQResizeble = false;

//-----------------------------------
//DATA_FILE
//-----------------------------------

struct MQDATA_FILE_MODEL
{
    Model model;
    ModelAnimation *anim;
    char name[255];
};
typedef struct MQDATA_FILE_MODEL MQDATA_FILE_MODEL;

struct MQDATA_FILE_HITBOX
{
    BoundingBox hitbox;
    char name[255];
};
typedef struct MQDATA_FILE_HITBOX MQDATA_FILE_HITBOX;

struct MQDATA_FILE_FONT
{
    Font font;
    char name[255];
};
typedef struct MQDATA_FILE_FONT MQDATA_FILE_FONT;

struct MQDATA_FILE_TEXT
{
    char text[255];
    char name[255];
};
typedef struct MQDATA_FILE_TEXT MQDATA_FILE_TEXT;

struct MQDATA_FILE_MUSIC
{
    Music music;
    char name[255];
};
typedef struct MQDATA_FILE_MUSIC MQDATA_FILE_MUSIC;

struct MQDATA_FILE_SOUND
{
    Sound sound;
    char name[255];
};
typedef struct MQDATA_FILE_SOUND MQDATA_FILE_SOUND;

struct MQDATA_FILES
{
    MQDATA_FILE_MODEL models[MAXOBJ];
    MQDATA_FILE_HITBOX hitboxes[MAXOBJ];
    MQDATA_FILE_HITBOX eventboxes[MAXOBJ];
    MQDATA_FILE_FONT fonts[MAXOBJ];
    MQDATA_FILE_TEXT texts[MAXOBJ];
    MQDATA_FILE_TEXT langs[MAXOBJ];
    MQDATA_FILE_MUSIC musics[MAXOBJ];
    MQDATA_FILE_SOUND sounds[MAXOBJ];
};
typedef struct MQDATA_FILES MQDATA_FILES;

//-----------------------------------
//DATA_SESSION
//-----------------------------------

struct MQDATA_RENDER_MODEL
{
    bool visible, playing, reverse;
    int modelIndex;
    int currentAnim;
    int currentFrame;
    Color color;
    Vector3 position;
    float rotation;
    char *name;
};
typedef struct MQDATA_RENDER_MODEL MQDATA_RENDER_MODEL;
#define MQEmptyRenderModel(MQDATA_RENDER_MODEL){false,false,false,MQTrue,MQTrue,MQTrue,PINK,MQCreateEmptyVec3(),MQTrue," "};

struct MQDATA_RENDER_TEXT
{
    bool visible;
    int textIndex;
    Vector2 position;
    Color color;
    char* string;
    int fontSize;
    int fontIndex;
    char *name;
};
typedef struct MQDATA_RENDER_TEXT MQDATA_RENDER_TEXT;
#define MQEmptyRenderText(MQDATA_RENDER_TEXT){false,MQTrue,MQEmptyVec3,PINK," ",MQTrue,MQTrue," "};

struct MQDATA_SESSION_RENDER
{
    MQDATA_RENDER_MODEL model[MAXOBJ];
    MQDATA_RENDER_TEXT text[MAXOBJ];
    Color background;
    Camera camera;
};
typedef struct MQDATA_SESSION_RENDER MQDATA_SESSION_RENDER;

struct MQDATA_SESSION
{
    long int frame;
    MQDATA_SESSION_RENDER render;
};
typedef struct MQDATA_SESSION MQDATA_SESSION;

//-----------------------------------
//DATA_GAME
//-----------------------------------

    //-----------------------------------
    //GAME_ITEM
    //-----------------------------------

struct MQDATA_GAME_ITEM
{
    char *name;
    char *type;
    int index;
    float content;
    float condition;
    int function;
    bool active;
    bool locked;
    BoundingBox hitbox;
    Vector3 position;
    float rotation;
};
typedef struct MQDATA_GAME_ITEM MQDATA_GAME_ITEM;
#define MQEmptyRenderItem(MQDATA_GAME_ITEM){" "," ",MQTrue,MQTrue,MQTrue,MQTrue,false,false,MQEmptyHitbox,MQEmptyVec3,MQTrue};

    //-----------------------------------
    //GAME_MAP
    //-----------------------------------

struct MQDATA_GAME_EVENT
{
    bool active;
    bool persistent;
    int function;
    BoundingBox hitbox;
    Vector3 position;
    float rotation;
    char *name;
};
typedef struct MQDATA_GAME_EVENT MQDATA_GAME_EVENT;

struct MQDATA_GAME_MAP
{
    MQDATA_GAME_ITEM item[MAXOBJ];
};
typedef struct MQDATA_GAME_MAP MQDATA_GAME_MAP;

    //-----------------------------------
    //DATA_PLAYER
    //-----------------------------------

struct MQDATA_PLAYER_INVENTORY
{
    MQDATA_GAME_ITEM equip[MAXOBJ];
    MQDATA_GAME_ITEM item[MAXOBJ];
};
typedef struct MQDATA_PLAYER_INVENTORY MQDATA_PLAYER_INVENTORY;

struct MQDATA_PLAYER
{
    MQDATA_PLAYER_INVENTORY inventory;
    float speed;
    int fallTime;
    Vector3 position;
    float rotation;
};
typedef struct MQDATA_PLAYER MQDATA_PLAYER;

struct MQDATA_WALLEXCLUDE
{
    char*name;
    bool exclude;
    int index;
};
typedef struct MQDATA_WALLEXCLUDE MQDATA_WALLEXCLUDE;

struct MQDATA_GAME_OTHER
{
    MQDATA_WALLEXCLUDE wallexclude[MAXOBJ];
};
typedef struct MQDATA_GAME_OTHER MQDATA_GAME_OTHER;

struct MQDATA_GAME
{
    MQDATA_GAME_EVENT event[MAXOBJ];
    MQDATA_GAME_MAP map;
    MQDATA_PLAYER player[MAXOBJ];
    MQDATA_GAME_OTHER other;
};
typedef struct MQDATA_GAME MQDATA_GAME;

//-----------------------------------
//DATA
//-----------------------------------

struct MQDATA
{
    MQDATA_FILES files;
    MQDATA_SESSION session;
    MQDATA_GAME game;
};
typedef struct MQDATA MQDATA;



#include "maquina.c"
