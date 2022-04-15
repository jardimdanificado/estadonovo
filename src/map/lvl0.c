
void LEVEL0(PERSONAGEM personagem, MAPA* mapa, NPC0* humano)
{
    mapa->mapaAtual = 0;
    
    humano->npc[0] = AIHUMAN_CONFIGSTART(personagem,*humano, 0, (Vector3){-4,0,-30});
    mapa->modelo[0] = LoadModel("./data/models/map/level0/lvl0.glb");
    mapa->dummy = LoadModel("data/models/map/level0/hitbox_chao.glb");
    mapa->hitboxHorizontal[0] = GetModelBoundingBox(mapa->dummy);
    UnloadModel(mapa->dummy);
    
    char texto_local[42];
    for(int i = 0; i <10; i++)
    {
        mapa->item[i].pegou = false;
        
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
        
    }
    
    //tipos 
    //0 - calca 
    //1 - chapeu 
    //2 - camisa 
    //3 - sapatos  
    //4 - oculos 
    //5 - arma
    mapa->item[0].hitbox = GetModelBoundingBox(mapa->item[0].modelo);
    mapa->item[0].nome = "calca do Estado";
    mapa->item[0].tipo = 0;
    mapa->item[0].ponteiro = 1;
    mapa->item[1].hitbox = GetModelBoundingBox(mapa->item[1].modelo);
    mapa->item[1].nome = "camisa do Estado";
    mapa->item[1].tipo = 1;
    mapa->item[1].ponteiro = 1;
    mapa->item[2].hitbox = GetModelBoundingBox(mapa->item[2].modelo);
    mapa->item[2].nome = "chapeu do Estado";
    mapa->item[2].tipo = 2;
    mapa->item[2].ponteiro = 1;
    mapa->item[3].hitbox = GetModelBoundingBox(mapa->item[3].modelo);
    mapa->item[3].nome = "38tao velho e fudido";
    mapa->item[3].tipo = 5;
    mapa->item[3].ponteiro = 1;
    mapa->item[3].municao = 5;
    mapa->item[3].municaoMax = 6;
    
    PORTA_CRIAR(*&mapa, (Vector3){-4,0,-9.87}, false, false, false);
    PORTA_CRIAR(*&mapa, (Vector3){-0.06,0,2.125}, false, false, false);
} 
