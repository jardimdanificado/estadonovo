typedef float (*EVENTFUNC)(MQDATA*, float);

float event0(MQDATA* data, float b) 
{
    data->game.personagem[0].posicao.y += 5;
    return 0;
}

float event1(MQDATA* data, float b) 
{
    return 0;
}

float event2(MQDATA* data, float b) 
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
        if(strcmp(data->queue.event[i].name," ")==0)
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
        if(strcmp(data->queue.event[i].name," ")==0)
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
        data->queue.event[i].name = " ";
        data->queue.event[i].hitbox = (BoundingBox){(Vector3){0,0,0},(Vector3){0,0,0}};
        data->queue.event[i].function = MQTRUE;
        data->queue.event[i].position = (Vector3){0,0,0};
        data->queue.event[i].rotation = 0;
        data->queue.event[i].active = false;
        data->queue.event[i].persistent = false;
    }
}

void MQAddEventToQueue(MQDATA *data, char*name, int functionIndex, BoundingBox hitbox, Vector3 position, float rotation, bool active, bool persistent)
{
    int LocalIndex;
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data->queue.event[i].name," ")==0)
        {
            LocalIndex = i;
            break;
        }
    }
    data->queue.event[LocalIndex].name = name;
    data->queue.event[LocalIndex].hitbox = hitbox;
    data->queue.event[LocalIndex].function = functionIndex;
    data->queue.event[LocalIndex].position = position;
    data->queue.event[LocalIndex].rotation = rotation;
    data->queue.event[LocalIndex].active = active;
    data->queue.event[LocalIndex].persistent = persistent;
}

void MQDeleteEvent(MQDATA* data, int index)
{
    data->queue.event[index].name = " ";
    data->queue.event[index].active = false;
    data->queue.event[index].persistent = false;
}

int MQFindEvent(MQDATA data, char* name)
{
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data.queue.event[i].name , name)==0)
        {
            return i;
        }
    }
    return -1;
}
