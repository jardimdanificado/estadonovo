


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

#define MAXWID 600
#define MAXHEI 240
#define MAXOBJ 64
unsigned int MAXANIM = 1;


bool MQEXIT = false;

struct LOGO
{
    int ponteiro, piscaPonteiro;
    clock_t relogio, relogiosub, relogiosubDef;
    bool pisca;
};
typedef struct LOGO LOGO;

//-----------------------------------
//ENVIROMENT
//-----------------------------------
struct AMBIENTE
{
    float gravidade;
};
typedef struct AMBIENTE AMBIENTE;

//-----------------------------------
//MENU
//-----------------------------------

struct MQMenuTabS
{
    bool ativo, itens, equips;
};
typedef struct MQMenuTabS MQMenuTabS;

struct MENU
{
    bool estaAberto, sair, esc;
    MQMenuTabS tab;
    int opcao, opcaoMax;
};
typedef struct MENU MENU;

//-----------------------------------
//DOORS
//-----------------------------------

struct PORTA_UNI
{
    //Model modelo;
    BoundingBox hitbox;
    bool aberta, abrindo, fechando, trancada, existe, invertido;
    int frame;
    Vector3 posicao;
    clock_t relogioVelho, relogioNovo;
};
typedef struct PORTA_UNI PORTA_UNI;

struct PORTA_BASE
{
    Model modelo[4], modeloI[3];
};
typedef struct PORTA_BASE PORTA_BASE;

struct PORTA
{
    PORTA_BASE base;
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
//PLAYER
//-----------------------------------

struct HITBOX_PERSONAGEM
{
    // 0
    BoundingBox use, useBase, atual;
    BoundingBox frenteBase, trasBase, pesBase, pesAtual, frenteAtual, trasAtual;
    BoundingBox frente45, frente90, frente135, frente180, frente225, frente270, frente315, tras45, tras90, tras135, tras180, tras225, tras270, tras315, pes90, pes180, pes270;
    BoundingBox anda0, anda45, anda90, anda135, anda180, anda225, anda270, anda315;
    BoundingBox anda0Base, anda45Base, anda90Base, anda135Base, anda180Base, anda225Base, anda270Base, anda315Base;
    BoundingBox andaAlvo;
    Model modelo;
};
typedef struct HITBOX_PERSONAGEM HITBOX_PERSONAGEM;

struct EQUIPAMENTO_EQUIP
{
    int ponteiro;
    int tipo;
    char nome[25];
};
typedef struct EQUIPAMENTO_EQUIP EQUIPAMENTO_EQUIP;

struct ARMA_EQUIP
{
    int ponteiro;
    int tipo;
    int municao;
    int municaoMax;
    int municaoReserva;
    char nome[25];
};
typedef struct ARMA_EQUIP ARMA_EQUIP;

struct EQUIPAMENTO
{
    EQUIPAMENTO_EQUIP chapeu, oculos, camisa, calca, sapato;
    ARMA_EQUIP arma;
};
typedef struct EQUIPAMENTO EQUIPAMENTO;

//-----------------------------------
//SAVE
//-----------------------------------

struct SAVE_PORTA
{
    char aberta[30], trancada[30];
};
typedef struct SAVE_PORTA SAVE_PORTA;

struct SAVE_ITEM
{
    char pegou[30];
};
typedef struct SAVE_ITEM SAVE_ITEM;

struct SAVE_VEC3
{
    char x[30], y[30], z[30];
};
typedef struct SAVE_VEC3 SAVE_VEC3;

struct SAVE_HITBOX
{
    SAVE_VEC3 min, max;
};
typedef struct SAVE_HITBOX SAVE_HITBOX;

struct SAVE_DROPS
{
    char ocupado[30], tipo[30], ponteiro[30];
    SAVE_VEC3 posicao;
};
typedef struct SAVE_DROPS SAVE_DROPS;

struct SAVE
{
    char x[30], y[30], z[30], r[30], echapeu[30], ecalca[30];
    char eoculos[30], esapato[30], ecamisa[30];
    char earma[30], armaMuni[30], armaMuniR[30], armaMuniMax[30];
    char mapa[30];
    SAVE_PORTA porta[MAXOBJ];
    SAVE_ITEM item[MAXOBJ];
    SAVE_DROPS drops[MAXOBJ];
};
typedef struct SAVE SAVE;

//-----------------------------------
//DATA
//-----------------------------------


struct DATA_TEXTOOPCAO
{
    char opcao[16][255];
    int size;
};
typedef struct DATA_TEXTOOPCAO DATA_TEXTOOPCAO;

struct DATA_TEXTOITEM
{
    DATA_TEXTOOPCAO arma;
    DATA_TEXTOOPCAO calca;
    DATA_TEXTOOPCAO camisa;
    DATA_TEXTOOPCAO sapato;
    DATA_TEXTOOPCAO oculos;
    DATA_TEXTOOPCAO chapeu;
};
typedef struct DATA_TEXTOITEM DATA_TEXTOITEM;

struct DATA_TEXTO
{
    DATA_TEXTOOPCAO menu;
    DATA_TEXTOOPCAO act;
    DATA_TEXTOITEM item;
};
typedef struct DATA_TEXTO DATA_TEXTO;

struct DATA_MODELITEM
{
    Model calca[2], camisa[2], oculos[2], chapeu[2], sapato[2];
    Model arma[2];
};
typedef struct DATA_MODELITEM DATA_MODELITEM;

struct DATA_ITEMANIM
{
    ModelAnimation *calca, *camisa, *chapeu, *sapato, *arma, *oculos;
};
typedef struct DATA_ITEMANIM DATA_ITEMANIM;

struct DATA_FRAMECOUNT
{
    int personagem[MAXOBJ + 1];
};
typedef struct DATA_FRAMECOUNT DATA_FRAMECOUNT;

struct DATA_COUNTER
{
    DATA_FRAMECOUNT frames;
};
typedef struct DATA_COUNTER DATA_COUNTER;

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
    float lastFloorHeight;
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

struct DATA_HITBOX
{
    HITBOX_PERSONAGEM personagem[MAXOBJ + 1];
};
typedef struct DATA_HITBOX DATA_HITBOX;

struct DATA_EQUIPAMENTO
{
    EQUIPAMENTO personagem[MAXOBJ + 1];
};
typedef struct DATA_EQUIPAMENTO DATA_EQUIPAMENTO;

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
    DATA_TEXTO text;
    ModelAnimation *anim[MAXOBJ];
    char link[MAXOBJ][255];
    DATA_IMAGEM imagem;
};
typedef struct DATA_FILES DATA_FILES;

struct DATA_GAME
{
    DATA_EQUIPAMENTO equip;
    DATA_HITBOX hitbox;
    DATA_VELOCIDADE velocidade;
    DATA_BOOLEAN boolean;
    DATA_PONTEIRO ponteiro;
    DATA_POSICAO posicao;
    DATA_ROTACAO rotacao;
    DATA_COUNTER contador;
};
typedef struct DATA_GAME DATA_GAME;

struct DATA_SESSION
{
    DATA_RELOGIO relogio;
    int ObjCount, AnimCount, HitboxCount;
};
typedef struct DATA_SESSION DATA_SESSION;

struct DATA
{
    DATA_GAME game;
    DATA_FILES file;
    DATA_SESSION session;
};
typedef struct DATA DATA;

int screenH, screenW;

#include "1964.c"
