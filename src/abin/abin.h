struct ABINMenu
{
    int ponteiro, max;
    bool estaAberto;
    char atual[64],*fileloc;
};
typedef struct ABINMenu ABINMenu;

bool AbinGlobalIsDebug = false;

#include "abincore.c"
#include "abindebug.c"
#include "abinary.c"
