void TECLADO_MAIN ( PERSONAGEM * personagem , ITEM *item)
{
	if ( IsKeyPressed ( KEY_RIGHT ) ||IsKeyPressed ( KEY_D ) )
	{
		if ( personagem->rotacao == 0 )
			personagem->rotacao = 360;
		//             personagem.posicao.x -= 0.03f;
		personagem->rotacao -= 45;

	}
	if ( IsKeyPressed ( KEY_LEFT ) ||IsKeyPressed ( KEY_A ) )
	{
		if ( personagem->rotacao == 360 )
			personagem->rotacao = 0;
		//             personagem.posicao.x += 0.03f;
		personagem->rotacao += 45;

	}
	if ( IsKeyDown ( KEY_DOWN ) ||IsKeyDown ( KEY_S ) )
	{
		PERSONAGEM_ANIMARUN (*&personagem,'-',*item );
		PERSONAGEM_MOVETRAS (*&personagem );
	}
	if ( IsKeyDown ( KEY_UP ) || IsKeyDown ( KEY_W ) )
	{
		PERSONAGEM_ANIMARUN (*&personagem,'+',*item  );
		PERSONAGEM_MOVEFRENTE (*&personagem );
	}
	if ( IsKeyDown ( KEY_LEFT_SHIFT ) )
	{
		personagem->velocidade = 0.2f;
	}
	if ( IsKeyReleased ( KEY_LEFT_SHIFT ) )
	{
		personagem->velocidade = 0.1f;
	}
	if ( IsKeyReleased ( KEY_UP ) || IsKeyReleased ( KEY_W ) )
	{
		personagem->modelo.atual = personagem->modelo.idle;
		personagem->equip.calcaAtual = item->calca[1].idle;
	}
	if ( IsKeyReleased ( KEY_DOWN ) || IsKeyReleased ( KEY_S ) )
	{
		personagem->modelo.atual = personagem->modelo.idle;
		personagem->equip.calcaAtual = item->calca[1].idle;
	}
	if ( IsKeyPressed ( KEY_SPACE ) &&personagem->posicao.y <= 0.1 )
	{
		personagem->modelo.atual = personagem->modelo.use_default[0];
		personagem->velocidadePulo = 0.2;
		personagem->pulando = true;
		personagem->pulo = clock();
	}
	if ( IsKeyDown ( KEY_SPACE ) )
	{
		if ( personagem->pulando == true )
			personagem->posicao.y += personagem->velocidade*2;
		if ( clock() >= personagem->pulo+5000&&clock() < personagem->pulo+7500 )
		{
			personagem->velocidadePulo = 0.1;
		}
		else if ( clock() >= personagem->pulo+7500&&clock() < personagem->pulo+9000 )
		{
			personagem->velocidadePulo = 0.05;
		}
		else if ( clock() >= personagem->pulo+9000&&clock() < personagem->pulo+10000 )
		{
			personagem->velocidadePulo = 0.025;
		}
		else if ( clock() > personagem->pulo+10000 )
		{
			personagem->pulando = false;
		}
	}
	if ( IsKeyReleased ( KEY_SPACE ) )
	{
		personagem->pulando = false;
		personagem->pulo = clock();
		personagem->modelo.atual = personagem->modelo.idle;
	}
	if ( IsKeyPressed ( KEY_E ) )
	{
		PERSONAGEM_USE (*&personagem );
		msg = " voce nao pegou nada ";}
}
