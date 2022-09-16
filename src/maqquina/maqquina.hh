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

struct qData
{
	//----------------------------------------------------------------------------------
	// file
	// file
	// file
	// file
	//----------------------------------------------------------------------------------

	struct qFile
	{
		//----------------------------------------------------------------------------------
		// hitbox
		// hitbox
		// hitbox
		//----------------------------------------------------------------------------------
	    class qHitbox
	    {
	        string name = "noname";
	        string type = "notype";
	        BoundingBox hitbox;
	        bool active = false;
	        public:
	            void setName(string newName);
	            void setType(string newtype);
	            void setActive(bool inActive = true);
	            bool getActive();
	            string getName();
	            string getType();
	            BoundingBox *getHitbox();
	            void loadFromFile(string path);
	            void loadFromModel(string path);
	            void create(string inName = "noname", string inType= "notype",BoundingBox inHitbox = (BoundingBox){{0,0,0},{0,0,0}});
	    };
	    //----------------------------------------------------------------------------------
		// model
		// model
		// model
		//----------------------------------------------------------------------------------
	    class qModel
	    {
	        string name = "noname";
	        string type = "notype";
	        Model model;
	        ModelAnimation *anim;
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
	    qFile::qModel* getModel(int index);
	    qFile::qModel* findGetModel(string inName);
	    int findModel(string inName);
	    void autoLoadModel(string inName, string inType, string path, bool inAnimated = false);
	    void autoCreateHitbox(string inName, string inType,BoundingBox inHitbox);
	    void autoCreateHitboxFromModel(string inName, string inType, string path, bool inActive = true);
	};
	//----------------------------------------------------------------------------------
	// qHuman
	// qHuman
	// qHuman
	// qHuman
	//----------------------------------------------------------------------------------	

	struct qMundo
	{
		//----------------------------------------------------------------------------------
		// qCreature
		// qCreature
		// qCreature
		//----------------------------------------------------------------------------------
		struct qCreature
		{
			//----------------------------------------------------------------------------------
			// qBody
			// qBody
			//----------------------------------------------------------------------------------
			struct qBody
			{
				//----------------------------------------------------------------------------------
				// qPart
				//----------------------------------------------------------------------------------
				class qPart
			   	{
					public:
						struct iStats//innerStats
				   		{
				   			string status = "saudavel";
				           	float hp = 100;
							BoundingBox *hitbox = nullptr;
				   		};
						iStats stats;
			   	};
			   	//----------------------------------------------------------------------------------
				// qHuman
				//----------------------------------------------------------------------------------	
			   	struct qHuman
			    {
			        struct qHead
			        {
			            BoundingBox *hitbox = nullptr;
			            struct qFace
			            {
			                qPart eye[2];
			                qPart nose;
			                qPart qEyebrow;
			                qPart qHair;
			                qPart qBeard;
		                    qPart::iStats stats;
			            };
			            qFace face;
			        };
			        struct qHand
			        {
			            struct qFinger
			            {
		            		qPart::iStats stats;
			                qPart nail;
			            };
			            qFinger finger[5];
			            qPart::iStats stats;
			        };
			        qHead head;
		   	        qPart neck;
		   	        qPart chest;
		   	        qPart belly;
		   	        qPart shoulder[2];
		   	        qPart arm[2];
			        qHand hand[2];
			        qPart qUpperLeg[2];
					qPart leg[2];
			    };
			};
			//----------------------------------------------------------------------------------
			// Creatures
			// Creatures
			//----------------------------------------------------------------------------------
			class qHuman
			{
			    qBody::qHuman body;
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
		};
		//----------------------------------------------------------------------------------
		// Creatures
		// Creatures
		// Creatures
		//----------------------------------------------------------------------------------
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
		
		qMap map;
		qCreature::qHuman player[MAX::OBJ];
	};
	

	//----------------------------------------------------------------------------------
	// session
	// session
	// session
	// session
	//----------------------------------------------------------------------------------

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
	                ModelAnimation *anim;
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
				qFile::qHitbox *hitbox[MAX::OBJ] = {nullptr};
	            Camera camera;
	            Color backgroundColor;
	            qModel modelSlot[MAX::OBJ];
	            qModel *findGetModel(string inName);
	            void autoCreateModel(string inName,string inType, Model *inModel,  ModelAnimation **inAnim = 0,bool inActive = false,  Vector3* inPosi = nullptr, Vector3* inRota = nullptr, int inFrame = 0, Color inColor = WHITE);
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
    qMundo world;
    qSession session;
    qFile file;
};

	
namespace qMath
{
    float round360(float input);
};
namespace qTools
{
	namespace qMesh
	{
		Mesh rotateMeshFromAnim(Model model, ModelAnimation anim, int frame);
	};
};


class qProgram
{
    public:
        struct qKeyboard
        {
            const int key_id[106] = {0,32,39,44,45,46,47,48,49,50,51,52,53,54,55,56,57,59,61,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,96,256,257,258,259,260,261,262,263,264,265,266,267,268,269,280,281,282,283,284,290,291,292,293,294,295,296,297,298,299,300,301,340,341,342,343,344,345,346,347,348,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336};
            class qKey
            {
                void (*keyFunc[3])(qData* inData);
                public:
                bool active[3] = {false,false,false};
                void setFunc(void (*inFunc)(qData* inData),int KeyEvent);
                void run(qData* inData, int KeyEvent);
            };
            qKey key[106];
            void setKeyFunc(void (*inFunc)(qData* inData),int KeyID,int KeyEvent);
        };
        void getKey();
        void setLoop(void (*inLoop)(qData *inData));
        void run();
        
        qData data;
        qKeyboard keyboard;
        qProgram(int inWidth, int inHeight, string inTitle);
    private:
        void (*userLoop) (qData *inData);
};

#endif
