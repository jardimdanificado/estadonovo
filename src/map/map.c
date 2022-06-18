#include "./lvl0.c"//lvl0

void MAPA_START(DATA *data)
{

    data->file.mapa.balasGLOBAL.todasBalasUsadas = false;
    for(int i = 0; i < 255; i++)
    {
        data->file.mapa.balas[i].existe = false;
        data->file.mapa.balas[i].parou = false;
    }
    for(int i = 0; i < MAXOBJ; i++)
    {
        data->file.mapa.drops[i].ocupado = false;
        data->file.mapa.drops[i].posicao = (Vector3)
        {
            0, 0, 0
        };
    }
    LEVEL0( *&data);
}




