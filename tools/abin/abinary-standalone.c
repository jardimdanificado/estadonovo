#include "abindependencies.h"
#include "abincore.c"
struct DATA_ABINARYTEXT
{
    char argumentos[512][512];
    char valores[512][512];
};
typedef struct DATA_ABINARYTEXT DATA_ABINARYTEXT;

int abin(char *filelocation)
{
	char *buff;
    buff = malloc(512);
    FILE *existente, *novo;  
    existente = fopen(filelocation, "r+");
    char* bufferzin = abinCoreRemoveExtension(filelocation);
    snprintf(buff, 512, "%s.abin", bufferzin);
    novo = fopen(buff, "w+b");
    char bufferfixed[512];
    int counter1 = 0, counter2 = 0;
    DATA_ABINARYTEXT abindata;
    while(fscanf(existente, "%s", bufferfixed)!=EOF)
    {
        if(counter1%2==0)
        {
            strcpy(abindata.argumentos[counter2],bufferfixed);
        }
        else if(counter1%2!=0)
        {
            strcpy(abindata.valores[counter2],bufferfixed);
        }
        counter1++;
        if(counter1%2==0)
        {
            counter2 = counter1/2;
        }
    }
    fwrite(&abindata,sizeof(abindata),1,novo);
    fclose(existente);
    fclose(novo);
    free(buff);
}

int unabin(char *filelocation)
{
	char *buff;
    buff = malloc(512);
    char bufferfixed[512];
    DATA_ABINARYTEXT abindata;
    FILE *existente, *novo;  
    existente = fopen(filelocation, "r+b");
    char* bufferzin = abinCoreRemoveExtension(filelocation);
    snprintf(buff, 512, "%s.text", bufferzin);
    novo = fopen(buff, "w+");
    int counter1 = 0, counter2 = 0;
    fread(&abindata, sizeof(struct DATA_ABINARYTEXT), 1, existente);
    for(int i =0;i<512;i++)
    {
        if(counter1%2==0)
        {
            strcpy(bufferfixed,abindata.argumentos[counter2]);
            strcat(bufferfixed, " ");
            fputs(bufferfixed,novo);
        }
        else if(counter1%2!=0)
        {
            strcpy(bufferfixed,abindata.valores[counter2]);
            strcat(bufferfixed, "\n");
            fputs(bufferfixed,novo);
        }
        counter1++;
        if(counter1%2==0)
        {
            counter2 = counter1/2;
        }
    }
    fclose(existente);
    fclose(novo);
    free(bufferzin);
    free(buff);
}

int main(int argc, char *argv[2])
{    
    if(strcmp(abinCoreFileExtension(argv[1]),".abin")==0)
    {
        unabin(argv[1]);
    }
    else
    {
        abin(argv[1]);
    }
}
