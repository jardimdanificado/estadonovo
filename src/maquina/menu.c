void MQRenderLogo(DATA data,char* title,char* subtitle,int frame)
{
/*     DrawTextEx(data.file.font[1], title, (Vector2){(GetScreenWidth() / 2) - 157,8}, data.file.font[1].baseSize, 0, COR_LARANJA);*/
    for(int i = 1; i<(GetScreenHeight()/data.file.font[1].baseSize)-1;i++)
    {
        if((frame+(i*i*i))%133>=0&&(frame+(i*i*i))%141<i)
            DrawTextEx(data.file.font[1], title, (Vector2){(GetScreenWidth() / 2) - 157, (data.file.font[1].baseSize*i)-16}, data.file.font[1].baseSize, 0, COR_LARANJA);
        else
            DrawTextEx(data.file.font[1], title, (Vector2){(GetScreenWidth() / 2) - 157, (data.file.font[1].baseSize*i)-16}, data.file.font[1].baseSize, 0, COR_CINZA);
    }
    if(frame%84>=0&&frame%120<1)
        DrawTextEx(data.file.font[2], subtitle, (Vector2){(GetScreenWidth() / 2) - 150 , GetScreenHeight()-(data.file.font[2].baseSize+(data.file.font[2].baseSize/2))}, data.file.font[2].baseSize, 0, COR_LARANJA);
    else
        DrawTextEx(data.file.font[2], subtitle, (Vector2){(GetScreenWidth() / 2) - 150 , GetScreenHeight()-(data.file.font[2].baseSize+(data.file.font[2].baseSize/2))}, data.file.font[2].baseSize, 0, COR_CINZA);
}

int MQMenuQuestions(DATA *data, int menu, int opcao )
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
/*         case 3:
            switch (opcao)
            {
                case 0:
                {
                    
                }
                break;
                case 1:
                {
                    
                }
                break;
                case 2:
                {
                    
                }
                break;
                case 3:
                {
                    
                }
                break;
            }
        break; */
        default:
            switch (opcao)
            {
                case 0:
                {
                    
                }
                break;
                case 1:
                {
                    
                }
                break;
                case 2:
                {
                    
                }
                break;
                case 3:
                {
                    
                }
                break;
            }
        break;
    }
}

void MQMenuRender(DATA data, int max, int opt ,char quotes[][255])
{
    BeginDrawing();
    ClearBackground(COR_BRANCO);
    for(int i = max-1; i >=0; i--)
    {
        if(i == opt)
            DrawTextEx(data.file.font[0], quotes[i], (Vector2){0,(GetScreenHeight() - data.file.font[0].baseSize) - (data.file.font[0].baseSize * i)}, data.file.font[0].baseSize, 0, COR_SELECIONADO);
        else
            DrawTextEx(data.file.font[0], quotes[i], (Vector2){0,(GetScreenHeight() - data.file.font[0].baseSize) - (data.file.font[0].baseSize * i)}, data.file.font[0].baseSize, 0, COR_CINZA);
    }
    EndDrawing();
}


bool MQMenu(DATA *data, int menuIndex)
{
    PlayMusicStream(data->file.audio[0]);
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
        strcpy(quotes[i],data->file.lang[langIndex[menuIndex][i]]);
    }
    while(menuIndex < MQTRUE&& menuIndex > MQFALSE)
    {
        UpdateMusicStream(data->file.audio[0]);
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
                    strcpy(quotes[i],data->file.lang[langIndex[menuIndex][i]]);
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



