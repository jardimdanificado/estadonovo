// ⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯
// ⣯⣇⣇⣇⣇⣇⣇⣇⣯⠁⠀⠀⠀⠀⢻⣧⣏⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇
// ⣏⣧⣇⣇⣇⣇⣇⣇⣯⠀⠀⠀⠀⠀⢠⣇⣧⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇⣯
// ⣧⣏⣇⣇⣇⣧⣧⣯⣯⡀⠀⠀⣤⣶⣿⣧⣏⣏⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇
// ⣯⣯⣇⣧⣯⠛⠉⣿⣇⣇⠀⠀⣯⣏⣇⣇⣧⣧⣇⣧⣇⣇⣇⣇⣇⣇⣇⣇⣇⣏
// ⣯⣯⠟⠁⠀⠀⣤⣿⣧⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇
// ⣯⠋⠀⠀⣴⣿⣇⣧⣯⣯⠀⠀⢰⣶⣶⣶⣶⣶⣶⣇⣏⣏⣧⣇⣇⣇⣇⣇⣇⣇
// ⡏⠀⠀⣾⣯⣯⣏⣧⣏⣯⠀⠀⠈⠋⠋⠋⠋⠋⠋⠋⠋⠋⣯⣧⣧⣇⣇⣇⣧⣇
// ⡂⠀⠀⣇⣧⣯⣧⣇⣇⣯⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣄⠀⠀⢫⣧⣏⣇⣇⣧⣇
// ⣧⠀⠀⣿⣇⣯⣏⣯⣇⣇⣧⣏⣏⣇⣧⣧⣏⡏⠙⣧⣏⣦⠀⠀⠻⣧⣇⣇⣏⣇
// ⣏⣄⠀⠈⢿⣧⣇⣇⣇⣇⣧⣏⣏⣏⣏⣯⠋⠀⠀⣼⣧⣯⣷⠀⠀⠙⣯⠏⢻⣏
// ⣯⣏⣦⠀⠀⠈⠛⢿⣇⣧⣇⣧⣇⠟⠋⠀⠀⢀⣾⣇⣧⣇⣯⣿⡀⠀⠀⠀⣠⣿
// ⣇⣇⣇⣏⣶⣤⣀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣾⣯⣯⣯⣧⣧⣧⣇⣏⣦⣮⣮⣮⣮

void TECLADO_MAIN ( PERSONAGEM * personagem , ITEM *item, MAPA*mapa, NPC0 *humano, MENU *menu, Font font)
{
    if ( IsKeyPressed ( KEY_ESCAPE ))
	{
        MENU_ESC(font, *&menu, true, *&personagem,*&mapa,*&humano);
	}
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
	if(IsKeyPressed ( KEY_DOWN ) ||IsKeyPressed ( KEY_S ))
    {
        if(personagem->mirando == false)
        {
            personagem->modelo.frame = 0;
        }
    }
	if ( IsKeyDown ( KEY_DOWN ) ||IsKeyDown ( KEY_S ) )
	{
        if(personagem->mirando == false)
        {
            PERSONAGEM_ANIMARUN (*&personagem,'-',*item );
            PERSONAGEM_MOVETRAS (*&personagem , *mapa, *humano);
        }
	}
	if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        if(personagem->mirando == false)
        {
            personagem->modelo.frame = 0;
        }
    }
	if ( IsKeyDown ( KEY_UP ) || IsKeyDown ( KEY_W ) )
	{
        if(personagem->mirando == false)
        {
            PERSONAGEM_ANIMARUN (*&personagem,'+',*item  );
            PERSONAGEM_MOVEFRENTE (*&personagem , *mapa, *humano);
        }
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
        if(personagem->mirando == false)
        {
            personagem->modelo.atual = personagem->modelo.idle;
            if(personagem->equip.calca.ponteiro != 0)
                personagem->equip.calca.modelo = item->calca[personagem->equip.calca.ponteiro].idle;
            if(personagem->equip.chapeu.ponteiro != 0)
                personagem->equip.chapeu.modelo = item->chapeu[personagem->equip.chapeu.ponteiro].idle;
            if(personagem->equip.camisa.ponteiro != 0)
                personagem->equip.camisa.modelo = item->camisa[personagem->equip.camisa.ponteiro].idle;
            if(personagem->equip.arma.ponteiro != 0)
                personagem->equip.arma.modelo = item->arma[personagem->equip.arma.ponteiro].idle;
        }
	}
	if ( IsKeyReleased ( KEY_DOWN ) || IsKeyReleased ( KEY_S ) )
	{
        if(personagem->mirando == false)
        {
            personagem->modelo.atual = personagem->modelo.idle;
            if(personagem->equip.calca.ponteiro != 0)
                personagem->equip.calca.modelo = item->calca[personagem->equip.calca.ponteiro].idle;
            if(personagem->equip.chapeu.ponteiro != 0)
                personagem->equip.chapeu.modelo = item->chapeu[personagem->equip.chapeu.ponteiro].idle;
            if(personagem->equip.camisa.ponteiro != 0)
                personagem->equip.camisa.modelo = item->camisa[personagem->equip.camisa.ponteiro].idle;
            if(personagem->equip.arma.ponteiro != 0)
                personagem->equip.arma.modelo = item->arma[personagem->equip.arma.ponteiro].idle;
        }
	}
	if ( IsKeyPressed ( KEY_SPACE ) &&PERSONAGEM_CHECARCHAO( *personagem, *mapa) )
	{
        if(personagem->mirando == false)
        {
            personagem->modelo.atual = personagem->modelo.use_default[0];
            if(personagem->equip.calca.ponteiro != 0)
                personagem->equip.calca.modelo = item->calca[personagem->equip.calca.ponteiro].use[0];
            if(personagem->equip.chapeu.ponteiro != 0)
                personagem->equip.chapeu.modelo = item->chapeu[personagem->equip.chapeu.ponteiro].use[0];
            if(personagem->equip.camisa.ponteiro != 0)
                personagem->equip.camisa.modelo = item->camisa[personagem->equip.camisa.ponteiro].use[0];
            if(personagem->equip.arma.ponteiro != 0)
                personagem->equip.arma.modelo = item->arma[personagem->equip.arma.ponteiro].use[0];
            personagem->velocidadePulo = 0.2;
            personagem->pulando = true;
            personagem->pulo = clock();
        }
        else if(personagem->mirando&&personagem->equip.arma.municao > 0)
        {
            MAPA_CRIARBALA(*&mapa, personagem->posicao, personagem->rotacao, personagem->equip.arma.ponteiro);
            personagem->equip.arma.municao--;
        }
	}
	if ( IsKeyDown ( KEY_SPACE ) )
	{
        if(personagem->mirando == false)
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
	}
	if ( IsKeyReleased ( KEY_SPACE ) )
	{
        if(personagem->mirando == false)
        {
            personagem->pulando = false;
            personagem->pulo = clock();
            personagem->modelo.atual = personagem->modelo.idle;
            if(personagem->equip.calca.ponteiro != 0)
                personagem->equip.calca.modelo = item->calca[personagem->equip.calca.ponteiro].idle;
            if(personagem->equip.chapeu.ponteiro != 0)
                personagem->equip.chapeu.modelo = item->chapeu[personagem->equip.chapeu.ponteiro].idle;
            if(personagem->equip.camisa.ponteiro != 0)
                personagem->equip.camisa.modelo = item->camisa[personagem->equip.camisa.ponteiro].idle;
            if(personagem->equip.arma.ponteiro != 0)
                personagem->equip.arma.modelo = item->arma[personagem->equip.arma.ponteiro].idle;
        }
	}
	if ( IsKeyPressed ( KEY_E ) )
	{
        personagem->modelo.frame = 0;
		PERSONAGEM_USE_PRESS (*&personagem ,false);
    }
    if ( IsKeyPressed ( KEY_F ) )
	{
        if(personagem->equip.arma.ponteiro >0)
        {
            personagem->modelo.frame = 0;
            personagem->mirando = true;
            personagem->modelo.atual = personagem->modelo.atirar38;
            if(personagem->equip.calca.ponteiro != 0)
                personagem->equip.calca.modelo = item->calca[personagem->equip.calca.ponteiro].idle;
            if(personagem->equip.chapeu.ponteiro != 0)
                personagem->equip.chapeu.modelo = item->chapeu[personagem->equip.chapeu.ponteiro].run[0];
            if(personagem->equip.camisa.ponteiro != 0)
                personagem->equip.camisa.modelo = item->camisa[personagem->equip.camisa.ponteiro].atirar;
            if(personagem->equip.arma.ponteiro != 0)
                personagem->equip.arma.modelo = item->arma[personagem->equip.arma.ponteiro].atirar;
        }
    }
    if ( IsKeyReleased ( KEY_F ) )
	{
        if(personagem->equip.arma.ponteiro >0)
        {
            personagem->mirando = false;
            personagem->modelo.atual = personagem->modelo.idle;
            if(personagem->equip.calca.ponteiro != 0)
                personagem->equip.calca.modelo = item->calca[personagem->equip.calca.ponteiro].idle;
            if(personagem->equip.chapeu.ponteiro != 0)
                personagem->equip.chapeu.modelo = item->chapeu[personagem->equip.chapeu.ponteiro].idle;
            if(personagem->equip.camisa.ponteiro != 0)
                personagem->equip.camisa.modelo = item->camisa[personagem->equip.camisa.ponteiro].idle;
            if(personagem->equip.arma.ponteiro != 0)
                personagem->equip.arma.modelo = item->arma[personagem->equip.arma.ponteiro].idle;
            
        }
    }
    if( IsKeyPressed (KEY_G))
    {
        if(personagem->equip.arma.ponteiro != 0||personagem->equip.calca.ponteiro != 0||personagem->equip.camisa.ponteiro != 0||personagem->equip.chapeu.ponteiro != 0||personagem->equip.oculos.ponteiro != 0||personagem->equip.sapato.ponteiro != 0)
        {
            personagem->modelo.frame = 0;
            PERSONAGEM_USE_PRESS (*&personagem , true);
        }
    }
}
