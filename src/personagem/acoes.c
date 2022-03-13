
void PERSONAGEM_USE(PERSONAGEM *personagem, MAPA* mapa)
{
    
    if(CheckCollisionBoxes(personagem->hitbox.use, mapa->item[1].hitbox)||CheckCollisionBoxes(personagem->hitbox.atual , mapa->item[1].hitbox))
    {
        mapa->item[1].pegou = true;
        if(mapa->mapaAtual == 0)
        {
            personagem->equip.chapeu = 1;
            mapa->item[1].hitbox = (BoundingBox){(Vector3){0,0,0}, (Vector3){0,0,0}};
            msg = " voce pegou um item ";
            personagem->relogioLogs = clock();
        }
        
    }
    else if(CheckCollisionBoxes(personagem->hitbox.use, mapa->item[0].hitbox)||CheckCollisionBoxes(personagem->hitbox.atual , mapa->item[0].hitbox))
    {
        mapa->item[0].pegou = true;
        if(mapa->mapaAtual == 0)
        {
            personagem->equip.calca = 1;
            mapa->item[0].hitbox = (BoundingBox){(Vector3){0,0,0}, (Vector3){0,0,0}};
            msg = " voce pegou um item ";
            personagem->relogioLogs = clock();
        }
        
    }
    else if(CheckCollisionBoxes(personagem->hitbox.use, mapa->item[2].hitbox)||CheckCollisionBoxes(personagem->hitbox.atual , mapa->item[2].hitbox))
    {
        mapa->item[2].pegou = true;
        if(mapa->mapaAtual == 0)
        {
            personagem->equip.camisa = 1;
            mapa->item[2].hitbox = (BoundingBox){(Vector3){0,0,0}, (Vector3){0,0,0}};
            msg = " voce pegou um item ";
            personagem->relogioLogs = clock();
        }
        
    }
    else if(CheckCollisionBoxes(personagem->hitbox.use, mapa->porta[0].hitbox)||CheckCollisionBoxes(personagem->hitbox.atual , mapa->porta[0].hitbox))
    {
        if(mapa->porta[0].aberta == false)
        {
            mapa->porta[0].abrindo = true;
            msg = " voce abre a porta ";
            personagem->relogioLogs = clock();
            
        }
        else if(mapa->porta[0].aberta == true)
        {
            mapa->porta[0].fechando = true;
            msg = " voce fecha a porta ";
            personagem->relogioLogs = clock();
            
        }
    }
    else if(CheckCollisionBoxes(personagem->hitbox.use, mapa->porta[1].hitbox)||CheckCollisionBoxes(personagem->hitbox.atual , mapa->porta[1].hitbox))
    {
        if(mapa->porta[1].aberta == false)
        {
            mapa->porta[1].abrindo = true;
            msg = " voce abre a porta ";
            personagem->relogioLogs = clock();
            
        }
        else if(mapa->porta[1].aberta == true)
        {
            mapa->porta[1].fechando = true;
            msg = " voce fecha a porta ";
            personagem->relogioLogs = clock();
            
        }
    }
}

void PERSONAGEM_USE_PRESS(PERSONAGEM* personagem)
{
	personagem->usando = true;
	personagem->modelo.frame = 0;
	personagem->relogioNovo = 0;
	personagem->relogioVelho = 0;
	//PERSONAGEM_USEANIM(*&personagem);
}

void PERSONAGEM_MOVEFRENTE(PERSONAGEM *personagem, MAPA mapa)
{
	if(PERSONAGEM_CHECARPAREDE( *personagem, mapa, '+') == false)
    {//0 ou 360
        if(personagem->rotacao == 0||personagem->rotacao == 360)
        {
            personagem->posicao.z += personagem->velocidade;
        }
        //45
        else if(personagem->rotacao == 45)
        {
            personagem->posicao.z += personagem->velocidade/1.5;
            personagem->posicao.x += personagem->velocidade/1.5;

        }
        //90
        else if(personagem->rotacao == 90)
            personagem->posicao.x += personagem->velocidade;
        //135
        else if(personagem->rotacao == 135)
        {
            personagem->posicao.z -= personagem->velocidade/1.5;
            personagem->posicao.x += personagem->velocidade/1.5;

        }
        //180
        else if(personagem->rotacao == 180)
            personagem->posicao.z -= personagem->velocidade;
        //225
        else if(personagem->rotacao == 225)
        {
            personagem->posicao.z -= personagem->velocidade/1.5;
            personagem->posicao.x -= personagem->velocidade/1.5;

        }
        //270
        else if(personagem->rotacao == 270)
            personagem->posicao.x -= personagem->velocidade;
        //315
        else if(personagem->rotacao == 315)
        {
            personagem->posicao.z += personagem->velocidade/1.5;
            personagem->posicao.x -= personagem->velocidade/1.5;

        }
    }

}

void PERSONAGEM_MOVETRAS(PERSONAGEM *personagem, MAPA mapa)
{
    if(PERSONAGEM_CHECARPAREDE( *personagem, mapa, '-') == false)
    {
        //0 ou 360
        if(personagem->rotacao == 0||personagem->rotacao == 360)
            personagem->posicao.z -= personagem->velocidade;
        //45
        else if(personagem->rotacao == 45)
        {
            personagem->posicao.z -= personagem->velocidade/1.5;
            personagem->posicao.x -= personagem->velocidade/1.5;

        }
        //90
        else if(personagem->rotacao == 90)
            personagem->posicao.x -= personagem->velocidade;
        //135
        else if(personagem->rotacao == 135)
        {
            personagem->posicao.z += personagem->velocidade/1.5;
            personagem->posicao.x -= personagem->velocidade/1.5;

        }
        //180
        else if(personagem->rotacao == 180)
            personagem->posicao.z += personagem->velocidade;
        //225
        else if(personagem->rotacao == 225)
        {
            personagem->posicao.z += personagem->velocidade/1.5;
            personagem->posicao.x += personagem->velocidade/1.5;

        }
        //270
        else if(personagem->rotacao == 270)
            personagem->posicao.x += personagem->velocidade;
        //315
        else if(personagem->rotacao == 315)
        {
            personagem->posicao.z -= personagem->velocidade/1.5;
            personagem->posicao.x += personagem->velocidade/1.5;

        }
    }

}
