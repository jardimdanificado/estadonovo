//ENGINE
#include "./maquina/maquina.h"

#ifndef PLATFORM_ANDROID
	ChangeDirectory("assets");
#endif

int main(void)
{
    MQDATA data;
    MQResetAllFileSlots(&data);
    MQWindowStart(abinCoreReturnData("config.text", "TITLE"));
    MQCleanAllRenderSlots(&data);
    MQCleanAllEventSlots(&data);
    
    MQCleanAllMapItemSlots(&data);
    data.session.render.camera = MQCameraStart(&data.session.render.camera);
    data.session.render.background = (Color){115, 105, 97, 255};
    data.session.frame = 0;
    MQLoadLang(&data,"ptbr");
    
    MQPlayerConfigStart(&data, 0, (Vector3) {-0.0625, 5, 6.0625});
    data.files.fonts[0].font= MQFontStart("data/font/acentos/KyrillaSansSerif-Bold.ttf", 16);
    data.files.fonts[1].font= MQFontStart("data/font/Mockery.ttf", 48);
    data.files.fonts[2].font= MQFontStart("data/font/Mockery.ttf", 24);
    SetTargetFPS(60);

    data.files.musics[0].music = LoadMusicStream("./data/audio/music/maintheme_by_kayoa.mp3");
    MQEXIT = MQMenu(&data,0);
    MQLoadAllModels(&data);
    data.session.render.camera.target = (Vector3)
    {
        data.files.hitboxes[MQFindHitbox(data, "player-cabeca0")].hitbox.min.x, data.files.hitboxes[MQFindHitbox(data, "player-cabeca0")].hitbox.min.y, data.files.hitboxes[MQFindHitbox(data, "player-cabeca0")].hitbox.min.z
    };
    SetExitKey(KEY_END);
    data.session.render.camera.position = (Vector3){0.4375, 3.5, 11.0625};
    MQRenderAddModelToQueue(&data, "mapa0", MQFindModelByName(data,"map0"), WHITE,(Vector3){0.0f, 0.0f, 0.0f}, 0,  0,0,true,false,false);
    MQRenderAddModelToQueue(&data, "player0", MQFindModelByName(data,"player"), COR_PELE0,data.game.player[0].position, data.game.player[0].rotation,  0,0,true,true,false);
    
    data.files.eventboxes[0].hitbox.min = (Vector3){-0.5,0,-0.5};
    data.files.eventboxes[0].hitbox.max = (Vector3){0.5,2.3,0.5};
    MQCreateEventbox(&data, "playeruse",data.files.eventboxes[0].hitbox);
    MQAddEventToQueue(&data,"playeruse0",MQTRUE,data.files.eventboxes[MQFindEventbox(data,"playeruse")].hitbox,(Vector3){0,0,0},0,true,false);

    MQAddMapItemToQueue(&data,"teste",0,1,(Vector3){0,0,0},0,0,0,(BoundingBox){(Vector3){0,0,0},(Vector3){1,1,1}},true);
    while(!WindowShouldClose() && !MQEXIT)
    {
        data.session.render.camera.target = (Vector3){data.files.hitboxes[MQFindHitbox(data, "player-cabeca0")].hitbox.min.x, data.files.hitboxes[MQFindHitbox(data, "player-cabeca0")].hitbox.min.y, data.files.hitboxes[MQFindHitbox(data, "player-cabeca0")].hitbox.min.z};
        data.session.frame++;
        UpdateCamera(&data.session.render.camera);
        data.session.render.model[MQFindRenderModel(data,"player0")].position = data.game.player[0].position;
        data.session.render.model[MQFindRenderModel(data,"player0")].rotation = data.game.player[0].rotation;
        data.game.event[MQFindEvent(data,"playeruse0")].position = data.game.player[0].position;

        TECLADO_MAIN(&data);
        MQPlayerUpdateBodyBox( &data, 0, data.session.render.model[MQFindRenderModel(data,"player0")].currentAnim);
        
        if((int)data.game.player[0].rotation%360 == 0)
            data.game.player[0].rotation = 0;

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
