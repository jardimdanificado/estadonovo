#include "maqquina/maqquina.hh"
namespace __startup
{
	void loadPlayerBase(qProgram::qData *inData)
	{
		inData->file.autoLoadModel("player","player","./assets/models/player/model.iqm",true);
		
		inData->file.autoLoadModel("player-barriga","player-hitbox","./assets/models/player/body/barriga.iqm",true);
		inData->file.autoLoadModel("player-bracodireito","player-hitbox","./assets/models/player/body/bracodireito.iqm",true);
		inData->file.autoLoadModel("player-bracoesquerdo","player-hitbox","./assets/models/player/body/bracoesquerdo.iqm",true);
		inData->file.autoLoadModel("player-cabeca","player-hitbox","./assets/models/player/body/cabeca.iqm",true);
		inData->file.autoLoadModel("player-coxadireita","player-hitbox","./assets/models/player/body/coxadireita.iqm",true);
		inData->file.autoLoadModel("player-coxaesquerda","player-hitbox","./assets/models/player/body/coxaesquerda.iqm",true);
		inData->file.autoLoadModel("player-maodireita","player-hitbox","./assets/models/player/body/maodireita.iqm",true);
		inData->file.autoLoadModel("player-maoesquerda","player-hitbox","./assets/models/player/body/maoesquerda.iqm",true);
		inData->file.autoLoadModel("player-ombrodireito","player-hitbox","./assets/models/player/body/ombrodireito.iqm",true);
		inData->file.autoLoadModel("player-ombroesquerdo","player-hitbox","./assets/models/player/body/ombroesquerdo.iqm",true);
		inData->file.autoLoadModel("player-peitoral","player-hitbox","./assets/models/player/body/peitoral.iqm",true);
		inData->file.autoLoadModel("player-pernadireta","player-hitbox","./assets/models/player/body/pernadireta.iqm",true);
		inData->file.autoLoadModel("player-pernaesquerda","player-hitbox","./assets/models/player/body/pernaesquerda.iqm",true);
		inData->file.autoLoadModel("player-pescoco","player-hitbox","./assets/models/player/body/pescoco.iqm",true);
	};
	
	void loadMap0(qProgram::qData *inData)
	{
		inData->file.autoLoadModel("map0","map","./assets/models/map/level0/0.glb");
		for(int i = 0;i<10;i++)
			inData->file.autoCreateHitboxFromModel(TextFormat("map0%d",i),"map", TextFormat("./assets/models/map/level0/hitbox/hitbox%d.glb",i), true);
	};

	void loadAll(qProgram::qData *inData)
	{
	    loadPlayerBase(*&inData);
		loadMap0(*&inData);
	};

	void setRenderModels(qProgram::qData *inData)
	{
		qProgram::qData::qFile::qModel *localmap0 = inData->file.findGetModel("map0");
		qProgram::qData::qFile::qModel *localplayer = inData->file.findGetModel("player");
		
		//add map to render	
	    inData->session.render.scene.autoCreateModel("mapa","map", localmap0->getModel(), localmap0->getAnim(), true, inData->game.map.getPosition(), inData->game.map.getRotation());
		//add player model to render
	    inData->session.render.scene.autoCreateModel("player0", "player", localplayer->getModel(), localplayer->getAnim(),true , inData->game.player[0].getPosition(), inData->game.player[0].getRotation(), 0, (Color){127,100,0,255});	
	};
}

namespace __keyboard
{
	void keyWUp(qProgram::qData *inData){inData->session.render.scene.findGetModel("player0")->currentAnim = 0;};
	void keySUp(qProgram::qData *inData){inData->session.render.scene.findGetModel("player0")->currentAnim = 0;};
    void keyWDown(qProgram::qData *inData)
    {
    	inData->session.render.scene.findGetModel("player0")->currentAnim = 1;
        inData->game.player[0].move();
        
    };
    void keySDown(qProgram::qData *inData)
    {
    	inData->session.render.scene.findGetModel("player0")->currentAnim = 1;
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
   	    estado->keyboard.setKeyFunc(keyWUp,KEY_W,KEY_EVENT::RELEASED);
   	    estado->keyboard.setKeyFunc(keySUp,KEY_S,KEY_EVENT::RELEASED);
   	    estado->keyboard.setKeyFunc(keyWDown,KEY_W,KEY_EVENT::DOWN);
	    estado->keyboard.setKeyFunc(keySDown,KEY_S,KEY_EVENT::DOWN);
	    estado->keyboard.setKeyFunc(keyADown,KEY_A,KEY_EVENT::DOWN);
	    estado->keyboard.setKeyFunc(keyDDown,KEY_D,KEY_EVENT::DOWN);
    };
};


void mainLoop (qProgram::qData *inData)
{
	inData->session.render.scene.findGetModel("player0")->frame();
};

int main(void)
{
    qProgram *estado = new qProgram(800,800,"Estado Novo");
	__startup::loadAll(&estado->data);
	__startup::setRenderModels(&estado->data);

    estado->setLoop(mainLoop);
	__keyboard::setKeyboard(estado);
	
    while (!WindowShouldClose())
        estado->run();

    return 0;
}
