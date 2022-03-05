 
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

 
void RENDER(PERSONAGEM personagem, MAPA mapa, ITEM item, Camera camera, Font font, Vector2 fontPosition)
{
    BeginDrawing();

		ClearBackground ( DARKBROWN );

		DrawTextEx ( font, msg, fontPosition, 16, 0, BLACK );

		BeginMode3D ( camera );
        DrawModel(mapa.modelo[mapa.mapaAtual],( Vector3 ){0.0f, 0.0f,0.0f}, 1.0f, WHITE);
        

        
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
            
        
        if(mapa.pegouItem[0] == false)
        {
            DrawModel(item.calca[1].drop, (Vector3){0,0,0}, 1.0f, WHITE);
            
        }
            
        
        if(mapa.pegouItem[1] == false)
        {
            DrawModel(item.chapeu[1].drop, (Vector3){0,0,0}, 1.0f, WHITE);
            
        }    
        if(mapa.pegouItem[2] == false)
        {
            DrawModel(item.camisa[1].drop, (Vector3){0,0,0}, 1.0f, WHITE);
        }    
            
        
		//DrawBoundingBox ( personagem.hitbox.use,BLACK );
        //DrawBoundingBox ( mapa.hitboxH[0] ,BLACK );
        //DrawBoundingBox ( mapa.hitboxV[0] ,BLACK );
        //DrawBoundingBox ( personagem.hitbox.trasAtual ,BLACK );
		//DrawBoundingBox ( personagem.hitbox.frenteAtual ,BLACK );
        //DrawBoundingBox ( personagem.hitbox.pesAtual ,BLACK );
		//DrawGrid ( 10, 1.0f );
        
        
		EndMode3D();
		EndDrawing();
}
