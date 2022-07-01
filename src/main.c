//LIB C
#include <time.h>
#include <locale.h>

//ENGINE
#include "./1964/1964.h"

int main(void)
{
    InitAudioDevice();
    maintheme = LoadMusicStream("./data/audio/music/main.mp3");
    setlocale(LC_ALL, "Portuguese");

    remove("./data/temp/lang");
    abinCoreFileCopy("./data/lang/ptbr/text.text", "./data/temp/lang");
    
    if(strcmp(abinCoreReturnData("./config.text", "MSAA"), "true") == 0)
        SetConfigFlags(FLAG_MSAA_4X_HINT);
    if(strcmp(abinCoreReturnData("./config.text", "RESIZE"), "true") == 0)
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    DATA data;
    MQCleanAllRenderSlots(&data);
    MQWindowStart();

    data.session.render.camera = MQCameraStart(&data.session.render.camera);
    data.session.render.background = (Color){115, 105, 97, 255};
    data.session.ModelCount = 0;
    data.session.HitboxCount = 0;
    data.session.LangCount = 0;
    data.session.TextCount = 0;
    data.session.frame = 0;
 
    MQLoadLangFromFile(&data,"./data/temp/lang");
    MQLoadAllModels(&data);
    MQPlayerConfigStart(&data, 0, (Vector3) {-0.0625, 5, 6.0625});
    data.file.font[0] = MQFontStart("data/font/acentos/KyrillaSansSerif-Bold.ttf", 16);
    data.file.font[1] = MQFontStart("data/font/Mockery.ttf", 48);
    data.file.font[2] = MQFontStart("data/font/Mockery.ttf", 24);
    SetTargetFPS(60);
    MQEXIT = MQMenu(&data,0);
    
    data.session.render.camera.target = (Vector3)
    {
        data.file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp", "player0-cabeca"))].min.x, data.file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp", "player0-cabeca"))].min.y, data.file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp", "player0-cabeca"))].min.z
    };
    SetExitKey(KEY_END);
    data.session.render.camera.position = (Vector3){0.4375, 3.5, 11.0625};
    MQRenderAddModelToQueue(&data, "mapa0", atoi(abinCoreReturnData("./data/temp/model.temp", "map0")), WHITE,(Vector3){0.0f, 0.0f, 0.0f}, 0,  0,0,true,false,false);
    MQRenderAddModelToQueue(&data, "player0", MQFindModelByName(data,"player"), COR_PELE0,data.game.posicao.personagem[0], data.game.rotacao.personagem[0],  0,0,true,true,false);
    while(!WindowShouldClose() && !MQEXIT)
    {
        data.session.render.camera.target = (Vector3)
        {
            data.file.hitbox[MQFindHitboxByName(data, "player0-cabeca")].min.x, data.file.hitbox[MQFindHitboxByName(data, "player0-cabeca")].min.y, data.file.hitbox[MQFindHitboxByName(data, "player0-cabeca")].min.z
        };
        data.session.frame++;
        UpdateCamera(&data.session.render.camera);
        data.session.render.model[MQFindRenderModelIndexByID(data,"player0")].position = data.game.posicao.personagem[0];
        data.session.render.model[MQFindRenderModelIndexByID(data,"player0")].rotation = data.game.rotacao.personagem[0];
        TECLADO_MAIN(&data);
        MQPlayerUpdateBodyBox( &data, 0, data.session.render.model[MQFindRenderModelIndexByID(data,"player0")].currentAnim);
        
        if((int)data.game.rotacao.personagem[0]%360 == 0)
            data.game.rotacao.personagem[0] = 0;

        if(MQReturnYMaxCollisionPoint(data, data.game.posicao.personagem[0]) == MQFALSE)
        {
            data.game.posicao.personagem[0].y = MQGravit(data.game.posicao.personagem[0], 0.1, data.game.ponteiro.personagem[0].tempoGravit);
            data.game.ponteiro.personagem[0].tempoGravit++;
        }
        else 
        {
            data.game.posicao.personagem[0].y = MQReturnYMaxCollisionPoint(data, data.game.posicao.personagem[0]);
            data.game.ponteiro.personagem[0].tempoGravit = 0;
        }
        MQRender(&data);
    }
    CloseAudioDevice();
    remove("./data/temp/lang.text");
    CloseWindow();          
    // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
