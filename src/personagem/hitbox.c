void PERSONAGEM_HITBOXUPDATE(PERSONAGEM* personagem)
{
// 	    BoundingBox *PersonagemReservaHitboxLocal = malloc(sizeof(BoundingBox));
// 		PersonagemReservaHitboxLocal[0] = personagem->hitbox.atual;
// 
// 		if(personagem->rotacao == 90||personagem->rotacao == 135||personagem->rotacao == 270||personagem->rotacao == 315)
// 		{
// 			personagem->hitbox.atual.min.x = PersonagemReservaHitboxLocal[0].min.z;
// 			personagem->hitbox.atual.max.x = PersonagemReservaHitboxLocal[0].max.z;
// 			personagem->hitbox.atual.min.z = PersonagemReservaHitboxLocal[0].min.x;
// 			personagem->hitbox.atual.max.z = PersonagemReservaHitboxLocal[0].max.x;
// 		}
// 
// 		free(PersonagemReservaHitboxLocal);
        
		personagem->hitbox.atual.min.x = personagem->hitbox.useBase.min.x + personagem->posicao.x;
		personagem->hitbox.atual.max.x = personagem->hitbox.useBase.max.x + personagem->posicao.x;
		personagem->hitbox.atual.min.z = personagem->hitbox.useBase.min.z + personagem->posicao.z;
		personagem->hitbox.atual.max.z = personagem->hitbox.useBase.max.z + personagem->posicao.z;
        personagem->hitbox.atual.min.y = personagem->hitbox.useBase.min.y + personagem->posicao.y;
		personagem->hitbox.atual.max.y = personagem->hitbox.useBase.max.y + personagem->posicao.y;
        
        personagem->hitbox.frenteAtual.min.y = personagem->hitbox.frenteBase.min.y + personagem->posicao.y;
		personagem->hitbox.frenteAtual.max.y = personagem->hitbox.frenteBase.max.y + personagem->posicao.y;
        personagem->hitbox.trasAtual.min.y = personagem->hitbox.trasBase.min.y + personagem->posicao.y;
		personagem->hitbox.trasAtual.max.y = personagem->hitbox.trasBase.max.y + personagem->posicao.y;
        personagem->hitbox.pesAtual.min.y = personagem->hitbox.pesBase.min.y + personagem->posicao.y;
		personagem->hitbox.pesAtual.max.y = personagem->hitbox.pesBase.max.y + personagem->posicao.y;
        personagem->hitbox.use.min.y = personagem->hitbox.useBase.min.y + personagem->posicao.y;
		personagem->hitbox.use.max.y = personagem->hitbox.useBase.max.y + personagem->posicao.y;
        
		if(personagem->rotacao == 0 )
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useBase.min.x + personagem->posicao.x;
			personagem->hitbox.use.max.x = personagem->hitbox.useBase.max.x + personagem->posicao.x;
			personagem->hitbox.use.min.z = personagem->hitbox.useBase.min.z + personagem->posicao.z+ET_diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
			personagem->hitbox.use.max.z = personagem->hitbox.useBase.max.z + personagem->posicao.z+ET_diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
            
            personagem->hitbox.trasAtual.min.x = personagem->hitbox.trasBase.min.x + personagem->posicao.x;
            personagem->hitbox.trasAtual.max.x = personagem->hitbox.trasBase.max.x + personagem->posicao.x;
            personagem->hitbox.trasAtual.min.z = personagem->hitbox.trasBase.min.z + personagem->posicao.z;
            personagem->hitbox.trasAtual.max.z = personagem->hitbox.trasBase.max.z + personagem->posicao.z;
            
            personagem->hitbox.frenteAtual.min.x = personagem->hitbox.frenteBase.min.x + personagem->posicao.x;
            personagem->hitbox.frenteAtual.max.x = personagem->hitbox.frenteBase.max.x + personagem->posicao.x;
            personagem->hitbox.frenteAtual.min.z = personagem->hitbox.frenteBase.min.z + personagem->posicao.z;
            personagem->hitbox.frenteAtual.max.z = personagem->hitbox.frenteBase.max.z + personagem->posicao.z;
            
            personagem->hitbox.pesAtual.min.x = personagem->hitbox.pesBase.min.x + personagem->posicao.x;
            personagem->hitbox.pesAtual.max.x = personagem->hitbox.pesBase.max.x + personagem->posicao.x;
            personagem->hitbox.pesAtual.min.z = personagem->hitbox.pesBase.min.z + personagem->posicao.z;
            personagem->hitbox.pesAtual.max.z = personagem->hitbox.pesBase.max.z + personagem->posicao.z;
		}
		else if(personagem->rotacao ==45)
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useBase.min.x + personagem->posicao.x +ET_diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.max.x = personagem->hitbox.useBase.max.x + personagem->posicao.x +ET_diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.min.z = personagem->hitbox.useBase.min.z + personagem->posicao.z +ET_diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
			personagem->hitbox.use.max.z = personagem->hitbox.useBase.max.z + personagem->posicao.z +ET_diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
            
            personagem->hitbox.trasAtual.min.x = personagem->hitbox.tras45.min.x + personagem->posicao.x;
            personagem->hitbox.trasAtual.max.x = personagem->hitbox.tras45.max.x + personagem->posicao.x;
            personagem->hitbox.trasAtual.min.z = personagem->hitbox.tras45.min.z + personagem->posicao.z;
            personagem->hitbox.trasAtual.max.z = personagem->hitbox.tras45.max.z + personagem->posicao.z;
            
            personagem->hitbox.frenteAtual.min.x = personagem->hitbox.frente45.min.x + personagem->posicao.x;
            personagem->hitbox.frenteAtual.max.x = personagem->hitbox.frente45.max.x + personagem->posicao.x;
            personagem->hitbox.frenteAtual.min.z = personagem->hitbox.frente45.min.z + personagem->posicao.z;
            personagem->hitbox.frenteAtual.max.z = personagem->hitbox.frente45.max.z + personagem->posicao.z;
            
            personagem->hitbox.pesAtual.min.x = personagem->hitbox.pesBase.min.x + personagem->posicao.x;
            personagem->hitbox.pesAtual.max.x = personagem->hitbox.pesBase.max.x + personagem->posicao.x;
            personagem->hitbox.pesAtual.min.z = personagem->hitbox.pesBase.min.z + personagem->posicao.z;
            personagem->hitbox.pesAtual.max.z = personagem->hitbox.pesBase.max.z + personagem->posicao.z;
		}
		else if(personagem->rotacao == 90)
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useBase.min.x + personagem->posicao.x +ET_diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.max.x = personagem->hitbox.useBase.max.x + personagem->posicao.x +ET_diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.min.z = personagem->hitbox.useBase.min.z + personagem->posicao.z;
			personagem->hitbox.use.max.z = personagem->hitbox.useBase.max.z + personagem->posicao.z;
            
            personagem->hitbox.trasAtual.min.x = personagem->hitbox.tras90.min.x + personagem->posicao.x;
            personagem->hitbox.trasAtual.max.x = personagem->hitbox.tras90.max.x + personagem->posicao.x;
            personagem->hitbox.trasAtual.min.z = personagem->hitbox.tras90.min.z + personagem->posicao.z;
            personagem->hitbox.trasAtual.max.z = personagem->hitbox.tras90.max.z + personagem->posicao.z;
            
            personagem->hitbox.frenteAtual.min.x = personagem->hitbox.frente90.min.x + personagem->posicao.x;
            personagem->hitbox.frenteAtual.max.x = personagem->hitbox.frente90.max.x + personagem->posicao.x;
            personagem->hitbox.frenteAtual.min.z = personagem->hitbox.frente90.min.z + personagem->posicao.z;
            personagem->hitbox.frenteAtual.max.z = personagem->hitbox.frente90.max.z + personagem->posicao.z;
            
            personagem->hitbox.pesAtual.min.x = personagem->hitbox.pes90.min.x + personagem->posicao.x;
            personagem->hitbox.pesAtual.max.x = personagem->hitbox.pes90.max.x + personagem->posicao.x;
            personagem->hitbox.pesAtual.min.z = personagem->hitbox.pes90.min.z + personagem->posicao.z;
            personagem->hitbox.pesAtual.max.z = personagem->hitbox.pes90.max.z + personagem->posicao.z;
		}
		else if(personagem->rotacao == 135)
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useBase.min.x + personagem->posicao.x +ET_diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.max.x = personagem->hitbox.useBase.max.x + personagem->posicao.x +ET_diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.min.z = personagem->hitbox.useBase.min.z + personagem->posicao.z -ET_diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
			personagem->hitbox.use.max.z = personagem->hitbox.useBase.max.z + personagem->posicao.z -ET_diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
            personagem->hitbox.trasAtual.min.x = personagem->hitbox.tras135.min.x + personagem->posicao.x;
            personagem->hitbox.trasAtual.max.x = personagem->hitbox.tras135.max.x + personagem->posicao.x;
            personagem->hitbox.trasAtual.min.z = personagem->hitbox.tras135.min.z + personagem->posicao.z;
            personagem->hitbox.trasAtual.max.z = personagem->hitbox.tras135.max.z + personagem->posicao.z;
            personagem->hitbox.frenteAtual.min.x = personagem->hitbox.frente135.min.x + personagem->posicao.x;
            personagem->hitbox.frenteAtual.max.x = personagem->hitbox.frente135.max.x + personagem->posicao.x;
            personagem->hitbox.frenteAtual.min.z = personagem->hitbox.frente135.min.z + personagem->posicao.z;
            personagem->hitbox.frenteAtual.max.z = personagem->hitbox.frente135.max.z + personagem->posicao.z;
            personagem->hitbox.pesAtual.min.x = personagem->hitbox.pes90.min.x + personagem->posicao.x;
            personagem->hitbox.pesAtual.max.x = personagem->hitbox.pes90.max.x + personagem->posicao.x;
            personagem->hitbox.pesAtual.min.z = personagem->hitbox.pes90.min.z + personagem->posicao.z;
            personagem->hitbox.pesAtual.max.z = personagem->hitbox.pes90.max.z + personagem->posicao.z;
		}
		else if(personagem->rotacao == 180)
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useBase.min.x + personagem->posicao.x;
			personagem->hitbox.use.max.x = personagem->hitbox.useBase.max.x + personagem->posicao.x;
			personagem->hitbox.use.min.z = personagem->hitbox.useBase.min.z + personagem->posicao.z -ET_diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
			personagem->hitbox.use.max.z = personagem->hitbox.useBase.max.z + personagem->posicao.z -ET_diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
            personagem->hitbox.trasAtual.min.x = personagem->hitbox.tras180.min.x + personagem->posicao.x;
            personagem->hitbox.trasAtual.max.x = personagem->hitbox.tras180.max.x + personagem->posicao.x;
            personagem->hitbox.trasAtual.min.z = personagem->hitbox.tras180.min.z + personagem->posicao.z;
            personagem->hitbox.trasAtual.max.z = personagem->hitbox.tras180.max.z + personagem->posicao.z;
            personagem->hitbox.frenteAtual.min.x = personagem->hitbox.frente180.min.x + personagem->posicao.x;
            personagem->hitbox.frenteAtual.max.x = personagem->hitbox.frente180.max.x + personagem->posicao.x;
            personagem->hitbox.frenteAtual.min.z = personagem->hitbox.frente180.min.z + personagem->posicao.z;
            personagem->hitbox.frenteAtual.max.z = personagem->hitbox.frente180.max.z + personagem->posicao.z;
            personagem->hitbox.pesAtual.min.x = personagem->hitbox.pes180.min.x + personagem->posicao.x;
            personagem->hitbox.pesAtual.max.x = personagem->hitbox.pes180.max.x + personagem->posicao.x;
            personagem->hitbox.pesAtual.min.z = personagem->hitbox.pes180.min.z + personagem->posicao.z;
            personagem->hitbox.pesAtual.max.z = personagem->hitbox.pes180.max.z + personagem->posicao.z;
		}
		else if(personagem->rotacao == 225)
		{
			personagem->hitbox.use.min.z = personagem->hitbox.useBase.min.z + personagem->posicao.z -ET_diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
			personagem->hitbox.use.max.z = personagem->hitbox.useBase.max.z + personagem->posicao.z -ET_diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
			personagem->hitbox.use.min.x = personagem->hitbox.useBase.min.x + personagem->posicao.x -ET_diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.max.x = personagem->hitbox.useBase.max.x + personagem->posicao.x -ET_diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
            personagem->hitbox.trasAtual.min.x = personagem->hitbox.tras225.min.x + personagem->posicao.x;
            personagem->hitbox.trasAtual.max.x = personagem->hitbox.tras225.max.x + personagem->posicao.x;
            personagem->hitbox.trasAtual.min.z = personagem->hitbox.tras225.min.z + personagem->posicao.z;
            personagem->hitbox.trasAtual.max.z = personagem->hitbox.tras225.max.z + personagem->posicao.z;
            personagem->hitbox.frenteAtual.min.x = personagem->hitbox.frente225.min.x + personagem->posicao.x;
            personagem->hitbox.frenteAtual.max.x = personagem->hitbox.frente225.max.x + personagem->posicao.x;
            personagem->hitbox.frenteAtual.min.z = personagem->hitbox.frente225.min.z + personagem->posicao.z;
            personagem->hitbox.frenteAtual.max.z = personagem->hitbox.frente225.max.z + personagem->posicao.z;
            personagem->hitbox.pesAtual.min.x = personagem->hitbox.pes180.min.x + personagem->posicao.x;
            personagem->hitbox.pesAtual.max.x = personagem->hitbox.pes180.max.x + personagem->posicao.x;
            personagem->hitbox.pesAtual.min.z = personagem->hitbox.pes180.min.z + personagem->posicao.z;
            personagem->hitbox.pesAtual.max.z = personagem->hitbox.pes180.max.z + personagem->posicao.z;
		}
		else if(personagem->rotacao == 270)
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useBase.min.x + personagem->posicao.x -ET_diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.max.x = personagem->hitbox.useBase.max.x + personagem->posicao.x -ET_diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.min.z = personagem->hitbox.useBase.min.z + personagem->posicao.z;
			personagem->hitbox.use.max.z = personagem->hitbox.useBase.max.z + personagem->posicao.z;
            personagem->hitbox.trasAtual.min.x = personagem->hitbox.tras270.min.x + personagem->posicao.x;
            personagem->hitbox.trasAtual.max.x = personagem->hitbox.tras270.max.x + personagem->posicao.x;
            personagem->hitbox.trasAtual.min.z = personagem->hitbox.tras270.min.z + personagem->posicao.z;
            personagem->hitbox.trasAtual.max.z = personagem->hitbox.tras270.max.z + personagem->posicao.z;
            personagem->hitbox.frenteAtual.min.x = personagem->hitbox.frente270.min.x + personagem->posicao.x;
            personagem->hitbox.frenteAtual.max.x = personagem->hitbox.frente270.max.x + personagem->posicao.x;
            personagem->hitbox.frenteAtual.min.z = personagem->hitbox.frente270.min.z + personagem->posicao.z;
            personagem->hitbox.frenteAtual.max.z = personagem->hitbox.frente270.max.z + personagem->posicao.z;
            personagem->hitbox.pesAtual.min.x = personagem->hitbox.pes270.min.x + personagem->posicao.x;
            personagem->hitbox.pesAtual.max.x = personagem->hitbox.pes270.max.x + personagem->posicao.x;
            personagem->hitbox.pesAtual.min.z = personagem->hitbox.pes270.min.z + personagem->posicao.z;
            personagem->hitbox.pesAtual.max.z = personagem->hitbox.pes270.max.z + personagem->posicao.z;
		}
		else if(personagem->rotacao == 315)
		{
			personagem->hitbox.use.min.x = personagem->hitbox.useBase.min.x + personagem->posicao.x -ET_diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.max.x = personagem->hitbox.useBase.max.x + personagem->posicao.x -ET_diferencaF(personagem->hitbox.useBase.min.x,personagem->hitbox.useBase.max.x);
			personagem->hitbox.use.min.z = personagem->hitbox.useBase.min.z + personagem->posicao.z+ET_diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
			personagem->hitbox.use.max.z = personagem->hitbox.useBase.max.z + personagem->posicao.z+ET_diferencaF(personagem->hitbox.useBase.min.z,personagem->hitbox.useBase.max.z);
            personagem->hitbox.trasAtual.min.x = personagem->hitbox.tras315.min.x + personagem->posicao.x;
            personagem->hitbox.trasAtual.max.x = personagem->hitbox.tras315.max.x + personagem->posicao.x;
            personagem->hitbox.trasAtual.min.z = personagem->hitbox.tras315.min.z + personagem->posicao.z;
            personagem->hitbox.trasAtual.max.z = personagem->hitbox.tras315.max.z + personagem->posicao.z;
            personagem->hitbox.frenteAtual.min.x = personagem->hitbox.frente315.min.x + personagem->posicao.x;
            personagem->hitbox.frenteAtual.max.x = personagem->hitbox.frente315.max.x + personagem->posicao.x;
            personagem->hitbox.frenteAtual.min.z = personagem->hitbox.frente315.min.z + personagem->posicao.z;
            personagem->hitbox.frenteAtual.max.z = personagem->hitbox.frente315.max.z + personagem->posicao.z;
            personagem->hitbox.pesAtual.min.x = personagem->hitbox.pes270.min.x + personagem->posicao.x;
            personagem->hitbox.pesAtual.max.x = personagem->hitbox.pes270.max.x + personagem->posicao.x;
            personagem->hitbox.pesAtual.min.z = personagem->hitbox.pes270.min.z + personagem->posicao.z;
            personagem->hitbox.pesAtual.max.z = personagem->hitbox.pes270.max.z + personagem->posicao.z;
		}


}
