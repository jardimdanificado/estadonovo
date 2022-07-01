
BoundingBox MQHitboxUpdateX(BoundingBox hitboxbase, Vector3 targetPosi)
{
    hitboxbase.min.x += targetPosi.x;
    hitboxbase.max.x += targetPosi.x;
    return hitboxbase;
}

BoundingBox MQHitboxUpdateY(BoundingBox hitboxbase, Vector3 targetPosi)
{
    hitboxbase.min.y += targetPosi.y;
    hitboxbase.max.y += targetPosi.y;
    return hitboxbase;
}

BoundingBox MQHitboxUpdateZ(BoundingBox hitboxbase, Vector3 targetPosi)
{
    hitboxbase.min.z += targetPosi.z;
    hitboxbase.max.z += targetPosi.z;
    return hitboxbase;
}

BoundingBox MQHitboxUpdateXYZ(BoundingBox hitboxbase, Vector3 targetPosi)
{
    BoundingBox hitbox;
    hitbox = hitboxbase;
    hitbox.max = Vector3Add(hitboxbase.max,targetPosi);
    hitbox.min = Vector3Add(hitboxbase.min, targetPosi);
    return hitbox;
}

int MQFindHitboxByName(DATA data, char* name)
{
    for(int i = 0; i < MAXOBJ; i++)
    {
        if(strcmp(data.session.LoadedNames[i].hitbox,name)==0)
            return i;
    }
    return -1;
}


int MQFindModelByName(DATA data, char* name)
{
    for(int i = 0; i < MAXOBJ; i++)
    {
        if(strcmp(data.session.LoadedNames[i].model,name)==0)
            return i;
    }
    return -1;
}

int MQFindRenderModelIndexByID(DATA data, char* id)
{
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data.session.render.model[i].id, id)==0)
        {
            return i;
        }
    }
    return -1;
}

int MQFindRenderTextIndexByID(DATA data, char* id)
{
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data.session.render.text[i].id, id)==0)
        {
            return i;
        }
    }
    return -1;
}

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

Vector3 MQDifferenceVec3(Vector3 vec1, Vector3 vec2)
{
    return((Vector3) {MQDifferenceFloat(vec1.x, vec2.x), MQDifferenceFloat(vec1.y, vec2.y), MQDifferenceFloat(vec1.z, vec2.z)});
}

Vector2 MQUpdateDirection(Vector2 posicao, float rotacao)
{
    //z+ frente
    //x+ esquerda
    int giro = rotacao / 90;
    Vector2 Resultado;
    switch(giro)
    {
        case 0:
        {
            Resultado.y = posicao.y;
            Resultado.x = posicao.x;
        }
        break;
        case 1:
        {
            Resultado.x = posicao.y * (-1);
            Resultado.y = posicao.x;
        }
        break;
        case 2:
        {
            Resultado.y = posicao.y * (-1);
            Resultado.x = posicao.x * (-1);
        }
        break;
        case 3:
        {
            Resultado.y = posicao.x;
            Resultado.x = posicao.y * (-1);
        }
        break;
    }
    return Resultado;
}

//-----------------------------------
//WINDOW
//-----------------------------------

void MQWindowInit(const int X, const int Y, const char *title)
{
    InitWindow(X, Y, title);
}

void MQWindowStart()
{
    char title[255];
    strcpy(title, abinCoreReturnData("config.text", "TITLE"));
    MQWindowInit(atoi(abinCoreReturnData("config.text", "SCRX")), atoi(abinCoreReturnData("config.text", "SCRY")), title);
}

//-----------------------------------
//FONT&TEXT 
//-----------------------------------

void MQLoadLangFromFile(DATA* data,char* fileloc)
{
    for(int i = 0; i <atoi(abinCoreReturnData(fileloc,"SIZE"));i++)
    {
        char buffer[4];
        snprintf(buffer,4,"%d",i);
        strcpy(data->file.lang[data->session.LangCount],abinCoreReturnData(fileloc,buffer));
        data->session.LangCount++;
    }
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
//PLAYER
//-----------------------------------

#include "player.c"

//-----------------------------------
//AI
//-----------------------------------

//#include "ai.c"

//-----------------------------------
//GRAVITY
//-----------------------------------

float MQGravit(Vector3 posicao, float gravidade, int tempo)
{
    return(posicao.y - gravidade*((tempo*(tempo/5)))/60);
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
//BULLETS
//-----------------------------------

//#include "core/bullet.c"

//-----------------------------------
//MODELS
//-----------------------------------

#include "models.c"

//-----------------------------------
//DOORS
//-----------------------------------

#include "door.c"

//-----------------------------------
//SAVE
//-----------------------------------

#include "savegame.c"

//-----------------------------------
//RENDER
//-----------------------------------

#include "render.c"

//-----------------------------------
//MENU
//-----------------------------------

#include "menu.c"

//-----------------------------------
//KEYBOARD
//-----------------------------------

#include "teclado.c"