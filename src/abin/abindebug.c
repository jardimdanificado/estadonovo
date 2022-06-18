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
