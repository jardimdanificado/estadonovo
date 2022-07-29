void MQPlayerConfigStart(MQDATA *data, int quem, Vector3 posi)
{
    //tipos
    //0 - calca
    //1 - chapeu
    //2 - camisa
    //3 - sapatos
    //4 - oculos
    //5 - arma
    data->game.player[quem].fallTime = 0;
    data->game.player[quem].rotation = 180;
    data->game.player[quem].position.y = posi.y;
    data->game.player[quem].position.x = posi.x;
    data->game.player[quem].position.z = posi.z;
    data->game.player[quem].speed = 0.1f;
    char bufferLocal[64];
    snprintf(bufferLocal,64,"playerexclude%d",quem);

    MQAddWallexcludeToQueue(*&data,MQCreateWallexclude(bufferLocal,false,MQTRUE));
}

Vector3 MQPlayerMove(Vector3 position, float rotation, float speed)
{
    //z+ frente
    //x+ esquerda
    float  valorZ, valorX;
    int giro = rotation / 90;
    float resto = rotation - (90 * giro);
    float restodoresto = 90 - resto;
    valorZ = speed - resto * (speed / 90);
    valorX = speed - restodoresto * (speed / 90);
    switch(giro)
    {
        case 0:
        {
            position.z += valorZ;
            position.x += valorX;
        }
        break;
        case 1:
        {
            position.z -= valorX;
            position.x += valorZ;
        }
        break;
        case 2:
        {
            position.z -= valorZ;
            position.x -= valorX;
        }
        break;
        case 3:
        {
            position.z += valorX;
            position.x -= valorZ;
        }
        break;
    }
    return position;
}

void MQPlayerPickupItem(MQDATA*data,int quem)
{
    int mapboxindex;
    char bufferLocal[64];
    snprintf(bufferLocal,64,"playeruse%d",quem);
    mapboxindex = MQVerifyMapItemColision(*data, MQHitboxUpdateXYZ(data->game.event[MQFindEvent(*data,bufferLocal)].hitbox, data->game.event[MQFindEvent(*data,bufferLocal)].position));
    if(mapboxindex!=-1)
    {
        int localIndex=-1;
        for(int i = 0;i<MAXOBJ;i++)
        {
            if(strcmp(data->game.player[quem].inventory.equip[i].name," ")==0)
            {
                localIndex = i;
                break;
            }
        }

        MQDATA_GAME_ITEM item = MQCreateItem(data->game.map.item[mapboxindex].name,data->game.map.item[mapboxindex].type,data->game.map.item[mapboxindex].index,data->game.map.item[mapboxindex].position,data->game.map.item[mapboxindex].rotation,data->game.map.item[mapboxindex].condition,data->game.map.item[mapboxindex].content,data->game.map.item[mapboxindex].function,data->game.map.item[mapboxindex].hitbox,data->game.map.item[mapboxindex].locked,data->game.map.item[mapboxindex].active);

        if(localIndex!=-1&&data->game.map.item[mapboxindex].active==true&&strcmp(data->game.map.item[mapboxindex].name," ")==0)
        {
            if(strcmp(data->game.map.item[mapboxindex].type,"calca")==0&&strcmp(data->game.map.item[mapboxindex].type,"camisa")==0&&strcmp(data->game.map.item[mapboxindex].type,"chapeu")==0&&strcmp(data->game.map.item[mapboxindex].type,"sapatos")==0&&strcmp(data->game.map.item[mapboxindex].type,"oculos")==0&&strcmp(data->game.map.item[mapboxindex].type,"arma")==0)
            {
                MQAddEquipToPlayerInventory(*&data,quem,item);
            }
            else
            {
                MQAddItemToPlayerInventory(*&data,quem,item);
            }
        }
        else
        {
            MQAddItemToPlayerInventory(*&data,quem,item);
        }
    }
}