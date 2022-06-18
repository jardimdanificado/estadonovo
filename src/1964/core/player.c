bool MQCheckCollisionPoint(Vector3 inPosi,BoundingBox target, int size)
{
    BoundingBox localhitbox;
    localhitbox.min = (Vector3) {inPosi.x - size/2, inPosi.y - size/2, inPosi.z - size/2};
    localhitbox.max = (Vector3) {inPosi.x + size/2, inPosi.y + size/2, inPosi.z + size/2};
    return(CheckCollisionBoxes(target, localhitbox));
}

bool* MQCheckHitboxPoints(BoundingBox input, BoundingBox target)
{
    //imagine a cube
    
    //facemin
    //2  3  4
    //1  0  5
    //8  7  6

    //facemeio
    //11 12 13
    //10 9  14
    //17 16 15

    //facemax
    //20 21 22
    //19 18 23
    //26 25 24

    BoundingBox hitboxLocal2;
    bool facemeio[9],facemin[9],facemax[9],resultado[27];

    hitboxLocal2.min = (Vector3) {input.max.x/2 - 0.01, input.max.y/2 - 0.01, input.min.z - 0.01};
    hitboxLocal2.max = (Vector3) {input.max.x/2 + 0.01, input.max.y/2 + 0.01, input.min.z + 0.01};
    resultado[0] = MQCheckHitboxPoints(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.max.x - 0.01, input.max.y/2 - 0.01, input.min.z - 0.01};
    hitboxLocal2.max = (Vector3) {input.max.x + 0.01, input.max.y/2 + 0.01, input.min.z + 0.01};
    facemin[1] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.max.x - 0.01, input.max.y - 0.01, input.min.z - 0.01};
    hitboxLocal2.max = (Vector3) {input.max.x + 0.01, input.max.y + 0.01, input.min.z + 0.01};
    facemin[2] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.max.x/2 - 0.01, input.max.y - 0.01, input.min.z - 0.01};
    hitboxLocal2.max = (Vector3) {input.max.x/2 + 0.01, input.max.y + 0.01, input.min.z + 0.01};
    facemin[3] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.min.x - 0.01, input.max.y - 0.01, input.min.z - 0.01};
    hitboxLocal2.max = (Vector3) {input.min.x + 0.01, input.max.y + 0.01, input.min.z + 0.01};
    facemin[4] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.min.x - 0.01, input.max.y/2 - 0.01, input.min.z - 0.01};
    hitboxLocal2.max = (Vector3) {input.min.x + 0.01, input.max.y/2 + 0.01, input.min.z + 0.01};
    facemin[5] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.min.x - 0.01, input.min.y - 0.01, input.min.z - 0.01};
    hitboxLocal2.max = (Vector3) {input.min.x + 0.01, input.min.y + 0.01, input.min.z + 0.01};
    facemin[6] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.max.x/2 - 0.01, input.min.y - 0.01, input.min.z - 0.01};
    hitboxLocal2.max = (Vector3) {input.max.x/2 + 0.01, input.min.y + 0.01, input.min.z + 0.01};
    facemin[7] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.max.x - 0.01, input.min.y - 0.01, input.min.z - 0.01};
    hitboxLocal2.max = (Vector3) {input.max.x + 0.01, input.min.y + 0.01, input.min.z + 0.01};
    facemin[8] = CheckCollisionBoxes(target, hitboxLocal2);

    hitboxLocal2.min = (Vector3) {input.max.x/2 - 0.01, input.max.y/2 - 0.01, input.max.z/2 - 0.01};
    hitboxLocal2.max = (Vector3) {input.max.x/2 + 0.01, input.max.y/2 + 0.01, input.max.z/2 + 0.01};
    facemax[0] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.max.x - 0.01, input.max.y/2 - 0.01, input.max.z/2 - 0.01};
    hitboxLocal2.max = (Vector3) {input.max.x + 0.01, input.max.y/2 + 0.01, input.max.z/2 + 0.01};
    facemax[1] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.max.x - 0.01, input.max.y - 0.01, input.max.z - 0.01};
    hitboxLocal2.max = (Vector3) {input.max.x + 0.01, input.max.y + 0.01, input.max.z + 0.01};
    facemax[2] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.max.x/2 - 0.01, input.max.y - 0.01, input.max.z - 0.01};
    hitboxLocal2.max = (Vector3) {input.max.x/2 + 0.01, input.max.y + 0.01, input.max.z + 0.01};
    facemax[3] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.min.x - 0.01, input.max.y - 0.01, input.max.z - 0.01};
    hitboxLocal2.max = (Vector3) {input.min.x + 0.01, input.max.y + 0.01, input.max.z + 0.01};
    facemax[4] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.min.x - 0.01, input.max.y/2 - 0.01, input.max.z - 0.01};
    hitboxLocal2.max = (Vector3) {input.min.x + 0.01, input.max.y/2 + 0.01, input.max.z + 0.01};
    facemax[5] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.min.x - 0.01, input.min.y - 0.01, input.max.z - 0.01};
    hitboxLocal2.max = (Vector3) {input.min.x + 0.01, input.min.y + 0.01, input.max.z + 0.01};
    facemax[6] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.max.x/2 - 0.01, input.min.y - 0.01, input.max.z - 0.01};
    hitboxLocal2.max = (Vector3) {input.max.x/2 + 0.01, input.min.y + 0.01, input.max.z + 0.01};
    facemax[7] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.max.x - 0.01, input.min.y - 0.01, input.max.z/2 - 0.01};
    hitboxLocal2.max = (Vector3) {input.max.x + 0.01, input.min.y + 0.01, input.max.z/2 + 0.01};
    facemax[8] = CheckCollisionBoxes(target, hitboxLocal2);

    hitboxLocal2.min = (Vector3) {input.max.x/2 - 0.01, input.max.y/2 - 0.01, input.max.z/2 - 0.01};
    hitboxLocal2.max = (Vector3) {input.max.x/2 + 0.01, input.max.y/2 + 0.01, input.max.z/2 + 0.01};
    facemeio[0] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.max.x - 0.01, input.max.y/2 - 0.01, input.max.z/2 - 0.01};
    hitboxLocal2.max = (Vector3) {input.max.x + 0.01, input.max.y/2 + 0.01, input.max.z/2 + 0.01};
    facemeio[1] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.max.x - 0.01, input.max.y - 0.01, input.max.z/2 - 0.01};
    hitboxLocal2.max = (Vector3) {input.max.x + 0.01, input.max.y + 0.01, input.max.z/2 + 0.01};
    facemeio[2] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.max.x/2 - 0.01, input.max.y - 0.01, input.max.z/2 - 0.01};
    hitboxLocal2.max = (Vector3) {input.max.x/2 + 0.01, input.max.y + 0.01, input.max.z/2 + 0.01};
    facemeio[3] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.min.x - 0.01, input.max.y - 0.01, input.max.z/2 - 0.01};
    hitboxLocal2.max = (Vector3) {input.min.x + 0.01, input.max.y + 0.01, input.max.z/2 + 0.01};
    facemeio[4] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.min.x - 0.01, input.max.y/2 - 0.01, input.max.z/2 - 0.01};
    hitboxLocal2.max = (Vector3) {input.min.x + 0.01, input.max.y/2 + 0.01, input.max.z/2 + 0.01};
    facemeio[5] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.min.x - 0.01, input.min.y - 0.01, input.max.z/2 - 0.01};
    hitboxLocal2.max = (Vector3) {input.min.x + 0.01, input.min.y + 0.01, input.max.z/2 + 0.01};
    facemeio[6] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.max.x/2 - 0.01, input.min.y - 0.01, input.max.z/2 - 0.01};
    hitboxLocal2.max = (Vector3) {input.max.x/2 + 0.01, input.min.y + 0.01, input.max.z/2 + 0.01};
    facemeio[7] = CheckCollisionBoxes(target, hitboxLocal2);
    hitboxLocal2.min = (Vector3) {input.max.x - 0.01, input.min.y - 0.01, input.max.z/2 - 0.01};
    hitboxLocal2.max = (Vector3) {input.max.x + 0.01, input.min.y + 0.01, input.max.z/2 + 0.01};
    facemeio[8] = CheckCollisionBoxes(target, hitboxLocal2);

    //resultbox
    //2  3  4
    //1  0  5
    //8  7  6

    //11 12 13
    //10 9  14
    //17 16 15

    //20 21 22
    //19 18 23
    //26 25 24

    resultado[0] = facemin[0];
    resultado[1] = facemin[1];
    resultado[2] = facemin[2];
    resultado[3] = facemin[3];
    resultado[4] = facemin[4];
    resultado[5] = facemin[5];
    resultado[6] = facemin[6];
    resultado[7] = facemin[7];
    resultado[8] = facemin[8];
    resultado[9] = facemeio[0];
    resultado[10] = facemeio[1];
    resultado[11] = facemeio[2];
    resultado[12] = facemeio[3];
    resultado[13] = facemeio[4];
    resultado[14] = facemeio[5];
    resultado[15] = facemeio[6];
    resultado[16] = facemeio[7];
    resultado[17] = facemeio[8];
    resultado[18] = facemax[0];
    resultado[19] = facemax[1];
    resultado[20] = facemax[2];
    resultado[21] = facemax[3];
    resultado[22] = facemax[4];
    resultado[23] = facemax[5];
    resultado[24] = facemax[6];
    resultado[25] = facemax[7];
    resultado[26] = facemax[8];
    return resultado;
}

float MQReturnWallCollisionPoint(DATA data, char *hitboxID,float LocalRotation)
{
    int hitboxIndex = atoi(abinCoreReturnData("./data/temp/hitbox.temp", hitboxID));
    int hitboxMax = atoi(abinCoreReturnData("./data/temp/hitbox.temp", "SIZE"));
    BoundingBox hitboxLocal = data.file.hitbox[hitboxIndex];
    
    for(int i = 0; i < hitboxMax; i++)
        if(CheckCollisionBoxes(data.file.hitbox[i], hitboxLocal) && i != hitboxIndex)
        {
            bool LocalBool[27] = MQCheckHitboxPoints( hitboxLocal, data.file.hitbox[i]);
            
            if(LocalRotation>=315||LocalRotation<45)
                return data.file.hitbox[i].min.z;
            else if(LocalRotation>=45||LocalRotation<135)
                return data.file.hitbox[i].min.x;
            else if(LocalRotation>=135||LocalRotation<225)
                return data.file.hitbox[i].max.z;
            else if(LocalRotation>=225||LocalRotation<315)
                return data.file.hitbox[i].max.x;
        }
        else if(i == hitboxMax)
        {
            return MQFALSE;
        }
    return MQFALSE;
}

bool MQCheckFloorFromHeight(DATA data, float point)
{
    int hitboxMax = atoi(abinCoreReturnData("./data/temp/hitbox.temp", "SIZE"));

    BoundingBox hitboxLocal;
    hitboxLocal.min = (Vector3) {point - 0.01, point - 0.01, point - 0.01};
    hitboxLocal.max = (Vector3) {point + 0.01, point + 0.01, point + 0.01};

    for(int i = 0; i < hitboxMax; i++)
        if(CheckCollisionBoxes(data.file.hitbox[i], hitboxLocal) && hitboxLocal.min.y > data.file.hitbox[i].max.y - 0.12)
        {
            return true;
        }
        else if(i == hitboxMax)
        {
            return false;
        }
    return false;
}

float MQReturnFloorCollisionPoint(DATA data, char *hitboxID)
{
    int hitboxIndex = atoi(abinCoreReturnData("./data/temp/hitbox.temp", hitboxID));
    int hitboxMax = atoi(abinCoreReturnData("./data/temp/hitbox.temp", "SIZE"));
    BoundingBox hitboxLocal = data.file.hitbox[hitboxIndex];

    for(int i = 0; i < hitboxMax; i++)
        if(CheckCollisionBoxes(data.file.hitbox[i], hitboxLocal) && i != hitboxIndex)
        {
            if(hitboxLocal.min.y > data.file.hitbox[i].max.y - 0.12)
                return data.file.hitbox[i].max.y;
        }
        else if(i == hitboxMax)
        {
            return MQFALSE;
        }
    return MQFALSE;
}

bool MQPlayerCheckWall(DATA data,   char opcao)
{
    if(opcao == '+')
    {
        for(int i = 0; i < MAXOBJ; i++)
        {
            if(CheckCollisionBoxes(data.game.hitbox.personagem[0].frenteAtual, data.file.mapa.hitboxVertical[i]))
            {
                return true;
            }
            else if(CheckCollisionBoxes(data.game.hitbox.personagem[0].frenteAtual, data.file.mapa.props[i].hitbox))
            {
                return true;
            }
            else if(CheckCollisionBoxes(data.game.hitbox.personagem[0].frenteAtual, data.file.mapa.porta.slots[i].hitbox))
            {
                return true;
            }
        }

        return false;
    }
    else if(opcao == '-')
    {
        for(int i = 0; i < MAXOBJ; i++)
        {
            if(CheckCollisionBoxes(data.game.hitbox.personagem[0].trasAtual, data.file.mapa.hitboxVertical[i]))
            {
                return true;
            }
            else if(CheckCollisionBoxes(data.game.hitbox.personagem[0].frenteAtual, data.file.mapa.porta.slots[i].hitbox))
            {
                return true;
            }
        }
        return false;
    }
}

void MQPlayerConfigStart(DATA *data, int quem, Vector3 posi)
{
    //tipos
    //0 - calca
    //1 - chapeu
    //2 - camisa
    //3 - sapatos
    //4 - oculos
    //5 - arma
    data->game.equip.personagem[quem].chapeu.tipo = 1;
    data->game.equip.personagem[quem].camisa.tipo = 2;
    data->game.equip.personagem[quem].oculos.tipo = 4;
    data->game.equip.personagem[quem].sapato.tipo = 3;
    data->game.equip.personagem[quem].calca.tipo = 0;
    data->game.equip.personagem[quem].arma.tipo = 5;
    data->game.ponteiro.personagem[quem].item.chapeu = 0;
    data->game.ponteiro.personagem[quem].item.camisa = 0;
    data->game.ponteiro.personagem[quem].item.oculos = 0;
    data->game.ponteiro.personagem[quem].item.sapato = 0;
    data->game.ponteiro.personagem[quem].item.calca = 0;
    data->game.ponteiro.personagem[quem].item.arma = 0;
    data->game.ponteiro.personagem[quem].lastFloorHeight = 0;
    data->game.rotacao.personagem[quem] = 180;
    data->game.contador.frames.personagem[quem] = 0;
    data->game.posicao.personagem[quem].y = posi.y;
    data->game.posicao.personagem[quem].x = posi.x;
    data->game.posicao.personagem[quem].z = posi.z;
    data->game.velocidade.personagem[quem].velocidade = 0.1f;
    data->game.boolean.personagem[quem].pulando = false;
    data->game.boolean.personagem[quem].usando = false;
    data->game.boolean.personagem[quem].andandoPraTras = false;
    data->session.relogio.personagem[quem].relogioNovo = 0;
    data->session.relogio.personagem[quem].relogioVelho = 0;
}

bool MQPlayerUse(DATA *data, int quem)
{
    for(int i = 0; i < MAXOBJ; i++)
    {
        if(CheckCollisionBoxes(data->game.hitbox.personagem[quem].use, data->file.mapa.item[i].hitbox) || CheckCollisionBoxes(data->game.hitbox.personagem[quem].atual, data->file.mapa.item[i].hitbox))
        {
            switch(data->file.mapa.item[i].tipo)
            {
                case 0:
                {
                    data->game.ponteiro.personagem[quem].item.calca = data->file.mapa.item[i].ponteiro;
                    snprintf(msg_simples, 512, "%s %s", data->file.text.act.opcao[3], data->file.text.item.calca.opcao[data->file.mapa.item[i].ponteiro]);
                }
                break;
                case 1:
                {
                    data->game.ponteiro.personagem[quem].item.chapeu = data->file.mapa.item[i].ponteiro;
                    snprintf(msg_simples, 512, "%s %s", data->file.text.act.opcao[3], data->file.text.item.chapeu.opcao[data->file.mapa.item[i].ponteiro]);
                }
                break;
                case 2:
                {
                    data->game.ponteiro.personagem[quem].item.camisa = data->file.mapa.item[i].ponteiro;
                    snprintf(msg_simples, 512, "%s %s", data->file.text.act.opcao[3], data->file.text.item.camisa.opcao[data->file.mapa.item[i].ponteiro]);
                }
                break;

                case 5:
                {
                    data->game.ponteiro.personagem[quem].item.arma = data->file.mapa.item[i].ponteiro;
                    data->game.equip.personagem[quem].arma.municao = data->file.mapa.item[i].municao;
                    data->game.equip.personagem[quem].arma.municaoMax = data->file.mapa.item[i].municaoMax;
                    snprintf(msg_simples, 512, "%s %s", data->file.text.act.opcao[3], data->file.text.item.arma.opcao[data->file.mapa.item[i].ponteiro]);
                }
                break;
            }

            data->file.mapa.item[i].pegou = true;
            data->file.mapa.item[i].hitbox = (BoundingBox)
            {
                (Vector3) {0, 0, 0}, (Vector3)
                {
                    0, 0, 0
                }
            };
            data->session.relogio.personagem[quem].relogioLogs = clock();
            msg = msg_simples;
            return true;
        }
    }
    for(int i = 0; i < MAXOBJ; i++)
    {
        if(CheckCollisionBoxes(data->game.hitbox.personagem[quem].use, data->file.mapa.porta.slots[i].hitbox) || CheckCollisionBoxes(data->game.hitbox.personagem[quem].atual, data->file.mapa.porta.slots[i].hitbox))
        {
            if(data->file.mapa.porta.slots[i].aberta == false)
            {
                data->file.mapa.porta.slots[i].abrindo = true;
                snprintf(msg_simples, 512, "%s", data->file.text.act.opcao[0]);
                msg = msg_simples;
                data->session.relogio.personagem[quem].relogioLogs = clock();
            }
            else if(data->file.mapa.porta.slots[i].aberta == true)
            {
                data->file.mapa.porta.slots[i].fechando = true;
                snprintf(msg_simples, 512, "%s", data->file.text.act.opcao[1]);
                msg = msg_simples;
                data->session.relogio.personagem[quem].relogioLogs = clock();
            }
            else if(data->file.mapa.porta.slots[i].trancada == true)
            {
                snprintf(msg_simples, 512, "%s", data->file.text.act.opcao[2]);
                msg = msg_simples;
                data->session.relogio.personagem[quem].relogioLogs = clock();
            }
            return true;
        }
    }
    for(int i = 0; i < MAXOBJ; i++)
    {
        if(data->file.mapa.drops[i].ocupado == true)
        {
            if(CheckCollisionBoxes(data->game.hitbox.personagem[quem].use, data->file.mapa.drops[i].hitbox) || CheckCollisionBoxes(data->game.hitbox.personagem[quem].atual, data->file.mapa.drops[i].hitbox))
            {
                switch(data->file.mapa.drops[i].tipo)
                {
                    case 0:
                    {
                        data->game.ponteiro.personagem[quem].item.calca = 1;
                    }
                    break;
                    case 1:
                    {
                        data->game.ponteiro.personagem[quem].item.chapeu = 1;
                    }
                    break;
                    case 2:
                    {
                        data->game.ponteiro.personagem[quem].item.camisa = 1;
                    }
                    break;
                    case 5:
                    {
                        data->game.ponteiro.personagem[quem].item.arma = 1;
                    }
                    break;
                }
                data->file.mapa.drops[i] = data->file.mapa.dropDUMMY;
                data->file.mapa.drops[i].ocupado = false;
                return true;
            }
        }
    }
    return false;
}

BoundingBox MQHitboxUpdateX(BoundingBox hitboxbase, Vector3 targetPosi)
{
    hitboxbase.min.x += targetPosi.x;
    hitboxbase.max.x += targetPosi.x;
    return hitboxbase;
}

BoundingBox MQHitboxUpdateY(BoundingBox hitboxbase, Vector3 targetPosi)
{
    hitboxbase.min.y += targetPosi.y;
    hitboxbase.max.y += targetPosi.y;
    return hitboxbase;
}

BoundingBox MQHitboxUpdateZ(BoundingBox hitboxbase, Vector3 targetPosi)
{
    hitboxbase.min.z += targetPosi.z;
    hitboxbase.max.z += targetPosi.z;
    return hitboxbase;
}

Vector3 MQHitboxUpdateMax(BoundingBox hitboxbase, Vector3 targetPosi)
{
    BoundingBox hitbox;
    hitbox.max.x = hitboxbase.max.x + targetPosi.x;
    hitbox.max.y = hitboxbase.max.y + targetPosi.y;
    hitbox.max.z = hitboxbase.max.z + targetPosi.z;
    return hitbox.max;
}

Vector3 MQHitboxUpdateMin(BoundingBox hitboxbase, Vector3 targetPosi)
{
    BoundingBox hitbox;
    hitbox.min.x = hitboxbase.min.x + targetPosi.x;
    hitbox.min.y = hitboxbase.min.y + targetPosi.y;
    hitbox.min.z = hitboxbase.min.z + targetPosi.z;
    return hitbox.min;
}

BoundingBox MQHitboxUpdateXYZ(BoundingBox hitboxbase, Vector3 targetPosi)
{
    BoundingBox hitbox;
    hitbox = hitboxbase;
    hitbox.max = MQHitboxUpdateMax(hitboxbase, targetPosi);
    hitbox.min = MQHitboxUpdateMin(hitboxbase, targetPosi);
    return hitbox;
}

Vector3 MQPlayerMove(Vector3 posicao, float rotacao, float velocidade)
{
    //z+ frente
    //x+ esquerda
    float  valorZ, valorX;
    int giro = rotacao / 90;
    float resto = rotacao - (90 * giro);
    float restodoresto = 90 - resto;
    valorZ = velocidade - resto * (velocidade / 90);
    valorX = velocidade - restodoresto * (velocidade / 90);
    switch(giro)
    {
        case 0:
        {
            posicao.z += valorZ;
            posicao.x += valorX;
        }
        break;
        case 1:
        {
            posicao.z -= valorX;
            posicao.x += valorZ;
        }
        break;
        case 2:
        {
            posicao.z -= valorZ;
            posicao.x -= valorX;
        }
        break;
        case 3:
        {
            posicao.z += valorX;
            posicao.x -= valorZ;
        }
        break;
    }
    return posicao;
}



void MQPlayerUpdateHitbox(DATA *data, int quem)
{
    data->game.hitbox.personagem[quem].atual = MQHitboxUpdateXYZ(data->game.hitbox.personagem[quem].useBase, data->game.posicao.personagem[quem]);
    data->game.hitbox.personagem[quem].anda0 = MQHitboxUpdateXYZ(data->game.hitbox.personagem[quem].anda0Base, data->game.posicao.personagem[quem]);
    data->game.hitbox.personagem[quem].anda45 = MQHitboxUpdateXYZ(data->game.hitbox.personagem[quem].anda45Base, data->game.posicao.personagem[quem]);
    data->game.hitbox.personagem[quem].anda90 = MQHitboxUpdateXYZ(data->game.hitbox.personagem[quem].anda90Base, data->game.posicao.personagem[quem]);
    data->game.hitbox.personagem[quem].anda135 = MQHitboxUpdateXYZ(data->game.hitbox.personagem[quem].anda135Base, data->game.posicao.personagem[quem]);
    data->game.hitbox.personagem[quem].anda180 = MQHitboxUpdateXYZ(data->game.hitbox.personagem[quem].anda180Base, data->game.posicao.personagem[quem]);
    data->game.hitbox.personagem[quem].anda225 = MQHitboxUpdateXYZ(data->game.hitbox.personagem[quem].anda225Base, data->game.posicao.personagem[quem]);
    data->game.hitbox.personagem[quem].anda270 = MQHitboxUpdateXYZ(data->game.hitbox.personagem[quem].anda270Base, data->game.posicao.personagem[quem]);
    data->game.hitbox.personagem[quem].anda315 = MQHitboxUpdateXYZ(data->game.hitbox.personagem[quem].anda315Base, data->game.posicao.personagem[quem]);

    data->game.hitbox.personagem[quem].frenteAtual = MQHitboxUpdateXYZ(data->game.hitbox.personagem[quem].frenteAtual, data->game.posicao.personagem[quem]);
    data->game.hitbox.personagem[quem].trasAtual = MQHitboxUpdateXYZ(data->game.hitbox.personagem[quem].trasAtual, data->game.posicao.personagem[quem]);
    data->game.hitbox.personagem[quem].pesAtual = MQHitboxUpdateXYZ(data->game.hitbox.personagem[quem].pesAtual, data->game.posicao.personagem[quem]);
    data->game.hitbox.personagem[quem].use = MQHitboxUpdateXYZ(data->game.hitbox.personagem[quem].use, data->game.posicao.personagem[quem]);
}
