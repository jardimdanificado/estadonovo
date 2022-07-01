//ABINary DATA
char ABINCACHE4[4];
char ABINCACHE8[8];
char ABINCACHE16[16];
char ABINCACHE32[32];
char ABINCACHE64[64];
char ABINCACHE128[128];
char ABINCACHE256[256];
char ABINCACHE512[512];
void HELP()
{
    printf("help       abin_help\n---------- FILE_MANAGER\ncreatefile abin_createfile_file\ndeletefile abin_deletefile_file\ncheckfile  abin_checkfile_file\ncopyfile   abin_copyfile_file_destfile\nmovefile   abin_movefile_file_destfile\nrenamefile abin_renamefile_file_destfile\nreadfile   abin_readfile_file\n---------- DATA_MANAGER\nfind       abin_find_file_keyword\nchange     abin_change_file_ID\nedit       abin_edit_file_ID\nremove     abin_remove_file_ID\nclean      abin_clean_file_ID\nadd        abin_add_file_ID_data\n");
}

char *abinCoreRemoveExtension(char *myStr)
{
    char *retStr;
    char *lastExt;
    if(myStr == NULL) return NULL;
    if((retStr = malloc(strlen(myStr) + 1)) == NULL) return NULL;
    strcpy(retStr, myStr);
    lastExt = strrchr(retStr, '.');
    if(lastExt != NULL)
        *lastExt = '\0';
    return retStr;
}

const char *abinCoreFileExtension(const char path[])
{
    const char *result;
    int i, n;

    assert(path != NULL);
    n = strlen(path);
    i = n - 1;
    while((i >= 0) && (path[i] != '.') && (path[i] != '/') & (path[i] != '\\'))
    {
        i--;
    }
    if((i > 0) && (path[i] == '.') && (path[i - 1] != '/') && (path[i - 1] != '\\'))
    {
        result = path + i;
    }
    else
    {
        result = path + n;
    }
    return result;
}

char *abinCoreInt2Str(int input)
{
    char bufferzin[64];
    snprintf(bufferzin, 64, "%d", input);
    strcpy(ABINCACHE64, bufferzin);
    return ABINCACHE64;
}

char *abinCoreFloat2Str(float input)
{
    char bufferzin[64];
    snprintf(bufferzin, 64, "%f", input);
    strcpy(ABINCACHE64, bufferzin);
    return ABINCACHE64;
}

void abinCoreChangeType(char *file, char *keyword, char *new, char *msg)
{
    char buff[255], ultimaInfo[255];
    FILE *existente, *novo;
    char fileNovoString[255];
    snprintf(fileNovoString, 255, "%s.abak", file);
    existente = fopen(file, "r+");
    novo = fopen(fileNovoString, "w");
    bool isValue = false;
    int contador = 0;
    while(fscanf(existente, "%s", buff) != EOF)
    {
        if(isValue == false)
        {
            if(strcmp(buff, keyword) == 0)
            {
                msg = malloc(sizeof(char) * 512);
                snprintf(msg, 512, "%s ", new);
                fputs(msg, novo);
            }
            else
            {
                msg = malloc(sizeof(char) * 512);
                snprintf(msg, 512, "%s ", buff);
                fputs(msg, novo);
            }


            for(int i = 0; i < 255; i++)
            {
                ultimaInfo[i] = buff[i];
            }
            isValue = true;
        }
        else
        {
            if(strcmp(ultimaInfo, keyword) == 0)
            {
                fputs(buff, novo);
                fputs("\n", novo);
            }
            else
            {
                fputs(buff, novo);
                fputs("\n", novo);
            }
            contador++;
            isValue = false;
        }
    }
    fclose(existente);
    fclose(novo);
    remove(file);
    rename(fileNovoString, file);
}

void abinCoreFileRead(char *file)
{
    char buff[255];
    FILE *existente;
    bool isValue = false;
    existente = fopen(file, "r+");
    printf("\n");
    while(fscanf(existente, "%s", buff) != EOF)
    {
        if(isValue == true)
        {
            printf("%s\n", buff);
            isValue = false;
        }
        else
        {
            printf("%s ", buff);
            isValue = true;
        }
    }
    printf("\n");
}

int abinCoreFindLine(char *file, char *keyword)
{
    FILE *save;
    char buff[255], ultimaInfo[255];
    save = fopen(file, "r");
    bool isValue = false;
    int contador = 0;
    bool LOCALexit = false;
    while(fscanf(save, "%s", buff) != EOF && LOCALexit == false)
    {
        if(isValue == false)
        {
            if(contador > 0)
            {
                for(int i = 0; i < 255; i++)
                {
                    ultimaInfo[i] = buff[i];
                }
                isValue = true;
            }
            else if(contador == 0)
            {
                if(strcmp(keyword, buff) == 0)
                    LOCALexit = true;
            }
        }
        else
        {
            if(strcmp(keyword, buff) == 0)
            {
                LOCALexit = true;
            }
            else if(strcmp(keyword, ultimaInfo) == 0)
            {
                LOCALexit = true;
            }
            if(LOCALexit == false)
                contador++;
            isValue = false;
        }
    }
    fclose(save);
    return contador;
}

char *abinCoreReturnData(char *file, char *keyword)
{
    FILE *save;
    char buff[255], ultimaInfo[255];
    save = fopen(file, "r");
    bool isValue = false;
    static char msgl[255];
    while(fscanf(save, "%s", buff) != EOF)
    {
        if(isValue == false)
        {
            for(int i = 0; i < 255; i++)
            {
                ultimaInfo[i] = buff[i];
            }
            isValue = true;
        }
        else
        {
            if(strcmp(keyword, ultimaInfo) == 0)
            {
                strcpy(msgl, buff);
                fclose(save);
                return msgl;
            }
            else
            {
                isValue = false;
            }
        }
    }
    fclose(save);
    return ("ERROR");
}

bool abinCoreFileCheck(const char *filename)
{
    FILE *file;
    file = fopen(filename, "r");
    if(file)
    {
        fclose(file);
        return true;
    }
    else
    {

        return false;
    }
}

void abinCoreRemoveData(char *file, char *keyword)
{
    char *msg;
    char buff[255], ultimaInfo[255];
    FILE *existente, *novo;
    char fileNovoString[255];
    snprintf(fileNovoString, 255, "%s.abak", file);
    existente = fopen(file, "r+");
    novo = fopen(fileNovoString, "w");
    bool isValue = false;
    int contador = 0;
    while(fscanf(existente, "%s", buff) != EOF)
    {
        if(isValue == false)
        {
            if(strcmp(buff, keyword) != 0)
            {
                msg = malloc(sizeof(char) * 512);
                snprintf(msg, 512, "%s ", buff);
                fputs(msg, novo);
            }
            for(int i = 0; i < 255; i++)
            {
                ultimaInfo[i] = buff[i];
            }
            isValue = true;
        }
        else
        {
            if(strcmp(ultimaInfo, keyword) != 0)
            {
                fputs(buff, novo);
                fputs("\n", novo);
            }
            contador++;
            isValue = false;
        }
    }
    fclose(existente);
    fclose(novo);
    remove(file);
    rename(fileNovoString, file);
}

void abinCoreCleanData(char *file, char *keyword, char *msg)
{
    char buff[255], ultimaInfo[255];
    FILE *existente, *novo;
    char fileNovoString[255];
    snprintf(fileNovoString, 255, "%s.abak", file);
    existente = fopen(file, "r+");
    novo = fopen(fileNovoString, "w");
    bool isValue = false;
    int contador = 0;
    while(fscanf(existente, "%s", buff) != EOF)
    {
        if(isValue == false)
        {
            msg = malloc(sizeof(char) * 512);
            snprintf(msg, 512, "%s ", buff);
            fputs(msg, novo);
            for(int i = 0; i < 255; i++)
            {
                ultimaInfo[i] = buff[i];
            }
            isValue = true;
        }
        else
        {
            if(strcmp(ultimaInfo, keyword) == 0)
            {
                fputs("vazio", novo);
                fputs("\n", novo);
            }
            else
            {
                fputs(buff, novo);
                fputs("\n", novo);
            }
            contador++;
            isValue = false;
        }
    }
    fclose(existente);
    fclose(novo);
    remove(file);
    rename(fileNovoString, file);
}

void abinCoreEditData(char *file, char *keyword, char *new)
{
    char *msg;
    char buff[255], ultimaInfo[255];
    FILE *existente, *novo;
    char fileNovoString[255];
    snprintf(fileNovoString, 255, "%s.abak", file);
    existente = fopen(file, "r+");
    novo = fopen(fileNovoString, "w");
    bool isValue = false;
    int contador = 0;
    while(fscanf(existente, "%s", buff) != EOF)
    {
        if(isValue == false)
        {
            msg = malloc(sizeof(char) * 512);
            snprintf(msg, 512, "%s ", buff);
            fputs(msg, novo);
            for(int i = 0; i < 255; i++)
            {
                ultimaInfo[i] = buff[i];
            }
            isValue = true;
        }
        else
        {
            if(strcmp(ultimaInfo, keyword) == 0)
            {
                fputs(new, novo);
                fputs("\n", novo);
            }
            else
            {
                fputs(buff, novo);
                fputs("\n", novo);
            }
            contador++;
            isValue = false;
        }
    }
    fclose(existente);
    fclose(novo);
    remove(file);
    rename(fileNovoString, file);
}

void abinCoreFileCopy(char *file, char *dest)
{
    char caracter;
    FILE *existente, *novo;
    existente = fopen(file, "r+");
    novo = fopen(dest, "w+");
    caracter = fgetc(existente);
    while(caracter != EOF)
    {
        fputc(caracter, novo);
        caracter = fgetc(existente);
    }
    fclose(existente);
    fclose(novo);
}

void abinCoreFileMove(char *file, char *dest)
{
    abinCoreFileCopy(file, dest);
    remove(file);
}

void abinCoreAddNewData(char *fileloc, char *type, char *new)
{
    char caracter;
    FILE *existente, *novo;
    snprintf(ABINCACHE512, 512, "%s.new", fileloc);
    existente = fopen(fileloc, "r+");
    novo = fopen(ABINCACHE512, "w+");
    caracter = fgetc(existente);
    while(caracter != EOF)
    {
        fputc(caracter, novo);
        caracter = fgetc(existente);
    }
    fputs(type, novo);
    fputc(' ', novo);
    fputs(new, novo);
    fputs("\n", novo);
    fclose(existente);
    fclose(novo);
    remove(fileloc);
    abinCoreFileMove(ABINCACHE512, fileloc);
}

bool abinCoreFileCreate(char *file)
{
    FILE *fp;
    fp = fopen(file, "w+");
    fputs("SIZE 0\n", fp);
    fclose(fp);
    return true;
}

void abinDEBUGcreate ( char* fileloc )
{
    char bufferzin[4];
    FILE * fp;
    fp = fopen ( fileloc, "w+" );
    for ( int i =0; i<512; i++ )
    {
        fputs ( "debug", fp );

        snprintf ( bufferzin, 4, "%d", i );
        fputs ( bufferzin,fp );
        fputs ( " vazio\n",fp );
    }
    fclose ( fp );
}

void abinDEBUGtext ( char* fileloc,char* input )
{
    if ( AbinGlobalIsDebug == false )
    {
        abinDEBUGcreate ( fileloc );
        AbinGlobalIsDebug = true;
    }
    char buff[35];
    for ( int i =0; i<512; i++ )
    {
        snprintf ( buff,35,"debug%d",i );
        if ( strcmp ( abinCoreReturnData ( fileloc,buff ),"vazio" ) == 0 )
        {
            abinCoreEditData ( fileloc,buff,input );
            i = 4544;
        }
    }
}

void abinDEBUGint ( char* fileloc,int input )
{
    if ( AbinGlobalIsDebug == false )
    {
        abinDEBUGcreate ( fileloc );
        AbinGlobalIsDebug = true;
    }
    char buff[35],traducao[30];
    snprintf ( traducao,30,"%d",input );
    for ( int i =0; i<10; i++ )
    {
        snprintf ( buff,35,"debug%d",i );
        if ( strcmp ( abinCoreReturnData ( fileloc,buff ),"vazio" ) == 0 )
        {
            abinCoreEditData ( fileloc,buff,traducao );
            i=98746546;
        }
    }
}

void abinDEBUGfloat ( char* fileloc,float input )
{
    if ( AbinGlobalIsDebug == false )
    {
        abinDEBUGcreate ( fileloc );
        AbinGlobalIsDebug = true;
    }
    char buff[35],traducao[30];
    snprintf ( traducao,30,"%f",input );
    for ( int i =0; i<20; i++ )
    {
        snprintf ( buff,35,"debug%d",i );
        if ( strcmp ( abinCoreReturnData ( fileloc,buff ),"vazio" ) == 0 )
        {
            abinCoreEditData ( fileloc,buff,traducao );
            i=8391273;
        }
    }
}
