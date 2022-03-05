#include "raylib/raylib.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif


struct MAPA
{
	Model modelo[2];
    
    BoundingBox hitboxH[10],hitboxV[10];
    Model dummy;
    
    int mapaAtual;
    
    BoundingBox item[10];
    bool pegouItem[10];
};
typedef struct MAPA MAPA;




char *msg;


#include "core/camera.c"
#include "core/et.c"
#include "core/font.c"
#include "core/item.c"
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
	LOADALL_MODELS(&personagem,&item);
	PERSONAGEM_CONFIGSTART ( &personagem );
    MAPA_START(&mapa, item);
	personagem.equip.calcaAtual = item.calca[1].idle;
    personagem.equip.chapeuAtual = item.chapeu[1].idle;
    personagem.equip.camisaAtual = item.camisa[1].idle;
	msg = malloc ( sizeof ( char ) *50 );
	msg = "Signed Distance Fields";


	Font font = FONT_START(screenH);
	Vector2 fontPosition = { 40, screenH/2.0f - 50 };

	// Ambient light level (some basic lighting)

	SetTargetFPS ( 60 );

	while ( !WindowShouldClose() )      // Detect window close button or ESC key
	{
		if ( IsMouseButtonDown ( MOUSE_MIDDLE_BUTTON ) == false )
			camera.target = personagem.posicao;

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
		RENDER(personagem, mapa, item, camera, font, fontPosition);
	}

	UNLOADALL_MODELS(&personagem, &item, &mapa);
	free ( relogio );
	free ( msg );

	CloseWindow();              // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
