bool MQCheckCollisionPoint(Vector3 inPosi,BoundingBox target, int size)
{
    BoundingBox localhitbox;
    localhitbox.min = (Vector3) {inPosi.x - (size/2), inPosi.y - (size/2), inPosi.z - (size/2)};
    localhitbox.max = (Vector3) {inPosi.x + (size/2), inPosi.y + (size/2), inPosi.z + (size/2)};
    return(CheckCollisionBoxes(target, localhitbox));
}

bool* MQReturnCollisionCube(BoundingBox input, BoundingBox target)
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

    return ((bool[]){
        MQCheckCollisionPoint((Vector3) {input.max.x/2, input.max.y/2, input.min.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x, input.max.y/2, input.min.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x, input.max.y, input.min.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x/2, input.max.y, input.min.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.min.x, input.max.y, input.min.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.min.x, input.max.y/2, input.min.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.min.x, input.min.y, input.min.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x/2, input.min.y, input.min.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x, input.min.y, input.min.z}, target, 0.02),
        
        MQCheckCollisionPoint((Vector3) {input.max.x/2, input.max.y/2, input.max.z/2}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x, input.max.y/2, input.max.z/2}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x, input.max.y, input.max.z/2}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x/2, input.max.y, input.max.z/2}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.min.x, input.max.y, input.max.z/2}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.min.x, input.max.y/2, input.max.z/2}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.min.x, input.min.y, input.max.z/2}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x/2, input.min.y, input.max.z/2}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x, input.min.y, input.max.z/2}, target, 0.02),
        
        MQCheckCollisionPoint((Vector3) {input.max.x/2, input.max.y/2, input.max.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x, input.max.y/2, input.max.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x, input.max.y, input.max.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x/2, input.max.y, input.max.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.min.x, input.max.y, input.max.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.min.x, input.max.y/2, input.max.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.min.x, input.min.y, input.max.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x/2, input.min.y, input.max.z}, target, 0.02),
        MQCheckCollisionPoint((Vector3) {input.max.x, input.min.y, input.max.z}, target, 0.02)
    });

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
}

bool MQWALLEXCLUDE = false;
int MQWALLEXCLUDEINDEX=0;

Vector3 MQCheckWall(DATA data, char *hitboxID,float LocalRotation)
{
    int hitboxIndex = MQFindHitboxByName(data, hitboxID);
    int hitboxMax = data.session.counter.hitbox;
    BoundingBox hitboxLocal = data.file.hitbox[hitboxIndex];
    
    for(int i = 0; i < hitboxMax; i++)
        if(CheckCollisionBoxes(data.file.hitbox[i], hitboxLocal)==true && i != hitboxIndex)
        {
            bool *LocalBool;
            LocalBool = malloc(sizeof(bool)*27);
            LocalBool = MQReturnCollisionCube( hitboxLocal, data.file.hitbox[i]);
            int localint=0;

            for(int i = 0;i<27;i++)
            {
                localint += LocalBool[i];
            }
                
            if( MQWALLEXCLUDE == true&&MQWALLEXCLUDEINDEX == i)
            {
                MQWALLEXCLUDE = false;
            }
            else if(localint != 0&&i != hitboxMax)
            {
                
                if(LocalRotation>=0&&LocalRotation<90&&LocalBool[21]+LocalBool[18]+LocalBool[25]+LocalBool[20]+LocalBool[19]+LocalBool[26]+LocalBool[10]+LocalBool[11]+LocalBool[17]!=0)
                {
                    MQWALLEXCLUDEINDEX=i;
                    if(hitboxLocal.max.z-0.5 < data.file.hitbox[i].min.z&&hitboxLocal.max.x-0.5 < data.file.hitbox[i].min.x)
                        return ((Vector3){data.file.hitbox[i].min.x-0.10,__INT_MAX__,data.file.hitbox[i].min.z-0.10});
                        
                    else if(hitboxLocal.max.z-0.5 < data.file.hitbox[i].min.z)
                        return ((Vector3){__INT_MAX__,__INT_MAX__,data.file.hitbox[i].min.z-0.10});

                    else if(hitboxLocal.max.x-0.5 < data.file.hitbox[i].min.x)
                        return ((Vector3){data.file.hitbox[i].min.x-0.10,__INT_MAX__,__INT_MAX__});
                }


                if(LocalRotation>=90&&LocalRotation<180&&LocalBool[11]+LocalBool[10]+LocalBool[17]+LocalBool[2]+LocalBool[1]+LocalBool[8]+LocalBool[3]+LocalBool[0]+LocalBool[7]!=0)
                {
                    MQWALLEXCLUDEINDEX=i;
                    if(hitboxLocal.min.z+0.5 > data.file.hitbox[i].max.z&&hitboxLocal.max.x-0.5 < data.file.hitbox[i].min.x)
                        return ((Vector3){data.file.hitbox[i].min.x-0.10,__INT_MAX__,data.file.hitbox[i].max.z+0.10});
                        
                    else if(hitboxLocal.min.z+0.5 > data.file.hitbox[i].max.z)
                        return ((Vector3){__INT_MAX__,__INT_MAX__,data.file.hitbox[i].max.z+0.10});

                    else if(hitboxLocal.max.x-0.5 < data.file.hitbox[i].min.x)
                        return ((Vector3){data.file.hitbox[i].min.x-0.10,__INT_MAX__,__INT_MAX__});
                }


                if(LocalRotation>=180&&LocalRotation<270&&LocalBool[3]+LocalBool[0]+LocalBool[7]+LocalBool[4]+LocalBool[5]+LocalBool[6]+LocalBool[13]+LocalBool[14]+LocalBool[15]!=0)
                {
                    MQWALLEXCLUDEINDEX=i;
                    if(hitboxLocal.min.z+0.5 > data.file.hitbox[i].max.z&&hitboxLocal.min.x+0.5 > data.file.hitbox[i].max.x)
                        return ((Vector3){data.file.hitbox[i].min.x-0.10,__INT_MAX__,data.file.hitbox[i].max.z+0.10});
                        
                    else if(hitboxLocal.min.z+0.5 > data.file.hitbox[i].max.z)
                        return ((Vector3){__INT_MAX__,__INT_MAX__,data.file.hitbox[i].max.z+0.10});

                    else if(hitboxLocal.min.x+0.5 > data.file.hitbox[i].max.x)
                        return ((Vector3){data.file.hitbox[i].max.x+0.10,__INT_MAX__,__INT_MAX__});
                }


                if(LocalRotation>=270&&LocalRotation<=360&&LocalBool[13]+LocalBool[14]+LocalBool[15]+LocalBool[22]+LocalBool[23]+LocalBool[24]+LocalBool[21]+LocalBool[18]+LocalBool[25]!=0)
                {
                    MQWALLEXCLUDEINDEX=i;
                    if(hitboxLocal.max.z-0.5 < data.file.hitbox[i].min.z&&hitboxLocal.min.x+0.5 > data.file.hitbox[i].max.x)
                        return ((Vector3){data.file.hitbox[i].min.x-0.10,__INT_MAX__,data.file.hitbox[i].max.z+0.10});
                        
                    else if(hitboxLocal.max.z-0.5 < data.file.hitbox[i].min.z)
                        return ((Vector3){__INT_MAX__,__INT_MAX__,data.file.hitbox[i].min.z-0.10});

                    else if(hitboxLocal.min.x+0.5 > data.file.hitbox[i].max.x)
                        return ((Vector3){data.file.hitbox[i].max.x+0.10,__INT_MAX__,__INT_MAX__});
                }
            } 
            MQWALLEXCLUDEINDEX = __INT_MAX__;
        }
    MQWALLEXCLUDEINDEX = __INT_MAX__;
    return ((Vector3){__INT_MAX__,__INT_MAX__,__INT_MAX__});
}

float MQReturnYMaxCollisionPoint(DATA data, Vector3 posi)
{
    int hitboxMax = data.session.counter.hitbox;
    BoundingBox hitboxLocal;
    hitboxLocal.max = (Vector3){posi.x+0.005,posi.y-0.05,posi.z+0.005};
    hitboxLocal.min = (Vector3){posi.x-0.005,posi.y-0.1,posi.z-0.005};
    for(int i = 0; i < hitboxMax; i++)
    {
        if(CheckCollisionBoxes(data.file.hitbox[i],hitboxLocal))
        {
            return data.file.hitbox[i].max.y;
        }
    }
    return MQFALSE;
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
    data->game.personagem[quem].tempoGravit = 0;
    data->game.personagem[quem].rotacao = 180;
    data->game.personagem[quem].posicao.y = posi.y;
    data->game.personagem[quem].posicao.x = posi.x;
    data->game.personagem[quem].posicao.z = posi.z;
    data->game.personagem[quem].velocidade = 0.1f;
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

