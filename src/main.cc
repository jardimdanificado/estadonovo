
#include "maqquina/maqquina.hh"

void mainLoop()
{

}

int main(void)
{
    PROGRAM cprog;
    cprog.start(800,600,"Estado Novo");
    Vector3 emptyVec3 = {0,0,0};
    cprog.data.file.loadModel("./assets/models/map/level0/0.glb","mapa","map");
    Texture texture = LoadTexture("assets/images/texel_checker.png");
    
    SetCameraMode(cprog.data.session.render.scene.camera, CAMERA_THIRD_PERSON);
    cprog.data.session.render.scene.camera.target = (Vector3){2.f, 2.f, 1.f};
    cprog.data.session.render.scene.autoCreateModel("mapa0","map",cprog.data.file.findGetModel("mapa")->getModel(),0,&emptyVec3,&emptyVec3,WHITE,true);
    
    cprog.setLoop(mainLoop);
    
    while (!WindowShouldClose())
    {
        cprog.run();
    }

    return 0;
}
