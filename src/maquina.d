module maquina;

import std.stdio;
import std.file;
import std.string;
import std.conv;

import util;

import raylib;

//--------------------------------------------
//FileData
//FileData
//FileData
//--------------------------------------------

struct FontSlot
{
    Font file;
    string name;
    int size = 20;
}

struct ModelSlot
{
    Model[] file;
    string name;
}

struct BoundingBoxSlot
{
    BoundingBox file;
    string name;
}

class FileData
{
    FontSlot[] fonts;
    ModelSlot[] models;
    BoundingBoxSlot[] boundingBoxes;

    FontSlot loadFont(string filepath, int size, string name = "")
    {
        if (name == "")
            name = filepath;
        FontSlot font = 
        {
            file: LoadFontEx(filepath.toStringz(), size, null, 0), name: name, size: size
        };
        this.fonts ~= font;
        return font;
    }

    ModelSlot loadModel(string filepath, int length = 1, string name = "")
    {
        if (name == "")
            name = filepath;
        
        ModelSlot model;

        if(filepath.endsWith(".glb")||filepath.endsWith(".obj"))
        {
            model = ModelSlot([LoadModel(filepath.toStringz())], name);
        }
        else if(filepath.endsWith('/'))
        {
            Model[] _models;

            for (int i = 0; i < length; i++) 
            {
                auto str = (filepath ~ to!string(i) ~ ".obj");
                writeln(str);
                _models ~= LoadModel(str.toStringz());
            }
            model = ModelSlot(_models, name);
        }
        this.models ~= model;
        return model;
    }
}


//--------------------------------------------
//RenderData Structs
//RenderData Structs
//RenderData Structs
//--------------------------------------------


struct RenderText
{
    string text;
    Vector2 position = Vector2(0, 0);
    Color color = Color(0, 0, 0, 255);
    int size = 1;
    Font font;
}

struct RenderModel
{
    Model[] model;
    Vector3 position;
    Vector3 scale;
    float rotationAngle;
    Color color;
    int currentFrame;
}

class RenderData
{
    Color background = {r: 255, g: 255, b: 255, a: 255};
    Camera3D camera = 
    {
        position: {x: 10, y: 5, z: 0}, 
        target: {x: 0, y: 4, z: -4}, 
        up: {x: 0, y: 1, z: 0}, 
        fovy: 80
    };
    RenderText[] texts;
    RenderModel[] models;
    void addText(string text, Vector2 position, Color color, int size, Font font)
    {
        RenderText renderText = 
        {
            text: text, 
            position: position, 
            color: color, 
            size: size, 
            font: font
        };
        this.texts ~= renderText;
    }

    void addModel(ModelSlot modelslot, Vector3 position, float rotationAngle, Vector3 scale, Color color)
    {
        RenderModel renderModel = 
        {
            model: modelslot.file, 
            position: position,  
            rotationAngle: rotationAngle, 
            scale: scale, 
            color: color,
            currentFrame: 0
        };
        this.models ~= renderModel;
    }

    void render()
    {
        BeginDrawing();
        ClearBackground(this.background);
        BeginMode3D(this.camera);
        for (int i = 0; i < this.models.length; i++)
        {
            DrawModelEx(this.models[i].model[this.models[i].currentFrame], 
                this.models[i].position, 
                Vector3(0, 1, 0), 
                this.models[i].rotationAngle, 
                this.models[i].scale, 
                this.models[i].color
            );
            if(this.models[i].currentFrame+1 < this.models[i].model.length)
                this.models[i].currentFrame++;
            else
                this.models[i].currentFrame = 0;
        }
        EndMode3D();
        for (int i = 0; i < this.texts.length; i++)
        {
            DrawTextEx(
                this.texts[i].font, 
                this.texts[i].text.ptr,
                this.texts[i].position,
                this.texts[i].size,
                0,
                this.texts[i].color
            );
        }
        EndDrawing();
    }
}

//--------------------------------------------
//WorldData
//WorldData
//WorldData
//--------------------------------------------

struct CreatureNeeds
{
    float health = 100;
    float food = 100;
    float water = 100;
    float sleep = 100;
    float social = 100;
    float fun = 100;
    float bath = 100;
    float pee = 100;
    float poo = 100;
}

struct CreatureRender
{
    ModelSlot model;
    Vector3* position;
    Vector3 scale;
    float* rotationAngle;
    Color color;
}

class Creature
{
    CreatureNeeds needs = CreatureNeeds();
    CreatureRender render = CreatureRender();
    Vector3 position = Vector3(0, 0, 0);
    float rotation = 0.0f;
    string name;
    string specime;
    this(string name, string specime)
    {
        this.name = name;
        this.specime = specime;
        ModelSlot dummy;//fix this ASAP
        this.render = CreatureRender(dummy, &this.position, Vector3(1,1,1), &this.rotation, Color(255,255,255,255));
    }
}

class WorldData
{
    Creature[] creatures;
}