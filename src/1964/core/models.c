// Update model animated vertex data (positions and normals) for a given frame
// NOTE: Updated data is uploaded to GPU
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
//                 TRACELOG(LOG_WARNING, "MODEL: UpdateModelAnimation Mesh %i has no connection to bones",m);
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
                    //int boneIdParent = model.bones[boneId].parent;
                    inTranslation = model.bindPose[boneId].translation;
                    inRotation = model.bindPose[boneId].rotation;
                    // inScale = model.bindPose[boneId].scale;
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
//                     animVertex = Vector3Transform(animVertex, model.transform);
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

            // Upload new vertex data to GPU for model drawing
            // Only update data when values changed.
            if(updated)
            {
                mesh.vertices = mesh.animVertices;
                return(mesh);
            }
        }
    }
}

void MQSetTempSpecsTypes2(char *type0, char *type1)
{
    strcpy(ABINCACHE32, "./data/temp/dummyt.specs");
    remove(ABINCACHE32);
    abinCoreFileCreate(ABINCACHE32);
    abinCoreAddNewData(ABINCACHE32, "type0", type0);
    abinCoreAddNewData(ABINCACHE32, "type1", type1);
}

void MQSetTempSpecsValues2(char *value0, char *value1)
{
    strcpy(ABINCACHE32, "./data/temp/dummyv.specs");
    remove(ABINCACHE32);
    abinCoreFileCreate(ABINCACHE32);
    abinCoreAddNewData(ABINCACHE32, "value0", value0);
    abinCoreAddNewData(ABINCACHE32, "value1", value1);
}

void MQSetTempSpecsToFile2(char *fileloc)
{
    char bufferlocal[2][64];
    char buffervalues[2][128];
    char buffertypes[2][128];
    strcpy(bufferlocal[0], "./data/temp/dummyv.specs");
    strcpy(bufferlocal[1], "./data/temp/dummyt.specs");
    strcpy(buffervalues[0], abinCoreReturnData(bufferlocal[0], "value0"));
    strcpy(buffervalues[1], abinCoreReturnData(bufferlocal[0], "value1"));
    strcpy(buffertypes[0], abinCoreReturnData(bufferlocal[1], "type0"));
    strcpy(buffertypes[1], abinCoreReturnData(bufferlocal[1], "type1"));
    for(int i = 0; i < 2; i++)
    {
        abinCoreAddNewData(fileloc, buffertypes[i], buffervalues[i]);
    }
    snprintf(ABINCACHE16, 16, "%d", atoi(abinCoreReturnData(fileloc, "SIZE")));
    abinCoreEditData(fileloc, "SIZE", ABINCACHE16);
}

void MQSetTempSpecsTypes4(char *type0, char *type1, char *type2, char *type3)
{
    strcpy(ABINCACHE32, "./data/temp/dummyt.specs");
    remove(ABINCACHE32);
    abinCoreFileCreate(ABINCACHE32);
    abinCoreAddNewData(ABINCACHE32, "type0", type0);
    abinCoreAddNewData(ABINCACHE32, "type1", type1);
    abinCoreAddNewData(ABINCACHE32, "type2", type2);
    abinCoreAddNewData(ABINCACHE32, "type3", type3);
}

void MQSetTempSpecsValues4(char *value0, char *value1, char *value2, char *value3)
{
    strcpy(ABINCACHE32, "./data/temp/dummyv.specs");
    remove(ABINCACHE32);
    abinCoreFileCreate(ABINCACHE32);
    abinCoreAddNewData(ABINCACHE32, "value0", value0);
    abinCoreAddNewData(ABINCACHE32, "value1", value1);
    abinCoreAddNewData(ABINCACHE32, "value2", value2);
    abinCoreAddNewData(ABINCACHE32, "value3", value3);
}

void MQSetTempSpecsToFile4(char *fileloc)
{
    char bufferlocal[4][64];
    char buffervalues[4][128];
    char buffertypes[4][128];
    strcpy(bufferlocal[0], "./data/temp/dummyv.specs");
    strcpy(bufferlocal[1], "./data/temp/dummyt.specs");
    strcpy(bufferlocal[2], "vazio");
    strcpy(bufferlocal[3], "vazio");
    strcpy(buffervalues[0], abinCoreReturnData(bufferlocal[0], "value0"));
    strcpy(buffervalues[1], abinCoreReturnData(bufferlocal[0], "value1"));
    strcpy(buffervalues[2], abinCoreReturnData(bufferlocal[0], "value2"));
    strcpy(buffervalues[3], abinCoreReturnData(bufferlocal[0], "value3"));
    strcpy(buffertypes[0], abinCoreReturnData(bufferlocal[1], "type0"));
    strcpy(buffertypes[1], abinCoreReturnData(bufferlocal[1], "type1"));
    strcpy(buffertypes[2], abinCoreReturnData(bufferlocal[1], "type2"));
    strcpy(buffertypes[3], abinCoreReturnData(bufferlocal[1], "type3"));
    for(int i = 0; i < 4; i++)
    {
        abinCoreAddNewData(fileloc, buffertypes[i], buffervalues[i]);
    }
    snprintf(ABINCACHE16, 16, "%d", atoi(abinCoreReturnData(fileloc, "SIZE")));
    abinCoreEditData(fileloc, "SIZE", ABINCACHE16);
}

void MQLoadModel(DATA *data, char *loadedfrom, int ponteiro)
{
    char bufferlocal[3][128], bufferresult[6][128];
    snprintf(bufferlocal[0], 128, "name%d", ponteiro);
    snprintf(bufferlocal[1], 128, "animated%d", ponteiro);
    bool animated;
    snprintf(bufferresult[0], 128, "%s", abinCoreReturnData(loadedfrom, bufferlocal[0]));
    if(strcmp(abinCoreReturnData(loadedfrom, bufferlocal[1]), "true") == 0)
        animated = true;
    snprintf(bufferresult[1], 128, "%s", abinCoreReturnData(loadedfrom, bufferlocal[1]));

    if(animated == true)
        snprintf(bufferresult[2], 128, "%d", data->session.AnimCount);
    else
        snprintf(bufferresult[2], 128, "vazio");

    snprintf(ABINCACHE4, 4, "%d", data->session.ObjCount);
    snprintf(bufferlocal[0], 128, "name%s", ABINCACHE4);
    snprintf(bufferlocal[1], 128, "animated%s", ABINCACHE4);
    snprintf(bufferlocal[2], 128, "anim%s", ABINCACHE4);

    MQSetTempSpecsTypes4(bufferlocal[0], bufferlocal[1], bufferlocal[2], bufferresult[0]);
    MQSetTempSpecsValues4(bufferresult[0], bufferresult[1], bufferresult[2], ABINCACHE4);
    MQSetTempSpecsToFile4("./data/temp/model.temp");
    snprintf(bufferlocal[0], 8, "link%d", ponteiro);
    abinCoreAddNewData("./data/temp/model.temp", bufferlocal[0], abinCoreReturnData(loadedfrom, bufferlocal[0]));
    data->file.model[data->session.ObjCount] = LoadModel(abinCoreReturnData(loadedfrom, bufferlocal[0]));
    data->session.ObjCount++;
    if(animated == true)
    {
        data->file.anim[data->session.AnimCount] = LoadModelAnimations(abinCoreReturnData(loadedfrom, bufferlocal[0]), &MAXANIM);
        data->session.AnimCount++;
    }
}

void MQLoadModelsFromText(DATA *data, char *fileloc)
{
    for(int i = 0; i < atoi(abinCoreReturnData(fileloc, "SIZE")); i++)
    {
        MQLoadModel( *&data, fileloc, i);
        snprintf(ABINCACHE4, 4, "%d", data->session.ObjCount);
        abinCoreEditData("./data/temp/model.temp", "SIZE", ABINCACHE4);
        snprintf(ABINCACHE16, 16, "anim=%d", data->session.AnimCount);
    }
}

void MQLoadHitbox(DATA *data, char *fileloc, int ponteiro)
{
    snprintf(ABINCACHE32, 32, "link%d", ponteiro);
    snprintf(ABINCACHE128, 128, "%s", abinCoreReturnData(fileloc, ABINCACHE32));
    Model localModel = LoadModel(ABINCACHE128);
    char bufferresult[2][128];
    snprintf(ABINCACHE16, 16, "%d", data->session.HitboxCount);
    snprintf(ABINCACHE32, 32, "name%s", ABINCACHE16);
    snprintf(bufferresult[0], 128, "%s", abinCoreReturnData(fileloc, ABINCACHE32));
    data->file.hitbox[data->session.HitboxCount] = GetModelBoundingBox(localModel);
    snprintf(bufferresult[1], 128, "name%d", ponteiro);
    MQSetTempSpecsTypes2(bufferresult[1], bufferresult[0]);
    MQSetTempSpecsValues2(bufferresult[0], ABINCACHE16);
    MQSetTempSpecsToFile2("./data/temp/hitbox.temp");
    UnloadModel(localModel);
}

void MQLoadHitboxFromText(DATA *data, char *fileloc)
{
    for(int i = 0; i < atoi(abinCoreReturnData(fileloc, "SIZE")); i++)
    {
        MQLoadHitbox( *&data, fileloc, i);
        data->session.HitboxCount++;
        snprintf(ABINCACHE4, 4, "%d", data->session.HitboxCount);
        abinCoreEditData("./data/temp/hitbox.temp", "SIZE", ABINCACHE4);
    }
}

void MQPlayerUpdateBodyBox(DATA *data, int quem, int qualAnim)
{
    Mesh LocalMesh;
    Vector3 LocVec3;
    int modelIndex, animIndex, hitboxIndex;
    if(quem >= 0)
    {
        for(int i = 0; i < 14; i++)
        {
            snprintf(ABINCACHE8, 8, "name%d", i);
            strcpy(ABINCACHE128, abinCoreReturnData("./data/models/playerhitbox.text", ABINCACHE8));
            snprintf(ABINCACHE32, 32, "anim%s", abinCoreReturnData("./data/temp/model.temp", ABINCACHE128));
            modelIndex =  atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE128));
            animIndex = atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE32));
            hitboxIndex = atoi(abinCoreReturnData("./data/temp/hitbox.temp", ABINCACHE128));

            UpdateModelAnimation(data->file.model[modelIndex], data->file.anim[animIndex][qualAnim], data->game.contador.frames.personagem[quem]);

            LocalMesh = MQApplyMeshTransformFromBone(data->file.model[modelIndex], data->file.anim[animIndex][qualAnim], data->game.contador.frames.personagem[quem]);

            for(int i = 0; i < LocalMesh.vertexCount * 3; i += 3)
            {
                LocVec3 = MQRotateVerticeSelf(270 - ((PI / 180) * (data->game.rotacao.personagem[quem])), (Vector3) {LocalMesh.vertices[i], LocalMesh.vertices[i + 1], LocalMesh.vertices[i + 2]});

                LocalMesh.vertices[i] = LocVec3.x;
                LocalMesh.vertices[i + 1] = LocVec3.y;
                LocalMesh.vertices[i + 2] = LocVec3.z;
            }
            data->file.hitbox[hitboxIndex] = GetMeshBoundingBox(LocalMesh);

            data->file.hitbox[hitboxIndex].min = Vector3Add(data->file.hitbox[hitboxIndex].min, (Vector3) {0.06, 0.06, 0.06});
            data->file.hitbox[hitboxIndex].max = Vector3Subtract(data->file.hitbox[hitboxIndex].max, (Vector3) {0.06, 0.06, 0.06});

            data->file.hitbox[hitboxIndex].min = Vector3Add(data->file.hitbox[hitboxIndex].min, data->game.posicao.personagem[quem]);
            data->file.hitbox[hitboxIndex].max = Vector3Add(data->file.hitbox[hitboxIndex].max, data->game.posicao.personagem[quem]);
        }
    }
    else
    {
        for(int i = 0; i < 14; i++)
        {
            snprintf(ABINCACHE8, 8, "name%d", i);
            strcpy(ABINCACHE128, abinCoreReturnData("./data/models/playerhitbox.text", ABINCACHE8));

            data->file.hitbox[data->session.HitboxCount] = GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE128))]);

            snprintf(ABINCACHE16, 16, "name%d", data->session.HitboxCount);
            MQSetTempSpecsTypes2(ABINCACHE16, ABINCACHE128);

            snprintf(ABINCACHE4, 4, "%d", data->session.HitboxCount);
            MQSetTempSpecsValues2(ABINCACHE128, ABINCACHE4);

            MQSetTempSpecsToFile2("./data/temp/hitbox.temp");

            data->session.HitboxCount++;
            snprintf(ABINCACHE4, 4, "%d", data->session.HitboxCount);
            abinCoreEditData("./data/temp/hitbox.temp", "SIZE", ABINCACHE4);
        }
    }
}

void MQLoadAllModels(DATA *data)
{
    remove("./data/temp/model.temp");
    abinCoreFileCreate("./data/temp/model.temp");
    MQLoadModelsFromText( *&data, "./data/models/player.text");
    MQLoadModelsFromText( *&data, "./data/models/playerhitbox.text");
    MQLoadModelsFromText( *&data, "./data/models/porta.text");
    MQLoadModelsFromText( *&data, "./data/models/map/level0/lvl0.text");
    remove("./data/temp/hitbox.temp");
    abinCoreFileCreate("./data/temp/hitbox.temp");
    MQLoadHitboxFromText( *&data, "./data/models/map/level0/hitbox.text");
    MQPlayerUpdateBodyBox( *&data, -1, 0);
}
