bool BALAS_CHECARCHAO(BoundingBox hitbox, MAPA mapa)
{
    if(CheckCollisionBoxes(hitbox, mapa.hitboxHorizontal[0]))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool BALAS_CHECARPAREDE(BoundingBox hitbox, MAPA mapa/*, NPC0 humano*/)
{
    for(int i = 0; i <10; i++)
    {
        if(CheckCollisionBoxes(hitbox, mapa.hitboxVertical[i]))
        {
            return true;
        }
        else if(CheckCollisionBoxes(hitbox, mapa.props[i].hitbox))
        {
            return true;
        }
        else if(CheckCollisionBoxes(hitbox, mapa.porta.slots[i].hitbox))
        {
            return true;
        }
    }
    return false;
}

void MAPA_BALAUPDATE(MAPA* mapa,  int qualArma)
{
    for(int i =0; i<255; i++)
    {
        if(mapa->balas[i].existe == true&&mapa->balas[i].parou == false&&clock() > (mapa->balas[i].relogio)+(CLOCKS_PER_SEC/200))
        {
            if(mapa->balas[i].velocidade > 0.3)
                mapa->balas[i].velocidade -= 0.001;
            
            switch(mapa->balas[i].rotacao)
            {
                case 0:
                {
                    mapa->balas[i].posicao.z += mapa->balas[i].velocidade/1.5f;
                }
                break;
                case 360:
                {
                    mapa->balas[i].posicao.z += mapa->balas[i].velocidade/1.5f;
                }
                break;
                case 45:
                {
                    mapa->balas[i].posicao.z += mapa->balas[i].velocidade/3;
                    mapa->balas[i].posicao.x += mapa->balas[i].velocidade/3;
                }
                break;
                case 90:
                {
                    mapa->balas[i].posicao.x += mapa->balas[i].velocidade/1.5f;
                }
                break;
                case 135:
                {
                    mapa->balas[i].posicao.z -= mapa->balas[i].velocidade/3;
                    mapa->balas[i].posicao.x += mapa->balas[i].velocidade/3;
                }
                break;
                case 180:
                {
                    mapa->balas[i].posicao.z -= mapa->balas[i].velocidade/1.5f;
                }
                break;
                case 225:
                {
                    mapa->balas[i].posicao.z -= mapa->balas[i].velocidade/3;
                    mapa->balas[i].posicao.x -= mapa->balas[i].velocidade/3;
                }
                break;
                case 270:
                {
                    mapa->balas[i].posicao.x -= mapa->balas[i].velocidade/1.5f;
                }
                break;
                case 315:
                {
                    mapa->balas[i].posicao.z += mapa->balas[i].velocidade/3;
                    mapa->balas[i].posicao.x -= mapa->balas[i].velocidade/3;
                }
                break;
            }
        }
        if(mapa->balas[i].existe == true)
        {
            mapa->balas[i].hitbox = GetModelBoundingBox(mapa->balasGLOBAL.modelo);
            mapa->balas[i].hitbox.max.x += mapa->balas[i].posicao.x;
            mapa->balas[i].hitbox.min.x += mapa->balas[i].posicao.x;
            mapa->balas[i].hitbox.max.y += mapa->balas[i].posicao.y;
            mapa->balas[i].hitbox.min.y += mapa->balas[i].posicao.y;
            mapa->balas[i].hitbox.max.z += mapa->balas[i].posicao.z;
            mapa->balas[i].hitbox.min.z += mapa->balas[i].posicao.z;
            if(BALAS_CHECARCHAO(mapa->balas[i].hitbox, *mapa) == true||BALAS_CHECARPAREDE(mapa->balas[i].hitbox, *mapa)== true)
            {
                mapa->balas[i].parou = true;
            }
            else if(clock() > mapa->balas[i].relogioCriado+CLOCKS_PER_SEC)
            {
                mapa->balas[i].existe = false;
            }
        }
    }
}

void MAPA_CRIARBALA(MAPA* mapa, Vector3 posicao, int rotacao, int qualArma)
{
    for(int i =0; i<255; i++)
    {
        if(mapa->balas[i].existe == false)
        {
            switch(rotacao)
            {
                case 0:
                {
                    mapa->balas[i].posicao.x = 0.04375 + posicao.x;
                    mapa->balas[i].posicao.y = 1.8 + posicao.y;
                    mapa->balas[i].posicao.z = 1.16875 + posicao.z;
                }
                break;
                case 360:
                {
                    mapa->balas[i].posicao.x = 0.04375 + posicao.x;
                    mapa->balas[i].posicao.y = 1.8 + posicao.y;
                    mapa->balas[i].posicao.z = -1.16875 + posicao.z;
                }
                break;
                case 45:
                {
                    mapa->balas[i].posicao.x = 0.83750+ posicao.x;
                    mapa->balas[i].posicao.y = 1.80000+ posicao.y;
                    mapa->balas[i].posicao.z = 0.76250+ posicao.z;
                }
                break;
                case 90:
                {
                    mapa->balas[i].posicao.x = 1.16875+ posicao.x;
                    mapa->balas[i].posicao.y = 1.8+ posicao.y;
                    mapa->balas[i].posicao.z = 0.04375+ posicao.z;
                }
                break;
                case 135:
                {
                    mapa->balas[i].posicao.x = 0.83750+ posicao.x;
                    mapa->balas[i].posicao.y = 1.80000+ posicao.y;
                    mapa->balas[i].posicao.z = -0.76250+ posicao.z;
                }
                break;
                case 180:
                {
                    mapa->balas[i].posicao.x = -0.04375+ posicao.x;
                    mapa->balas[i].posicao.y = 1.80625+ posicao.y;
                    mapa->balas[i].posicao.z = -1.16875+ posicao.z;
                }
                break;
                case 225:
                {
                    mapa->balas[i].posicao.x = -0.83750+ posicao.x;
                    mapa->balas[i].posicao.y = 1.80000+ posicao.y;
                    mapa->balas[i].posicao.z = -0.76250+ posicao.z;
                }
                break;
                case 270:
                {
                    mapa->balas[i].posicao.x = -1.16875+ posicao.x;
                    mapa->balas[i].posicao.y = 1.80625+ posicao.y;
                    mapa->balas[i].posicao.z = -0.04375+ posicao.z;
                }
                break;
                case 315:
                {
                    mapa->balas[i].posicao.x = -0.83750+ posicao.x;
                    mapa->balas[i].posicao.y = 1.80000+ posicao.y;
                    mapa->balas[i].posicao.z = 0.76250+ posicao.z;
                }
                break;
            }
            mapa->balas[i].velocidade = 2;
            mapa->balas[i].rotacao = rotacao;
            mapa->balas[i].relogioCriado = clock();
            mapa->balas[i].relogio = clock();
            mapa->balas[i].existe = true;
            mapa->balas[i].parou = false;
            i = 300;
        }
    }
}

void PORTA_CRIAR(MAPA* mapa, Vector3 posicaoLOCAL, bool invertidoLOCAL, bool trancadaLOCAL, bool abertaLOCAL)
{
    for(int i = 0; i <10 ; i++)
    {
        if(mapa->porta.slots[i].existe == false)
        {
            mapa->porta.slots[i].frame = 0;
            mapa->porta.slots[i].existe = true;
            mapa->porta.slots[i].abrindo = false;
            mapa->porta.slots[i].fechando = false;
            mapa->porta.slots[i].aberta = false;
            mapa->porta.slots[i].invertido = invertidoLOCAL;
            mapa->porta.slots[i].posicao = posicaoLOCAL;
            mapa->porta.slots[i].trancada = trancadaLOCAL;
            
            if(abertaLOCAL == false)
            {
                mapa->porta.slots[i].hitbox = GetModelBoundingBox(mapa->porta.base.modelo[0]);
            }
            else if(abertaLOCAL == true)
            {
                if(invertidoLOCAL == false)
                {
                    mapa->porta.slots[i].hitbox = GetModelBoundingBox(mapa->porta.base.modelo[3]);
                }
                else if(invertidoLOCAL == true)
                {
                    mapa->porta.slots[i].hitbox = GetModelBoundingBox(mapa->porta.base.modeloI[2]);
                }
            }
            mapa->porta.slots[i].hitbox.min.x = mapa->porta.slots[i].hitbox.min.x + mapa->porta.slots[i].posicao.x;
            mapa->porta.slots[i].hitbox.max.x = mapa->porta.slots[i].hitbox.max.x + mapa->porta.slots[i].posicao.x;
            mapa->porta.slots[i].hitbox.min.z = mapa->porta.slots[i].hitbox.min.z + mapa->porta.slots[i].posicao.z;
            mapa->porta.slots[i].hitbox.max.z = mapa->porta.slots[i].hitbox.max.z + mapa->porta.slots[i].posicao.z;
            mapa->porta.slots[i].hitbox.min.y = mapa->porta.slots[i].hitbox.min.y + mapa->porta.slots[i].posicao.y;
            mapa->porta.slots[i].hitbox.max.y = mapa->porta.slots[i].hitbox.max.y + mapa->porta.slots[i].posicao.y;
            i = 80;
        }
    }
    
}

#include "./lvl0.c"//lvl0

void MAPA_START(PERSONAGEM personagem, MAPA* mapa, NPC0* humano)
{
    
    mapa->balasGLOBAL.todasBalasUsadas = false;
    for(int i = 0; i<255; i++)
    {
        mapa->balas[i].existe = false;
        mapa->balas[i].parou = false;
    }
    for(int i = 0; i<10; i++)
    {
        mapa->drops[i].ocupado = false;
        mapa->drops[i].posicao = (Vector3){0,0,0};
    }
    LEVEL0(personagem,*&mapa,*&humano);
    for(int i= 0; i<10;i++)
    {
        mapa->item[i].nome = malloc(sizeof(char)*25);
    }
}

void PORTA_HBUPDATE(MAPA* mapa)
{
    for(int i = 0; i<10; i++)
    {
        if(mapa->porta.slots[i].existe)
        {
            if(mapa->porta.slots[i].invertido == false)
            {
                switch (mapa->porta.slots[i].frame)
                {
                    case 0:
                    {
                        mapa->porta.slots[i].hitbox = GetModelBoundingBox(mapa->porta.base.modelo[0]);
                        mapa->porta.slots[i].hitbox.min.x = mapa->porta.slots[i].hitbox.min.x + mapa->porta.slots[i].posicao.x;
                        mapa->porta.slots[i].hitbox.max.x = mapa->porta.slots[i].hitbox.max.x + mapa->porta.slots[i].posicao.x;
                        mapa->porta.slots[i].hitbox.min.z = mapa->porta.slots[i].hitbox.min.z + mapa->porta.slots[i].posicao.z;
                        mapa->porta.slots[i].hitbox.max.z = mapa->porta.slots[i].hitbox.max.z + mapa->porta.slots[i].posicao.z;
                        mapa->porta.slots[i].hitbox.min.y = mapa->porta.slots[i].hitbox.min.y + mapa->porta.slots[i].posicao.y;
                        mapa->porta.slots[i].hitbox.max.y = mapa->porta.slots[i].hitbox.max.y + mapa->porta.slots[i].posicao.y;
                    }
                    break;
                    case 1:
                    {
                        mapa->porta.slots[i].hitbox = GetModelBoundingBox(mapa->porta.base.modelo[1]);
                        mapa->porta.slots[i].hitbox.min.x = mapa->porta.slots[i].hitbox.min.x + mapa->porta.slots[i].posicao.x;
                        mapa->porta.slots[i].hitbox.max.x = mapa->porta.slots[i].hitbox.max.x + mapa->porta.slots[i].posicao.x;
                        mapa->porta.slots[i].hitbox.min.z = mapa->porta.slots[i].hitbox.min.z + mapa->porta.slots[i].posicao.z;
                        mapa->porta.slots[i].hitbox.max.z = mapa->porta.slots[i].hitbox.max.z + mapa->porta.slots[i].posicao.z;
                        mapa->porta.slots[i].hitbox.min.y = mapa->porta.slots[i].hitbox.min.y + mapa->porta.slots[i].posicao.y;
                        mapa->porta.slots[i].hitbox.max.y = mapa->porta.slots[i].hitbox.max.y + mapa->porta.slots[i].posicao.y;
                    }
                    break;
                    case 2:
                    {
                        mapa->porta.slots[i].hitbox = GetModelBoundingBox(mapa->porta.base.modelo[2]);
                        mapa->porta.slots[i].hitbox.min.x = mapa->porta.slots[i].hitbox.min.x + mapa->porta.slots[i].posicao.x;
                        mapa->porta.slots[i].hitbox.max.x = mapa->porta.slots[i].hitbox.max.x + mapa->porta.slots[i].posicao.x;
                        mapa->porta.slots[i].hitbox.min.z = mapa->porta.slots[i].hitbox.min.z + mapa->porta.slots[i].posicao.z;
                        mapa->porta.slots[i].hitbox.max.z = mapa->porta.slots[i].hitbox.max.z + mapa->porta.slots[i].posicao.z;
                        mapa->porta.slots[i].hitbox.min.y = mapa->porta.slots[i].hitbox.min.y + mapa->porta.slots[i].posicao.y;
                        mapa->porta.slots[i].hitbox.max.y = mapa->porta.slots[i].hitbox.max.y + mapa->porta.slots[i].posicao.y;
                    }
                    break;
                    case 3:
                    {
                        mapa->porta.slots[i].hitbox = GetModelBoundingBox(mapa->porta.base.modelo[3]);
                        mapa->porta.slots[i].hitbox.min.x = mapa->porta.slots[i].hitbox.min.x + mapa->porta.slots[i].posicao.x;
                        mapa->porta.slots[i].hitbox.max.x = mapa->porta.slots[i].hitbox.max.x + mapa->porta.slots[i].posicao.x;
                        mapa->porta.slots[i].hitbox.min.z = mapa->porta.slots[i].hitbox.min.z + mapa->porta.slots[i].posicao.z;
                        mapa->porta.slots[i].hitbox.max.z = mapa->porta.slots[i].hitbox.max.z + mapa->porta.slots[i].posicao.z;
                        mapa->porta.slots[i].hitbox.min.y = mapa->porta.slots[i].hitbox.min.y + mapa->porta.slots[i].posicao.y;
                        mapa->porta.slots[i].hitbox.max.y = mapa->porta.slots[i].hitbox.max.y + mapa->porta.slots[i].posicao.y;
                    }
                    break;
                }
            }
            else if(mapa->porta.slots[i].invertido == true)
            {
                switch (mapa->porta.slots[i].frame)
                {
                    case 0:
                    {
                        mapa->porta.slots[i].hitbox = GetModelBoundingBox(mapa->porta.base.modelo[0]);
                        mapa->porta.slots[i].hitbox.min.x = mapa->porta.slots[i].hitbox.min.x + mapa->porta.slots[i].posicao.x;
                        mapa->porta.slots[i].hitbox.max.x = mapa->porta.slots[i].hitbox.max.x + mapa->porta.slots[i].posicao.x;
                        mapa->porta.slots[i].hitbox.min.z = mapa->porta.slots[i].hitbox.min.z + mapa->porta.slots[i].posicao.z;
                        mapa->porta.slots[i].hitbox.max.z = mapa->porta.slots[i].hitbox.max.z + mapa->porta.slots[i].posicao.z;
                        mapa->porta.slots[i].hitbox.min.y = mapa->porta.slots[i].hitbox.min.y + mapa->porta.slots[i].posicao.y;
                        mapa->porta.slots[i].hitbox.max.y = mapa->porta.slots[i].hitbox.max.y + mapa->porta.slots[i].posicao.y;
                    }
                    break;
                    case 1:
                    {
                        mapa->porta.slots[i].hitbox = GetModelBoundingBox(mapa->porta.base.modeloI[0]);
                        mapa->porta.slots[i].hitbox.min.x = mapa->porta.slots[i].hitbox.min.x + mapa->porta.slots[i].posicao.x;
                        mapa->porta.slots[i].hitbox.max.x = mapa->porta.slots[i].hitbox.max.x + mapa->porta.slots[i].posicao.x;
                        mapa->porta.slots[i].hitbox.min.z = mapa->porta.slots[i].hitbox.min.z + mapa->porta.slots[i].posicao.z;
                        mapa->porta.slots[i].hitbox.max.z = mapa->porta.slots[i].hitbox.max.z + mapa->porta.slots[i].posicao.z;
                        mapa->porta.slots[i].hitbox.min.y = mapa->porta.slots[i].hitbox.min.y + mapa->porta.slots[i].posicao.y;
                        mapa->porta.slots[i].hitbox.max.y = mapa->porta.slots[i].hitbox.max.y + mapa->porta.slots[i].posicao.y;
                    }
                    break;
                    case 2:
                    {
                        mapa->porta.slots[i].hitbox = GetModelBoundingBox(mapa->porta.base.modeloI[1]);
                        mapa->porta.slots[i].hitbox.min.x = mapa->porta.slots[i].hitbox.min.x + mapa->porta.slots[i].posicao.x;
                        mapa->porta.slots[i].hitbox.max.x = mapa->porta.slots[i].hitbox.max.x + mapa->porta.slots[i].posicao.x;
                        mapa->porta.slots[i].hitbox.min.z = mapa->porta.slots[i].hitbox.min.z + mapa->porta.slots[i].posicao.z;
                        mapa->porta.slots[i].hitbox.max.z = mapa->porta.slots[i].hitbox.max.z + mapa->porta.slots[i].posicao.z;
                        mapa->porta.slots[i].hitbox.min.y = mapa->porta.slots[i].hitbox.min.y + mapa->porta.slots[i].posicao.y;
                        mapa->porta.slots[i].hitbox.max.y = mapa->porta.slots[i].hitbox.max.y + mapa->porta.slots[i].posicao.y;
                    }
                    break;
                    case 3:
                    {
                        mapa->porta.slots[i].hitbox = GetModelBoundingBox(mapa->porta.base.modeloI[2]);
                        mapa->porta.slots[i].hitbox.min.x = mapa->porta.slots[i].hitbox.min.x + mapa->porta.slots[i].posicao.x;
                        mapa->porta.slots[i].hitbox.max.x = mapa->porta.slots[i].hitbox.max.x + mapa->porta.slots[i].posicao.x;
                        mapa->porta.slots[i].hitbox.min.z = mapa->porta.slots[i].hitbox.min.z + mapa->porta.slots[i].posicao.z;
                        mapa->porta.slots[i].hitbox.max.z = mapa->porta.slots[i].hitbox.max.z + mapa->porta.slots[i].posicao.z;
                        mapa->porta.slots[i].hitbox.min.y = mapa->porta.slots[i].hitbox.min.y + mapa->porta.slots[i].posicao.y;
                        mapa->porta.slots[i].hitbox.max.y = mapa->porta.slots[i].hitbox.max.y + mapa->porta.slots[i].posicao.y;
                    }
                    break;
                }
            }
        }
    }
    
}

void PORTA_ANIM(MAPA* mapa)
{
    for(int qual = 0; qual < 10; qual++)
    {
        if(mapa->porta.slots[qual].existe)
        {
            if(mapa->porta.slots[qual].abrindo)
            {
                if(mapa->porta.slots[qual].relogioNovo > mapa->porta.slots[qual].relogioVelho+10000)
                {
                    mapa->porta.slots[qual].relogioVelho = mapa->porta.slots[qual].relogioNovo;
                }
                mapa->porta.slots[qual].relogioNovo = clock();
                
                if(mapa->porta.slots[qual].relogioNovo > mapa->porta.slots[qual].relogioVelho+10000&&mapa->porta.slots[qual].frame < 3)
                {
                    mapa->porta.slots[qual].frame++;
                }
                else if(mapa->porta.slots[qual].frame == 3&&mapa->porta.slots[qual].relogioNovo > mapa->porta.slots[qual].relogioVelho+10000)
                {

                    mapa->porta.slots[qual].abrindo = false;
                    mapa->porta.slots[qual].aberta = true;
                    PORTA_HBUPDATE(*&mapa);
                }
                
            }
            else if(mapa->porta.slots[qual].fechando)
            {
                
                if(mapa->porta.slots[qual].relogioNovo > mapa->porta.slots[qual].relogioVelho+10000)
                {
                    mapa->porta.slots[qual].relogioVelho = mapa->porta.slots[qual].relogioNovo;
                }
                mapa->porta.slots[qual].relogioNovo = clock();
                
                if(mapa->porta.slots[qual].relogioNovo > mapa->porta.slots[qual].relogioVelho+10000&&mapa->porta.slots[qual].frame > 0)
                {
                    mapa->porta.slots[qual].frame--;
                }
                else if(mapa->porta.slots[qual].frame == 0&&mapa->porta.slots[qual].relogioNovo > mapa->porta.slots[qual].relogioVelho+10000)
                {
                    mapa->porta.slots[qual].fechando = false;
                    mapa->porta.slots[qual].aberta = false;
                    PORTA_HBUPDATE(*&mapa);
                }
                
            }
        }
    }
} 
