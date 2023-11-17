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
import engine;

//main
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
            player.creaturePointer.generic.rotation += 6;
            if(player.creaturePointer.generic.rotation > 360)
            {
                player.creaturePointer.generic.rotation -= 360;
            }
        }
        if(IsKeyDown(65))
        {
            player.creaturePointer.generic.rotation -= 6;
            if(player.creaturePointer.generic.rotation < 0)
            {
                player.creaturePointer.generic.rotation += 360;
            }
        }
        if (IsKeyDown(87) && !playerCollider(&world, &player.creaturePointer.generic, false))
        {
            Vector3 temp = move3d(player.creaturePointer.generic.position, player.creaturePointer.generic.rotation, player.creaturePointer.generic.speed);
            player.creaturePointer.generic.position.x = temp.x;
            player.creaturePointer.generic.position.z = temp.z;
        }
        if (IsKeyDown(83) && !playerCollider(&world, &player.creaturePointer.generic, true))
        {
            Vector3 temp = move3d(player.creaturePointer.generic.position, player.creaturePointer.generic.rotation, -player.creaturePointer.generic.speed);
            player.creaturePointer.generic.position.x = temp.x;
            player.creaturePointer.generic.position.z = temp.z;
        }
        if (IsKeyDown(32) && player.creaturePointer.generic.fallTime < 32)
        {
            player.creaturePointer.generic.position.y += 0.3;
            //writeln(player.creaturePointer.generic.fallTime);
        }
    };
    SetTargetFPS(to!int(config["framerate"].integer));

    while(!WindowShouldClose())
    {
        render.render();
        world.player.keyboard(&world.player);
        for(short i = 0; i < world.creatures.length; i++)
        {
            gravit(&world, &world.creatures[i].generic);
        }
        //teclado(player);
        //random = Random(counter);
    }
    CloseWindow();
}


