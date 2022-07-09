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

void MQPlayerUpdateBodyBox(DATA *data, int quem, int qualAnim)
{
    Mesh LocalMesh;
    Vector3 LocVec3;
    int modelIndex, hitboxIndex;
    char buffer[128];
    snprintf(buffer,128,"player-cabeca%d",quem);
    int hitboxheadfind,modelheadfind; 
    hitboxheadfind = MQFindHitboxByName(*data,buffer);
    snprintf(ABINCACHE16,16,"hitbox%d",hitboxheadfind);
    modelheadfind = MQFindModelByName(*data,"player-cabeca");
    snprintf(ABINCACHE16,16,"model%d",modelheadfind);
    for(int i = 0; i < 14; i++)
    {
        modelIndex =  modelheadfind+i;
        hitboxIndex = hitboxheadfind+i;
        snprintf(buffer,128,"player%d",quem);
        snprintf(ABINCACHE16,16,"hitbox%d",hitboxheadfind);
        snprintf(ABINCACHE16,16,"model%d",modelheadfind);
        LocalMesh = MQApplyMeshTransformFromBone(data->file.model[modelIndex], data->file.anim[modelIndex][qualAnim], data->queue.render.model[MQFindRenderModelIndexByName(*data,buffer)].currentFrame);
        

        for(int i = 0; i < LocalMesh.vertexCount * 3; i += 3)
        {
            LocVec3 = MQRotateVerticeSelf(270 - ((PI / 180) * (data->game.personagem[quem].rotacao)), (Vector3) {LocalMesh.vertices[i], LocalMesh.vertices[i + 1], LocalMesh.vertices[i + 2]});

            LocalMesh.vertices[i] = LocVec3.x;
            LocalMesh.vertices[i + 1] = LocVec3.y;
            LocalMesh.vertices[i + 2] = LocVec3.z;
        }
        data->file.hitbox[hitboxIndex] = GetMeshBoundingBox(LocalMesh);

        data->file.hitbox[hitboxIndex].min = Vector3Add(data->file.hitbox[hitboxIndex].min, (Vector3) {0.06, 0.06, 0.06});
        data->file.hitbox[hitboxIndex].max = Vector3Subtract(data->file.hitbox[hitboxIndex].max, (Vector3) {0.06, 0.06, 0.06});

        data->file.hitbox[hitboxIndex].min = Vector3Add(data->file.hitbox[hitboxIndex].min, data->game.personagem[quem].posicao);
        data->file.hitbox[hitboxIndex].max = Vector3Add(data->file.hitbox[hitboxIndex].max, data->game.personagem[quem].posicao);
    }
}

void MQLoadAllModels(DATA *data)
{
    MQLoadModelsFromText( *&data, "./data/models/player.text");
    MQLoadModelsFromText( *&data, "./data/models/playerhitbox.text");
    MQLoadModelsFromText( *&data, "./data/models/porta.text");
    MQLoadModelsFromText( *&data, "./data/models/map/level0/lvl0.text");
    MQLoadHitboxFromText( *&data, "./data/models/map/level0/hitbox.text");
    MQPlayerCreateBodyBox( *&data, 0);
}
