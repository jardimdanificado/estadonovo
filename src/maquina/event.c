typedef float (*EVENTFUNC)(MQDATA*, float, float);

float event0(MQDATA* data, float optionalIn0, float optionalIn1) 
{
    data->game.personagem[0].posicao.y += 5;
    return 0;
}

float event1(MQDATA* data, float optionalIn0, float optionalIn1) 
{
    return 0;
}

float event2(MQDATA* data, float optionalIn0, float optionalIn1) 
{
    return 0;
}

EVENTFUNC MQEventFunctions[3] = {&event0,&event1,&event2};
char *MQEventNames[3] = {"evento0","evento1","evento2"};

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

void MQCleanAllMapItemSlots(MQDATA* data)
{
    for (short int i = 0; i < MAXOBJ; i++)
    {
        data->game.map.item[i].name = " ";
        data->game.map.item[i].type = " ";
        data->game.map.item[i].index = MQTRUE;
        data->game.map.item[i].content = MQTRUE;
        data->game.map.item[i].active = false;
        data->game.map.item[i].hitbox = (BoundingBox){(Vector3){MQTRUE,MQTRUE,MQTRUE},(Vector3){MQTRUE,MQTRUE,MQTRUE}};
        data->game.map.item[i].position = (Vector3){MQTRUE,MQTRUE,MQTRUE};
        data->game.map.item[i].rotation = MQTRUE;
        data->game.map.item[i].function = MQTRUE;
    }
}

void MQAddMapItemToQueue(MQDATA *data, char*name, char*type, Vector3 position, float rotation, int index, float content, int function, BoundingBox hitbox, bool active)
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
    data->game.map.item[LocalIndex].active = true;
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
