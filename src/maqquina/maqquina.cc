#ifndef ENGINE_C
#define ENGINE_C

#include "maqquina.hh"

using _file_ = qProgram::qData::qFile;
using _render_ = qProgram::qData::qSession::qRender;
using _game_ = qProgram::qData::qGame;

qProgram::qProgram(int x, int y, string title)
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
    loadDefaultModels();
}

void qProgram::loadDefaultModels()
{
    data.file.autoLoadModel("./assets/models/map/level0/0.glb","map0","map");
    data.file.autoLoadModel("./assets/models/player/model.iqm","player","player",true);

}

void qProgram::setLoop(void(*inLoop)(qProgram::qData *prog)){userLoop = inLoop;}
void qProgram::run()
{
    data.session.render.frame++;
    data.session.render.frameRatio = round(GetFPS()/60.0);
    if(data.session.render.frameRatio != 0)
        if(data.session.render.frame%data.session.render.frameRatio==0)
        {
            userLoop(&data);
            getKey();
        }
    data.session.render.renderCurrentScene();
}

//----------------------------------------------------------------------------------
// qMath
//----------------------------------------------------------------------------------

float qMath::round360(float input)
{
    if(input >= 360)
        input -= 360;
    else if(input <0)
        input += 360;
    return(input);
}

//----------------------------------------------------------------------------------
// qKeyboard
//----------------------------------------------------------------------------------

void qProgram::qKeyboard::qKey::setFunc(void (*inFunc)(qProgram::qData*),int KeyEvent) {keyFunc[KeyEvent] = inFunc;}
void qProgram::qKeyboard::setKeyFunc(void (*inFunc)(qProgram::qData*),int KeyID, int KeyEvent)
{
    for (short int i = 0; i < 106; i++)
        if(key_id[i]==KeyID)
        {
            key[i].active[KeyEvent] = true;
            key[i].setFunc(inFunc,KeyEvent);
            break;
        }
}
void qProgram::qKeyboard::qKey::run(qProgram::qData*prog,int KeyEvent){keyFunc[KeyEvent](prog);}
void qProgram::getKey()
{
    for(short int i=0;i<106;i++)
        for(short int k=0;k<3;k++)
            if(keyboard.key[i].active[k]==true)
                switch (k)
                {
                    case KEY_EVENT::DOWN:
                    {
                        if(IsKeyDown(keyboard.key_id[i])==true)
                            keyboard.key[i].run(&data,k);
                    }
                    break;
                    case KEY_EVENT::PRESSED:
                    {
                        if(IsKeyPressed(keyboard.key_id[i])==true)
                            keyboard.key[i].run(&data,k);
                    }
                    break;
                    case KEY_EVENT::RELEASED:
                    {
                        if(IsKeyReleased(keyboard.key_id[i])==true)
                            keyboard.key[i].run(&data,k);
                    }
                    break;
                }
}

//----------------------------------------------------------------------------------
// qData FILE
//----------------------------------------------------------------------------------

qProgram::qData::qFile::qModel* _file_::getModel(int index){return(&model[index]);}
qProgram::qData::qFile::qModel* _file_::findGetModel(string inName)
{
    for(int i = 0;i<MAX::OBJ;i++)
        if(model[i].getName().compare(inName)==0)
            return(&model[i]);
    return(nullptr);
}
int _file_::findModel(string inName)
{
    for(int i = 0;i<MAX::OBJ;i++)
        if(model[i].getName().compare(inName)==0)
            return(i);
    return(-1);
}
void _file_::autoLoadModel(string path, string inName, string inType,bool animated)
{
    for(int i = 0;i<MAX::OBJ;i++)
        if(model[i].getName().compare("noname")==0)
        {
            model[i].loadModel(path);
            if(animated)
                model[i].loadAnim(path);
            model[i].setName(inName);
            model[i].setType(inType);
            break;
        }
}
void _file_::autoCreateHitbox(string inName, string inType, BoundingBox inHitbox)
{
    for(int i = 0;i<MAX::OBJ;i++)
        if(hitbox[i].getName().compare("noname")==0)
        {
            hitbox[i].create(inName,inType,inHitbox);
            break;
        }
}

//----------------------------------------------------------------------------------
// qData FILE qModelS
//----------------------------------------------------------------------------------

void _file_::qModel::setName(string newName){name = newName;}
void _file_::qModel::setType(string newType){type = newType;}
string _file_::qModel::getName(){return(name);}
string _file_::qModel::getType(){return(type);}
void _file_::qModel::loadModel(string path){model = LoadModel(path.c_str());}
void _file_::qModel::unloadModel(){UnloadModel(model);}
void _file_::qModel::loadAnim(string path)
{
    unsigned int localMax = MAX::ANIM;
    anim = LoadModelAnimations(path.c_str(), &localMax);
    animated = true;
}
Model* _file_::qModel::getModel(){return(&model);}

//----------------------------------------------------------------------------------
// qData FILE qHitbox
//----------------------------------------------------------------------------------

void _file_::qHitbox::setName(string newName){name = newName;}
void _file_::qHitbox::setType(string newType){type = newType;}
void _file_::qHitbox::loadFromFile(string path)
{
    Model localModel;
    localModel = LoadModel(path.c_str());
    hitbox = GetModelBoundingBox(localModel);
    UnloadModel(localModel);
}
void _file_::qHitbox::loadFromModel(Model* inModel){hitbox = GetModelBoundingBox(*inModel);}
void _file_::qHitbox::create(string inName, string inType, BoundingBox inHitbox)
{
    name = inName;
    type = inType;
    hitbox = inHitbox;
}
string _file_::qHitbox::getName(){return(name);}
string _file_::qHitbox::getType(){return(type);}
BoundingBox* _file_::qHitbox::getHitbox(){return(&hitbox);}

//----------------------------------------------------------------------------------
// qData qSession qRender
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
            Vector3 zerp = {0,0,0};
            for(int i = 0;i<MAX::OBJ;i++)
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

void _render_::qScene::autoCreateModel(string inName,string inType, Model *inModel, Vector3* inPosi, Vector3* inRota, bool inActive, int inFrame, Color inColor)
{
    for(int i =0; i< MAX::OBJ; i++)
        if(modelSlot[i].getName().compare("noname") == 0)
        {
            modelSlot[i].create( inName, inType, inModel, inFrame, inPosi, inRota, inColor, inActive);
            break;
        }
}
            

qProgram::qData::qSession::qRender::qScene::qModel * _render_::qScene::findGetModel(string inName)
{
    for(int i =0; i< MAX::OBJ; i++)
        if(modelSlot[i].getName().compare(inName) == 0)
            return (&modelSlot[i]);
    return nullptr;
}

//----------------------------------------------------------------------------------
// qData qSession qScene
//----------------------------------------------------------------------------------


string _render_::qScene::qModel::getName(){return(name);}
string _render_::qScene::qModel::getType(){return(type);}
bool _render_::qScene::qModel::getActive(){return(active);}
Model* _render_::qScene::qModel::getModel(){return(model);}
Vector3* _render_::qScene::qModel::getPosition(){return(position);}
Vector3* _render_::qScene::qModel::getRotation(){return(rotation);}
void _render_::qScene::qModel::setName(string newName){name = newName;}
void _render_::qScene::qModel::setType(string newType){type = newType;}
void _render_::qScene::qModel::setActive(bool newActive){active = newActive;}
void _render_::qScene::qModel::setModel(Model *inModel){model = inModel;}
void _render_::qScene::qModel::setPosition(Vector3 *newP){position = newP;}
void _render_::qScene::qModel::setRotation(Vector3 *newR){rotation = newR;}
//provide no parameters to reset the slot
void _render_::qScene::qModel::create(string inName,string inType, Model *inModel, int inFrame, Vector3* inPosi, Vector3* inRota, Color inColor, bool inActive)
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
// qSession qRender qScreen
//----------------------------------------------------------------------------------

Vector2 _render_::qScreen::getResolution(){return resolution;};
float _render_::qScreen::getMaxX(){return resolution.x;};
float _render_::qScreen::getMaxY(){return resolution.y;};
void _render_::qScreen::setResolution(int x,int y){resolution.x = x;resolution.y = y;};
void _render_::qScreen::setMaxX(float input){resolution.x = input;};
void _render_::qScreen::setMaxY(float input){resolution.y = input;};

//----------------------------------------------------------------------------------
// qData qGame qPlayer
//----------------------------------------------------------------------------------

void _game_::qPlayer::setName(string newName){name = newName;}
void _game_::qPlayer::setPosition(Vector3 newVec3){position = newVec3;}
void _game_::qPlayer::setRotation(Vector3 newVec3){position = newVec3;}
void _game_::qPlayer::setRotationY(float inY){rotation.y = inY;}
string _game_::qPlayer::getName(){return(name);}
Vector3* _game_::qPlayer::getPosition(){return &position;}
Vector3* _game_::qPlayer::getRotation(){return &rotation;}
void _game_::qPlayer::move(bool backwards)
{
    //z+ frente
    //x+ esquerda
    float  valorZ, valorX;
    int giro = rotation.y / 90;
    float resto = rotation.y - (90 * giro);
    float restodoresto = 90 - resto;
    float localSpeed = speed;
    if(backwards==true)
        localSpeed *= (-1);
    valorZ = localSpeed - resto * (localSpeed / 90);
    valorX = localSpeed - restodoresto * (localSpeed / 90);
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
    }
}
void _game_::qPlayer::rotate(bool right)
{
    if(right == true)
        rotation.y -= 3;
    else
        rotation.y += 3;
}
//----------------------------------------------------------------------------------
// qData qGame qMap
//----------------------------------------------------------------------------------

void _game_::qMap::setName(string newName){name = newName;}
void _game_::qMap::setModel(Model*inModel){model = inModel;}
string _game_::qMap::getName(){return(name);}
Model* _game_::qMap::getModel(){return(model);}
void _game_::qMap::setPosition(Vector3 newVec3){position = newVec3;}
void _game_::qMap::setRotation(Vector3 newVec3){position = newVec3;}
Vector3* _game_::qMap::getPosition(){return &position;}
Vector3* _game_::qMap::getRotation(){return &rotation;}

#endif
