#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#define MAX_GLTF_MODELS  8

#define RLIGHTS_IMPLEMENTATION
#include "raylib/rlights.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif


struct TEXTO
{
	// 0
	Font font;
	char *msg;
	float tamanho;
	Vector2 posicao;

};
typedef struct TEXTO TEXTO;

struct MINMAX
{
	float min, max;
};
typedef struct MINMAX MINMAX;

struct MAPA
{
	Model modelo[2];
    BoundingBox hitboxH[10],hitboxV[10];
    Model dummy;
    int mapaAtual;
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
#include "core/teclado.c"

int main ( void )
{
	const int screenW = 600;
	const int screenH = 240;
	//SetConfigFlags(FLAG_MSAA_4X_HINT);
	START_WINDOW(screenW,screenH);


	clock_t *relogio;
	relogio = malloc ( sizeof ( clock_t ) *10 );

	Camera camera = { 0 };
	camera = CAMERA_START(&camera);

    

	AMBIENTE ambiente;
	ambiente.gravidade = 0.2;

	PERSONAGEM personagem;
	ITEM item;
    MAPA mapa;
	LOADALL_MODELS(&personagem,&item,&mapa);
	PERSONAGEM_CONFIGSTART ( &personagem );
    MAPA_START(&mapa);
	personagem.equip.calcaAtual = item.calca[1].idle;
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
		GRAVIT ( &personagem, &ambiente, mapa );

		if ( personagem.usando != false )
		{
			PERSONAGEM_USEANIM ( &personagem , item);
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
		BeginDrawing();

		ClearBackground ( DARKBROWN );

		DrawTextEx ( font, msg, fontPosition, 16, 0, BLACK );

		// 			CheckCollisionBoxes();
		BeginMode3D ( camera );
        DrawModel(mapa.modelo[mapa.mapaAtual],( Vector3 ){0.0f, 0.0f,0.0f}, 1.0f, WHITE);
        //DrawModelEx ( mapa.modelo[mapa.mapaAtual], ( Vector3 ){0.0f, 0.0f,0.0f}, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, WHITE );
        DrawModelEx ( personagem.modelo.atual, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, (Color){ 240, 199, 156, 255 }  );
		if(personagem.equip.calca != 0)
			DrawModelEx ( personagem.equip.calcaAtual, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, WHITE );
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

	UNLOADALL_MODELS(&personagem, &item);
	free ( relogio );
	free ( msg );

	CloseWindow();              // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
