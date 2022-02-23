
struct HITBOX_PERSONAGEM
{
	// 0
	BoundingBox use,useR,atual;
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
	personagem->posicao.y = 0;
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
	personagem->hitbox.useR = GetModelBoundingBox(personagem->hitbox.modelo);
	personagem->hitbox.atual = personagem->hitbox.useR;
	UnloadModel(personagem->hitbox.modelo);
}

void PERSONAGEM_USEANIM(PERSONAGEM* personagem)
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
//
		}
		break;
		case 1:
		{
			personagem->modelo.atual = personagem->modelo.use_default[1];

		}
		break;
		case 2:
		{
			personagem->modelo.atual = personagem->modelo.use_default[2];
			if(personagem->usando == false)
			{
				personagem->modelo.atual = personagem->modelo.idle;
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
void PERSONAGEM_MOVEFRENTE(PERSONAGEM *personagem)
{
	//0 ou 360
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

		personagem->hitbox.atual.min.x = personagem->hitbox.useR.min.x + personagem->posicao.x;
		personagem->hitbox.atual.max.x = personagem->hitbox.useR.max.x + personagem->posicao.x;
		personagem->hitbox.atual.min.y = personagem->hitbox.useR.min.y + personagem->posicao.y;
		personagem->hitbox.atual.max.y = personagem->hitbox.useR.max.y + personagem->posicao.y;
		personagem->hitbox.atual.min.z = personagem->hitbox.useR.min.z + personagem->posicao.z;
		personagem->hitbox.atual.max.z = personagem->hitbox.useR.max.z + personagem->posicao.z;

		personagem->hitbox.use.min.y = personagem->hitbox.useR.min.y + personagem->posicao.y;
		personagem->hitbox.use.max.y = personagem->hitbox.useR.max.y + personagem->posicao.y;

		if(personagem->rotacao == 0 )
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useR.min.x + personagem->posicao.x;
			personagem->hitbox.use.max.x = personagem->hitbox.useR.max.x + personagem->posicao.x;
			personagem->hitbox.use.min.z = personagem->hitbox.useR.min.z + personagem->posicao.z+diferencaF(personagem->hitbox.useR.min.z,personagem->hitbox.useR.max.z);
			personagem->hitbox.use.max.z = personagem->hitbox.useR.max.z + personagem->posicao.z+diferencaF(personagem->hitbox.useR.min.z,personagem->hitbox.useR.max.z);
		}
		else if(personagem->rotacao ==45)
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useR.min.x + personagem->posicao.x +diferencaF(personagem->hitbox.useR.min.x,personagem->hitbox.useR.max.x);
			personagem->hitbox.use.max.x = personagem->hitbox.useR.max.x + personagem->posicao.x +diferencaF(personagem->hitbox.useR.min.x,personagem->hitbox.useR.max.x);
			personagem->hitbox.use.min.z = personagem->hitbox.useR.min.z + personagem->posicao.z +diferencaF(personagem->hitbox.useR.min.z,personagem->hitbox.useR.max.z);
			personagem->hitbox.use.max.z = personagem->hitbox.useR.max.z + personagem->posicao.z +diferencaF(personagem->hitbox.useR.min.z,personagem->hitbox.useR.max.z);
		}
		else if(personagem->rotacao == 90)
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useR.min.x + personagem->posicao.x +diferencaF(personagem->hitbox.useR.min.x,personagem->hitbox.useR.max.x);
			personagem->hitbox.use.max.x = personagem->hitbox.useR.max.x + personagem->posicao.x +diferencaF(personagem->hitbox.useR.min.x,personagem->hitbox.useR.max.x);
			personagem->hitbox.use.min.z = personagem->hitbox.useR.min.z + personagem->posicao.z;
			personagem->hitbox.use.max.z = personagem->hitbox.useR.max.z + personagem->posicao.z;
		}
		else if(personagem->rotacao == 135)
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useR.min.x + personagem->posicao.x +diferencaF(personagem->hitbox.useR.min.x,personagem->hitbox.useR.max.x);
			personagem->hitbox.use.max.x = personagem->hitbox.useR.max.x + personagem->posicao.x +diferencaF(personagem->hitbox.useR.min.x,personagem->hitbox.useR.max.x);
			personagem->hitbox.use.min.z = personagem->hitbox.useR.min.z + personagem->posicao.z -diferencaF(personagem->hitbox.useR.min.z,personagem->hitbox.useR.max.z);
			personagem->hitbox.use.max.z = personagem->hitbox.useR.max.z + personagem->posicao.z -diferencaF(personagem->hitbox.useR.min.z,personagem->hitbox.useR.max.z);
		}
		else if(personagem->rotacao == 180)
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useR.min.x + personagem->posicao.x;
			personagem->hitbox.use.max.x = personagem->hitbox.useR.max.x + personagem->posicao.x;
			personagem->hitbox.use.min.z = personagem->hitbox.useR.min.z + personagem->posicao.z -diferencaF(personagem->hitbox.useR.min.z,personagem->hitbox.useR.max.z);
			personagem->hitbox.use.max.z = personagem->hitbox.useR.max.z + personagem->posicao.z -diferencaF(personagem->hitbox.useR.min.z,personagem->hitbox.useR.max.z);
		}
		else if(personagem->rotacao == 225)
		{
			personagem->hitbox.use.min.z = personagem->hitbox.useR.min.z + personagem->posicao.z -diferencaF(personagem->hitbox.useR.min.z,personagem->hitbox.useR.max.z);
			personagem->hitbox.use.max.z = personagem->hitbox.useR.max.z + personagem->posicao.z -diferencaF(personagem->hitbox.useR.min.z,personagem->hitbox.useR.max.z);
			personagem->hitbox.use.min.x = personagem->hitbox.useR.min.x + personagem->posicao.x -diferencaF(personagem->hitbox.useR.min.x,personagem->hitbox.useR.max.x);
			personagem->hitbox.use.max.x = personagem->hitbox.useR.max.x + personagem->posicao.x -diferencaF(personagem->hitbox.useR.min.x,personagem->hitbox.useR.max.x);
		}
		else if(personagem->rotacao == 270)
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useR.min.x + personagem->posicao.x -diferencaF(personagem->hitbox.useR.min.x,personagem->hitbox.useR.max.x);
			personagem->hitbox.use.max.x = personagem->hitbox.useR.max.x + personagem->posicao.x -diferencaF(personagem->hitbox.useR.min.x,personagem->hitbox.useR.max.x);
			personagem->hitbox.use.min.z = personagem->hitbox.useR.min.z + personagem->posicao.z;
			personagem->hitbox.use.max.z = personagem->hitbox.useR.max.z + personagem->posicao.z;
		}
		else if(personagem->rotacao == 315)
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useR.min.x + personagem->posicao.x -diferencaF(personagem->hitbox.useR.min.x,personagem->hitbox.useR.max.x);
			personagem->hitbox.use.max.x = personagem->hitbox.useR.max.x + personagem->posicao.x -diferencaF(personagem->hitbox.useR.min.x,personagem->hitbox.useR.max.x);
			personagem->hitbox.use.min.z = personagem->hitbox.useR.min.z + personagem->posicao.z+diferencaF(personagem->hitbox.useR.min.z,personagem->hitbox.useR.max.z);
			personagem->hitbox.use.max.z = personagem->hitbox.useR.max.z + personagem->posicao.z+diferencaF(personagem->hitbox.useR.min.z,personagem->hitbox.useR.max.z);
		}


}
