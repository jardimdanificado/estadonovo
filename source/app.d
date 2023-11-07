import std.stdio;
import std.string;
import std.conv;
import raylib;

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
    Vector3 rotation;
    Vector3 scale;
    float rotationAngle;
    Color color;
    int currentFrame;
}

class Data
{
    FontSlot[] fonts;
    ModelSlot[] models;
    BoundingBoxSlot[] boundingBoxes;
    void loadFont(string filepath, int size, string name = "")
    {
        if (name == "")
            name = filepath;
        FontSlot font = {
            file: LoadFontEx(filepath.toStringz(), size, null, 0), name: name, size: size
        };
        this.fonts ~= font;
    }

    ModelSlot loadModel(string filepath, int length = 1, string name = "")
    {
        if (name == "")
            name = filepath;
        
        ModelSlot model;

        if(filepath.endsWith(".glb")||filepath.endsWith(".obj")||filepath.endsWith(".glfw"))
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

    this()
    {

    }
}

class Render
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

    void addModel(ModelSlot modelslot, Vector3 position, Vector3 rotation, float rotationAngle, Vector3 scale, Color color)
    {

        RenderModel renderModel = 
        {
            model: modelslot.file, 
            position: position, 
            rotation: rotation, 
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
                this.models[i].rotation, 
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
            DrawTextEx(this.texts[i].font, this.texts[i].text.ptr, this.texts[i].position, this.texts[i].size, 0, this
                    .texts[i].color);
        }
        EndDrawing();
    }
}

void main()
{
    Data data = new Data();
    Render render = new Render();
    // call this before using raylib
    validateRaylibBinding();
    InitWindow(800, 600, "Estado Novo");
    SetTargetFPS(60);

    data.loadFont("assets/font/kremlin.ttf", 20);
    data.loadModel("assets/models/map/level0/0.glb");
    data.loadModel("assets/models/player/walk/",24);
    
    render.addText("Estado Novo", Vector2(100,100), Color(255,0,0,255), 20, data.fonts[0].file);
    render.addModel(data.models[0], Vector3Zero(), Vector3Zero(), 0, Vector3(1,1,1), Color(255, 255, 255, 255));
    render.addModel(data.models[1], Vector3(1,3,1), Vector3Zero(), 0, Vector3(1,1,1), Color(255, 0, 0, 255));
    
    while (!WindowShouldClose())
    {
        render.render();
    }
    CloseWindow();
}
