

bool AIHUMAN_CHECARCHAO(HUMANO_NPC humano, MAPA mapa)
{
    if(CheckCollisionBoxes(humano.hitbox.pesAtual, mapa.hitboxHorizontal[0]))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool AIHUMAN_CHECARPAREDE(HUMANO_NPC humano, MAPA mapa, int qual)
{
        for(int i = 0; i <10; i++)
        {
            if(CheckCollisionBoxes(humano.hitbox.frenteAtual, mapa.hitboxVertical[i]))
            {
                return true;
            }
            else if(CheckCollisionBoxes(humano.hitbox.frenteAtual, mapa.porta.slots[i].hitbox))
            {
                return true;
            }
            else if(CheckCollisionBoxes(humano.hitbox.frenteAtual, mapa.props[i].hitbox))
            {
                return true;
            }
                
        }
        
        return false;
}

bool AIHUMAN_USE(HUMANO_NPC *personagem, MAPA* mapa)
{
//     for(int i = 0; i<10; i++)
//     {
//         if(CheckCollisionBoxes(personagem->hitbox.use, mapa->item[i].hitbox)||CheckCollisionBoxes(personagem->hitbox.atual , mapa->item[i].hitbox))
//         {
//             switch(mapa->item[i].tipo)
//             {
//                 case 0:
//                 {
//                     personagem->equip.calca.ponteiro = mapa->item[i].ponteiro;
//                 }
//                 break;
//                 case 1:
//                 {
//                     personagem->equip.chapeu.ponteiro = mapa->item[i].ponteiro;
//                 }
//                 break;
//                 case 2:
//                 {
//                     personagem->equip.camisa.ponteiro = mapa->item[i].ponteiro;
//                 }
//                 break;
//                 
//                 case 5:
//                 {
//                     personagem->equip.arma.ponteiro = mapa->item[i].ponteiro;
//                 }
//                 break;
//             }
//             mapa->item[i].pegou = true;
//             mapa->item[i].hitbox = (BoundingBox){(Vector3){0,0,0}, (Vector3){0,0,0}};
//             char *texto_local;
//             texto_local = malloc(sizeof(char)*40);
//             snprintf(texto_local, 40 , " voce pegou %s",mapa->item[i].nome);
//             msg = texto_local;
//             free(texto_local);
//             personagem->relogioLogs = clock();
//             return true;
//         }
//     }
    for(int i = 0; i<10; i++)
    {
        if(CheckCollisionBoxes(personagem->hitbox.use, mapa->porta.slots[i].hitbox) == true||CheckCollisionBoxes(personagem->hitbox.atual , mapa->porta.slots[i].hitbox) == true)
        {
            if(mapa->porta.slots[i].aberta == false)
            {
                mapa->porta.slots[i].abrindo = true;
                personagem->usando = false;
                //msg = " voce abre a porta ";
                personagem->relogioLogs = clock();
                return true;
            }
            else if(mapa->porta.slots[i].aberta == true)
            {
                mapa->porta.slots[i].fechando = true;
                personagem->usando = false;
                //msg = " voce fecha a porta ";
                personagem->relogioLogs = clock();
                return true;
                
            }
            else if(mapa->porta.slots[i].trancada == true)
            {
                personagem->usando = false;
                //msg = " esta trancada ";
                personagem->relogioLogs = clock();
                return true;
            }
        }
    }
    return false;
}

void AIHUMAN_USE_PRESS(HUMANO_NPC* personagem)
{
	personagem->usando = true;
	personagem->modelo.frame = 0;
	personagem->relogioNovo = 0;
	personagem->relogioVelho = 0;
	//PERSONAGEM_USEANIM(*&personagem);
}

 
void AIHUMAN_USEANIM(HUMANO_NPC* humano, MAPA *mapa, ITEM item, PERSONAGEM personagem)
{
	if(humano->relogioNovo > humano->relogioVelho+10000)
	{
		humano->relogioVelho = humano->relogioNovo;
// 		printf("aoba");
	}
	humano->relogioNovo = clock();

	if(humano->relogioNovo > humano->relogioVelho+10000&&humano->modelo.frame < 2)
		humano->modelo.frame++;
	else if(humano->modelo.frame == 2&&humano->relogioNovo > humano->relogioVelho+10000)
		humano->usando = false;
	switch(humano->modelo.frame)
	{
		case 0:
		{
			humano->modelo.atual = personagem.modelo.use_default[0];
            if(humano->equip.calca.ponteiro != 0)
                humano->equip.calca.modelo = item.calca[humano->equip.calca.ponteiro].use[0];
            if(humano->equip.chapeu.ponteiro != 0)
                humano->equip.chapeu.modelo = item.chapeu[humano->equip.chapeu.ponteiro].use[0];
            if(humano->equip.camisa.ponteiro != 0)
                humano->equip.camisa.modelo = item.camisa[humano->equip.camisa.ponteiro].use[0];
            if(humano->equip.arma.ponteiro != 0)
                humano->equip.arma.modelo = item.arma[humano->equip.arma.ponteiro].use[0];
		}
		break;
		case 1:
		{
			humano->modelo.atual = personagem.modelo.use_default[1];
            if(humano->equip.calca.ponteiro != 0)
                humano->equip.calca.modelo = item.calca[humano->equip.calca.ponteiro].use[1];
            if(humano->equip.chapeu.ponteiro != 0)
                humano->equip.chapeu.modelo = item.chapeu[humano->equip.chapeu.ponteiro].use[1];
            if(humano->equip.camisa.ponteiro != 0)
                humano->equip.camisa.modelo = item.camisa[humano->equip.camisa.ponteiro].use[1];
            if(humano->equip.arma.ponteiro != 0)
                humano->equip.arma.modelo = item.arma[humano->equip.arma.ponteiro].use[0];
            AIHUMAN_USE(*&humano, *&mapa);

		}
		break;
        case 2:
		{
			humano->modelo.atual = personagem.modelo.use_default[2];
            if(humano->equip.calca.ponteiro != 0)
                humano->equip.calca.modelo = item.calca[humano->equip.calca.ponteiro].use[2];
            if(humano->equip.chapeu.ponteiro != 0)
                humano->equip.chapeu.modelo = item.chapeu[humano->equip.chapeu.ponteiro].use[2];
            if(humano->equip.camisa.ponteiro != 0)
                humano->equip.camisa.modelo = item.camisa[humano->equip.camisa.ponteiro].use[2];
            if(humano->equip.arma.ponteiro != 0)
                humano->equip.arma.modelo = item.arma[humano->equip.arma.ponteiro].use[0];
			if(humano->usando == false)
			{
				humano->modelo.atual = personagem.modelo.idle;
                if(humano->equip.calca.ponteiro != 0)
                    humano->equip.calca.modelo = item.calca[humano->equip.calca.ponteiro].idle;
                if(humano->equip.chapeu.ponteiro != 0)
                    humano->equip.chapeu.modelo = item.chapeu[humano->equip.chapeu.ponteiro].idle;
                if(humano->equip.camisa.ponteiro != 0)
                    humano->equip.camisa.modelo = item.camisa[humano->equip.camisa.ponteiro].idle;
                if(humano->equip.arma.ponteiro != 0)
                    humano->equip.arma.modelo = item.arma[humano->equip.arma.ponteiro].idle;
                
				//msg = " ";
			}
		}
		break;
	}
}


void AIHUMAN_ANIMARUN(PERSONAGEM personagem, NPC0* humano, int qual, ITEM item)
{

    if(humano->npc[qual].relogioNovo > humano->npc[qual].relogioVelho+10000)
    {
        humano->npc[qual].relogioVelho = humano->npc[qual].relogioNovo;

    }
    humano->npc[qual].relogioNovo = clock();

    if(humano->npc[qual].relogioNovo > humano->npc[qual].relogioVelho+10000&&humano->npc[qual].modelo.frame < 4)
        humano->npc[qual].modelo.frame++;
    else if(humano->npc[qual].modelo.frame == 4)
        humano->npc[qual].modelo.frame = 0;

	
	switch(humano->npc[qual].modelo.frame)
	{
		case 0:
		{
			humano->npc[qual].modelo.atual = personagem.modelo.run[0];
            if(humano->npc[qual].equip.calca.ponteiro != 0)
                humano->npc[qual].equip.calca.modelo = item.calca[humano->npc[qual].equip.calca.ponteiro].run[0];
            if(humano->npc[qual].equip.chapeu.ponteiro != 0)
                humano->npc[qual].equip.chapeu.modelo = item.chapeu[humano->npc[qual].equip.chapeu.ponteiro].run[0];
            if(humano->npc[qual].equip.camisa.ponteiro != 0)
                humano->npc[qual].equip.camisa.modelo = item.camisa[humano->npc[qual].equip.camisa.ponteiro].run[0];
            if(humano->npc[qual].equip.arma.ponteiro != 0)
                humano->npc[qual].equip.arma.modelo = item.arma[humano->npc[qual].equip.arma.ponteiro].run[0];
            
		}
		break;
		case 1:
		{
			humano->npc[qual].modelo.atual = personagem.modelo.run[1];
            if(humano->npc[qual].equip.calca.ponteiro != 0)
                humano->npc[qual].equip.calca.modelo = item.calca[humano->npc[qual].equip.calca.ponteiro].run[1];
            if(humano->npc[qual].equip.chapeu.ponteiro != 0)
                humano->npc[qual].equip.chapeu.modelo = item.chapeu[humano->npc[qual].equip.chapeu.ponteiro].run[1];
            if(humano->npc[qual].equip.camisa.ponteiro != 0)
                humano->npc[qual].equip.camisa.modelo = item.camisa[humano->npc[qual].equip.camisa.ponteiro].run[1];
            if(humano->npc[qual].equip.arma.ponteiro != 0)
                humano->npc[qual].equip.arma.modelo = item.arma[humano->npc[qual].equip.arma.ponteiro].run[1];
		}
		break;
		case 2:
		{
			humano->npc[qual].modelo.atual = personagem.modelo.run[2];
            if(humano->npc[qual].equip.calca.ponteiro != 0)
                humano->npc[qual].equip.calca.modelo = item.calca[humano->npc[qual].equip.calca.ponteiro].run[2];
            if(humano->npc[qual].equip.chapeu.ponteiro != 0)
                humano->npc[qual].equip.chapeu.modelo = item.chapeu[humano->npc[qual].equip.chapeu.ponteiro].run[2];
            if(humano->npc[qual].equip.camisa.ponteiro != 0)
                humano->npc[qual].equip.camisa.modelo = item.camisa[humano->npc[qual].equip.camisa.ponteiro].run[2];
            if(humano->npc[qual].equip.arma.ponteiro != 0)
                humano->npc[qual].equip.arma.modelo = item.arma[humano->npc[qual].equip.arma.ponteiro].run[2];

		}
		break;
		case 3:
		{
			humano->npc[qual].modelo.atual = personagem.modelo.run[3];
            if(humano->npc[qual].equip.calca.ponteiro != 0)
                humano->npc[qual].equip.calca.modelo = item.calca[humano->npc[qual].equip.calca.ponteiro].run[3];
            if(humano->npc[qual].equip.chapeu.ponteiro != 0)
                humano->npc[qual].equip.chapeu.modelo = item.chapeu[humano->npc[qual].equip.chapeu.ponteiro].run[3];
            if(humano->npc[qual].equip.camisa.ponteiro != 0)
                humano->npc[qual].equip.camisa.modelo = item.camisa[humano->npc[qual].equip.camisa.ponteiro].run[3];
            if(humano->npc[qual].equip.arma.ponteiro != 0)
                humano->npc[qual].equip.arma.modelo = item.arma[humano->npc[qual].equip.arma.ponteiro].run[3];

		}
		break;
		case 4:
		{
			humano->npc[qual].modelo.atual = personagem.modelo.run[4];
            if(humano->npc[qual].equip.calca.ponteiro != 0)
                humano->npc[qual].equip.calca.modelo = item.calca[humano->npc[qual].equip.calca.ponteiro].run[4];
            if(humano->npc[qual].equip.chapeu.ponteiro != 0)
                humano->npc[qual].equip.chapeu.modelo = item.chapeu[humano->npc[qual].equip.chapeu.ponteiro].run[4];
            if(humano->npc[qual].equip.camisa.ponteiro != 0)
                humano->npc[qual].equip.camisa.modelo = item.camisa[humano->npc[qual].equip.camisa.ponteiro].run[4];
            if(humano->npc[qual].equip.arma.ponteiro != 0)
                humano->npc[qual].equip.arma.modelo = item.arma[humano->npc[qual].equip.arma.ponteiro].run[4];
		}
		break;
	}              
}

void AIHUMAN_DEFINEALVO(NPC0* humano, int qual, Vector3 posicao)
{
    humano->npc[qual].hitbox.andaAlvo.max.x = 0.1 + posicao.x;
    humano->npc[qual].hitbox.andaAlvo.max.y = 0.1 + posicao.y;
    humano->npc[qual].hitbox.andaAlvo.max.z = 0.1 + posicao.z;
    humano->npc[qual].hitbox.andaAlvo.min.x = -0.1 + posicao.x;
    humano->npc[qual].hitbox.andaAlvo.min.y = -0.1 + posicao.y;
    humano->npc[qual].hitbox.andaAlvo.min.z = -0.1 + posicao.z;
}

void AIHUMAN_HITBOXUPDATE(NPC0* humano, int qual)
{
    humano->npc[qual].hitbox.atual.min.x = humano->npc[qual].hitbox.useBase.min.x + humano->npc[qual].posicao.x;
    humano->npc[qual].hitbox.atual.max.x = humano->npc[qual].hitbox.useBase.max.x + humano->npc[qual].posicao.x;
    humano->npc[qual].hitbox.atual.min.z = humano->npc[qual].hitbox.useBase.min.z + humano->npc[qual].posicao.z;
    humano->npc[qual].hitbox.atual.max.z = humano->npc[qual].hitbox.useBase.max.z + humano->npc[qual].posicao.z;
    humano->npc[qual].hitbox.atual.min.y = humano->npc[qual].hitbox.useBase.min.y + humano->npc[qual].posicao.y;
    humano->npc[qual].hitbox.atual.max.y = humano->npc[qual].hitbox.useBase.max.y + humano->npc[qual].posicao.y;
        
    humano->npc[qual].hitbox.anda0.min.x = humano->npc[qual].hitbox.anda0Base.min.x + humano->npc[qual].posicao.x;
    humano->npc[qual].hitbox.anda0.max.x = humano->npc[qual].hitbox.anda0Base.max.x + humano->npc[qual].posicao.x;
    humano->npc[qual].hitbox.anda0.min.z = humano->npc[qual].hitbox.anda0Base.min.z + humano->npc[qual].posicao.z;
    humano->npc[qual].hitbox.anda0.max.z = humano->npc[qual].hitbox.anda0Base.max.z + humano->npc[qual].posicao.z;
    humano->npc[qual].hitbox.anda0.min.y = humano->npc[qual].hitbox.anda0Base.min.y + humano->npc[qual].posicao.y;
    humano->npc[qual].hitbox.anda0.max.y = humano->npc[qual].hitbox.anda0Base.max.y + humano->npc[qual].posicao.y;
    
    humano->npc[qual].hitbox.anda45.min.x = humano->npc[qual].hitbox.anda45Base.min.x + humano->npc[qual].posicao.x;
    humano->npc[qual].hitbox.anda45.max.x = humano->npc[qual].hitbox.anda45Base.max.x + humano->npc[qual].posicao.x;
    humano->npc[qual].hitbox.anda45.min.z = humano->npc[qual].hitbox.anda45Base.min.z + humano->npc[qual].posicao.z;
    humano->npc[qual].hitbox.anda45.max.z = humano->npc[qual].hitbox.anda45Base.max.z + humano->npc[qual].posicao.z;
    humano->npc[qual].hitbox.anda45.min.y = humano->npc[qual].hitbox.anda45Base.min.y + humano->npc[qual].posicao.y;
    humano->npc[qual].hitbox.anda45.max.y = humano->npc[qual].hitbox.anda45Base.max.y + humano->npc[qual].posicao.y;
    
    humano->npc[qual].hitbox.anda90.min.x = humano->npc[qual].hitbox.anda90Base.min.x + humano->npc[qual].posicao.x;
    humano->npc[qual].hitbox.anda90.max.x = humano->npc[qual].hitbox.anda90Base.max.x + humano->npc[qual].posicao.x;
    humano->npc[qual].hitbox.anda90.min.z = humano->npc[qual].hitbox.anda90Base.min.z + humano->npc[qual].posicao.z;
    humano->npc[qual].hitbox.anda90.max.z = humano->npc[qual].hitbox.anda90Base.max.z + humano->npc[qual].posicao.z;
    humano->npc[qual].hitbox.anda90.min.y = humano->npc[qual].hitbox.anda90Base.min.y + humano->npc[qual].posicao.y;
    humano->npc[qual].hitbox.anda90.max.y = humano->npc[qual].hitbox.anda90Base.max.y + humano->npc[qual].posicao.y;
    
    humano->npc[qual].hitbox.anda135.min.x = humano->npc[qual].hitbox.anda135Base.min.x + humano->npc[qual].posicao.x;
    humano->npc[qual].hitbox.anda135.max.x = humano->npc[qual].hitbox.anda135Base.max.x + humano->npc[qual].posicao.x;
    humano->npc[qual].hitbox.anda135.min.z = humano->npc[qual].hitbox.anda135Base.min.z + humano->npc[qual].posicao.z;
    humano->npc[qual].hitbox.anda135.max.z = humano->npc[qual].hitbox.anda135Base.max.z + humano->npc[qual].posicao.z;
    humano->npc[qual].hitbox.anda135.min.y = humano->npc[qual].hitbox.anda135Base.min.y + humano->npc[qual].posicao.y;
    humano->npc[qual].hitbox.anda135.max.y = humano->npc[qual].hitbox.anda135Base.max.y + humano->npc[qual].posicao.y;
    
    humano->npc[qual].hitbox.anda180.min.x = humano->npc[qual].hitbox.anda180Base.min.x + humano->npc[qual].posicao.x;
    humano->npc[qual].hitbox.anda180.max.x = humano->npc[qual].hitbox.anda180Base.max.x + humano->npc[qual].posicao.x;
    humano->npc[qual].hitbox.anda180.min.z = humano->npc[qual].hitbox.anda180Base.min.z + humano->npc[qual].posicao.z;
    humano->npc[qual].hitbox.anda180.max.z = humano->npc[qual].hitbox.anda180Base.max.z + humano->npc[qual].posicao.z;
    humano->npc[qual].hitbox.anda180.min.y = humano->npc[qual].hitbox.anda180Base.min.y + humano->npc[qual].posicao.y;
    humano->npc[qual].hitbox.anda180.max.y = humano->npc[qual].hitbox.anda180Base.max.y + humano->npc[qual].posicao.y;
    
    humano->npc[qual].hitbox.anda225.min.x = humano->npc[qual].hitbox.anda225Base.min.x + humano->npc[qual].posicao.x;
    humano->npc[qual].hitbox.anda225.max.x = humano->npc[qual].hitbox.anda225Base.max.x + humano->npc[qual].posicao.x;
    humano->npc[qual].hitbox.anda225.min.z = humano->npc[qual].hitbox.anda225Base.min.z + humano->npc[qual].posicao.z;
    humano->npc[qual].hitbox.anda225.max.z = humano->npc[qual].hitbox.anda225Base.max.z + humano->npc[qual].posicao.z;
    humano->npc[qual].hitbox.anda225.min.y = humano->npc[qual].hitbox.anda225Base.min.y + humano->npc[qual].posicao.y;
    humano->npc[qual].hitbox.anda225.max.y = humano->npc[qual].hitbox.anda225Base.max.y + humano->npc[qual].posicao.y;
    
    humano->npc[qual].hitbox.anda270.min.x = humano->npc[qual].hitbox.anda270Base.min.x + humano->npc[qual].posicao.x;
    humano->npc[qual].hitbox.anda270.max.x = humano->npc[qual].hitbox.anda270Base.max.x + humano->npc[qual].posicao.x;
    humano->npc[qual].hitbox.anda270.min.z = humano->npc[qual].hitbox.anda270Base.min.z + humano->npc[qual].posicao.z;
    humano->npc[qual].hitbox.anda270.max.z = humano->npc[qual].hitbox.anda270Base.max.z + humano->npc[qual].posicao.z;
    humano->npc[qual].hitbox.anda270.min.y = humano->npc[qual].hitbox.anda270Base.min.y + humano->npc[qual].posicao.y;
    humano->npc[qual].hitbox.anda270.max.y = humano->npc[qual].hitbox.anda270Base.max.y + humano->npc[qual].posicao.y;
    
    humano->npc[qual].hitbox.anda315.min.x = humano->npc[qual].hitbox.anda315Base.min.x + humano->npc[qual].posicao.x;
    humano->npc[qual].hitbox.anda315.max.x = humano->npc[qual].hitbox.anda315Base.max.x + humano->npc[qual].posicao.x;
    humano->npc[qual].hitbox.anda315.min.z = humano->npc[qual].hitbox.anda315Base.min.z + humano->npc[qual].posicao.z;
    humano->npc[qual].hitbox.anda315.max.z = humano->npc[qual].hitbox.anda315Base.max.z + humano->npc[qual].posicao.z;
    humano->npc[qual].hitbox.anda315.min.y = humano->npc[qual].hitbox.anda315Base.min.y + humano->npc[qual].posicao.y;
    humano->npc[qual].hitbox.anda315.max.y = humano->npc[qual].hitbox.anda315Base.max.y + humano->npc[qual].posicao.y;
    
    humano->npc[qual].hitbox.frenteAtual.min.y = humano->npc[qual].hitbox.frenteBase.min.y + humano->npc[qual].posicao.y;
    humano->npc[qual].hitbox.frenteAtual.max.y = humano->npc[qual].hitbox.frenteBase.max.y + humano->npc[qual].posicao.y;
    humano->npc[qual].hitbox.trasAtual.min.y = humano->npc[qual].hitbox.trasBase.min.y + humano->npc[qual].posicao.y;
    humano->npc[qual].hitbox.trasAtual.max.y = humano->npc[qual].hitbox.trasBase.max.y + humano->npc[qual].posicao.y;
    humano->npc[qual].hitbox.pesAtual.min.y = humano->npc[qual].hitbox.pesBase.min.y + humano->npc[qual].posicao.y;
    humano->npc[qual].hitbox.pesAtual.max.y = humano->npc[qual].hitbox.pesBase.max.y + humano->npc[qual].posicao.y;
    humano->npc[qual].hitbox.use.min.y = humano->npc[qual].hitbox.useBase.min.y + humano->npc[qual].posicao.y;
    humano->npc[qual].hitbox.use.max.y = humano->npc[qual].hitbox.useBase.max.y + humano->npc[qual].posicao.y;
    
    if(humano->npc[qual].rotacao == 0 )
    {
        humano->npc[qual].hitbox.use.min.x = humano->npc[qual].hitbox.useBase.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.use.max.x = humano->npc[qual].hitbox.useBase.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.use.min.z = humano->npc[qual].hitbox.useBase.min.z + humano->npc[qual].posicao.z+ET_diferencaF(humano->npc[qual].hitbox.useBase.min.z,humano->npc[qual].hitbox.useBase.max.z);
        humano->npc[qual].hitbox.use.max.z = humano->npc[qual].hitbox.useBase.max.z + humano->npc[qual].posicao.z+ET_diferencaF(humano->npc[qual].hitbox.useBase.min.z,humano->npc[qual].hitbox.useBase.max.z);
        
        humano->npc[qual].hitbox.trasAtual.min.x = humano->npc[qual].hitbox.trasBase.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.trasAtual.max.x = humano->npc[qual].hitbox.trasBase.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.trasAtual.min.z = humano->npc[qual].hitbox.trasBase.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.trasAtual.max.z = humano->npc[qual].hitbox.trasBase.max.z + humano->npc[qual].posicao.z;
        
        humano->npc[qual].hitbox.frenteAtual.min.x = humano->npc[qual].hitbox.frenteBase.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.frenteAtual.max.x = humano->npc[qual].hitbox.frenteBase.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.frenteAtual.min.z = humano->npc[qual].hitbox.frenteBase.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.frenteAtual.max.z = humano->npc[qual].hitbox.frenteBase.max.z + humano->npc[qual].posicao.z;
        
        humano->npc[qual].hitbox.pesAtual.min.x = humano->npc[qual].hitbox.pesBase.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.pesAtual.max.x = humano->npc[qual].hitbox.pesBase.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.pesAtual.min.z = humano->npc[qual].hitbox.pesBase.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.pesAtual.max.z = humano->npc[qual].hitbox.pesBase.max.z + humano->npc[qual].posicao.z;
    }
    else if(humano->npc[qual].rotacao ==45)
    {
        humano->npc[qual].hitbox.use.min.x = humano->npc[qual].hitbox.useBase.min.x + humano->npc[qual].posicao.x +ET_diferencaF(humano->npc[qual].hitbox.useBase.min.x,humano->npc[qual].hitbox.useBase.max.x);
        humano->npc[qual].hitbox.use.max.x = humano->npc[qual].hitbox.useBase.max.x + humano->npc[qual].posicao.x +ET_diferencaF(humano->npc[qual].hitbox.useBase.min.x,humano->npc[qual].hitbox.useBase.max.x);
        humano->npc[qual].hitbox.use.min.z = humano->npc[qual].hitbox.useBase.min.z + humano->npc[qual].posicao.z +ET_diferencaF(humano->npc[qual].hitbox.useBase.min.z,humano->npc[qual].hitbox.useBase.max.z);
        humano->npc[qual].hitbox.use.max.z = humano->npc[qual].hitbox.useBase.max.z + humano->npc[qual].posicao.z +ET_diferencaF(humano->npc[qual].hitbox.useBase.min.z,humano->npc[qual].hitbox.useBase.max.z);
        
        humano->npc[qual].hitbox.trasAtual.min.x = humano->npc[qual].hitbox.tras45.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.trasAtual.max.x = humano->npc[qual].hitbox.tras45.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.trasAtual.min.z = humano->npc[qual].hitbox.tras45.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.trasAtual.max.z = humano->npc[qual].hitbox.tras45.max.z + humano->npc[qual].posicao.z;
        
        humano->npc[qual].hitbox.frenteAtual.min.x = humano->npc[qual].hitbox.frente45.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.frenteAtual.max.x = humano->npc[qual].hitbox.frente45.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.frenteAtual.min.z = humano->npc[qual].hitbox.frente45.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.frenteAtual.max.z = humano->npc[qual].hitbox.frente45.max.z + humano->npc[qual].posicao.z;
        
        humano->npc[qual].hitbox.pesAtual.min.x = humano->npc[qual].hitbox.pesBase.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.pesAtual.max.x = humano->npc[qual].hitbox.pesBase.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.pesAtual.min.z = humano->npc[qual].hitbox.pesBase.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.pesAtual.max.z = humano->npc[qual].hitbox.pesBase.max.z + humano->npc[qual].posicao.z;
    }
    else if(humano->npc[qual].rotacao == 90)
    {
        humano->npc[qual].hitbox.use.min.x = humano->npc[qual].hitbox.useBase.min.x + humano->npc[qual].posicao.x +ET_diferencaF(humano->npc[qual].hitbox.useBase.min.x,humano->npc[qual].hitbox.useBase.max.x);
        humano->npc[qual].hitbox.use.max.x = humano->npc[qual].hitbox.useBase.max.x + humano->npc[qual].posicao.x +ET_diferencaF(humano->npc[qual].hitbox.useBase.min.x,humano->npc[qual].hitbox.useBase.max.x);
        humano->npc[qual].hitbox.use.min.z = humano->npc[qual].hitbox.useBase.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.use.max.z = humano->npc[qual].hitbox.useBase.max.z + humano->npc[qual].posicao.z;
        
        humano->npc[qual].hitbox.trasAtual.min.x = humano->npc[qual].hitbox.tras90.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.trasAtual.max.x = humano->npc[qual].hitbox.tras90.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.trasAtual.min.z = humano->npc[qual].hitbox.tras90.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.trasAtual.max.z = humano->npc[qual].hitbox.tras90.max.z + humano->npc[qual].posicao.z;
        
        humano->npc[qual].hitbox.frenteAtual.min.x = humano->npc[qual].hitbox.frente90.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.frenteAtual.max.x = humano->npc[qual].hitbox.frente90.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.frenteAtual.min.z = humano->npc[qual].hitbox.frente90.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.frenteAtual.max.z = humano->npc[qual].hitbox.frente90.max.z + humano->npc[qual].posicao.z;
        
        humano->npc[qual].hitbox.pesAtual.min.x = humano->npc[qual].hitbox.pes90.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.pesAtual.max.x = humano->npc[qual].hitbox.pes90.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.pesAtual.min.z = humano->npc[qual].hitbox.pes90.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.pesAtual.max.z = humano->npc[qual].hitbox.pes90.max.z + humano->npc[qual].posicao.z;
    }
    else if(humano->npc[qual].rotacao == 135)
    {
        humano->npc[qual].hitbox.use.min.x = humano->npc[qual].hitbox.useBase.min.x + humano->npc[qual].posicao.x +ET_diferencaF(humano->npc[qual].hitbox.useBase.min.x,humano->npc[qual].hitbox.useBase.max.x);
        humano->npc[qual].hitbox.use.max.x = humano->npc[qual].hitbox.useBase.max.x + humano->npc[qual].posicao.x +ET_diferencaF(humano->npc[qual].hitbox.useBase.min.x,humano->npc[qual].hitbox.useBase.max.x);
        humano->npc[qual].hitbox.use.min.z = humano->npc[qual].hitbox.useBase.min.z + humano->npc[qual].posicao.z -ET_diferencaF(humano->npc[qual].hitbox.useBase.min.z,humano->npc[qual].hitbox.useBase.max.z);
        humano->npc[qual].hitbox.use.max.z = humano->npc[qual].hitbox.useBase.max.z + humano->npc[qual].posicao.z -ET_diferencaF(humano->npc[qual].hitbox.useBase.min.z,humano->npc[qual].hitbox.useBase.max.z);
        humano->npc[qual].hitbox.trasAtual.min.x = humano->npc[qual].hitbox.tras135.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.trasAtual.max.x = humano->npc[qual].hitbox.tras135.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.trasAtual.min.z = humano->npc[qual].hitbox.tras135.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.trasAtual.max.z = humano->npc[qual].hitbox.tras135.max.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.frenteAtual.min.x = humano->npc[qual].hitbox.frente135.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.frenteAtual.max.x = humano->npc[qual].hitbox.frente135.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.frenteAtual.min.z = humano->npc[qual].hitbox.frente135.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.frenteAtual.max.z = humano->npc[qual].hitbox.frente135.max.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.pesAtual.min.x = humano->npc[qual].hitbox.pes90.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.pesAtual.max.x = humano->npc[qual].hitbox.pes90.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.pesAtual.min.z = humano->npc[qual].hitbox.pes90.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.pesAtual.max.z = humano->npc[qual].hitbox.pes90.max.z + humano->npc[qual].posicao.z;
    }
    else if(humano->npc[qual].rotacao == 180)
    {
        humano->npc[qual].hitbox.use.min.x = humano->npc[qual].hitbox.useBase.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.use.max.x = humano->npc[qual].hitbox.useBase.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.use.min.z = humano->npc[qual].hitbox.useBase.min.z + humano->npc[qual].posicao.z -ET_diferencaF(humano->npc[qual].hitbox.useBase.min.z,humano->npc[qual].hitbox.useBase.max.z);
        humano->npc[qual].hitbox.use.max.z = humano->npc[qual].hitbox.useBase.max.z + humano->npc[qual].posicao.z -ET_diferencaF(humano->npc[qual].hitbox.useBase.min.z,humano->npc[qual].hitbox.useBase.max.z);
        humano->npc[qual].hitbox.trasAtual.min.x = humano->npc[qual].hitbox.tras180.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.trasAtual.max.x = humano->npc[qual].hitbox.tras180.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.trasAtual.min.z = humano->npc[qual].hitbox.tras180.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.trasAtual.max.z = humano->npc[qual].hitbox.tras180.max.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.frenteAtual.min.x = humano->npc[qual].hitbox.frente180.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.frenteAtual.max.x = humano->npc[qual].hitbox.frente180.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.frenteAtual.min.z = humano->npc[qual].hitbox.frente180.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.frenteAtual.max.z = humano->npc[qual].hitbox.frente180.max.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.pesAtual.min.x = humano->npc[qual].hitbox.pes180.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.pesAtual.max.x = humano->npc[qual].hitbox.pes180.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.pesAtual.min.z = humano->npc[qual].hitbox.pes180.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.pesAtual.max.z = humano->npc[qual].hitbox.pes180.max.z + humano->npc[qual].posicao.z;
    }
    else if(humano->npc[qual].rotacao == 225)
    {
        humano->npc[qual].hitbox.use.min.z = humano->npc[qual].hitbox.useBase.min.z + humano->npc[qual].posicao.z -ET_diferencaF(humano->npc[qual].hitbox.useBase.min.z,humano->npc[qual].hitbox.useBase.max.z);
        humano->npc[qual].hitbox.use.max.z = humano->npc[qual].hitbox.useBase.max.z + humano->npc[qual].posicao.z -ET_diferencaF(humano->npc[qual].hitbox.useBase.min.z,humano->npc[qual].hitbox.useBase.max.z);
        humano->npc[qual].hitbox.use.min.x = humano->npc[qual].hitbox.useBase.min.x + humano->npc[qual].posicao.x -ET_diferencaF(humano->npc[qual].hitbox.useBase.min.x,humano->npc[qual].hitbox.useBase.max.x);
        humano->npc[qual].hitbox.use.max.x = humano->npc[qual].hitbox.useBase.max.x + humano->npc[qual].posicao.x -ET_diferencaF(humano->npc[qual].hitbox.useBase.min.x,humano->npc[qual].hitbox.useBase.max.x);
        humano->npc[qual].hitbox.trasAtual.min.x = humano->npc[qual].hitbox.tras225.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.trasAtual.max.x = humano->npc[qual].hitbox.tras225.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.trasAtual.min.z = humano->npc[qual].hitbox.tras225.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.trasAtual.max.z = humano->npc[qual].hitbox.tras225.max.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.frenteAtual.min.x = humano->npc[qual].hitbox.frente225.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.frenteAtual.max.x = humano->npc[qual].hitbox.frente225.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.frenteAtual.min.z = humano->npc[qual].hitbox.frente225.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.frenteAtual.max.z = humano->npc[qual].hitbox.frente225.max.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.pesAtual.min.x = humano->npc[qual].hitbox.pes180.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.pesAtual.max.x = humano->npc[qual].hitbox.pes180.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.pesAtual.min.z = humano->npc[qual].hitbox.pes180.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.pesAtual.max.z = humano->npc[qual].hitbox.pes180.max.z + humano->npc[qual].posicao.z;
    }
    else if(humano->npc[qual].rotacao == 270)
    {
        humano->npc[qual].hitbox.use.min.x = humano->npc[qual].hitbox.useBase.min.x + humano->npc[qual].posicao.x -ET_diferencaF(humano->npc[qual].hitbox.useBase.min.x,humano->npc[qual].hitbox.useBase.max.x);
        humano->npc[qual].hitbox.use.max.x = humano->npc[qual].hitbox.useBase.max.x + humano->npc[qual].posicao.x -ET_diferencaF(humano->npc[qual].hitbox.useBase.min.x,humano->npc[qual].hitbox.useBase.max.x);
        humano->npc[qual].hitbox.use.min.z = humano->npc[qual].hitbox.useBase.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.use.max.z = humano->npc[qual].hitbox.useBase.max.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.trasAtual.min.x = humano->npc[qual].hitbox.tras270.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.trasAtual.max.x = humano->npc[qual].hitbox.tras270.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.trasAtual.min.z = humano->npc[qual].hitbox.tras270.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.trasAtual.max.z = humano->npc[qual].hitbox.tras270.max.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.frenteAtual.min.x = humano->npc[qual].hitbox.frente270.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.frenteAtual.max.x = humano->npc[qual].hitbox.frente270.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.frenteAtual.min.z = humano->npc[qual].hitbox.frente270.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.frenteAtual.max.z = humano->npc[qual].hitbox.frente270.max.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.pesAtual.min.x = humano->npc[qual].hitbox.pes270.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.pesAtual.max.x = humano->npc[qual].hitbox.pes270.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.pesAtual.min.z = humano->npc[qual].hitbox.pes270.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.pesAtual.max.z = humano->npc[qual].hitbox.pes270.max.z + humano->npc[qual].posicao.z;
    }
    else if(humano->npc[qual].rotacao == 315)
    {
        humano->npc[qual].hitbox.use.min.x = humano->npc[qual].hitbox.useBase.min.x + humano->npc[qual].posicao.x -ET_diferencaF(humano->npc[qual].hitbox.useBase.min.x,humano->npc[qual].hitbox.useBase.max.x);
        humano->npc[qual].hitbox.use.max.x = humano->npc[qual].hitbox.useBase.max.x + humano->npc[qual].posicao.x -ET_diferencaF(humano->npc[qual].hitbox.useBase.min.x,humano->npc[qual].hitbox.useBase.max.x);
        humano->npc[qual].hitbox.use.min.z = humano->npc[qual].hitbox.useBase.min.z + humano->npc[qual].posicao.z+ET_diferencaF(humano->npc[qual].hitbox.useBase.min.z,humano->npc[qual].hitbox.useBase.max.z);
        humano->npc[qual].hitbox.use.max.z = humano->npc[qual].hitbox.useBase.max.z + humano->npc[qual].posicao.z+ET_diferencaF(humano->npc[qual].hitbox.useBase.min.z,humano->npc[qual].hitbox.useBase.max.z);
        humano->npc[qual].hitbox.trasAtual.min.x = humano->npc[qual].hitbox.tras315.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.trasAtual.max.x = humano->npc[qual].hitbox.tras315.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.trasAtual.min.z = humano->npc[qual].hitbox.tras315.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.trasAtual.max.z = humano->npc[qual].hitbox.tras315.max.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.frenteAtual.min.x = humano->npc[qual].hitbox.frente315.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.frenteAtual.max.x = humano->npc[qual].hitbox.frente315.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.frenteAtual.min.z = humano->npc[qual].hitbox.frente315.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.frenteAtual.max.z = humano->npc[qual].hitbox.frente315.max.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.pesAtual.min.x = humano->npc[qual].hitbox.pes270.min.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.pesAtual.max.x = humano->npc[qual].hitbox.pes270.max.x + humano->npc[qual].posicao.x;
        humano->npc[qual].hitbox.pesAtual.min.z = humano->npc[qual].hitbox.pes270.min.z + humano->npc[qual].posicao.z;
        humano->npc[qual].hitbox.pesAtual.max.z = humano->npc[qual].hitbox.pes270.max.z + humano->npc[qual].posicao.z;
    }
}

void AIHUMAN_ANDA(NPC0* humano, MAPA mapa,int qual)
{
    if(humano->npc[qual].andando == false)
    {
        humano->npc[qual].andando = true;
        humano->npc[qual].modelo.frame = 0;
    }
    
    if(humano->npc[qual].rotacao == -45)
    {
        humano->npc[qual].rotacao = 315;
    }
    else if(humano->npc[qual].rotacao == 405)
    {
        humano->npc[qual].rotacao = 45;
    }
    
    if(humano->npc[qual].rotacao == 0||humano->npc[qual].rotacao == 360)
    {

        if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda0, humano->npc[qual].hitbox.andaAlvo ))
        {
            if(AIHUMAN_CHECARPAREDE(humano->npc[qual], mapa, qual ) == false)
            {
                humano->npc[qual].posicao.z += humano->npc[qual].velocidade;
            }
            else 
            {
                for(int i = 0; i <5; i++)
                {
                    if(CheckCollisionBoxes(humano->npc[qual].hitbox.frenteAtual, mapa.porta.slots[i].hitbox))
                    {
                        AIHUMAN_USE_PRESS( &humano->npc[qual]);
                    }
                }
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda45, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda90, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda135, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda180, humano->npc[qual].hitbox.andaAlvo ))
        {
            if(clock()%2 == 0)
            {
                humano->npc[qual].rotacao -= 45;
            }
            else
            {
                humano->npc[qual].rotacao += 45;
            }
            
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda225, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda270, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda315, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
    }
    //45
    else if(humano->npc[qual].rotacao == 45)
    {
        if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda0, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda45, humano->npc[qual].hitbox.andaAlvo ))
        {
            if(AIHUMAN_CHECARPAREDE(humano->npc[qual], mapa, qual ) == false)
            {
                humano->npc[qual].posicao.z += humano->npc[qual].velocidade/1.5;
                humano->npc[qual].posicao.x += humano->npc[qual].velocidade/1.5;
            }
            else 
            {
                for(int i = 0; i <5; i++)
                {
                    if(CheckCollisionBoxes(humano->npc[qual].hitbox.frenteAtual, mapa.porta.slots[i].hitbox))
                    {
                        AIHUMAN_USE_PRESS( &humano->npc[qual]);
                    }
                }
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda90, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda135, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda180, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda225, humano->npc[qual].hitbox.andaAlvo ))
        {
            if(clock()%2 == 0)
            {
                humano->npc[qual].rotacao -= 45;
            }
            else
            {
                humano->npc[qual].rotacao += 45;
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda270, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda315, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
    }
    //90
    else if(humano->npc[qual].rotacao == 90)
    {
        if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda0, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda45, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda90, humano->npc[qual].hitbox.andaAlvo ))
        {
            if(AIHUMAN_CHECARPAREDE(humano->npc[qual], mapa, qual ) == false)
            {
                humano->npc[qual].posicao.x += humano->npc[qual].velocidade;
            }
            else 
            {
                for(int i = 0; i <5; i++)
                {
                    if(CheckCollisionBoxes(humano->npc[qual].hitbox.frenteAtual, mapa.porta.slots[i].hitbox))
                    {
                        AIHUMAN_USE_PRESS( &humano->npc[qual]);
                    }
                }
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda135, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda180, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda225, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda270, humano->npc[qual].hitbox.andaAlvo ))
        {
            if(clock()%2 == 0)
            {
                humano->npc[qual].rotacao -= 45;
            }
            else
            {
                humano->npc[qual].rotacao += 45;
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda315, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
    }
    //135
    else if(humano->npc[qual].rotacao == 135)
    {
        if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda0, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda45, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda90, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda135, humano->npc[qual].hitbox.andaAlvo ))
        {
            if(AIHUMAN_CHECARPAREDE(humano->npc[qual], mapa, qual ) == false)
            {
                humano->npc[qual].posicao.z -= humano->npc[qual].velocidade/1.5;
                humano->npc[qual].posicao.x += humano->npc[qual].velocidade/1.5;
            }
            else 
            {
                for(int i = 0; i <5; i++)
                {
                    if(CheckCollisionBoxes(humano->npc[qual].hitbox.frenteAtual, mapa.porta.slots[i].hitbox))
                    {
                        AIHUMAN_USE_PRESS( &humano->npc[qual]);
                    }
                }
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda180, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda225, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda270, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda315, humano->npc[qual].hitbox.andaAlvo ))
        {
            if(clock()%2 == 0)
            {
                humano->npc[qual].rotacao -= 45;
            }
            else
            {
                humano->npc[qual].rotacao += 45;
            }
        }
    }
    //180
    else if(humano->npc[qual].rotacao == 180)
    {
        if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda0, humano->npc[qual].hitbox.andaAlvo ))
        {
            if(clock()%2 == 0)
            {
                humano->npc[qual].rotacao -= 45;
            }
            else
            {
                humano->npc[qual].rotacao += 45;
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda45, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda90, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda135, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda180, humano->npc[qual].hitbox.andaAlvo ))
        {
            if(AIHUMAN_CHECARPAREDE(humano->npc[qual], mapa, qual ) == false)
            {
                humano->npc[qual].posicao.z -= humano->npc[qual].velocidade;
            }
            else 
            {
                for(int i = 0; i <5; i++)
                {
                    if(CheckCollisionBoxes(humano->npc[qual].hitbox.frenteAtual, mapa.porta.slots[i].hitbox))
                    {
                        AIHUMAN_USE_PRESS( &humano->npc[qual]);
                    }
                }
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda225, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda270, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda315, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
    }
    //225
    else if(humano->npc[qual].rotacao == 225)
    {
        if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda0, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda45, humano->npc[qual].hitbox.andaAlvo ))
        {
            if(clock()%2 == 0)
            {
                humano->npc[qual].rotacao -= 45;
            }
            else
            {
                humano->npc[qual].rotacao += 45;
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda90, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda135, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda180, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda225, humano->npc[qual].hitbox.andaAlvo ))
        {
            if(AIHUMAN_CHECARPAREDE(humano->npc[qual], mapa, qual ) == false)
            {
                humano->npc[qual].posicao.z -= humano->npc[qual].velocidade/1.5;
                humano->npc[qual].posicao.x -= humano->npc[qual].velocidade/1.5;
            }
            else 
            {
                for(int i = 0; i <5; i++)
                {
                    if(CheckCollisionBoxes(humano->npc[qual].hitbox.frenteAtual, mapa.porta.slots[i].hitbox))
                    {
                        AIHUMAN_USE_PRESS( &humano->npc[qual]);
                    }
                }
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda270, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda315, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
    }
    //270
    else if(humano->npc[qual].rotacao == 270)
    {
        if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda0, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda45, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda90, humano->npc[qual].hitbox.andaAlvo ))
        {
            if(clock()%2 == 0)
            {
                humano->npc[qual].rotacao -= 45;
            }
            else
            {
                humano->npc[qual].rotacao += 45;
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda135, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda180, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda225, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda270, humano->npc[qual].hitbox.andaAlvo ))
        {
            if(AIHUMAN_CHECARPAREDE(humano->npc[qual], mapa, qual ) == false)
            {
                humano->npc[qual].posicao.x -= humano->npc[qual].velocidade;
            }
            else 
            {
                for(int i = 0; i <5; i++)
                {
                    if(CheckCollisionBoxes(humano->npc[qual].hitbox.frenteAtual, mapa.porta.slots[i].hitbox))
                    {
                        AIHUMAN_USE_PRESS( &humano->npc[qual]);
                    }
                }
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda315, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
    }
    //315
    else if(humano->npc[qual].rotacao == 315)
    {
        if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda0, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda45, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda90, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda135, humano->npc[qual].hitbox.andaAlvo ))
        {
            if(clock()%2 == 0)
            {
                humano->npc[qual].rotacao -= 45;
            }
            else
            {
                humano->npc[qual].rotacao += 45;
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda180, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda225, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda270, humano->npc[qual].hitbox.andaAlvo ))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda315, humano->npc[qual].hitbox.andaAlvo ))
        {
            if(AIHUMAN_CHECARPAREDE(humano->npc[qual], mapa, qual ) == false)
            {
                humano->npc[qual].posicao.z += humano->npc[qual].velocidade/1.5;
                humano->npc[qual].posicao.x -= humano->npc[qual].velocidade/1.5;
            }
            else 
            {
                for(int i = 0; i <5; i++)
                {
                    if(CheckCollisionBoxes(humano->npc[qual].hitbox.frenteAtual, mapa.porta.slots[i].hitbox))
                    {
                        AIHUMAN_USE_PRESS( &humano->npc[qual]);
                    }
                }
            }
        }
    }
}

void AIHUMAN_MOVIMENTO(PERSONAGEM personagem, MAPA mapa,NPC0* humano, int qual, ITEM item)
{
    humano->npc[qual].relogioAndaN = clock();
    if(humano->npc[qual].relogioAndaN > humano->npc[qual].relogioAndaV +10000)
    {
        humano->npc[qual].relogioAndaV = humano->npc[qual].relogioAndaN;
        if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda45,humano->npc[qual].hitbox.andaAlvo ))
        {
            AIHUMAN_ANDA(*&humano, mapa ,qual);
            AIHUMAN_ANIMARUN(personagem, *&humano, 0, item);
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda135,humano->npc[qual].hitbox.andaAlvo ))
        {
            AIHUMAN_ANDA(*&humano, mapa ,qual);
            AIHUMAN_ANIMARUN(personagem, *&humano, 0, item);
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda225,humano->npc[qual].hitbox.andaAlvo ))
        {
            AIHUMAN_ANDA(*&humano, mapa ,qual);
            AIHUMAN_ANIMARUN(personagem, *&humano, 0, item);
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda315,humano->npc[qual].hitbox.andaAlvo ))
        {
            AIHUMAN_ANDA(*&humano, mapa ,qual);
            AIHUMAN_ANIMARUN(personagem, *&humano, 0, item);
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda0,humano->npc[qual].hitbox.andaAlvo ))
        {
            AIHUMAN_ANDA(*&humano, mapa ,qual);
            AIHUMAN_ANIMARUN(personagem, *&humano, 0, item);
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda90,humano->npc[qual].hitbox.andaAlvo ))
        {
            AIHUMAN_ANDA(*&humano, mapa ,qual);
            AIHUMAN_ANIMARUN(personagem, *&humano, 0, item);
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda180,humano->npc[qual].hitbox.andaAlvo ))
        {
            AIHUMAN_ANDA(*&humano, mapa ,qual);
            AIHUMAN_ANIMARUN(personagem, *&humano, 0, item);
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda270,humano->npc[qual].hitbox.andaAlvo ))
        {
            AIHUMAN_ANDA(*&humano, mapa ,qual);
            AIHUMAN_ANIMARUN(personagem, *&humano, 0, item);
        }
        else
        {
            humano->npc[qual].andando = false;
            humano->npc[qual].modelo.frame = 0;
            humano->npc[qual].modelo.atual = personagem.modelo.idle;
            
            if(humano->npc[qual].equip.calca.ponteiro != 0)
                humano->npc[qual].equip.calca.modelo = item.calca[humano->npc[qual].equip.calca.ponteiro].idle;
            if(humano->npc[qual].equip.chapeu.ponteiro != 0)
                humano->npc[qual].equip.chapeu.modelo = item.chapeu[humano->npc[qual].equip.chapeu.ponteiro].idle;
            if(humano->npc[qual].equip.camisa.ponteiro != 0)
                humano->npc[qual].equip.camisa.modelo = item.camisa[humano->npc[qual].equip.camisa.ponteiro].idle;
            if(humano->npc[qual].equip.arma.ponteiro != 0)
                humano->npc[qual].equip.arma.modelo = item.arma[humano->npc[qual].equip.arma.ponteiro].idle;
        }
    }
    AIHUMAN_HITBOXUPDATE(*&humano,qual);
}

HUMANO_NPC AIHUMAN_CONFIGSTART(PERSONAGEM personagem, NPC0 humano, int qual, Vector3 posicao)
{
	humano.npc[qual].equip.chapeu.ponteiro = 1;
	humano.npc[qual].equip.camisa.ponteiro = 1;
	humano.npc[qual].equip.oculos.ponteiro = 0;
	humano.npc[qual].equip.sapato.ponteiro = 0;
	humano.npc[qual].equip.calca.ponteiro = 1;
    humano.npc[qual].equip.arma.ponteiro = 1;
	humano.npc[qual].rotacao = 0;
	humano.npc[qual].modelo.frame = 0;
	humano.npc[qual].posicao.y = posicao.y;
	humano.npc[qual].posicao.x = posicao.x;
	humano.npc[qual].posicao.z = posicao.z;
	humano.npc[qual].velocidade = 0.5f;
	humano.npc[qual].modelo.atual = personagem.modelo.idle;
	humano.npc[qual].pulando = false;
	humano.npc[qual].usando = false;
	humano.npc[qual].relogioNovo = 0;
	humano.npc[qual].relogioVelho = 0;
    humano.npc[qual].hitbox.andaAlvo.max.x = 0.1;
    humano.npc[qual].hitbox.andaAlvo.max.y = 0.1;
    humano.npc[qual].hitbox.andaAlvo.max.z = 0.1;
    humano.npc[qual].hitbox.andaAlvo.min.x = -0.1;
    humano.npc[qual].hitbox.andaAlvo.min.y = -0.1;
    humano.npc[qual].hitbox.andaAlvo.min.z = -0.1;
    
    humano.npc[qual].relogioAndaV = 0;
    humano.npc[qual].relogioAndaN = 0;
    
    humano.npc[qual].posicaoInicial = humano.npc[qual].posicao;
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/action.glb");
	humano.npc[qual].hitbox.useBase = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
	humano.npc[qual].hitbox.atual = humano.npc[qual].hitbox.useBase;
	UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/pes.glb");
    humano.npc[qual].hitbox.pesBase = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/pes90.glb");
    humano.npc[qual].hitbox.pes90 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/pes180.glb");
    humano.npc[qual].hitbox.pes180 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/pes270.glb");
    humano.npc[qual].hitbox.pes270 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente.glb");
    humano.npc[qual].hitbox.frenteBase = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras.glb");
    humano.npc[qual].hitbox.trasBase = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente45.glb");
    humano.npc[qual].hitbox.frente45 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras45.glb");
    humano.npc[qual].hitbox.tras45 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente90.glb");
    humano.npc[qual].hitbox.frente90 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras90.glb");
    humano.npc[qual].hitbox.tras90 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente135.glb");
    humano.npc[qual].hitbox.frente135 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras135.glb");
    humano.npc[qual].hitbox.tras135 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente180.glb");
    humano.npc[qual].hitbox.frente180 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras180.glb");
    humano.npc[qual].hitbox.tras180 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente225.glb");
    humano.npc[qual].hitbox.frente225 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras225.glb");
    humano.npc[qual].hitbox.tras225 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente270.glb");
    humano.npc[qual].hitbox.frente270 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras270.glb");
    humano.npc[qual].hitbox.tras270 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente315.glb");
    humano.npc[qual].hitbox.frente315 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras315.glb");
    humano.npc[qual].hitbox.tras315 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/ai/0.glb");
    humano.npc[qual].hitbox.anda0Base = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/ai/45.glb");
    humano.npc[qual].hitbox.anda45Base = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/ai/90.glb");
    humano.npc[qual].hitbox.anda90Base = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/ai/135.glb");
    humano.npc[qual].hitbox.anda135Base = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/ai/180.glb");
    humano.npc[qual].hitbox.anda180Base = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/ai/225.glb");
    humano.npc[qual].hitbox.anda225Base = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/ai/270.glb");
    humano.npc[qual].hitbox.anda270Base = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    
    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/ai/315.glb");
    humano.npc[qual].hitbox.anda315Base = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);
    

    
    return (humano.npc[qual]);
}
