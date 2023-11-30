import std.stdio;
import std.string;
import std.conv;
import std.file;
import std.json;
import std.random;
import std.math;

import raylib;

import util;
import engine;

alias key = KeyboardKey;

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
    
    // set exit key to none
    SetExitKey(0);

    //adding specimes and maps
    world.specimes ~= new SpecimeData("data/specime/human/");
    world.maps ~= new MapData("data/map/0/");
    CreatureData* player = world.newCreature("player", "human");
    player.generic.position.y = 5;
    
    world.startup(player);
    
    //menu
    Font titleFont = render.loadFont("data/font/Mockery.ttf", uniform(20, 90));
    FullscreenMenu menu = FullscreenMenu();
    
    menu.buttons ~= MenuButton("exit",Vector2(GetScreenWidth() - (MeasureTextEx(render.fonts[0],"exit",20,0)).x-7, GetScreenHeight() - 26), cor_cinza, cor_marrom, cor_laranja, &render.fonts[0]);
    menu.buttons ~= MenuButton("play",Vector2(GetScreenWidth() - (MeasureTextEx(render.fonts[0],"play",20,0)).x-7, GetScreenHeight() - 48), cor_cinza, cor_marrom, cor_laranja, &render.fonts[0]);
    
    int vmargin = to!int(((((render.screen.y/titleFont.baseSize)+1)*titleFont.baseSize) - render.screen.y)/3);
    int hmargin = to!int((render.screen.x - 50) - to!int((render.screen.x-50)/MeasureTextEx(titleFont, "estado novo ", titleFont.baseSize, 0).x)*MeasureTextEx(titleFont, "estado novo ", titleFont.baseSize, 0).x);
    for(short i = 0; i < to!int(render.screen.y/titleFont.baseSize)+2; i++)
    {
        for(short j = 0; j < to!int((render.screen.x-50)/MeasureTextEx(titleFont, "estado novo ", titleFont.baseSize, 0).x); j++)
        {
            menu.buttons ~= MenuButton("estado novo",Vector2(hmargin/2 + j * (MeasureTextEx(titleFont, "estado novo ", titleFont.baseSize, 0).x), -vmargin + i*titleFont.baseSize), cor_cinza, cor_marrom, cor_laranja, &titleFont, titleFont.baseSize);
            menu.buttons[menu.buttons.length-1].action = ()
            {
                return "offload";
            };
        }
        //menu.buttons ~= MenuButton("estado novo",Vector2(7, -margin + i*titleFont.baseSize), cor_cinza, cor_marrom, cor_laranja, &titleFont, titleFont.baseSize);
        
    }
    
    menu.backgroundColor = cor_quase_branco;

    menu.buttons[1].action = () 
    {
        return "offload";
    };
    menu.buttons[0].action = () 
    {
        session.exit = true;
        return "exit";
    };

    menu.loop(()
    {
        session.tick++;
    });


    world.player.keyboard = (PlayerData* player) 
    {
        if (IsKeyPressed(key.KEY_W))
        {
            player.creaturePointer.renderData.anim = 1;
        }
        else if(IsKeyReleased(key.KEY_W))
        {
            player.creaturePointer.renderData.anim = 0;
        }
        
        if (IsKeyPressed(key.KEY_S))
        {
            player.creaturePointer.renderData.anim = 1;
            player.creaturePointer.renderData.reverse = true;
        }
        else if(IsKeyReleased(key.KEY_S))
        {
            player.creaturePointer.renderData.anim = 0;
            player.creaturePointer.renderData.reverse = false;
        }

        if(IsKeyDown(key.KEY_D))
        {
            player.creaturePointer.generic.rotation += 6;
            if(player.creaturePointer.generic.rotation > 360)
            {
                player.creaturePointer.generic.rotation -= 360;
            }
        }
        if(IsKeyDown(key.KEY_A))
        {
            player.creaturePointer.generic.rotation -= 6;
            if(player.creaturePointer.generic.rotation < 0)
            {
                player.creaturePointer.generic.rotation += 360;
            }
        }
        if (IsKeyDown(key.KEY_W) && !playerCollider(&world, &player.creaturePointer.generic, false))
        {
            float tempSpeed;
            if(IsKeyDown(key.KEY_LEFT_SHIFT))
            {
                tempSpeed = player.creaturePointer.generic.speed*1.75;
                player.creaturePointer.renderData.anim = 2;
            }
            else
            {
                tempSpeed = player.creaturePointer.generic.speed;
                player.creaturePointer.renderData.anim = 1;
            }
            Vector3 temp = move3d(player.creaturePointer.generic.position, player.creaturePointer.generic.rotation, tempSpeed);
            player.creaturePointer.generic.position.x = temp.x;
            player.creaturePointer.generic.position.z = temp.z;
        }
        if (IsKeyDown(key.KEY_S) && !playerCollider(&world, &player.creaturePointer.generic, true))
        {
            float tempSpeed;
            if(IsKeyDown(key.KEY_LEFT_SHIFT))
            {
                tempSpeed = player.creaturePointer.generic.speed*1.75;
                player.creaturePointer.renderData.anim = 2;
            }
            else
            {
                tempSpeed = player.creaturePointer.generic.speed * 0.75;
                player.creaturePointer.renderData.anim = 1;
            }
            Vector3 temp = move3d(player.creaturePointer.generic.position, player.creaturePointer.generic.rotation, -tempSpeed);
            player.creaturePointer.generic.position.x = temp.x;
            player.creaturePointer.generic.position.z = temp.z;
        }
        if (IsKeyDown(key.KEY_SPACE) && player.creaturePointer.generic.fallTime < 32)
        {
            player.creaturePointer.generic.position.y += 0.3;
        }
        if(IsKeyDown(key.KEY_ESCAPE))
        {
            menu.loop(()
            {
                session.tick++;
            });
        }
    };
    
    SetTargetFPS(to!int(config["framerate"].integer));

    while(!WindowShouldClose() && !session.exit)
    {
        render.render();
        world.player.keyboard(&world.player);
        for(short i = 0; i < world.creatures.length; i++)
        {
            gravit(&world, &world.creatures[i].generic);
        }
    }
    CloseWindow();
}


