int MQMenuQuestions(MQDATA *data, int menu, int opcao )
{
    switch (menu)
    {
        case 0:
            switch (opcao)
            {
                case 0:
                {
                    return MQFALSE;
                }
                break;
                case 1:
                {
                    return MQTRUE;
                }
                break;
            }
        break;
        case 1:
            switch (opcao)
            {
                case 0:
                {
                    return MQFALSE;
                }
                break;
                case 1:
                {
                    return 2;
                }
                break;
                case 2:
                {
                    return MQTRUE;
                }
                break;
            }
        break;
        case 2:
            switch (opcao)
            {
                case 0:
                {
                    return MQFALSE;
                }
                break;
                case 1:
                {
                    MQSaveGame(*data);
                    return MQFALSE;
                }
                break;
                case 2:
                {
                    MQLoadGame(*&data);
                    return MQFALSE;
                }
                break;
            }
        break;
    }
}

void MQRenderLogo(MQDATA data,char* title,char* subtitle,int frame)
{
    for(int i = 1; i<(GetScreenHeight()/data.files.fonts[1].font.baseSize)-1;i++)
    {
        if((frame+(i*i*i))%133>=0&&(frame+(i*i*i))%141<i)
            DrawTextEx(data.files.fonts[1].font, title, (Vector2){(GetScreenWidth() / 2) - 157, (data.files.fonts[1].font.baseSize*i)-16}, data.files.fonts[1].font.baseSize, 0, COR_LARANJA);
        else
            DrawTextEx(data.files.fonts[1].font, title, (Vector2){(GetScreenWidth() / 2) - 157, (data.files.fonts[1].font.baseSize*i)-16}, data.files.fonts[1].font.baseSize, 0, COR_CINZA);
    }
    if(frame%84>=0&&frame%120<1)
        DrawTextEx(data.files.fonts[2].font, subtitle, (Vector2){(GetScreenWidth() / 2) - 150 , GetScreenHeight()-(data.files.fonts[2].font.baseSize+(data.files.fonts[2].font.baseSize/2))}, data.files.fonts[2].font.baseSize, 0, COR_LARANJA);
    else
        DrawTextEx(data.files.fonts[2].font, subtitle, (Vector2){(GetScreenWidth() / 2) - 150 , GetScreenHeight()-(data.files.fonts[2].font.baseSize+(data.files.fonts[2].font.baseSize/2))}, data.files.fonts[2].font.baseSize, 0, COR_CINZA);
}

void MQMenuRender(MQDATA data, int max, int opt ,char quotes[][255])
{
    BeginDrawing();
    ClearBackground(COR_BRANCO);
    for(int i = max-1; i >=0; i--)
    {
        if(i == opt)
            DrawTextEx(data.files.fonts[0].font, quotes[i], (Vector2){0,(GetScreenHeight() - data.files.fonts[0].font.baseSize) - (data.files.fonts[0].font.baseSize * i)}, data.files.fonts[0].font.baseSize, 0, COR_SELECIONADO);
        else
            DrawTextEx(data.files.fonts[0].font, quotes[i], (Vector2){0,(GetScreenHeight() - data.files.fonts[0].font.baseSize) - (data.files.fonts[0].font.baseSize * i)}, data.files.fonts[0].font.baseSize, 0, COR_CINZA);
    }
    EndDrawing();
}


bool MQMenu(MQDATA *data, int menuIndex)
{
    PlayMusicStream(data->files.musics[0].music);
    int allmax[] = {2,3,3,0,0};
    int langIndex[3][3] = {{0,1},{4,7,1},{4,2,3}};

    int optIndex = 0;
    char quotes[allmax[menuIndex]][255];
    char title[2][64];
    strcpy(title[0],abinCoreReturnData("./config.text","TITLE"));
    strcpy(title[1],abinCoreReturnData("./config.text","SUBTITLE"));
    int localframe = 0;
    for(short int i = 0 ;i<allmax[menuIndex];i++)
    {
        strcpy(quotes[i],data->files.langs[langIndex[menuIndex][i]].text);
    }
    while(menuIndex < MQTRUE&& menuIndex > MQFALSE)
    {
        UpdateMusicStream(data->files.musics[0].music);
        //RENDER
        MQRenderLogo(*data,title[0],title[1],localframe);
        MQMenuRender(*data,  allmax[menuIndex], optIndex, quotes );
        //keyboard
        if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        {
            if(optIndex == 0)
            {
                optIndex = allmax[menuIndex] - 1;
            }
            else
            {
                optIndex--;
            }
        }
        if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        {
            if(optIndex == allmax[menuIndex] - 1)
            {
                optIndex = 0;
            }
            else
            {
                optIndex++;
            }
        }
        if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_E))
        {
            menuIndex = MQMenuQuestions(*&data,menuIndex,optIndex);
            if (menuIndex>MQFALSE&&menuIndex<MQTRUE)
            {
                for(short int i = 0 ;i<allmax[menuIndex];i++)
                {
                    strcpy(quotes[i],data->files.langs[langIndex[menuIndex][i]].text);
                }
            }
        }
        localframe++;
    }
    if(menuIndex==MQTRUE)
        return true;
    else
        return false;
}



