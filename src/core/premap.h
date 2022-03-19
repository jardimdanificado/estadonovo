 
struct PORTA
{
    Model modelo[4];
	BoundingBox hitbox;
    bool aberta, abrindo, fechando;
    int frame;
    clock_t relogioVelho, relogioNovo;
};
typedef struct PORTA PORTA;

struct MAPA_ITEM
{
    Model modelo;
	BoundingBox hitbox;
    bool pegou;
};
typedef struct MAPA_ITEM MAPA_ITEM;

struct MAPA_PROPS
{
    Model modelo;
	BoundingBox hitbox;
};
typedef struct MAPA_PROPS MAPA_PROPS;

struct MAPA
{
	Model modelo[2];
    BoundingBox hitboxHorizontal[10],hitboxVertical[10];
    Model dummy;
    MAPA_PROPS props[10];
    int mapaAtual;
    BoundingBox area[10];
    MAPA_ITEM item[10];
    PORTA porta[5];
};
typedef struct MAPA MAPA;

//#include "premap.c"
