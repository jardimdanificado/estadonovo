const r = require('raylib');
const fs = require('fs');
//const {app} = require('electron');//this need to be uncommented to be run it on electron
var mqq = require("./maquina.js");
var data;

const Teclado =
{
	gameplay: 
	{
		escMenu: 
		[
			{//exit the current menu(possibly go back to another menu, or go back to the game)
				text:"voltar ao jogo",
				func:function(){Teclado.gameplay.escMenu.offload = true;}
			},
			{//exit(to OS)
				text:"sair",
				func:function(){Teclado.gameplay.escMenu.data.session.exit = true;Teclado.gameplay.escMenu.offload = true;}, 
			},
		],
		pressed:
		{
			w:function(data)
			{
				data.scene.render.model['joao451'].progression = 1;
				data.scene.render.model['joao451'].id = 'player-walk';
			},
			s:function(data)
			{
				data.scene.render.model['joao451'].progression = -1;
				data.scene.render.model['joao451'].id = 'player-walk';
			},
		},
		down:
		{
			w:function(data)
			{
				if(mqq.PlayerCollider(data,data.scene.render.model['joao451'],false)==false)
				{
					mqq.Move3D(data.scene.creature['joao451'].position,data.scene.creature['joao451'].rotation.y,data.scene.creature['joao451'].speed);
				}
			},
			s:function(data)
			{
				if(mqq.PlayerCollider(data,data.scene.render.model['joao451'],true)==false)
				{
					mqq.Move3D(data.scene.creature['joao451'].position,data.scene.creature['joao451'].rotation.y,(-1)*data.scene.creature['joao451'].speed);
				}
			},
			a:function(data)
			{
				data.scene.creature['joao451'].rotation.y += data.config.rotationspeed;
				data.scene.creature['joao451'].rotation.y = mqq.limito(data.scene.creature['joao451'].rotation.y,0,359);
			},
			d:function(data)
			{
				data.scene.creature['joao451'].rotation.y -= data.config.rotationspeed;
				data.scene.creature['joao451'].rotation.y = mqq.limito(data.scene.creature['joao451'].rotation.y,0,359);
			},
			space:function(data)
			{
				data.scene.creature['joao451'].position.y += 0.2;
			},
		},
		released:
		{
			w:function(data)
			{
				data.scene.render.model['joao451'].progression = 1;
				data.scene.render.model['joao451'].id = 'player-idle';
			},
			s:function(data)
			{
				data.scene.render.model['joao451'].progression = 1;
				data.scene.render.model['joao451'].id = 'player-idle';
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
			data.keyboard.set(r.KEY_SPACE,'down',this.down.space,[data]);
			data.keyboard.set(r.KEY_G,'pressed',mqq.Save,[data]);
		}
	}
}

function load(data)
{
	//DEFAULT FONTS
	data.file.font.push(r.LoadFontEx("assets/font/acentos/KyrillaSansSerif-Bold.ttf", 16, 0, 0));
	data.file.font.push(r.LoadFontEx("assets/font/Mockery.ttf", 48, 0, 0));
	data.file.font.push(r.LoadFontEx("assets/font/Mockery.ttf", 24, 0, 0));
	//MUSIC
	data.file.music.push(r.LoadMusicStream("assets/audio/music/maintheme_by_kayoa.mp3"));
	//MODELS
	data.file.loadModel("lvl0_map0","assets/models/map/level0/0.glb",false);
	data.file.loadModel("lvl0_props0","assets/models/map/level0/props/0.glb",true);
	data.file.loadModel("lvl0_hitbox0","assets/models/map/level0/hitbox/hitbox0.glb",true);
	data.file.loadModel("lvl0_hitbox1","assets/models/map/level0/hitbox/hitbox1.glb",true);
	data.file.loadModel("lvl0_hitbox2","assets/models/map/level0/hitbox/hitbox2.glb",true);
	data.file.loadModel("lvl0_hitbox3","assets/models/map/level0/hitbox/hitbox3.glb",true);
	data.file.loadModel("lvl0_hitbox4","assets/models/map/level0/hitbox/hitbox4.glb",true);
	data.file.loadModel("lvl0_hitbox5","assets/models/map/level0/hitbox/hitbox5.glb",true);
	data.file.loadModel("lvl0_hitbox6","assets/models/map/level0/hitbox/hitbox6.glb",true);
	data.file.loadModel("lvl0_hitbox7","assets/models/map/level0/hitbox/hitbox7.glb",true);
	data.file.loadModel("lvl0_hitbox8","assets/models/map/level0/hitbox/hitbox8.glb",true);
	data.file.loadModel("lvl0_hitbox9","assets/models/map/level0/hitbox/hitbox9.glb",true);
	data.file.loadModel("lvl0_hitbox10","assets/models/map/level0/hitbox/chao.glb",true);
	data.file.loadModel("lvl0_map0item0","assets/models/map/level0/item/0.glb",true);
	data.file.loadModel("lvl0_map0item1","assets/models/map/level0/item/1.glb",true);
	data.file.loadModel("lvl0_map0item2","assets/models/map/level0/item/2.glb",true);
	data.file.loadModel("lvl0_map0item3","assets/models/map/level0/item/3.glb",true);
	data.file.loadModel("lvl0_area0","assets/models/map/level0/area/0.glb",true);
	data.file.loadModel("lvl0_area1","assets/models/map/level0/area/1.glb",true);
	data.file.loadModel("lvl0_area2","assets/models/map/level0/area/2.glb",true);
	data.file.loadModel("lvl0_area3","assets/models/map/level0/area/3.glb",true);
	data.file.loadModel("lvl0_area4","assets/models/map/level0/area/4.glb",true);
	data.file.loadModel("lvl0_area5","assets/models/map/level0/area/5.glb",true);
	data.file.loadModel("player-idle","assets/models/player/idle/",false);//note that i didnt provided any file, so it loads all files of the folder as a animation
	data.file.loadModel("player-walk","assets/models/player/walk/",false);
}

function main()
{
	//if you provide the constructor a load function it will boot a start menu
	//note that the menu will only showup if at least 3 fonts and a music are loaded 
	data = new mqq.Data(load);//all startup needs are in the constructor
	//load(data);//
	
	data.scene.addCreature('joao451','human',{x:1,y:4,z:0},{x:0,y:180,z:0},0.15,true,true);//create the creature in scene
	data.scene.render.addCreature(data.scene.creature['joao451']);//add the just created creature in the render context
	//or you can use this instead, does the same as the 2 functions above
	//data.scene.addCreature2Render2('joao451','human',{x:0,y:4,z:0},{x:0,y:0,z:0},0.1,true,true);
	
	data.scene.render.addModel('map0','lvl0_map0');//add the map model to the render scene
	
    data.scene.camera.target = data.scene.creature[0].position;
    data.scene.camera.position = {x:0.4375, y:10, z:11.0625};

	//this add all lvl0 hitboxes and areas to scene
	for(let i = 0;i<data.file.hitbox.length;i++)
		if(data.file.hitbox[i].name.includes('lvl0_hitbox'))
			data.scene.addHitbox(data.file.hitbox[i].name,data.file.hitbox[i].hitbox);
		else if(data.file.hitbox[i].name.includes('lvl0_area'))
			data.scene.addArea(data.file.hitbox[i].name,data.file.hitbox[i].hitbox);
	
	Teclado.gameplay.useThis(data);//use the gameplay keyboard template
	
    while(!r.WindowShouldClose() && data.session.exit == false)
    {
		data.keyboard.run(data);
		
		if(data.session.frame%(Math.floor(data.config.framerate/30.0))==0)
		{
			mqq.Gravit(data,data.scene.render.model[0]);
		}
		mqq.Render(data);
    }
    r.CloseAudioDevice();
	r.CloseWindow();
	//app.quit();//this need to be uncommented to be run it on electron
}
main();//this need to be commented to be run it on electron
//app.on('ready', main);//this need to be uncommented to be run it on electron