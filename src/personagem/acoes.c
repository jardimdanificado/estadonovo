
void PERSONAGEM_USE(PERSONAGEM *personagem, MAPA* mapa)
{
    
    if(CheckCollisionBoxes(personagem->hitbox.use, mapa->item[1])||CheckCollisionBoxes(personagem->hitbox.atual , mapa->item[1]))
    {
        mapa->pegouItem[1] = true;
        if(mapa->mapaAtual == 0)
        {
            personagem->equip.chapeu = 1;
            mapa->item[1] = (BoundingBox){(Vector3){0,0,0}, (Vector3){0,0,0}};
        }
        
    }
    else if(CheckCollisionBoxes(personagem->hitbox.use, mapa->item[0])||CheckCollisionBoxes(personagem->hitbox.atual , mapa->item[0]))
    {
        mapa->pegouItem[0] = true;
        if(mapa->mapaAtual == 0)
        {
            personagem->equip.calca = 1;
            mapa->item[0] = (BoundingBox){(Vector3){0,0,0}, (Vector3){0,0,0}};
        }
        
    }
    else if(CheckCollisionBoxes(personagem->hitbox.use, mapa->item[2])||CheckCollisionBoxes(personagem->hitbox.atual , mapa->item[2]))
    {
        mapa->pegouItem[2] = true;
        if(mapa->mapaAtual == 0)
        {
            personagem->equip.camisa = 1;
            mapa->item[2] = (BoundingBox){(Vector3){0,0,0}, (Vector3){0,0,0}};
        }
        
    }
    else
    {
        msg = " voce nao pegou nada ";
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
