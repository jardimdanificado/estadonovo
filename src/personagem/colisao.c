 
bool PERSONAGEM_CHECARCHAO(PERSONAGEM personagem, MAPA mapa)
{
    if(CheckCollisionBoxes(personagem.hitbox.pesAtual, mapa.hitboxHorizontal[0]))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PERSONAGEM_CHECARPAREDE(PERSONAGEM personagem, MAPA mapa, char opcao)
{
    if(opcao == '+')
    {
        for(int i = 0; i <10; i++)
        {
            if(CheckCollisionBoxes(personagem.hitbox.frenteAtual, mapa.hitboxVertical[i]))
            {
                return true;
            }
            else if(i<5&&CheckCollisionBoxes(personagem.hitbox.frenteAtual, mapa.porta[0].hitbox))
            {
                return true;
            }
            else if(i<5&&CheckCollisionBoxes(personagem.hitbox.frenteAtual, mapa.porta[1].hitbox))
            {
                return true;
            }
                
        }
        
        return false;
    }
    else if(opcao == '-')
    {
        for(int i = 0; i <10; i++)
        {
            if(CheckCollisionBoxes(personagem.hitbox.trasAtual, mapa.hitboxVertical[i]))
            {
                return true;
            }
            else if(i<5&&CheckCollisionBoxes(personagem.hitbox.frenteAtual, mapa.porta[0].hitbox))
            {
                return true;
            }
            else if(i<5&&CheckCollisionBoxes(personagem.hitbox.frenteAtual, mapa.porta[1].hitbox))
            {
                return true;
            }
                
        }
        
        return false;

    }
}
