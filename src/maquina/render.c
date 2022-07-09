void MQCleanAllRenderSlots(DATA *data)
{
    for(int i = 0;i<MAXOBJ;i++)
    { 
        data->queue.render.model[i].color.r = 0;
        data->queue.render.model[i].color.g = 0;
        data->queue.render.model[i].color.b = 0;
        data->queue.render.model[i].color.a = 0;
        data->queue.render.model[i].modelIndex = __INT_MAX__;
        data->queue.render.model[i].position = (Vector3){ __INT_MAX__,__INT_MAX__,__INT_MAX__ };
        data->queue.render.model[i].rotation = __INT_MAX__;
        data->queue.render.model[i].visible = false;
        data->queue.render.model[i].playing = false;
        data->queue.render.model[i].reverse = false;
        data->queue.render.model[i].name = " ";
        data->queue.render.model[i].currentAnim = 0;
        data->queue.render.model[i].currentFrame = 0;
        data->queue.render.text[i].color.r = 0;
        data->queue.render.text[i].color.g = 0;
        data->queue.render.text[i].color.b = 0;
        data->queue.render.text[i].color.a = 0;
        data->queue.render.text[i].textIndex = __INT_MAX__;
        data->queue.render.text[i].position = (Vector2){ __INT_MAX__,__INT_MAX__ };
        data->queue.render.text[i].visible = false;
        data->queue.render.text[i].fontSize = __INT_MAX__;
        data->queue.render.text[i].fontIndex = __INT_MAX__;
        data->queue.render.text[i].string = " ";
        data->queue.render.text[i].name = " ";
    }
}

void MQCleanAllRenderModelSlots(DATA *data)
{
    for(int i = 0;i<MAXOBJ;i++)
    { 
        data->queue.render.model[i].color.r = 0;
        data->queue.render.model[i].color.g = 0;
        data->queue.render.model[i].color.b = 0;
        data->queue.render.model[i].color.a = 0;
        data->queue.render.model[i].modelIndex = __INT_MAX__;
        data->queue.render.model[i].position = (Vector3){ __INT_MAX__,__INT_MAX__,__INT_MAX__ };
        data->queue.render.model[i].rotation = __INT_MAX__;
        data->queue.render.model[i].visible = false;
        data->queue.render.model[i].playing = false;
        data->queue.render.model[i].reverse = false;
        data->queue.render.model[i].name = " ";
        data->queue.render.model[i].currentAnim = 0;
        data->queue.render.model[i].currentFrame = 0;
    }
}

void MQCleanAllRenderTextSlots(DATA *data)
{
    for(int i = 0;i<MAXOBJ;i++)
    { 
        data->queue.render.text[i].color.r = 0;
        data->queue.render.text[i].color.g = 0;
        data->queue.render.text[i].color.b = 0;
        data->queue.render.text[i].color.a = 0;
        data->queue.render.text[i].textIndex = __INT_MAX__;
        data->queue.render.text[i].position = (Vector2){ __INT_MAX__,__INT_MAX__ };
        data->queue.render.text[i].visible = false;
        data->queue.render.text[i].fontSize = __INT_MAX__;
        data->queue.render.text[i].fontIndex = __INT_MAX__;
        data->queue.render.text[i].string = " ";
        data->queue.render.text[i].name = " ";
    }
}

void MQRenderAddModelToQueue(DATA *data, char* name, int modelIndex, Color color, Vector3 position, float rotation, int currentAnim, int currentFrame, bool visible, bool playing, bool reverse)
{
    int LocalIndex;
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(data->queue.render.model[i].modelIndex == __INT_MAX__)
        {
            LocalIndex = i;
            break;
        }
    }
    data->queue.render.model[LocalIndex].name = name;
    data->queue.render.model[LocalIndex].currentAnim = currentAnim;
    data->queue.render.model[LocalIndex].currentFrame = currentFrame;
    data->queue.render.model[LocalIndex].color.r = color.r;
    data->queue.render.model[LocalIndex].color.g = color.g;
    data->queue.render.model[LocalIndex].color.b = color.b;
    data->queue.render.model[LocalIndex].color.a = color.a;
    data->queue.render.model[LocalIndex].modelIndex = modelIndex;
    data->queue.render.model[LocalIndex].position = position;
    data->queue.render.model[LocalIndex].rotation = rotation;
    data->queue.render.model[LocalIndex].visible = visible;
    data->queue.render.model[LocalIndex].playing = playing;
    data->queue.render.model[LocalIndex].reverse = reverse;
}

void MQRenderAddTextToQueue(DATA *data,char* name, int textIndex, Color color, Vector2 position, int fontIndex, int fontSize, char* string, bool visible)
{
    int LocalIndex;
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(data->queue.render.text[i].textIndex == __INT_MAX__)
        {
            LocalIndex = i;
            break;
        }
    }
    data->queue.render.text[LocalIndex].name = name;
    data->queue.render.text[LocalIndex].color.r = color.r;
    data->queue.render.text[LocalIndex].color.g = color.g;
    data->queue.render.text[LocalIndex].color.b = color.b;
    data->queue.render.text[LocalIndex].color.a = color.a;
    data->queue.render.text[LocalIndex].textIndex = textIndex;
    data->queue.render.text[LocalIndex].position = position;
    data->queue.render.text[LocalIndex].visible = visible;
    data->queue.render.text[LocalIndex].fontSize = fontSize;
    data->queue.render.text[LocalIndex].fontIndex = fontIndex;
    data->queue.render.text[LocalIndex].string = string;
}

void MQRenderQueue(DATA* data)
{
    
    BeginDrawing();
    ClearBackground(data->queue.render.background);
    BeginMode3D(data->queue.render.camera);
    for(int i=0;i<MAXOBJ;i++)
    {
        DrawBoundingBox(data->file.hitbox[i],BLACK);
        DrawBoundingBox(MQHitboxUpdateXYZ(data->queue.event[i].originEventbox, data->queue.event[i].position),GREEN);
        if(data->queue.render.model[i].modelIndex != __INT_MAX__)
        {
            if(data->queue.render.model[i].playing == true)
            {
                if(data->queue.render.model[i].reverse == false)
                    if(data->queue.render.model[i].currentFrame < data->file.anim[data->queue.render.model[i].modelIndex][data->queue.render.model[i].currentAnim].frameCount)
                        data->queue.render.model[i].currentFrame++;
                    else
                        data->queue.render.model[i].currentFrame = 0;
                else
                    if(data->queue.render.model[i].currentFrame > 0)
                        data->queue.render.model[i].currentFrame--;
                    else
                        data->queue.render.model[i].currentFrame = data->file.anim[data->queue.render.model[i].modelIndex][data->queue.render.model[i].currentAnim].frameCount;
                UpdateModelAnimation(data->file.model[data->queue.render.model[i].modelIndex], data->file.anim[data->queue.render.model[i].modelIndex][data->queue.render.model[i].currentAnim], data->queue.render.model[i].currentFrame);
            }
            DrawModelEx(data->file.model[data->queue.render.model[i].modelIndex], data->queue.render.model[i].position, (Vector3){0.0f, 1.0f, 0.0f}, data->queue.render.model[i].rotation , (Vector3){1.0f, 1.0f, 1.0f}, data->queue.render.model[i].color);
        }
        if(data->queue.render.text[i].textIndex != __INT_MAX__)
        {
            DrawTextEx(data->file.font[data->queue.render.text[i].fontIndex], data->queue.render.text[i].string,data->queue.render.text[i].position , data->queue.render.text[i].fontSize, 0, data->queue.render.text[i].color);
        }
    }
    EndMode3D();
    EndDrawing();
}

