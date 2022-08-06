void MQNewPlayer(MQDATA *data, int quem, Vector3 posi)
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
    MQPlayerCreateBodyBox(*&data,quem);
    snprintf(bufferLocal,64,"playergravityray%d",quem);
    MQAddRayToFiles(*&data,(Ray){.position = (Vector3){data->game.player[quem].position.x,data->game.player[quem].position.y-(0.005*(data->game.player[quem].fallTime+1)),data->game.player[quem].position.z}, .direction = (Vector3){0,1,0}},bufferLocal);
    snprintf(bufferLocal,64,"playerdirectionray%d",quem);
    MQAddRayToFiles(*&data,(Ray){.position = (Vector3){data->game.player[quem].position.x,data->game.player[quem].position.y,data->game.player[quem].position.z}, .direction = (Vector3){0,1,0}},bufferLocal);
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

        MQDATA_GAME_ITEM item = data->game.map.item[mapboxindex];

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