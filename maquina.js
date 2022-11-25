//MAQUINA
//AKA MQEngine

const r = require('raylib');
const fs = require('fs')

//-----------------------------------
//COLORS
//-----------------------------------

function RGBA(rr,gg,bb,aa)
{
    return ({r:rr,g:gg,b:bb,a:aa});
}

function Vector3(xx,yy,zz)
{
    return({x:xx,y:yy,z:zz});
}

function Vector3Zero()
{
    return({x:0,y:0,z:0});
}

function Vector2(xx,yy)
{
    return({x:xx,y:yy});
}

function Vector2Zero()
{
    return({x:0,y:0});
}

const COR_VERMELHO = RGBA(235, 64, 52,255);
const COR_SELECIONADO   = RGBA(202,137,109,255);
const COR_SELECIONADO2 = RGBA(145, 39, 32,255);
const COR_PRETO = RGBA(31, 9, 7,255);
const COR_VAZIO   = RGBA(55,55,55,255);
const COR_BRANCO   = RGBA(250,239,229,255);
const COR_CINZA   = RGBA(115,105,97,255);
const COR_LARANJA   = RGBA(202,137,109,255);

const COR_PELE0 = RGBA(240, 199, 156,255);
const COR_ROUPA0 = RGBA(103, 122, 137,255);
const COR_ROUPA1 = RGBA(110, 125, 103,255);

const MAXANIM = 1;

//-----------------------------------
//BASICS
//-----------------------------------

//A QUICK IMPLEMENTATIONS TO DEFAULT ARGS
function DefaultsTo(target,def)
{
	if(typeof target == 'undefined')
		return def;
	else 
		return target;
}
var defsto = DefaultsTo;

//-----------------------------------
//CALCULATE
//-----------------------------------

function DifferenceFloat(a, b)
{
    return ((a+b+Math.abs(a-b))/2);
}

function DifferenceVec3(vec1, vec2)
{
    return(Vector3(DifferenceFloat(vec1.x, vec2.x),DifferenceFloat(vec1.y, vec2.y),DifferenceFloat(vec1.z, vec2.z)));
}

//-----------------------------------
//FONT&STRING
//-----------------------------------

function FontStart(FontLoc, FontSize)
{
    var fileize = 0;
    var fileData = r.LoadFileData(FontLoc, fileize);
    // Default font generation from TTF font
    var fontDefault = {};
    fontDefault.baseSize = FontSize;
    fontDefault.glyphCount = 95;

    // Loading font data from memory data
    // Parameters > font size: FontSize, no glyphs array provided (0), glyphs count: 95 (autogenerate chars array)
    fontDefault.glyphs = r.LoadFontData(fileData, fileize, FontSize, 0, 95, r.FONT_DEFAULT);

    fontDefault.glyphs = r.LoadFontData(fileData, fileize, FontSize, 0, 95, r.FONT_DEFAULT);
    // Parameters > glyphs count: 95, font size: FontSize, glyphs padding in image: 4 px, pack method: 0 (default)
    var atlas = r.GenImageFontAtlas(fontDefault.glyphs, fontDefault.recs, 95, FontSize, 14, 0);
    fontDefault.texture = r.LoadTextureFromImage(atlas);
    r.UnloadImage(atlas);

    // SDF font generation from TTF font
    let fontSDF = {  };
    fontSDF.baseSize = FontSize;
    fontSDF.glyphCount = 95;
    // Parameters > font size: FontSize, no glyphs array provided (0), glyphs count: 0 (defaults to 95)
    fontSDF.glyphs = r.LoadFontData(fileData, fileize, FontSize, 0, 0, FONT_SDF);
    // Parameters > glyphs count: 95, font size: FontSize, glyphs padding in image: 0 px, pack method: 1 (Skyline algorythm)
    atlas = r.GenImageFontAtlas(fontSDF.glyphs, fontSDF.recs, 95, FontSize, 0, 1);
    fontSDF.texture = r.LoadTextureFromImage(atlas);
    r.UnloadImage(atlas);

    r.UnloadFileData(fileData);      // Free memory from loaded file

    // Load SDF required shader (we use default vertex shader)
    //Shader shader = LoadShader(0, TextFormat("data/shaders/sdf.fs", 330));
    r.SetTextureFilter(fontSDF.texture, r.TEXTURE_FILTER_POINT);    // Required for SDF font

    return (fontDefault);
}

//-----------------------------------
//CAMERA
//-----------------------------------

function CameraStart()
{
    let camera = {};
    camera.position = {x:10.0, y:10.0, z:10.0};
    camera.target = {x:0.0, y:10.0, z:0.0};
    camera.up = {x:0.0, y:1.0, z:0.0};
    camera.fovy = 30.0;
    camera.projection = r.CAMERA_PERSPECTIVE;
    r.SetCameraMode(camera, r.CAMERA_CUSTOM);
    return (camera);
}

//-----------------------------------
//DATA_FILE
//-----------------------------------

const _Data = 
{
    file:
    {
        model:[],
        hitbox:[],
        eventbox:[],
        font:[],
        text:[],
        lang:[],
        music:[],
        sound:[],
        loadModel:function(name, link, isHitbox)
        {
            var LocalIndex;
            this.model[name] = {};
            
            //this.loading.push("(model) " + name);
            if(!link.includes('.iqm') && !link.includes('.obj') && !link.includes('.glb') && !link.includes('.gltf'))
            {
                const files = fs.readdirSync(link);
                this.model[name].model = [];
                if(files[0].includes('.glb') || files[0].includes('.obj') || files[0].includes('.iqm') || files[0].includes('.gltf'))
                    for(let i = 0;i<files.length;i++)
                        if(fs.existsSync(link+files[i]))
                            this.model[name].model.push(r.LoadModel(link+files[i]));
                this.model[name].name = name;
            }
            else
            {
                this.model[name].model = r.LoadModel(link);
                this.model[name].name = name;
            }
            if(isHitbox === true)
            {
                this.hitbox[name] = {};
                this.hitbox[name].hitbox = r.GetModelBoundingBox(this.model[name].model);
                this.hitbox.push(this.hitbox[name]);
            }
            this.model.push(this.model[name]);
        }
    },
    session:
    {
        frame:0,
        resizableWindow:true,
        exit:false,
        rendertexture:{},
    },
    scene:
    {
        background:RGBA(0,0,0,0),
        camera:CameraStart(),
        event:[],
        map:{},
        creature:[],
		render:
		{	
			file:{},//is set then, in the 
			addCreature:function(crt,specime)
			{
				specime = defsto(specime,'human');
				console.log(specime)
				if(specime === 'human')
					this.addModel(crt.name,'player-walk',0,r.BLUE,crt.position,crt.rotation,Vector3(1,1,1));
			},
			addModel:function(name,modelid,frame,color,position,rotation,scale)
			{
				position = DefaultsTo(position,{x:0,y:0,z:0});
				rotation = defsto(rotation,Vector3(0,0,0));//Same as DefaultsTo
				scale = defsto(scale,Vector3(1,1,1));
				frame = defsto(frame,0);
				color = defsto(color,RGBA(0,0,0,0));
				let temp = {name:name,id:modelid,position:position,rotation:rotation,scale:scale,frame:frame,color:color};
				this.model[name] = temp;
				
				this.model.push(temp);
			},
			addHitbox:function(name,hitboxid,position,rotation,frame,color)
			{
				position = DefaultsTo(position,{x:0,y:0,z:0});
				rotation = defsto(rotation,Vector3(0,0,0));//Same as DefaultsTo
				frame = defsto(frame,0);
				color = defsto(color,RGBA(0,0,0,0));
				let temp = {name:name,id:hitboxid,position:position,rotation:rotation,frame:frame,color:color};//color stands for wireframe color
				this.hitbox[name] = temp;
				this.hitbox.push(temp);
			},
			addText:function(name,fontid,msg,position,scale,color)
			{
				position = DefaultsTo(position,{x:0,y:0});
				msg = defsto(msg,"empty");
				scale = defsto(scale,1);
				color = defsto(color,RGBA(0,0,0,0));
				let temp = {name:name,id:fontid,msg:msg,position:position,rotation:rotation,frame:frame,color:color};//color stands for wireframe color
				this.text[name] = temp;
				this.text.push(temp);
			},
			addImage:function(name,imageid,msg,position,scale,color)
			{
				position = DefaultsTo(position,{x:0,y:0});
				msg = defsto(msg,"empty");
				color = defsto(color,RGBA(0,0,0,0));
				let temp = {name:name,id:imageid,position:position,rotation:rotation,frame:frame,color:color};//color stands for wireframe color
				this.image[name] = temp;
				this.image.push(temp);
			},
			model:[],
			hitbox:[],
			text:[],
			image:[]
		}
    },
}

class Data	
{
	constructor()
	{
		this.session = {..._Data.session};
		this.scene = {..._Data.scene};
		this.file = {..._Data.file};
		this.config = require("./config.json");
		this.scene.render.file = this.file;
	}
}

//-----------------------------------
//STARTUP
//-----------------------------------

function Start(data)
{
	if(data.config.resizebleWindow == true)
		r.SetConfigFlags(r.FLAG_WINDOW_RESIZABLE);
	//r.InitAudioDevice();
	r.InitWindow(data.config.screen.x, data.config.screen.y, data.config.title);
	r.SetTargetFPS(data.config.framerate);
	r.SetExitKey(r.KEY_END);
	//load.c
	//MQLoadAll(data);
	//SESSION_RENDER
	data.config.upscale = data.config.upscale;
	data.session.rendertexture = r.LoadRenderTexture(data.config.screen.x/data.config.upscale, data.config.screen.y/data.config.upscale);
	data.scene.background = {r:115, g:105, b:97, a:255};
	data.scene.creature = [];
	data.session.frame = 0;
	//FONTS
	//data.file.font.push(FontStart("data/font/acentos/KyrillaSansSerif-Bold.ttf", 16));
	//data.file.font.push(FontStart("data/font/Mockery.ttf", 48));
	//data.file.font.push(FontStart("data/font/Mockery.ttf", 24));
	//MUSIC
	data.file.music.push(r.LoadMusicStream("data/audio/music/maintheme_by_kayoa.mp3"));
    
	//CURRENT_LEVEL
	data.scene.map.currentLevel = 0;
};

module.exports = {Data,Start,CameraStart,FontStart,DefaultsTo,defsto};