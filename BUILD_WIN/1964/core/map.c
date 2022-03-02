
void LVL0(MAPA* mapa)
{
    mapa->mapaAtual = 0;
    mapa->dummy = LoadModel("data/models/map/level0/hitbox0.glb");
    mapa->hitboxH[0] = GetModelBoundingBox(mapa->dummy);
    UnloadModel(mapa->dummy);
    mapa->dummy = LoadModel("data/models/map/level0/hitbox1.glb");
    mapa->hitboxV[0] = GetModelBoundingBox(mapa->dummy);
    UnloadModel(mapa->dummy);
    
}

void MAPA_START(MAPA* mapa)
{
    LVL0(*&mapa);
}

