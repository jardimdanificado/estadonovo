


#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

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

#define MQFALSE __INT_MAX__*(-1)
#define MQTRUE __INT_MAX__

#define MAXOBJ 64

unsigned int MAXANIM = 1;

bool MQEXIT = false;

//-----------------------------------
//ENVIROMENT
//-----------------------------------

//-----------------------------------
//MENU
//-----------------------------------

//-----------------------------------
//DOORS
//-----------------------------------

struct PORTA_UNI
{
    bool aberta, abrindo, fechando, trancada, existe, invertido;
    int frame;
    Vector3 posicao;
    clock_t relogioVelho, relogioNovo;
};
typedef struct PORTA_UNI PORTA_UNI;

struct PORTA
{
    PORTA_UNI slots[MAXOBJ];
};
typedef struct PORTA PORTA;

//-----------------------------------
//MAP & BULLETS
//-----------------------------------

struct MAPA_ITEM
{
    Model modelo;
    BoundingBox hitbox;
    bool pegou;
    int tipo;
    int municao, municaoMax;
    //tipos
    //0 - calca
    //1 - chapeu
    //2 - camisa
    //3 - sapatos
    //4 - oculos
    //5 - arma
    int ponteiro;
};
typedef struct MAPA_ITEM MAPA_ITEM;

struct MAPA_PROPS
{
    Model modelo;
    BoundingBox hitbox;
};
typedef struct MAPA_PROPS MAPA_PROPS;

struct MAPA_DROPS
{
    Model modelo;
    bool ocupado;
    Vector3 posicao;
    BoundingBox hitbox;
    int tipo, ponteiro;
};
typedef struct MAPA_DROPS MAPA_DROPS;

struct BALAS_MAPA
{
    Vector3 posicao;
    int rotacao;
    bool existe, parou;
    float velocidade;
    BoundingBox hitbox;
    clock_t relogio, relogioCriado;
};
typedef struct BALAS_MAPA BALAS_MAPA;

struct BALAS_GLOBALVAR
{
    Model modelo;
    bool todasBalasUsadas;
};
typedef struct BALAS_GLOBALVAR BALAS_GLOBALVAR;

struct MAPA
{
    Model modelo[MAXOBJ];
    BoundingBox hitboxHorizontal[MAXOBJ], hitboxVertical[MAXOBJ];
    Model dummy;
    MAPA_PROPS props[MAXOBJ];
    int mapaAtual;
    BoundingBox area[MAXOBJ];
    MAPA_ITEM item[MAXOBJ];
    PORTA porta;
    MAPA_DROPS drops[MAXOBJ];
    MAPA_DROPS dropDUMMY;
    BALAS_MAPA balas[255];
    BALAS_GLOBALVAR balasGLOBAL;
};
typedef struct MAPA MAPA;

//-----------------------------------
//DATA
//-----------------------------------

struct DATA_FRAMECOUNT
{
    int personagem[MAXOBJ + 1];
};
typedef struct DATA_FRAMECOUNT DATA_FRAMECOUNT;

struct DATA_ROTACAO
{
    float personagem[MAXOBJ + 1];
};
typedef struct DATA_ROTACAO DATA_ROTACAO;

struct DATA_POSICAO
{
    Vector3 personagem[MAXOBJ + 1];
};
typedef struct DATA_POSICAO DATA_POSICAO;

struct DATA_PONTEIROitem
{
    int calca, camisa, chapeu, sapato, arma, oculos;
};
typedef struct DATA_PONTEIROitem DATA_PONTEIROitem;

struct DATA_ponteiroPERSONAGEM
{
    DATA_PONTEIROitem item;
    /* float lastFloorHeight; */
    int tempoGravit;
};
typedef struct DATA_ponteiroPERSONAGEM DATA_ponteiroPERSONAGEM;

struct DATA_PONTEIRO
{
    DATA_ponteiroPERSONAGEM personagem[MAXOBJ + 1];
};
typedef struct DATA_PONTEIRO DATA_PONTEIRO;

struct DATA_booleanPERSONAGEM
{
    bool pulando, usando, andando, mirando, dropando, andandoPraTras;
};
typedef struct DATA_booleanPERSONAGEM DATA_booleanPERSONAGEM;

struct DATA_BOOLEAN
{
    DATA_booleanPERSONAGEM personagem[MAXOBJ + 1];
};
typedef struct DATA_BOOLEAN DATA_BOOLEAN;

struct DATA_RELOGIOplayer
{
    clock_t relogioVelho, relogioNovo, pulo, relogioLogs;
};
typedef struct DATA_RELOGIOplayer DATA_RELOGIOplayer;

struct DATA_RELOGIO
{
    DATA_RELOGIOplayer personagem[MAXOBJ + 1];
};
typedef struct DATA_RELOGIO DATA_RELOGIO;

struct DATA_VELOCIDADEPLAYER
{
    float velocidade, velocidadePulo;
};
typedef struct DATA_VELOCIDADEPLAYER DATA_VELOCIDADEPLAYER;

struct DATA_VELOCIDADE
{
    DATA_VELOCIDADEPLAYER personagem[MAXOBJ + 1];
};
typedef struct DATA_VELOCIDADE DATA_VELOCIDADE;

struct DATA_IMAGEM
{
    Texture2D textura[MAXOBJ + 1];
};
typedef struct DATA_IMAGEM DATA_IMAGEM;

struct DATA_FILES
{
    MAPA mapa;
    Model model[MAXOBJ];
    BoundingBox hitbox[MAXOBJ];
    Font font[MAXOBJ];
    char text[MAXOBJ][255];
    char lang[MAXOBJ][255];
    ModelAnimation *anim[MAXOBJ];
    char link[MAXOBJ][255];
    DATA_IMAGEM imagem;
};
typedef struct DATA_FILES DATA_FILES;

struct DATA_GAME
{
    DATA_VELOCIDADE velocidade;
    DATA_BOOLEAN boolean;
    DATA_PONTEIRO ponteiro;
    DATA_POSICAO posicao;
    DATA_ROTACAO rotacao;
};
typedef struct DATA_GAME DATA_GAME;

struct DATA_RENDER_MODEL
{
    bool visible, playing, reverse;
    int modelIndex;
    int currentAnim;
    int currentFrame;
    Color color;
    Vector3 position;
    float rotation;
    char *id;
};
typedef struct DATA_RENDER_MODEL DATA_RENDER_MODEL;

struct DATA_RENDER_TEXT
{
    bool visible;
    int textIndex;
    Vector2 position;
    Color color;
    char* string;
    int fontSize;
    int fontIndex;
    char *id;
};
typedef struct DATA_RENDER_TEXT DATA_RENDER_TEXT;

struct DATA_SESSION_RENDER
{
    DATA_RENDER_MODEL model[MAXOBJ];
    DATA_RENDER_TEXT text[MAXOBJ];
    Color background;
    Camera camera;
};
typedef struct DATA_SESSION_RENDER DATA_SESSION_RENDER;

struct DATA_SESSION_LOADEDNAMES
{
    char model[255],hitbox[255],text[255];
};
typedef struct DATA_SESSION_LOADEDNAMES DATA_SESSION_LOADEDNAMES;

struct DATA_SESSION
{
    DATA_RELOGIO relogio;
    DATA_SESSION_RENDER render;
    int ModelCount, HitboxCount, TextCount, LangCount,frame;
    DATA_SESSION_LOADEDNAMES LoadedNames[MAXOBJ];
};
typedef struct DATA_SESSION DATA_SESSION;

struct DATA
{
    DATA_GAME game;
    DATA_FILES file;
    DATA_SESSION session;
};
typedef struct DATA DATA;



#include "1964.c"