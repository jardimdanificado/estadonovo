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

#define MAX_OBJ 64
#define MAX_ANIM 2;

//TYPES
enum
{
    MAP,
    PLAYER,
    ITEM
};

enum
{
    KDOWN,KRELEASED,KPRESSED
};
class PROGRAM
{
    public:
        struct DATA
        {
            struct LFILE
            {
                class HITBOX
                {
                    string name = "noname";
                    string type = "notype";
                    BoundingBox hitbox;
                    public:
                        void setName(string newName);
                        void setType(string newtype);
                        string getName();
                        string getType();
                        BoundingBox *getHitbox();
                        void loadFromFile(string path);
                        void loadFromModel(Model*inModel);
                        void create(string inName = "noname", string inType= "notype",BoundingBox inHitbox = (BoundingBox){{0,0,0},{0,0,0}});
                };
                class MODEL
                {
                    string name = "noname";
                    string type = "notype";
                    Model model={0};
                    ModelAnimation* anim;
                    bool animated = false;
                    public:
                        void setName(string newName);
                        void setType(string newtype);
                        string getName();
                        string getType();
                        Model *getModel();
                        void loadModel(string path);
                        void loadAnim(string path);
                        void unloadAnim();
                        void unloadModel();
                };
                MODEL model[MAX_OBJ];
                HITBOX hitbox[MAX_OBJ];
                PROGRAM::DATA::LFILE::MODEL* getModel(int index);
                PROGRAM::DATA::LFILE::MODEL* findGetModel(string inName);
                int findModel(string inName);
                void autoLoadModel(string path, string inType, string inName, bool inAnimated = false);
                void autoCreateHitbox(string inName, string inType,BoundingBox inHitbox);
            };
            struct GAME
            {
                class PLAYER
                {
                    struct BODY
                    {
                        struct HEAD
                        {
                            BoundingBox *hitbox = nullptr;
                            struct FACE
                            {
                                struct EYE
                                {
                                    string status = "saudavel";
                                    float hp = 100;
                                };
                                struct MOUTH
                                {
                                    struct TEETH
                                    {
                                        string status = "saudavel";
                                        float hp = 100;
                                    };
                                    TEETH teeth[32];
                                    string status = "saudavel";
                                    float hp = 100;
                                };
                                struct NOSE
                                {
                                    string status = "saudavel";
                                    float hp = 100;
                                };
                                struct EYEBROW
                                {
                                    string status = "natural";
                                    float hp = 100;
                                };
                                struct HAIR
                                {
                                    string status = "careca";
                                    float hp = 0;
                                };
                                struct BEARD
                                {
                                    string status = "careca";
                                    float hp = 0;
                                };
                                EYE eye[2];
                                MOUTH mouth;
                                NOSE nose;
                                EYEBROW eyebrow[2];
                                HAIR hair;
                                BEARD beard;
                            };
                        };
                        struct NECK
                        {
                            BoundingBox *hitbox = nullptr;
                            string status = "saudavel";
                            float hp = 100;
                        };
                        struct CHEST
                        {
                            BoundingBox *hitbox = nullptr;
                            string status = "saudavel";
                            float hp = 100;
                        };
                        struct BELLY
                        {
                            BoundingBox *hitbox = nullptr;
                            string status = "saudavel";
                            float hp = 100;
                        };
                        struct SHOULDER
                        {
                            BoundingBox *hitbox = nullptr;
                            string status = "saudavel";
                            float hp = 100;
                        };
                        struct ARM
                        {
                            BoundingBox *hitbox = nullptr;
                            string status = "saudavel";
                            float hp = 100;
                        };
                        struct HAND
                        {
                            struct FINGER
                            {
                                struct NAIL
                                {
                                    string status = "saudavel";
                                    float hp = 100;
                                };
                                NAIL nail;
                            };
                            FINGER finger[5];
                            BoundingBox *hitbox = nullptr;
                            string status = "saudavel";
                            float hp = 100;
                        };
                        struct UPPERLEG
                        {
                            BoundingBox *hitbox = nullptr;
                            string status = "saudavel";
                            float hp = 100;
                        };
                        struct LEG
                        {
                            struct FEET
                            {
                                BoundingBox *hitbox = nullptr;
                                string status = "saudavel";
                                float hp = 100;
                            };
                            FEET feet;
                            BoundingBox *hitbox = nullptr;
                            string status = "saudavel";
                            float hp = 100;
                        };
                        HEAD head;
                        NECK neck;
                        CHEST chest;
                        SHOULDER shoulder[2];
                        ARM arm[2];
                        HAND hand[2];
                        UPPERLEG upperleg[2];
                        LEG leg[2];
                    };
                    BODY body;
                    string name = "ninguem";
                    Vector3 position = {0,0,0};
                    Vector3 rotation = {0,0,0};
                    public:
                        void setName(string newName);
                        void setPosition(Vector3 inPosition);
                        void setRotation(Vector3 inRotation);
                        string getName();
                        Vector3 *getPosition();
                        Vector3 *getRotation();
                };
                class MAP
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
                    PLAYER player[MAX_OBJ];
                    MAP map;
            };
            struct SESSION
            {
                struct RENDER
                {
                    struct SCENE
                    {
                        class MODEL
                        {
                            string name = "noname";
                            string type = "notype";
                            int frame = 0;
                            bool active = false;
                            Model *model = nullptr;
                            Vector3 *position = nullptr;
                            Vector3 *rotation = nullptr;
                            Color color = WHITE;
                            public:
                                void setName(string newName);
                                void setType(string newType);
                                void setActive(bool newActive);
                                void setModel(Model *inModel);
                                void setColor(Color inColor);
                                void setPosition(Vector3 *inPosi);
                                void setRotation(Vector3 *inRota);
                                void create(string inName = "noname",string inType = "notype", Model *inModel = nullptr, int inFrame = 0, Vector3* inPosi = nullptr, Vector3* inRota = nullptr,  Color inColor = WHITE, bool inActive = false);
                                void reset();
                                string getName();
                                string getType();
                                bool getActive();
                                Model *getModel();
                                Vector3 *getPosition();
                                Vector3 *getRotation();
                                Color *getColor();
                        };
                        Camera camera;
                        Color backgroundColor;
                        MODEL modelSlot[MAX_OBJ];
                        PROGRAM::DATA::SESSION::RENDER::SCENE::MODEL *findGetModel(string inName);
                        void autoCreateModel(string inName,string inType, Model *inModel, Vector3* inPosi, Vector3* inRota,  bool inActive, int inFrame = 0, Color inColor = WHITE);
                    };
                    class SCREEN
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
                    SCREEN screen;
                    SCENE scene;
                    void renderCurrentScene();
                };
                public:
                    RENDER render;
            };
            GAME game;
            SESSION session;
            LFILE file;
        };
        struct KEYBOARD
        {
            const int key_id[106] = {0,32,39,44,45,46,47,48,49,50,51,52,53,54,55,56,57,59,61,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,96,256,257,258,259,260,261,262,263,264,265,266,267,268,269,280,281,282,283,284,290,291,292,293,294,295,296,297,298,299,300,301,340,341,342,343,344,345,346,347,348,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336};
            class KEY
            {
                void (*keyFunc[3])();
                public:
                bool active[3] = {false,false,false};
                void setFunc(void (*inFunc)(),int keyCondition);
                void run(int keyCondition);
            };
            KEY key[106];
            void setKeyFunc(void (*inFunc)(),int KeyID,int keyCondition);
            void run();
        };
        void setLoop(void (*inLoop)(PROGRAM::DATA *inData));
        void run();
        void start(int wid,int hei,string title);
        DATA data;
        KEYBOARD keyboard;
    private:
        void (*userLoop) (PROGRAM::DATA *inData);
        void loadDefaultModels();
};

#endif