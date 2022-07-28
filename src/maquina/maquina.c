//-----------------------------------
//CALCULATE
//-----------------------------------

float MQDifferenceFloat(float a, float b)
{
    bool negativo = false;
    float resultado;
    if(a < 0)
    {
        a = a * (-1);
        negativo = true;
    }
    else if(b < 0)
    {
        b = b * (-1);
        negativo = true;
    }

    if(negativo == true)
    {
        resultado = a + b;
    }
    else if(a == b)
    {
        return 0;
    }
    else if(a > b)
    {
        resultado = a - b;
    }
    else if(a < b)
    {
        resultado = b - a;
    }
    return resultado;
}

Vector3 MQDifferenceVec3(Vector3 vec1, Vector3 vec2)
{
    return((Vector3) {MQDifferenceFloat(vec1.x, vec2.x), MQDifferenceFloat(vec1.y, vec2.y), MQDifferenceFloat(vec1.z, vec2.z)});
}

//-----------------------------------
//WINDOW
//-----------------------------------

void MQWindowStart()
{
    if(MQMSAAX4 == true)
        SetConfigFlags(FLAG_MSAA_4X_HINT);
    if(MQResizeble == true)
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitAudioDevice();
    InitWindow(MQScreenX, MQScreenY, MQTitle);
}

//-----------------------------------
//FONT&STRING
//-----------------------------------

//Use into a strcmp() or strcpy()
//DONT use it direcly
char *MQStrAddInt(char* string, int value)
{
    char buffer[sizeof(string)];
    strcpy(buffer,string);
    string = malloc(sizeof(string)+8);
    snprintf(string,sizeof(string)+8,"%s%d",buffer,value);
    return string;
}

Font MQFontStart(char *FontLoc, int FontSize)
{
    unsigned int fileSize = 0;
    unsigned char *fileData = LoadFileData(FontLoc, &fileSize);
    // Default font generation from TTF font
    Font fontDefault = { 0 };
    fontDefault.baseSize = FontSize;
    fontDefault.glyphCount = 95;

    // Loading font data from memory data
    // Parameters > font size: FontSize, no glyphs array provided (0), glyphs count: 95 (autogenerate chars array)
    fontDefault.glyphs = LoadFontData(fileData, fileSize, FontSize, 0, 95, FONT_DEFAULT);

    fontDefault.glyphs = LoadFontData(fileData, fileSize, FontSize, 0, 95, FONT_DEFAULT);
    // Parameters > glyphs count: 95, font size: FontSize, glyphs padding in image: 4 px, pack method: 0 (default)
    Image atlas = GenImageFontAtlas(fontDefault.glyphs, &fontDefault.recs, 95, FontSize, 14, 0);
    fontDefault.texture = LoadTextureFromImage(atlas);
    UnloadImage(atlas);

    // SDF font generation from TTF font
    Font fontSDF = { 0 };
    fontSDF.baseSize = FontSize;
    fontSDF.glyphCount = 95;
    // Parameters > font size: FontSize, no glyphs array provided (0), glyphs count: 0 (defaults to 95)
    fontSDF.glyphs = LoadFontData(fileData, fileSize, FontSize, 0, 0, FONT_SDF);
    // Parameters > glyphs count: 95, font size: FontSize, glyphs padding in image: 0 px, pack method: 1 (Skyline algorythm)
    atlas = GenImageFontAtlas(fontSDF.glyphs, &fontSDF.recs, 95, FontSize, 0, 1);
    fontSDF.texture = LoadTextureFromImage(atlas);
    UnloadImage(atlas);

    UnloadFileData(fileData);      // Free memory from loaded file

    // Load SDF required shader (we use default vertex shader)
    //Shader shader = LoadShader(0, TextFormat("data/shaders/sdf.fs", 330));
    SetTextureFilter(fontSDF.texture, TEXTURE_FILTER_POINT);    // Required for SDF font

    return (fontDefault);
}

//-----------------------------------
//FILES
//-----------------------------------

void MQResetAllFileSlots(MQDATA* data)
{
    for(int i = 0; i < MAXOBJ; i++)
    {
        strcpy(data->files.eventboxes[i].name," ");
        strcpy(data->files.fonts[i].name," ");
        strcpy(data->files.hitboxes[i].name," ");
        strcpy(data->files.langs[i].name," ");
        strcpy(data->files.models[i].name," ");
        strcpy(data->files.musics[i].name," ");
        strcpy(data->files.sounds[i].name," ");
        strcpy(data->files.texts[i].name," ");
    }
}

//-----------------------------------
//FIND
//-----------------------------------

int MQFindHitbox(MQDATA data, char* name)
{
    for(int i = 0; i < MAXOBJ; i++)
    {
        if(strcmp(data.files.hitboxes[i].name,name)==0)
            return i;
    }
    return -1;
}

int MQFindModelByName(MQDATA data, char* name)
{
    for(int i = 0; i < MAXOBJ; i++)
    {
        if(strcmp(data.files.models[i].name,name)==0)
            return i;
    }
    return -1;
}

int MQFindRenderModel(MQDATA data, char* name)
{
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data.session.render.model[i].name, name)==0)
        {
            return i;
        }
    }
    return -1;
}

int MQFindRenderTextIndexByName(MQDATA data, char* name)
{
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data.session.render.text[i].name, name)==0)
        {
            return i;
        }
    }
    return -1;
}

//-----------------------------------
//VERTICES
//-----------------------------------

Vector3 MQRotateVerticeSelf(float angle, Vector3 vertice)
{
    Vector3 NewVertice;
    NewVertice.y = vertice.y;
    NewVertice.x = vertice.x * cos(angle) - vertice.z * sin(angle);
    NewVertice.z = vertice.x * sin(angle) + vertice.z * cos(angle);
    return NewVertice;
}

Vector3 MQRotateVertice(Vector3 pivot, float angle, Vector3 vertice)
{
    Vector3 NewVertice;
    NewVertice.y = vertice.y;
    NewVertice.x = ((vertice.x - pivot.x) * cos(angle)) - ((vertice.z - pivot.z) * sin(angle)) + pivot.x;
    NewVertice.z = ((vertice.x - pivot.x) * sin(angle)) + ((vertice.z - pivot.z) * cos(angle)) + pivot.z;
    return NewVertice;
}

//-----------------------------------
//MODELS&HITBOXES
//-----------------------------------

#include "models.c"

//-----------------------------------
//PLAYER
//-----------------------------------

#include "player.c"

//-----------------------------------
//COLISION
//-----------------------------------

float MQGravity(Vector3 position, float gravidade, int tempo)
{
    return(position.y - gravidade*((tempo*(tempo/5)))/60);
}

void MQGravit(MQDATA* data, int quem)
{
    if(MQReturnYMaxCollisionPoint(*data,  data->game.player[quem].position) == MQFALSE)
    {
        data->game.player[quem].position.y = MQGravity(data->game.player[quem].position, 0.1, data->game.player[quem].fallTime);
        data->game.player[quem].fallTime++;
    }
    else 
    {
        data->game.player[quem].position.y = MQReturnYMaxCollisionPoint(*data, data->game.player[quem].position);
        data->game.player[quem].fallTime = 0;
    }
}

//-----------------------------------
//CAMERA
//-----------------------------------

Camera MQCameraStart(Camera *camera)
{
    camera->position = (Vector3)
    {
        10.0f, 10.0f, 10.0f
    };
    camera->target = (Vector3)
    {
        0.0f, 0.0f, 0.0f
    };
    camera->up = (Vector3)
    {
        0.0f, 1.0f, 0.0f
    };
    camera->fovy = 30.0f;
    camera->projection = CAMERA_PERSPECTIVE;
    SetCameraMode(*camera, CAMERA_CUSTOM);
    return (*camera);
}

//-----------------------------------
//LOAD
//-----------------------------------

#include "load.c"


//-----------------------------------
//SAVEGAME
//-----------------------------------

void MQLoadGame(MQDATA *data)
{
/*     FILE *file;
    file = fopen("data/save/savegame", "r+b");
    fread(&data->game, sizeof(struct MQDATA_GAME), 1, file);
    fclose(file); */
}

void MQSaveGame(MQDATA data)
{
/*     remove("data/save/savegame");
    FILE *file = fopen("data/save/savegame", "w+b");
    fwrite(&data.game, sizeof(struct MQDATA_GAME), 1, file);
    fclose(file); */
}

//-----------------------------------
//RENDER
//-----------------------------------

#include "render.c"

//-----------------------------------
//MENU
//-----------------------------------

#include "menu.c"

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

void MQAddEquipToPlayerInventory(MQDATA *data, int quem, MQDATA_GAME_ITEM item)
{
    int LocalIndex;
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data->game.player[quem].inventory.equip[i].name," ")==0)
        {
            LocalIndex = i;
            break;
        }
    }
    data->game.player[quem].inventory.equip[LocalIndex] = MQCreateItem(item.name,item.type,item.index,item.position,item.rotation,item.condition,item.content,item.function,item.hitbox,item.locked,item.active);
}

void MQAddItemToPlayerInventory(MQDATA *data, int quem, MQDATA_GAME_ITEM item)
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
    data->game.player[quem].inventory.item[LocalIndex] = MQCreateItem(item.name,item.type,item.index,item.position,item.rotation,item.condition,item.content,item.function,item.hitbox,item.locked,item.active);
}

void MQAddItemToMapQueue(MQDATA *data, MQDATA_GAME_ITEM item)
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
    data->game.map.item[LocalIndex] = MQCreateItem(item.name,item.type,item.index,item.position,item.rotation,item.condition,item.content,item.function,item.hitbox,item.locked,item.active);
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

//-----------------------------------
//EVENTS
//-----------------------------------

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
//KEYBOARD
//-----------------------------------

#include "teclado.c"