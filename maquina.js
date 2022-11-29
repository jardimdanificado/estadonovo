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

function BoundingBox(min,max)
{
    return({min:{x:min.x,y:min.y,z:min.z},max:{x:max.x,y:max.y,z:max.z}});
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

function LimitItTo(value,min,max)
{
	if(value > max)
	{
		while(value > max)
			value -= max;
	}
	if(value < min)
	{
		while(value < min)
			value += max;
	}
	return value;
}
var limito = LimitItTo;

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
//3D && CAMERA
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

function Move3D(position, rotation, speed)
{
    //z+ frente
    //x+ esquerda
    let  valorZ, valorX;
    let giro = Math.floor(rotation / 90.0);
    let resto = rotation - (90.0 * giro);
    let restodoresto = 90.0 - resto;
    valorZ = speed - (resto * (speed / 90.0));
    valorX = (speed - (restodoresto * (speed / 90)));
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
    return position;
}

function UpdateGravityRay(targetobj)
{
    targetobj.ray.gravity.position = Vector3(targetobj.position.x,(targetobj.position.y+0.00001)-(0.005*(targetobj.fallTime)),targetobj.position.z);
    targetobj.ray.gravity.direction = Vector3(0,1,0);
}

function UpdateHorizontalRay(ref,backwards)
{
    //z+ frente
    //x+ esquerda
    let valorZ;
    let valorX;
    if(ref.rotation.y<=90.0)
    {
        if(backwards)
        {
            valorZ = -1.0+((1.0/90.0)*ref.rotation.y);
            valorX = 0.0-(1.0/90.0)*ref.rotation.y;
        }
        else
        {
            valorZ = 1.0-((1.0/90.0)*ref.rotation.y);
            valorX = 0.0+(1.0/90.0)*ref.rotation.y;
        }
    }
    else if(ref.rotation.y<=180)
    {
        if(backwards)
        {
            valorZ = 0.0+((1.0/90.0)*(ref.rotation.y-90.0));
            valorX = -1.0+((1.0/90.0)*(ref.rotation.y-90.0));
        }
        else
        {
            valorZ = 0.0-((1.0/90.0)*(ref.rotation.y-90.0));
            valorX = 1.0-((1.0/90.0)*(ref.rotation.y-90.0));
        }
    }
    else if(ref.rotation.y<=270)
    {
        if(backwards)
        {
            valorZ = 1.0-((1.0/90.0)*(ref.rotation.y-180.0));
            valorX = 0.0+((1.0/90.0)*(ref.rotation.y-180.0));
        }
        else
        {
            valorZ = -1.0+((1.0/90.0)*(ref.rotation.y-180.0));
            valorX = 0.0-((1.0/90.0)*(ref.rotation.y-180.0));
        }
    }
    else 
    {
        if(backwards)
        {
            valorZ = 0.0-((1.0/90.0)*(ref.rotation.y-270.0));
            valorX = 1.0-((1.0/90.0)*(ref.rotation.y-270.0));
        }
        else
        {
            valorZ = 0.0+((1.0/90.0)*(ref.rotation.y-270.0));
            valorX = -1.0+((1.0/90.0)*(ref.rotation.y-270.0));
        }
    }
    ref.ray.horizontal.position = Vector3(ref.position.x,ref.position.y+0.7,ref.position.z);
   	ref.ray.horizontal.direction = Vector3(valorX,0,valorZ);
}

function Gravity(targetobj, gravidade)
{
    return((targetobj.position.y) - gravidade*((targetobj.fallTime*(targetobj.fallTime/10)))/60);
}

function Gravit(data, targetobj)
{
	UpdateGravityRay(targetobj);
	var gravityraiocolisao = {hit:false};
    for(let i=0;i<data.scene.render.hitbox.length;i++)
    {
		if(data.scene.render.hitbox[i].active == true)
		{
			gravityraiocolisao = r.GetRayCollisionBox(targetobj.ray.gravity,data.scene.render.hitbox[i].hitbox);
			if(gravityraiocolisao.hit == true)
				break;
			gravityraiocolisao.hit = false;
		}
    }
	
    if(gravityraiocolisao.hit == false)
    {
        targetobj.position.y = (Gravity(targetobj, 0.1));
        targetobj.fallTime++;
    }
    else
    {
        if(gravityraiocolisao.distance<0.7)
        {
            targetobj.position.y = gravityraiocolisao.point.y;
            targetobj.fallTime = 0;
        }
    }
}

function PlayerCollider(data,ref, backwards)
{
    var directionraiocolisao = {hit:false};
    UpdateHorizontalRay(ref,backwards);
    for(let i=0;i<data.scene.render.hitbox.length;i++)
		if(data.scene.render.hitbox[i].active == true)
		{
			directionraiocolisao = r.GetRayCollisionBox(ref.ray.horizontal,data.scene.render.hitbox[i].hitbox);
			if(directionraiocolisao.hit == true)
			{
				break;
			}
			directionraiocolisao.hit = false;
		}
    if(directionraiocolisao.hit == true)
    {
        if(directionraiocolisao.distance<0.5)
        {
            return true;
        }
        else
        {
            let caixa = {max:{...ref.position},min:{...ref.position}};
            caixa.max.x += 0.2;
            caixa.max.y += 1.2;
            caixa.max.z += 0.2;
            caixa.min.x += -0.2;
            caixa.min.y += 0.8;
            caixa.min.z += -0.2;
            if(backwards)
            {
                Move3D(caixa.max,ref.rotation.y,-0.1);
                Move3D(caixa.min,ref.rotation.y,-0.1);
            }
            else
            {
                Move3D(caixa.max,ref.rotation.y,0.1);
                Move3D(caixa.min,ref.rotation.y,0.1);
            }
            for(let i = 0;i<data.scene.render.hitbox.length;i++)
				if(data.scene.render.hitbox[i].active == true)
					if(r.CheckCollisionBoxes(caixa,data.scene.render.hitbox[i].hitbox)==true)
					{
						return true;
					}
        }
    }
    return false;
}

//-----------------------------------
//MENU
//-----------------------------------

function Menu(input)
{
	/*
 		{
   			fs.writeFileSync('/tmp/test-sync', 'Hey there!');
		}
	*/
}

//-----------------------------------
//SAVE
//-----------------------------------
function Save(data)
{
	fs.writeFileSync('./data/save/save.json', JSON.stringify(data.scene));
}

function Load(data,link)
{
	let tempLoad = require("./data/save/save.json")
	data.scene = Object.assign(data.scene, tempLoad);
	data.scene.render.file = data.file;
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
				files.sort((a,b)=>parseInt(a)-parseInt(b));
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
				this.hitbox[name].name = name;
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
			file:{},//is set then, in the constructor
			addCreature:function(crt,specime)
			{
				specime = defsto(specime,'human');
				if(specime === 'human')
					this.addModel(crt.name,'player-idle',0,RGBA(153,100,0,255),crt.position,crt.rotation);
			},
			addModel:function(name,modelid,frame,color,position,rotation,scale,visible,progression)
			{
				position = DefaultsTo(position,{x:0,y:0,z:0});
				rotation = defsto(rotation,Vector3(0,0,0));//Same as DefaultsTo
				scale = defsto(scale,Vector3(1,1,1));
				frame = defsto(frame,0);
				color = defsto(color,RGBA(255,255,255,255));
				visible = defsto(visible,true);
				ray = 
				{
					gravity:{position:Vector3(0,0,0), direction: {x:0,y:1,z:0}},
					horizontal:{position:Vector3(0,0,0), direction: {x:0,y:0,z:0}}
				};
				fallTime = 0;
				if(this.file.model[modelid].model[0])
					progression = defsto(progression,1);
				else
					progression = defsto(progression,0);
				
				let temp = {name:name,id:modelid,position:position,rotation:rotation,scale:scale,frame:frame,color:color,visible:visible,progression:progression,ray:ray,fallTime:0};
				this.model[name] = temp;
				this.model.push(temp);
			},
			addHitbox:function(name,hitbox,position,rotation,frame,color,visible)
			{
				position = DefaultsTo(position,{x:0,y:0,z:0});
				rotation = defsto(rotation,Vector3(0,0,0));//Same as DefaultsTo
				frame = defsto(frame,0);
				color = defsto(color,RGBA(0,0,0,0));
				visible = defsto(visible,true);
				active = true;
				let temp = {name:name,hitbox:hitbox,position:position,rotation:rotation,frame:frame,color:color,active:active,visible:visible};//color stands for wireframe color
				this.hitbox[name] = temp;
				this.hitbox.push(temp);
			},
			addText:function(name,fontid,msg,position,scale,color,visible)
			{
				position = DefaultsTo(position,{x:0,y:0});
				msg = defsto(msg,"empty");
				scale = defsto(scale,1);
				color = defsto(color,RGBA(0,0,0,0));
				visible = defsto(visible,true);
				let temp = {name:name,id:fontid,msg:msg,position:position,rotation:rotation,frame:frame,color:color,visible:visible};//color stands for wireframe color
				this.text[name] = temp;
				this.text.push(temp);
			},
			addImage:function(name,imageid,msg,position,scale,color,visible)
			{
				position = DefaultsTo(position,{x:0,y:0});
				msg = defsto(msg,"empty");
				color = defsto(color,RGBA(0,0,0,0));
				visible = defsto(visible,true);
				let temp = {name:name,id:imageid,position:position,rotation:rotation,frame:frame,color:color,visible:visible};//color stands for wireframe color
				this.image[name] = temp;
				this.image.push(temp);
			},
			model:[],
			hitbox:[],
			text:[],
			image:[]
		}
    },
	keyboard:
	{
		key:[],
		set:function(id,type,infunc,args)
		{
			if(typeof this.key[id] == 'undefined')
			{
				id += "k";
				this.key[id] = [];
				this.key[id] = {id:id,pressed:{},down:{},released:{}};
				this.key[id][0] = (this.key[id].pressed);
				this.key[id][1] = (this.key[id].down);
				this.key[id][2] = (this.key[id].released);
				this.key.push(this.key[id]);
			}
			this.key[id][type].func = infunc;
			if(args)
			{
				this.key[id][type].args = args;
			}
		},
		run:function()
		{
			for(let i = 0; i< this.key.length; i++)
				for(let type = 0; type< 3; type++)
				{
					var isk;
					switch(type)
					{
						case 0:
						{
							isk = r.IsKeyPressed;
						}
						break;
						case 1:
						{
							isk = r.IsKeyDown;
						}
						break;
						case 2:
						{
							isk = r.IsKeyReleased;
						}
						break;
					}
					if(typeof this.key[i][type].func == "function")//existence check
						if(isk(parseInt(this.key[i].id)) == true)//check if key is pressed/down/released
						{	
							if(!this.key[i][type].args[0])
							{
								this.key[i][type].func();
							}
							else if(!this.key[i][type].args[1])
							{
								this.key[i][type].func(this.key[i][type].args[0]);
							}
							else if(!this.key[i][type].args[2])
							{
								this.key[i][type].func(this.key[i][type].args[0],this.key[i][type].args[1]);
							}
							else if(!this.key[i][type].args[3])
							{
								this.key[i][type].func(this.key[i][type].args[0],this.key[i][type].args[1],this.key[i][type].args[2]);
							}
							else if(!this.key[i][type].args[4])
							{
								this.key[i][type].func(this.key[i][type].args[0],this.key[i][type].args[1],this.key[i][type].args[2],this.key[i][type].args[3]);
							}
							else
							{
								this.key[i][type].func(this.key[i][type].args[0],this.key[i][type].args[1],this.key[i][type].args[2],this.key[i][type].args[3],this.key[i][type].args[4]);
							}
						}
				}
		}
	}
}

class Data	
{
	constructor()
	{
		this.session = {..._Data.session};
		if(fs.existsSync('./data/save/save.json'))
		{
			let temp = require('./data/save/save.json');
			this.scene = {..._Data.scene,temp}
		}
		else
			this.scene = {..._Data.scene};
		this.file = {..._Data.file};
		this.keyboard = {..._Data.keyboard};
		this.config = require("./config.json");
		this.scene.render.file = this.file;//just a link
		if(this.config.resizebleWindow == true)
			r.SetConfigFlags(r.FLAG_WINDOW_RESIZABLE);
		//r.InitAudioDevice();
		r.InitWindow(this.config.screen.x, this.config.screen.y, this.config.title);
		r.SetTargetFPS(this.config.framerate);
		r.SetExitKey(r.KEY_END);
		this.session.rendertexture = r.LoadRenderTexture(this.config.screen.x/this.config.upscale, this.config.screen.y/this.config.upscale);
		this.scene.background = {r:115, g:105, b:97, a:255};
		this.scene.creature = [];
		this.session.frame = 0;
		//CURRENT_LEVEL
		this.scene.map.currentLevel = 0;
	}
}

//-----------------------------------
//exports
//-----------------------------------

module.exports = {Data,CameraStart,Move3D,PlayerCollider,Gravit,Save,Load,DefaultsTo,defsto,LimitItTo,limito};