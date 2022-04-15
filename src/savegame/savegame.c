bool VERIFICANUM(char letra)
{
    if(letra == '0'||letra == '1'||letra == '2'||letra == '3'||letra == '4'||letra == '5'||letra == '6'||letra == '7'||letra == '8'||letra == '9')
    {
        return true;
    }
    else{return false;}
}

int LOAD_DECRYPT(char letra)
{
    if(letra == 'i')
    {
        return 0;
    }
    else if(letra == 'e')
    {
        return 1;
    }
    else if(letra == 'a')
    {
        return 2;
    }
    else if(letra == 'p')
    {
        return 3;
    }
    else if(letra == 'x')
    {
        return 4;
    }
    else if(letra == 'y')
    {
        return 5;
    }
    else if(letra == 'z')
    {
        return 6;
    }
    else
    {
        return -1;
    }
}
// i=0
// e=1
// a=2
// p=3
// x=4
// y=5
// z=6
void LOAD_GAME(PERSONAGEM* personagem, MAPA* mapa, NPC0* humano)
{
    FILE *save;  
	char buff[25],ultimaInfo[4];//creating char array to store data of file  
	save = fopen("savegame", "r");  
    bool eUmValor = false;
    
	while(fscanf(save, "%s", buff)!=EOF)
	{
        
		//printf("%s ", buff );  
        if(eUmValor == false)
        {
            ultimaInfo[0] = buff[0];
            ultimaInfo[1] = buff[1];
            ultimaInfo[2] = buff[2];
            eUmValor = true;
        }
        else
        {
            if(ultimaInfo[0] == 'i'&&ultimaInfo[1] == 'p'&&ultimaInfo[2] == 'x')
            {
                personagem->posicao.x = atof(buff);
            }
            else if(ultimaInfo[0] == 'i'&&ultimaInfo[1] == 'p'&&ultimaInfo[2] == 'y')
            {
                personagem->posicao.y = atof(buff);
            }
            else if(ultimaInfo[0] == 'i'&&ultimaInfo[1] == 'p'&&ultimaInfo[2] == 'z')
            {
                personagem->posicao.z = atof(buff);
            }
            else if(ultimaInfo[0] == 'i'&&ultimaInfo[1] == 'e'&&ultimaInfo[2] == 'p')
            {
                personagem->rotacao = atof(buff);
            }
            else if(ultimaInfo[0] == 'e'&&ultimaInfo[1] == 'p'&&ultimaInfo[2] == 'e')
            {
                personagem->equip.oculos.ponteiro = atoi(buff);
            }
            else if(ultimaInfo[0] == 'e'&&ultimaInfo[1] == 'p'&&ultimaInfo[2] == 'a')
            {
                personagem->equip.chapeu.ponteiro = atoi(buff);
            }
            else if(ultimaInfo[0] == 'e'&&ultimaInfo[1] == 'p'&&ultimaInfo[2] == 'x')
            {
                personagem->equip.camisa.ponteiro = atoi(buff);
            }
            else if(ultimaInfo[0] == 'e'&&ultimaInfo[1] == 'p'&&ultimaInfo[2] == 'y')
            {
                personagem->equip.sapato.ponteiro = atoi(buff);
            }
            else if(ultimaInfo[0] == 'e'&&ultimaInfo[1] == 'p'&&ultimaInfo[2] == 'p')
            {
                personagem->equip.calca.ponteiro = atoi(buff);
            }
            else if(ultimaInfo[0] == 'a'&&ultimaInfo[1] == 'p'&&ultimaInfo[2] == 'y')
            {
                personagem->equip.arma.ponteiro = atoi(buff);
            }
            else if(ultimaInfo[0] == 'a'&&ultimaInfo[1] == 'p'&&ultimaInfo[2] == 'p')
            {
                personagem->equip.arma.municao = atoi(buff);
            }
            else if(ultimaInfo[0] == 'a'&&ultimaInfo[1] == 'p'&&ultimaInfo[2] == 'e')
            {
                personagem->equip.arma.municaoReserva = atoi(buff);
            }
            else if(ultimaInfo[0] == 'a'&&ultimaInfo[1] == 'p'&&ultimaInfo[2] == 'x')
            {
                personagem->equip.arma.municaoMax = atoi(buff);
            }
            else if(ultimaInfo[0] == 'p'&&ultimaInfo[1] == 'a'&&ultimaInfo[2] == 'z')
            {
                mapa->mapaAtual = atoi(buff);
            }
            else if(ultimaInfo[0] == 'p'&&ultimaInfo[1] == 'e'&&ultimaInfo[2] == 'p')
            {
                for(int i = 0;i<10;i++)
                {
                    if(atoi(ultimaInfo) == i)
                    {
                        mapa->porta.slots[i].aberta = atoi(buff);
                    }
                }
            }
            else if(ultimaInfo[0] == 'p'&&ultimaInfo[1] == 'e'&&ultimaInfo[2] == 'e')
            {
                for(int i = 0;i<10;i++)
                {
                    if(atoi(ultimaInfo) == i)
                    {
                        mapa->porta.slots[i].trancada = atoi(buff);
                    }
                }
            }
            else if(ultimaInfo[0] == 'p'&&ultimaInfo[1] == 'a'&&ultimaInfo[2] == 'p')
            {
                for(int i = 0;i<10;i++)
                {
                    if(atoi(ultimaInfo) == i)
                    {
                        mapa->item[i].pegou = atoi(buff);
                    }
                }
            }
            else if(ultimaInfo[0] == 'p'&&ultimaInfo[1] == 'p'&&ultimaInfo[2] == 'p')
            {
                for(int i = 0;i<10;i++)
                {
                    if(atoi(ultimaInfo) == i)
                    {
                        mapa->drops[i].ponteiro = atoi(buff);
                    }
                }
            }
            else if(ultimaInfo[0] == 'p'&&ultimaInfo[1] == 'p'&&ultimaInfo[2] == 'i')
            {
                for(int i = 0;i<10;i++)
                {
                    if(atoi(ultimaInfo) == i)
                    {
                        mapa->drops[i].ocupado = atoi(buff);
                    }
                }
            }
            else if(ultimaInfo[0] == 'p'&&ultimaInfo[1] == 'p'&&ultimaInfo[2] == 'a')
            {
                for(int i = 0;i<10;i++)
                {
                    if(atoi(ultimaInfo) == i)
                    {
                        mapa->drops[i].tipo = atoi(buff);
                    }
                }
            }
            else if(ultimaInfo[0] == 'p'&&ultimaInfo[1] == 'p'&&ultimaInfo[2] == 'x')
            {
                for(int i = 0;i<10;i++)
                {
                    if(atoi(ultimaInfo) == i)
                    {
                        mapa->drops[i].posicao.x = atoi(buff);
                    }
                }
            }
            else if(ultimaInfo[0] == 'p'&&ultimaInfo[1] == 'p'&&ultimaInfo[2] == 'y')
            {
                for(int i = 0;i<10;i++)
                {
                    if(atoi(ultimaInfo) == i)
                    {
                        mapa->drops[i].posicao.y = atoi(buff);
                    }
                }
            }
            else if(ultimaInfo[0] == 'p'&&ultimaInfo[1] == 'p'&&ultimaInfo[2] == 'z')
            {
                for(int i = 0;i<10;i++)
                {
                    if(atoi(ultimaInfo) == i)
                    {
                        mapa->drops[i].posicao.z = atoi(buff);
                    }
                }
            }
            
            eUmValor = false;
        }
	}
	fclose(save);  
}
// i=0
// e=1
// a=2
// p=3
// x=4
// y=5
// z=6


void SAVE_GAME(PERSONAGEM personagem, MAPA mapa, NPC0 humano)
{
    FILE *save;
    save = fopen ("savegame", "w+");
    SAVE sv;
    snprintf(sv.x, 30, "ipx %.2f \n",personagem.posicao.x);
    snprintf(sv.y, 30, "ipy %.2f \n",personagem.posicao.y);
    snprintf(sv.z, 30, "ipz %.2f \n",personagem.posicao.z);
    snprintf(sv.r, 30, "iep %.2f \n",personagem.rotacao);
    snprintf(sv.eoculos, 30, "epe %d \n",personagem.equip.oculos.ponteiro);
    snprintf(sv.echapeu, 30, "epa %d \n",personagem.equip.chapeu.ponteiro);
    snprintf(sv.ecamisa, 30, "epx %d \n",personagem.equip.camisa.ponteiro);
    snprintf(sv.esapato, 30, "epy %d \n",personagem.equip.sapato.ponteiro);
    snprintf(sv.ecalca, 30, "epp %d \n",personagem.equip.calca.ponteiro);
    snprintf(sv.earma, 30, "apy %d \n",personagem.equip.arma.ponteiro);
    snprintf(sv.armaMuni, 30, "app %d \n",personagem.equip.arma.municao);
    snprintf(sv.armaMuniR, 30, "ape %d \n",personagem.equip.arma.municaoReserva);
    snprintf( sv.armaMuniMax, 30, "apx %d \n",personagem.equip.arma.municaoMax);
    snprintf( sv.mapa, 30, "paz %d \n",mapa.mapaAtual);
    for(int i = 0; i<10;i++)
    {
        snprintf( sv.porta[i].aberta , 30, "pep%d %d \n",i,mapa.porta.slots[i].aberta);
        snprintf( sv.porta[i].trancada, 30, "pee%d %d \n",i,mapa.porta.slots[i].trancada);
        snprintf( sv.item[i].pegou, 30, "pap%d %d \n",i,mapa.item[i].pegou);
        snprintf( sv.drops[i].ponteiro, 30, "ppp%d %d \n",i,mapa.drops[i].ponteiro);
        snprintf( sv.drops[i].ocupado, 30, "ppi%d %d \n",i,mapa.drops[i].ocupado);
        snprintf( sv.drops[i].tipo, 30, "ppa%d %d \n",i,mapa.drops[i].tipo);
        snprintf( sv.drops[i].posicao.x, 30, "ppx%d %.2f \n",i,mapa.drops[i].posicao.x);
        snprintf( sv.drops[i].posicao.y, 30, "ppy%d %.2f \n",i,mapa.drops[i].posicao.y);
        snprintf( sv.drops[i].posicao.z, 30, "ppz%d %.2f \n",i,mapa.drops[i].posicao.z);
    }
    char PortaEItem[260],drops[830];
    for(int i = 0; i<10;i++)
    {
        strcpy(PortaEItem,sv.porta[i].aberta);
        strcpy(PortaEItem,sv.porta[i].trancada);
        strcpy(PortaEItem,sv.item[i].pegou);
        strcpy(drops,sv.drops[i].ponteiro);
        strcpy(drops,sv.drops[i].ocupado);
        strcpy(drops,sv.drops[i].tipo);
        strcpy(drops,sv.drops[i].posicao.x);
        strcpy(drops,sv.drops[i].posicao.y);
        strcpy(drops,sv.drops[i].posicao.z);
    }
    fprintf(save,"%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",sv.x,sv.y,sv.z,sv.r,sv.eoculos,sv.echapeu,sv.ecamisa,sv.esapato,sv.ecalca,sv.earma,sv.armaMuni,sv.armaMuniR,sv.armaMuniMax,sv.mapa,PortaEItem,drops);
    fclose (save);
}
