
// bool PERSONAGEM_ATIRAR(PERSONAGEM *personagem, MAPA *mapa)
// {
//     if(personagem->equip.arma.ponteiro != 0)
//     {
//         MAPA_CRIARBALA(*&mapa, personagem->posicao, personagem->rotacao, personagem->equip.arma.ponteiro);
//     }    
// }

bool PERSONAGEM_USE(PERSONAGEM *personagem, MAPA* mapa)
{
    for(int i = 0; i<10; i++)
    {
        if(CheckCollisionBoxes(personagem->hitbox.use, mapa->item[i].hitbox)||CheckCollisionBoxes(personagem->hitbox.atual , mapa->item[i].hitbox))
        {
            switch(mapa->item[i].tipo)
            {
                case 0:
                {
                    personagem->equip.calca.ponteiro = mapa->item[i].ponteiro;
                }
                break;
                case 1:
                {
                    personagem->equip.chapeu.ponteiro = mapa->item[i].ponteiro;
                }
                break;
                case 2:
                {
                    personagem->equip.camisa.ponteiro = mapa->item[i].ponteiro;
                }
                break;
                
                case 5:
                {
                    personagem->equip.arma.ponteiro = mapa->item[i].ponteiro;
                    personagem->equip.arma.municao = mapa->item[i].municao;
                    personagem->equip.arma.municaoMax = mapa->item[i].municaoMax;
                }
                break;
            }
            mapa->item[i].pegou = true;
            mapa->item[i].hitbox = (BoundingBox){(Vector3){0,0,0}, (Vector3){0,0,0}};
            char *texto_local;
            texto_local = malloc(sizeof(char)*40);
            snprintf(texto_local, 40 , " voce pegou %s",mapa->item[i].nome);
            msg = texto_local;
            free(texto_local);
            personagem->relogioLogs = clock();
            return true;
        }
    }
    for(int i = 0; i<10; i++)
    {
        if(CheckCollisionBoxes(personagem->hitbox.use, mapa->porta.slots[i].hitbox)||CheckCollisionBoxes(personagem->hitbox.atual , mapa->porta.slots[i].hitbox))
        {
            if(mapa->porta.slots[i].aberta == false)
            {
                mapa->porta.slots[i].abrindo = true;
                msg = " voce abre a porta ";
                personagem->relogioLogs = clock();
                return true;
                
            }
            else if(mapa->porta.slots[i].aberta == true)
            {
                mapa->porta.slots[i].fechando = true;
                msg = " voce fecha a porta ";
                personagem->relogioLogs = clock();
                return true;
                
            }
            else if(mapa->porta.slots[i].trancada == true)
            {
                msg = " esta trancada ";
                personagem->relogioLogs = clock();
                return true;
            }
        }
    }
    for(int i = 0; i<10; i++)
    {
        if(mapa->drops[i].ocupado == true )
        {
            if(CheckCollisionBoxes(personagem->hitbox.use, mapa->drops[i].hitbox)||CheckCollisionBoxes(personagem->hitbox.atual , mapa->drops[i].hitbox))
            {
                switch (mapa->drops[i].tipo)
                {
                    case 0:
                    {
                        personagem->equip.calca.ponteiro = 1;
                    }
                    break;
                    case 1:
                    {
                        personagem->equip.chapeu.ponteiro = 1;
                    }
                    break;
                    case 2:
                    {
                        personagem->equip.camisa.ponteiro = 1;
                    }
                    break;
                    case 5:
                    {
                        personagem->equip.arma.ponteiro = 1;
                    }
                    break;
                }
                mapa->drops[i] = mapa->dropDUMMY;
                mapa->drops[i].ocupado = false;
                return true;
            }
        }
    }
    return false;
}

void PERSONAGEM_USE_PRESS(PERSONAGEM* personagem, bool drop)
{
    if(drop == false)
    {
        personagem->usando = true;
        personagem->modelo.frame = 0;
        personagem->relogioNovo = 0;
        personagem->relogioVelho = 0;
    }
    else if(drop == true)
    {
        personagem->usando = true;
        personagem->dropando = true;
        personagem->modelo.frame = 0;
        personagem->relogioNovo = 0;
        personagem->relogioVelho = 0;
    }
	//PERSONAGEM_USEANIM(*&personagem);
}

void PERSONAGEM_MOVEFRENTE(PERSONAGEM *personagem, MAPA mapa, NPC0 humano)
{
	if(PERSONAGEM_CHECARPAREDE( *personagem, mapa, humano, '+') == false)
    {   //0 ou 360
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

void PERSONAGEM_MOVETRAS(PERSONAGEM *personagem, MAPA mapa, NPC0 humano)
{
    if(PERSONAGEM_CHECARPAREDE( *personagem, mapa, humano, '-') == false)
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
