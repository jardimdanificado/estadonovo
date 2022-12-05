const r = require('raylib');
const fs = require('fs');
//const {app} = require('electron');//this need to be uncommented to be run it on electron
var mqq = require("./maquina.js");
var data;
var player;

const Teclado =
{
	gameplay: 
	{
		escMenu: 
		{
			0:{//exit the current menu(possibly go back to another menu, or go back to the game)
				text:"voltar ao jogo",
				func:function(){Teclado.gameplay.escMenu.offload = true;}
			},
			1:{//exit(to OS)
				text:"sair",
				func:function(){Teclado.gameplay.escMenu.data.session.exit = true;Teclado.gameplay.escMenu.offload = true;}, 
			},
			length:2,
			offloadkey:r.KEY_ESCAPE
		},
		pressed:
		{
			w:function(data)
			{
				player.render.progression = 1;
				player.render.id = 'player-walk';
			},
			s:function(data)
			{
				player.render.progression = -1;
				player.render.id = 'player-walk';
			},
			f:function(data)
			{
				for(let i = 0; i< data.scene.event.length;i++)
				{
					if(data.scene.event[i].type == 'item')
					{
						if(player.creature.inventory.length < player.creature.inventory.max)
						{
							player.creature.inventory.push(data.scene.event[i].item);
							data.scene.event = data.scene.event.splice(i,1);
						}
					}
				}
			},
			j:function()
			{
				mqq.pend(15,console.log,['aoba','teste']);
			}
		},
		down:
		{
			w:function(data)
			{
				if(mqq.PlayerCollider(data,player.render,false)==false)
				{
					mqq.Move3D(player.creature.position,player.creature.rotation.y,player.creature.speed);
					if(data.config.camerafollow == true)
						mqq.Move3D(data.scene.camera.position,player.creature.rotation.y,player.creature.speed);
				}
			},
			s:function(data)
			{
				if(mqq.PlayerCollider(data,player.render,true)==false)
				{
					mqq.Move3D(player.creature.position,player.creature.rotation.y,(-1)*player.creature.speed);
					if(data.config.camerafollow == true)
						mqq.Move3D(data.scene.camera.position,player.creature.rotation.y,player.creature.speed*(-1));
				}
			},
			a:function(data)
			{
				player.creature.rotation.y += data.config.rotationspeed;
				player.creature.rotation.y = mqq.limito(player.creature.rotation.y,0,359);
			},
			d:function(data)
			{
				player.creature.rotation.y -= data.config.rotationspeed;
				player.creature.rotation.y = mqq.limito(player.creature.rotation.y,0,359);
			},
			q:function(data)
			{
				data.scene.camera.position = mqq.RotateAroundPivot(data.scene.camera.position,player.creature.position,data.config.rotationspeed);
			},
			e:function(data)
			{
				data.scene.camera.position = mqq.RotateAroundPivot(data.scene.camera.position,player.creature.position,data.config.rotationspeed*(-1));
			},
			space:function(data)
			{
				player.creature.position.y += 0.2;
			},
		},
		released:
		{
			w:function(data)
			{
				player.render.progression = 1;
				player.render.id = 'player-idle';
			},
			s:function(data)
			{
				player.render.progression = 1;
				player.render.id = 'player-idle';
			},
		},
		useThis:function(data)
		{
			data.keyboard.set(r.KEY_ESCAPE,'pressed',mqq.Menu,[Teclado.gameplay.escMenu,data]);
			data.keyboard.set(r.KEY_W,'down',this.down.w,[data]);
			data.keyboard.set(r.KEY_W,'pressed',this.pressed.w,[data]);
			data.keyboard.set(r.KEY_W,'released',this.released.w,[data]);
			data.keyboard.set(r.KEY_S,'down',this.down.s,[data]);
			data.keyboard.set(r.KEY_S,'pressed',this.pressed.s,[data]);
			data.keyboard.set(r.KEY_S,'released',this.released.s,[data]);
			data.keyboard.set(r.KEY_A,'down',this.down.a,[data]);
			data.keyboard.set(r.KEY_D,'down',this.down.d,[data]);
			data.keyboard.set(r.KEY_Q,'down',this.down.q,[data]);
			data.keyboard.set(r.KEY_E,'down',this.down.e,[data]);
			data.keyboard.set(r.KEY_SPACE,'down',this.down.space,[data]);
			data.keyboard.set(r.KEY_G,'pressed',mqq.Save,[data]);
			data.keyboard.set(r.KEY_J,'pressed',this.pressed.j,[data]);
		}
	}
}

function load(data)
{
	//DEFAULT FONTS
	data.file.font.push(r.LoadFontEx("assets/font/acentos/KyrillaSansSerif-Bold.ttf", data.config.fontsize, 0, 0));
	data.file.font.push(r.LoadFontEx("assets/font/Mockery.ttf", data.config.fontsize*3, 0, 0));
	data.file.font.push(r.LoadFontEx("assets/font/Mockery.ttf", data.config.fontsize*1.5, 0, 0));
	//MUSIC
	data.file.music.push(r.LoadMusicStream("assets/audio/music/maintheme_by_kayoa.mp3"));
	//MODELS
	data.file.loadModel("lvl0_map0","assets/models/map/level0/0.glb",false);
	data.file.loadModel("lvl0_hitbox0","assets/models/map/level0/hitbox/0.obj",true);
	data.file.loadModel("lvl0_hitbox1","assets/models/map/level0/hitbox/1.obj",true);
	data.file.loadModel("lvl0_hitbox2","assets/models/map/level0/hitbox/2.obj",true);
	data.file.loadModel("lvl0_hitbox3","assets/models/map/level0/hitbox/3.obj",true);
	data.file.loadModel("lvl0_hitbox4","assets/models/map/level0/hitbox/4.obj",true);
	data.file.loadModel("lvl0_hitbox5","assets/models/map/level0/hitbox/5.obj",true);
	data.file.loadModel("lvl0_hitbox6","assets/models/map/level0/hitbox/6.obj",true);
	data.file.loadModel("lvl0_hitbox7","assets/models/map/level0/hitbox/7.obj",true);
	data.file.loadModel("lvl0_hitbox8","assets/models/map/level0/hitbox/8.obj",true);
	data.file.loadModel("lvl0_hitbox9","assets/models/map/level0/hitbox/9.obj",true);
	data.file.loadModel("lvl0_hitbox10","assets/models/map/level0/hitbox/10.obj",true);
	data.file.loadModel("lvl0_hitbox11","assets/models/map/level0/hitbox/11.obj",true);
	data.file.loadModel("lvl0_hitbox12","assets/models/map/level0/hitbox/12.obj",true);
	data.file.loadModel("lvl0_hitbox13","assets/models/map/level0/hitbox/13.obj",true);
	data.file.loadModel("lvl0_hitbox14","assets/models/map/level0/hitbox/14.obj",true);
	data.file.loadModel("player-idle","assets/models/player/idle/",false);//note that i didnt provided any file, so it loads all files of the folder as a animation
	data.file.loadModel("player-walk","assets/models/player/walk/",false);
}

function main()
{
	//if you provide the constructor a load function it will boot a start menu
	//note that the menu will only showup if at least 3 fonts and a music are loaded 
	data = new mqq.Data(load);//all startup needs are in the constructor
	
	data.scene.addCreature('joao451','human',{x:1,y:4,z:0},{x:0,y:180,z:0},0.15,true,true);//create the creature in scene
	data.scene.render.addCreature(data.scene.creature['joao451']);//add the just created creature in the render context
	//or you can use this instead, does the same as the 2 functions above
	//data.scene.addCreature2Render2('joao451','human',{x:0,y:4,z:0},{x:0,y:0,z:0},0.1,true,true);

	player = {};
	player.render = data.scene.render.model['joao451'];
	player.creature = data.scene.creature['joao451'];
	
	data.scene.render.addModel('map0','lvl0_map0');//add the map model to the render scene
    data.scene.camera.target = data.scene.creature[0].position;
    data.scene.camera.position = {x:0.4375, y:10, z:11.0625};

	//this add all lvl0 hitboxes to scene
	for(let i = 0;i<data.file.hitbox.length;i++)
		if(data.file.hitbox[i].name.includes('lvl0_hitbox'))
			data.scene.addHitbox(data.file.hitbox[i].name,data.file.hitbox[i].hitbox);
	
	Teclado.gameplay.useThis(data);//use the gameplay keyboard template
    while(!r.WindowShouldClose() && data.session.exit == false)
    {
		data.keyboard.run(data);
		if(data.session.frame%(Math.floor(data.config.framerate/30.0))==0)
		{
			mqq.pend();//frames the pendending events
			mqq.Gravit(data,player.render);
		}
		mqq.Render(data);
    }
    r.CloseAudioDevice();
	r.CloseWindow();
	//app.quit();//this need to be uncommented to be run it on electron
}
main();//this need to be commented to be run it on electron
//app.on('ready', main);//this need to be uncommented to be run it on electron