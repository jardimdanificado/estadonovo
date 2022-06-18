
// bool MQAIHumanUse(  DATA* data)
// {
//     for(int i = 0; i<MAXOBJ; i++)
//     {
//         if(CheckCollisionBoxes(data->game.hitbox.personagem[0].hitbox.use, data->file.mapa.porta.slots[i].hitbox) == true||CheckCollisionBoxes(data->game.hitbox.personagem[0].hitbox.atual , data->file.mapa.porta.slots[i].hitbox) == true)
//         {
//             if(data->file.mapa.porta.slots[i].aberta == false)
//             {
//                 data->file.mapa.porta.slots[i].abrindo = true;
//                 data->game.boolean.personagem[0].usando = false;
//                 data->session.relogio.personagem[0].relogioLogs = clock();
//                 return true;
//             }
//             else if(data->file.mapa.porta.slots[i].aberta == true)
//             {
//                 data->file.mapa.porta.slots[i].fechando = true;
//                 data->game.boolean.personagem[0].usando = false;
//                 data->session.relogio.personagem[0].relogioLogs = clock();
//                 return true;
//
//             }
//             else if(data->file.mapa.porta.slots[i].trancada == true)
//             {
//                 data->game.boolean.personagem[0].usando = false;
//                 data->session.relogio.personagem[0].relogioLogs = clock();
//                 return true;
//             }
//         }
//     }
//     return false;
// }
//
// void MQAIHumanAnimUse(PERSONAGEM* humano, DATA *data, PERSONAGEM personagem)
// {
//  if(humano->relogioNovo > humano->relogioVelho+10000)
//  {
//      humano->relogioVelho = humano->relogioNovo;
// //       printf("aoba");
//  }
//  humano->relogioNovo = clock();
//
//  if(humano->relogioNovo > humano->relogioVelho+10000&&humano->modelo.frame < 2)
//      humano->modelo.frame++;
//  else if(humano->modelo.frame == 2&&humano->relogioNovo > humano->relogioVelho+10000)
//      humano->usando = false;
//  switch(humano->modelo.frame)
//  {
//      case 0:
//      {
//          humano->modelo.atual = data->file.model.personagem.use_default[0];
//             if(humano->equip.calca.ponteiro != 0)
//                 humano->equip.calca.modelo = data->file.model.item.calca[humano->equip.calca.ponteiro].use[0];
//             if(humano->equip.chapeu.ponteiro != 0)
//                 humano->equip.chapeu.modelo = data->file.model.item.chapeu[humano->equip.chapeu.ponteiro].use[0];
//             if(humano->equip.camisa.ponteiro != 0)
//                 humano->equip.camisa.modelo = data->file.model.item.camisa[humano->equip.camisa.ponteiro].use[0];
//             if(humano->equip.arma.ponteiro != 0)
//                 humano->equip.arma.modelo = data->file.model.item.arma[humano->equip.arma.ponteiro].use[0];
//      }
//      break;
//      case 1:
//      {
//          humano->modelo.atual = data->file.model.personagem.use_default[1];
//             if(humano->equip.calca.ponteiro != 0)
//                 humano->equip.calca.modelo = data->file.model.item.calca[humano->equip.calca.ponteiro].use[1];
//             if(humano->equip.chapeu.ponteiro != 0)
//                 humano->equip.chapeu.modelo = data->file.model.item.chapeu[humano->equip.chapeu.ponteiro].use[1];
//             if(humano->equip.camisa.ponteiro != 0)
//                 humano->equip.camisa.modelo = data->file.model.item.camisa[humano->equip.camisa.ponteiro].use[1];
//             if(humano->equip.arma.ponteiro != 0)
//                 humano->equip.arma.modelo = data->file.model.item.arma[humano->equip.arma.ponteiro].use[0];
//
//
//      }
//      break;
//         case 2:
//      {
//          humano->modelo.atual = data->file.model.personagem.use_default[2];
//             if(humano->equip.calca.ponteiro != 0)
//                 humano->equip.calca.modelo = data->file.model.item.calca[humano->equip.calca.ponteiro].use[2];
//             if(humano->equip.chapeu.ponteiro != 0)
//                 humano->equip.chapeu.modelo = data->file.model.item.chapeu[humano->equip.chapeu.ponteiro].use[2];
//             if(humano->equip.camisa.ponteiro != 0)
//                 humano->equip.camisa.modelo = data->file.model.item.camisa[humano->equip.camisa.ponteiro].use[2];
//             if(humano->equip.arma.ponteiro != 0)
//                 humano->equip.arma.modelo = data->file.model.item.arma[humano->equip.arma.ponteiro].use[0];
//          if(humano->usando == false)
//          {
//              humano->modelo.atual = data->file.model.personagem.idle;
//                 if(humano->equip.calca.ponteiro != 0)
//                     humano->equip.calca.modelo = data->file.model.item.calca[humano->equip.calca.ponteiro].idle;
//                 if(humano->equip.chapeu.ponteiro != 0)
//                     humano->equip.chapeu.modelo = data->file.model.item.chapeu[humano->equip.chapeu.ponteiro].idle;
//                 if(humano->equip.camisa.ponteiro != 0)
//                     humano->equip.camisa.modelo = data->file.model.item.camisa[humano->equip.camisa.ponteiro].idle;
//                 if(humano->equip.arma.ponteiro != 0)
//                     humano->equip.arma.modelo = data->file.model.item.arma[humano->equip.arma.ponteiro].idle;
//
//              //msg = " ";
//          }
//      }
//      break;
//  }
// }
//
//
// void MQAIHumanAnimRun(    int qual, DATA data)
// {
//
//     if(humano->npc[qual].relogioNovo > humano->npc[qual].relogioVelho+10000)
//     {
//         humano->npc[qual].relogioVelho = humano->npc[qual].relogioNovo;
//
//     }
//     humano->npc[qual].relogioNovo = clock();
//
//     if(humano->npc[qual].relogioNovo > humano->npc[qual].relogioVelho+10000&&humano->npc[qual].modelo.frame < 4)
//         humano->npc[qual].modelo.frame++;
//     else if(humano->npc[qual].modelo.frame == 4)
//         humano->npc[qual].modelo.frame = 0;
//
//
//  switch(humano->npc[qual].modelo.frame)
//  {
//      case 0:
//      {
//          humano->npc[qual].modelo.atual = data.file.model.personagem.run[0];
//             if(humano->npc[qual].equip.calca.ponteiro != 0)
//                 humano->npc[qual].equip.calca.modelo = data.file.model.item.calca[humano->npc[qual].equip.calca.ponteiro].run[0];
//             if(humano->npc[qual].equip.chapeu.ponteiro != 0)
//                 humano->npc[qual].equip.chapeu.modelo = data.file.model.item.chapeu[humano->npc[qual].equip.chapeu.ponteiro].run[0];
//             if(humano->npc[qual].equip.camisa.ponteiro != 0)
//                 humano->npc[qual].equip.camisa.modelo = data.file.model.item.camisa[humano->npc[qual].equip.camisa.ponteiro].run[0];
//             if(humano->npc[qual].equip.arma.ponteiro != 0)
//                 humano->npc[qual].equip.arma.modelo = data.file.model.item.arma[humano->npc[qual].equip.arma.ponteiro].run[0];
//
//      }
//      break;
//      case 1:
//      {
//          humano->npc[qual].modelo.atual = data.file.model.personagem.run[1];
//             if(humano->npc[qual].equip.calca.ponteiro != 0)
//                 humano->npc[qual].equip.calca.modelo = data.file.model.item.calca[humano->npc[qual].equip.calca.ponteiro].run[1];
//             if(humano->npc[qual].equip.chapeu.ponteiro != 0)
//                 humano->npc[qual].equip.chapeu.modelo = data.file.model.item.chapeu[humano->npc[qual].equip.chapeu.ponteiro].run[1];
//             if(humano->npc[qual].equip.camisa.ponteiro != 0)
//                 humano->npc[qual].equip.camisa.modelo = data.file.model.item.camisa[humano->npc[qual].equip.camisa.ponteiro].run[1];
//             if(humano->npc[qual].equip.arma.ponteiro != 0)
//                 humano->npc[qual].equip.arma.modelo = data.file.model.item.arma[humano->npc[qual].equip.arma.ponteiro].run[1];
//      }
//      break;
//      case 2:
//      {
//          humano->npc[qual].modelo.atual = data.file.model.personagem.run[2];
//             if(humano->npc[qual].equip.calca.ponteiro != 0)
//                 humano->npc[qual].equip.calca.modelo = data.file.model.item.calca[humano->npc[qual].equip.calca.ponteiro].run[2];
//             if(humano->npc[qual].equip.chapeu.ponteiro != 0)
//                 humano->npc[qual].equip.chapeu.modelo = data.file.model.item.chapeu[humano->npc[qual].equip.chapeu.ponteiro].run[2];
//             if(humano->npc[qual].equip.camisa.ponteiro != 0)
//                 humano->npc[qual].equip.camisa.modelo = data.file.model.item.camisa[humano->npc[qual].equip.camisa.ponteiro].run[2];
//             if(humano->npc[qual].equip.arma.ponteiro != 0)
//                 humano->npc[qual].equip.arma.modelo = data.file.model.item.arma[humano->npc[qual].equip.arma.ponteiro].run[2];
//
//      }
//      break;
//      case 3:
//      {
//          humano->npc[qual].modelo.atual = data.file.model.personagem.run[3];
//             if(humano->npc[qual].equip.calca.ponteiro != 0)
//                 humano->npc[qual].equip.calca.modelo = data.file.model.item.calca[humano->npc[qual].equip.calca.ponteiro].run[3];
//             if(humano->npc[qual].equip.chapeu.ponteiro != 0)
//                 humano->npc[qual].equip.chapeu.modelo = data.file.model.item.chapeu[humano->npc[qual].equip.chapeu.ponteiro].run[3];
//             if(humano->npc[qual].equip.camisa.ponteiro != 0)
//                 humano->npc[qual].equip.camisa.modelo = data.file.model.item.camisa[humano->npc[qual].equip.camisa.ponteiro].run[3];
//             if(humano->npc[qual].equip.arma.ponteiro != 0)
//                 humano->npc[qual].equip.arma.modelo = data.file.model.item.arma[humano->npc[qual].equip.arma.ponteiro].run[3];
//
//      }
//      break;
//      case 4:
//      {
//          humano->npc[qual].modelo.atual = data.file.model.personagem.run[4];
//             if(humano->npc[qual].equip.calca.ponteiro != 0)
//                 humano->npc[qual].equip.calca.modelo = data.file.model.item.calca[humano->npc[qual].equip.calca.ponteiro].run[4];
//             if(humano->npc[qual].equip.chapeu.ponteiro != 0)
//                 humano->npc[qual].equip.chapeu.modelo = data.file.model.item.chapeu[humano->npc[qual].equip.chapeu.ponteiro].run[4];
//             if(humano->npc[qual].equip.camisa.ponteiro != 0)
//                 humano->npc[qual].equip.camisa.modelo = data.file.model.item.camisa[humano->npc[qual].equip.camisa.ponteiro].run[4];
//             if(humano->npc[qual].equip.arma.ponteiro != 0)
//                 humano->npc[qual].equip.arma.modelo = data.file.model.item.arma[humano->npc[qual].equip.arma.ponteiro].run[4];
//      }
//      break;
//  }
// }

void MQAIHumanTargetSet(int qual, Vector3 posicao)
{
    humano->npc[qual].hitbox.andaAlvo.max.x = 0.1 + posicao.x;
    humano->npc[qual].hitbox.andaAlvo.max.y = 0.1 + posicao.y;
    humano->npc[qual].hitbox.andaAlvo.max.z = 0.1 + posicao.z;
    humano->npc[qual].hitbox.andaAlvo.min.x = -0.1 + posicao.x;
    humano->npc[qual].hitbox.andaAlvo.min.y = -0.1 + posicao.y;
    humano->npc[qual].hitbox.andaAlvo.min.z = -0.1 + posicao.z;
}

void MQAIHumanRun(DATA *data, int qual)
{
    if(humano->npc[qual].andando == false)
    {
        humano->npc[qual].andando = true;
        //humano->npc[qual].modelo.frame = 0;
    }

    if(humano->npc[qual].rotacao == -45)
    {
        humano->npc[qual].rotacao = 315;
    }
    else if(humano->npc[qual].rotacao == 405)
    {
        humano->npc[qual].rotacao = 45;
    }

    if(humano->npc[qual].rotacao == 0 || humano->npc[qual].rotacao == 360)
    {

        if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda0, humano->npc[qual].hitbox.andaAlvo))
        {
            if(MQPlayerCheckWall(humano->npc[qual], *data,   qual) == false)
            {
                humano->npc[qual].posicao.z += humano->npc[qual].velocidade;
            }
            else
            {
                for(int i = 0; i < 5; i++)
                {
                    if(CheckCollisionBoxes(humano->npc[qual].hitbox.frenteAtual, data->file.mapa.porta.slots[i].hitbox))
                    {
                        MQPlayerUsePress(&humano->npc[qual], false, * &data);
                    }
                }
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda45, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda90, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda135, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda180, humano->npc[qual].hitbox.andaAlvo))
        {
            if(clock() % 2 == 0)
            {
                humano->npc[qual].rotacao -= 45;
            }
            else
            {
                humano->npc[qual].rotacao += 45;
            }

        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda225, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda270, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda315, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
    }
    //45
    else if(humano->npc[qual].rotacao == 45)
    {
        if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda0, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda45, humano->npc[qual].hitbox.andaAlvo))
        {
            if(MQPlayerCheckWall(humano->npc[qual], *data,   qual) == false)
            {
                humano->npc[qual].posicao.z += humano->npc[qual].velocidade / 1.5;
                humano->npc[qual].posicao.x += humano->npc[qual].velocidade / 1.5;
            }
            else
            {
                for(int i = 0; i < 5; i++)
                {
                    if(CheckCollisionBoxes(humano->npc[qual].hitbox.frenteAtual, data->file.mapa.porta.slots[i].hitbox))
                    {
                        MQPlayerUsePress(&humano->npc[qual], false, * &data);
                    }
                }
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda90, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda135, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda180, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda225, humano->npc[qual].hitbox.andaAlvo))
        {
            if(clock() % 2 == 0)
            {
                humano->npc[qual].rotacao -= 45;
            }
            else
            {
                humano->npc[qual].rotacao += 45;
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda270, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda315, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
    }
    //90
    else if(humano->npc[qual].rotacao == 90)
    {
        if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda0, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda45, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda90, humano->npc[qual].hitbox.andaAlvo))
        {
            if(MQPlayerCheckWall(humano->npc[qual], *data,   qual) == false)
            {
                humano->npc[qual].posicao.x += humano->npc[qual].velocidade;
            }
            else
            {
                for(int i = 0; i < 5; i++)
                {
                    if(CheckCollisionBoxes(humano->npc[qual].hitbox.frenteAtual, data->file.mapa.porta.slots[i].hitbox))
                    {
                        MQPlayerUsePress(&humano->npc[qual], false, * &data);
                    }
                }
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda135, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda180, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda225, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda270, humano->npc[qual].hitbox.andaAlvo))
        {
            if(clock() % 2 == 0)
            {
                humano->npc[qual].rotacao -= 45;
            }
            else
            {
                humano->npc[qual].rotacao += 45;
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda315, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
    }
    //135
    else if(humano->npc[qual].rotacao == 135)
    {
        if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda0, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda45, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda90, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda135, humano->npc[qual].hitbox.andaAlvo))
        {
            if(MQPlayerCheckWall(humano->npc[qual], *data,   qual) == false)
            {
                humano->npc[qual].posicao.z -= humano->npc[qual].velocidade / 1.5;
                humano->npc[qual].posicao.x += humano->npc[qual].velocidade / 1.5;
            }
            else
            {
                for(int i = 0; i < 5; i++)
                {
                    if(CheckCollisionBoxes(humano->npc[qual].hitbox.frenteAtual, data->file.mapa.porta.slots[i].hitbox))
                    {
                        MQPlayerUsePress(&humano->npc[qual], false, * &data);
                    }
                }
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda180, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda225, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda270, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda315, humano->npc[qual].hitbox.andaAlvo))
        {
            if(clock() % 2 == 0)
            {
                humano->npc[qual].rotacao -= 45;
            }
            else
            {
                humano->npc[qual].rotacao += 45;
            }
        }
    }
    //180
    else if(humano->npc[qual].rotacao == 180)
    {
        if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda0, humano->npc[qual].hitbox.andaAlvo))
        {
            if(clock() % 2 == 0)
            {
                humano->npc[qual].rotacao -= 45;
            }
            else
            {
                humano->npc[qual].rotacao += 45;
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda45, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda90, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda135, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda180, humano->npc[qual].hitbox.andaAlvo))
        {
            if(MQPlayerCheckWall(humano->npc[qual], *data,   qual) == false)
            {
                humano->npc[qual].posicao.z -= humano->npc[qual].velocidade;
            }
            else
            {
                for(int i = 0; i < 5; i++)
                {
                    if(CheckCollisionBoxes(humano->npc[qual].hitbox.frenteAtual, data->file.mapa.porta.slots[i].hitbox))
                    {
                        MQPlayerUsePress(&humano->npc[qual], false, * &data);
                    }
                }
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda225, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda270, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda315, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
    }
    //225
    else if(humano->npc[qual].rotacao == 225)
    {
        if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda0, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda45, humano->npc[qual].hitbox.andaAlvo))
        {
            if(clock() % 2 == 0)
            {
                humano->npc[qual].rotacao -= 45;
            }
            else
            {
                humano->npc[qual].rotacao += 45;
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda90, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda135, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda180, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda225, humano->npc[qual].hitbox.andaAlvo))
        {
            if(MQPlayerCheckWall(humano->npc[qual], *data,   qual) == false)
            {
                humano->npc[qual].posicao.z -= humano->npc[qual].velocidade / 1.5;
                humano->npc[qual].posicao.x -= humano->npc[qual].velocidade / 1.5;
            }
            else
            {
                for(int i = 0; i < 5; i++)
                {
                    if(CheckCollisionBoxes(humano->npc[qual].hitbox.frenteAtual, data->file.mapa.porta.slots[i].hitbox))
                    {
                        MQPlayerUsePress(&humano->npc[qual], false, * &data);
                    }
                }
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda270, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda315, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
    }
    //270
    else if(humano->npc[qual].rotacao == 270)
    {
        if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda0, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda45, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda90, humano->npc[qual].hitbox.andaAlvo))
        {
            if(clock() % 2 == 0)
            {
                humano->npc[qual].rotacao -= 45;
            }
            else
            {
                humano->npc[qual].rotacao += 45;
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda135, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda180, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda225, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda270, humano->npc[qual].hitbox.andaAlvo))
        {
            if(MQPlayerCheckWall(humano->npc[qual], *data,  qual) == false)
            {
                humano->npc[qual].posicao.x -= humano->npc[qual].velocidade;
            }
            else
            {
                for(int i = 0; i < 5; i++)
                {
                    if(CheckCollisionBoxes(humano->npc[qual].hitbox.frenteAtual, data->file.mapa.porta.slots[i].hitbox))
                    {
                        MQPlayerUsePress(&humano->npc[qual], false, * &data);
                    }
                }
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda315, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
    }
    //315
    else if(humano->npc[qual].rotacao == 315)
    {
        if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda0, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda45, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda90, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao += 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda135, humano->npc[qual].hitbox.andaAlvo))
        {
            if(clock() % 2 == 0)
            {
                humano->npc[qual].rotacao -= 45;
            }
            else
            {
                humano->npc[qual].rotacao += 45;
            }
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda180, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda225, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda270, humano->npc[qual].hitbox.andaAlvo))
        {
            humano->npc[qual].rotacao -= 45;
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda315, humano->npc[qual].hitbox.andaAlvo))
        {
            if(MQPlayerCheckWall(humano->npc[qual], *data,   qual) == false)
            {
                humano->npc[qual].posicao.z += humano->npc[qual].velocidade / 1.5;
                humano->npc[qual].posicao.x -= humano->npc[qual].velocidade / 1.5;
            }
            else
            {
                for(int i = 0; i < 5; i++)
                {
                    if(CheckCollisionBoxes(humano->npc[qual].hitbox.frenteAtual, data->file.mapa.porta.slots[i].hitbox))
                    {
                        MQPlayerUsePress(&humano->npc[qual], false, * &data);
                    }
                }
            }
        }
    }
}

void MQAIHumanMove(DATA data,  int qual)
{
    humano->npc[qual].relogioAndaN = clock();
    if(humano->npc[qual].relogioAndaN > humano->npc[qual].relogioAndaV + 10000)
    {
        humano->npc[qual].relogioAndaV = humano->npc[qual].relogioAndaN;
        if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda45, humano->npc[qual].hitbox.andaAlvo))
        {
            ////MQAIHumanRun(  *data ,qual);
            //MQAIHumanAnimRun(personagem,   0, data);
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda135, humano->npc[qual].hitbox.andaAlvo))
        {
            ////MQAIHumanRun(  *data ,qual);
            //MQAIHumanAnimRun(personagem,   0,  data);
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda225, humano->npc[qual].hitbox.andaAlvo))
        {
            ////MQAIHumanRun(  *data ,qual);
            //MQAIHumanAnimRun(personagem,   0, data);
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda315, humano->npc[qual].hitbox.andaAlvo))
        {
            //MQAIHumanRun(  data ,qual);
            //MQAIHumanAnimRun(personagem,   0, data);
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda0, humano->npc[qual].hitbox.andaAlvo))
        {
            //MQAIHumanRun(  data ,qual);
            //MQAIHumanAnimRun(personagem,   0, data);
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda90, humano->npc[qual].hitbox.andaAlvo))
        {
            //MQAIHumanRun(  data ,qual);
            //MQAIHumanAnimRun(personagem,   0, data);
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda180, humano->npc[qual].hitbox.andaAlvo))
        {
            //MQAIHumanRun(  data ,qual);
            //MQAIHumanAnimRun(personagem,   0, data);
        }
        else if(CheckCollisionBoxes(humano->npc[qual].hitbox.anda270, humano->npc[qual].hitbox.andaAlvo))
        {
            //MQAIHumanRun(  data ,qual);
            //MQAIHumanAnimRun(personagem,   0, data);
        }
//         else
//         {
//             humano->npc[qual].andando = false;
//             //humano->npc[qual].modelo.frame = 0;
//             //humano->npc[qual].modelo.atual = data.file.model.personagem.idle;
//
//             if(humano->npc[qual].equip.calca.ponteiro != 0)
//                 humano->npc[qual].equip.calca.modelo = data.file.model.item.calca[humano->npc[qual].equip.calca.ponteiro];
//             if(humano->npc[qual].equip.chapeu.ponteiro != 0)
//                 humano->npc[qual].equip.chapeu.modelo = data.file.model.item.chapeu[humano->npc[qual].equip.chapeu.ponteiro];
//             if(humano->npc[qual].equip.camisa.ponteiro != 0)
//                 humano->npc[qual].equip.camisa.modelo = data.file.model.item.camisa[humano->npc[qual].equip.camisa.ponteiro];
//             if(humano->npc[qual].equip.arma.ponteiro != 0)
//                 humano->npc[qual].equip.arma.modelo = data.file.model.item.arma[humano->npc[qual].equip.arma.ponteiro];
//         }
    }
    //MQPlayerUpdateHitbox(&humano->npc[qual]);
}

PERSONAGEM MQAIHumanConfigStart(int qual, Vector3 posicao, DATA data)
{
    humano.npc[qual].equip.chapeu.ponteiro = 1;
    humano.npc[qual].equip.camisa.ponteiro = 1;
    humano.npc[qual].equip.oculos.ponteiro = 0;
    humano.npc[qual].equip.sapato.ponteiro = 0;
    humano.npc[qual].equip.calca.ponteiro = 1;
    humano.npc[qual].equip.arma.ponteiro = 1;
    humano.npc[qual].rotacao = 0;
    data->game.contador.frames.personagem[qual] = 0;
    humano.npc[qual].posicao.y = posicao.y;
    humano.npc[qual].posicao.x = posicao.x;
    humano.npc[qual].posicao.z = posicao.z;
    humano.npc[qual].velocidade = 0.5f;
//  humano.npc[qual].modelo.atual = data.file.model.personagem.idle;
    humano.npc[qual].pulando = false;
    humano.npc[qual].usando = false;
    humano.npc[qual].relogioNovo = 0;
    humano.npc[qual].relogioVelho = 0;
    humano.npc[qual].hitbox.andaAlvo.max.x = 0.1;
    humano.npc[qual].hitbox.andaAlvo.max.y = 0.1;
    humano.npc[qual].hitbox.andaAlvo.max.z = 0.1;
    humano.npc[qual].hitbox.andaAlvo.min.x = -0.1;
    humano.npc[qual].hitbox.andaAlvo.min.y = -0.1;
    humano.npc[qual].hitbox.andaAlvo.min.z = -0.1;

    humano.npc[qual].relogioAndaV = 0;
    humano.npc[qual].relogioAndaN = 0;

    humano.npc[qual].posicaoInicial = humano.npc[qual].posicao;

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/action.glb");
    humano.npc[qual].hitbox.useBase = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    humano.npc[qual].hitbox.atual = humano.npc[qual].hitbox.useBase;
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/pes.glb");
    humano.npc[qual].hitbox.pesBase = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/pes90.glb");
    humano.npc[qual].hitbox.pes90 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/pes180.glb");
    humano.npc[qual].hitbox.pes180 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/pes270.glb");
    humano.npc[qual].hitbox.pes270 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente.glb");
    humano.npc[qual].hitbox.frenteBase = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras.glb");
    humano.npc[qual].hitbox.trasBase = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente45.glb");
    humano.npc[qual].hitbox.frente45 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras45.glb");
    humano.npc[qual].hitbox.tras45 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente90.glb");
    humano.npc[qual].hitbox.frente90 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras90.glb");
    humano.npc[qual].hitbox.tras90 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente135.glb");
    humano.npc[qual].hitbox.frente135 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras135.glb");
    humano.npc[qual].hitbox.tras135 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente180.glb");
    humano.npc[qual].hitbox.frente180 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras180.glb");
    humano.npc[qual].hitbox.tras180 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente225.glb");
    humano.npc[qual].hitbox.frente225 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras225.glb");
    humano.npc[qual].hitbox.tras225 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente270.glb");
    humano.npc[qual].hitbox.frente270 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras270.glb");
    humano.npc[qual].hitbox.tras270 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/frente315.glb");
    humano.npc[qual].hitbox.frente315 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/hitbox/tras315.glb");
    humano.npc[qual].hitbox.tras315 = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/ai/0.glb");
    humano.npc[qual].hitbox.anda0Base = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/ai/45.glb");
    humano.npc[qual].hitbox.anda45Base = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/ai/90.glb");
    humano.npc[qual].hitbox.anda90Base = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/ai/135.glb");
    humano.npc[qual].hitbox.anda135Base = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/ai/180.glb");
    humano.npc[qual].hitbox.anda180Base = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/ai/225.glb");
    humano.npc[qual].hitbox.anda225Base = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/ai/270.glb");
    humano.npc[qual].hitbox.anda270Base = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    humano.npc[qual].hitbox.modelo = LoadModel("data/models/personagem/ai/315.glb");
    humano.npc[qual].hitbox.anda315Base = GetModelBoundingBox(humano.npc[qual].hitbox.modelo);
    UnloadModel(humano.npc[qual].hitbox.modelo);

    return (humano.npc[qual]);
}
