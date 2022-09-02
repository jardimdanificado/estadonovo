
#include "maqquina/maqquina.hh"

void mainLoop (PROGRAM::DATA *inData)
{

};

namespace __keyboard
{
    void keyWDown(PROGRAM::DATA *inData)
    {
        inData->game.player[0].move();
    }
    void keySDown(PROGRAM::DATA *inData)
    {
        if(inData->game.player[0].getRotation()->y == 360)
            
        inData->game.player[0].move(true);
    }
    void keyADown(PROGRAM::DATA *inData)
    {
        inData->game.player[0].rotate();
    }
    void keyDDown(PROGRAM::DATA *inData)
    {
        inData->game.player[0].rotate(true);
    }
};

int main(void)
{
    PROGRAM *estado = new PROGRAM(800,800,"Estado Novo");
    estado->setLoop(mainLoop);


    estado->data.session.render.scene.autoCreateModel("mapa","map",estado->data.file.findGetModel("map0")->getModel(),estado->data.game.map.getPosition(),estado->data.game.map.getRotation(),true);
    estado->data.session.render.scene.autoCreateModel("player0", "player", estado->data.file.findGetModel("player")->getModel(),estado->data.game.player[0].getPosition(),estado->data.game.player[0].getRotation(),true);
    
    estado->keyboard.setKeyFunc(__keyboard::keyWDown,KEY_W,KEYEVENT_DOWN);
    estado->keyboard.setKeyFunc(__keyboard::keySDown,KEY_S,KEYEVENT_DOWN);
    estado->keyboard.setKeyFunc(__keyboard::keyADown,KEY_A,KEYEVENT_DOWN);
    estado->keyboard.setKeyFunc(__keyboard::keyDDown,KEY_D,KEYEVENT_DOWN);
    while (!WindowShouldClose())
        estado->run();
    return 0;
}
