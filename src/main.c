#include <raylib.h>
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

struct HITBOX_PERSONAGEM
{
	// 0
	BoundingBox use,useR,atual;
	Model modelo;
};
typedef struct HITBOX_PERSONAGEM HITBOX_PERSONAGEM;

struct MODELO_PERSONAGEM
{
	// 0
	Model idle;
	// 1-5
	Model run[5];
	Model use_default[3];
	Model atual;
	int frame;
};
typedef struct MODELO_PERSONAGEM MODELO_PERSONAGEM;

struct MINMAX
{
	float min, max;
};
typedef struct MINMAX MINMAX;

struct PERSONAGEM
{
    Vector3 posicao;
	MODELO_PERSONAGEM modelo;
	//BOUNDS bounds;
	HITBOX_PERSONAGEM hitbox;
	float rotacao;
	float velocidade, velocidadePulo;
	clock_t relogioVelho, relogioNovo, pulo;
	bool pulando, usando;
};
typedef struct PERSONAGEM PERSONAGEM;




char *msg;


#include "core/et.c"

#include "personagem.h"
#include "ambiente.h"
//#include "core/font.c"
#include "core/teclado.c"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 600;
    const int screenHeight = 240;
	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	time_t *seconds = MemAlloc(sizeof(time_t));
	char *textotitulo = MemAlloc(sizeof(char)*40);
	*seconds = time(NULL);
	sprintf(textotitulo,"19.64-%ld",*seconds);
    InitWindow(screenWidth, screenHeight, textotitulo);
	MemFree(seconds);
	MemFree(textotitulo);


	clock_t *relogio;
	relogio = malloc(sizeof(clock_t)*10);

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 30.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;
	// Camera mode type

	//TEXTO texto;
    // Load some models
    //Model model[MAX_GLTF_MODELS] = { 0 };
	//check
	AMBIENTE ambiente;
	ambiente.gravidade = 0.2;
	PERSONAGEM personagem;
    //int currentModel = 0;
	PERSONAGEM_CONFIGSTART(&personagem);
	msg = malloc(sizeof(char)*50);


    SetCameraMode(camera, CAMERA_FREE); // Set free camera mode


	//FONT_START(&texto.font,0);
	//texto.tamanho = 30;
	//texto.posicao =(Vector2) { 0,0};


	msg = "Signed Distance Fields";

    // Loading file to memory
    unsigned int fileSize = 0;
    unsigned char *fileData = LoadFileData("data/font/anonymous_pro_bold.ttf", &fileSize);
	Vector2 fontSubPosi;

	fontSubPosi.x = 0;
	fontSubPosi.y = screenHeight -16;
    // Default font generation from TTF font
    Font fontDefault = { 0 };
    fontDefault.baseSize = 16;
    fontDefault.glyphCount = 95;

    // Loading font data from memory data
    // Parameters > font size: 16, no glyphs array provided (0), glyphs count: 95 (autogenerate chars array)
    fontDefault.glyphs = LoadFontData(fileData, fileSize, 16, 0, 95, FONT_DEFAULT);

	fontDefault.glyphs = LoadFontData(fileData, fileSize, 16, 0, 95, FONT_DEFAULT);
    // Parameters > glyphs count: 95, font size: 16, glyphs padding in image: 4 px, pack method: 0 (default)
    Image atlas = GenImageFontAtlas(fontDefault.glyphs, &fontDefault.recs, 95, 16, 14, 0);
    fontDefault.texture = LoadTextureFromImage(atlas);
    UnloadImage(atlas);

    // SDF font generation from TTF font
    Font fontSDF = { 0 };
    fontSDF.baseSize = 16;
    fontSDF.glyphCount = 95;
    // Parameters > font size: 16, no glyphs array provided (0), glyphs count: 0 (defaults to 95)
    fontSDF.glyphs = LoadFontData(fileData, fileSize, 16, 0, 0, FONT_SDF);
    // Parameters > glyphs count: 95, font size: 16, glyphs padding in image: 0 px, pack method: 1 (Skyline algorythm)
    atlas = GenImageFontAtlas(fontSDF.glyphs, &fontSDF.recs, 95, 16, 0, 1);
    fontSDF.texture = LoadTextureFromImage(atlas);
    UnloadImage(atlas);

    UnloadFileData(fileData);      // Free memory from loaded file

    // Load SDF required shader (we use default vertex shader)
    //Shader shader = LoadShader(0, TextFormat("data/shaders/sdf.fs", 330));
    SetTextureFilter(fontSDF.texture, TEXTURE_FILTER_POINT);    // Required for SDF font

//     Vector2 fontPosition = { 40, screenHeight/2.0f - 50 };
//     Vector2 textSize = { 0.0f, 0.0f };
//     float fontSize = 16.0f;
//     int currentFont = 0;

    SetTargetFPS(60);

	// Set our game to run at 60 modelo.atuals-per-second
    //--------------------------------------------------------------------------------------
    // Main game loop

    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
		if(IsMouseButtonDown(MOUSE_MIDDLE_BUTTON) == false)
			camera.target = personagem.posicao;


        UpdateCamera(&camera);          // Update our camera with inputs
		GRAVIT(&personagem, &ambiente);

		//personagem.hitbox.atual = GetModelBoundingBox(personagem.modelo.atual);





		//BoundingBox *PersonagemReservaHitboxLocal = MemAlloc(sizeof(BoundingBox));
		//PersonagemReservaHitboxLocal[0] = personagem.hitbox.atual;

		// TECLADO
		// ---------------------------------

		if(personagem.usando != false)
		{
			PERSONAGEM_USEANIM(&personagem);

		}
		else
		{
			TECLADO_MAIN(&personagem);
		}

		if(personagem.rotacao == 360)
			personagem.rotacao=0;

		PERSONAGEM_HITBOXUPDATE(&personagem);

		/*char *localTEXTO = MemAlloc(sizeof(char)*50);
		sprintf(localTEXTO,"x=%f\ny=%f\nz=%f",personagem.posicao.x,personagem.posicao.y,personagem.posicao.z);
		for(int i = 0; i < 49; i ++)
			texto.msg[i] = localTEXTO[i];
		MemFree(localTEXTO);*/

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKBROWN);
			//texto.msg[0] = 'a';
 			DrawTextEx(fontDefault, msg, fontSubPosi, 16, 0, BLACK);

// 			CheckCollisionBoxes();
            BeginMode3D(camera);

				DrawBoundingBox(personagem.hitbox.use,BLACK);
				//DrawBoundingBox(personagem.hitbox.atual,BLACK);
                DrawModelEx(personagem.modelo.atual, personagem.posicao,(Vector3) {0.0f, 1.0f,0.0f}, personagem.rotacao, (Vector3) {1.0f, 1.0f,1.0f}, WHITE);

				DrawGrid(10, 1.0f);         // Draw a grid

            EndMode3D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    //for (int i = 0; i < MAX_GLTF_MODELS; i++) UnloadModel(model[i]);  // Unload models
	UnloadModel(personagem.modelo.idle);
	//UnloadFont(texto.font);
	free(relogio);
	free(msg);
	for (int i = 0; i < sizeof(personagem.modelo.run); i++)
		UnloadModel(personagem.modelo.run[i]);
	for (int i = 0; i < sizeof(personagem.modelo.use_default); i++)
		UnloadModel(personagem.modelo.use_default[i]);
    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
