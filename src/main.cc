
#include "maqquina/maqquina.hh"

void mainLoop (PROGRAM::DATA *inData)
{

};

void keyWDown(PROGRAM::DATA *inData)
{
    printf("\npegou\n");
}

int main(void)
{
    PROGRAM estado;

    estado.start(800,600,"Estado Novo");
    
    estado.data.session.render.scene.autoCreateModel("mapa","map",estado.data.file.findGetModel("map0")->getModel(),estado.data.game.map.getPosition(),estado.data.game.map.getRotation(),true);
    estado.data.session.render.scene.autoCreateModel("player0", "player", estado.data.file.findGetModel("player")->getModel(),estado.data.game.player[0].getPosition(),estado.data.game.player[0].getRotation(),true);
    estado.setLoop(mainLoop);
    estado.keyboard.setKeyFunc(keyWDown,KEY_W,KDOWN);
    while (!WindowShouldClose())
        estado.run();
    return 0;
}
