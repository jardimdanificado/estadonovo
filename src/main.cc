
#include "maqquina/maqquina.hh"

void mainLoop()
{

}

int main(void)
{
    PROGRAM estado;
    estado.start(800,600,"Estado Novo");
    estado.data.file.loadModel("./assets/models/map/level0/0.glb","mapa","map");
    estado.data.session.render.scene.autoCreateModel("mapa0","map",estado.data.file.findGetModel("mapa")->getModel(),0,estado.data.game.map.getPosition(),estado.data.game.map.getRotation(),WHITE,true);
    estado.setLoop(mainLoop);
    
    while (!WindowShouldClose())
        estado.run();
    return 0;
}
