struct ROUPA
{
	Model idle;
	Model run[5];
    Model use[3];
    Model drop;
    Model atirar;
};
typedef struct ROUPA ROUPA;

struct ARMA
{
	Model idle;
	Model run[5];
    Model use[3];
    Model drop;
    Model atirar;
    int municao, municaoMax;
};
typedef struct ARMA ARMA;

struct ITEM
{
	ROUPA calca[2], chapeu[2], camisa[2];
    ARMA arma[2];
};
typedef struct ITEM ITEM;


