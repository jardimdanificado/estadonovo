 
struct MENU
{
	bool estaAberto, sair, esc;
    int opcao, opcaoMax;
};
typedef struct MENU MENU;

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
    Model modelo[4],modeloI[3];
};
typedef struct PORTA_BASE PORTA_BASE;

struct PORTA
{
    PORTA_BASE base;
    PORTA_UNI slots[10];
};
typedef struct PORTA PORTA;

struct MAPA_ITEM
{
    Model modelo;
	BoundingBox hitbox;
    bool pegou;
    char *nome;
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
	Model modelo[2];
    BoundingBox hitboxHorizontal[10],hitboxVertical[10];
    Model dummy;
    MAPA_PROPS props[10];
    int mapaAtual;
    BoundingBox area[10];
    MAPA_ITEM item[10];
    PORTA porta;
    MAPA_DROPS drops[10];
    MAPA_DROPS dropDUMMY;
    BALAS_MAPA balas[255];
    BALAS_GLOBALVAR balasGLOBAL;

};
typedef struct MAPA MAPA;

struct HITBOX_PERSONAGEM
{
	// 0
	BoundingBox use,useBase,atual;
    BoundingBox frenteBase, trasBase, pesBase, pesAtual, frenteAtual, trasAtual;
    BoundingBox frente45, frente90, frente135, frente180, frente225, frente270, frente315,tras45, tras90,tras135 , tras180, tras225, tras270, tras315, pes90, pes180, pes270;
	Model modelo;
};
typedef struct HITBOX_PERSONAGEM HITBOX_PERSONAGEM;

struct EQUIPAMENTO_EQUIP
{
	int ponteiro;
	Model modelo;
    int tipo;
};
typedef struct EQUIPAMENTO_EQUIP EQUIPAMENTO_EQUIP;

struct ARMA_EQUIP
{
	int ponteiro;
	Model modelo;
    int tipo;
    int municao;
    int municaoMax;
    int municaoReserva;
};
typedef struct ARMA_EQUIP ARMA_EQUIP;

struct EQUIPAMENTO
{
	EQUIPAMENTO_EQUIP chapeu, oculos, camisa, calca, sapato;
    ARMA_EQUIP arma;
};
typedef struct EQUIPAMENTO EQUIPAMENTO;

struct MODELO_PERSONAGEM
{
	EQUIPAMENTO equip;
	// 0
	Model idle;
	// 1-5
	Model run[5];
	Model use_default[3];
	Model atual;
    Model atirar38;
	int frame;
};
typedef struct MODELO_PERSONAGEM MODELO_PERSONAGEM;

struct PERSONAGEM
{
	EQUIPAMENTO equip;
	Vector3 posicao;
	MODELO_PERSONAGEM modelo;
	//BOUNDS bounds;
	HITBOX_PERSONAGEM hitbox;
	float rotacao;
	float velocidade, velocidadePulo;
	clock_t relogioVelho, relogioNovo, pulo, relogioLogs;
	bool pulando, usando, dropando, mirando;
};
typedef struct PERSONAGEM PERSONAGEM;



struct HITBOX_NPC
{
	// 0
	BoundingBox use,useBase,atual;
    BoundingBox frenteBase, trasBase, pesBase, pesAtual, frenteAtual, trasAtual;
    BoundingBox frente45, frente90, frente135, frente180, frente225, frente270, frente315,tras45, tras90,tras135 , tras180, tras225, tras270, tras315, pes90, pes180, pes270;
    BoundingBox anda0, anda45, anda90, anda135, anda180, anda225, anda270, anda315;
    BoundingBox anda0Base, anda45Base, anda90Base, anda135Base, anda180Base, anda225Base, anda270Base, anda315Base;
    BoundingBox andaAlvo;
	Model modelo;
};
typedef struct HITBOX_NPC HITBOX_NPC;

struct HUMANO_NPC
{
	EQUIPAMENTO equip;
	Vector3 posicao, posicaoInicial;
	MODELO_PERSONAGEM modelo;
	HITBOX_NPC hitbox;
	float rotacao;
	float velocidade, velocidadePulo;
	clock_t relogioVelho, relogioNovo, pulo, relogioLogs, relogioAndaV, relogioAndaN;
	bool pulando, usando, andando;
};
typedef struct HUMANO_NPC HUMANO_NPC;

struct NPC0
{
	HUMANO_NPC npc[10];
};
typedef struct NPC0 NPC0;


