#include "../libs/raylib/raylib.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GLSL_VERSION            100

char *msg;

#include "core/premap.h"
#include "core/camera.c"
#include "core/et.c"
#include "core/font.c"
#include "core/item.h"
#include "personagem.h"
#include "core/map.c"
#include "ambiente.h"
#include "core/load.c"
#include "core/render.c"
#include "core/teclado.c"

int main ( void )
{
	const int screenW = 600;
	const int screenH = 240;
	//SetConfigFlags(FLAG_MSAA_4X_HINT);
	RENDER_START_WINDOW(screenW,screenH);


	clock_t *relogio;
	relogio = malloc ( sizeof ( clock_t ) *10 );

	Camera camera = { 0 };
	camera = CAMERA_START(&camera);
    
    

	AMBIENTE ambiente;
	ambiente.gravidade = 0.2;

	PERSONAGEM personagem;
	ITEM item;
    MAPA mapa;
	LOADALL_MODELS(&mapa,&personagem,&item);
	PERSONAGEM_CONFIGSTART ( &personagem );
    MAPA_START(&mapa);
	personagem.equip.calcaAtual = item.calca[1].idle;
    personagem.equip.chapeuAtual = item.chapeu[1].idle;
    personagem.equip.camisaAtual = item.camisa[1].idle;
    personagem.equip.armaAtual = item.arma[1].idle;
	msg = malloc ( sizeof ( char ) *50 );
	msg = " ";
	Font font = FONT_START(screenH);
	Vector2 fontPosition = { 0, 0 };

	// Ambient light level (some basic lighting)

	SetTargetFPS ( 60 );
    camera.target =  (Vector3){personagem.posicao.x,personagem.posicao.y+2,personagem.posicao.z};
    
	while ( !WindowShouldClose() )      // Detect window close button or ESC key
	{
		UpdateCamera ( &camera );
		GRAVIDADE ( &personagem, &ambiente, mapa );
        //printf("abjahdshadha");
		if ( personagem.usando != false )
		{
			PERSONAGEM_USEANIM ( &personagem , &mapa, item);
		}
		else
		{
			TECLADO_MAIN ( &personagem, &item, mapa);
		}

		if ( personagem.rotacao == 360 )
			personagem.rotacao=0;

		PERSONAGEM_HITBOXUPDATE ( &personagem );
		
		//----------------------------------------------------------------------------------
		// Draw
		//----------------------------------------------------------------------------------
        
        if(mapa.porta[0].abrindo||mapa.porta[0].fechando)
        {
            PORTA_ANIM(&mapa,0);
        }
        else if(mapa.porta[1].abrindo||mapa.porta[1].fechando)
        {
            PORTA_ANIM(&mapa,1);
        }
        
        if(clock() > personagem.relogioLogs+(2*(CLOCKS_PER_SEC/10)))
        {
            msg = " ";
        }
        RENDER_CAMERAUPDATE(personagem, mapa, &camera);
		RENDER(personagem, mapa, camera, font, fontPosition);
	}

	UNLOADALL_MODELS(&personagem, &item, &mapa);
	free ( relogio );
	free ( msg );

	CloseWindow();              // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
