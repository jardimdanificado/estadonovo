struct SAVE_PORTA
{
    char aberta[30],trancada[30];
};
typedef struct SAVE_PORTA SAVE_PORTA;

struct SAVE_ITEM
{
    char pegou[30];
};
typedef struct SAVE_ITEM SAVE_ITEM;

struct SAVE_VEC3
{
    char x[30],y[30],z[30];
};
typedef struct SAVE_VEC3 SAVE_VEC3;

struct SAVE_HITBOX
{
    SAVE_VEC3 min,max;
};
typedef struct SAVE_HITBOX SAVE_HITBOX;

struct SAVE_DROPS
{
    char ocupado[30],tipo[30],ponteiro[30];
    SAVE_VEC3 posicao;
};
typedef struct SAVE_DROPS SAVE_DROPS;

struct SAVE
{
    char x[30],y[30],z[30],r[30],echapeu[30],ecalca[30];
    char eoculos[30],esapato[30],ecamisa[30];
    char earma[30],armaMuni[30],armaMuniR[30],armaMuniMax[30];
    char mapa[30];
    SAVE_PORTA porta[10];
    SAVE_ITEM item[10];
    SAVE_DROPS drops[10];
};
typedef struct SAVE SAVE;
 
#include "savegame.c"

