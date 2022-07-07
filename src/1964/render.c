void MQCleanAllRenderSlots(DATA *data)
{
    for(int i = 0;i<MAXOBJ;i++)
    { 
        data->session.render.model[i].color.r = 0;
        data->session.render.model[i].color.g = 0;
        data->session.render.model[i].color.b = 0;
        data->session.render.model[i].color.a = 0;
        data->session.render.model[i].modelIndex = __INT_MAX__;
        data->session.render.model[i].position = (Vector3){ __INT_MAX__,__INT_MAX__,__INT_MAX__ };
        data->session.render.model[i].rotation = __INT_MAX__;
        data->session.render.model[i].visible = false;
        data->session.render.model[i].playing = false;
        data->session.render.model[i].reverse = false;
        data->session.render.model[i].name = " ";
        data->session.render.model[i].currentAnim = 0;
        data->session.render.model[i].currentFrame = 0;
        data->session.render.text[i].color.r = 0;
        data->session.render.text[i].color.g = 0;
        data->session.render.text[i].color.b = 0;
        data->session.render.text[i].color.a = 0;
        data->session.render.text[i].textIndex = __INT_MAX__;
        data->session.render.text[i].position = (Vector2){ __INT_MAX__,__INT_MAX__ };
        data->session.render.text[i].visible = false;
        data->session.render.text[i].fontSize = __INT_MAX__;
        data->session.render.text[i].fontIndex = __INT_MAX__;
        data->session.render.text[i].string = " ";
        data->session.render.text[i].name = " ";
    }
}

void MQCleanAllRenderModelSlots(DATA *data)
{
    for(int i = 0;i<MAXOBJ;i++)
    { 
        data->session.render.model[i].color.r = 0;
        data->session.render.model[i].color.g = 0;
        data->session.render.model[i].color.b = 0;
        data->session.render.model[i].color.a = 0;
        data->session.render.model[i].modelIndex = __INT_MAX__;
        data->session.render.model[i].position = (Vector3){ __INT_MAX__,__INT_MAX__,__INT_MAX__ };
        data->session.render.model[i].rotation = __INT_MAX__;
        data->session.render.model[i].visible = false;
        data->session.render.model[i].playing = false;
        data->session.render.model[i].reverse = false;
        data->session.render.model[i].name = " ";
        data->session.render.model[i].currentAnim = 0;
        data->session.render.model[i].currentFrame = 0;
    }
}

void MQCleanAllRenderTextSlots(DATA *data)
{
    for(int i = 0;i<MAXOBJ;i++)
    { 
        data->session.render.text[i].color.r = 0;
        data->session.render.text[i].color.g = 0;
        data->session.render.text[i].color.b = 0;
        data->session.render.text[i].color.a = 0;
        data->session.render.text[i].textIndex = __INT_MAX__;
        data->session.render.text[i].position = (Vector2){ __INT_MAX__,__INT_MAX__ };
        data->session.render.text[i].visible = false;
        data->session.render.text[i].fontSize = __INT_MAX__;
        data->session.render.text[i].fontIndex = __INT_MAX__;
        data->session.render.text[i].string = " ";
        data->session.render.text[i].name = " ";
    }
}

void MQRenderAddModelToQueue(DATA *data, char* name, int modelIndex, Color color, Vector3 position, float rotation, int currentAnim, int currentFrame, bool visible, bool playing, bool reverse)
{
    int LocalIndex;
    for(int i = 0;i<MAXOBJ;i++)
    {
        if(data->session.render.model[i].modelIndex == __INT_MAX__)
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

void MQRenderAddTextToQueue(DATA *data,char* name, int textIndex, Color color, Vector2 position, int fontIndex, int fontSize, char* string, bool visible)
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

void MQRenderQueue(DATA* data)
{
    
    BeginDrawing();
    ClearBackground(data->session.render.background);
    BeginMode3D(data->session.render.camera);
    for(int i=0;i<MAXOBJ;i++)
    {
        DrawBoundingBox(data->file.hitbox[i],BLACK);
        if(data->session.render.model[i].modelIndex != __INT_MAX__)
        {
            if(data->session.render.model[i].playing == true)
            {
                if(data->session.render.model[i].reverse == false)
                    if(data->session.render.model[i].currentFrame < data->file.anim[data->session.render.model[i].modelIndex][data->session.render.model[i].currentAnim].frameCount)
                        data->session.render.model[i].currentFrame++;
                    else
                        data->session.render.model[i].currentFrame = 0;
                else
                    if(data->session.render.model[i].currentFrame > 0)
                        data->session.render.model[i].currentFrame--;
                    else
                        data->session.render.model[i].currentFrame = data->file.anim[data->session.render.model[i].modelIndex][data->session.render.model[i].currentAnim].frameCount;
                UpdateModelAnimation(data->file.model[data->session.render.model[i].modelIndex], data->file.anim[data->session.render.model[i].modelIndex][data->session.render.model[i].currentAnim], data->session.render.model[i].currentFrame);
            }
            DrawModelEx(data->file.model[data->session.render.model[i].modelIndex], data->session.render.model[i].position, (Vector3){0.0f, 1.0f, 0.0f}, data->session.render.model[i].rotation , (Vector3){1.0f, 1.0f, 1.0f}, data->session.render.model[i].color);
        }
        if(data->session.render.text[i].textIndex != __INT_MAX__)
        {
            DrawTextEx(data->file.font[data->session.render.text[i].fontIndex], data->session.render.text[i].string,data->session.render.text[i].position , data->session.render.text[i].fontSize, 0, data->session.render.text[i].color);
        }
    }
    EndMode3D();
    EndDrawing();
}

