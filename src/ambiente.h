
struct AMBIENTE
{
	float gravidade;
};
typedef struct AMBIENTE AMBIENTE;

void GRAVIDADE ( PERSONAGEM* personagem, AMBIENTE* ambiente, MAPA mapa )
{
	if ( PERSONAGEM_CHECARCHAO( *personagem,mapa) == false&&personagem->pulando == false )
	{
		personagem->posicao.y -= ambiente->gravidade;

		if ( clock() >= personagem->pulo&&clock() < personagem->pulo+5000 )
		{
			ambiente->gravidade = 0.025;
		}
		else if ( clock() >= personagem->pulo+5000&&clock() < personagem->pulo+7500 )
		{
			ambiente->gravidade = 0.05;
		}
		else if ( clock() >= personagem->pulo+9000&&clock() < personagem->pulo+10000 )
		{
			ambiente->gravidade = 0.075;
		}
		else if ( clock() > personagem->pulo+10000 )
		{
			ambiente->gravidade = 0.15;
		}
	}
}
