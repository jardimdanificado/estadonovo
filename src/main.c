//LIB C

//ENGINE
#include "./1964/1964.h"

int main(void)
{
    DATA data;
    MQWindowStart(abinCoreReturnData("config.text", "TITLE"));
    MQCleanAllRenderSlots(&data);
    MQCleanAllEventSlots(&data);
    data.session.render.camera = MQCameraStart(&data.session.render.camera);
    data.session.render.background = (Color){115, 105, 97, 255};
    data.session.counter.model = 0;
    data.session.counter.hitbox = 0;
    data.session.counter.lang = 0;
    data.session.counter.text = 0;
    data.session.counter.eventbox = 0;
    data.session.frame = 0;
    MQLoadLang(&data,"ptbr");
    MQLoadAllModels(&data);
    MQPlayerConfigStart(&data, 0, (Vector3) {-0.0625, 5, 6.0625});
    data.file.font[0] = MQFontStart("data/font/acentos/KyrillaSansSerif-Bold.ttf", 16);
    data.file.font[1] = MQFontStart("data/font/Mockery.ttf", 48);
    data.file.font[2] = MQFontStart("data/font/Mockery.ttf", 24);
    SetTargetFPS(60);

    
    data.file.audio[0] = LoadMusicStream("./data/audio/music/maintheme_by_kayoa.mp3");
    MQEXIT = MQMenu(&data,0);
    
    data.session.render.camera.target = (Vector3)
    {
        data.file.hitbox[MQFindHitboxByName(data, "player-cabeca0")].min.x, data.file.hitbox[MQFindHitboxByName(data, "player-cabeca0")].min.y, data.file.hitbox[MQFindHitboxByName(data, "player-cabeca0")].min.z
    };
    SetExitKey(KEY_END);
    data.session.render.camera.position = (Vector3){0.4375, 3.5, 11.0625};
    MQRenderAddModelToQueue(&data, "mapa0", MQFindModelByName(data,"map0"), WHITE,(Vector3){0.0f, 0.0f, 0.0f}, 0,  0,0,true,false,false);
    MQRenderAddModelToQueue(&data, "player0", MQFindModelByName(data,"player"), COR_PELE0,data.game.personagem[0].posicao, data.game.personagem[0].rotacao,  0,0,true,true,false);
    
    data.file.eventbox[data.session.counter.eventbox].min = (Vector3){-0.5,0,-0.5};
    data.file.eventbox[data.session.counter.eventbox].max = (Vector3){0.5,2,1};
    MQCreateEventbox(&data, "playeruse",data.file.eventbox[data.session.counter.eventbox]);
    MQAddEventToQueue(&data,"playeruse0",MQTRUE,data.file.eventbox[MQFindEventboxIndexByName(data,"playeruse")],(Vector3){0,0,0},0,true);

    while(!WindowShouldClose() && !MQEXIT)
    {
        data.session.render.camera.target = (Vector3){data.file.hitbox[MQFindHitboxByName(data, "player-cabeca0")].min.x, data.file.hitbox[MQFindHitboxByName(data, "player-cabeca0")].min.y, data.file.hitbox[MQFindHitboxByName(data, "player-cabeca0")].min.z};
        data.session.frame++;
        UpdateCamera(&data.session.render.camera);


        data.session.render.model[MQFindRenderModelIndexByName(data,"player0")].position = data.game.personagem[0].posicao;
        data.session.render.model[MQFindRenderModelIndexByName(data,"player0")].rotation = data.game.personagem[0].rotacao;
        data.session.event[MQFindEventIndexByName(data,"playeruse0")].position = data.game.personagem[0].posicao;

        TECLADO_MAIN(&data);
        MQPlayerUpdateBodyBox( &data, 0, data.session.render.model[MQFindRenderModelIndexByName(data,"player0")].currentAnim);
        
        if((int)data.game.personagem[0].rotacao%360 == 0)
            data.game.personagem[0].rotacao = 0;

        MQGravit(&data, 0);
        MQRenderQueue(&data);
    }
    CloseAudioDevice();
    remove("./data/temp/lang");
    CloseWindow();          
    // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
