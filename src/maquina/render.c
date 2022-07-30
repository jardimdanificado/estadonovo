MQDATA_RENDER_MODEL MQCreateRenderModel(bool visible, bool playing, bool reverse,int modelIndex,int anim,int frame,Color color,Vector3 position,float rotation,char*name)
{
    return((MQDATA_RENDER_MODEL){visible,playing,reverse,modelIndex,anim,frame,color,position,rotation,name});
}

MQDATA_RENDER_TEXT MQCreateRenderText(char* name, int textIndex, Color color, Vector2 position, int fontIndex, int fontSize, char* string, bool visible)
{
    return((MQDATA_RENDER_TEXT){visible,textIndex,position,color,string,fontSize,fontIndex,name});
}

void MQCleanAllRenderSlots(MQDATA *data)
{
    for(int i = 0;i<MAXOBJ;i++)
    { 
        data->session.render.model[i] = MQEmptyRenderModel;
        data->session.render.text[i] = MQEmptyRenderText;
    }
}

void MQCleanAllRenderModelSlots(MQDATA *data)
{
    for(int i = 0;i<MAXOBJ;i++)
    { 
        data->session.render.model[i] = MQEmptyRenderModel;
    }
}

void MQCleanAllRenderTextSlots(MQDATA *data)
{
    for(int i = 0;i<MAXOBJ;i++)
    {
        data->session.render.text[i] = MQEmptyRenderText;
    }
}

void MQAddRenderModelToQueue(MQDATA *data, MQDATA_RENDER_MODEL rendermodel)
{
    int emptyslot;
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(data->session.render.model[i].modelIndex == MQTrue)
        {
            emptyslot = i;
            break;
        }
    }
    data->session.render.model[emptyslot] = rendermodel;
}

void MQAddRenderTextToQueue(MQDATA *data,MQDATA_RENDER_TEXT rendertext)
{
    int emptyslot;
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(data->session.render.text[i].textIndex == MQTrue)
        {
            emptyslot = i;
            break;
        }
    }
    data->session.render.text[emptyslot] = rendertext;
}

void MQRenderQueue(MQDATA* data)
{
    BeginTextureMode(data->session.render.rendertexture);
    BeginDrawing();
    ClearBackground(data->session.render.background);
    BeginMode3D(data->session.render.camera);
    for(int i=0;i<MAXOBJ;i++)
    {
        DrawBoundingBox(data->files.hitboxes[i].hitbox,BLACK);
        DrawBoundingBox(MQHitboxUpdateXYZ(data->game.event[i].hitbox, data->game.event[i].position),GREEN);
        DrawBoundingBox(MQHitboxUpdateXYZ(data->game.map.item[i].hitbox, data->game.map.item[i].position),RED);
        if(data->session.render.model[i].modelIndex != MQTrue)
        {
            if(data->session.render.model[i].playing == true)
            {
                if(data->session.render.model[i].reverse == false)
                    if(data->session.render.model[i].currentFrame < data->files.models[data->session.render.model[i].modelIndex].anim[data->session.render.model[i].currentAnim].frameCount)
                        data->session.render.model[i].currentFrame++;
                    else
                        data->session.render.model[i].currentFrame = 0;
                else
                    if(data->session.render.model[i].currentFrame > 0)
                        data->session.render.model[i].currentFrame--;
                    else
                        data->session.render.model[i].currentFrame = data->files.models[data->session.render.model[i].modelIndex].anim[data->session.render.model[i].currentAnim].frameCount;
                UpdateModelAnimation(data->files.models[data->session.render.model[i].modelIndex].model, data->files.models[data->session.render.model[i].modelIndex].anim[data->session.render.model[i].currentAnim], data->session.render.model[i].currentFrame);
            }
            DrawModelEx(data->files.models[data->session.render.model[i].modelIndex].model, data->session.render.model[i].position, (Vector3){0.0f, 1.0f, 0.0f}, data->session.render.model[i].rotation , (Vector3){1.0f, 1.0f, 1.0f}, data->session.render.model[i].color);
        }
        if(data->session.render.text[i].textIndex != MQTrue)
        {
            DrawTextEx(data->files.fonts[data->session.render.text[i].fontIndex].font, data->session.render.text[i].string,data->session.render.text[i].position , data->session.render.text[i].fontSize, 0, data->session.render.text[i].color);
        }
    }
    EndMode3D();
    EndDrawing();
    EndTextureMode();
    DrawTexturePro(data->session.render.rendertexture.texture,(Rectangle){.x = 0, .y=0, .width = MQScreenX/data->session.render.upscale, .height = (MQScreenY/data->session.render.upscale)*-1},(Rectangle){.x = 0, .y=0, .width = MQScreenX, .height = MQScreenY},(Vector2){0,0},0,WHITE);
}

