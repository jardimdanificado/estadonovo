 
void RENDER_START_WINDOW(const int screenW,const int screenH)
{

	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	time_t *seconds = malloc ( sizeof ( time_t ) );
	char *textotitulo = malloc ( sizeof ( char ) *40 );
	*seconds = time ( NULL );
	sprintf ( textotitulo,"19.64-%ld",*seconds );
	InitWindow ( screenW, screenH, textotitulo );
	free ( seconds );
	free ( textotitulo );
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
 
 
void RENDER(PERSONAGEM personagem, MAPA mapa, Camera camera, Font font, Vector2 fontPosition)
{
    BeginDrawing();

    ClearBackground ( DARKBROWN );

    //DrawTextEx ( font, msg, fontPosition, 16, 0, BLACK );

    BeginMode3D ( camera );
    DrawModel(mapa.modelo[mapa.mapaAtual],( Vector3 ){0.0f, 0.0f,0.0f}, 1.0f, WHITE);
    DrawModel(mapa.props[0].modelo,( Vector3 ){0.0f, 0.0f,0.0f}, 1.0f, WHITE);
    DrawModel(mapa.porta[0].modelo[mapa.porta[0].frame],( Vector3 ){0.0f, 0.0f,0.0f}, 1.0f, WHITE);
    DrawModel(mapa.porta[1].modelo[mapa.porta[1].frame],( Vector3 ){0.0f, 0.0f,0.0f}, 1.0f, WHITE);
    DrawModel(mapa.porta[2].modelo[0],( Vector3 ){0.0f, 0.0f,0.0f}, 1.0f, WHITE);
    DrawModel(mapa.porta[3].modelo[0],( Vector3 ){0.0f, 0.0f,0.0f}, 1.0f, WHITE);
    
    DrawModelEx ( personagem.modelo.atual, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, (Color){ 240, 199, 156, 255 }  );
    
    if(personagem.equip.calca != 0&&personagem.equip.calcaAtual.meshCount != 0)
    {
        DrawModelEx ( personagem.equip.calcaAtual, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, WHITE );
    }
    
    if(personagem.equip.camisa != 0&&personagem.equip.camisaAtual.meshCount != 0)
    {
        DrawModelEx ( personagem.equip.camisaAtual, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, WHITE );
    }
        
    if(personagem.equip.chapeu != 0&&personagem.equip.chapeuAtual.meshCount != 0)
    {
        DrawModelEx ( personagem.equip.chapeuAtual, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, WHITE );
    }
        
    if(personagem.equip.arma != 0&&personagem.equip.armaAtual.meshCount != 0)
    {
        DrawModelEx ( personagem.equip.armaAtual, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, WHITE );
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
        
    /*for(int i = 0; i <10; i++)
    {
        DrawBoundingBox ( mapa.hitboxVertical[i],BLACK );
    }*/
    //DrawBoundingBox ( personagem.hitbox.use,BLACK );
    //DrawBoundingBox ( mapa.hitboxHorizontal[0] ,BLACK );
    //DrawBoundingBox ( mapa.hitboxVertical[0] ,BLACK );
    //DrawBoundingBox ( personagem.hitbox.trasAtual ,BLACK );
    //DrawBoundingBox ( personagem.hitbox.frenteAtual ,BLACK );
    //DrawBoundingBox (mapa.porta[0].hitbox, BLACK);
//         DrawBoundingBox ( personagem.hitbox.pesAtual ,BLACK );
    //DrawGrid ( 10, 1.0f );
    
    
    EndMode3D();
    
    DrawTextEx ( font, msg, fontPosition, 16, 0, BLACK );
    EndDrawing();
}
