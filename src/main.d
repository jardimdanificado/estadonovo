import std.stdio;
import std.string;
import std.conv;
import std.file;
import std.json;
import std.random;
import std.math;

import raylib;

//import maquina;
import util;

T[][] splitList(T)(T[] lista, size_t tamanho)
{
    T[][] listasMenores;

    size_t inicio = 0;
    size_t fim = tamanho;

    while (inicio < lista.length)
    {
        if (fim > lista.length)
        {
            fim = lista.length;
        }

        T[] sublista = lista[inicio..fim];
        listasMenores ~= sublista;

        inicio = fim;
        fim += tamanho;
    }

    return listasMenores;
}

struct HitboxSlot
{
    BoundingBox hitbox;
    bool active = true;
}

private struct GenericObjectRayData
{
    Ray gravity = Ray(Vector3(0,0,0), Vector3(0,0,0));
    Ray horizontal = Ray(Vector3(0,0,0), Vector3(0,0,0));
}

struct GenericData
{
    Vector3 position = {0, 0, 0};
    float rotation = 0;
    float speed = 0.25;
    float fallTime = 0;
    GenericObjectRayData ray =  GenericObjectRayData(Ray(Vector3(0,0,0), Vector3(0,1,0)), Ray(Vector3(0,0,0), Vector3(0,0,0)));
}

struct CreatureRenderData
{
    int anim = 0;
    int frame = 0;
    int lastcheck = 0;
    bool reverse = false;
}

struct CreatureNeeds
{
    float hunger = 100;
    float thirst = 100;
    float sleep = 100;
    float hygiene = 100;
    float fun = 100;
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
        this.models = splitList(tempModels, to!int(json["anim_length"].integer));
    }
}

struct CreatureData
{
    string name;
    string specime = "human";
    int map = 0;
    CreatureNeeds needs = CreatureNeeds();
    Color color = Color(155, 132, 15, 255);
    CreatureRenderData renderData = CreatureRenderData();
    GenericData generic = GenericData();
}

class MapData
{
    string name;
    JSONValue json;
    Model[] models;
    HitboxSlot[] hitboxes;
    this(string mapPath)
    {
        this.json = parseJSON(readTxt(mapPath ~ "map.json"));
        this.name = this.json["name"].str;
        this.models = bulkLoadModel(mapPath ~ "model/", to!int(this.json["model_count"].integer), this.json["model_extension"].str);
        BoundingBox[] _hitboxes = bulkLoadHitbox(mapPath ~ "hitbox/", to!int(this.json["hitbox_count"].integer), this.json["hitbox_extension"].str);
        foreach (key; _hitboxes)
        {
            this.hitboxes ~= HitboxSlot(key, true);
        }
    }
}

alias KeyboardFuncType = void delegate(PlayerData*);

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
    int time = 0;

    void startup(CreatureData* playerCreature = &this.creatures[0])
    {
        player = new PlayerData(playerCreature, (PlayerData*){});
    }

    CreatureData* newCreature(string name, string specime = "human")
    {
        this.creatures ~= CreatureData(name, specime);
        return &this.creatures[this.creatures.length - 1];
    }
}

class SessionData
{
    int tick = 0;
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
    Font defaultFont;
    Vector2 screen = Vector2(0, 0);
    RenderTexture renderTexture = RenderTexture(0, Texture(0,0,0,0,0), Texture(0,0,0,0,0));
    string title = "Untitled";
    int framerate = 60;
    int pixelSize = 2;

    this(WorldData* worldPointer, SessionData* sessionPointer)
    {
        this.worldPointer = worldPointer;
        this.sessionPointer = sessionPointer;
    }

    Font loadFont(string fontPath)
    {
        Font tempFont = LoadFont(fontPath.toStringz());
        this.fonts ~= tempFont;
        return tempFont;
    }

    void startup(int w, int h, string title, int framerate = 60, int pixelSize = 2, string defaultFont = "data/font/Papirology.ttf")
    {
        this.screen = Vector2(w, h);
        this.title = title;
        this.framerate = framerate;
        this.pixelSize = pixelSize;
        InitWindow(w, h, title.toStringz());
        SetTargetFPS(framerate);
        this.renderTexture = LoadRenderTexture(w/this.pixelSize, h/this.pixelSize);
        Font tempFont = this.loadFont(defaultFont);
        this.defaultFont = tempFont;
    }

    private void bakeRenderTexture()
    {
        BeginTextureMode(this.renderTexture);
        ClearBackground(Color(0, 0, 0, 255));
        BeginMode3D(this.camera);
        
        foreach (key; this.worldPointer.maps[this.worldPointer.player.creaturePointer.map].models)
        {
            DrawModel(key, Vector3(0, 0, 0), 1.0f, Color(255, 255, 255, 255));
        }

        for (int i = 0; i < this.worldPointer.creatures.length; i++)
        {
            CreatureData* key = &this.worldPointer.creatures[i];
            if(key.map == this.worldPointer.player.creaturePointer.map)
            {

                DrawModelEx(this.worldPointer.specimes[0].models[key.renderData.anim][key.renderData.frame], key.generic.position, Vector3(0, 1, 0), (key.generic.rotation), Vector3(1, 1, 1), key.color);
                
                bool tempCondition = false;
                int tempFrame = 0;
                if(key.renderData.reverse)
                {
                    tempCondition = key.renderData.frame >= 0;
                    tempFrame = to!int(this.worldPointer.specimes[0].models[0].length - 1);
                }
                else
                {
                    tempCondition = key.renderData.frame <= this.worldPointer.specimes[0].models[0].length - 1;
                }

                if(key.renderData.lastcheck + (this.framerate/this.worldPointer.specimes[0].models[0].length) <= this.sessionPointer.tick)
                {
                    if (key.renderData.frame + (key.renderData.reverse ? -1 : 1) < this.worldPointer.specimes[0].models[0].length)
                    {
                        key.renderData.frame += key.renderData.reverse ? -1 : 1;
                    }
                    else
                    {
                        key.renderData.frame = key.renderData.reverse ? to!int(this.worldPointer.specimes[0].models[0].length) -1 : 0;
                    }
                    key.renderData.lastcheck = this.sessionPointer.tick;
                }
            }
        }
        foreach (key; this.worldPointer.maps[this.worldPointer.player.creaturePointer.map].hitboxes)
        {
            DrawBoundingBox(key.hitbox, Color(255, 0, 0, 255));
        }

        foreach (key; this.worldPointer.creatures)
        {
            DrawRay(key.generic.ray.gravity, Color(0, 255, 0, 255));
            DrawRay(key.generic.ray.horizontal, Color(0, 0, 255, 255));
        }
        //DrawGrid(10, 1.0f);
        
        EndMode3D();
        EndTextureMode();
    }

    void render()
    {
        camera.target = this.worldPointer.player.creaturePointer.generic.position;
        BeginDrawing();
        bakeRenderTexture();
        
        DrawTextureEx(this.renderTexture.texture, Vector2(this.screen.x, this.screen.y), 180, this.pixelSize, Color(255, 255, 255, 255));
        DrawTextEx(this.defaultFont, "Estado Novo", Vector2(0, this.screen.y-17), 20, 0, Color(255, 255, 244, 255));
        
        EndDrawing();
        this.sessionPointer.tick++;
    }
}


Vector3 move3d(Vector3 position, float rotation, float speed)
{
    //z+ frente
    //x+ esquerda
    float  valorZ, valorX;
    int giro = to!int(floor(rotation / 90.0));
    float resto = rotation - (90.0 * giro);
    float restodoresto = 90.0 - resto;
    valorZ = speed - (resto * (speed / 90.0));
    valorX = (speed - (restodoresto * (speed / 90)));
	switch(giro)
    {
        case 0:
        {
            position.z += valorZ;
            position.x += valorX;
        }
        break;
        case 1:
        {
            position.z -= valorX;
            position.x += valorZ;
        }
        break;
        case 2:
        {
            position.z -= valorZ;
            position.x -= valorX;
        }
        break;
        case 3:
        {
            position.z += valorX;
            position.x -= valorZ;
        }
        break;
        default:break;
    }
    return position;
}

void UpdateHorizontalRay(GenericData* targetobj, bool backwards)
{
    //z+ frente
    //x+ esquerda
    float valorZ;
    float valorX;
    if(targetobj.rotation<=90.0)
    {
        if(backwards)
        {
            valorZ = -1.0+((1.0/90.0)*targetobj.rotation);
            valorX = 0.0-(1.0/90.0)*targetobj.rotation;
        }
        else
        {
            valorZ = 1.0-((1.0/90.0)*targetobj.rotation);
            valorX = 0.0+(1.0/90.0)*targetobj.rotation;
        }
    }
    else if(targetobj.rotation<=180)
    {
        if(backwards)
        {
            valorZ = 0.0+((1.0/90.0)*(targetobj.rotation-90.0));
            valorX = -1.0+((1.0/90.0)*(targetobj.rotation-90.0));
        }
        else
        {
            valorZ = 0.0-((1.0/90.0)*(targetobj.rotation-90.0));
            valorX = 1.0-((1.0/90.0)*(targetobj.rotation-90.0));
        }
    }
    else if(targetobj.rotation<=270)
    {
        if(backwards)
        {
            valorZ = 1.0-((1.0/90.0)*(targetobj.rotation-180.0));
            valorX = 0.0+((1.0/90.0)*(targetobj.rotation-180.0));
        }
        else
        {
            valorZ = -1.0+((1.0/90.0)*(targetobj.rotation-180.0));
            valorX = 0.0-((1.0/90.0)*(targetobj.rotation-180.0));
        }
    }
    else 
    {
        if(backwards)
        {
            valorZ = 0.0-((1.0/90.0)*(targetobj.rotation-270.0));
            valorX = 1.0-((1.0/90.0)*(targetobj.rotation-270.0));
        }
        else
        {
            valorZ = 0.0+((1.0/90.0)*(targetobj.rotation-270.0));
            valorX = -1.0+((1.0/90.0)*(targetobj.rotation-270.0));
        }
    }
    Vector3 newPosition = Vector3(targetobj.position.x,targetobj.position.y+0.7,targetobj.position.z);
    //newPosition = move3d(newPosition,targetobj.rotation,0.1);
    targetobj.ray.horizontal.position.x = newPosition.x;
    targetobj.ray.horizontal.position.y = newPosition.y;
    targetobj.ray.horizontal.position.z = newPosition.z;
    Vector3 newDirection = Vector3(valorX,0,valorZ);
   	targetobj.ray.horizontal.direction.x = newDirection.x;
    targetobj.ray.horizontal.direction.y = newDirection.y;
    targetobj.ray.horizontal.direction.z = newDirection.z;
}

float Gravity(GenericData targetobj, float gravidade)
{
    return((targetobj.position.y) - gravidade*((targetobj.fallTime*(targetobj.fallTime/10.0)))/30.0);
}

void Gravit(WorldData* world, GenericData* targetobj)
{
    //writeln(world.player.creaturePointer.generic is *targetobj);
	targetobj.ray.gravity.position.x = targetobj.position.x;
    targetobj.ray.gravity.position.y = (targetobj.position.y+0.00001)-(0.005*(targetobj.fallTime));
    targetobj.ray.gravity.position.z = targetobj.position.z;

	RayCollision gravityraiocolisao = RayCollision(false,0,Vector3(0,0,0),Vector3(0,0,0));
    HitboxSlot[] hitboxes = world.maps[world.player.creaturePointer.map].hitboxes;

    foreach(key;hitboxes)
    {
		if(key.active == true)
		{
			gravityraiocolisao = GetRayCollisionBox(targetobj.ray.gravity, key.hitbox);
			if(gravityraiocolisao.hit == true)
				break;
			gravityraiocolisao.hit = false;
		}
    }
	
    if(gravityraiocolisao.hit == false)
    {
        //writeln(targetobj.position.y);
        targetobj.position.y = Gravity(*targetobj, 1);
        targetobj.fallTime++;
        //writeln(targetobj.position.y);
    }
    else
    {
        if(gravityraiocolisao.distance<0.1)
        {
            targetobj.position.y = gravityraiocolisao.point.y;
            targetobj.fallTime = 0;
        }
    }
}

bool PlayerCollider(WorldData* world,GenericData* targetobj, bool backwards)
{
    RayCollision directionraiocolisao = RayCollision(false,0,Vector3(0,0,0),Vector3(0,0,0));
    UpdateHorizontalRay(targetobj,backwards);
    HitboxSlot[] hitboxes = world.maps[world.player.creaturePointer.map].hitboxes;
    foreach(key;hitboxes)
		if(key.active == true)
		{
			directionraiocolisao = GetRayCollisionBox(targetobj.ray.horizontal,key.hitbox);
			if(directionraiocolisao.hit == true)
			{
				break;
			}
			directionraiocolisao.hit = false;
		}
    
    if(directionraiocolisao.hit == true)
    {
        if(directionraiocolisao.distance<0.7)
        {
            return true;
        }
        else
        {
            BoundingBox caixa = BoundingBox(targetobj.position,targetobj.position);
            caixa.max.x += 0.2;
            caixa.max.y += 1.2;
            caixa.max.z += 0.2;
            caixa.min.x += -0.2;
            caixa.min.y += 0.7;
            caixa.min.z += -0.2;
            if(backwards)
            {
                caixa.max = move3d(caixa.max,targetobj.rotation,-targetobj.speed);
                caixa.min = move3d(caixa.min,targetobj.rotation,-targetobj.speed);
            }
            else
            {
                caixa.max = move3d(caixa.max,targetobj.rotation,targetobj.speed);
                caixa.min = move3d(caixa.min,targetobj.rotation,targetobj.speed);
            }
            foreach(key;hitboxes)
				if(key.active == true)
					if(CheckCollisionBoxes(caixa,key.hitbox)==true)
					{
						return true;
					}
        }
    }
    return false;
}

void main()
{
    JSONValue config = parseJSON(readTxt("data/config.json"));
    WorldData world = WorldData();
    SessionData session = new SessionData(to!int(config["seed"].integer));
    RenderData render = new RenderData(&world, &session);

    // call this before using raylib
    validateRaylibBinding();

    render.startup(to!int(config["screen"]["x"].integer), to!int(config["screen"]["y"].integer), config["title"].str, to!int(config["framerate"].integer), to!int(config["pixel_size"].integer));
    
    //adding specimes and maps
    world.specimes ~= new SpecimeData("data/specime/human/");
    world.maps ~= new MapData("data/map/0/");
    CreatureData* player = world.newCreature("player", "human");
    player.generic.position.y = 5;
    world.startup(player);
    world.player.keyboard = (PlayerData* player) 
    {
        if (IsKeyPressed(87))
        {
            player.creaturePointer.renderData.anim = 1;
        }
        else if(IsKeyReleased(87))
        {
            player.creaturePointer.renderData.anim = 0;
        }
        
        if (IsKeyPressed(83))
        {
            player.creaturePointer.renderData.anim = 1;
            player.creaturePointer.renderData.reverse = true;
        }
        else if(IsKeyReleased(83))
        {
            player.creaturePointer.renderData.anim = 0;
            player.creaturePointer.renderData.reverse = false;
        }

        if(IsKeyDown(68))
        {
            player.creaturePointer.generic.rotation += 3;
            if(player.creaturePointer.generic.rotation > 360)
            {
                player.creaturePointer.generic.rotation -= 360;
            }
        }
        if(IsKeyDown(65))
        {
            player.creaturePointer.generic.rotation -= 3;
            if(player.creaturePointer.generic.rotation < 0)
            {
                player.creaturePointer.generic.rotation += 360;
            }
        }
        if (IsKeyDown(87) && !PlayerCollider(&world, &player.creaturePointer.generic, false))
        {
            Vector3 temp = move3d(player.creaturePointer.generic.position, player.creaturePointer.generic.rotation, player.creaturePointer.generic.speed);
            player.creaturePointer.generic.position.x = temp.x;
            player.creaturePointer.generic.position.z = temp.z;
        }
        if (IsKeyDown(83) && !PlayerCollider(&world, &player.creaturePointer.generic, true))
        {
            Vector3 temp = move3d(player.creaturePointer.generic.position, player.creaturePointer.generic.rotation, -player.creaturePointer.generic.speed);
            player.creaturePointer.generic.position.x = temp.x;
            player.creaturePointer.generic.position.z = temp.z;
        }
        if (IsKeyDown(32))
        {
            player.creaturePointer.generic.position.y += 0.3;
        }
    };
    SetTargetFPS(to!int(config["framerate"].integer));

    while(!WindowShouldClose())
    {
        render.render();
        world.player.keyboard(&world.player);
        for(short i = 0; i < world.creatures.length; i++)
        {
            Gravit(&world, &world.creatures[i].generic);
        }
        //teclado(player);
        //random = Random(counter);
    }
    CloseWindow();
}


