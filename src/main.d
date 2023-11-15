import std.stdio;
import std.string;
import std.conv;
import std.file;
import std.json;
import std.random;

import raylib;

//import maquina;
import util;

class CreatureNeeds
{
    float hunger = 0;
    float thirst = 0;
    float sleep = 0;
    float hygiene = 0;
    float fun = 0;
}

class SpecimeData
{
    string name;
    Model[][] models;
    this(string specimePath)
    {
        JSONValue json = parseJSON(readTxt(specimePath ~ "specime.json"));
        this.name = json["name"].str;
        Model[] tempModels = bulkLoadModel(specimePath ~ "model/", to!int(json["model_count"].integer), json["model_extension"].str);
        writeln(tempModels.length);
        Model[] emptyAnim;
        Model[] tempAnim;
        for(int i = 0; i < tempModels.length; i++)
        {
            tempAnim ~= tempModels[i];
            if(i % to!int(json["anim_length"].integer) == 0)
            {
                this.models ~= tempAnim;
                tempAnim = emptyAnim;
            }
        }
    }
}

struct CreatureData
{
    string name;
    string specime = "human";
    Vector3 position = {0, 0, 0};
    float rotation = 0;
    float speed = 0;
}

class MapData
{
    string name;
    JSONValue json;
    Model[] models;
    BoundingBox[] hitboxes;
    this(string mapPath)
    {
        this.json = parseJSON(readTxt(mapPath ~ "map.json"));
        this.name = this.json["name"].str;
        this.models = bulkLoadModel(mapPath ~ "model/", to!int(this.json["model_count"].integer), this.json["model_extension"].str);
        this.hitboxes = bulkLoadHitbox(mapPath ~ "hitbox/", to!int(this.json["hitbox_count"].integer), this.json["hitbox_extension"].str);
    }
}

alias KeyboardFuncType = void function(PlayerData*);

class PlayerData
{
    CreatureData* creaturePointer;
    KeyboardFuncType keyboard;
    this(CreatureData* creaturePointer, KeyboardFuncType _teclado)
    {
        this.keyboard = _teclado;
        this.creaturePointer = creaturePointer;
    }
}

struct WorldData
{
    SpecimeData[] specimes;
    CreatureData[] creatures;
    MapData[] maps;
    PlayerData player;
}

class SessionData
{
    Random random;
    this(int seed = 7)
    {
        this.random = Random(seed);
    }
}

class RenderData
{
    WorldData* worldPointer;
    SessionData* sessionPointer;
    Camera camera = Camera(Vector3(10, 10, 10), Vector3(0, 0, 0), Vector3(0, 1, 0), 45, 0);
    Font[] fonts;
    Font* defaultFont = null;
    Vector2 screen = Vector2(0, 0);
    RenderTexture renderTexture = RenderTexture(0, Texture(0,0,0,0,0), Texture(0,0,0,0,0));
    string title = "Untitled";
    int framerate = 60;

    this(WorldData* worldPointer, SessionData* sessionPointer)
    {
        this.worldPointer = worldPointer;
        this.sessionPointer = sessionPointer;
    }

    Font loadFont(string fontPath)
    {
        Font tempFont = LoadFontEx(fontPath.toStringz(), 20, null, 0);
        this.fonts ~= tempFont;
        return tempFont;
    }

    void render()
    {
        BeginDrawing();
        ClearBackground(Color(0, 0, 0, 255));
        
        BeginMode3D(this.camera);
        DrawGrid(10, 1.0f);
        
        EndMode3D();
        //DrawText("Congrats! You created your first window!", 190, 200, 20, Color(0,0,0,255));
        EndDrawing();
    }

    void startup(int w, int h, string title, int framerate = 60)
    {
        this.screen = Vector2(w, h);
        this.title = title;
        this.framerate = framerate;
        
        InitWindow(w, h, title.toStringz());
        SetTargetFPS(framerate);
        this.renderTexture = LoadRenderTexture(w, h);
        Font tempFont = this.loadFont("data/font/kremlin.ttf");
        this.defaultFont = &tempFont;
    }
}

void main()
{
    JSONValue config = parseJSON(readTxt("data/config.json"));
    WorldData world = WorldData();
    SessionData session = new SessionData(to!int(config["seed"].integer));
    RenderData render = new RenderData(&world, &session);

    // call this before using raylib
    validateRaylibBinding();

    render.startup(to!int(config["screen"]["x"].integer), to!int(config["screen"]["y"].integer), config["title"].str, to!int(config["framerate"].integer));
    
    //adding specimes and maps
    world.specimes ~= new SpecimeData("data/specime/human/");
    world.maps ~= new MapData("data/map/0/");
    

    SetTargetFPS(to!int(config["framerate"].integer));
    while(!WindowShouldClose())
    {
        render.render();
        //teclado(player);
        //random = Random(counter);
    }
    CloseWindow();
}


