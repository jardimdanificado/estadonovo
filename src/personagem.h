 
struct HITBOX_PERSONAGEM
{
	// 0
	BoundingBox use,useBase,atual;
    BoundingBox frenteBase, trasBase, pesBase, pesAtual, frenteAtual, trasAtual;
    BoundingBox frente90, frente180, frente270, tras90, tras180, tras270, pes90, pes180, pes270;
	Model modelo;
};
typedef struct HITBOX_PERSONAGEM HITBOX_PERSONAGEM;

struct EQUIPAMENTO
{
	int chapeu, oculos, camisa, calca, sapato;
	Model chapeuAtual,oculosAtual,camisaAtual,calcaAtual,sapatoAtual;
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
	clock_t relogioVelho, relogioNovo, pulo;
	bool pulando, usando;
};
typedef struct PERSONAGEM PERSONAGEM;


#include "personagem/colisao.c"
#include "personagem/config.c"
#include "personagem/acoes.c"
#include "personagem/anim.c"
#include "personagem/hitbox.c"
