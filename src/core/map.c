#include "../map/lvl0.c"//lvl0

void MAPA_START(MAPA* mapa)
{
    LEVEL0(*&mapa);
}


void PORTA_ANIM(MAPA* mapa, int qual)
{
    if(mapa->porta[qual].abrindo)
    {
        
        if(mapa->porta[qual].relogioNovo > mapa->porta[qual].relogioVelho+10000)
        {
            mapa->porta[qual].relogioVelho = mapa->porta[qual].relogioNovo;
    // 		printf("aoba");

        }
        mapa->porta[qual].relogioNovo = clock();
        
        if(mapa->porta[qual].relogioNovo > mapa->porta[qual].relogioVelho+10000&&mapa->porta[qual].frame < 3)
        {
            mapa->porta[qual].frame++;
        }
        else if(mapa->porta[qual].frame == 3&&mapa->porta[qual].relogioNovo > mapa->porta[qual].relogioVelho+10000)
        {

            mapa->porta[qual].abrindo = false;
            mapa->porta[qual].aberta = true;
            mapa->porta[qual].hitbox = GetModelBoundingBox(mapa->porta[qual].modelo[mapa->porta[qual].frame]);
        }
        
    }
    else if(mapa->porta[qual].fechando)
    {
        
        if(mapa->porta[qual].relogioNovo > mapa->porta[qual].relogioVelho+10000)
        {
            mapa->porta[qual].relogioVelho = mapa->porta[qual].relogioNovo;
        }
        mapa->porta[qual].relogioNovo = clock();
        
        if(mapa->porta[qual].relogioNovo > mapa->porta[qual].relogioVelho+10000&&mapa->porta[qual].frame > 0)
        {
            mapa->porta[qual].frame--;
        }
        else if(mapa->porta[qual].frame == 0&&mapa->porta[qual].relogioNovo > mapa->porta[qual].relogioVelho+10000)
        {
            mapa->porta[qual].fechando = false;
            mapa->porta[qual].aberta = false;
            mapa->porta[qual].hitbox = GetModelBoundingBox(mapa->porta[qual].modelo[mapa->porta[qual].frame]);
        }
        
    }
} 
