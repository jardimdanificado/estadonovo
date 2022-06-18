bool MQBulletCheckFloor(BoundingBox hitbox, DATA data)
{
    if(CheckCollisionBoxes(hitbox, data.file.mapa.hitboxHorizontal[0]))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MQBulletCheckWall(BoundingBox hitbox, DATA data)
{
    for(int i = 0; i < MAXOBJ; i++)
    {
        if(CheckCollisionBoxes(hitbox, data.file.mapa.hitboxVertical[i]))
        {
            return true;
        }
        else if(CheckCollisionBoxes(hitbox, data.file.mapa.props[i].hitbox))
        {
            return true;
        }
        else if(CheckCollisionBoxes(hitbox, data.file.mapa.porta.slots[i].hitbox))
        {
            return true;
        }
    }
    return false;
}

void MQBulletUpdate(DATA *data,  int qualArma)
{
    for(int i = 0; i < 255; i++)
    {
        if(data->file.mapa.balas[i].existe == true && data->file.mapa.balas[i].parou == false && clock() > (data->file.mapa.balas[i].relogio) + (CLOCKS_PER_SEC / 200))
        {
            if(data->file.mapa.balas[i].velocidade > 0.3)
                data->file.mapa.balas[i].velocidade -= 0.001;

            switch(data->file.mapa.balas[i].rotacao)
            {
                case 0:
                {
                    data->file.mapa.balas[i].posicao.z += data->file.mapa.balas[i].velocidade / 1.5f;
                }
                break;
                case 360:
                {
                    data->file.mapa.balas[i].posicao.z += data->file.mapa.balas[i].velocidade / 1.5f;
                }
                break;
                case 45:
                {
                    data->file.mapa.balas[i].posicao.z += data->file.mapa.balas[i].velocidade / 3;
                    data->file.mapa.balas[i].posicao.x += data->file.mapa.balas[i].velocidade / 3;
                }
                break;
                case 90:
                {
                    data->file.mapa.balas[i].posicao.x += data->file.mapa.balas[i].velocidade / 1.5f;
                }
                break;
                case 135:
                {
                    data->file.mapa.balas[i].posicao.z -= data->file.mapa.balas[i].velocidade / 3;
                    data->file.mapa.balas[i].posicao.x += data->file.mapa.balas[i].velocidade / 3;
                }
                break;
                case 180:
                {
                    data->file.mapa.balas[i].posicao.z -= data->file.mapa.balas[i].velocidade / 1.5f;
                }
                break;
                case 225:
                {
                    data->file.mapa.balas[i].posicao.z -= data->file.mapa.balas[i].velocidade / 3;
                    data->file.mapa.balas[i].posicao.x -= data->file.mapa.balas[i].velocidade / 3;
                }
                break;
                case 270:
                {
                    data->file.mapa.balas[i].posicao.x -= data->file.mapa.balas[i].velocidade / 1.5f;
                }
                break;
                case 315:
                {
                    data->file.mapa.balas[i].posicao.z += data->file.mapa.balas[i].velocidade / 3;
                    data->file.mapa.balas[i].posicao.x -= data->file.mapa.balas[i].velocidade / 3;
                }
                break;
            }
        }
        if(data->file.mapa.balas[i].existe == true)
        {
            data->file.mapa.balas[i].hitbox = GetModelBoundingBox(data->file.mapa.balasGLOBAL.modelo);
            data->file.mapa.balas[i].hitbox.max.x += data->file.mapa.balas[i].posicao.x;
            data->file.mapa.balas[i].hitbox.min.x += data->file.mapa.balas[i].posicao.x;
            data->file.mapa.balas[i].hitbox.max.y += data->file.mapa.balas[i].posicao.y;
            data->file.mapa.balas[i].hitbox.min.y += data->file.mapa.balas[i].posicao.y;
            data->file.mapa.balas[i].hitbox.max.z += data->file.mapa.balas[i].posicao.z;
            data->file.mapa.balas[i].hitbox.min.z += data->file.mapa.balas[i].posicao.z;
            if(MQBulletCheckFloor(data->file.mapa.balas[i].hitbox, *data) == true || MQBulletCheckWall(data->file.mapa.balas[i].hitbox, *data) == true)
            {
                data->file.mapa.balas[i].parou = true;
            }
            else if(clock() > data->file.mapa.balas[i].relogioCriado + CLOCKS_PER_SEC)
            {
                data->file.mapa.balas[i].existe = false;
            }
        }
    }
}

void MQBulletCreate(DATA *data, Vector3 posicao, int rotacao, int qualArma)
{
    for(int i = 0; i < 255; i++)
    {
        if(data->file.mapa.balas[i].existe == false)
        {
            switch(rotacao)
            {
                case 0:
                {
                    data->file.mapa.balas[i].posicao.x = 0.04375 + posicao.x;
                    data->file.mapa.balas[i].posicao.y = 1.8 + posicao.y;
                    data->file.mapa.balas[i].posicao.z = 1.16875 + posicao.z;
                }
                break;
                case 360:
                {
                    data->file.mapa.balas[i].posicao.x = 0.04375 + posicao.x;
                    data->file.mapa.balas[i].posicao.y = 1.8 + posicao.y;
                    data->file.mapa.balas[i].posicao.z = -1.16875 + posicao.z;
                }
                break;
                case 45:
                {
                    data->file.mapa.balas[i].posicao.x = 0.83750 + posicao.x;
                    data->file.mapa.balas[i].posicao.y = 1.80000 + posicao.y;
                    data->file.mapa.balas[i].posicao.z = 0.76250 + posicao.z;
                }
                break;
                case 90:
                {
                    data->file.mapa.balas[i].posicao.x = 1.16875 + posicao.x;
                    data->file.mapa.balas[i].posicao.y = 1.8 + posicao.y;
                    data->file.mapa.balas[i].posicao.z = 0.04375 + posicao.z;
                }
                break;
                case 135:
                {
                    data->file.mapa.balas[i].posicao.x = 0.83750 + posicao.x;
                    data->file.mapa.balas[i].posicao.y = 1.80000 + posicao.y;
                    data->file.mapa.balas[i].posicao.z = -0.76250 + posicao.z;
                }
                break;
                case 180:
                {
                    data->file.mapa.balas[i].posicao.x = -0.04375 + posicao.x;
                    data->file.mapa.balas[i].posicao.y = 1.80625 + posicao.y;
                    data->file.mapa.balas[i].posicao.z = -1.16875 + posicao.z;
                }
                break;
                case 225:
                {
                    data->file.mapa.balas[i].posicao.x = -0.83750 + posicao.x;
                    data->file.mapa.balas[i].posicao.y = 1.80000 + posicao.y;
                    data->file.mapa.balas[i].posicao.z = -0.76250 + posicao.z;
                }
                break;
                case 270:
                {
                    data->file.mapa.balas[i].posicao.x = -1.16875 + posicao.x;
                    data->file.mapa.balas[i].posicao.y = 1.80625 + posicao.y;
                    data->file.mapa.balas[i].posicao.z = -0.04375 + posicao.z;
                }
                break;
                case 315:
                {
                    data->file.mapa.balas[i].posicao.x = -0.83750 + posicao.x;
                    data->file.mapa.balas[i].posicao.y = 1.80000 + posicao.y;
                    data->file.mapa.balas[i].posicao.z = 0.76250 + posicao.z;
                }
                break;
            }
            data->file.mapa.balas[i].velocidade = 2;
            data->file.mapa.balas[i].rotacao = rotacao;
            data->file.mapa.balas[i].relogioCriado = clock();
            data->file.mapa.balas[i].relogio = clock();
            data->file.mapa.balas[i].existe = true;
            data->file.mapa.balas[i].parou = false;
            i = 300;
        }
    }
}
