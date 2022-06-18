
void MQMenuRender(ABINMenu menu, bool invertido,   DATA *data,   Font font, Font fontTitle, Font fontSubTitle, LOGO *logo, int screenH)
{
    BeginDrawing();
    ClearBackground(COR_BRANCO);
    MQRenderLogo(fontTitle, fontSubTitle, * &logo);
    if(invertido == true)
    {
        char *buffzin;
        buffzin = malloc(40);
        for(int i = 0; i < menu.max; i++)
        {
            snprintf(buffzin, 40, "txt%d", i);
            DrawTextEx(font, abinCoreReturnData("./data/temp/lang.text", abinCoreReturnData(menu.fileloc, buffzin)), (Vector2)
            {
                0, screenH - (32 - (16 * i))
            }, 16, 0, COR_CINZA);
        }
        free(buffzin);
    }
    else if(invertido == false)
    {
        char *buffzin;
        buffzin = malloc(40);
        for(int i = 0; i < menu.max; i++)
        {
            snprintf(buffzin, 40, "txt%d", i);
            DrawTextEx(font, abinCoreReturnData("./data/temp/lang.text", abinCoreReturnData(menu.fileloc, buffzin)), (Vector2)
            {
                0, 0 + (16 * i)
            }, 16, 0, COR_CINZA);
        }
        free(buffzin);
    }
    char *buffzin, buffzao[255];
    buffzin = malloc(40);
    snprintf(buffzin, 40, "txt%d", menu.ponteiro);
    char *buffcopia = abinCoreReturnData(menu.fileloc, buffzin);
    snprintf(buffzao, 255, "%s", buffcopia);
    if(invertido == true)
    {
        DrawTextEx(font, buffzao, (Vector2)
        {
            0, screenH - (32 - (16 * menu.ponteiro))
        }, 16, 0, COR_SELECIONADO);
    }
    else if(invertido == false)
    {
        DrawTextEx(font, buffzao, (Vector2)
        {
            0, 0 + (16 * menu.ponteiro)
        }, 16, 0, COR_SELECIONADO);
    }
    free(buffzin);
    EndDrawing();
}

bool MQMenu(char *file, bool invertido,   DATA *data,   Font font, Font fontTitle, Font fontSubTitle, LOGO *logo, int screenH)
{
    PlayMusicStream(maintheme);
    ABINMenu menu;
    menu.estaAberto = true;
    char buff[255];
    menu.fileloc = malloc(255);
    strcpy(menu.fileloc, file);
    menu.max = atoi(abinCoreReturnData(file, "MAX"));
    menu.ponteiro = 0;
    while(menu.estaAberto == true)
    {
        UpdateMusicStream(maintheme);
        //RENDER
        MQMenuRender(menu, invertido, * &data,  font, fontTitle, fontSubTitle, * &logo,  screenH);
        //keyboard
        if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        {
            if(menu.ponteiro == menu.max - 1)
            {
                menu.ponteiro = 0;
            }
            else if(menu.ponteiro < menu.max)
            {
                menu.ponteiro++;
            }
        }
        if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        {
            if(menu.ponteiro == 0)
            {
                menu.ponteiro = menu.max - 1;
            }
            else if(menu.ponteiro > 0)
            {
                menu.ponteiro--;
            }
        }
        if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_E))
        {
            snprintf(buff, 255, "f%d", menu.ponteiro);
            if(strcmp(abinCoreReturnData(file, buff), "EXIT") == 0)
            {
                free(menu.fileloc);
                return true;
            }
            else if(strcmp(abinCoreReturnData(file, buff), "OFFLOOP") == 0)
            {
                menu.estaAberto = false;
                free(menu.fileloc);
                return false;
            }
            else if(strcmp(abinCoreReturnData(file, buff), "GO") == 0)
            {
                menu.estaAberto = false;
                char newlink[255], bakbuff[255];
                snprintf(bakbuff, 255, "to%d", menu.ponteiro);
                strcpy(newlink, abinCoreReturnData(file, bakbuff));
                MQMenu(newlink, false, * &data,  font, fontTitle, fontSubTitle, * &logo,  screenH);
                free(menu.fileloc);
                return false;
            }
            else if(strcmp(abinCoreReturnData(file, buff), "SAVE") == 0)
                MQSaveGame(*data);
            else if(strcmp(abinCoreReturnData(file, buff), "LOAD") == 0)
                MQLoadGame( *&data);
        }
    }
    free(menu.fileloc);
}
