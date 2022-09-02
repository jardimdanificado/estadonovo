#ifndef ENGINE_C
#define ENGINE_C

#include "maqquina.hh"
using _file_ = PROGRAM::DATA::LFILE;
using _render_ = PROGRAM::DATA::SESSION::RENDER;
using _game_ = PROGRAM::DATA::GAME;

void PROGRAM::start(int x, int y, string title)
{
    //SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); 
    data.session.render.screen.setMaxX(x);
    data.session.render.screen.setMaxY(y);
    InitWindow(x, x, title.c_str());
    
    // Define the camera to look into our 3d world
    data.session.render.scene.camera = {
        (Vector3){ 2.0f, 2.0f, 6.0f },      // position
        (Vector3){ 0.0f, 0.5f, 0.0f },      // target
        (Vector3){ 0.0f, 1.0f, 0.0f },      // up
        45.0f, CAMERA_PERSPECTIVE };        // fov, type
    SetCameraMode(data.session.render.scene.camera, CAMERA_FREE);
}

void PROGRAM::setLoop(void(*inLoop)()){userLoop = inLoop;}
void PROGRAM::run()
{
    data.session.render.frame++;
    data.session.render.frameRatio = round(GetFPS()/60.0);
    if(data.session.render.frameRatio == 0)
        data.session.render.frameRatio = 1;
    if(data.session.render.frame%data.session.render.frameRatio==0)
        userLoop();
    data.session.render.renderCurrentScene();
}

//----------------------------------------------------------------------------------
// DATA FILE
//----------------------------------------------------------------------------------

PROGRAM::DATA::LFILE::MODEL* _file_::getModel(int index){return(&model[index]);}
PROGRAM::DATA::LFILE::MODEL* _file_::findGetModel(string name)
{
    for(int i = 0;i<MAX_OBJ;i++)
        if(model[i].getName().compare(name)==0)
            return(&model[i]);
    return(nullptr);
}
int _file_::findModel(string name)
{
    for(int i = 0;i<MAX_OBJ;i++)
        if(model[i].getName().compare(name)==0)
            return(i);
    return(-1);
}
void _file_::loadModel(string path, string name, string type = "notype")
{
    for(int i = 0;i<MAX_OBJ;i++)
        if(model[i].getName().compare("noname")==0)
        {
            model[i].load(path);
            model[i].setName(name);
            model[i].setType(type);
            break;
        }
}

//----------------------------------------------------------------------------------
// DATA FILE MODELS
//----------------------------------------------------------------------------------

void _file_::MODEL::setName(string newName){name = newName;}
void _file_::MODEL::setType(string newType){type = newType;}
string _file_::MODEL::getName(){return(name);}
string _file_::MODEL::getType(){return(type);}
void _file_::MODEL::load(string path){model = LoadModel(path.c_str());}
void _file_::MODEL::unload(){UnloadModel(model);}
Model* _file_::MODEL::getModel(){return(&model);}

//----------------------------------------------------------------------------------
// DATA FILE HITBOX
//----------------------------------------------------------------------------------

void _file_::HITBOX::setName(string newName){name = newName;}
void _file_::HITBOX::setType(string newType){type = newType;}
void _file_::HITBOX::loadFromFile(string path)
{
    Model localModel;
    localModel = LoadModel(path.c_str());
    hitbox = GetModelBoundingBox(localModel);
    UnloadModel(localModel);
}
void _file_::HITBOX::loadFromModel(Model* inModel){hitbox = GetModelBoundingBox(*inModel);}
void _file_::HITBOX::create(string inName, string inType, BoundingBox inHitbox)
{
    name = inName;
    type = inType;
    hitbox = inHitbox;
}
string _file_::HITBOX::getName(){return(name);}
string _file_::HITBOX::getType(){return(type);}
BoundingBox* _file_::HITBOX::getHitbox(){return(&hitbox);}

//----------------------------------------------------------------------------------
// DATA SESSION RENDER
//----------------------------------------------------------------------------------

void _render_::renderCurrentScene()
{
    UpdateCamera(&scene.camera);
    
    BeginDrawing();
    {
        ClearBackground(GRAY);
        BeginMode3D(scene.camera);
        {
            bool doubleCheck = false;//it checks if there are 2 empty slots in sequence, if true it will exit loop
            
            for(int i = 0;i<MAX_OBJ;i++)
                if(scene.modelSlot[i].getActive()==true)
                    DrawModelEx(*scene.modelSlot[i].getModel(),*scene.modelSlot[i].getPosition(),{0,1,0},scene.modelSlot[i].getRotation()->y,{1,1,1},WHITE);
                else
                    if(doubleCheck == true)
                        break;
                    else
                        doubleCheck = true;
        }
        EndMode3D();
    }
    EndDrawing();
};

void _render_::SCENE::autoCreateModel(string inName,string inType, Model *inModel, int inFrame, Vector3* inPosi, Vector3* inRota, Color inColor, bool inActive)
{
    for(int i =0; i< MAX_OBJ; i++)
        if(modelSlot[i].getName().compare("noname") == 0)
            modelSlot[i].create( inName, inType, inModel, inFrame, inPosi, inRota, inColor, inActive);
}

PROGRAM::DATA::SESSION::RENDER::SCENE::MODEL * _render_::SCENE::findGetModel(string inName)
{
    for(int i =0; i< MAX_OBJ; i++)
        if(modelSlot[i].getName().compare(inName) == 0)
            return (&modelSlot[i]);
    return nullptr;
}

//----------------------------------------------------------------------------------
// DATA SESSION SCENE
//----------------------------------------------------------------------------------


string _render_::SCENE::MODEL::getName(){return(name);}
string _render_::SCENE::MODEL::getType(){return(type);}
bool _render_::SCENE::MODEL::getActive(){return(active);}
Model* _render_::SCENE::MODEL::getModel(){return(model);}
Vector3* _render_::SCENE::MODEL::getPosition(){return(position);}
Vector3* _render_::SCENE::MODEL::getRotation(){return(rotation);}
void _render_::SCENE::MODEL::setName(string newName){name = newName;}
void _render_::SCENE::MODEL::setType(string newType){type = newType;}

void _render_::SCENE::MODEL::setActive(bool newActive){active = newActive;}
void _render_::SCENE::MODEL::setModel(Model *inModel){model = inModel;}
void _render_::SCENE::MODEL::setPosition(Vector3 *newP){position = newP;}
void _render_::SCENE::MODEL::setRotation(Vector3 *newR){rotation = newR;}
//provide no parameters to reset the slot
void _render_::SCENE::MODEL::create(string inName,string inType, Model *inModel, int inFrame, Vector3* inPosi, Vector3* inRota, Color inColor, bool inActive)
{
    name = inName;
    type = inType;
    model = inModel;
    frame = inFrame;
    position = inPosi;
    rotation = inRota;
    color = inColor;
    active = inActive;
}

//----------------------------------------------------------------------------------
// SESSION RENDER SCREEN
//----------------------------------------------------------------------------------

Vector2 _render_::SCREEN::getResolution(){return resolution;};
float _render_::SCREEN::getMaxX(){return resolution.x;};
float _render_::SCREEN::getMaxY(){return resolution.y;};
void _render_::SCREEN::setResolution(int x,int y){resolution.x = x;resolution.y = y;};
void _render_::SCREEN::setMaxX(float input){resolution.x = input;};
void _render_::SCREEN::setMaxY(float input){resolution.y = input;};

//----------------------------------------------------------------------------------
// DATA GAME PLAYER
//----------------------------------------------------------------------------------

void _game_::PLAYER::setName(string newName){name = newName;}
void _game_::PLAYER::setPosition(Vector3 newVec3){position = newVec3;}
void _game_::PLAYER::setRotation(Vector3 newVec3){position = newVec3;}
string _game_::PLAYER::getName(){return(name);}
Vector3* _game_::PLAYER::getPosition(){return &position;}
Vector3* _game_::PLAYER::getRotation(){return &rotation;}

//----------------------------------------------------------------------------------
// DATA GAME MAP
//----------------------------------------------------------------------------------

void _game_::MAP::setName(string newName){name = newName;}
void _game_::MAP::setModel(Model*inModel){model = inModel;}
string _game_::MAP::getName(){return(name);}
Model* _game_::MAP::getModel(){return(model);}
void _game_::MAP::setPosition(Vector3 newVec3){position = newVec3;}
void _game_::MAP::setRotation(Vector3 newVec3){position = newVec3;}
Vector3* _game_::MAP::getPosition(){return &position;}
Vector3* _game_::MAP::getRotation(){return &rotation;}

#endif
