
struct HITBOX_PERSONAGEM
{
	// 0
	BoundingBox use,useBase,atual;
    BoundingBox frenteBase, pesBase, pesAtual, frenteAtual;
	Model modelo;
};
typedef struct HITBOX_PERSONAGEM HITBOX_PERSONAGEM;

struct EQUIPAMENTO
{
	int capacete, oculos, camisa, calca, sapato;
	Model capaceteAtual,oculosAtual,camisaAtual,calcaAtual,sapatoAtual;
};
typedef struct EQUIPAMENTO EQUIPAMENTO;

struct MODELO_PERSONAGEM
{
	EQUIPAMENTO equip;
	// 0
	Model idle;
	// 1-5
	Model run[5];
	Model use_default[3];
	Model atual;
	int frame;
};
typedef struct MODELO_PERSONAGEM MODELO_PERSONAGEM;

struct PERSONAGEM
{
	EQUIPAMENTO equip;
	Vector3 posicao;
	MODELO_PERSONAGEM modelo;
	//BOUNDS bounds;
	HITBOX_PERSONAGEM hitbox;
	float rotacao;
	float velocidade, velocidadePulo;
	clock_t relogioVelho, relogioNovo, pulo;
	bool pulando, usando;
};
typedef struct PERSONAGEM PERSONAGEM;

void PERSONAGEM_CONFIGSTART(PERSONAGEM* personagem)
{
	personagem->equip.capacete = 0;
	personagem->equip.camisa = 0;
	personagem->equip.oculos = 0;
	personagem->equip.sapato = 0;
	personagem->equip.calca = 1;
	personagem->rotacao = 0;
	personagem->modelo.frame = 0;
	personagem->posicao.y = 2;
	personagem->posicao.x = 0;
	personagem->posicao.z = 0;
	personagem->velocidade = 0.1f;
	personagem->modelo.atual = personagem->modelo.idle;
	personagem->pulando = false;
	personagem->usando = false;
	personagem->relogioNovo = 0;
	personagem->relogioVelho = 0;
	//personagem->hitbox.atual = GetModelBoundingBox(personagem->modelo.atual);
	personagem->hitbox.modelo = LoadModel("data/models/hitbox/action.glb");
	personagem->hitbox.useBase = GetModelBoundingBox(personagem->hitbox.modelo);
	personagem->hitbox.atual = personagem->hitbox.useBase;
	UnloadModel(personagem->hitbox.modelo);
    personagem->hitbox.modelo = LoadModel("data/models/hitbox/pes.glb");
    personagem->hitbox.pesBase = GetModelBoundingBox(personagem->hitbox.modelo);
    UnloadModel(personagem->hitbox.modelo);
    personagem->hitbox.modelo = LoadModel("data/models/hitbox/frente.glb");
    personagem->hitbox.frenteBase = GetModelBoundingBox(personagem->hitbox.modelo);
    UnloadModel(personagem->hitbox.modelo);
}

bool PERSONAGEM_CHECARCHAO(PERSONAGEM personagem, MAPA mapa)
{
    if(CheckCollisionBoxes(personagem.hitbox.pesAtual, mapa.hitboxH[0]))
    {
        return true;
    }
    else if(CheckCollisionBoxes(personagem.hitbox.pesAtual, mapa.hitboxV[0]))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PERSONAGEM_CHECARPAREDE(PERSONAGEM personagem, MAPA mapa)
{

    if(CheckCollisionBoxes(personagem.hitbox.frenteAtual, mapa.hitboxV[0]))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PERSONAGEM_USEANIM(PERSONAGEM* personagem, ITEM item)
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
            personagem->equip.calcaAtual = item.calca[personagem->equip.calca].use[0];
//
		}
		break;
		case 1:
		{
			personagem->modelo.atual = personagem->modelo.use_default[1];
            personagem->equip.calcaAtual = item.calca[personagem->equip.calca].use[1];

		}
		break;
		case 2:
		{
			personagem->modelo.atual = personagem->modelo.use_default[2];
            personagem->equip.calcaAtual = item.calca[personagem->equip.calca].use[2];
			if(personagem->usando == false)
			{
				personagem->modelo.atual = personagem->modelo.idle;
                personagem->equip.calcaAtual = item.calca[personagem->equip.calca].idle;
				msg = " ";
			}

		}
		break;
	}

}

void PERSONAGEM_USE(PERSONAGEM* personagem)
{
	personagem->usando = true;
	personagem->modelo.frame = 0;
	personagem->relogioNovo = 0;
	personagem->relogioVelho = 0;
	//PERSONAGEM_USEANIM(*&personagem);
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
			personagem->equip.calcaAtual = item.calca[personagem->equip.calca].run[0];
		}
		break;
		case 1:
		{
			personagem->modelo.atual = personagem->modelo.run[1];
			personagem->equip.calcaAtual = item.calca[personagem->equip.calca].run[1];
		}
		break;
		case 2:
		{
			personagem->modelo.atual = personagem->modelo.run[2];
			personagem->equip.calcaAtual = item.calca[personagem->equip.calca].run[2];

		}
		break;
		case 3:
		{
			personagem->modelo.atual = personagem->modelo.run[3];
			personagem->equip.calcaAtual = item.calca[personagem->equip.calca].run[3];

		}
		break;
		case 4:
		{
			personagem->modelo.atual = personagem->modelo.run[4];
			personagem->equip.calcaAtual = item.calca[personagem->equip.calca].run[0];
		}
		break;
	}
}
void PERSONAGEM_MOVEFRENTE(PERSONAGEM *personagem, MAPA mapa)
{
	if(PERSONAGEM_CHECARPAREDE( *personagem, mapa) == false)
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

void PERSONAGEM_MOVETRAS(PERSONAGEM *personagem)
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

void PERSONAGEM_HITBOXUPDATE(PERSONAGEM* personagem)
{
	BoundingBox *PersonagemReservaHitboxLocal = malloc(sizeof(BoundingBox));
		PersonagemReservaHitboxLocal[0] = personagem->hitbox.atual;

		if(personagem->rotacao == 90||personagem->rotacao == 135||personagem->rotacao == 270||personagem->rotacao == 315)
		{
			personagem->hitbox.atual.min.x = PersonagemReservaHitboxLocal[0].min.z;
			personagem->hitbox.atual.max.x = PersonagemReservaHitboxLocal[0].max.z;
			personagem->hitbox.atual.min.z = PersonagemReservaHitboxLocal[0].min.x;
			personagem->hitbox.atual.max.z = PersonagemReservaHitboxLocal[0].max.x;
		}

		free(PersonagemReservaHitboxLocal);

		personagem->hitbox.atual.min.x = personagem->hitbox.useBase.min.x + personagem->posicao.x;
		personagem->hitbox.atual.max.x = personagem->hitbox.useBase.max.x + personagem->posicao.x;
		personagem->hitbox.atual.min.y = personagem->hitbox.useBase.min.y + personagem->posicao.y;
		personagem->hitbox.atual.max.y = personagem->hitbox.useBase.max.y + personagem->posicao.y;
		personagem->hitbox.atual.min.z = personagem->hitbox.useBase.min.z + personagem->posicao.z;
		personagem->hitbox.atual.max.z = personagem->hitbox.useBase.max.z + personagem->posicao.z;

		personagem->hitbox.use.min.y = personagem->hitbox.useBase.min.y + personagem->posicao.y;
		personagem->hitbox.use.max.y = personagem->hitbox.useBase.max.y + personagem->posicao.y;
        
        personagem->hitbox.pesAtual.min.x = personagem->hitbox.pesBase.min.x + personagem->posicao.x;
		personagem->hitbox.pesAtual.max.x = personagem->hitbox.pesBase.max.x + personagem->posicao.x;
		personagem->hitbox.pesAtual.min.y = personagem->hitbox.pesBase.min.y + personagem->posicao.y;
		personagem->hitbox.pesAtual.max.y = personagem->hitbox.pesBase.max.y + personagem->posicao.y;
		personagem->hitbox.pesAtual.min.z = personagem->hitbox.pesBase.min.z + personagem->posicao.z;
		personagem->hitbox.pesAtual.max.z = personagem->hitbox.pesBase.max.z + personagem->posicao.z;
        
        personagem->hitbox.frenteAtual.min.x = personagem->hitbox.frenteBase.min.x + personagem->posicao.x;
		personagem->hitbox.frenteAtual.max.x = personagem->hitbox.frenteBase.max.x + personagem->posicao.x;
		personagem->hitbox.frenteAtual.min.y = personagem->hitbox.frenteBase.min.y + personagem->posicao.y;
		personagem->hitbox.frenteAtual.max.y = personagem->hitbox.frenteBase.max.y + personagem->posicao.y;
		personagem->hitbox.frenteAtual.min.z = personagem->hitbox.frenteBase.min.z + personagem->posicao.z;
		personagem->hitbox.frenteAtual.max.z = personagem->hitbox.frenteBase.max.z + personagem->posicao.z;
        
		if(personagem->rotacao == 0 )
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useBase.min.x + personagem->posicao.x;
			personagem->hitbox.use.max.x = personagem->hitbox.useBase.max.x + personagem->posicao.x;
			personagem->hitbox.use.min.z = personagem->hitbox.useBase.min.z + personagem->posicao.z+diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
			personagem->hitbox.use.max.z = personagem->hitbox.useBase.max.z + personagem->posicao.z+diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
		}
		else if(personagem->rotacao ==45)
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useBase.min.x + personagem->posicao.x +diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.max.x = personagem->hitbox.useBase.max.x + personagem->posicao.x +diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.min.z = personagem->hitbox.useBase.min.z + personagem->posicao.z +diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
			personagem->hitbox.use.max.z = personagem->hitbox.useBase.max.z + personagem->posicao.z +diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
		}
		else if(personagem->rotacao == 90)
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useBase.min.x + personagem->posicao.x +diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.max.x = personagem->hitbox.useBase.max.x + personagem->posicao.x +diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.min.z = personagem->hitbox.useBase.min.z + personagem->posicao.z;
			personagem->hitbox.use.max.z = personagem->hitbox.useBase.max.z + personagem->posicao.z;
		}
		else if(personagem->rotacao == 135)
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useBase.min.x + personagem->posicao.x +diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.max.x = personagem->hitbox.useBase.max.x + personagem->posicao.x +diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.min.z = personagem->hitbox.useBase.min.z + personagem->posicao.z -diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
			personagem->hitbox.use.max.z = personagem->hitbox.useBase.max.z + personagem->posicao.z -diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
		}
		else if(personagem->rotacao == 180)
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useBase.min.x + personagem->posicao.x;
			personagem->hitbox.use.max.x = personagem->hitbox.useBase.max.x + personagem->posicao.x;
			personagem->hitbox.use.min.z = personagem->hitbox.useBase.min.z + personagem->posicao.z -diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
			personagem->hitbox.use.max.z = personagem->hitbox.useBase.max.z + personagem->posicao.z -diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
		}
		else if(personagem->rotacao == 225)
		{
			personagem->hitbox.use.min.z = personagem->hitbox.useBase.min.z + personagem->posicao.z -diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
			personagem->hitbox.use.max.z = personagem->hitbox.useBase.max.z + personagem->posicao.z -diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
			personagem->hitbox.use.min.x = personagem->hitbox.useBase.min.x + personagem->posicao.x -diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.max.x = personagem->hitbox.useBase.max.x + personagem->posicao.x -diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
		}
		else if(personagem->rotacao == 270)
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useBase.min.x + personagem->posicao.x -diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.max.x = personagem->hitbox.useBase.max.x + personagem->posicao.x -diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.min.z = personagem->hitbox.useBase.min.z + personagem->posicao.z;
			personagem->hitbox.use.max.z = personagem->hitbox.useBase.max.z + personagem->posicao.z;
		}
		else if(personagem->rotacao == 315)
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useBase.min.x + personagem->posicao.x -diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.max.x = personagem->hitbox.useBase.max.x + personagem->posicao.x -diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.min.z = personagem->hitbox.useBase.min.z + personagem->posicao.z+diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
			personagem->hitbox.use.max.z = personagem->hitbox.useBase.max.z + personagem->posicao.z+diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
		}


}
