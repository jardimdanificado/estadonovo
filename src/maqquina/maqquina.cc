#ifndef ENGINE_C
#define ENGINE_C

#include "maqquina.hh"

unsigned int MAX_ANIM = MAX::ANIM;

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
    data.session.render.scene.camera = 
    {
        (Vector3){ 2.0f, 2.0f, 6.0f },      // position
        (Vector3){ 0.0f, 0.5f, 0.0f },      // target
        (Vector3){ 0.0f, 1.0f, 0.0f },      // up
        45.0f, CAMERA_PERSPECTIVE 
    };        // fov, type
    SetCameraMode(data.session.render.scene.camera, CAMERA_FREE);
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
void _file_::autoLoadModel(string inName, string inType,string path,bool inAnimated)
{
    for(int i = 0;i<MAX::OBJ;i++)
        if(model[i].getName().compare("noname")==0)
        {
            model[i].loadModel(path);
            if(inAnimated)
            {
                model[i].loadAnim(path);
            }
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
void _file_::autoCreateHitboxFromModel(string inName, string inType, string path, bool inActive)
{
    for(int i = 0;i<MAX::OBJ;i++)
        if(hitbox[i].getName().compare("noname")==0)
        {
        	hitbox[i].setName(inName);
        	hitbox[i].setType(inType);
        	hitbox[i].setActive(inActive);
            hitbox[i].loadFromModel(path);
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
    anim = LoadModelAnimations(path.c_str(), &MAX_ANIM);
	printf("anim0=%d  anim1=%d\n",anim[0].frameCount,anim[1].frameCount);
    animated = true;
}
ModelAnimation **_file_::qModel::getAnim(){return(&anim);}
Model* _file_::qModel::getModel(){return(&model);}

//----------------------------------------------------------------------------------
// qData FILE qHitbox
//----------------------------------------------------------------------------------

void _file_::qHitbox::setName(string newName){name = newName;}
void _file_::qHitbox::setType(string newType){type = newType;}
void _file_::qHitbox::setActive(bool inActive){active = inActive;}
void _file_::qHitbox::loadFromFile(string path)
{
    Model localModel;
    localModel = LoadModel(path.c_str());
    hitbox = GetModelBoundingBox(localModel);
    UnloadModel(localModel);
}
void _file_::qHitbox::loadFromModel(string path)
{
	Model tempModel;
	tempModel = LoadModel(path.c_str());
	hitbox = GetModelBoundingBox(tempModel);
	UnloadModel(tempModel);
}
void _file_::qHitbox::create(string inName, string inType, BoundingBox inHitbox)
{
    name = inName;
    type = inType;
    hitbox = inHitbox;
}
string _file_::qHitbox::getName(){return(name);}
string _file_::qHitbox::getType(){return(type);}
BoundingBox* _file_::qHitbox::getHitbox(){return(&hitbox);}
bool _file_::qHitbox::getActive(){return(active);}

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
            for(int i = 0;i<MAX::OBJ;i++)
                if(scene.modelSlot[i].getActive()==true)
                {
                    DrawModelEx(*scene.modelSlot[i].getModel(), *scene.modelSlot[i].getPosition(), {0,1,0}, scene.modelSlot[i].getRotation()->y, {1,1,1}, *scene.modelSlot[i].getColor());
				}
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

void _render_::qScene::autoCreateModel(string inName,string inType, Model *inModel, ModelAnimation **inAnim,  bool inActive, Vector3* inPosi, Vector3* inRota,  int inFrame, Color inColor)
{
    for(int i =0; i< MAX::OBJ; i++)
        if(modelSlot[i].getName().compare("noname") == 0)
        {
            modelSlot[i] = qModel( inName, inType, inModel, inAnim, inActive, inFrame, inPosi, inRota, inColor);
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
Color* _render_::qScene::qModel::getColor(){return &color;}
void _render_::qScene::qModel::setColor(Color inColor){color = inColor;}
void _render_::qScene::qModel::setName(string newName){name = newName;}
void _render_::qScene::qModel::setType(string newType){type = newType;}
void _render_::qScene::qModel::setActive(bool newActive){active = newActive;}
void _render_::qScene::qModel::setModel(Model *inModel){model = inModel;}
void _render_::qScene::qModel::setPosition(Vector3 *newP){position = newP;}
void _render_::qScene::qModel::setRotation(Vector3 *newR){rotation = newR;}
void _render_::qScene::qModel::frame(int inVal)
{
	currentFrame+=inVal;
	
    if (currentFrame >= anim[currentAnim].frameCount) 
    	currentFrame = 0;
    else if(currentFrame <0) 
    	currentFrame = currentFrame + (anim[currentAnim].frameCount - 1 );
    printf("anim0=%d  anim1=%d\n",anim[0].frameCount,anim[1].frameCount);
    UpdateModelAnimation(*model, anim[currentAnim], currentFrame);
}

_render_::qScene::qModel::qModel(string inName ,string inType, Model *inModel , ModelAnimation **inAnim ,bool inActive , int inFrame , Vector3* inPosi, Vector3* inRota,  Color inColor)
{
	name = inName;
    type = inType;
    model = inModel;
    anim = *inAnim;
    currentFrame = inFrame;
    position = inPosi;
    rotation = inRota;
    color = inColor;
    active = inActive;
    if(inAnim != nullptr)
    	animated = true;
};

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
