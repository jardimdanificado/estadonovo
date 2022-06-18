void MQRenderLogo(Font fontTitle, Font fontSubTitle, LOGO *logo)
{
    char bufferLocal[255];
    strcpy(bufferLocal, abinCoreReturnData("config.text", "TITLE"));
    DrawTextEx(fontTitle, bufferLocal, (Vector2)
    {
        (screenW / 2) - 157, 8
    }, 48, 0, COR_CINZA);
    DrawTextEx(fontTitle, bufferLocal, (Vector2)
    {
        (screenW / 2) - 157, 46
    }, 48, 0, COR_CINZA);
    DrawTextEx(fontTitle, bufferLocal, (Vector2)
    {
        (screenW / 2) - 157, 84
    }, 48, 0, COR_CINZA);
    DrawTextEx(fontTitle, bufferLocal, (Vector2)
    {
        (screenW / 2) - 157, 122
    }, 48, 0, COR_CINZA);
    DrawTextEx(fontTitle, bufferLocal, (Vector2)
    {
        (screenW / 2) - 157, 160
    }, 48, 0, COR_CINZA);
    switch(logo->ponteiro)
    {
        case 0:
        {
            DrawTextEx(fontTitle, bufferLocal, (Vector2)
            {
                (screenW / 2) - 157, 8
            }, 48, 0, COR_LARANJA);
        }
        break;
        case 1:
        {
            DrawTextEx(fontTitle, bufferLocal, (Vector2)
            {
                (screenW / 2) - 157, 46
            }, 48, 0, COR_LARANJA);
        }
        break;
        case 2:
        {
            DrawTextEx(fontTitle, bufferLocal, (Vector2)
            {
                (screenW / 2) - 157, 84
            }, 48, 0, COR_LARANJA);
        }
        break;
        case 3:
        {
            DrawTextEx(fontTitle, bufferLocal, (Vector2)
            {
                (screenW / 2) - 157, 122
            }, 48, 0, COR_LARANJA);
        }
        break;
        case 4:
        {
            DrawTextEx(fontTitle, bufferLocal, (Vector2)
            {
                (screenW / 2) - 157, 160
            }, 48, 0, COR_LARANJA);
        }
        break;
    }

    if(clock() > logo->relogio + CLOCKS_PER_SEC * 1.5)
    {
        logo->relogio = clock();
        if(logo->ponteiro < 4)
            logo->ponteiro++;
        else if(logo->ponteiro == 4)
            logo->ponteiro = 0;
    }

    logo->relogiosub = clock();
    strcpy(bufferLocal, abinCoreReturnData("config.text", "SUBTITLE"));
    DrawTextEx(fontSubTitle, bufferLocal, (Vector2)
    {
        (screenW / 2) - 150, 202
    }, 24, 0, COR_CINZA);
    if(logo->relogiosub % 19 == 0 && logo->pisca == false)
    {
        logo->pisca = true;
        logo->relogiosubDef = clock();
    }
    else if(logo->pisca == true && logo->piscaPonteiro == 0 && clock() > logo->relogiosubDef + (CLOCKS_PER_SEC / 50))
    {
        logo->piscaPonteiro++;
        strcpy(bufferLocal, abinCoreReturnData("config.text", "SUBTITLE"));
        DrawTextEx(fontSubTitle, bufferLocal, (Vector2)
        {
            (screenW / 2) - 150, 202
        }, 24, 0, COR_LARANJA);
        logo->relogiosubDef = clock();
    }
    else if(logo->pisca == true && logo->piscaPonteiro == 1 && clock() > logo->relogiosubDef + (CLOCKS_PER_SEC / 30))
    {
        logo->piscaPonteiro = 0;
        strcpy(bufferLocal, abinCoreReturnData("config.text", "SUBTITLE"));
        DrawTextEx(fontSubTitle, bufferLocal, (Vector2)
        {
            (screenW / 2) - 150, 202
        }, 24, 0, COR_LARANJA);
        logo->pisca = false;
    }
}

void MQRenderPlayerItem(DATA *data, int quem, int qualAnim)
{
    int modelIndex;
    MQPlayerUpdateBodyBox( *&data, quem, qualAnim);
    snprintf(ABINCACHE16, 16, "calca%d", data->game.ponteiro.personagem[quem].item.calca);
    if(data->game.ponteiro.personagem[quem].item.calca != 0 && data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE16))].meshCount != 0)
    {
        modelIndex = atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE16));
        snprintf(ABINCACHE32, 32, "anim%d", data->game.ponteiro.personagem[quem].item.calca);
        UpdateModelAnimation(data->file.model[modelIndex], data->file.anim[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE32))][qualAnim], data->game.contador.frames.personagem[quem]);
        DrawModelEx(data->file.model[modelIndex], data->game.posicao.personagem[quem], (Vector3)
        {
            0.0f, 1.0f, 0.0f
        }, data->game.rotacao.personagem[quem], (Vector3)
        {
            1.0f, 1.0f, 1.0f
        }, COR_ROUPA0);
    }
    snprintf(ABINCACHE16, 16, "camisa%d", data->game.ponteiro.personagem[quem].item.camisa);
    if(data->game.ponteiro.personagem[quem].item.camisa != 0 && data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE16))].meshCount != 0)
    {
        snprintf(ABINCACHE32, 32, "anim%d", data->game.ponteiro.personagem[quem].item.camisa);
        UpdateModelAnimation(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE16))], data->file.anim[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE32))][qualAnim], data->game.contador.frames.personagem[quem]);
        DrawModelEx(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE16))], data->game.posicao.personagem[quem], (Vector3)
        {
            0.0f, 1.0f, 0.0f
        }, data->game.rotacao.personagem[quem], (Vector3)
        {
            1.0f, 1.0f, 1.0f
        }, COR_ROUPA0);
    }
    snprintf(ABINCACHE16, 16, "chapeu%d", data->game.ponteiro.personagem[quem].item.chapeu);
    if(data->game.ponteiro.personagem[quem].item.chapeu != 0 && data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE16))].meshCount != 0)
    {
        snprintf(ABINCACHE32, 32, "anim%d", data->game.ponteiro.personagem[quem].item.chapeu);
        UpdateModelAnimation(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE16))], data->file.anim[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE32))][qualAnim], data->game.contador.frames.personagem[quem]);
        DrawModelEx(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE16))], data->game.posicao.personagem[quem], (Vector3)
        {
            0.0f, 1.0f, 0.0f
        }, data->game.rotacao.personagem[quem], (Vector3)
        {
            1.0f, 1.0f, 1.0f
        }, COR_ROUPA0);
    }
    snprintf(ABINCACHE16, 16, "oculos%d", data->game.ponteiro.personagem[quem].item.oculos);
    if(data->game.ponteiro.personagem[quem].item.oculos != 0 && data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE16))].meshCount != 0)
    {
        snprintf(ABINCACHE32, 32, "anim%d", data->game.ponteiro.personagem[quem].item.oculos);
        UpdateModelAnimation(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE16))], data->file.anim[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE32))][qualAnim], data->game.contador.frames.personagem[quem]);
        DrawModelEx(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE16))], data->game.posicao.personagem[quem], (Vector3)
        {
            0.0f, 1.0f, 0.0f
        }, data->game.rotacao.personagem[quem], (Vector3)
        {
            1.0f, 1.0f, 1.0f
        }, COR_ROUPA0);
    }
    snprintf(ABINCACHE16, 16, "sapato%d", data->game.ponteiro.personagem[quem].item.sapato);
    if(data->game.ponteiro.personagem[quem].item.sapato != 0 && data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE16))].meshCount != 0)
    {
        snprintf(ABINCACHE32, 32, "anim%d", data->game.ponteiro.personagem[quem].item.sapato);
        UpdateModelAnimation(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE16))], data->file.anim[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE32))][qualAnim], data->game.contador.frames.personagem[quem]);
        DrawModelEx(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE16))], data->game.posicao.personagem[quem], (Vector3)
        {
            0.0f, 1.0f, 0.0f
        }, data->game.rotacao.personagem[quem], (Vector3)
        {
            1.0f, 1.0f, 1.0f
        }, COR_ROUPA0);
    }
}
void MQRenderPlayer(DATA *data, int quem)
{
    if(data->game.boolean.personagem[0].andando == true)
    {
        if(data->game.boolean.personagem[0].andandoPraTras == true)
        {
            data->game.contador.frames.personagem[quem]--;
            if(data->game.contador.frames.personagem[quem] < 0)
            {
                snprintf(ABINCACHE64, 64, "player");
                data->game.contador.frames.personagem[quem] = data->file.anim[atoi(abinCoreReturnData("./data/temp/model.temp", "player"))][1].frameCount - 1;
            }
            MQRenderPlayerItem( *&data, quem, 1);
        }
        else
        {
            data->game.contador.frames.personagem[quem]++;
            if(data->game.contador.frames.personagem[quem] >= data->file.anim[atoi(abinCoreReturnData("./data/temp/model.temp", "player"))][1].frameCount)
                data->game.contador.frames.personagem[quem] = 0;
            MQRenderPlayerItem( *&data, quem, 1);
        }

        UpdateModelAnimation(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "player"))], data->file.anim[atoi(abinCoreReturnData("./data/temp/model.temp", "player"))][1], data->game.contador.frames.personagem[quem]);

        DrawModelEx(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "player"))], data->game.posicao.personagem[quem], (Vector3)
        {
            0.0f, 1.0f, 0.0f
        }, data->game.rotacao.personagem[quem], (Vector3)
        {
            1.0f, 1.0f, 1.0f
        }, COR_PELE0);
    }
    else
    {
        snprintf(ABINCACHE8, 8, "anim%s", abinCoreReturnData("./data/temp/model.temp", "player"));
        if(data->game.contador.frames.personagem[quem] >= data->file.anim[atoi(abinCoreReturnData("./data/temp/model.temp", ABINCACHE8))][0].frameCount)
            data->game.contador.frames.personagem[quem] = 0;
        data->game.contador.frames.personagem[quem]++;
        MQRenderPlayerItem( *&data, quem, 0);

        UpdateModelAnimation(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "player"))], data->file.anim[atoi(abinCoreReturnData("./data/temp/model.temp", abinCoreReturnData("./data/temp/model.temp", ABINCACHE8)))][0], data->game.contador.frames.personagem[quem]);
        DrawModelEx(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "player"))], data->game.posicao.personagem[quem], (Vector3)
        {
            0.0f, 1.0f, 0.0f
        }, data->game.rotacao.personagem[quem], (Vector3)
        {
            1.0f, 1.0f, 1.0f
        }, (Color)
        {
            240, 199, 156, 255
        });
    }
}

void RENDER_LVL0(DATA *data, Camera camera, Font font, MENU menu)
{
    BeginDrawing();

    ClearBackground((Color)
    {
        115, 105, 97, 255
    });

    //DrawTextEx ( font, msg, fontPosition, 16, 0, COR_CINZA );

    BeginMode3D(camera);
    DrawModel(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "map0"))], (Vector3)
    {
        0.0f, 0.0f, 0.0f
    }, 1.0f, WHITE);
    DrawModel(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "props0"))], (Vector3)
    {
        0.0f, 0.0f, 0.0f
    }, 1.0f, WHITE);

    for(int i = 0; i < MAXOBJ; i++)
    {
        if(data->file.mapa.porta.slots[i].existe)
        {
            for(int i = 0; i < MAXOBJ; i++)
            {
                if(data->file.mapa.porta.slots[i].existe)
                {
                    if(data->file.mapa.porta.slots[i].invertido == false)
                    {
                        switch(data->file.mapa.porta.slots[i].frame)
                        {
                            case 0:
                            {
                                DrawModel(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta0"))], data->file.mapa.porta.slots[i].posicao, 1.0f, WHITE);
                            }
                            break;
                            case 1:
                            {
                                DrawModel(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta1"))], data->file.mapa.porta.slots[i].posicao, 1.0f, WHITE);
                            }
                            break;
                            case 2:
                            {
                                DrawModel(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta2"))], data->file.mapa.porta.slots[i].posicao, 1.0f, WHITE);
                            }
                            break;
                            case 3:
                            {
                                DrawModel(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta3"))], data->file.mapa.porta.slots[i].posicao, 1.0f, WHITE);
                            }
                            break;
                        }
                    }
                    else if(data->file.mapa.porta.slots[i].invertido == true)
                    {
                        switch(data->file.mapa.porta.slots[i].frame)
                        {
                            case 0:
                            {
                                DrawModel(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta0"))], data->file.mapa.porta.slots[i].posicao, 1.0f, WHITE);

                            }
                            break;
                            case 1:
                            {
                                DrawModel(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta-1"))], data->file.mapa.porta.slots[i].posicao, 1.0f, WHITE);

                            }
                            break;
                            case 2:
                            {
                                DrawModel(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta-2"))], data->file.mapa.porta.slots[i].posicao, 1.0f, WHITE);
                            }
                            break;
                            case 3:
                            {
                                DrawModel(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "porta-3"))], data->file.mapa.porta.slots[i].posicao, 1.0f, WHITE);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    for(int i = atoi(abinCoreReturnData("./data/temp/hitbox.temp", "SIZE")); i > 0; i--)
    {
        DrawBoundingBox(data->file.hitbox[i], BLACK);
    }
    MQRenderPlayer( *&data, 0);
    if(data->file.mapa.item[0].pegou == false)
    {
        DrawModel(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "item0"))], (Vector3)
        {
            0, 0, 0
        }, 1.0f, WHITE);
    }
    if(data->file.mapa.item[1].pegou == false)
    {
        DrawModel(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "item1"))], (Vector3)
        {
            0, 0, 0
        }, 1.0f, WHITE);
    }
    if(data->file.mapa.item[2].pegou == false)
    {
        DrawModel(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "item2"))], (Vector3)
        {
            0, 0, 0
        }, 1.0f, WHITE);
    }
    if(data->file.mapa.item[3].pegou == false)
    {
        DrawModel(data->file.model[atoi(abinCoreReturnData("./data/temp/model.temp", "item3"))], (Vector3)
        {
            0, 0, 0
        }, 1.0f, WHITE);
    }

    for(int i = 0; i < MAXOBJ; i++)
    {
        if(data->file.mapa.drops[i].ocupado == true)
        {
            DrawModel(data->file.mapa.drops[i].modelo, data->file.mapa.drops[i].posicao, 1.0f, WHITE);
        }
    }
    EndMode3D();
    DrawTextEx(font, msg, (Vector2)
    {
        0, MAXHEI - 16
    }, 16, 0, COR_PRETO);
    EndDrawing();
}

void MQCameraUpdate(DATA data, Camera *camera)
{
    if(CheckCollisionBoxes(data.game.hitbox.personagem[0].frenteAtual, data.file.mapa.area[0]))
    {
        camera->position = (Vector3)
        {
            0.4375, 3.5, 11.0625
        };
    }
    else if(CheckCollisionBoxes(data.game.hitbox.personagem[0].frenteAtual, data.file.mapa.area[1]))
    {
        camera->position = (Vector3)
        {
            4.473, 3.5, 0.562
        };
    }
    else if(CheckCollisionBoxes(data.game.hitbox.personagem[0].frenteAtual, data.file.mapa.area[2]))
    {
        camera->position = (Vector3)
        {
            7.5, 2.5, -4
        };
    }
    else if(CheckCollisionBoxes(data.game.hitbox.personagem[0].frenteAtual, data.file.mapa.area[3]))
    {
        camera->position = (Vector3)
        {
            -3.56, 2.5, -4.8375
            };
    }
    else if(CheckCollisionBoxes(data.game.hitbox.personagem[0].frenteAtual, data.file.mapa.area[4]))
    {
        camera->position = (Vector3)
        {
            -19, 6, -16.5
            };
    }
    else if(CheckCollisionBoxes(data.game.hitbox.personagem[0].frenteAtual, data.file.mapa.area[5]))
    {
        camera->position = (Vector3)
        {
            -6.5, 8.5, -29
            };
    }

    if(CheckCollisionBoxes(data.game.hitbox.personagem[0].frenteAtual, data.file.mapa.area[4]) == false)
        camera->target = (Vector3)
    {
        data.game.posicao.personagem[0].x, data.game.posicao.personagem[0].y + 2, data.game.posicao.personagem[0].z
    };
    else
        camera->target = (Vector3)
    {
        0, 4, -16.5
    };
}

void MQRender(DATA *data, Camera camera, Font font,  MENU menu)
{
    RENDER_LVL0( *&data, camera, font, menu);
}
