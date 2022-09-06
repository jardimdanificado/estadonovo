
#include "maqquina/maqquina.hh"

void mainLoop (qProgram::qData *inData)
{

};

namespace __keyboard
{
    void keyWDown(qProgram::qData *inData)
    {
        inData->game.player[0].move();
    }
    void keySDown(qProgram::qData *inData)
    {
        inData->game.player[0].move(true);
    }
    void keyADown(qProgram::qData *inData)
    {
        inData->game.player[0].setRotationY(qMath::round360(inData->game.player[0].getRotation()->y));
        inData->game.player[0].rotate();
    }
    void keyDDown(qProgram::qData *inData)
    {
        inData->game.player[0].setRotationY(qMath::round360(inData->game.player[0].getRotation()->y));
        inData->game.player[0].rotate(true);
    }
};

int main(void)
{
    qProgram *estado = new qProgram(800,800,"Estado Novo");
    estado->setLoop(mainLoop);

    estado->data.session.render.scene.autoCreateModel("mapa","map",estado->data.file.findGetModel("map0")->getModel(),estado->data.game.map.getPosition(),estado->data.game.map.getRotation(),true);
    estado->data.session.render.scene.autoCreateModel("player0", "player", estado->data.file.findGetModel("player")->getModel(),estado->data.game.player[0].getPosition(),estado->data.game.player[0].getRotation(),true,0,(Color){127,100,0,255});
    
    estado->keyboard.setKeyFunc(__keyboard::keyWDown,KEY_W,KEY_EVENT::DOWN);
    estado->keyboard.setKeyFunc(__keyboard::keySDown,KEY_S,KEY_EVENT::DOWN);
    estado->keyboard.setKeyFunc(__keyboard::keyADown,KEY_A,KEY_EVENT::DOWN);
    estado->keyboard.setKeyFunc(__keyboard::keyDDown,KEY_D,KEY_EVENT::DOWN);
    while (!WindowShouldClose())
        estado->run();
    return 0;
}
