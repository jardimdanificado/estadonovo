/* void MQCleanPlayerInventory(MQDATA *data)
{
    for(int i = 0;i<MAXOBJ;i++)
    { 
        data->game.player[i].inventory = " ";
        data->game.event[i].hitbox = (BoundingBox){(Vector3){0,0,0},(Vector3){0,0,0}};
        data->game.event[i].function = MQTRUE;
        data->game.event[i].position = (Vector3){0,0,0};
        data->game.event[i].rotation = 0;
        data->game.event[i].active = false;
        data->game.event[i].persistent = false;
    }
}
 */

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

Vector3 MQCheckWall(MQDATA data, char *hitboxID,float LocalRotation)
{
    int hitboxMax;
    for(int i = MAXOBJ-1;i>0;i--)
    {
        if(strcmp(data.game.event[i].name," ")==0)
        {
            hitboxMax = i;
            break;
        }
    }
    int hitboxIndex = MQFindHitbox(data, hitboxID);
    BoundingBox hitboxLocal = data.files.hitboxes[hitboxIndex].hitbox;
    
    for(int i = 0; i < hitboxMax; i++)
        if(CheckCollisionBoxes(data.files.hitboxes[i].hitbox, hitboxLocal)==true && i != hitboxIndex)
        {
            bool *LocalBool;
            LocalBool = malloc(sizeof(bool)*27);
            LocalBool = MQReturnCollisionCube( hitboxLocal, data.files.hitboxes[i].hitbox);
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
                    if(hitboxLocal.max.z-0.5 < data.files.hitboxes[i].hitbox.min.z&&hitboxLocal.max.x-0.5 < data.files.hitboxes[i].hitbox.min.x)
                        return ((Vector3){data.files.hitboxes[i].hitbox.min.x-0.10,__INT_MAX__,data.files.hitboxes[i].hitbox.min.z-0.10});
                        
                    else if(hitboxLocal.max.z-0.5 < data.files.hitboxes[i].hitbox.min.z)
                        return ((Vector3){__INT_MAX__,__INT_MAX__,data.files.hitboxes[i].hitbox.min.z-0.10});

                    else if(hitboxLocal.max.x-0.5 < data.files.hitboxes[i].hitbox.min.x)
                        return ((Vector3){data.files.hitboxes[i].hitbox.min.x-0.10,__INT_MAX__,__INT_MAX__});
                }


                if(LocalRotation>=90&&LocalRotation<180&&LocalBool[11]+LocalBool[10]+LocalBool[17]+LocalBool[2]+LocalBool[1]+LocalBool[8]+LocalBool[3]+LocalBool[0]+LocalBool[7]!=0)
                {
                    MQWALLEXCLUDEINDEX=i;
                    if(hitboxLocal.min.z+0.5 > data.files.hitboxes[i].hitbox.max.z&&hitboxLocal.max.x-0.5 < data.files.hitboxes[i].hitbox.min.x)
                        return ((Vector3){data.files.hitboxes[i].hitbox.min.x-0.10,__INT_MAX__,data.files.hitboxes[i].hitbox.max.z+0.10});
                        
                    else if(hitboxLocal.min.z+0.5 > data.files.hitboxes[i].hitbox.max.z)
                        return ((Vector3){__INT_MAX__,__INT_MAX__,data.files.hitboxes[i].hitbox.max.z+0.10});

                    else if(hitboxLocal.max.x-0.5 < data.files.hitboxes[i].hitbox.min.x)
                        return ((Vector3){data.files.hitboxes[i].hitbox.min.x-0.10,__INT_MAX__,__INT_MAX__});
                }


                if(LocalRotation>=180&&LocalRotation<270&&LocalBool[3]+LocalBool[0]+LocalBool[7]+LocalBool[4]+LocalBool[5]+LocalBool[6]+LocalBool[13]+LocalBool[14]+LocalBool[15]!=0)
                {
                    MQWALLEXCLUDEINDEX=i;
                    if(hitboxLocal.min.z+0.5 > data.files.hitboxes[i].hitbox.max.z&&hitboxLocal.min.x+0.5 > data.files.hitboxes[i].hitbox.max.x)
                        return ((Vector3){data.files.hitboxes[i].hitbox.min.x-0.10,__INT_MAX__,data.files.hitboxes[i].hitbox.max.z+0.10});
                        
                    else if(hitboxLocal.min.z+0.5 > data.files.hitboxes[i].hitbox.max.z)
                        return ((Vector3){__INT_MAX__,__INT_MAX__,data.files.hitboxes[i].hitbox.max.z+0.10});

                    else if(hitboxLocal.min.x+0.5 > data.files.hitboxes[i].hitbox.max.x)
                        return ((Vector3){data.files.hitboxes[i].hitbox.max.x+0.10,__INT_MAX__,__INT_MAX__});
                }


                if(LocalRotation>=270&&LocalRotation<=360&&LocalBool[13]+LocalBool[14]+LocalBool[15]+LocalBool[22]+LocalBool[23]+LocalBool[24]+LocalBool[21]+LocalBool[18]+LocalBool[25]!=0)
                {
                    MQWALLEXCLUDEINDEX=i;
                    if(hitboxLocal.max.z-0.5 < data.files.hitboxes[i].hitbox.min.z&&hitboxLocal.min.x+0.5 > data.files.hitboxes[i].hitbox.max.x)
                        return ((Vector3){data.files.hitboxes[i].hitbox.min.x-0.10,__INT_MAX__,data.files.hitboxes[i].hitbox.max.z+0.10});
                        
                    else if(hitboxLocal.max.z-0.5 < data.files.hitboxes[i].hitbox.min.z)
                        return ((Vector3){__INT_MAX__,__INT_MAX__,data.files.hitboxes[i].hitbox.min.z-0.10});

                    else if(hitboxLocal.min.x+0.5 > data.files.hitboxes[i].hitbox.max.x)
                        return ((Vector3){data.files.hitboxes[i].hitbox.max.x+0.10,__INT_MAX__,__INT_MAX__});
                }
            } 
            MQWALLEXCLUDEINDEX = __INT_MAX__;
        }
    MQWALLEXCLUDEINDEX = __INT_MAX__;
    return ((Vector3){__INT_MAX__,__INT_MAX__,__INT_MAX__});
}

float MQReturnPlayerLegsColisionHeight(MQDATA data, int quem)
{
    char bufferlocal[64];
    BoundingBox pdireita, pesquerda;
    int indexd,indexe;

    snprintf(bufferlocal,64,"player-pernad%d",quem);
    indexd = MQFindHitbox(data,bufferlocal);
    snprintf(bufferlocal,64,"player-pernae%d",quem);
    indexe = MQFindHitbox(data,bufferlocal);

    pdireita = data.files.hitboxes[indexd].hitbox;
    pesquerda = data.files.hitboxes[indexe].hitbox;

    for(int i = 0; i < MAXOBJ; i++)
    {
        if(i != indexd&&i != indexe)
        {
            if(CheckCollisionBoxes(data.files.hitboxes[i].hitbox,pdireita)==true)
            {
                return data.files.hitboxes[i].hitbox.max.y;
            }
            else if(CheckCollisionBoxes(data.files.hitboxes[i].hitbox,pesquerda)==true)
            {
                return data.files.hitboxes[i].hitbox.max.y;
            }
        }
        
    }
    return MQFALSE;
}

void MQPlayerConfigStart(MQDATA *data, int quem, Vector3 posi)
{
    //tipos
    //0 - calca
    //1 - chapeu
    //2 - camisa
    //3 - sapatos
    //4 - oculos
    //5 - arma
    data->game.player[quem].fallTime = 0;
    data->game.player[quem].rotation = 180;
    data->game.player[quem].position.y = posi.y;
    data->game.player[quem].position.x = posi.x;
    data->game.player[quem].position.z = posi.z;
    data->game.player[quem].speed = 0.1f;
}

Vector3 MQPlayerMove(Vector3 position, float rotation, float speed)
{
    //z+ frente
    //x+ esquerda
    float  valorZ, valorX;
    int giro = rotation / 90;
    float resto = rotation - (90 * giro);
    float restodoresto = 90 - resto;
    valorZ = speed - resto * (speed / 90);
    valorX = speed - restodoresto * (speed / 90);
    switch(giro)
    {
        case 0:
        {
            position.z += valorZ;
            position.x += valorX;
        }
        break;
        case 1:
        {
            position.z -= valorX;
            position.x += valorZ;
        }
        break;
        case 2:
        {
            position.z -= valorZ;
            position.x -= valorX;
        }
        break;
        case 3:
        {
            position.z += valorX;
            position.x -= valorZ;
        }
        break;
    }
    return position;
}

