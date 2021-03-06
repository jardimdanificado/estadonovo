void MQLoadAll(MQDATA* data)
{
    strcpy(data->files.langs[0].text,"Jogar");
    strcpy(data->files.langs[0].name,"sem-nome");
    strcpy(data->files.langs[1].text,"Sair");
    strcpy(data->files.langs[1].name,"sem-nome");
    strcpy(data->files.langs[2].text,"Salvar");
    strcpy(data->files.langs[2].name,"sem-nome");
    strcpy(data->files.langs[3].text,"Carregar");
    strcpy(data->files.langs[3].name,"sem-nome");
    strcpy(data->files.langs[4].text,"Voltar ao Estado");
    strcpy(data->files.langs[4].name,"sem-nome");
    strcpy(data->files.langs[5].text,"Equipamentos");
    strcpy(data->files.langs[5].name,"sem-nome");
    strcpy(data->files.langs[6].text,"Itens");
    strcpy(data->files.langs[6].name,"sem-nome");
    strcpy(data->files.langs[7].text,"Salvar/Carregar");
    strcpy(data->files.langs[7].name,"sem-nome");


    MQLoadModel(*&data, "player-cabeca","data/models/player/body/cabeca.iqm",true,false);
    MQLoadModel(*&data, "player-pescoco","data/models/player/body/pescoco.iqm",true,false);
    MQLoadModel(*&data, "player-peitoral","data/models/player/body/peitoral.iqm",true,false);
    MQLoadModel(*&data, "player-barriga","data/models/player/body/barriga.iqm",true,false);
    MQLoadModel(*&data, "player-maod","data/models/player/body/maodireita.iqm",true,false);
    MQLoadModel(*&data, "player-maoe","data/models/player/body/maoesquerda.iqm",true,false);
    MQLoadModel(*&data, "player-bracod","data/models/player/body/bracodireito.iqm",true,false);
    MQLoadModel(*&data, "player-bracoe","data/models/player/body/bracoesquerdo.iqm",true,false);
    MQLoadModel(*&data, "player-ombrod","data/models/player/body/ombrodireito.iqm",true,false);
    MQLoadModel(*&data, "player-ombroe","data/models/player/body/ombroesquerdo.iqm",true,false);
    MQLoadModel(*&data, "player-coxad","data/models/player/body/coxadireita.iqm",true,false);
    MQLoadModel(*&data, "player-coxae","data/models/player/body/coxaesquerda.iqm",true,false);
    MQLoadModel(*&data, "player-pernad","data/models/player/body/pernadireita.iqm",true,false);
    MQLoadModel(*&data, "player-pernae","data/models/player/body/pernaesquerda.iqm",true,false);
    MQLoadModel(*&data, "player","data/models/player/model.iqm",true,false);
    MQLoadModel(*&data, "calca1","data/models/equips/calca/1.iqm",true,false);
    MQLoadModel(*&data, "camisa1","data/models/equips/camisa/1.iqm",true,false);
    MQLoadModel(*&data, "chapeu1","data/models/equips/chapeu/1.iqm",true,false);
    MQLoadModel(*&data, "arma1","data/models/equips/arma/1.iqm",true,false);
    MQLoadModel(*&data, "map0","data/models/map/level0/0.glb",false,false);
    MQLoadModel(*&data, "props0","data/models/map/level0/props/0.glb",false,true);
    MQLoadModel(*&data, "hitbox0","data/models/map/level0/hitbox/hitbox0.glb",false,true);
    MQLoadModel(*&data, "hitbox1","data/models/map/level0/hitbox/hitbox1.glb",false,true);
    MQLoadModel(*&data, "hitbox2","data/models/map/level0/hitbox/hitbox2.glb",false,true);
    MQLoadModel(*&data, "hitbox3","data/models/map/level0/hitbox/hitbox3.glb",false,true);
    MQLoadModel(*&data, "hitbox4","data/models/map/level0/hitbox/hitbox4.glb",false,true);
    MQLoadModel(*&data, "hitbox5","data/models/map/level0/hitbox/hitbox5.glb",false,true);
    MQLoadModel(*&data, "hitbox6","data/models/map/level0/hitbox/hitbox6.glb",false,true);
    MQLoadModel(*&data, "hitbox7","data/models/map/level0/hitbox/hitbox7.glb",false,true);
    MQLoadModel(*&data, "hitbox8","data/models/map/level0/hitbox/hitbox8.glb",false,true);
    MQLoadModel(*&data, "hitbox9","data/models/map/level0/hitbox/hitbox9.glb",false,true);
    MQLoadModel(*&data, "map0item0","data/models/map/level0/item/0.glb",false,true);
    MQLoadModel(*&data, "map0item1","data/models/map/level0/item/1.glb",false,true);
    MQLoadModel(*&data, "map0item2","data/models/map/level0/item/2.glb",false,true);
    MQLoadModel(*&data, "map0item3","data/models/map/level0/item/3.glb",false,true);
    MQLoadModel(*&data, "area0","data/models/map/level0/area/0.glb",false,false);
    MQLoadModel(*&data, "area1","data/models/map/level0/area/1.glb",false,false);
    MQLoadModel(*&data, "area2","data/models/map/level0/area/2.glb",false,false);
    MQLoadModel(*&data, "area3","data/models/map/level0/area/3.glb",false,false);
    MQLoadModel(*&data, "area4","data/models/map/level0/area/4.glb",false,false);
    MQLoadModel(*&data, "area5","data/models/map/level0/area/5.glb",false,false);
    MQLoadModel(*&data, "chao0","data/models/map/level0/hitbox/chao.glb",false,true);

}
