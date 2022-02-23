#include "raylib/raylib.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#define MAX_GLTF_MODELS  8



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






char *msg;


#include "core/camera.c"
#include "core/et.c"
#include "core/font.c"
#include "core/item.c"
#include "personagem.h"
#include "ambiente.h"
#include "core/load.c"
#include "core/teclado.c"

int main ( void )
{
	const int screenW = 600;
	const int screenH = 240;
	START_WINDOW(screenW,screenH);


	clock_t *relogio;
	relogio = malloc ( sizeof ( clock_t ) *10 );

	Camera camera = { 0 };
	camera = CAMERA_START(&camera);

	AMBIENTE ambiente;
	ambiente.gravidade = 0.2;

	PERSONAGEM personagem;
	ITEM item;
	LOADALL_MODELS(&personagem,&item);
	PERSONAGEM_CONFIGSTART ( &personagem );
	personagem.equip.calcaAtual = item.calca[1].idle;
	msg = malloc ( sizeof ( char ) *50 );
	msg = "Signed Distance Fields";

	Font font = FONT_START(screenH);
	Vector2 fontPosition = { 40, screenH/2.0f - 50 };

	SetTargetFPS ( 60 );

	while ( !WindowShouldClose() )      // Detect window close button or ESC key
	{
		if ( IsMouseButtonDown ( MOUSE_MIDDLE_BUTTON ) == false )
			camera.target = personagem.posicao;

		UpdateCamera ( &camera );
		GRAVIT ( &personagem, &ambiente );

		if ( personagem.usando != false )
		{
			PERSONAGEM_USEANIM ( &personagem );
		}
		else
		{
			TECLADO_MAIN ( &personagem, &item);
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
		if(personagem.equip.calca != 0)
			DrawModelEx ( personagem.equip.calcaAtual, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, WHITE );
		DrawBoundingBox ( personagem.hitbox.use,BLACK );
		DrawModelEx ( personagem.modelo.atual, personagem.posicao, ( Vector3 ){0.0f, 1.0f,0.0f}, personagem.rotacao, ( Vector3 ){1.0f, 1.0f,1.0f}, WHITE );
		DrawGrid ( 10, 1.0f );

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
