
void LEVEL0(DATA *data)
{
    data->file.mapa.mapaAtual = 0;

    MQCreateHitbox(*&data,"props0", GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "props0"))]));
    //tipos
    //0 - calca
    //1 - chapeu
    //2 - camisa
    //3 - sapatos
    //4 - oculos
    //5 - arma
    MQCreateHitbox(*&data,"item0", GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "item0"))]));
    data->file.mapa.item[0].tipo = 0;
    data->file.mapa.item[0].ponteiro = 1;
    MQCreateHitbox(*&data,"item1", GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "item1"))]));
    data->file.mapa.item[1].tipo = 1;
    data->file.mapa.item[1].ponteiro = 1;
    MQCreateHitbox(*&data,"item2", GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "item2"))]));
    data->file.mapa.item[2].tipo = 2;
    data->file.mapa.item[2].ponteiro = 1;
    MQCreateHitbox(*&data,"item3", GetModelBoundingBox(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "item3"))]));
    data->file.mapa.item[3].tipo = 5;
    data->file.mapa.item[3].ponteiro = 1;
    data->file.mapa.item[3].municao = 5;
    data->file.mapa.item[3].municaoMax = 6;

    MQDoorCreate( *&data, (Vector3)
    {
        -4, 0, -9.87
        }, false, false, false);
    MQDoorCreate( *&data, (Vector3)
    {
        -0.06, 0, 2.125
        }, false, false, false);
}
