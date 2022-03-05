 
bool PERSONAGEM_CHECARCHAO(PERSONAGEM personagem, MAPA mapa)
{
    if(CheckCollisionBoxes(personagem.hitbox.pesAtual, mapa.hitboxH[0]))
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
        if(CheckCollisionBoxes(personagem.hitbox.frenteAtual, mapa.hitboxV[0]))
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }
    else if(opcao == '-')
    {
        if(CheckCollisionBoxes(personagem.hitbox.trasAtual, mapa.hitboxV[0]))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
