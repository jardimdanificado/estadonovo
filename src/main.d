import std.stdio;
import std.string;
import std.conv;
import std.file;
import std.json;

import raylib;

import maquina;
import util;

void main()
{
    FileData data = new FileData();
    RenderData render = new RenderData();

    // Caminho para o arquivo JSON
    string jsonFilePath = "src/config.json";

    JSONValue config = parseJSON(readTxt(jsonFilePath));
    
    // call this before using raylib
    validateRaylibBinding();
    InitWindow(
        to!int(config["screen"]["x"].integer), //need to convert from long
        to!int(config["screen"]["y"].integer), //need to convert from long
        config["title"].str.ptr
    );
    SetTargetFPS(to!int(config["framerate"].integer));

    data.loadFont("assets/font/kremlin.ttf", 20);
    data.loadModel("assets/models/map/level0/0.glb");
    data.loadModel("assets/models/player/walk/",24);

    render.addText("Estado Novo", Vector2(100,100), Color(255,0,0,255), 20, data.fonts[0].file);
    render.addModel(data.models[0], Vector3Zero(), Vector3Zero(), 0, Vector3(1,1,1), Color(255, 255, 255, 255));
    render.addModel(data.models[1], Vector3(1,3,1), Vector3Zero(), 0, Vector3(1,1,1), Color(255, 0, 0, 255));
    //config = null;
    while (!WindowShouldClose())
    {
        render.render();
    }
    CloseWindow();
}


