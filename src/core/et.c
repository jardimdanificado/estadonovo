
void START_WINDOW(const int screenW,const int screenH)
{

	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	time_t *seconds = MemAlloc ( sizeof ( time_t ) );
	char *textotitulo = MemAlloc ( sizeof ( char ) *40 );
	*seconds = time ( NULL );
	sprintf ( textotitulo,"19.64-%ld",*seconds );
	InitWindow ( screenW, screenH, textotitulo );
	MemFree ( seconds );
	MemFree ( textotitulo );
}

float diferencaF(float a, float b)
{
	bool negativo = false;
	float resultado;
	if(a < 0)
	{
		a = a*(-1);
		negativo = true;
	}
	else if(b < 0)
	{
		b = b*(-1);
		negativo = true;
	}

	if(negativo == true)
	{
		resultado = a + b;
	}
	else if(a == b)
	{
		return 0;
	}
	else if(a > b)
	{
		resultado = a - b;
	}
	else if(a < b)
	{
		resultado = b - a;
	}
}
