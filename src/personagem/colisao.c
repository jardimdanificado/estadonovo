
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

bool PERSONAGEM_CHECARPAREDE(PERSONAGEM personagem, MAPA mapa, NPC0 humano, char opcao)
{
    if(opcao == '+')
    {
        for(int i = 0; i <10; i++)
        {
            if(CheckCollisionBoxes(personagem.hitbox.frenteAtual, mapa.hitboxVertical[i]))
            {
                return true;
            }
            else if(CheckCollisionBoxes(personagem.hitbox.frenteAtual, mapa.props[i].hitbox))
            {
                return true;
            }
            else if(CheckCollisionBoxes(personagem.hitbox.frenteAtual, mapa.porta.slots[i].hitbox))
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
            else if(CheckCollisionBoxes(personagem.hitbox.frenteAtual, mapa.porta.slots[i].hitbox))
            {
                return true;
            }
                
        }
        
        return false;

    }
}
