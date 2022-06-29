void MQRenderLogo(Font fontTitle, Font fontSubTitle, LOGO *logo)
{
    char bufferLocal[255];
    strcpy(bufferLocal, abinCoreReturnData("config.text", "TITLE"));
    DrawTextEx(fontTitle, bufferLocal, (Vector2)
    {
        (GetScreenWidth() / 2) - 157, 8
    }, 48, 0, COR_CINZA);
    DrawTextEx(fontTitle, bufferLocal, (Vector2)
    {
        (GetScreenWidth() / 2) - 157, 46
    }, 48, 0, COR_CINZA);
    DrawTextEx(fontTitle, bufferLocal, (Vector2)
    {
        (GetScreenWidth() / 2) - 157, 84
    }, 48, 0, COR_CINZA);
    DrawTextEx(fontTitle, bufferLocal, (Vector2)
    {
        (GetScreenWidth() / 2) - 157, 122
    }, 48, 0, COR_CINZA);
    DrawTextEx(fontTitle, bufferLocal, (Vector2)
    {
        (GetScreenWidth() / 2) - 157, 160
    }, 48, 0, COR_CINZA);
    switch(logo->ponteiro)
    {
        case 0:
        {
            DrawTextEx(fontTitle, bufferLocal, (Vector2)
            {
                (GetScreenWidth() / 2) - 157, 8
            }, 48, 0, COR_LARANJA);
        }
        break;
        case 1:
        {
            DrawTextEx(fontTitle, bufferLocal, (Vector2)
            {
                (GetScreenWidth() / 2) - 157, 46
            }, 48, 0, COR_LARANJA);
        }
        break;
        case 2:
        {
            DrawTextEx(fontTitle, bufferLocal, (Vector2)
            {
                (GetScreenWidth() / 2) - 157, 84
            }, 48, 0, COR_LARANJA);
        }
        break;
        case 3:
        {
            DrawTextEx(fontTitle, bufferLocal, (Vector2)
            {
                (GetScreenWidth() / 2) - 157, 122
            }, 48, 0, COR_LARANJA);
        }
        break;
        case 4:
        {
            DrawTextEx(fontTitle, bufferLocal, (Vector2)
            {
                (GetScreenWidth() / 2) - 157, 160
            }, 48, 0, COR_LARANJA);
        }
        break;
    }

    if(clock() > logo->relogio + CLOCKS_PER_SEC * 1.5)
    {
        logo->relogio = clock();
        if(logo->ponteiro < 4)
            logo->ponteiro++;
        else if(logo->ponteiro == 4)
            logo->ponteiro = 0;
    }

    logo->relogiosub = clock();
    strcpy(bufferLocal, abinCoreReturnData("config.text", "SUBTITLE"));
    DrawTextEx(fontSubTitle, bufferLocal, (Vector2)
    {
        (GetScreenWidth() / 2) - 150, 202
    }, 24, 0, COR_CINZA);
    if(logo->relogiosub % 19 == 0 && logo->pisca == false)
    {
        logo->pisca = true;
        logo->relogiosubDef = clock();
    }
    else if(logo->pisca == true && logo->piscaPonteiro == 0 && clock() > logo->relogiosubDef + (CLOCKS_PER_SEC / 50))
    {
        logo->piscaPonteiro++;
        strcpy(bufferLocal, abinCoreReturnData("config.text", "SUBTITLE"));
        DrawTextEx(fontSubTitle, bufferLocal, (Vector2)
        {
            (GetScreenWidth() / 2) - 150, 202
        }, 24, 0, COR_LARANJA);
        logo->relogiosubDef = clock();
    }
    else if(logo->pisca == true && logo->piscaPonteiro == 1 && clock() > logo->relogiosubDef + (CLOCKS_PER_SEC / 30))
    {
        logo->piscaPonteiro = 0;
        strcpy(bufferLocal, abinCoreReturnData("config.text", "SUBTITLE"));
        DrawTextEx(fontSubTitle, bufferLocal, (Vector2)
        {
            (GetScreenWidth() / 2) - 150, 202
        }, 24, 0, COR_LARANJA);
        logo->pisca = false;
    }
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
                    return MQTRUE;
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

void MQMenuRender(DATA *data, int max, int opt ,char quotes[][255])
{
    BeginDrawing();
    ClearBackground(COR_BRANCO);
    /* MQRenderLogo(fontTitle, fontSubTitle, *&logo); */

    for(int i = max-1; i >=0; i--)
    {
        if(i == opt)
            DrawTextEx(data->file.font[0], quotes[i], (Vector2){0,(GetScreenHeight() - data->file.font[0].baseSize) - (data->file.font[0].baseSize * i)}, data->file.font[0].baseSize, 0, COR_SELECIONADO);
        else
            DrawTextEx(data->file.font[0], quotes[i], (Vector2){0,(GetScreenHeight() - data->file.font[0].baseSize) - (data->file.font[0].baseSize * i)}, data->file.font[0].baseSize, 0, COR_CINZA);
    }
    EndDrawing();
}


bool MQMenu(DATA *data, int menuIndex)
{
    PlayMusicStream(maintheme);
    int allmax[] = {2,3,3,0,0};
    int langIndex[3][3] = {{0,1},{4,7,1},{4,2,3}};

    int optIndex = 0;
    char quotes[allmax[menuIndex]][255];
    for(short int i = 0 ;i<allmax[menuIndex];i++)
    {
        strcpy(quotes[i],data->file.lang[langIndex[menuIndex][i]]);
    }
    while(menuIndex < MQTRUE&& menuIndex > MQFALSE)
    {
        UpdateMusicStream(maintheme);
        //RENDER
        MQMenuRender(* &data,  allmax[menuIndex], optIndex, quotes );
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
    }
    if(menuIndex==MQTRUE)
        return true;
    else
        return false;
}



