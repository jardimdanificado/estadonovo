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
                    public:
                        void setName(string newName);
                        void setType(string newtype);
                        string getName();
                        string getType();
                        Model *getModel();
                        void load(string path);
                        void unload();
                };
                MODEL model[MAX_OBJ];
                HITBOX hitbox[MAX_OBJ];
                PROGRAM::DATA::LFILE::MODEL* getModel(int index);
                PROGRAM::DATA::LFILE::MODEL* findGetModel(string name);
                int findModel(string name);
                void loadModel(string path, string name, string type);
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
                                string getName();
                                string getType();
                                bool getActive();
                                Model *getModel();
                                Vector3 *getPosition();
                                Vector3 *getRotation();
                                Color *getColor();
                                void create(string inName = "noname",string inType = "notype", Model *inModel = nullptr, int inFrame = 0, Vector3* inPosi = nullptr, Vector3* inRota = nullptr,  Color inColor = WHITE, bool inActive = false);
                                void reset();
                        };
                        Camera camera;
                        Color backgroundColor;
                        MODEL modelSlot[MAX_OBJ];
                        PROGRAM::DATA::SESSION::RENDER::SCENE::MODEL *findGetModel(string inName);
                        void autoCreateModel(string inName = "noname",string inType = "notype", Model *inModel = nullptr, int inFrame = 0, Vector3* inPosi = nullptr, Vector3* inRota = nullptr,  Color inColor = WHITE, bool inActive = false);
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
                    //razao
                    int frameRatio = 1;
                    int frame = 0;
                    SCREEN screen;
                    SCENE scene;
                    void renderCurrentScene();
                };
                public:
                    RENDER render;
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
                    Vector3 position;
                    Vector3 rotation;
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
                    Vector3 position = {0,0,0};
                    Vector3 rotation = {0,0,0};
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
            GAME game;
            SESSION session;
            LFILE file;
        };
        void setLoop(void (*inLoop)());
        void run();
        void start(int wid,int hei,string title);
        DATA data;
    private:
        void (*userLoop) ();
};

#endif