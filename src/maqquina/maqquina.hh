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

struct PROGRAM
{
    struct DATA
    {
        struct LFILE
        {
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
                //public:
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
                string name = "ninguem";
                Vector3 position;
                Vector3 rotation;
                public:
                    void setName(string newName);
                    void setPosition(Vector3 inPosition);
                    void setRotation(Vector3 inRotation);
                    string getName();
                    Vector3 getPosition();
                    Vector3 getRotation();
            };
            class MAP
            {
                string name = "nenhum";
                Model *model = nullptr;
                public:
                    void setName(string newName);
                    void setModel(Model *modelPtr);
                    string getName();
                    Model* getModel();
            };
            public:
                PLAYER player[MAX_OBJ];
        };
        public:
            GAME game;
            SESSION session;
            LFILE file;
    };
    void start(int wid,int hei,string title);
    DATA data;
};

#endif