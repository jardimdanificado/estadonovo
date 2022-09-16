#ifndef ENGINE_C
#define ENGINE_C

#include "maqquina.hh"

unsigned int MAX_ANIM = MAX::ANIM;

using _file_ = qData::qFile;
using _render_ = qData::qSession::qRender;
using _game_ = qData::qMundo;

// Update model animated vertex data (positions and normals) for a given frame
// NOTE: Updated data is returned as mesh
Mesh qTools::qMesh::rotateMeshFromAnim(Model model, ModelAnimation anim, int frame)
{
    if((anim.frameCount > 0) && (anim.bones != NULL) && (anim.framePoses != NULL))
    {
        if(frame >= anim.frameCount) frame = frame % anim.frameCount;

        for(int m = 0; m < model.meshCount; m++)
        {
            Mesh mesh = model.meshes[m];
            if(mesh.boneIds == NULL || mesh.boneWeights == NULL)
            {
                continue;
            }

            bool updated = false; // set to true when anim vertex information is updated
            Vector3 animVertex = { 0,0,0 };
            Vector3 animNormal = { 0,0,0 };

            Vector3 inTranslation = { 0,0,0 };
            Quaternion inRotation = { 0,0,0,0 };
            // Vector3 inScale = { 0 };

            Vector3 outTranslation = { 0,0,0 };
            Quaternion outRotation = { 0,0,0,0 };
            Vector3 outScale = { 0,0,0 };

            int boneId = 0;
            int boneCounter = 0;
            float boneWeight = 0.0;

            const int vValues = mesh.vertexCount * 3;
            for(int vCounter = 0; vCounter < vValues; vCounter += 3)
            {
                mesh.animVertices[vCounter] = 0;
                mesh.animVertices[vCounter + 1] = 0;
                mesh.animVertices[vCounter + 2] = 0;

                if(mesh.animNormals != NULL)
                {
                    mesh.animNormals[vCounter] = 0;
                    mesh.animNormals[vCounter + 1] = 0;
                    mesh.animNormals[vCounter + 2] = 0;
                }

                // Iterates over 4 bones per vertex
                for(int j = 0; j < 4; j++, boneCounter++)
                {
                    boneWeight = mesh.boneWeights[boneCounter];
                    // early stop when no transformation will be applied
                    if(boneWeight == 0.0f)
                    {
                        continue;
                    }
                    boneId = mesh.boneIds[boneCounter];
                    inTranslation = model.bindPose[boneId].translation;
                    inRotation = model.bindPose[boneId].rotation;
                    outTranslation = anim.framePoses[frame][boneId].translation;
                    outRotation = anim.framePoses[frame][boneId].rotation;
                    outScale = anim.framePoses[frame][boneId].scale;

                    // Vertices processing
                    // NOTE: We use meshes.vertices (default vertex position) to calculate meshes.animVertices (animated vertex position)
                    animVertex = (Vector3) { mesh.vertices[vCounter], mesh.vertices[vCounter + 1], mesh.vertices[vCounter + 2] };
                    animVertex = Vector3Multiply(animVertex, outScale);
                    animVertex = Vector3Subtract(animVertex, inTranslation);
                    animVertex = Vector3RotateByQuaternion(animVertex, QuaternionMultiply(outRotation, QuaternionInvert(inRotation)));
                    animVertex = Vector3Add(animVertex, outTranslation);
                    mesh.animVertices[vCounter] += animVertex.x * boneWeight;
                    mesh.animVertices[vCounter + 1] += animVertex.y * boneWeight;
                    mesh.animVertices[vCounter + 2] += animVertex.z * boneWeight;
                    updated = true;

                    // Normals processing
                    // NOTE: We use meshes.baseNormals (default normal) to calculate meshes.normals (animated normals)
                    if(mesh.normals != NULL)
                    {
                        animNormal = (Vector3) { mesh.normals[vCounter], mesh.normals[vCounter + 1], mesh.normals[vCounter + 2] };
                        animNormal = Vector3RotateByQuaternion(animNormal, QuaternionMultiply(outRotation, QuaternionInvert(inRotation)));
                        mesh.animNormals[vCounter] += animNormal.x * boneWeight;
                        mesh.animNormals[vCounter + 1] += animNormal.y * boneWeight;
                        mesh.animNormals[vCounter + 2] += animNormal.z * boneWeight;
                    }
                }
            }
            if(updated)
            {
                mesh.vertices = mesh.animVertices;
                return(mesh);
            }
        }
    }
    return(model.meshes[0]);
}

qProgram::qProgram(int x, int y, string title)
{
    //SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); 
    data.session.render.screen.setMaxX(x);
    data.session.render.screen.setMaxY(y);
    InitWindow(x, x, title.c_str());
    for(int i = 0;i<MAX::OBJ;i++)
    	data.session.render.scene.hitbox[i] = &data.file.hitbox[i];
    // Define the camera to look into our 3d world
    data.session.render.scene.camera = 
    {
        (Vector3){ 2.0f, 2.0f, 6.0f },      // position
        (Vector3){ 0.0f, 0.5f, 0.0f },      // target
        (Vector3){ 0.0f, 1.0f, 0.0f },      // up
        45.0f, CAMERA_PERSPECTIVE 
    };        // fov, type
    SetCameraMode(data.session.render.scene.camera, CAMERA_FREE);
};

void qProgram::setLoop(void(*inLoop)(qData *prog)){userLoop = inLoop;}
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

void qProgram::qKeyboard::qKey::setFunc(void (*inFunc)(qData*),int KeyEvent) {keyFunc[KeyEvent] = inFunc;}
void qProgram::qKeyboard::setKeyFunc(void (*inFunc)(qData*),int KeyID, int KeyEvent)
{
    for (short int i = 0; i < 106; i++)
        if(key_id[i]==KeyID)
        {
            key[i].active[KeyEvent] = true;
            key[i].setFunc(inFunc,KeyEvent);
            break;
        }
}
void qProgram::qKeyboard::qKey::run(qData*prog,int KeyEvent){keyFunc[KeyEvent](prog);}
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

qData::qFile::qModel* _file_::getModel(int index){return(&model[index]);}
qData::qFile::qModel* _file_::findGetModel(string inName)
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
            hitbox[i].loadFromModel(path);
            hitbox[i].setActive(inActive);
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
bool _file_::qHitbox::getActive(){return(active);}
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
            {
            	if(scene.hitbox[i]->getActive()==true)
                {
                	DrawBoundingBox(*scene.hitbox[i]->getHitbox() , BLACK);
				}
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

qData::qSession::qRender::qScene::qModel * _render_::qScene::findGetModel(string inName)
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
// qData qGame qHuman
//----------------------------------------------------------------------------------

void _game_::qCreature::qHuman::setName(string newName){name = newName;}
void _game_::qCreature::qHuman::setPosition(Vector3 newVec3){position = newVec3;}
void _game_::qCreature::qHuman::setRotation(Vector3 newVec3){position = newVec3;}
void _game_::qCreature::qHuman::setRotationY(float inY){rotation.y = inY;}
string _game_::qCreature::qHuman::getName(){return(name);}
Vector3* _game_::qCreature::qHuman::getPosition(){return &position;}
Vector3* _game_::qCreature::qHuman::getRotation(){return &rotation;}
void _game_::qCreature::qHuman::move(bool backwards)
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
void _game_::qCreature::qHuman::rotate(bool right)
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
