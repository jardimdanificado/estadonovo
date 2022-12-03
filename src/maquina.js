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
const COR_SELECIONADO = RGBA(202,137,109,255);
const COR_SELECIONADO2 = RGBA(145, 39, 32,255);
const COR_PRETO = RGBA(31, 9, 7,255);
const COR_VAZIO = RGBA(55,55,55,255);
const COR_BRANCO = RGBA(250,239,229,255);
const COR_CINZA = RGBA(115,105,97,255);
const COR_LARANJA = RGBA(202,137,109,255);

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

function RotateAroundPivot(point,center,angle)
{
	angle = (angle ) * (Math.PI/180); // Convert to radians
	var rotatedX = Math.cos(angle) * (point.x - center.x) - Math.sin(angle) * (point.z-center.z) + center.x;
	var rotatedZ = Math.sin(angle) * (point.x - center.x) + Math.cos(angle) * (point.z - center.z) + center.z;
	return Vector3(rotatedX,point.y,rotatedZ);
}

//-----------------------------------
//3D && CAMERA
//-----------------------------------

function CameraStart(fov)
{
	
    let camera = {};
    camera.position = {x:10.0, y:10.0, z:10.0};
    camera.target = {x:0.0, y:10.0, z:0.0};
    camera.up = {x:0.0, y:1.0, z:0.0};
	camera.fovy = defsto(camera.fovy,30);
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
    return((targetobj.position.y) - gravidade*((targetobj.fallTime*(targetobj.fallTime/10)))/30);
}

function Gravit(data, targetobj)
{
	UpdateGravityRay(targetobj);
	var gravityraiocolisao = {hit:false};
    for(let i=0;i<data.scene.hitbox.length;i++)
    {
		if(data.scene.hitbox[i].active == true)
		{
			gravityraiocolisao = r.GetRayCollisionBox(targetobj.ray.gravity,data.scene.hitbox[i].hitbox);
			if(gravityraiocolisao.hit == true)
				break;
			gravityraiocolisao.hit = false;
		}
    }
	
    if(gravityraiocolisao.hit == false)
    {
        targetobj.position.y = (Gravity(targetobj, 1));
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
    for(let i=0;i<data.scene.hitbox.length;i++)
		if(data.scene.hitbox[i].active == true)
		{
			directionraiocolisao = r.GetRayCollisionBox(ref.ray.horizontal,data.scene.hitbox[i].hitbox);
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
            for(let i = 0;i<data.scene.hitbox.length;i++)
				if(data.scene.hitbox[i].active == true)
					if(r.CheckCollisionBoxes(caixa,data.scene.hitbox[i].hitbox)==true)
					{
						return true;
					}
        }
    }
    return false;
}

//-----------------------------------
//RENDER && MENU
//-----------------------------------
function Render(data)
{
	data.session.frame++;
	r.BeginDrawing();
	r.BeginTextureMode(data.session.rendertexture);
	r.ClearBackground(data.scene.background);
	r.BeginMode3D(data.scene.camera);
	for(let i = 0; i< data.scene.render.model.length;i++)
	{
		if(data.scene.render.model[i].progression != 0)
		{
			if(data.session.frame % Math.floor(data.config.framerate/24) == 0)//setten up for 24fps
			{
				data.scene.render.model[i].frame += data.scene.render.model[i].progression;
			}
		}
		data.scene.render.model[i].frame = limito(data.scene.render.model[i].frame,0,data.file.model[data.scene.render.model[i].id].model.length-2);
		if(data.scene.render.model[i].visible == true)
		{
			if(typeof data.file.model[data.scene.render.model[i].id].model[0] != 'undefined')
				r.DrawModelEx(
					data.file.model[data.scene.render.model[i].id].model[data.scene.render.model[i].frame], 
					data.scene.render.model[i].position, 
					r.Vector3(0,1,0), 
					data.scene.render.model[i].rotation.y, 
					data.scene.render.model[i].scale, 
					data.scene.render.model[i].color
				);
			else
				r.DrawModelEx(
					data.file.model[data.scene.render.model[i].id].model, 
					data.scene.render.model[i].position,
					r.Vector3(0,1,0), 
					data.scene.render.model[i].rotation.y, 
					data.scene.render.model[i].scale, 
					data.scene.render.model[i].color
				);
		}
	}
	r.EndMode3D();
	r.EndTextureMode();
	r.DrawTexturePro(
		data.session.rendertexture.texture,
		{
			x:0,
			y:0,
			width:data.config.screen.x/data.config.pixelsize,
			height:(data.config.screen.y/data.config.pixelsize)*-1
		},
		{x:0,y:0,width:data.config.screen.x,height:data.config.screen.y},
		{x:0,y:0}
		,0,
		r.WHITE
	);
	for(let i = 0; i< data.scene.render.text.length;i++)
	{
		if(data.scene.render.text[i].visible == true)
		{
			r.DrawTextEx(
				data.file.font[0],
				data.scene.render.text[i].text,
				data.scene.render.text[i].position, 
				16, 
				0, 
				data.scene.render.text[i].color
			);
		}
	}
	for(let i = 0; i< data.scene.creature.length;i++)
	{
		if(typeof data.scene.render.model[data.scene.creature[i].name] != 'undefined')
		{
			let temp;
			let trm = data.scene.render.model[data.scene.creature[i].name];//TEMP RENDER MODEL
			if(typeof data.file.model[trm.id].model[0]!="undefined")
				temp = r.GetModelBoundingBox(data.file.model[trm.id].model[trm.frame]);
			else
				temp = r.GetModelBoundingBox(data.file.model[trm.id].model);
			temp.min = RotateAroundPivot(temp.min,Vector3(0,0,0),trm.rotation.y);
			temp.max = RotateAroundPivot(temp.max,Vector3(0,0,0),trm.rotation.y);
			temp = {x:Math.max(temp.min.x,temp.max.x),y:Math.max(temp.min.y,temp.max.y),z:Math.max(temp.min.z,temp.max.z)}
			temp = r.Vector3Add(Vector3(temp.x + temp.x/2,temp.y,temp.z + temp.z/2),trm.position);
			temp = r.GetWorldToScreen(temp, data.scene.camera);
			r.DrawTextEx(
				data.file.font[0],
				trm.name,
				Vector2(temp.x - (r.ImageTextEx(data.file.font[0], trm.name,16, 0, COR_PRETO).width),temp.y - 24), 
				16, 
				0, 
				data.scene.render.text[i].color
			);
		}
	}
	
	if(data.config.showfps == true)
		r.DrawFPS(0,0);
	r.EndDrawing();
}

function Menu(ref,data)
{
	/*
 		{
   			offload:false,
	  		currentOption:0,
	 		data:data,
   			options:
 			[
		   		{//exit the current menu(possibly go back to another menu, or go back to the game)
			  		text:"return",
	 				func:function(){this.offload = true;}, 
				},
	 			{//exit(to OS)
		  			text:"exit",
	 				func:function(){data.session.exit = true;this.offload = true;}, 
				},
	  		]
 		}
  	*/
	ref.offload = defsto(ref.offload,false);
	ref.offloadkey = defsto(ref.offloadkey,r.KEY_NULL);
	ref.currentOption = defsto(ref.currentOption,0);
	ref.logo = defsto(ref.logo,false);
	var locframe = 0;
	if(typeof data != 'undefined')
		ref.data = defsto(ref.data,data);
	
	if(typeof ref.data == 'undefined')
		return false;

	var locframe = 0;
	var logoimg = r.ImageTextEx(ref.data.file.font[1], ref.data.config.title,48, 0, COR_PRETO);
	var txtimg = [];
	var mouse = {};
	
	for(let i = 0; i< ref.length;i++)
		txtimg.push(r.ImageTextEx(ref.data.file.font[0], ref[i].text,16, 0, COR_PRETO));
	r.StopMusicStream(ref.data.file.music[0]);
	r.PlayMusicStream(ref.data.file.music[0]);
	while(ref.offload == false)
	{
		r.UpdateMusicStream(ref.data.file.music[0]);
		r.BeginDrawing();
		r.ClearBackground(COR_BRANCO);
		
		mouse = r.GetMousePosition();

		for(let i = 0;i<ref.length;i++)
			if(mouse.x>0&&
			   mouse.x<txtimg[i].width&&
			   mouse.y>16*i&&
			   mouse.y<16*i+txtimg[i].height)
			{
				ref.currentOption = i;
				break;
			}
		
		for(let i = 0;i<ref.length;i++)
			if(ref.currentOption != i)
				r.DrawTextEx(ref.data.file.font[0],ref[i].text, r.Vector2(0, 16*i), 16, 0, COR_PRETO);
			else
				r.DrawTextEx(ref.data.file.font[0],ref[i].text, r.Vector2(0, 16*i), 16, 0, COR_SELECIONADO2);

		if(ref.logo == true)
		{
			if(mouse.x>0&&
			   mouse.x<logoimg.width&&
			   mouse.y>ref.data.config.screen.y-64&&
			   mouse.y<ref.data.config.screen.y-64+logoimg.height)
				r.DrawTextEx(ref.data.file.font[1],ref.data.config.title, r.Vector2(0,ref.data.config.screen.y-64), 48, 0, COR_SELECIONADO2);
			else
				r.DrawTextEx(ref.data.file.font[1],ref.data.config.title, r.Vector2(0,ref.data.config.screen.y-64), 48, 0, COR_PRETO);
			
			if(locframe%331 == 0)
				r.DrawTextEx(ref.data.file.font[2],ref.data.config.subtitle, r.Vector2(0,ref.data.config.screen.y-24), 24, 0, COR_SELECIONADO);
			else
				r.DrawTextEx(ref.data.file.font[2],ref.data.config.subtitle, r.Vector2(0,ref.data.config.screen.y-24), 24, 0, COR_PRETO);
		}
		
		if(r.IsKeyPressed(r.KEY_ENTER)||
		   r.IsKeyPressed(r.KEY_E)||
		   (r.IsMouseButtonPressed(r.MOUSE_BUTTON_LEFT)&&
			mouse.x>0&&
			mouse.x<txtimg[ref.currentOption].width&&
			mouse.y>16*ref.currentOption&&
			mouse.y<16*ref.currentOption+txtimg[ref.currentOption].height))
		{	
			if(ref[ref.currentOption].args != 'undefined')
				ref[ref.currentOption].func(ref[ref.currentOption].args);
			else
				ref[ref.currentOption].func();
		}
		else if(r.IsKeyPressed(r.KEY_DOWN)||r.IsKeyPressed(r.KEY_S))
		{	
			if(ref.currentOption<ref.length)
				ref.currentOption++;
			else 
				ref.currentOption = 0;
		}
		else if(r.IsKeyPressed(r.KEY_UP)||r.IsKeyPressed(r.KEY_W))
		{
			if(ref.currentOption>0)
				ref.currentOption--;
			else 
				ref.currentOption = ref.length-1;
		}
		else if(locframe>0&&r.IsKeyPressed(ref.offloadkey))
		{
			ref.offload = true;
		}
		r.EndDrawing();
		locframe++;
	}
	ref.offload = false;
}

function CreateDynamicKeyboard()
{
	return {
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
		run:function(data)
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
								if(type == 1)
								{
									if(data.session.frame%(Math.floor(data.config.framerate/30.0))==0)
										this.key[i][type].func();
								}
								else
									this.key[i][type].func();
							}
							else if(!this.key[i][type].args[1])
							{
								if(type == 1)
								{
									if(data.session.frame%(Math.floor(data.config.framerate/30.0))==0)
										this.key[i][type].func(this.key[i][type].args[0]);
								}
								else
									this.key[i][type].func(this.key[i][type].args[0]);
							}
							else if(!this.key[i][type].args[2])
							{
								if(type == 1)
								{
									if(data.session.frame%(Math.floor(data.config.framerate/30.0))==0)
										this.key[i][type].func(this.key[i][type].args[0],this.key[i][type].args[1]);
								}
								else
									this.key[i][type].func(this.key[i][type].args[0],this.key[i][type].args[1]);
							}
							else if(!this.key[i][type].args[3])
							{
								if(type == 1)
								{
									if(data.session.frame%(Math.floor(data.config.framerate/30.0))==0)
										this.key[i][type].func(this.key[i][type].args[0],this.key[i][type].args[1],this.key[i][type].args[2]);
								}
								else
									this.key[i][type].func(this.key[i][type].args[0],this.key[i][type].args[1],this.key[i][type].args[2]);
							}
							else if(!this.key[i][type].args[4])
							{
								if(type == 1)
								{
									if(data.session.frame%(Math.floor(data.config.framerate/30.0))==0)
										this.key[i][type].func(this.key[i][type].args[0],this.key[i][type].args[1],this.key[i][type].args[2],this.key[i][type].args[3]);
								}
								else
									this.key[i][type].func(this.key[i][type].args[0],this.key[i][type].args[1],this.key[i][type].args[2],this.key[i][type].args[3]);
							}
							else
							{
								if(type == 1)
								{
									if(data.session.frame%(Math.floor(data.config.framerate/30.0))==0)
										this.key[i][type].func(this.key[i][type].args[0],this.key[i][type].args[1],this.key[i][type].args[2],this.key[i][type].args[3],this.key[i][type].args[4]);
								}
								else
									this.key[i][type].func(this.key[i][type].args[0],this.key[i][type].args[1],this.key[i][type].args[2],this.key[i][type].args[3],this.key[i][type].args[4]);
							}
						}
				}
		}
	}
}

//-----------------------------------
//SAVE
//-----------------------------------
function Save(data)
{
	fs.writeFileSync('./assets/save/save.json', JSON.stringify(data.scene));
}

function Load(data,link)
{
	let tempLoad = require("./assets/save/save.json")
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
        font:[],
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
        camera:{},
        event:[],
        map:{},
        creature:[],
		hitbox:[],
		area:[],
		addArea:function(name,hitbox,position,active,visible,color)
		{
			position = DefaultsTo(position,{x:0,y:0,z:0});
			color = defsto(color,RGBA(0,0,0,0));
			visible = defsto(visible,true);
			active = true;
			let temp = {name:name,hitbox:hitbox,position:position,color:color,active:active,visible:visible};//color stands for wireframe color
			this.area[name] = temp;
			this.area.push(temp);
		},
		addHitbox:function(name,hitbox,position,rotation,frame,color,visible,active)
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
		addCreature:function(name,type,position,rotation,speed,alive,active)
		{
			type = defsto(type,'human');
			position = defsto(position,Vector3(0,0,0));
			rotation = defsto(rotation,Vector3(0,0,0));
			speed = defsto(speed,0.1);
			alive = defsto(alive,true);
			active = defsto(active,true);
			this.creature[name] = {name:name,position:position,rotation:rotation,speed:speed,alive:alive,active:active};
			this.creature.push(this.creature[name]);
		},
		addCreature2Render2:function(name,type,position,rotation,speed,alive,active)
		{
			type = defsto(type,'human');
			position = defsto(position,Vector3(0,0,0));
			rotation = defsto(rotation,Vector3(0,0,0));
			speed = defsto(speed,0.1);
			alive = defsto(alive,true);
			active = defsto(active,true);
			this.addCreature(name,type,position,rotation,speed,alive,active);
			this.render.addCreature(this.creature[name], this.creature[name].type);
		},
		render:
		{
			file:{},//is set afterwards in the constructor
			model:[],
			text:[],
			image:[],
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
			addText:function(name,fontid,text,position,color,visible)
			{
				position = DefaultsTo(position,{x:0,y:0});
				text = defsto(text,"empty");
				color = defsto(color,RGBA(0,0,0,0));
				visible = defsto(visible,true);
				let temp = {name:name,id:fontid,text:text,position:position,color:color,visible:visible};//color stands for wireframe color
				this.text[name] = temp;
				this.text.push(temp);
			},
			addImage:function(name,imageid,position,scale,color,visible)
			{
				position = DefaultsTo(position,{x:0,y:0});
				color = defsto(color,RGBA(0,0,0,0));
				visible = defsto(visible,true);
				let temp = {name:name,id:imageid,position:position,color:color,visible:visible};//color stands for wireframe color
				this.image[name] = temp;
				this.image.push(temp);
			},

		}
    },
	keyboard:CreateDynamicKeyboard(),
}

class Data	
{
	constructor(loadCallback)
	{
		this.session = {..._Data.session};
		this.scene = {..._Data.scene};
		this.file = {..._Data.file};
		this.keyboard = {..._Data.keyboard};
		this.config = require("./config.json");
		this.scene.render.file = this.file;//just a link
		this.scene.camera = CameraStart(this.config.camerafov);
		r.InitAudioDevice();
		r.InitWindow(this.config.screen.x, this.config.screen.y, this.config.title);
		r.SetTargetFPS(this.config.framerate);
		r.SetExitKey(r.KEY_END);
		this.session.rendertexture = r.LoadRenderTexture(this.config.screen.x/this.config.pixelsize, this.config.screen.y/this.config.pixelsize);
		this.scene.background = {r:115, g:105, b:97, a:255};
		this.scene.creature = [];
		this.session.frame = 0;
		this.scene.render.addText('build',0,this.config.title + " v" + (this.config.build/10000),r.Vector2(0,(this.config.screen.y)-16),COR_PRETO,true);
		//CURRENT_LEVEL
		this.scene.map.currentLevel = 0;
		if(typeof loadCallback != 'undefined')
			loadCallback(this);
		//start menu
		if(typeof this.file.font[2] != 'undefined'&&typeof this.file.music[0] != 'undefined')
		{
			let startMenu = 
			[
				{//exit the current menu(possibly go back to another menu, or go back to the game)
					text:"jogar",
					func:function(){startMenu.offload = true;}
				},
				{//exit(to OS)
					text:"sair",
					func:function(){startMenu.data.session.exit = true;startMenu.offload = true;}, 
				},
			];
			startMenu.logo = true;
			startMenu.data = this;
			Menu(startMenu);
		}
	}
}

//-----------------------------------
//exports
//-----------------------------------

module.exports = 
{
	COR_VERMELHO,COR_SELECIONADO,COR_SELECIONADO2,COR_PRETO,COR_VAZIO,
	COR_BRANCO,COR_CINZA,COR_LARANJA,COR_PELE0,COR_ROUPA0,COR_ROUPA1,
	Vector2,Vector2Zero,Vector3,Vector3Zero,RGBA,BoundingBox,RotateAroundPivot,
	LimitItTo,limito,DefaultsTo,defsto,
	Data,Render,Menu,CameraStart,Move3D,PlayerCollider,Gravit,Save,Load,
};