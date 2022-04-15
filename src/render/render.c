void RENDER_ESCMENU(MENU menu, Font font)
{
    switch(menu.opcao)
    {
        case 0:
        {
            DrawTextEx ( font, "Voltar ao jogo", (Vector2){0,0}, 16, 0, COR_SELECIONADO );
            DrawTextEx ( font, "Salvar progresso", (Vector2){0,0+16}, 16, 0, COR_NAOSELECIONADO );
            DrawTextEx ( font, "Carregar jogo salvo", (Vector2){0,0+32}, 16, 0, COR_NAOSELECIONADO );
            DrawTextEx ( font, "Sair", (Vector2){0,0+48}, 16, 0, COR_NAOSELECIONADO );
        }
        break;
        case 1:
        {
            DrawTextEx ( font, "Voltar ao jogo", (Vector2){0,0}, 16, 0, COR_NAOSELECIONADO );
            DrawTextEx ( font, "Salvar progresso", (Vector2){0,0+16}, 16, 0, COR_SELECIONADO );
            DrawTextEx ( font, "Carregar jogo salvo", (Vector2){0,0+32}, 16, 0, COR_NAOSELECIONADO );
            DrawTextEx ( font, "Sair", (Vector2){0,0+48}, 16, 0, COR_NAOSELECIONADO );
        }
        break;
        case 2:
        {
            DrawTextEx ( font, "Voltar ao jogo", (Vector2){0,0}, 16, 0, COR_NAOSELECIONADO );
            DrawTextEx ( font, "Salvar progresso", (Vector2){0,0+16}, 16, 0, COR_NAOSELECIONADO );
            DrawTextEx ( font, "Carregar jogo salvo", (Vector2){0,0+32}, 16, 0, COR_SELECIONADO );
            DrawTextEx ( font, "Sair", (Vector2){0,0+48}, 16, 0, COR_NAOSELECIONADO );
        }
        break;
        case 3:
        {
            DrawTextEx ( font, "Voltar ao jogo", (Vector2){0,0}, 16, 0, COR_NAOSELECIONADO );
            DrawTextEx ( font, "Salvar progresso", (Vector2){0,0+16}, 16, 0, COR_NAOSELECIONADO );
            DrawTextEx ( font, "Carregar jogo salvo", (Vector2){0,0+32}, 16, 0, COR_NAOSELECIONADO );
            DrawTextEx ( font, "Sair", (Vector2){0,0+48}, 16, 0, COR_SELECIONADO );
        }
        break;
    }
}

void RENDER_MENUSTART(MAPA mapa, Camera camera, Font font, Vector2 fontPosition, MENU menu)
{
    BeginDrawing();

    ClearBackground ( (Color){ 115, 105, 97, 255 }   );

    //DrawTextEx ( font, msg, fontPosition, 16, 0, COR_NAOSELECIONADO );

    BeginMode3D ( camera );
    DrawModel(mapa.modelo[mapa.mapaAtual],( Vector3 ){0.0f, 0.0f,0.0f}, 1.0f, WHITE);
    DrawModel(mapa.props[0].modelo,( Vector3 ){0.0f, 0.0f,0.0f}, 1.0f, WHITE);
    
    for(int i = 0; i<10;i++)
    {
        if(mapa.porta.slots[i].existe)
        {
            for(int i = 0; i<10; i++)
            {
                if(mapa.porta.slots[i].existe)
                {
                    if(mapa.porta.slots[i].invertido == false)
                    {
                        switch (mapa.porta.slots[i].frame)
                        {
                            case 0:
                            {
                                DrawModel(mapa.porta.base.modelo[0],mapa.porta.slots[i].posicao, 1.0f, WHITE);
                            }
                            break;
                            case 1:
                            {
                                DrawModel(mapa.porta.base.modelo[1],mapa.porta.slots[i].posicao, 1.0f, WHITE);
                            }
                            break;
                            case 2:
                            {
                                DrawModel(mapa.porta.base.modelo[2],mapa.porta.slots[i].posicao, 1.0f, WHITE);
                            }
                            break;
                            case 3:
                            {
                                DrawModel(mapa.porta.base.modelo[3],mapa.porta.slots[i].posicao, 1.0f, WHITE);

                            }
                            break;
                        }
                    }
                    else if(mapa.porta.slots[i].invertido == true)
                    {
                        switch (mapa.porta.slots[i].frame)
                        {
                            case 0:
                            {
                                DrawModel(mapa.porta.base.modelo[0],mapa.porta.slots[i].posicao, 1.0f, WHITE);

                            }
                            break;
                            case 1:
                            {
                                DrawModel(mapa.porta.base.modeloI[0],mapa.porta.slots[i].posicao, 1.0f, WHITE);

                            }
                            break;
                            case 2:
                            {
                                DrawModel(mapa.porta.base.modeloI[1],mapa.porta.slots[i].posicao, 1.0f, WHITE);
                            }
                            break;
                            case 3:
                            {
                                DrawModel(mapa.porta.base.modeloI[2],mapa.porta.slots[i].posicao, 1.0f, WHITE);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    if(mapa.item[0].pegou == false)
    {
        DrawModel(mapa.item[0].modelo, (Vector3){0,0,0}, 1.0f, WHITE);
    }
    if(mapa.item[1].pegou == false)
    {
        DrawModel(mapa.item[1].modelo, (Vector3){0,0,0}, 1.0f, WHITE);
    }    
    if(mapa.item[2].pegou == false)
    {
        DrawModel(mapa.item[2].modelo, (Vector3){0,0,0}, 1.0f, WHITE);
    }  
    if(mapa.item[3].pegou == false)
    {
        DrawModel(mapa.item[3].modelo, (Vector3){0,0,0}, 1.0f, WHITE);
    } 
        
    for(int i = 0; i<10; i++)
    {
        if(mapa.drops[i].ocupado == true )
        {
            DrawModel(mapa.drops[i].modelo, mapa.drops[i].posicao, 1.0f, WHITE);
        }
    }
    for(int i= 0; i<255;i++)
    {
        if(mapa.balas[i].existe == true )
        {
            DrawModelEx ( mapa.balasGLOBAL.modelo, mapa.balas[i].posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, mapa.balas[i].rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, WHITE );
        }
    }
    for(int i = 0; i <255; i++)
    {
        if(mapa.balas[i].existe == true )
        {
            DrawBoundingBox ( mapa.balas[i].hitbox,COR_NAOSELECIONADO );
        }
    }
    EndMode3D();
    switch(menu.opcao)
    {
        case 0:
        {
            DrawTextEx ( font, "Jogar", fontPosition, 16, 0, COR_SELECIONADO );
            DrawTextEx ( font, "Sair", (Vector2){fontPosition.x,fontPosition.y+16}, 16, 0, COR_NAOSELECIONADO );
        }
        break;
        case 1:
        {
            DrawTextEx ( font, "Jogar", fontPosition, 16, 0, COR_NAOSELECIONADO );
            DrawTextEx ( font, "Sair", (Vector2){fontPosition.x,fontPosition.y+16}, 16, 0, COR_SELECIONADO );
        }
        break;
    }
    
    
    EndDrawing();
}

void RENDER_NPC(HUMANO_NPC personagem)
{
    DrawModelEx ( personagem.modelo.atual, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, (Color){ 240, 199, 156, 255 }  );
    
    if(personagem.equip.calca.ponteiro != 0&&personagem.equip.calca.modelo.meshCount != 0)
    {
        DrawModelEx ( personagem.equip.calca.modelo, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, WHITE );
    }
    
    if(personagem.equip.camisa.ponteiro != 0&&personagem.equip.camisa.modelo.meshCount != 0)
    {
        DrawModelEx ( personagem.equip.camisa.modelo, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, WHITE );
    }
        
    if(personagem.equip.chapeu.ponteiro != 0&&personagem.equip.chapeu.modelo.meshCount != 0)
    {
        DrawModelEx ( personagem.equip.chapeu.modelo, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, WHITE );
    }
        
    if(personagem.equip.arma.ponteiro != 0&&personagem.equip.arma.modelo.meshCount != 0)
    {
        DrawModelEx ( personagem.equip.arma.modelo, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, WHITE );
    }
}

void RENDER_PERSONAGEM(PERSONAGEM personagem)
{
    DrawModelEx ( personagem.modelo.atual, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, (Color){ 240, 199, 156, 255 }  );
    
    if(personagem.equip.calca.ponteiro != 0&&personagem.equip.calca.modelo.meshCount != 0)
    {
        DrawModelEx ( personagem.equip.calca.modelo, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, WHITE );
    }
    
    if(personagem.equip.camisa.ponteiro != 0&&personagem.equip.camisa.modelo.meshCount != 0)
    {
        DrawModelEx ( personagem.equip.camisa.modelo, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, WHITE );
    }
        
    if(personagem.equip.chapeu.ponteiro != 0&&personagem.equip.chapeu.modelo.meshCount != 0)
    {
        DrawModelEx ( personagem.equip.chapeu.modelo, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, WHITE );
    }
        
    if(personagem.equip.arma.ponteiro != 0&&personagem.equip.arma.modelo.meshCount != 0)
    {
        DrawModelEx ( personagem.equip.arma.modelo, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, WHITE );
    }
}

void RENDER_LVL0(PERSONAGEM personagem, NPC0 humano, MAPA mapa, Camera camera, Font font, Vector2 fontPosition, MENU menu)
{
    BeginDrawing();

    ClearBackground ( (Color){ 115, 105, 97, 255 }   );

    //DrawTextEx ( font, msg, fontPosition, 16, 0, COR_NAOSELECIONADO );

    BeginMode3D ( camera );
    DrawModel(mapa.modelo[mapa.mapaAtual],( Vector3 ){0.0f, 0.0f,0.0f}, 1.0f, WHITE);
    DrawModel(mapa.props[0].modelo,( Vector3 ){0.0f, 0.0f,0.0f}, 1.0f, WHITE);
    
    for(int i = 0; i<10;i++)
    {
        if(mapa.porta.slots[i].existe)
        {
            for(int i = 0; i<10; i++)
            {
                if(mapa.porta.slots[i].existe)
                {
                    if(mapa.porta.slots[i].invertido == false)
                    {
                        switch (mapa.porta.slots[i].frame)
                        {
                            case 0:
                            {
                                DrawModel(mapa.porta.base.modelo[0],mapa.porta.slots[i].posicao, 1.0f, WHITE);
                            }
                            break;
                            case 1:
                            {
                                DrawModel(mapa.porta.base.modelo[1],mapa.porta.slots[i].posicao, 1.0f, WHITE);
                            }
                            break;
                            case 2:
                            {
                                DrawModel(mapa.porta.base.modelo[2],mapa.porta.slots[i].posicao, 1.0f, WHITE);
                            }
                            break;
                            case 3:
                            {
                                DrawModel(mapa.porta.base.modelo[3],mapa.porta.slots[i].posicao, 1.0f, WHITE);

                            }
                            break;
                        }
                    }
                    else if(mapa.porta.slots[i].invertido == true)
                    {
                        switch (mapa.porta.slots[i].frame)
                        {
                            case 0:
                            {
                                DrawModel(mapa.porta.base.modelo[0],mapa.porta.slots[i].posicao, 1.0f, WHITE);

                            }
                            break;
                            case 1:
                            {
                                DrawModel(mapa.porta.base.modeloI[0],mapa.porta.slots[i].posicao, 1.0f, WHITE);

                            }
                            break;
                            case 2:
                            {
                                DrawModel(mapa.porta.base.modeloI[1],mapa.porta.slots[i].posicao, 1.0f, WHITE);
                            }
                            break;
                            case 3:
                            {
                                DrawModel(mapa.porta.base.modeloI[2],mapa.porta.slots[i].posicao, 1.0f, WHITE);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    
    
    RENDER_PERSONAGEM(personagem);
    RENDER_NPC(humano.npc[0]);
    if(mapa.item[0].pegou == false)
    {
        DrawModel(mapa.item[0].modelo, (Vector3){0,0,0}, 1.0f, WHITE);
    }
    if(mapa.item[1].pegou == false)
    {
        DrawModel(mapa.item[1].modelo, (Vector3){0,0,0}, 1.0f, WHITE);
    }    
    if(mapa.item[2].pegou == false)
    {
        DrawModel(mapa.item[2].modelo, (Vector3){0,0,0}, 1.0f, WHITE);
    }  
    if(mapa.item[3].pegou == false)
    {
        DrawModel(mapa.item[3].modelo, (Vector3){0,0,0}, 1.0f, WHITE);
    } 
        
    for(int i = 0; i<10; i++)
    {
        if(mapa.drops[i].ocupado == true )
        {
            DrawModel(mapa.drops[i].modelo, mapa.drops[i].posicao, 1.0f, WHITE);
        }
    }
    for(int i= 0; i<255;i++)
    {
        if(mapa.balas[i].existe == true )
        {
            DrawModelEx ( mapa.balasGLOBAL.modelo, mapa.balas[i].posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, mapa.balas[i].rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, WHITE );
        }
    }
    EndMode3D();
    
    if(menu.esc==true)
    {
        RENDER_ESCMENU(menu, font);
    }
    
    DrawTextEx ( font, msg, fontPosition, 16, 0, COR_NAOSELECIONADO );
    EndDrawing();
}
 
 
void RENDER_START_WINDOW(const int screenW,const int screenH)
{

	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	//time_t *seconds = malloc ( sizeof ( time_t ) );
	//char *textotitulo = malloc ( sizeof ( char ) *40 );
	//*seconds = time ( NULL );
	//sprintf ( textotitulo,"19.64-%ld",*seconds );
	InitWindow ( screenW, screenH, "O Estado Novo" );
	//free ( seconds );
	//free ( textotitulo );
}

void RENDER_CAMERAUPDATE(PERSONAGEM personagem, MAPA mapa, Camera *camera)
{
    if(CheckCollisionBoxes(personagem.hitbox.frenteAtual, mapa.area[0]))
    {
        camera->position = (Vector3){0.4375,3.5,11.0625};
    }
    else if(CheckCollisionBoxes(personagem.hitbox.frenteAtual, mapa.area[1]))
    {
        camera->position = (Vector3){4.473,3.5,0.562};
    }
    else if(CheckCollisionBoxes(personagem.hitbox.frenteAtual, mapa.area[2]))
    {
        camera->position = (Vector3){7.5,2.5,-4};
    }
    else if(CheckCollisionBoxes(personagem.hitbox.frenteAtual, mapa.area[3]))
    {
        camera->position = (Vector3){-3.56,2.5,-4.8375};
    }
    else if(CheckCollisionBoxes(personagem.hitbox.frenteAtual, mapa.area[4]))
    {
        camera->position = (Vector3){-19,6,-16.5};
    }
    else if(CheckCollisionBoxes(personagem.hitbox.frenteAtual, mapa.area[5]))
    {
        camera->position = (Vector3){-6.5,8.5,-29};
    }
    
    if (CheckCollisionBoxes(personagem.hitbox.frenteAtual, mapa.area[4]) == false)
			camera->target =  (Vector3){personagem.posicao.x,personagem.posicao.y+2,personagem.posicao.z};
    else
            camera->target =  (Vector3){0,4,-16.5};
}
 
 
void RENDER(PERSONAGEM personagem, NPC0 humano, MAPA mapa, Camera camera, Font font, Vector2 fontPosition, MENU menu)
{
    RENDER_LVL0(personagem, humano, mapa, camera, font, fontPosition, menu);
}
