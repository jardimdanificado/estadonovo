void MENU_ESC( Font font, MENU* menu, bool Pressionado, PERSONAGEM *personagem,MAPA *mapa, NPC0 *humano)
{
    if(Pressionado == true)
    {
        menu->esc = true;
        menu->estaAberto = true;
        menu->opcao = 0;
        menu->opcaoMax = 3;
    }
    else
    {
        if ( IsKeyPressed ( KEY_ESCAPE ) )
        {
            menu->esc = false;
            menu->estaAberto = false;
        }
        if ( IsKeyPressed ( KEY_UP ) ||IsKeyPressed ( KEY_W ))
        {
            if(menu->opcao == 0)
            {
                menu->opcao = menu->opcaoMax;
            }
            else if(menu->opcao > 0)
            {
                menu->opcao--;
            }
        }
        if ( IsKeyPressed ( KEY_DOWN ) ||IsKeyPressed ( KEY_S ) )
        {
            if(menu->opcao == menu->opcaoMax)
            {
                menu->opcao = 0;
            }
            else if(menu->opcao < menu->opcaoMax)
            {
                menu->opcao++;
            }
        }
        if ( IsKeyPressed ( KEY_ENTER ) ||IsKeyPressed ( KEY_SPACE )||IsKeyPressed ( KEY_E ) )
        {
            switch(menu->opcao)
            {
                case 0:
                {
                    menu->estaAberto = false;
                    menu->esc = false;
                    menu->sair = false;
                }
                break;
                case 1:
                {
                    SAVE_GAME(*personagem,*mapa,*humano);
                    menu->estaAberto = false;
                }
                break;
                case 2:
                {
                    LOAD_GAME(*&personagem, *&mapa, *&humano);
                    menu->estaAberto = false;
                }
                break;
                case 3:
                {
                    menu->estaAberto = false;
                    menu->sair = true;
                }
                break;
            }
        }
    }
}

void MENU_START(MAPA mapa, Camera *camera, Font font, Vector2 fontPosition, MENU* menu)
{
    camera->position = (Vector3){0,1.5,-2.25};
    menu->opcao = 0;
    menu->opcaoMax = 1;
    while(menu->estaAberto == true)
    {
        RENDER_MENUSTART(mapa, *camera, font, fontPosition, *menu);
        if ( IsKeyPressed ( KEY_DOWN ) ||IsKeyPressed ( KEY_S ))
        {
            if(menu->opcao == 0)
            {
                menu->opcao = menu->opcaoMax;
            }
            else if(menu->opcao > 0)
            {
                menu->opcao--;
            }
        }
        if ( IsKeyPressed ( KEY_UP ) ||IsKeyPressed ( KEY_W ) )
        {
            if(menu->opcao == menu->opcaoMax)
            {
                menu->opcao = 0;
            }
            else if(menu->opcao < menu->opcaoMax)
            {
                menu->opcao++;
            }
        }
        if ( IsKeyPressed ( KEY_ENTER ) ||IsKeyPressed ( KEY_SPACE )||IsKeyPressed ( KEY_E ) )
        {
            switch(menu->opcao)
            {
                case 0:
                {
                    menu->estaAberto = false;
                    menu->sair = false;
                }
                break;
                case 1:
                {
                    menu->estaAberto = false;
                    menu->sair = true;
                }
                break;
            }
        }
    }
    
}
