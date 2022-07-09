typedef float (*EVENTFUNC)(DATA*, float);

float event0(DATA* data, float b) 
{
    return 0;
}

float event1(DATA* data, float b) 
{
    return 0;
}

float event2(DATA* data, float b) 
{
    return 0;
}

EVENTFUNC MQEventFuntions[3] = {&event0,&event1,&event2};
char *MQEventNames[3] = {"evento0","evento1","evento2"};

//-----------------------------------------------------
//EVENTS MANIPULATION
//-----------------------------------------------------

void MQCreateEventbox(DATA *data, char *name, BoundingBox Hitbox)
{
    data->file.eventbox[data->session.counter.hitbox] = Hitbox;
    strcpy(data->session.LoadedFilenames.eventbox[data->session.counter.eventbox],name);
    data->session.counter.eventbox++;
}

void MQCreateEmptyEventbox(DATA *data, char *name)
{
    strcpy(data->session.LoadedFilenames.eventbox[data->session.counter.eventbox],name);
    data->session.counter.eventbox++;
}

int MQFindEventboxIndexByName(DATA data, char* name)
{
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data.session.LoadedFilenames.eventbox[i], name)==0)
        {
            return i;
        }
    }
    return -1;
}

void MQCleanAllEventSlots(DATA *data)
{
    for(int i = 0;i<MAXOBJ;i++)
    { 
        data->queue.event[i].name = " ";
        data->queue.event[i].originEventbox = (BoundingBox){(Vector3){0,0,0},(Vector3){0,0,0}};
        data->queue.event[i].eventFuncionIndex = MQTRUE;
        data->queue.event[i].position = (Vector3){0,0,0};
        data->queue.event[i].rotation = 0;
        data->queue.event[i].active = false;
    }
}

void MQAddEventToQueue(DATA *data, char*name, int functionIndex, BoundingBox originEventbox, Vector3 position, float rotation, bool active)
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
    data->queue.event[LocalIndex].originEventbox = originEventbox;
    data->queue.event[LocalIndex].eventFuncionIndex = functionIndex;
    data->queue.event[LocalIndex].position = position;
    data->queue.event[LocalIndex].rotation = rotation;
    data->queue.event[LocalIndex].active = active;
}

void MQDeleteEvent(DATA* data, int index)
{
    data->queue.event[index].name = " ";
    data->queue.event[index].active = false;
}

int MQFindEventIndexByName(DATA data, char* name)
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

/* typedef float (*event)(DATA*, float); */                 //declare typdef

/* event func[3] = {&event0, &event1, &event2}; */
