
void LEVEL0(MAPA* mapa, ITEM item)
{
    mapa->mapaAtual = 0;
    for(int i=0;i<10;i++)
        mapa->pegouItem[i] = false;
    
    mapa->modelo[0] = LoadModel("./data/models/map/level0/lvl0.glb");
    mapa->dummy = LoadModel("data/models/map/level0/hitbox0.glb");
    mapa->hitboxH[0] = GetModelBoundingBox(mapa->dummy);
    UnloadModel(mapa->dummy);
    mapa->dummy = LoadModel("data/models/map/level0/hitbox1.glb");
    mapa->hitboxV[0] = GetModelBoundingBox(mapa->dummy);
    UnloadModel(mapa->dummy);
    
    mapa->item[0] = GetModelBoundingBox(item.calca[1].drop);
    mapa->item[1] = GetModelBoundingBox(item.chapeu[1].drop);
    mapa->item[2] = GetModelBoundingBox(item.camisa[1].drop);
} 
