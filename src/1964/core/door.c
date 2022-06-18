
void MQDoorCreate(DATA *data, Vector3 posicaoLOCAL, bool invertidoLOCAL, bool trancadaLOCAL, bool abertaLOCAL)
{
    for(int i = 0; i < MAXOBJ ; i++)
    {
        if(data->file.mapa.porta.slots[i].existe == false)
        {
            data->file.mapa.porta.slots[i].frame = 0;
            data->file.mapa.porta.slots[i].existe = true;
            data->file.mapa.porta.slots[i].abrindo = false;
            data->file.mapa.porta.slots[i].fechando = false;
            data->file.mapa.porta.slots[i].aberta = false;
            data->file.mapa.porta.slots[i].invertido = invertidoLOCAL;
            data->file.mapa.porta.slots[i].posicao = posicaoLOCAL;
            data->file.mapa.porta.slots[i].trancada = trancadaLOCAL;

            if(abertaLOCAL == false)
            {
                data->file.mapa.porta.slots[i].hitbox = GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta0"))]);
            }
            else if(abertaLOCAL == true)
            {
                if(invertidoLOCAL == false)
                {
                    data->file.mapa.porta.slots[i].hitbox = GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta3"))]);
                }
                else if(invertidoLOCAL == true)
                {
                    data->file.mapa.porta.slots[i].hitbox = GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta-2"))]);;
                }
            }
            data->file.mapa.porta.slots[i].hitbox = MQHitboxUpdateXYZ(data->file.mapa.porta.slots[i].hitbox, data->file.mapa.porta.slots[i].posicao);
            i = 80;
        }
    }

}

void MQUpdateDoor(DATA *data)
{
    for(int i = 0; i < MAXOBJ; i++)
    {
        if(data->file.mapa.porta.slots[i].existe)
        {
            if(data->file.mapa.porta.slots[i].invertido == false)
            {
                switch(data->file.mapa.porta.slots[i].frame)
                {
                    case 0:
                    {
                        data->file.mapa.porta.slots[i].hitbox = GetModelBoundingBox(data->file.mapa.porta.base.modelo[0]);
                        data->file.mapa.porta.slots[i].hitbox = MQHitboxUpdateXYZ(data->file.mapa.porta.slots[i].hitbox, data->file.mapa.porta.slots[i].posicao);
                    }
                    break;
                    case 1:
                    {
                        data->file.mapa.porta.slots[i].hitbox = GetModelBoundingBox(data->file.mapa.porta.base.modelo[1]);
                        data->file.mapa.porta.slots[i].hitbox = MQHitboxUpdateXYZ(data->file.mapa.porta.slots[i].hitbox, data->file.mapa.porta.slots[i].posicao);
                    }
                    break;
                    case 2:
                    {
                        data->file.mapa.porta.slots[i].hitbox = GetModelBoundingBox(data->file.mapa.porta.base.modelo[2]);
                        data->file.mapa.porta.slots[i].hitbox = MQHitboxUpdateXYZ(data->file.mapa.porta.slots[i].hitbox, data->file.mapa.porta.slots[i].posicao);
                    }
                    break;
                    case 3:
                    {
                        data->file.mapa.porta.slots[i].hitbox = GetModelBoundingBox(data->file.mapa.porta.base.modelo[3]);
                        data->file.mapa.porta.slots[i].hitbox = MQHitboxUpdateXYZ(data->file.mapa.porta.slots[i].hitbox, data->file.mapa.porta.slots[i].posicao);
                    }
                    break;
                }
            }
            else if(data->file.mapa.porta.slots[i].invertido == true)
            {
                switch(data->file.mapa.porta.slots[i].frame)
                {
                    case 0:
                    {
                        data->file.mapa.porta.slots[i].hitbox = GetModelBoundingBox(data->file.mapa.porta.base.modelo[0]);
                        data->file.mapa.porta.slots[i].hitbox = MQHitboxUpdateXYZ(data->file.mapa.porta.slots[i].hitbox, data->file.mapa.porta.slots[i].posicao);
                    }
                    break;
                    case 1:
                    {
                        data->file.mapa.porta.slots[i].hitbox = MQHitboxUpdateXYZ(data->file.mapa.porta.slots[i].hitbox, data->file.mapa.porta.slots[i].posicao);
                    }
                    break;
                    case 2:
                    {
                        data->file.mapa.porta.slots[i].hitbox = GetModelBoundingBox(data->file.mapa.porta.base.modeloI[1]);
                        data->file.mapa.porta.slots[i].hitbox = MQHitboxUpdateXYZ(data->file.mapa.porta.slots[i].hitbox, data->file.mapa.porta.slots[i].posicao);
                    }
                    break;
                    case 3:
                    {
                        data->file.mapa.porta.slots[i].hitbox = GetModelBoundingBox(data->file.mapa.porta.base.modeloI[2]);
                        data->file.mapa.porta.slots[i].hitbox = MQHitboxUpdateXYZ(data->file.mapa.porta.slots[i].hitbox, data->file.mapa.porta.slots[i].posicao);
                    }
                    break;
                }
            }
        }
    }
}

void MQDoorAnim(DATA *data)
{
    for(int qual = 0; qual < MAXOBJ; qual++)
    {
        if(data->file.mapa.porta.slots[qual].existe)
        {
            if(data->file.mapa.porta.slots[qual].abrindo)
            {
                if(data->file.mapa.porta.slots[qual].relogioNovo > data->file.mapa.porta.slots[qual].relogioVelho + 10000)
                {
                    data->file.mapa.porta.slots[qual].relogioVelho = data->file.mapa.porta.slots[qual].relogioNovo;
                }
                data->file.mapa.porta.slots[qual].relogioNovo = clock();

                if(data->file.mapa.porta.slots[qual].relogioNovo > data->file.mapa.porta.slots[qual].relogioVelho + 10000 && data->file.mapa.porta.slots[qual].frame < 3)
                {
                    data->file.mapa.porta.slots[qual].frame++;
                }
                else if(data->file.mapa.porta.slots[qual].frame == 3 && data->file.mapa.porta.slots[qual].relogioNovo > data->file.mapa.porta.slots[qual].relogioVelho + 10000)
                {

                    data->file.mapa.porta.slots[qual].abrindo = false;
                    data->file.mapa.porta.slots[qual].aberta = true;
                    MQUpdateDoor( *&data);
                }
            }
            else if(data->file.mapa.porta.slots[qual].fechando)
            {
                if(data->file.mapa.porta.slots[qual].relogioNovo > data->file.mapa.porta.slots[qual].relogioVelho + 10000)
                {
                    data->file.mapa.porta.slots[qual].relogioVelho = data->file.mapa.porta.slots[qual].relogioNovo;
                }
                data->file.mapa.porta.slots[qual].relogioNovo = clock();

                if(data->file.mapa.porta.slots[qual].relogioNovo > data->file.mapa.porta.slots[qual].relogioVelho + 10000 && data->file.mapa.porta.slots[qual].frame > 0)
                {
                    data->file.mapa.porta.slots[qual].frame--;
                }
                else if(data->file.mapa.porta.slots[qual].frame == 0 && data->file.mapa.porta.slots[qual].relogioNovo > data->file.mapa.porta.slots[qual].relogioVelho + 10000)
                {
                    data->file.mapa.porta.slots[qual].fechando = false;
                    data->file.mapa.porta.slots[qual].aberta = false;
                    MQUpdateDoor( *&data);
                }
            }
        }
    }
}
