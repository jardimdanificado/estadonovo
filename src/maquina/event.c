void MQCreateEventbox(MQDATA *data, char *name, BoundingBox Hitbox)
{
    int LocalIndex;
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data->game.event[i].name," ")==0)
        {
            LocalIndex = i;
            break;
        }
    }
    data->files.eventboxes[LocalIndex].hitbox= Hitbox;
    strcpy(data->files.eventboxes[LocalIndex].name,name);
    LocalIndex++;
}

void MQCreateEmptyEventbox(MQDATA *data, char *name)
{
    int LocalIndex;
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data->game.event[i].name," ")==0)
        {
            LocalIndex = i;
            break;
        }
    }
    strcpy(data->files.eventboxes[LocalIndex].name,name);
    LocalIndex++;
}

int MQFindEventbox(MQDATA data, char* name)
{
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data.files.eventboxes[i].name, name)==0)
        {
            return i;
        }
    }
    return -1;
}

void MQCleanAllEventSlots(MQDATA *data)
{
    for(int i = 0;i<MAXOBJ;i++)
    { 
        data->game.event[i].name = " ";
        data->game.event[i].hitbox = (BoundingBox){(Vector3){0,0,0},(Vector3){0,0,0}};
        data->game.event[i].function = MQTRUE;
        data->game.event[i].position = (Vector3){0,0,0};
        data->game.event[i].rotation = 0;
        data->game.event[i].active = false;
        data->game.event[i].persistent = false;
    }
}

void MQAddEventToQueue(MQDATA *data, char*name, int functionIndex, BoundingBox hitbox, Vector3 position, float rotation, bool active, bool persistent)
{
    int LocalIndex;
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data->game.event[i].name," ")==0)
        {
            LocalIndex = i;
            break;
        }
    }
    data->game.event[LocalIndex].name = name;
    data->game.event[LocalIndex].hitbox = hitbox;
    data->game.event[LocalIndex].function = functionIndex;
    data->game.event[LocalIndex].position = position;
    data->game.event[LocalIndex].rotation = rotation;
    data->game.event[LocalIndex].active = active;
    data->game.event[LocalIndex].persistent = persistent;
}

void MQDeleteEvent(MQDATA* data, int index)
{
    data->game.event[index].name = " ";
    data->game.event[index].active = false;
    data->game.event[index].persistent = false;
}

int MQFindEvent(MQDATA data, char* name)
{
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data.game.event[i].name , name)==0)
        {
            return i;
        }
    }
    return -1;
}

//-----------------------------------
//ITEM
//-----------------------------------

//only use this with MQDATA_GAME_ITEM pointers
MQDATA_GAME_ITEM MQCreateItem(char*name, char* type, int index,Vector3 position, float rotation, float condition, float content, int function, BoundingBox hitbox, bool locked, bool active)
{
    return((MQDATA_GAME_ITEM){name,type,index,content,condition,function,active,locked,hitbox,position,rotation});
}

MQDATA_GAME_ITEM MQCreateEmptyItem()
{
    return((MQDATA_GAME_ITEM){" "," ",MQTRUE,MQTRUE,MQTRUE,MQTRUE,false,false,(BoundingBox){(Vector3){MQTRUE,MQTRUE,MQTRUE},(Vector3){MQTRUE,MQTRUE,MQTRUE}},MQTRUE,MQTRUE});
}

void MQCleanAllItemSlots(MQDATA* data)
{
    for (short int i = 0; i < MAXOBJ; i++)
    {
        data->game.map.item[i] = MQCreateEmptyItem();
        for (short int x = 0; x < MAXOBJ; x++)
        {
            data->game.player[i].inventory.equip[x] = MQCreateEmptyItem();
            data->game.player[i].inventory.item[x] = MQCreateEmptyItem();
        }
    }
}

void MQAddEquipToPlayerInventory(MQDATA *data, int quem, char*name, char* type,int index, Vector3 position, float rotation, float condition, float content, int function, BoundingBox hitbox, bool locked, bool active)
{
    int LocalIndex;
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data->game.player[quem].inventory.item[i].name," ")==0)
        {
            LocalIndex = i;
            break;
        }
    }
    data->game.player[quem].inventory.item[LocalIndex] = MQCreateItem(name,type,index,position,rotation,condition,content,function,hitbox,locked,active);
}
void MQAddMapItemToQueue(MQDATA *data, char*name, char* type,int index, Vector3 position, float rotation, float condition, float content, int function, BoundingBox hitbox, bool locked, bool active)
{
    int LocalIndex;
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data->game.map.item[i].name," ")==0)
        {
            LocalIndex = i;
            break;
        }
    }
    
    data->game.map.item[LocalIndex].name = name;
    data->game.map.item[LocalIndex].type = type;
    data->game.map.item[LocalIndex].position = position;
    data->game.map.item[LocalIndex].rotation = rotation;
    data->game.map.item[LocalIndex].index = index;
    data->game.map.item[LocalIndex].content = content;
    data->game.map.item[LocalIndex].function = function;
    data->game.map.item[LocalIndex].hitbox = hitbox;
    data->game.map.item[LocalIndex].active = active;
    data->game.map.item[LocalIndex].locked = locked;
}

int MQFindMapItem(MQDATA data, char* name)
{
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data.game.map.item[i].name , name)==0)
        {
            return i;
        }
    }
    return -1;
}

void MQDeleteMapItem(MQDATA* data, int index)
{
    data->game.map.item[index].name = " ";
    data->game.map.item[index].type = " ";
    data->game.map.item[index].index = MQTRUE;
    data->game.map.item[index].content = MQTRUE;
    data->game.map.item[index].active = false;
    data->game.map.item[index].hitbox = (BoundingBox){(Vector3){MQTRUE,MQTRUE,MQTRUE},(Vector3){MQTRUE,MQTRUE,MQTRUE}};
    data->game.map.item[index].position = (Vector3){MQTRUE,MQTRUE,MQTRUE};
    data->game.map.item[index].rotation = 0;
    data->game.map.item[index].function = MQTRUE;
}

int MQVerifyMapItemColision(MQDATA data, BoundingBox collider)
{
    for (short int i = 0; i < MAXOBJ; i++)
    {
        if(data.game.map.item[i].active == true)
        {
            if(CheckCollisionBoxes(collider,data.game.map.item[i].hitbox)==true)
            {
                return i;
            }
        }
    }
    return -1;
}
