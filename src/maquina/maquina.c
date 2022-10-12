//-----------------------------------
//CALCULATE
//-----------------------------------

float MQDifferenceFloat(float a, float b)
{
    return ((a+b+abs(a-b))/2);
}

Vector3 MQDifferenceVec3(Vector3 vec1, Vector3 vec2)
{
    return((Vector3) {MQDifferenceFloat(vec1.x, vec2.x), MQDifferenceFloat(vec1.y, vec2.y), MQDifferenceFloat(vec1.z, vec2.z)});
}

//-----------------------------------
//FONT&STRING
//-----------------------------------

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

void MQCleanAllFileSlots(MQDATA* data)
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
        strcpy(data->files.rays[i].name," ");
    }
}

//-----------------------------------
//FIND
//-----------------------------------

int MQFindHitbox(MQDATA_FILE_HITBOX *hitboxList, char* name)
{
    for(int i = 0; i < MAXOBJ; i++)
    {
        if(strcmp(hitboxList[i].name,name)==0)
            return i;
    }
    return -1;
}

int MQFindModel(MQDATA data, char* name)
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

int MQFindEmptyHitboxSlot(MQDATA_FILE_HITBOX *hitboxList)
{
    for(int i = 0; i < MAXOBJ; i++)
    {
        if(strcmp(hitboxList[i].name," ")==0)
            return i;
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

//---------------------------------------
//HITBOX
//---------------------------------------

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

MQDATA_FILE_HITBOX MQCreateHitbox(char *name, BoundingBox hitbox)
{
    //abinDEBUGtext("debug.txt",name);
    return((MQDATA_FILE_HITBOX){hitbox,name});
}

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

//---------------------------------------
//RAY
//---------------------------------------

void MQAddRayToFiles(MQDATA*data,Ray ray, char*name)
{
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data->files.rays[i].name," ")==0)
        {
            data->files.rays[i].ray = ray;
            strcpy(data->files.rays[i].name,name);
            break;
        }
    }
}

int MQFindRay(MQDATA data,char*name)
{
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data.files.rays[i].name,name)==0)
        {
            return i;
        }
    }
    return MQTrue;
}

//---------------------------------------
//MODEL
//---------------------------------------

// Update model animated vertex data (positions and normals) for a given frame
// NOTE: Updated data is returned as mesh
Mesh MQApplyMeshTransformFromBone(Model model, ModelAnimation anim, int frame)
{
    if((anim.frameCount > 0) && (anim.bones != NULL) && (anim.framePoses != NULL))
    {
        if(frame >= anim.frameCount) frame = frame % anim.frameCount;

        for(int m = 0; m < model.meshCount; m++)
        {
            Mesh mesh = model.meshes[m];
            if(mesh.boneIds == NULL || mesh.boneWeights == NULL)
            {
                continue;
            }

            bool updated = false; // set to true when anim vertex information is updated
            Vector3 animVertex = { 0 };
            Vector3 animNormal = { 0 };

            Vector3 inTranslation = { 0 };
            Quaternion inRotation = { 0 };
            // Vector3 inScale = { 0 };

            Vector3 outTranslation = { 0 };
            Quaternion outRotation = { 0 };
            Vector3 outScale = { 0 };

            int boneId = 0;
            int boneCounter = 0;
            float boneWeight = 0.0;

            const int vValues = mesh.vertexCount * 3;
            for(int vCounter = 0; vCounter < vValues; vCounter += 3)
            {
                mesh.animVertices[vCounter] = 0;
                mesh.animVertices[vCounter + 1] = 0;
                mesh.animVertices[vCounter + 2] = 0;

                if(mesh.animNormals != NULL)
                {
                    mesh.animNormals[vCounter] = 0;
                    mesh.animNormals[vCounter + 1] = 0;
                    mesh.animNormals[vCounter + 2] = 0;
                }

                // Iterates over 4 bones per vertex
                for(int j = 0; j < 4; j++, boneCounter++)
                {
                    boneWeight = mesh.boneWeights[boneCounter];
                    // early stop when no transformation will be applied
                    if(boneWeight == 0.0f)
                    {
                        continue;
                    }
                    boneId = mesh.boneIds[boneCounter];
                    inTranslation = model.bindPose[boneId].translation;
                    inRotation = model.bindPose[boneId].rotation;
                    outTranslation = anim.framePoses[frame][boneId].translation;
                    outRotation = anim.framePoses[frame][boneId].rotation;
                    outScale = anim.framePoses[frame][boneId].scale;

                    // Vertices processing
                    // NOTE: We use meshes.vertices (default vertex position) to calculate meshes.animVertices (animated vertex position)
                    animVertex = (Vector3) { mesh.vertices[vCounter], mesh.vertices[vCounter + 1], mesh.vertices[vCounter + 2] };
                    animVertex = Vector3Multiply(animVertex, outScale);
                    animVertex = Vector3Subtract(animVertex, inTranslation);
                    animVertex = Vector3RotateByQuaternion(animVertex, QuaternionMultiply(outRotation, QuaternionInvert(inRotation)));
                    animVertex = Vector3Add(animVertex, outTranslation);
                    mesh.animVertices[vCounter] += animVertex.x * boneWeight;
                    mesh.animVertices[vCounter + 1] += animVertex.y * boneWeight;
                    mesh.animVertices[vCounter + 2] += animVertex.z * boneWeight;
                    updated = true;

                    // Normals processing
                    // NOTE: We use meshes.baseNormals (default normal) to calculate meshes.normals (animated normals)
                    if(mesh.normals != NULL)
                    {
                        animNormal = (Vector3) { mesh.normals[vCounter], mesh.normals[vCounter + 1], mesh.normals[vCounter + 2] };
                        animNormal = Vector3RotateByQuaternion(animNormal, QuaternionMultiply(outRotation, QuaternionInvert(inRotation)));
                        mesh.animNormals[vCounter] += animNormal.x * boneWeight;
                        mesh.animNormals[vCounter + 1] += animNormal.y * boneWeight;
                        mesh.animNormals[vCounter + 2] += animNormal.z * boneWeight;
                    }
                }
            }
            if(updated)
            {
                mesh.vertices = mesh.animVertices;
                return(mesh);
            }
        }
    }
}

void MQLoadModel(MQDATA *data, char *name, char *link, bool animated, bool isHitbox)
{
    int LocalIndex;
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data->files.models[i].name," ")==0)
        {
            LocalIndex = i;
            break;
        }
    }
    data->files.models[LocalIndex].model = LoadModel(link);
    strcpy(data->files.models[LocalIndex].name ,name);
    if(animated==true)
    {
        data->files.models[LocalIndex].anim = LoadModelAnimations(link, &MAXANIM);
    }
    if(isHitbox==true)
    {
        data->files.hitboxes[MQFindEmptyHitboxSlot(data->files.hitboxes)].hitbox = MQCreateHitbox(name,GetModelBoundingBox(data->files.models[LocalIndex].model)).hitbox;
        strcpy(data->files.hitboxes[MQFindEmptyHitboxSlot(data->files.hitboxes)].name,name);
    }
}

void MQPlayerCreateBodyBox(MQDATA *data, int quem)
{
    char buffer[266],buffer0[255];
    int modelheadfind;
    modelheadfind = MQFindModel(*data,"player-cabeca");
    for(int i = modelheadfind; i < modelheadfind+14; i++)
    {
        snprintf(buffer,266,"%s%d",data->files.models[i].name,quem);
        snprintf(buffer0,255,"%s",data->files.models[i].name);
        data->files.hitboxes[MQFindEmptyHitboxSlot(data->files.hitboxes)] = MQCreateHitbox(buffer, GetModelBoundingBox(data->files.models[MQFindModel(*data,buffer0)].model));
    } 
}

void MQPlayerUpdateBodyBox(MQDATA *data, int quem, int qualAnim)
{
    Mesh LocalMesh;
    Vector3 LocVec3;
    int modelIndex, hitboxIndex;
    char buffer[128];
    snprintf(buffer,128,"player-cabeca%d",quem);
    int hitboxheadfind,modelheadfind; 
    hitboxheadfind = MQFindHitbox(data->files.hitboxes, buffer);
    modelheadfind = MQFindModel(*data,"player-cabeca");
    for(int i = 0; i < 14; i++)
    {
        modelIndex =  modelheadfind+i;
        hitboxIndex = hitboxheadfind+i;
        snprintf(buffer,128,"player%d",quem);
        LocalMesh = MQApplyMeshTransformFromBone(data->files.models[modelIndex].model, data->files.models[modelIndex].anim[qualAnim], data->session.render.model[MQFindRenderModel(*data,buffer)].currentFrame);
        

        for(int i = 0; i < LocalMesh.vertexCount * 3; i += 3)
        {
            LocVec3 = MQRotateVerticeSelf(270 - ((PI / 180) * (data->game.player[quem].rotation)), (Vector3) {LocalMesh.vertices[i], LocalMesh.vertices[i + 1], LocalMesh.vertices[i + 2]});

            LocalMesh.vertices[i] = LocVec3.x;
            LocalMesh.vertices[i + 1] = LocVec3.y;
            LocalMesh.vertices[i + 2] = LocVec3.z;
        }
        data->files.hitboxes[hitboxIndex].hitbox = GetMeshBoundingBox(LocalMesh);

        data->files.hitboxes[hitboxIndex].hitbox.min = Vector3Add(data->files.hitboxes[hitboxIndex].hitbox.min, (Vector3) {0.06, 0.06, 0.06});
        data->files.hitboxes[hitboxIndex].hitbox.max = Vector3Subtract(data->files.hitboxes[hitboxIndex].hitbox.max, (Vector3) {0.06, 0.06, 0.06});

        data->files.hitboxes[hitboxIndex].hitbox.min = Vector3Add(data->files.hitboxes[hitboxIndex].hitbox.min, data->game.player[quem].position);
        data->files.hitboxes[hitboxIndex].hitbox.max = Vector3Add(data->files.hitboxes[hitboxIndex].hitbox.max, data->game.player[quem].position);
    }
}

//-----------------------------------
//ITEM
//-----------------------------------

//only use this with MQDATA_GAME_ITEM pointers
MQDATA_GAME_ITEM MQCreateItem(char*name, char* type, int index,Vector3 position, float rotation, float condition, float content, int function, BoundingBox hitbox, bool locked, bool active)
{
    return((MQDATA_GAME_ITEM){name,type,index,content,condition,function,active,locked,hitbox,position,rotation});
}

void MQCleanAllItemSlots(MQDATA* data)
{
    for (short int i = 0; i < MAXOBJ; i++)
    {
        data->game.map.item[i] = MQEmptyItem;
        for (short int x = 0; x < MAXOBJ; x++)
        {
            data->game.player[i].inventory.equip[x] = MQEmptyItem;
            data->game.player[i].inventory.item[x] = MQEmptyItem;
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

void MQCleanAllEventSlots(MQDATA *data)
{
    for(int i = 0;i<MAXOBJ;i++)
    { 
        data->game.event[i].name = " ";
        data->game.event[i].hitbox = (BoundingBox){(Vector3){0,0,0},(Vector3){0,0,0}};
        data->game.event[i].function = MQTrue;
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
        if(strcmp(" ", data->game.event[i].name)==0)
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
//AREA
//-----------------------------------

void MQCleanAllAreaSlots(MQDATA*data)
{
    for(int i = 0;i<MAXOBJ;i++)
    {
        data->game.map.area[i] = (MQDATA_GAME_MAP_AREA){.name = " ",.hitboxIndex=MQTrue,.cameraPosition={0,0,0}};
    }
}

//-----------------------------------
//COLISION
//-----------------------------------

Vector3 MQ3DMove(Vector3 position, float rotation, float speed)
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

bool MQCheckCollisionPoint(Vector3 inPosi,BoundingBox target, float size)
{
    BoundingBox localhitbox;
    localhitbox.min = (Vector3) {inPosi.x - (size/2), inPosi.y - (size/2), inPosi.z - (size/2)};
    localhitbox.max = (Vector3) {inPosi.x + (size/2), inPosi.y + (size/2), inPosi.z + (size/2)};
    return(CheckCollisionBoxes(target, localhitbox));
}

bool* MQReturnCollisionCube(BoundingBox input, BoundingBox target)
{
    //imagine a cube
    
    //facemin
    //2  3  4
    //1  0  5
    //8  7  6

    //facemeio
    //11 12 13
    //10 9  14
    //17 16 15

    //facemax
    //20 21 22
    //19 18 23
    //26 25 24

    return ((bool[])
    {
        MQCheckCollisionPoint((Vector3) {input.max.x/2, input.max.y/2, input.min.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x, input.max.y/2, input.min.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x, input.max.y, input.min.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x/2, input.max.y, input.min.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.min.x, input.max.y, input.min.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.min.x, input.max.y/2, input.min.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.min.x, input.min.y, input.min.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x/2, input.min.y, input.min.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x, input.min.y, input.min.z}, target, 0.02),
        
        MQCheckCollisionPoint((Vector3) {input.max.x/2, input.max.y/2, input.max.z/2}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x, input.max.y/2, input.max.z/2}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x, input.max.y, input.max.z/2}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x/2, input.max.y, input.max.z/2}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.min.x, input.max.y, input.max.z/2}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.min.x, input.max.y/2, input.max.z/2}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.min.x, input.min.y, input.max.z/2}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x/2, input.min.y, input.max.z/2}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x, input.min.y, input.max.z/2}, target, 0.02),
        
        MQCheckCollisionPoint((Vector3) {input.max.x/2, input.max.y/2, input.max.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x, input.max.y/2, input.max.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x, input.max.y, input.max.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x/2, input.max.y, input.max.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.min.x, input.max.y, input.max.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.min.x, input.max.y/2, input.max.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.min.x, input.min.y, input.max.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x/2, input.min.y, input.max.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x, input.min.y, input.max.z}, target, 0.02)
    });
}

void MQRotateHorizontalRay(MQDATA *data,int rayIndex, float rotation, Vector3 position,bool backwards)
{
    //z+ frente
    //x+ esquerda
    float valorZ;
    float valorX;
    if(rotation<=90.0)
    {
        if(backwards)
        {
            valorZ = -1.0+((1.0/90.0)*rotation);
            valorX = 0.0-(1.0/90.0)*rotation;
        }
        else
        {
            valorZ = 1.0-((1.0/90.0)*rotation);
            valorX = 0.0+(1.0/90.0)*rotation;
        }
    }
    else if(rotation<=180)
    {
        
        if(backwards)
        {
            valorZ = 0.0+((1.0/90.0)*(rotation-90.0));
            valorX = -1.0+((1.0/90.0)*(rotation-90.0));
        }
        else
        {
            valorZ = 0.0-((1.0/90.0)*(rotation-90.0));
            valorX = 1.0-((1.0/90.0)*(rotation-90.0));
        }
    }
    else if(rotation<=270)
    {
        if(backwards)
        {
            valorZ = 1.0-((1.0/90.0)*(rotation-180.0));
            valorX = 0.0+((1.0/90.0)*(rotation-180.0));
        }
        else
        {
            valorZ = -1.0+((1.0/90.0)*(rotation-180.0));
            valorX = 0.0-((1.0/90.0)*(rotation-180.0));
        }
    }
    else 
    {
        if(backwards)
        {
            valorZ = 0.0-((1.0/90.0)*(rotation-270.0));
            valorX = 1.0-((1.0/90.0)*(rotation-270.0));
        }
        else
        {
            valorZ = 0.0+((1.0/90.0)*(rotation-270.0));
            valorX = -1.0+((1.0/90.0)*(rotation-270.0));
        }
    }
    data->files.rays[rayIndex].ray.position = (Vector3){position.x,position.y+1,position.z};
    data->files.rays[rayIndex].ray.direction = (Vector3){valorX,0,valorZ};
}

void MQUpdateGravityRay(MQDATA *data,int rayIndex, int time, Vector3 position)
{
    data->files.rays[rayIndex].ray.position = (Vector3){position.x,position.y-(0.005*(time)),position.z};
    data->files.rays[rayIndex].ray.direction = (Vector3){0,1,0};
}

float MQGravity(Vector3 position, float gravidade, int tempo)
{
    return(position.y - gravidade*((tempo*(tempo/5)))/60);
}

void MQGravit(MQDATA* data, int quem)
{
    int headIndex = MQTrue;
    RayCollision gravityraiocolisao;
    char *buffer= malloc(32);
    snprintf(buffer,32,"player-cabeca%d",quem);
    headIndex = MQFindHitbox(data->files.hitboxes, buffer);

    snprintf(buffer,32,"playergravityray%d",quem);
    int gravityrayindex = MQFindRay(*data,buffer);
    snprintf(buffer,32,"lvl%d_area",data->game.map.currentLevel);
    MQUpdateGravityRay(*&data,gravityrayindex,data->game.player[quem].fallTime+1,data->game.player[quem].position);
    for(short i=0;i<MAXOBJ;i++)
    {
        if(strncmp(data->files.hitboxes[i].name,buffer,9)!=0&&strcmp(data->files.hitboxes[i].name," ")!=0)
            if(i<headIndex||i>headIndex+14)
            {
                gravityraiocolisao = GetRayCollisionBox(data->files.rays[gravityrayindex].ray,data->files.hitboxes[i].hitbox);
                if(gravityraiocolisao.hit == true)
                    break;
                gravityraiocolisao.hit = false;
            }
    }
    free(buffer);
    if(gravityraiocolisao.hit == false)
    {
        data->game.player[quem].position.y = MQGravity(data->game.player[quem].position, 0.1, data->game.player[quem].fallTime);
        data->game.player[quem].fallTime++;
    }
    else
    {
        if(gravityraiocolisao.distance<0.7)
        {   
            data->game.player[quem].position.y = gravityraiocolisao.point.y;
            data->game.player[quem].fallTime = 0;
        }
    }
}

//-----------------------------------
//PLAYER
//-----------------------------------

#include "player.c"

bool MQPlayerCollider(MQDATA*data, int quem, bool backwards)
{
    char *buffer= malloc(32);
    int headIndex;
    snprintf(buffer,32,"player-cabeca%d",quem);
    MQFindHitbox(data->files.hitboxes, buffer);

    RayCollision directionraiocolisao;
    int directionrayindex;
    snprintf(buffer,32,"playerdirectionray%d",quem);
    directionrayindex = MQFindRay(*data,buffer);
    MQRotateHorizontalRay(*&data,directionrayindex,data->game.player[quem].rotation,data->game.player[quem].position,backwards);
    
    snprintf(buffer,32,"lvl%d_area",data->game.map.currentLevel);
    for(short i=0;i<MAXOBJ;i++)
        if(strncmp(data->files.hitboxes[i].name,buffer,9)!=0&&strcmp(data->files.hitboxes[i].name," ")!=0)
            if(i<headIndex||i>headIndex+14)
            {
                directionraiocolisao = GetRayCollisionBox(data->files.rays[directionrayindex].ray,data->files.hitboxes[i].hitbox);
                if(directionraiocolisao.hit == true)
                    break;
                directionraiocolisao.hit = false;
            }
    
    if(directionraiocolisao.hit == true)
    {
        if(directionraiocolisao.distance<0.5)
        {
            free(buffer);
            return true;
        }
        else
        {
            BoundingBox caixa = (BoundingBox){.max = data->game.player[quem].position,.min = data->game.player[quem].position};
            caixa.max.x += 0.2;
            caixa.max.y += 1.2;
            caixa.max.z += 0.2;
            caixa.min.x += -0.2;
            caixa.min.y += 0.8;
            caixa.min.z += -0.2;
            if(backwards)
            {
                caixa.max = MQ3DMove(caixa.max,data->game.player[quem].rotation,-0.1);
                caixa.min = MQ3DMove(caixa.min,data->game.player[quem].rotation,-0.1);
            }
            else
            {
                caixa.max = MQ3DMove(caixa.max,data->game.player[quem].rotation,0.1);
                caixa.min = MQ3DMove(caixa.min,data->game.player[quem].rotation,0.1);
            }
            data->files.hitboxes[MAXOBJ-2].hitbox = caixa;
            for(int i = 0;i<MAXOBJ;i++)
                if(i<headIndex||i>headIndex+14)
                    if(strcmp(data->files.hitboxes[i].name," ")!=0)
                        if(CheckCollisionBoxes(caixa,data->files.hitboxes[i].hitbox)==true)
                        {
                            snprintf(buffer,32,"lvl%d_area",data->game.map.currentLevel);
                            if(strncmp(data->files.hitboxes[i].name,buffer,9)!=0)
                            {
                                free(buffer);
                                return true;
                            }
                                
                        }
        }
    }
    free(buffer);
    return false;
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
//MENU
//-----------------------------------

#include "menu.c"

//-----------------------------------
//KEYBOARD
//-----------------------------------

void TECLADO_MAIN(MQDATA *data)
{
    if(IsKeyPressed(KEY_ESCAPE))
    {
        MQMenu(*&data, 1);
    }
    if(IsKeyPressed(KEY_E) || IsKeyPressed(KEY_E))
    {
        MQPlayerPickupItem(*&data,0);
    } 
    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        MQPlayerCollider(*&data,0,false);
        if(data->game.player[0].rotation == 0)
            data->game.player[0].rotation = 360;
        data->game.player[0].rotation -= 6;
    }
    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        MQPlayerCollider(*&data,0,false);
        if(data->game.player[0].rotation == 360)
            data->game.player[0].rotation = 0;
        data->game.player[0].rotation += 6;
    }
    if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        data->session.render.model[MQFindRenderModel(*data,"player0")].reverse = true;
        data->session.render.model[MQFindRenderModel(*data,"player0")].currentAnim = 1;
    }
    if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
    {
        if(MQPlayerCollider(*&data,0,true)==false)
            data->game.player[0].position = MQ3DMove(data->game.player[0].position, data->game.player[0].rotation, (data->game.player[0].speed) * (-1));
    }
    if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        data->session.render.model[MQFindRenderModel(*data,"player0")].currentAnim = 1;
    }
    if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
    {
        if(MQPlayerCollider(*&data,0,false)==false)
            data->game.player[0].position = MQ3DMove(data->game.player[0].position, data->game.player[0].rotation, data->game.player[0].speed);
    }
    if(IsKeyDown(KEY_LEFT_SHIFT))
    {
        data->game.player[0].speed = 0.2f;
    }
    if(IsKeyReleased(KEY_LEFT_SHIFT))
    {
        data->game.player[0].speed = 0.1f;
    }
    if(IsKeyReleased(KEY_UP) || IsKeyReleased(KEY_W))
    {
        data->session.render.model[MQFindRenderModel(*data,"player0")].currentAnim = 0;
    }
    if(IsKeyReleased(KEY_DOWN) || IsKeyReleased(KEY_S))
    {
        data->session.render.model[MQFindRenderModel(*data,"player0")].reverse = false;
        data->session.render.model[MQFindRenderModel(*data,"player0")].currentAnim = 0;
    }
    if(IsKeyDown(KEY_SPACE))
    {
        data->game.player[0].position.y +=0.14;
    }
    if(IsKeyPressed(KEY_L))
    {
        //abinDEBUGcreate("hitboxes.txt");
        for(int i =0;i<MAXOBJ;i++)
        {
            if(strcmp(data->files.hitboxes[i].name," ")==0)
                break;
            else
            {
                //abinDEBUGtext("debug.txt",data->files.models[i].name);
                abinDEBUGtext("debug.txt",data->files.hitboxes[i].name);
            }
                
        }
        /* abinDEBUGcreate("hitboxes.txt");
        for(int i =0;i<MAXOBJ;i++)
        {
            if(strcmp(data->files.hitboxes[i].name," ")==0)
                break;
            else
                abinDEBUGtext("hitboxes.txt",data->files.hitboxes[i].name);
        } */
    }
}

//-----------------------------------
//WINDOW&ECOSYSTEM
//-----------------------------------

void MQStart(MQDATA *data)
{
    data->session.resizebleWindow = true;
    if(data->session.resizebleWindow == true)
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitAudioDevice();
    InitWindow(MQScreenX, MQScreenY, MQTitle);
    SetTargetFPS(60);
    SetExitKey(KEY_END);
    //cleaning scripts
    MQCleanAllFileSlots(*&data);
    MQCleanAllItemSlots(*&data);
    MQCleanAllRenderSlots(*&data);
    MQCleanAllEventSlots(*&data);
    MQCleanAllAreaSlots(*&data);
    //load.c
    MQLoadAll(*&data);
    //SESSION_RENDER
    data->session.render.upscale = 1;
    data->session.render.rendertexture = LoadRenderTexture(MQScreenX/data->session.render.upscale, MQScreenY/data->session.render.upscale);
    data->session.render.camera = MQCameraStart(&data->session.render.camera);
    data->session.render.background = (Color){115, 105, 97, 255};
    
    data->session.frame = 0;
    //FONTS
    data->files.fonts[0].font= MQFontStart("data/font/acentos/KyrillaSansSerif-Bold.ttf", 16);
    data->files.fonts[1].font= MQFontStart("data/font/Mockery.ttf", 48);
    data->files.fonts[2].font= MQFontStart("data/font/Mockery.ttf", 24);
    //MUSIC
    data->files.musics[0].music = LoadMusicStream("data/audio/music/maintheme_by_kayoa.mp3");

    //CURRENT_LEVEL
    data->game.map.currentLevel = 0;
}