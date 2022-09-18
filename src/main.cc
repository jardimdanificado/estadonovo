#include "maqquina/maqquina.hh"
namespace __startup
{
	void loadPlayerBase(qProgram::qData::qFile *inFile)
	{
		inFile->autoLoadModel("player","player","./assets/models/player/model.iqm",true);
		
		inFile->autoLoadModel("player-barriga","player-hitbox","./assets/models/player/body/barriga.iqm",true);
		inFile->autoLoadModel("player-bracodireito","player-hitbox","./assets/models/player/body/bracodireito.iqm",true);
		inFile->autoLoadModel("player-bracoesquerdo","player-hitbox","./assets/models/player/body/bracoesquerdo.iqm",true);
		inFile->autoLoadModel("player-cabeca","player-hitbox","./assets/models/player/body/cabeca.iqm",true);
		inFile->autoLoadModel("player-pernadireita","player-hitbox","./assets/models/player/body/coxadireita.iqm",true);
		inFile->autoLoadModel("player-pernaesquerda","player-hitbox","./assets/models/player/body/coxaesquerda.iqm",true);
		inFile->autoLoadModel("player-maodireita","player-hitbox","./assets/models/player/body/maodireita.iqm",true);
		inFile->autoLoadModel("player-maoesquerda","player-hitbox","./assets/models/player/body/maoesquerda.iqm",true);
		inFile->autoLoadModel("player-ombrodireito","player-hitbox","./assets/models/player/body/ombrodireito.iqm",true);
		inFile->autoLoadModel("player-ombroesquerdo","player-hitbox","./assets/models/player/body/ombroesquerdo.iqm",true);
		inFile->autoLoadModel("player-peitoral","player-hitbox","./assets/models/player/body/peitoral.iqm",true);
		inFile->autoLoadModel("player-pedireito","player-hitbox","./assets/models/player/body/pernadireta.iqm",true);
		inFile->autoLoadModel("player-peesquerda","player-hitbox","./assets/models/player/body/pernaesquerda.iqm",true);
		inFile->autoLoadModel("player-pescoco","player-hitbox","./assets/models/player/body/pescoco.iqm",true);
	};
	
	void loadMap0(qProgram::qData::qFile *inFile)
	{
		inFile->autoLoadModel("map0","map","./assets/models/map/level0/0.glb");
		for(int i = 0;i<10;i++)
			inFile->autoCreateHitboxFromModel(TextFormat("map0%d",i),"map", TextFormat("./assets/models/map/level0/hitbox/hitbox%d.glb",i), true);
	};

	void loadAll(qProgram::qData::qFile *inFile)
	{
	    loadPlayerBase(*&inFile);
		loadMap0(*&inFile);
	};

	void setRenderModels(qProgram::qData *inData)
	{
		qProgram::qData::qFile::qModel *localmap0 = inData->file.findGetModel("map0");
		qProgram::qData::qFile::qModel *localplayer = inData->file.findGetModel("player");
		
		//add map to render	
	    inData->session.render.scene.autoCreateModel("mapa","map", localmap0->getModel(), localmap0->getAnim(), true, inData->world->map.getPosition(), inData->world->map.getRotation());
		//add player model to render
	    inData->session.render.scene.autoCreateModel("player0", "player", localplayer->getModel(), localplayer->getAnim(),true , inData->world->creature->player[0]->getPosition(), inData->world->creature->player[0]->getRotation(), 0, (Color){127,100,0,255});	
	};
}

void mainLoop (qProgram *estado)
{
	estado->data.session.render.scene.findGetModel("player0")->frame();
};

int main(void)
{
    qProgram *estado = new qProgram(800,800,"Estado Novo");
	__startup::loadAll(&estado->data.file);
	__startup::setRenderModels(&estado->data);

	estado->keyboard.layout.gameplay.useLayout(estado);
	
    while (!WindowShouldClose())
        estado->run(&mainLoop);

    return 0;
}
