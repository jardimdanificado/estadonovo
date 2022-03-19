
void LEVEL0(MAPA* mapa)
{
    mapa->mapaAtual = 0;
    
    
    
    for(int i=0;i<10;i++)
        mapa->item[i].pegou = false;
    
    mapa->modelo[0] = LoadModel("./data/models/map/level0/lvl0.glb");
    mapa->dummy = LoadModel("data/models/map/level0/hitbox_chao.glb");
    mapa->hitboxHorizontal[0] = GetModelBoundingBox(mapa->dummy);
    UnloadModel(mapa->dummy);
    
    char texto_local[42];
    for(int i = 0; i <10; i++)
    {
        snprintf(texto_local, 42, "data/models/map/level0/hitbox_parede%d.glb", i);
        mapa->dummy = LoadModel(texto_local);
        mapa->hitboxVertical[i] = GetModelBoundingBox(mapa->dummy);
        UnloadModel(mapa->dummy);
    }
    
    mapa->dummy = LoadModel("data/models/map/level0/area0.glb");
    mapa->area[0] = GetModelBoundingBox(mapa->dummy);
    UnloadModel(mapa->dummy);
    
    mapa->dummy = LoadModel("data/models/map/level0/area1.glb");
    mapa->area[1] = GetModelBoundingBox(mapa->dummy);
    UnloadModel(mapa->dummy);
    
    mapa->dummy = LoadModel("data/models/map/level0/area2.glb");
    mapa->area[2] = GetModelBoundingBox(mapa->dummy);
    UnloadModel(mapa->dummy);
    
    mapa->dummy = LoadModel("data/models/map/level0/area3.glb");
    mapa->area[3] = GetModelBoundingBox(mapa->dummy);
    UnloadModel(mapa->dummy);
    
    mapa->dummy = LoadModel("data/models/map/level0/area4.glb");
    mapa->area[4] = GetModelBoundingBox(mapa->dummy);
    UnloadModel(mapa->dummy);
    
    mapa->dummy = LoadModel("data/models/map/level0/area5.glb");
    mapa->area[5] = GetModelBoundingBox(mapa->dummy);
    UnloadModel(mapa->dummy);
    
    mapa->props[0].hitbox = GetModelBoundingBox(mapa->props[0].modelo);
    
    for(int i = 0; i <5; i++)
    {
        mapa->porta[i].aberta = false;
        mapa->porta[i].frame = 0;
        mapa->porta[i].abrindo = false;
        mapa->porta[i].fechando = false;
    }
    
    mapa->item[0].hitbox = GetModelBoundingBox(mapa->item[0].modelo);
    mapa->item[1].hitbox = GetModelBoundingBox(mapa->item[1].modelo);
    mapa->item[2].hitbox = GetModelBoundingBox(mapa->item[2].modelo);
    mapa->item[3].hitbox = GetModelBoundingBox(mapa->item[3].modelo);
    
    mapa->porta[0].hitbox = GetModelBoundingBox(mapa->porta[0].modelo[mapa->porta[0].frame]);
    mapa->porta[1].hitbox = GetModelBoundingBox(mapa->porta[1].modelo[mapa->porta[1].frame]);
} 
