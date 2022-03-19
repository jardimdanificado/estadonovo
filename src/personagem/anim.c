void PERSONAGEM_USEANIM(PERSONAGEM* personagem, MAPA *mapa, ITEM item)
{
	if(personagem->relogioNovo > personagem->relogioVelho+10000)
	{
		personagem->relogioVelho = personagem->relogioNovo;
// 		printf("aoba");

	}
	personagem->relogioNovo = clock();

	if(personagem->relogioNovo > personagem->relogioVelho+10000&&personagem->modelo.frame < 2)
		personagem->modelo.frame++;
	else if(personagem->modelo.frame == 2&&personagem->relogioNovo > personagem->relogioVelho+10000)
		personagem->usando = false;
	switch(personagem->modelo.frame)
	{
		case 0:
		{
			personagem->modelo.atual = personagem->modelo.use_default[0];
            if(personagem->equip.calca != 0)
                personagem->equip.calcaAtual = item.calca[personagem->equip.calca].use[0];
            if(personagem->equip.chapeu != 0)
                personagem->equip.chapeuAtual = item.chapeu[personagem->equip.chapeu].use[0];
            if(personagem->equip.camisa != 0)
                personagem->equip.camisaAtual = item.camisa[personagem->equip.camisa].use[0];
            if(personagem->equip.arma != 0)
                personagem->equip.armaAtual = item.arma[personagem->equip.arma].use[0];
		}
		break;
		case 1:
		{
			personagem->modelo.atual = personagem->modelo.use_default[1];
            if(personagem->equip.calca != 0)
                personagem->equip.calcaAtual = item.calca[personagem->equip.calca].use[1];
            if(personagem->equip.chapeu != 0)
                personagem->equip.chapeuAtual = item.chapeu[personagem->equip.chapeu].use[1];
            if(personagem->equip.camisa != 0)
                personagem->equip.camisaAtual = item.camisa[personagem->equip.camisa].use[1];
            if(personagem->equip.arma != 0)
                personagem->equip.armaAtual = item.arma[personagem->equip.arma].use[0];
            PERSONAGEM_USE(*&personagem, *&mapa);

		}
		break;
        case 2:
		{
			personagem->modelo.atual = personagem->modelo.use_default[2];
            if(personagem->equip.calca != 0)
                personagem->equip.calcaAtual = item.calca[personagem->equip.calca].use[2];
            if(personagem->equip.chapeu != 0)
                personagem->equip.chapeuAtual = item.chapeu[personagem->equip.chapeu].use[2];
            if(personagem->equip.camisa != 0)
                personagem->equip.camisaAtual = item.camisa[personagem->equip.camisa].use[2];
            if(personagem->equip.arma != 0)
                personagem->equip.armaAtual = item.arma[personagem->equip.arma].use[0];
			if(personagem->usando == false)
			{
				personagem->modelo.atual = personagem->modelo.idle;
                if(personagem->equip.calca != 0)
                    personagem->equip.calcaAtual = item.calca[personagem->equip.calca].idle;
                if(personagem->equip.chapeu != 0)
                    personagem->equip.chapeuAtual = item.chapeu[personagem->equip.chapeu].idle;
                if(personagem->equip.camisa != 0)
                    personagem->equip.camisaAtual = item.camisa[personagem->equip.camisa].idle;
                if(personagem->equip.arma != 0)
                    personagem->equip.armaAtual = item.arma[personagem->equip.arma].idle;
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
            if(personagem->equip.calca != 0)
                personagem->equip.calcaAtual = item.calca[personagem->equip.calca].run[0];
            if(personagem->equip.chapeu != 0)
                personagem->equip.chapeuAtual = item.chapeu[personagem->equip.chapeu].run[0];
            if(personagem->equip.camisa != 0)
                personagem->equip.camisaAtual = item.camisa[personagem->equip.camisa].run[0];
            if(personagem->equip.arma != 0)
                personagem->equip.armaAtual = item.arma[personagem->equip.arma].run[0];
            
		}
		break;
		case 1:
		{
			personagem->modelo.atual = personagem->modelo.run[1];
            if(personagem->equip.calca != 0)
                personagem->equip.calcaAtual = item.calca[personagem->equip.calca].run[1];
            if(personagem->equip.chapeu != 0)
                personagem->equip.chapeuAtual = item.chapeu[personagem->equip.chapeu].run[1];
            if(personagem->equip.camisa != 0)
                personagem->equip.camisaAtual = item.camisa[personagem->equip.camisa].run[1];
            if(personagem->equip.arma != 0)
                personagem->equip.armaAtual = item.arma[personagem->equip.arma].run[1];
		}
		break;
		case 2:
		{
			personagem->modelo.atual = personagem->modelo.run[2];
            if(personagem->equip.calca != 0)
                personagem->equip.calcaAtual = item.calca[personagem->equip.calca].run[2];
            if(personagem->equip.chapeu != 0)
                personagem->equip.chapeuAtual = item.chapeu[personagem->equip.chapeu].run[2];
            if(personagem->equip.camisa != 0)
                personagem->equip.camisaAtual = item.camisa[personagem->equip.camisa].run[2];
            if(personagem->equip.arma != 0)
                personagem->equip.armaAtual = item.arma[personagem->equip.arma].run[2];

		}
		break;
		case 3:
		{
			personagem->modelo.atual = personagem->modelo.run[3];
            if(personagem->equip.calca != 0)
                personagem->equip.calcaAtual = item.calca[personagem->equip.calca].run[3];
            if(personagem->equip.chapeu != 0)
                personagem->equip.chapeuAtual = item.chapeu[personagem->equip.chapeu].run[3];
            if(personagem->equip.camisa != 0)
                personagem->equip.camisaAtual = item.camisa[personagem->equip.camisa].run[3];
            if(personagem->equip.arma != 0)
                personagem->equip.armaAtual = item.arma[personagem->equip.arma].run[3];

		}
		break;
		case 4:
		{
			personagem->modelo.atual = personagem->modelo.run[4];
            if(personagem->equip.calca != 0)
                personagem->equip.calcaAtual = item.calca[personagem->equip.calca].run[4];
            if(personagem->equip.chapeu != 0)
                personagem->equip.chapeuAtual = item.chapeu[personagem->equip.chapeu].run[4];
            if(personagem->equip.camisa != 0)
                personagem->equip.camisaAtual = item.camisa[personagem->equip.camisa].run[4];
            if(personagem->equip.arma != 0)
                personagem->equip.armaAtual = item.arma[personagem->equip.arma].run[4];
		}
		break;
	}
}
