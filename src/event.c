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

void MQCreateEventbox(DATA *data, char *name, BoundingBox Hitbox)
{
    data->file.eventbox[data->session.counter.hitbox] = Hitbox;
    strcpy(data->session.LoadedNames.eventbox[data->session.counter.eventbox],name);
    data->session.counter.eventbox++;
}

void MQCreateEmptyEventbox(DATA *data, char *name)
{
    strcpy(data->session.LoadedNames.eventbox[data->session.counter.eventbox],name);
    data->session.counter.eventbox++;
}

int MQFindEventboxIndexByName(DATA data, char* name)
{
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data.session.LoadedNames.eventbox[i], name)==0)
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
        data->session.event[i].name = " ";
        data->session.event[i].eventboxIndex = MQTRUE;
        data->session.event[i].eventFuncionIndex = MQTRUE;
        data->session.event[i].position = (Vector3){MQTRUE,MQTRUE,MQTRUE};
        data->session.event[i].rotation = MQTRUE;
        data->session.event[i].active = false;
    }
}

void MQAddEventToQueue(DATA *data, char*name, int functionIndex, int eventboxIndex, Vector3 position, float rotation, bool active)
{
    int LocalIndex;
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(data->session.render.text[i].textIndex == __INT_MAX__)
        {
            LocalIndex = i;
            break;
        }
    }
    data->session.event[LocalIndex].name = name;
    data->session.event[LocalIndex].eventboxIndex = eventboxIndex;
    data->session.event[LocalIndex].eventFuncionIndex = functionIndex;
    data->session.event[LocalIndex].position = position;
    data->session.event[LocalIndex].rotation = rotation;
    data->session.event[LocalIndex].active = active;
}

int MQFindEventIndexByName(DATA data, char* name)
{
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(MQEventNames[i] , name)==0)
        {
            return i;
        }
    }
    return -1;
}

/* typedef float (*event)(DATA*, float); */                 //declare typdef

/* event func[3] = {&event0, &event1, &event2}; */
