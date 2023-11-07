import std.stdio;
import raylib;

struct FontSlot
{
    Font file;
    string name;
    int size;
}

struct ModelSlot
{
    Model file;
    string name;
    int size;
}

class Data 
{
    FontSlot[] fonts;
    ModelSlot[] models;

    this()
    {

    }
}

void main()
{
    // call this before using raylib
    validateRaylibBinding();
    InitWindow(800, 600, "Hello, Raylib-D!");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Colors.RAYWHITE);
        //DrawText("Hello, World!", 400, 300, 20, Colors.BLACK);
        EndDrawing();
    }
    CloseWindow();
}