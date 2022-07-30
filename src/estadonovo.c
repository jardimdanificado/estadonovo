//ENGINE
#include "maquina/maquina.h"

int main(void)
{
    MQDATA data;
    MQStart(&data);
    
    MQNewPlayer(&data, 0, (Vector3) {-0.0625, 5, 6.0625});
    
    //start menu
    MQMenu(&data,0);
    data.session.render.camera.target = (Vector3)
    {
        data.files.hitboxes[MQFindHitbox(data, "player-cabeca0")].hitbox.min.x, data.files.hitboxes[MQFindHitbox(data, "player-cabeca0")].hitbox.min.y, data.files.hitboxes[MQFindHitbox(data, "player-cabeca0")].hitbox.min.z
    };
    data.session.render.camera.position = (Vector3){0.4375, 3.5, 11.0625};
    
    MQAddRenderModelToQueue(&data, MQCreateRenderModel(false,false,true,MQFindModelByName(data,"map0"),0,0,WHITE,(Vector3){0,0,0},0,"map0"));
    MQAddRenderModelToQueue(&data, MQCreateRenderModel(true,true,false,MQFindModelByName(data,"player"),0,0,COR_PELE0,data.game.player[0].position,data.game.player[0].rotation,"player0"));    
    data.files.eventboxes[0].hitbox = (BoundingBox){(Vector3){-0.5,0,-0.5},(Vector3){0.5,2.3,0.5}};

    MQCreateEventbox(&data, "playeruse",data.files.eventboxes[0].hitbox);
    MQAddEventToQueue(&data,"playeruse0",MQTrue,data.files.eventboxes[MQFindEventbox(data,"playeruse")].hitbox,(Vector3){0,0,0},0,true,false);

    MQAddItemToMapQueue(&data,MQCreateItem("teste","calca",1,(Vector3){0,0,0},0,0,0,0,(BoundingBox){(Vector3){0,0,0},(Vector3){1,1,1}},false,true));
    while(!WindowShouldClose() && !data.session.exit)
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
    CloseWindow();          
    // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
