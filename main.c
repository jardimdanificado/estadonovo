//LIB C
#include <time.h>
#include <locale.h>
#include "src/abin/abindependencies.h"
char *msg, msg_simples[512];

//RAYLIB
#include "src/raylib/raylib.h"
#include "src/raylib/raymath.h"

//ABIN Files
#include "src/abin/abin.h"

Music maintheme;

//ENGINE
#include "src/1964/1964.h"

//PROJECT SPECIFIC
#include "src/map/map.c"
#include "src/system/teclado.c"


int main(void)
{
    InitAudioDevice();
    maintheme = LoadMusicStream("./data/audio/music/main.mp3");
    setlocale(LC_ALL, "Portuguese");
    int screenH, screenW;
    char *bufferScrSz, *langstartbuffer;
    bufferScrSz = malloc(30);
    strcpy(bufferScrSz, abinCoreReturnData("config.text", "SCRY"));
    screenH = atoi(bufferScrSz);
    strcpy(bufferScrSz, abinCoreReturnData("config.text", "SCRX"));
    screenW = atoi(bufferScrSz);
    free(bufferScrSz);
    langstartbuffer = malloc(27);
    bufferScrSz = malloc(4);
    strcpy(bufferScrSz, abinCoreReturnData("config.text", "LANG"));
    snprintf(langstartbuffer, 27, "./data/lang/%s/text.text", bufferScrSz);
    if(abinCoreFileCheck(langstartbuffer) == false)
    {
        abinCoreEditData("config.text", "LANG", "ptbr");
    }
    strcpy(bufferScrSz, abinCoreReturnData("config.text", "LANG"));
    snprintf(langstartbuffer, 27, "./data/lang/%s/text.text", bufferScrSz);
    abinCoreFileCopy(langstartbuffer, "./data/temp/lang.text");
    free(bufferScrSz);
    free(langstartbuffer);
    DATA data;

    if(strcmp(abinCoreReturnData("./config.text", "MSAA"), "true") == 0)
        SetConfigFlags(FLAG_MSAA_4X_HINT);
    if(strcmp(abinCoreReturnData("./config.text", "RESIZE"), "true") == 0)
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    MQWindowStart();
    clock_t *relogio;
    relogio = malloc(sizeof(clock_t) * 10);
    Camera camera = MQCameraStart(&camera);

    data.session.ObjCount = 0;
    data.session.AnimCount = 0;
    data.session.HitboxCount = 0;
    data.game.contador.frames.personagem[0] = 0;
    MENU menu;
    menu.estaAberto = true;
    AMBIENTE ambiente;
    ambiente.gravidade = 0.2;
    MQLoadAllModels(&data);
    MQPlayerConfigStart(&data, 0, (Vector3) {-0.0625, 5, 6.0625});
    MAPA_START(&data);
    msg = malloc(sizeof(char) * 255);
    //msg = " ";
    Font font = MQFontStart("data/font/acentos/KyrillaSansSerif-Bold.ttf", 16);
    Font fontTitle = MQFontStart("data/font/Mockery.ttf", 48);
    Font fontSubTitle = MQFontStart("data/font/Mockery.ttf", 24);
    LOGO logo;
    logo.ponteiro = 0;
    logo.relogio = 0;
    logo.relogiosub = 0;
    logo.relogiosubDef = 0;
    logo.pisca = false;
    logo.piscaPonteiro = 0;
    MQEXIT = MQMenu("data/menu/start.menu", true,  &data, font, fontTitle, fontSubTitle, &logo,  screenH);
    SetTargetFPS(60);
    camera.target = (Vector3)
    {
        data.file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp", "player-cabeca"))].min.x, data.file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp", "player-cabeca"))].min.y, data.file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp", "player-cabeca"))].min.z
    };
    SetExitKey(KEY_END);
    Vector3 Vec3buff;
    while(!WindowShouldClose() && MQEXIT == false)
    {
        camera.target = (Vector3)
        {
            data.file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp", "player-cabeca"))].min.x, data.file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp", "player-cabeca"))].min.y, data.file.hitbox[atoi(abinCoreReturnData("./data/temp/hitbox.temp", "player-cabeca"))].min.z
        };

        /* Vec3buff = MQCheckWall(data,"player-cabeca",data.game.rotacao.personagem[0]);
        if(Vec3buff.x != __INT_MAX__)
        {
            if(data.game.posicao.personagem[0].x+0.2 > Vec3buff.x&&data.game.posicao.personagem[0].x-2<Vec3buff.x)
                data.game.posicao.personagem[0].x = Vec3buff.x;
        } 
        if(Vec3buff.z != __INT_MAX__)
        {
            if(data.game.posicao.personagem[0].z+0.2 > Vec3buff.z&&data.game.posicao.personagem[0].z-2<Vec3buff.z)
                data.game.posicao.personagem[0].z = Vec3buff.z;
        } */

        SetExitKey(KEY_END);
        if(menu.esc == false)
        {
            UpdateCamera(&camera);

            TECLADO_MAIN(&menu, font, fontTitle, fontSubTitle, logo, &data);

            if(data.game.rotacao.personagem[0] / 360 == 0)
                data.game.rotacao.personagem[0] = 0;

            if(MQCheckFloorFromHeight(data, data.game.posicao.personagem[0].y - (3 / 60)) == false)
            {
                if(MQReturnFloorCollisionPoint(data, "player-pernae") == MQFALSE)
                {
                    data.game.posicao.personagem[0].y = MQGravit(data.game.posicao.personagem[0], 1, data.game.ponteiro.personagem[0].tempoGravit);
                    data.game.ponteiro.personagem[0].lastFloorHeight = data.game.posicao.personagem[0].y;
                    data.game.ponteiro.personagem[0].tempoGravit++;
                }
                else if(data.game.ponteiro.personagem[0].lastFloorHeight != data.game.posicao.personagem[0].y)
                {
                    data.game.posicao.personagem[0].y = MQReturnFloorCollisionPoint(data, "player-pernae");
                    data.game.ponteiro.personagem[0].tempoGravit = 0;
                }
            }

            for(int i = 0; i < MAXOBJ; i++)
            {
                if(data.file.mapa.porta.slots[i].abrindo || data.file.mapa.porta.slots[i].fechando)
                {
                    if(data.file.mapa.porta.slots[i].existe == true)
                        MQDoorAnim(&data);
                }
            }
            snprintf(msg,255,"%d",data.game.ponteiro.personagem[0].tempoGravit);
            MQRender(&data, camera, font, menu);
        }
        else if(menu.esc == true)
        {
            data.game.boolean.personagem[0].pulando = false;
            data.game.boolean.personagem[0].andando = false;
            MQEXIT = MQMenu("data/menu/esc.menu", false,  &data, font, fontTitle, fontSubTitle, &logo,  screenH);
            menu.esc = false;
        }
    }
    CloseAudioDevice();
    remove("./data/temp/lang.text");
    free(relogio);
    free(msg);
    UnloadFont(font);
    UnloadFont(fontTitle);
    UnloadFont(fontSubTitle);
    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
