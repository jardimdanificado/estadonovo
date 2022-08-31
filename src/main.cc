
#include "system/maqquina.hh"

int main(void)
{
    PROGRAM cprog;
    cprog.start(800,600,"Estado Novo");

    // Load models and texture
    cprog.data.file.loadModel("./assets/models/map/level0/0.glb","mapa","map");
    Texture texture = LoadTexture("assets/images/texel_checker.png");

    // Load shader and set up some uniforms
    
    SetCameraMode(cprog.data.session.render.scene.camera, CAMERA_THIRD_PERSON);  // Set an orbital camera mode

    SetTargetFPS(60);                       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    cprog.data.session.render.scene.camera.target = (Vector3){2.f, 2.f, 1.f};
    // Main game loop
    int razao;
    while (!WindowShouldClose())
    {
        razao = (GetFPS()/60);
        UpdateCamera(&cprog.data.session.render.scene.camera);

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------

        BeginDrawing();
        {

            ClearBackground(GRAY);
            BeginMode3D(cprog.data.session.render.scene.camera);
            {
                DrawModel(*cprog.data.file.findGetModel("mapa")->getModel(),(Vector3){0,0,0},1,WHITE);
            }
            EndMode3D();

        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
