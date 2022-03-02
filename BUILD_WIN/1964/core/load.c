 


void LOADALL_MODELS(PERSONAGEM* personagem,ITEM* item, MAPA* mapa)
{
	personagem->modelo.idle = LoadModel("./data/models/idle/2.glb");
	personagem->modelo.run[0] = LoadModel("./data/models/run/0.glb");
	personagem->modelo.run[1] = LoadModel("./data/models/run/1.glb");
	personagem->modelo.run[2] = LoadModel("./data/models/run/2.glb");
	personagem->modelo.run[3] = LoadModel("./data/models/run/3.glb");
	personagem->modelo.run[4] = LoadModel("./data/models/run/4.glb");
	personagem->modelo.use_default[0] = LoadModel("./data/models/use_default/0.glb");
	personagem->modelo.use_default[1] = LoadModel("./data/models/use_default/1.glb");
	personagem->modelo.use_default[2] = LoadModel("./data/models/use_default/2.glb");
	item->calca[1].idle = LoadModel("./data/models/equips/calca/1/idle/2.glb");
	item->calca[1].run[0] = LoadModel("./data/models/equips/calca/1/run/0.glb");
	item->calca[1].run[1] = LoadModel("./data/models/equips/calca/1/run/1.glb");
	item->calca[1].run[2] = LoadModel("./data/models/equips/calca/1/run/2.glb");
	item->calca[1].run[3] = LoadModel("./data/models/equips/calca/1/run/3.glb");
	item->calca[1].run[4] = LoadModel("./data/models/equips/calca/1/run/4.glb");
    item->calca[1].use[0] = LoadModel("./data/models/equips/calca/1/use/0.glb");
	item->calca[1].use[1] = LoadModel("./data/models/equips/calca/1/use/1.glb");
	item->calca[1].use[2] = LoadModel("./data/models/equips/calca/1/use/2.glb");
    mapa->modelo[0] = LoadModel("./data/models/map/level0/lvl0.glb");
}

void UNLOADALL_MODELS(PERSONAGEM* personagem, ITEM* item)
{
	UnloadModel(personagem->modelo.idle);
	UnloadModel(item->calca[1].idle);

	for ( int i = 0; i < sizeof ( personagem->modelo.run ); i++ )
		UnloadModel ( personagem->modelo.run[i] );

	for ( int i = 0; i < sizeof ( personagem->modelo.use_default ); i++ )
		UnloadModel ( personagem->modelo.use_default[i] );

	for ( int i = 0; i < sizeof ( personagem->modelo.use_default ); i++ )
		UnloadModel ( item->calca[1].run[i] );

}
