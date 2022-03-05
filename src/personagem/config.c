 
void PERSONAGEM_CONFIGSTART(PERSONAGEM* personagem)
{
	personagem->equip.chapeu = 0;
	personagem->equip.camisa = 0;
	personagem->equip.oculos = 0;
	personagem->equip.sapato = 0;
	personagem->equip.calca = 0;
	personagem->rotacao = 0;
	personagem->modelo.frame = 0;
	personagem->posicao.y = 2;
	personagem->posicao.x = 0;
	personagem->posicao.z = 0;
	personagem->velocidade = 0.1f;
	personagem->modelo.atual = personagem->modelo.idle;
	personagem->pulando = false;
	personagem->usando = false;
	personagem->relogioNovo = 0;
	personagem->relogioVelho = 0;
    
    personagem->hitbox.modelo = LoadModel("data/models/personagem/hitbox/action.glb");
	personagem->hitbox.useBase = GetModelBoundingBox(personagem->hitbox.modelo);
	personagem->hitbox.atual = personagem->hitbox.useBase;
	UnloadModel(personagem->hitbox.modelo);
    
    personagem->hitbox.modelo = LoadModel("data/models/personagem/hitbox/pes.glb");
    personagem->hitbox.pesBase = GetModelBoundingBox(personagem->hitbox.modelo);
    UnloadModel(personagem->hitbox.modelo);
    
    personagem->hitbox.modelo = LoadModel("data/models/personagem/hitbox/pes90.glb");
    personagem->hitbox.pes90 = GetModelBoundingBox(personagem->hitbox.modelo);
    UnloadModel(personagem->hitbox.modelo);
    
    personagem->hitbox.modelo = LoadModel("data/models/personagem/hitbox/pes180.glb");
    personagem->hitbox.pes180 = GetModelBoundingBox(personagem->hitbox.modelo);
    UnloadModel(personagem->hitbox.modelo);
    
    personagem->hitbox.modelo = LoadModel("data/models/personagem/hitbox/pes270.glb");
    personagem->hitbox.pes270 = GetModelBoundingBox(personagem->hitbox.modelo);
    UnloadModel(personagem->hitbox.modelo);
    
    personagem->hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente.glb");
    personagem->hitbox.frenteBase = GetModelBoundingBox(personagem->hitbox.modelo);
    UnloadModel(personagem->hitbox.modelo);
    
    personagem->hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras.glb");
    personagem->hitbox.trasBase = GetModelBoundingBox(personagem->hitbox.modelo);
    UnloadModel(personagem->hitbox.modelo);
    
    personagem->hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente90.glb");
    personagem->hitbox.frente90 = GetModelBoundingBox(personagem->hitbox.modelo);
    UnloadModel(personagem->hitbox.modelo);
    
    personagem->hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras90.glb");
    personagem->hitbox.tras90 = GetModelBoundingBox(personagem->hitbox.modelo);
    UnloadModel(personagem->hitbox.modelo);
    
    personagem->hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente180.glb");
    personagem->hitbox.frente180 = GetModelBoundingBox(personagem->hitbox.modelo);
    UnloadModel(personagem->hitbox.modelo);
    
    personagem->hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras180.glb");
    personagem->hitbox.tras180 = GetModelBoundingBox(personagem->hitbox.modelo);
    UnloadModel(personagem->hitbox.modelo);
    
    personagem->hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente270.glb");
    personagem->hitbox.frente270 = GetModelBoundingBox(personagem->hitbox.modelo);
    UnloadModel(personagem->hitbox.modelo);
    
    personagem->hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras270.glb");
    personagem->hitbox.tras270 = GetModelBoundingBox(personagem->hitbox.modelo);
    UnloadModel(personagem->hitbox.modelo);
}
