
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
            char bufferlocal[32];
            snprintf(bufferlocal,32,"porta%d",i);

            if(abertaLOCAL == false)
            {
                MQCreateHitbox(*&data,bufferlocal,GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta0"))]));
            }
            else
            {
                if(invertidoLOCAL == false)
                {
                    MQCreateHitbox(*&data,bufferlocal,GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta3"))]));
                }
                else 
                {
                    MQCreateHitbox(*&data,bufferlocal,GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta-2"))]));
                }
            }
            data->file.hitbox[atoi(abinCoreReturnData("./data/temp/model.temp", bufferlocal))] = MQHitboxUpdateXYZ(data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE32))], data->file.mapa.porta.slots[i].posicao);
            break;
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
                snprintf(ABINCACHE16,16,"porta%d",i);
                switch(data->file.mapa.porta.slots[i].frame)
                {
                    case 0:
                    {
                        data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))] = GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta0"))]);;
                        data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))] = MQHitboxUpdateXYZ(data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))], data->file.mapa.porta.slots[i].posicao);
                    }
                    break;
                    case 1:
                    {
                        data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))] = GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta1"))]);
                        data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))] = MQHitboxUpdateXYZ(data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))], data->file.mapa.porta.slots[i].posicao);
                    }
                    break;
                    case 2:
                    {
                        data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))] = GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta2"))]);
                        data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))] = MQHitboxUpdateXYZ(data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))], data->file.mapa.porta.slots[i].posicao);
                    }
                    break;
                    case 3:
                    {
                        data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))] = GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta3"))]);
                        data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))] = MQHitboxUpdateXYZ(data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))], data->file.mapa.porta.slots[i].posicao);
                    }
                    break;
                }
            }
            else
            {
                switch(data->file.mapa.porta.slots[i].frame)
                {
                    case 0:
                    {
                        data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))] = GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta0"))]);
                        data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))] = MQHitboxUpdateXYZ(data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))], data->file.mapa.porta.slots[i].posicao);
                    }
                    break;
                    case 1:
                    {
                        data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))] = GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta-1"))]);
                        data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))] = MQHitboxUpdateXYZ(data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))], data->file.mapa.porta.slots[i].posicao);
                    }
                    break;
                    case 2:
                    {
                        data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))] = GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta-2"))]);
                        data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))] = MQHitboxUpdateXYZ(data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))], data->file.mapa.porta.slots[i].posicao);
                    }
                    break;
                    case 3:
                    {
                        data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))] = GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta-3"))]);
                        data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))] = MQHitboxUpdateXYZ(data->file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp",ABINCACHE16))], data->file.mapa.porta.slots[i].posicao);
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
