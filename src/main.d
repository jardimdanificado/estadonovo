import std.stdio;
import std.string;
import std.conv;
import std.file;
import std.json;


import raylib;

import maquina;
import util;

void teclado(Creature* player)
{
    if (IsKeyDown(87))
    {
        player.position.z += 0.1;
    }
    if (IsKeyDown(83))
    {
        player.position.z -= 0.1;
    }
    if (IsKeyDown(65))
    {
        player.position.x -= 0.1;
    }
    if (IsKeyDown(68))
    {
        player.position.x += 0.1;
    }
    if (IsKeyDown(32))
    {
        player.position.y += 0.1;
    }
    if (IsKeyDown(340))
    {
        player.position.y -= 0.1;
    }
}

void main()
{
    FileData data = new FileData();
    RenderData render = new RenderData();
    WorldData world = new WorldData();

    // Caminho para o arquivo JSON
    string jsonFilePath = "src/config.json";

    JSONValue config = parseJSON(readTxt(jsonFilePath));
    
    // call this before using raylib
    validateRaylibBinding();
    InitWindow(
        to!int(config["screen"]["x"].integer), //need to convert from long
        to!int(config["screen"]["y"].integer), //need to convert from long
        config["title"].str.toStringz()
    );
    SetTargetFPS(to!int(config["framerate"].integer));

    data.loadFont("assets/font/kremlin.ttf", 20);
    data.loadModel("assets/models/map/level0/0.glb");
    ModelSlot humanModel = data.loadModel("assets/models/player/walk/",24);
    world.newSpecime("human", &humanModel, CreatureNeeds());
    Creature* player = world.newCreature("joao451","human",Vector3(0,0,0),0);
    render.addText("Estado Novo", Vector2(4,480-20), Color(255,0,0,255), 20, data.fonts[0].file);
    render.addModel(&data.models[0], player.render.position, player.rotation, Vector3(1,1,1), Color(255, 255, 255, 255));
    render.addModel(
        player.render.model, 
        player.render.position, 
        player.render.rotationAngle, 
        player.render.scale, 
        Color(255, 0, 0, 255)
    );
    while (!WindowShouldClose())
    {
        render.render();
        teclado(player);
    }
    CloseWindow();
}


