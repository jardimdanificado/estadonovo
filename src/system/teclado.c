// ⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯⣯
// ⣯⣇⣇⣇⣇⣇⣇⣇⣯⠁⠀⠀⠀⠀⢻⣧⣏⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇
// ⣏⣧⣇⣇⣇⣇⣇⣇⣯⠀⠀⠀⠀⠀⢠⣇⣧⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇⣯
// ⣧⣏⣇⣇⣇⣧⣧⣯⣯⡀⠀⠀⣤⣶⣿⣧⣏⣏⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇
// ⣯⣯⣇⣧⣯⠛⠉⣿⣇⣇⠀⠀⣯⣏⣇⣇⣧⣧⣇⣧⣇⣇⣇⣇⣇⣇⣇⣇⣇⣏
// ⣯⣯⠟⠁⠀⠀⣤⣿⣧⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇⣇
// ⣯⠋⠀⠀⣴⣿⣇⣧⣯⣯⠀⠀⢰⣶⣶⣶⣶⣶⣶⣇⣏⣏⣧⣇⣇⣇⣇⣇⣇⣇
// ⡏⠀⠀⣾⣯⣯⣏⣧⣏⣯⠀⠀⠈⠋⠋⠋⠋⠋⠋⠋⠋⠋⣯⣧⣧⣇⣇⣇⣧⣇
// ⡂⠀⠀⣇⣧⣯⣧⣇⣇⣯⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣄⠀⠀⢫⣧⣏⣇⣇⣧⣇
// ⣧⠀⠀⣿⣇⣯⣏⣯⣇⣇⣧⣏⣏⣇⣧⣧⣏⡏⠙⣧⣏⣦⠀⠀⠻⣧⣇⣇⣏⣇
// ⣏⣄⠀⠈⢿⣧⣇⣇⣇⣇⣧⣏⣏⣏⣏⣯⠋⠀⠀⣼⣧⣯⣷⠀⠀⠙⣯⠏⢻⣏
// ⣯⣏⣦⠀⠀⠈⠛⢿⣇⣧⣇⣧⣇⠟⠋⠀⠀⢀⣾⣇⣧⣇⣯⣿⡀⠀⠀⠀⣠⣿
// ⣇⣇⣇⣏⣶⣤⣀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣾⣯⣯⣯⣧⣧⣧⣇⣏⣦⣮⣮⣮⣮

void TECLADO_MAIN(MENU *menu, Font font, Font fontTitle, Font fontSubTitle, LOGO logo, DATA *data)
{
    if(IsKeyPressed(KEY_ESCAPE))
    {
        MQEXIT = MQMenu("data/menu/esc.menu", false,  * &data, font, fontTitle, fontSubTitle, &logo,  screenH);
    }
    if(IsKeyPressed(KEY_TAB))
    {

    }
    if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)||IsKeyPressed(KEY_A)||IsKeyPressed(KEY_LEFT))
    {
        data->game.boolean.personagem[0].encontrouParedeX = false;
        data->game.boolean.personagem[0].encontrouParedeZ = false;
    }
    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        if(data->game.rotacao.personagem[0] == 0)
            data->game.rotacao.personagem[0] = 360;
        //             data.game.posicao.personagem[0].x -= 0.03f;
        data->game.rotacao.personagem[0] -= 6;
    }
    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        data->game.boolean.personagem[0].encontrouParedeX = false;
        data->game.boolean.personagem[0].encontrouParedeZ = false;
        if(data->game.rotacao.personagem[0] == 360)
            data->game.rotacao.personagem[0] = 0;
        //             data.game.posicao.personagem[0].x += 0.03f;
        data->game.rotacao.personagem[0] += 6;

    }
    /* if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        if(data->game.boolean.personagem[0].mirando == false)
        {
            data->game.boolean.personagem[0].andando = true;
            data->game.boolean.personagem[0].andandoPraTras = true;
        }
    }
    if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
    {
        if(data->game.boolean.personagem[0].encontrouParede == false)
        {
            data->game.posicao.personagem[0] = MQPlayerMove(data->game.posicao.personagem[0], data->game.rotacao.personagem[0], (data->game.velocidade.personagem[0].velocidade) * (-1));
        }
        Vector3 Vec3buff = MQCheckWall(*data,"player-peitoral",360-(data->game.rotacao.personagem[0]));
        if(Vec3buff.x != __INT_MAX__)
        {
            data->game.posicao.personagem[0].x = Vec3buff.x;
        } 
        if(Vec3buff.z != __INT_MAX__)
        {
            data->game.posicao.personagem[0].z = Vec3buff.z;
        }
    } */
    if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        if(data->game.boolean.personagem[0].mirando == false)
        {
            data->game.boolean.personagem[0].andando = true;
        }
    }
    if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
    {
        Vector3 LocalPosi;
/*         if(data->game.boolean.personagem[0].encontrouParedeX == false)
        { */
        LocalPosi = MQPlayerMove(data->game.posicao.personagem[0], data->game.rotacao.personagem[0], data->game.velocidade.personagem[0].velocidade);
/*         } */
        if(data->game.boolean.personagem[0].encontrouParedeX == false)
        {
            data->game.posicao.personagem[0].x = LocalPosi.x;
            Vector3 Vec3buff = MQCheckWall(*data,"player-barriga",data->game.rotacao.personagem[0]);
            if(Vec3buff.x != __INT_MAX__)
            {
                if(data->game.posicao.personagem[0].x+0.5 > Vec3buff.x&&data->game.posicao.personagem[0].x-0.5<Vec3buff.x)
                    data->game.posicao.personagem[0].x = Vec3buff.x;
                data->game.boolean.personagem[0].encontrouParedeX = true;
            } 
        }
        if(data->game.boolean.personagem[0].encontrouParedeZ == false)
        {
            data->game.posicao.personagem[0].z = LocalPosi.z;
            Vector3 Vec3buff = MQCheckWall(*data,"player-barriga",data->game.rotacao.personagem[0]);
            if(Vec3buff.z != __INT_MAX__&&data->game.boolean.personagem[0].encontrouParedeZ == false)
            {
                if(data->game.posicao.personagem[0].z+0.5 > Vec3buff.z&&data->game.posicao.personagem[0].z-0.5<Vec3buff.z)
                    data->game.posicao.personagem[0].z = Vec3buff.z;
                data->game.boolean.personagem[0].encontrouParedeZ = true;
            }
        }
        


        if(MQWALLEXCLUDEINDEX != __INT_MAX__)
        {
            MQWALLEXCLUDE=true;
            Vector3 Vec3buff = MQCheckWall(*data,"player-barriga",data->game.rotacao.personagem[0]);
            if(Vec3buff.x != __INT_MAX__)
            {
                if(data->game.posicao.personagem[0].x+0.5 > Vec3buff.x&&data->game.posicao.personagem[0].x-0.5<Vec3buff.x)
                    data->game.posicao.personagem[0].x = Vec3buff.x;
                data->game.boolean.personagem[0].encontrouParedeX = true;
            } 
            if(Vec3buff.z != __INT_MAX__)
            {
                if(data->game.posicao.personagem[0].z+0.5 > Vec3buff.z&&data->game.posicao.personagem[0].z-0.5<Vec3buff.z)
                    data->game.posicao.personagem[0].z = Vec3buff.z;
                data->game.boolean.personagem[0].encontrouParedeZ = true;
            }
        }
    }
    if(IsKeyDown(KEY_LEFT_SHIFT))
    {
        data->game.velocidade.personagem[0].velocidade = 0.2f;
    }
    if(IsKeyReleased(KEY_LEFT_SHIFT))
    {
        data->game.velocidade.personagem[0].velocidade = 0.1f;
    }
    if(IsKeyReleased(KEY_UP) || IsKeyReleased(KEY_W))
    {
        if(data->game.boolean.personagem[0].andando == true)
            data->game.boolean.personagem[0].andando = false;
    }
    if(IsKeyReleased(KEY_DOWN) || IsKeyReleased(KEY_S))
    {
        data->game.boolean.personagem[0].andando = false;
        data->game.boolean.personagem[0].andandoPraTras = false;
    }
    if(IsKeyPressed(KEY_SPACE))
    {
        if(data->game.boolean.personagem[0].mirando == false)
        {
            data->game.velocidade.personagem[0].velocidadePulo = 0.2;
            data->game.boolean.personagem[0].pulando = true;
            data->session.relogio.personagem[0].pulo = clock();
        }
    }
    if(IsKeyDown(KEY_SPACE))
    {
        if(data->game.boolean.personagem[0].andando == false)
            data->game.posicao.personagem[0].y +=0.2;
    }
    if(IsKeyReleased(KEY_SPACE))
    {
        if(data->game.boolean.personagem[0].mirando == false)
        {
            data->game.boolean.personagem[0].pulando = false;
            data->session.relogio.personagem[0].pulo = clock();
        }
    }
    if(IsKeyPressed(KEY_E))
    {

        data->game.boolean.personagem[0].usando = true;

        data->session.relogio.personagem[0].relogioNovo = 0;
        data->session.relogio.personagem[0].relogioVelho = 0;
        MQPlayerUse( *&data, 0);
        data->game.boolean.personagem[0].usando = false;
    }
    if(IsKeyPressed(KEY_F))
    {
        data->game.boolean.personagem[0].pulando = false;
        if(data->game.ponteiro.personagem[0].item.arma > 0)
        {

            data->game.boolean.personagem[0].mirando = true;
        }
    }
    if(IsKeyReleased(KEY_F))
    {
        if(data->game.ponteiro.personagem[0].item.arma > 0)
        {
            data->game.boolean.personagem[0].mirando = false;
        }
    }
    if(IsKeyPressed(KEY_G))
    {
        if(data->game.ponteiro.personagem[0].item.arma != 0 || data->game.ponteiro.personagem[0].item.calca != 0 || data->game.ponteiro.personagem[0].item.camisa != 0 || data->game.ponteiro.personagem[0].item.chapeu != 0 || data->game.ponteiro.personagem[0].item.oculos != 0 || data->game.ponteiro.personagem[0].item.sapato != 0)
        {

        }
    }
}
