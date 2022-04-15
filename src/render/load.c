 


void LOADALL_MODELS(MAPA* mapa,PERSONAGEM* personagem,ITEM* item)
{
	personagem->modelo.idle = LoadModel("./data/models/personagem/idle/2.glb");
	personagem->modelo.run[0] = LoadModel("./data/models/personagem/run/0.glb");
	personagem->modelo.run[1] = LoadModel("./data/models/personagem/run/1.glb");
	personagem->modelo.run[2] = LoadModel("./data/models/personagem/run/2.glb");
	personagem->modelo.run[3] = LoadModel("./data/models/personagem/run/3.glb");
	personagem->modelo.run[4] = LoadModel("./data/models/personagem/run/4.glb");
	personagem->modelo.use_default[0] = LoadModel("./data/models/personagem/use_default/0.glb");
	personagem->modelo.use_default[1] = LoadModel("./data/models/personagem/use_default/1.glb");
	personagem->modelo.use_default[2] = LoadModel("./data/models/personagem/use_default/2.glb");
	personagem->modelo.atirar38 = LoadModel("./data/models/personagem/use_default/x.glb");

	
    
    
    item->chapeu[1].idle = LoadModel("./data/models/equips/chapeu/1/idle/2.glb");
	item->chapeu[1].run[0] = LoadModel("./data/models/equips/chapeu/1/run/0.glb");
	item->chapeu[1].run[1] = LoadModel("./data/models/equips/chapeu/1/run/1.glb");
	item->chapeu[1].run[2] = LoadModel("./data/models/equips/chapeu/1/run/2.glb");
	item->chapeu[1].run[3] = LoadModel("./data/models/equips/chapeu/1/run/3.glb");
	item->chapeu[1].run[4] = LoadModel("./data/models/equips/chapeu/1/run/4.glb");
    item->chapeu[1].use[0] = LoadModel("./data/models/equips/chapeu/1/use/0.glb");
	item->chapeu[1].use[1] = LoadModel("./data/models/equips/chapeu/1/use/1.glb");
	item->chapeu[1].use[2] = LoadModel("./data/models/equips/chapeu/1/use/2.glb");
    item->chapeu[1].drop = LoadModel("./data/models/equips/chapeu/1/drop/0.glb");
    
    item->calca[1].idle = LoadModel("./data/models/equips/calca/1/idle/2.glb");
	item->calca[1].run[0] = LoadModel("./data/models/equips/calca/1/run/0.glb");
	item->calca[1].run[1] = LoadModel("./data/models/equips/calca/1/run/1.glb");
	item->calca[1].run[2] = LoadModel("./data/models/equips/calca/1/run/2.glb");
	item->calca[1].run[3] = LoadModel("./data/models/equips/calca/1/run/3.glb");
	item->calca[1].run[4] = LoadModel("./data/models/equips/calca/1/run/4.glb");
    item->calca[1].use[0] = LoadModel("./data/models/equips/calca/1/use/0.glb");
	item->calca[1].use[1] = LoadModel("./data/models/equips/calca/1/use/1.glb");
	item->calca[1].use[2] = LoadModel("./data/models/equips/calca/1/use/2.glb");
    item->calca[1].drop = LoadModel("./data/models/equips/calca/1/drop/0.glb");
    //mapa->item[1].modelo = LoadModel("./data/models/map/level0/calca_drop.glb");
    
    item->camisa[1].idle = LoadModel("./data/models/equips/camisa/1/idle/2.glb");
	item->camisa[1].run[0] = LoadModel("./data/models/equips/camisa/1/run/0.glb");
	item->camisa[1].run[1] = LoadModel("./data/models/equips/camisa/1/run/1.glb");
	item->camisa[1].run[2] = LoadModel("./data/models/equips/camisa/1/run/2.glb");
	item->camisa[1].run[3] = LoadModel("./data/models/equips/camisa/1/run/3.glb");
	item->camisa[1].run[4] = LoadModel("./data/models/equips/camisa/1/run/4.glb");
    item->camisa[1].use[0] = LoadModel("./data/models/equips/camisa/1/use/0.glb");
	item->camisa[1].use[1] = LoadModel("./data/models/equips/camisa/1/use/1.glb");
	item->camisa[1].use[2] = LoadModel("./data/models/equips/camisa/1/use/2.glb");
    item->camisa[1].drop = LoadModel("./data/models/equips/camisa/1/drop/0.glb");
    item->camisa[1].atirar = LoadModel("./data/models/equips/camisa/1/use/x.glb");
    
    item->arma[1].idle = LoadModel("./data/models/equips/arma/1/idle/2.glb");
	item->arma[1].run[0] = LoadModel("./data/models/equips/arma/1/run/0.glb");
	item->arma[1].run[1] = LoadModel("./data/models/equips/arma/1/run/1.glb");
	item->arma[1].run[2] = LoadModel("./data/models/equips/arma/1/run/2.glb");
	item->arma[1].run[3] = LoadModel("./data/models/equips/arma/1/run/3.glb");
	item->arma[1].run[4] = LoadModel("./data/models/equips/arma/1/run/4.glb");
    item->arma[1].use[0] = LoadModel("./data/models/equips/arma/1/use/0.glb");
    item->arma[1].drop = LoadModel("./data/models/equips/arma/1/drop/0.glb");
    item->arma[1].atirar = LoadModel("./data/models/equips/arma/1/use/x.glb");
    
    mapa->item[0].modelo = LoadModel("./data/models/map/level0/calca_drop.glb");
    mapa->item[1].modelo = LoadModel("./data/models/map/level0/chapeu_drop.glb");
    mapa->item[2].modelo = LoadModel("./data/models/map/level0/camisa_drop.glb");
    mapa->item[3].modelo = LoadModel("./data/models/map/level0/38_drop.glb");
    
    mapa->props[0].modelo = LoadModel("./data/models/map/level0/banquinhos0.glb");
    
    mapa->balasGLOBAL.modelo = LoadModel("./data/models/equips/arma/1/bala/0.glb"); 
    
    char texto_local[39];
    for(int i = 0; i <4; i++)
    {
        snprintf(texto_local, 39, "./data/models/map/porta/%d.glb", i);
        mapa->porta.base.modelo[i] = LoadModel(texto_local);
    }
    for(int i = 1; i <3; i++)
    {
        snprintf(texto_local, 39, "./data/models/map/porta/-%d.glb", i);
        mapa->porta.base.modeloI[i] = LoadModel(texto_local);
    }
    
//     mapa->porta[2].modelo[0] = LoadModel("./data/models/map/level0/porta2-0.glb");
//     mapa->porta[3].modelo[0] = LoadModel("./data/models/map/level0/porta3-0.glb");

}

void UNLOADALL_MODELS(PERSONAGEM* personagem, ITEM* item, MAPA* mapa)
{
	UnloadModel(personagem->modelo.idle);
	UnloadModel(item->calca[1].idle);
    UnloadModel(item->chapeu[1].idle);
    UnloadModel(item->camisa[1].idle);
    UnloadModel(item->arma[1].idle);
    UnloadModel ( item->arma[1].drop);
    UnloadModel ( item->camisa[1].drop);
    UnloadModel ( item->calca[1].drop);
    UnloadModel ( item->chapeu[1].drop);
	for ( int i = 0; i < sizeof ( personagem->modelo.run ); i++ )
		UnloadModel ( personagem->modelo.run[i] );

	for ( int i = 0; i < sizeof ( personagem->modelo.use_default ); i++ )
		UnloadModel ( personagem->modelo.use_default[i] );

	for ( int i = 0; i < sizeof ( item->calca[1].run ); i++ )
		UnloadModel ( item->calca[1].run[i] );
    
    for ( int i = 0; i < sizeof ( item->chapeu[1].run ); i++ )
		UnloadModel ( item->chapeu[1].run[i] );
    
    for ( int i = 0; i < sizeof ( item->camisa[1].run ); i++ )
		UnloadModel ( item->camisa[1].run[i] );
    
    for ( int i = 0; i < sizeof ( item->arma[1].run ); i++ )
		UnloadModel ( item->arma[1].run[i] );
    
    for ( int i = 0; i < sizeof ( item->calca[1].use ); i++ )
		UnloadModel ( item->calca[1].use[i] );
    
    for ( int i = 0; i < sizeof ( item->chapeu[1].use ); i++ )
		UnloadModel ( item->chapeu[1].use[i] );
    
    for ( int i = 0; i < sizeof ( item->camisa[1].use ); i++ )
		UnloadModel ( item->camisa[1].use[i] );
    
    UnloadModel ( item->arma[1].use[0] );
    
    for(int i = 0; i <4; i++)
        UnloadModel(mapa->porta.base.modelo[i]);
    
    for(int i = -0; i <3; i++)
        UnloadModel(mapa->porta.base.modeloI[i]);
//     
//     UnloadModel(mapa->porta[2].modelo[0]);
//     UnloadModel(mapa->porta[3].modelo[0]);
    UnloadModel(mapa->balasGLOBAL.modelo);
    UnloadModel(mapa->item[0].modelo);
    UnloadModel(mapa->item[1].modelo);
    UnloadModel(mapa->item[2].modelo);
    UnloadModel(mapa->item[3].modelo);
    UnloadModel(mapa->props[0].modelo);
    UnloadModel(mapa->modelo[0]);
    UnloadModel(personagem->modelo.atirar38);
    UnloadModel(item->arma[1].atirar);
    UnloadModel(item->camisa[1].atirar);
}
