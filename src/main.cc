#include "maqquina/maqquina.hh"
namespace __startup
{
	void loadMap0(qProgram::qData *inData)
	{
		inData->file.autoLoadModel("map0","map","./assets/models/map/level0/0.glb");
		for(int i = 0;i<10;i++)
			inData->file.autoCreateHitboxFromModel(TextFormat("map0%d",i),"map", TextFormat("./assets/models/map/level0/hitbox/hitbox%d.glb",i), true);
	};

	void loadAllModels(qProgram::qData *inData)
	{
	    inData->file.autoLoadModel("player","player","./assets/models/player/model.iqm",true);
		loadMap0(*&inData);
	};

	void setRenderModels(qProgram::qData *inData)
	{
		//add map to render	
	    inData->session.render.scene.autoCreateModel("mapa","map", inData->file.findGetModel("map0")->getModel(), inData->game.map.getPosition(), inData->game.map.getRotation(), true);
		//add player model to render
	    inData->session.render.scene.autoCreateModel("player0", "player", inData->file.findGetModel("player")->getModel(), inData->game.player[0].getPosition(), inData->game.player[0].getRotation(), true, 0, (Color){127,100,0,255});	
	};
}

namespace __keyboard
{
    void keyWDown(qProgram::qData *inData)
    {
        inData->game.player[0].move();
    };
    void keySDown(qProgram::qData *inData)
    {
        inData->game.player[0].move(true);
    };
    void keyADown(qProgram::qData *inData)
    {
        inData->game.player[0].setRotationY(qMath::round360(inData->game.player[0].getRotation()->y));
        inData->game.player[0].rotate();
    };
    void keyDDown(qProgram::qData *inData)
    {
        inData->game.player[0].setRotationY(qMath::round360(inData->game.player[0].getRotation()->y));
        inData->game.player[0].rotate(true);
    };
    void setKeyboard(qProgram *estado)
    {
   	    estado->keyboard.setKeyFunc(keyWDown,KEY_W,KEY_EVENT::DOWN);
	    estado->keyboard.setKeyFunc(keySDown,KEY_S,KEY_EVENT::DOWN);
	    estado->keyboard.setKeyFunc(keyADown,KEY_A,KEY_EVENT::DOWN);
	    estado->keyboard.setKeyFunc(keyDDown,KEY_D,KEY_EVENT::DOWN);
    };
};


void mainLoop (qProgram::qData *inData)
{
};


int main(void)
{
    qProgram *estado = new qProgram(800,800,"Estado Novo");
	__startup::loadAllModels(&estado->data);
	__startup::setRenderModels(&estado->data);

    estado->setLoop(mainLoop);
	__keyboard::setKeyboard(estado);
	
    while (!WindowShouldClose())
        estado->run();

    return 0;
}
