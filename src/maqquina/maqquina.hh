#ifndef MQENGINE_HEADER
#define MQENGINE_HEADER

#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;
using std::string;
using std::stringstream;

#include "raylib/raylib.h"
#include "raylib/raymath.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

namespace mqq
{
    enum TYPE
    {
        PLAYER,
        MAP,
        ITEM
    };

    enum KEY_EVENT
    {
        DOWN,RELEASED,PRESSED
    };

    enum MAX
    {
        OBJ = 64,
        ANIM = 3
    };

    namespace qMath
    {
        float round360(float input);
    };
    class qProgram
    {
        public:
            struct qData
            {
                struct qFile
                {
                    class qHitbox
                    {
                        string name = "noname";
                        string type = "notype";
                        bool active = false;
                        BoundingBox hitbox;
                        public:
                        	void setActive(bool inActive);
                            void setName(string newName);
                            void setType(string newtype);
                            bool getActive();
                            string getName();
                            string getType();
                            BoundingBox *getHitbox();
                            void loadFromFile(string path);
                            void loadFromModel(string path);
                            void create(string inName = "noname", string inType= "notype",BoundingBox inHitbox = (BoundingBox){{0,0,0},{0,0,0}});
                    };
                    class qModel
                    {
                        string name = "noname";
                        string type = "notype";
                        Model model;
                        ModelAnimation* anim;
                       	bool animated = false;
                        public:
                            void setName(string newName);
                            void setType(string newtype);
                            string getName();
                            string getType();
                            Model *getModel();
                            ModelAnimation **getAnim();
                            void loadModel(string path);
                            void loadAnim(string path);
                            void unloadAnim();
                            void unloadModel();
                    };
                    qModel model[MAX::OBJ];
                    qHitbox hitbox[MAX::OBJ];
                    qProgram::qData::qFile::qModel* getModel(int index);
                    qProgram::qData::qFile::qModel* findGetModel(string inName);
                    int findModel(string inName);
                    void autoLoadModel(string inName, string inType, string path, bool inAnimated = false);
                    void autoCreateHitbox(string inName, string inType,BoundingBox inHitbox);
                    void autoCreateHitboxFromModel(string inName, string inType, string path, bool inActive = true);
                };
                struct qGame
                {
                    class qPlayer
                    {
                        struct qBody
                        {
                            struct qHead
                            {
                                BoundingBox *hitbox = nullptr;
                                struct qFace
                                {
                                    struct qEye
                                    {
                                        string status = "saudavel";
                                        float hp = 100;
                                    };
                                    struct qMouth
                                    {
                                        struct qTeeth
                                        {
                                            string status = "saudavel";
                                            float hp = 100;
                                        };
                                        qTeeth teeth[32];
                                        string status = "saudavel";
                                        float hp = 100;
                                    };
                                    struct qNose
                                    {
                                        string status = "saudavel";
                                        float hp = 100;
                                    };
                                    struct qEyebrow
                                    {
                                        string status = "natural";
                                        float hp = 100;
                                    };
                                    struct qHair
                                    {
                                        string status = "careca";
                                        float hp = 0;
                                    };
                                    struct qBeard
                                    {
                                        string status = "careca";
                                        float hp = 0;
                                    };
                                    qEye eye[2];
                                    qMouth mouth;
                                    qNose nose;
                                    qEyebrow eyebrow[2];
                                    qHair hair;
                                    qBeard beard;
                                };
                                qFace face;
                            };
                            struct qNeck
                            {
                                BoundingBox *hitbox = nullptr;
                                string status = "saudavel";
                                float hp = 100;
                            };
                            struct qChest
                            {
                                BoundingBox *hitbox = nullptr;
                                string status = "saudavel";
                                float hp = 100;
                            };
                            struct qBelly
                            {
                                BoundingBox *hitbox = nullptr;
                                string status = "saudavel";
                                float hp = 100;
                            };
                            struct qShoulder
                            {
                                BoundingBox *hitbox = nullptr;
                                string status = "saudavel";
                                float hp = 100;
                            };
                            struct qArm
                            {
                                BoundingBox *hitbox = nullptr;
                                string status = "saudavel";
                                float hp = 100;
                            };
                            struct qHand
                            {
                                struct qFinger
                                {
                                    struct qNail
                                    {
                                        string status = "saudavel";
                                        float hp = 100;
                                    };
                                    qNail nail;
                                };
                                qFinger finger[5];
                                BoundingBox *hitbox = nullptr;
                                string status = "saudavel";
                                float hp = 100;
                            };
                            struct qUpperleg
                            {
                                BoundingBox *hitbox = nullptr;
                                string status = "saudavel";
                                float hp = 100;
                            };
                            struct qLeg
                            {
                                struct qFeet
                                {
                                    BoundingBox *hitbox = nullptr;
                                    string status = "saudavel";
                                    float hp = 100;
                                };
                                qFeet feet;
                                BoundingBox *hitbox = nullptr;
                                string status = "saudavel";
                                float hp = 100;
                            };
                            qHead head;
                            qNeck neck;
                            qChest chest;
                            qBelly belly;
                            qShoulder shoulder[2];
                            qArm arm[2];
                            qHand hand[2];
                            qUpperleg upperleg[2];
                            qLeg leg[2];
                        };
                        qBody body;
                        string name = "ninguem";
                        Vector3 position = {0,0,0};
                        Vector3 rotation = {0,0,0};
                        float speed = 0.06;
                        public:
                            void setName(string newName);
                            void setPosition(Vector3 inPosition);
                            void setRotation(Vector3 inRotation);
                            void setRotationY(float inY);
                            string getName();
                            Vector3 *getPosition();
                            Vector3 *getRotation();
                            void move(bool backward = false);//negative values for moving backwards
                            void rotate(bool right = false);
                    };
                    class qMap
                    {
                        string name = "nenhum";
                        Model *model = nullptr;
                        Vector3 position = (Vector3){0,0,0};
                        Vector3 rotation = (Vector3){0,0,0};
                        public:
                            void setName(string newName);
                            void setModel(Model *modelPtr);
                            void setPosition(Vector3 inPosition);
                            void setRotation(Vector3 inRotation);
                            string getName();
                            Model* getModel();
                            Vector3* getPosition();
                            Vector3* getRotation();
                    };
                    public:
                        qPlayer player[MAX::OBJ];
                        qMap map;
                };
                struct qSession
                {
                    struct qRender
                    {
                        struct qScene
                        {
                            class qModel
                            {
                                string name = "noname";
                                string type = "notype";
                                bool active = false;
                                Model *model = nullptr;
                                ModelAnimation **anim = nullptr;
                                Vector3 *position = nullptr;
                                Vector3 *rotation = nullptr;
                                Color color = WHITE;
                                bool animated = false;
                                public:
                                	int currentFrame = 0;
                                	int currentAnim = 0;
                                    void setName(string newName);
                                    void setType(string newType);
                                    void setActive(bool newActive);
                                    void setModel(Model *inModel);
                                    void setColor(Color inColor);
                                    void setPosition(Vector3 *inPosi);
                                    void setRotation(Vector3 *inRota);
                                    void reset();
									void updateAnim();
									void frame(int inVal = 1);
                                    string getName();
                                    string getType();
                                    bool getActive();
                                    Model *getModel();
                                    Vector3 *getPosition();
                                    Vector3 *getRotation();
                                    Color *getColor();
                                    qModel(string inName = "noname",string inType = "notype", Model *inModel = nullptr, ModelAnimation **inAnim = nullptr,bool inActive = false, int inFrame = 0, Vector3* inPosi = nullptr, Vector3* inRota = nullptr,  Color inColor = WHITE);
                            };

                            Camera camera;
                            Color backgroundColor;
                            qModel modelSlot[MAX::OBJ];
                            qProgram::qData::qSession::qRender::qScene::qModel *findGetModel(string inName);
                            void autoCreateModel(string inName,string inType, Model *inModel,  ModelAnimation **inAnim = nullptr,bool inActive = false,  Vector3* inPosi = nullptr, Vector3* inRota = nullptr, int inFrame = 0, Color inColor = WHITE);
                        };
                        class qScreen
                        {
                            Vector2 resolution=(Vector2){800,600};
                            bool resizable = true;
                            public:
                                RenderTexture renderTexture;
                                Vector2 getResolution();
                                float getMaxX();
                                float getMaxY();
                                void setResolution(int x,int y);
                                void setMaxX(float input);
                                void setMaxY(float input);
                        };
                        int frameRatio = 1;
                        int frame = 0;
                        qScreen screen;
                        qScene scene;
                        void renderCurrentScene();
                    };
                    public:
                        qRender render;
                };
                qGame game;
                qSession session;
                qFile file;
            };
            struct qKeyboard
            {
                const int key_id[106] = {0,32,39,44,45,46,47,48,49,50,51,52,53,54,55,56,57,59,61,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,96,256,257,258,259,260,261,262,263,264,265,266,267,268,269,280,281,282,283,284,290,291,292,293,294,295,296,297,298,299,300,301,340,341,342,343,344,345,346,347,348,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336};
                class qKey
                {
                    void (*keyFunc[3])(qProgram::qData* inData);
                    public:
                    bool active[3] = {false,false,false};
                    void setFunc(void (*inFunc)(qProgram::qData* inData),int KeyEvent);
                    void run(qProgram::qData* inData, int KeyEvent);
                };
                qKey key[106];
                void setKeyFunc(void (*inFunc)(qProgram::qData* inData),int KeyID,int KeyEvent);
            };
            void getKey();
            void setLoop(void (*inLoop)(qProgram::qData *inData));
            void run();
            
            qData data;
            qKeyboard keyboard;
            qProgram(int inWidth, int inHeight, string inTitle);
        private:
            void (*userLoop) (qProgram::qData *inData);
    };
}

using namespace mqq;

#endif
