MQDATA_RENDER_MODEL MQCreateRenderModel(bool visible, bool playing, bool reverse,int modelIndex,int anim,int frame,Color color,Vector3 position,float rotation,char*name)
{
    return((MQDATA_RENDER_MODEL){visible,playing,reverse,modelIndex,MQTrue,MQTrue,PINK,MQCreateEmptyVec3(),MQTrue," "});
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

void MQRenderAddModelToQueue(MQDATA *data, char* name, int modelIndex, Color color, Vector3 position, float rotation, int currentAnim, int currentFrame, bool visible, bool playing, bool reverse)
{
    int LocalIndex;
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(data->session.render.model[i].modelIndex == MQTrue)
        {
            LocalIndex = i;
            break;
        }
    }
    data->session.render.model[LocalIndex].name = name;
    data->session.render.model[LocalIndex].currentAnim = currentAnim;
    data->session.render.model[LocalIndex].currentFrame = currentFrame;
    data->session.render.model[LocalIndex].color.r = color.r;
    data->session.render.model[LocalIndex].color.g = color.g;
    data->session.render.model[LocalIndex].color.b = color.b;
    data->session.render.model[LocalIndex].color.a = color.a;
    data->session.render.model[LocalIndex].modelIndex = modelIndex;
    data->session.render.model[LocalIndex].position = position;
    data->session.render.model[LocalIndex].rotation = rotation;
    data->session.render.model[LocalIndex].visible = visible;
    data->session.render.model[LocalIndex].playing = playing;
    data->session.render.model[LocalIndex].reverse = reverse;
}

void MQRenderAddTextToQueue(MQDATA *data,char* name, int textIndex, Color color, Vector2 position, int fontIndex, int fontSize, char* string, bool visible)
{
    int LocalIndex;
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(data->session.render.text[i].textIndex == MQTrue)
        {
            LocalIndex = i;
            break;
        }
    }
    data->session.render.text[LocalIndex].name = name;
    data->session.render.text[LocalIndex].color.r = color.r;
    data->session.render.text[LocalIndex].color.g = color.g;
    data->session.render.text[LocalIndex].color.b = color.b;
    data->session.render.text[LocalIndex].color.a = color.a;
    data->session.render.text[LocalIndex].textIndex = textIndex;
    data->session.render.text[LocalIndex].position = position;
    data->session.render.text[LocalIndex].visible = visible;
    data->session.render.text[LocalIndex].fontSize = fontSize;
    data->session.render.text[LocalIndex].fontIndex = fontIndex;
    data->session.render.text[LocalIndex].string = string;
}

void MQRenderQueue(MQDATA* data)
{
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
}

