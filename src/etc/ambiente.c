void GRAVIDADE_BALA ( Vector3* posicao, AMBIENTE ambiente)
{
    posicao->y -= ambiente.gravidade/1000;
}


void GRAVIDADE_AIHUMAN ( HUMANO_NPC* personagem, AMBIENTE* ambiente, MAPA mapa )
{
	if ( AIHUMAN_CHECARCHAO( *personagem,mapa) == false&&personagem->pulando == false )
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
