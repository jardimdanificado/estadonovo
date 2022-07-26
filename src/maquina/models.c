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

void MQCreateHitbox(MQDATA *data, char *name, BoundingBox Hitbox)
{
    int LocalIndex;
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data->files.hitboxes[i].name," ")==0)
        {
            LocalIndex = i;
            break;
        }
    }
    data->files.hitboxes[LocalIndex].hitbox = Hitbox;
    strcpy(data->files.hitboxes[LocalIndex].name,name);
    LocalIndex++;
}

void MQCreateEmptyHitbox(MQDATA *data, char *name)
{
    int LocalIndex;
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(strcmp(data->files.hitboxes[i].name," ")==0)
        {
            LocalIndex = i;
            break;
        }
    }
    strcpy(data->files.hitboxes[LocalIndex].name,name);
    LocalIndex++;
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
        MQCreateHitbox(*&data,name,GetModelBoundingBox(data->files.models[LocalIndex].model));
    }
}

void MQPlayerCreateBodyBox(MQDATA *data, int quem)
{
    char buffer[128],buffer0[128];
    for(int i = 0; i < 14; i++)
    {
        snprintf(buffer,266,"%s%d",data->files.models[i].name,quem);
        snprintf(buffer0,255,"%s",data->files.models[i].name);
        MQCreateHitbox(*&data, buffer, GetModelBoundingBox(data->files.models[MQFindModelByName(*data,buffer0)].model));
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
    hitboxheadfind = MQFindHitbox(*data,buffer);
    modelheadfind = MQFindModelByName(*data,"player-cabeca");
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

