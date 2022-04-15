int PERSONAGEM_USEANIM(PERSONAGEM* personagem, MAPA *mapa, ITEM item)
{
	if(personagem->relogioNovo > personagem->relogioVelho+10000)
	{
		personagem->relogioVelho = personagem->relogioNovo;
	}
	personagem->relogioNovo = clock();

	if(personagem->relogioNovo > personagem->relogioVelho+10000&&personagem->modelo.frame < 2)
		personagem->modelo.frame++;
	else if(personagem->modelo.frame == 2&&personagem->relogioNovo > personagem->relogioVelho+10000)
    {
        personagem->usando = false;
        personagem->dropando = false;
    }
	switch(personagem->modelo.frame)
	{
		case 0:
		{
			personagem->modelo.atual = personagem->modelo.use_default[0];
            if(personagem->equip.calca.ponteiro != 0)
                personagem->equip.calca.modelo = item.calca[personagem->equip.calca.ponteiro].use[0];
            if(personagem->equip.chapeu.ponteiro != 0)
                personagem->equip.chapeu.modelo = item.chapeu[personagem->equip.chapeu.ponteiro].use[0];
            if(personagem->equip.camisa.ponteiro != 0)
                personagem->equip.camisa.modelo = item.camisa[personagem->equip.camisa.ponteiro].use[0];
            if(personagem->equip.arma.ponteiro != 0)
                personagem->equip.arma.modelo = item.arma[personagem->equip.arma.ponteiro].use[0];
		}
		break;
		case 1:
		{
			personagem->modelo.atual = personagem->modelo.use_default[1];
            if(personagem->equip.calca.ponteiro != 0)
                personagem->equip.calca.modelo = item.calca[personagem->equip.calca.ponteiro].use[1];
            if(personagem->equip.chapeu.ponteiro != 0)
                personagem->equip.chapeu.modelo = item.chapeu[personagem->equip.chapeu.ponteiro].use[1];
            if(personagem->equip.camisa.ponteiro != 0)
                personagem->equip.camisa.modelo = item.camisa[personagem->equip.camisa.ponteiro].use[1];
            if(personagem->equip.arma.ponteiro != 0)
                personagem->equip.arma.modelo = item.arma[personagem->equip.arma.ponteiro].use[0];
            if(personagem->dropando == false)
                PERSONAGEM_USE(*&personagem, *&mapa);
            else if(personagem->dropando == true)
            {
                int ponteiroLocal;
                if(personagem->equip.arma.ponteiro != 0)
                {
                    ponteiroLocal = personagem->equip.arma.tipo;
                }
                else if(personagem->equip.chapeu.ponteiro != 0)
                {
                    ponteiroLocal = personagem->equip.chapeu.tipo;
                }
                else if(personagem->equip.camisa.ponteiro != 0)
                {
                    ponteiroLocal = personagem->equip.camisa.tipo;
                }
                else if(personagem->equip.calca.ponteiro != 0)
                {
                    ponteiroLocal = personagem->equip.calca.tipo;
                }
                else if(personagem->equip.sapato.ponteiro != 0)
                {
                    ponteiroLocal = personagem->equip.sapato.tipo;
                }
                else if(personagem->equip.oculos.ponteiro != 0)
                {
                    ponteiroLocal = personagem->equip.oculos.tipo;
                }
                
                for(int i = 0; i<10; i++)
                {
                    if(mapa->drops[i].ocupado == false)
                    {
                        switch(ponteiroLocal)
                        {
                            case 5:
                            {
                                mapa->drops[i].modelo = item.arma[personagem->equip.arma.ponteiro].drop;
                                mapa->drops[i].posicao = personagem->posicao;
                                personagem->equip.arma.ponteiro = 0;
                                mapa->drops[i].tipo = personagem->equip.arma.tipo;
                                mapa->drops[i].ponteiro = personagem->equip.arma.ponteiro;
                                personagem->equip.arma.municao = mapa->item[i].municao;
                                personagem->equip.arma.municaoMax = mapa->item[i].municaoMax;
                            }
                            break;
                            case 1:
                            {
                                mapa->drops[i].modelo = item.chapeu[personagem->equip.chapeu.ponteiro].drop;
                                mapa->drops[i].posicao = personagem->posicao;
                                personagem->equip.chapeu.ponteiro = 0;
                                mapa->drops[i].tipo = personagem->equip.chapeu.tipo;
                                mapa->drops[i].ponteiro = personagem->equip.chapeu.ponteiro;
                            }
                            break;
                            case 2:
                            {
                                mapa->drops[i].modelo = item.camisa[personagem->equip.camisa.ponteiro].drop;
                                mapa->drops[i].posicao = personagem->posicao;
                                personagem->equip.camisa.ponteiro = 0;
                                mapa->drops[i].tipo = personagem->equip.camisa.tipo;
                                mapa->drops[i].ponteiro = personagem->equip.camisa.ponteiro;
                            }
                            break;
                            case 0:
                            {
                                mapa->drops[i].modelo = item.calca[personagem->equip.calca.ponteiro].drop;
                                mapa->drops[i].posicao = personagem->posicao;
                                personagem->equip.calca.ponteiro = 0;
                                mapa->drops[i].tipo = personagem->equip.calca.tipo;
                                mapa->drops[i].ponteiro = personagem->equip.calca.ponteiro;
                            }
                            break;
                        }
                        mapa->drops[i].ocupado = true;
                        mapa->drops[i].hitbox = GetModelBoundingBox(mapa->drops[i].modelo);
                        mapa->drops[i].hitbox.max.x += mapa->drops[i].posicao.x;
                        mapa->drops[i].hitbox.min.x += mapa->drops[i].posicao.x;
                        mapa->drops[i].hitbox.max.y += mapa->drops[i].posicao.y;
                        mapa->drops[i].hitbox.min.y += mapa->drops[i].posicao.y;
                        mapa->drops[i].hitbox.max.z += mapa->drops[i].posicao.z;
                        mapa->drops[i].hitbox.min.z += mapa->drops[i].posicao.z;
                        i = 20;
                        return 0;
                    }
                }
            }
		}
		break;
        case 2:
		{
			personagem->modelo.atual = personagem->modelo.use_default[2];
            if(personagem->equip.calca.ponteiro != 0)
                personagem->equip.calca.modelo = item.calca[personagem->equip.calca.ponteiro].use[2];
            if(personagem->equip.chapeu.ponteiro != 0)
                personagem->equip.chapeu.modelo = item.chapeu[personagem->equip.chapeu.ponteiro].use[2];
            if(personagem->equip.camisa.ponteiro != 0)
                personagem->equip.camisa.modelo = item.camisa[personagem->equip.camisa.ponteiro].use[2];
            if(personagem->equip.arma.ponteiro != 0)
                personagem->equip.arma.modelo = item.arma[personagem->equip.arma.ponteiro].use[0];
			if(personagem->usando == false)
			{
				personagem->modelo.atual = personagem->modelo.idle;
                if(personagem->equip.calca.ponteiro != 0)
                    personagem->equip.calca.modelo = item.calca[personagem->equip.calca.ponteiro].idle;
                if(personagem->equip.chapeu.ponteiro != 0)
                    personagem->equip.chapeu.modelo = item.chapeu[personagem->equip.chapeu.ponteiro].idle;
                if(personagem->equip.camisa.ponteiro != 0)
                    personagem->equip.camisa.modelo = item.camisa[personagem->equip.camisa.ponteiro].idle;
                if(personagem->equip.arma.ponteiro != 0)
                    personagem->equip.arma.modelo = item.arma[personagem->equip.arma.ponteiro].idle;
				//msg = " ";
			}
		}
		break;
	}
}

void PERSONAGEM_ANIMARUN(PERSONAGEM *personagem, char local_local, ITEM item)
{
	if(local_local == '+')
	{
		if(personagem->relogioNovo > personagem->relogioVelho+10000)
		{
			personagem->relogioVelho = personagem->relogioNovo;
	// 		printf("aoba");

		}
		personagem->relogioNovo = clock();

		if(personagem->relogioNovo > personagem->relogioVelho+10000&&personagem->modelo.frame < 4)
			personagem->modelo.frame++;
		else if(personagem->modelo.frame == 4)
			personagem->modelo.frame = 0;

	}
	else if(local_local == '-')
	{
		if(personagem->relogioNovo > personagem->relogioVelho+10000)
		{
			personagem->relogioVelho = personagem->relogioNovo;
	// 		printf("aoba");

		}
		personagem->relogioNovo = clock();

		if(personagem->relogioNovo > personagem->relogioVelho+10000&&personagem->modelo.frame > 0)
			personagem->modelo.frame--;
		else if(personagem->modelo.frame == 0)
			personagem->modelo.frame = 4;
	}

	switch(personagem->modelo.frame)
	{
		case 0:
		{
			personagem->modelo.atual = personagem->modelo.run[0];
            if(personagem->equip.calca.ponteiro != 0)
                personagem->equip.calca.modelo = item.calca[personagem->equip.calca.ponteiro].run[0];
            if(personagem->equip.chapeu.ponteiro != 0)
                personagem->equip.chapeu.modelo = item.chapeu[personagem->equip.chapeu.ponteiro].run[0];
            if(personagem->equip.camisa.ponteiro != 0)
                personagem->equip.camisa.modelo = item.camisa[personagem->equip.camisa.ponteiro].run[0];
            if(personagem->equip.arma.ponteiro != 0)
                personagem->equip.arma.modelo = item.arma[personagem->equip.arma.ponteiro].run[0];
            
		}
		break;
		case 1:
		{
			personagem->modelo.atual = personagem->modelo.run[1];
            if(personagem->equip.calca.ponteiro != 0)
                personagem->equip.calca.modelo = item.calca[personagem->equip.calca.ponteiro].run[1];
            if(personagem->equip.chapeu.ponteiro != 0)
                personagem->equip.chapeu.modelo = item.chapeu[personagem->equip.chapeu.ponteiro].run[1];
            if(personagem->equip.camisa.ponteiro != 0)
                personagem->equip.camisa.modelo = item.camisa[personagem->equip.camisa.ponteiro].run[1];
            if(personagem->equip.arma.ponteiro != 0)
                personagem->equip.arma.modelo = item.arma[personagem->equip.arma.ponteiro].run[1];
		}
		break;
		case 2:
		{
			personagem->modelo.atual = personagem->modelo.run[2];
            if(personagem->equip.calca.ponteiro != 0)
                personagem->equip.calca.modelo = item.calca[personagem->equip.calca.ponteiro].run[2];
            if(personagem->equip.chapeu.ponteiro != 0)
                personagem->equip.chapeu.modelo = item.chapeu[personagem->equip.chapeu.ponteiro].run[2];
            if(personagem->equip.camisa.ponteiro != 0)
                personagem->equip.camisa.modelo = item.camisa[personagem->equip.camisa.ponteiro].run[2];
            if(personagem->equip.arma.ponteiro != 0)
                personagem->equip.arma.modelo = item.arma[personagem->equip.arma.ponteiro].run[2];

		}
		break;
		case 3:
		{
			personagem->modelo.atual = personagem->modelo.run[3];
            if(personagem->equip.calca.ponteiro != 0)
                personagem->equip.calca.modelo = item.calca[personagem->equip.calca.ponteiro].run[3];
            if(personagem->equip.chapeu.ponteiro != 0)
                personagem->equip.chapeu.modelo = item.chapeu[personagem->equip.chapeu.ponteiro].run[3];
            if(personagem->equip.camisa.ponteiro != 0)
                personagem->equip.camisa.modelo = item.camisa[personagem->equip.camisa.ponteiro].run[3];
            if(personagem->equip.arma.ponteiro != 0)
                personagem->equip.arma.modelo = item.arma[personagem->equip.arma.ponteiro].run[3];

		}
		break;
		case 4:
		{
			personagem->modelo.atual = personagem->modelo.run[4];
            if(personagem->equip.calca.ponteiro != 0)
                personagem->equip.calca.modelo = item.calca[personagem->equip.calca.ponteiro].run[4];
            if(personagem->equip.chapeu.ponteiro != 0)
                personagem->equip.chapeu.modelo = item.chapeu[personagem->equip.chapeu.ponteiro].run[4];
            if(personagem->equip.camisa.ponteiro != 0)
                personagem->equip.camisa.modelo = item.camisa[personagem->equip.camisa.ponteiro].run[4];
            if(personagem->equip.arma.ponteiro != 0)
                personagem->equip.arma.modelo = item.arma[personagem->equip.arma.ponteiro].run[4];
		}
		break;
	}
}
