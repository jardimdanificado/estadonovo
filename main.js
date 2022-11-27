const r = require('raylib');
const fs = require('fs');

var mqq = require("./maquina");
var data;

function Teclado(data)
{
	if(r.IsKeyPressed(r.KEY_W))
	{
		data.scene.render.model['joao451'].progression = 1;
		data.scene.render.model['joao451'].id = 'player-walk';
	}
	if(r.IsKeyDown(r.KEY_W))
	{
		mqq.Move3D(data.scene.creature['joao451'].position,data.scene.creature['joao451'].rotation.y,0.1);
	}
	if(r.IsKeyReleased(r.KEY_W))
	{
		data.scene.render.model['joao451'].progression = 1;
		data.scene.render.model['joao451'].id = 'player-idle';
	}
	
	if(r.IsKeyPressed(r.KEY_S))
	{
		data.scene.render.model['joao451'].progression = -1;
		data.scene.render.model['joao451'].id = 'player-walk';
	}
	if(r.IsKeyDown(r.KEY_S))
	{
		mqq.Move3D(data.scene.creature['joao451'].position,data.scene.creature['joao451'].rotation.y,-0.1);
	}
	if(r.IsKeyReleased(r.KEY_S))
	{
		data.scene.render.model['joao451'].progression = 1;
		data.scene.render.model['joao451'].id = 'player-idle';
	}
	
	if(r.IsKeyDown(r.KEY_A))
	{
		data.scene.creature['joao451'].rotation.y += 6;
	}
	
	if(r.IsKeyDown(r.KEY_D))
	{
		data.scene.creature['joao451'].rotation.y -= 6;
	}
}

function main()
{
	data = new mqq.Data();
	mqq.Start(data);
	function load()
	{
		data.file.loadModel("lvl0_map0","data/models/map/level0/0.glb",false);
		data.file.loadModel("lvl0_props0","data/models/map/level0/props/0.glb",true);
		data.file.loadModel("lvl0_hitbox0","data/models/map/level0/hitbox/hitbox0.glb",true);
		data.file.loadModel("lvl0_hitbox1","data/models/map/level0/hitbox/hitbox1.glb",true);
		data.file.loadModel("lvl0_hitbox2","data/models/map/level0/hitbox/hitbox2.glb",true);
		data.file.loadModel("lvl0_hitbox3","data/models/map/level0/hitbox/hitbox3.glb",true);
		data.file.loadModel("lvl0_hitbox4","data/models/map/level0/hitbox/hitbox4.glb",true);
		data.file.loadModel("lvl0_hitbox5","data/models/map/level0/hitbox/hitbox5.glb",true);
		data.file.loadModel("lvl0_hitbox6","data/models/map/level0/hitbox/hitbox6.glb",true);
		data.file.loadModel("lvl0_hitbox7","data/models/map/level0/hitbox/hitbox7.glb",true);
		data.file.loadModel("lvl0_hitbox8","data/models/map/level0/hitbox/hitbox8.glb",true);
		data.file.loadModel("lvl0_hitbox9","data/models/map/level0/hitbox/hitbox9.glb",true);
		data.file.loadModel("lvl0_hitbox10","data/models/map/level0/hitbox/chao.glb",true);
		data.file.loadModel("lvl0_map0item0","data/models/map/level0/item/0.glb",true);
		data.file.loadModel("lvl0_map0item1","data/models/map/level0/item/1.glb",true);
		data.file.loadModel("lvl0_map0item2","data/models/map/level0/item/2.glb",true);
		data.file.loadModel("lvl0_map0item3","data/models/map/level0/item/3.glb",true);
		data.file.loadModel("lvl0_area0","data/models/map/level0/area/0.glb",true);
		data.file.loadModel("lvl0_area1","data/models/map/level0/area/1.glb",true);
		data.file.loadModel("lvl0_area2","data/models/map/level0/area/2.glb",true);
		data.file.loadModel("lvl0_area3","data/models/map/level0/area/3.glb",true);
		data.file.loadModel("lvl0_area4","data/models/map/level0/area/4.glb",true);
		data.file.loadModel("lvl0_area5","data/models/map/level0/area/5.glb",true);
		data.file.loadModel("player-idle","data/models/player/idle/",false);
		data.file.loadModel("player-walk","data/models/player/walk/",false);
	}
	load();
	data.scene.creature.push
	(
		{
			name:"joao451",
			type:"human",
			position:{x:0,y:0,z:0},
			rotation:{x:0,y:0,z:0},
			speed:0.1,
			ray:{position:this.position, direction: {x:0,y:1,z:0}},
			alive:true,
			active:true
		}
	);
	data.scene.creature['joao451'] = data.scene.creature[0];
	data.scene.render.addCreature(data.scene.creature['joao451']);
	data.scene.render.addModel('map0','lvl0_map0');
	//data.scene.render.addModel(data.scene.creature['joao451']);
    //start menu
    //MQMenu(data,0);
	r.UpdateCamera(data.scene.camera);
    data.scene.camera.target = data.scene.creature[0].position;
    data.scene.camera.position = {x:0.4375, y:10, z:11.0625};
	for(let i = 0;i<data.file.hitbox.length;i++)
		if(data.file.hitbox[i].name.includes('lvl0_hitbox'))
		{
			data.scene.render.hitbox.push(data.file.hitbox[i].hitbox);
			data.scene.render.hitbox[data.file.hitbox[i].name] = data.file.hitbox[i].hitbox;
		}
    while(!r.WindowShouldClose()/* && data.session.exit == false*/)
    {
        data.session.frame++;
		Teclado(data);
		//console.log(data.session.frame)
        
		r.BeginDrawing();
		r.ClearBackground(r.RAYWHITE);
		r.BeginMode3D(data.scene.camera);
		for(let i = 0; i< data.scene.render.model.length;i++)
		{	
			if(data.scene.render.model[i].progression != 0)
			{
				if(data.session.frame % Math.floor(data.config.framerate/24) == 0)//setten up for 24fps
				{
					data.scene.render.model[i].frame += data.scene.render.model[i].progression;
				}
				data.scene.render.model[i].frame = mqq.limito(data.scene.render.model[i].frame,0,data.file.model[data.scene.render.model[i].id].model.length-2);
			}
			data.scene.render.model[i].rotation.y = mqq.limito(data.scene.render.model[i].rotation.y,0,359);
			
			if(data.scene.render.model[i].visible == true)
			{
				//console.log(data.file.model[data.scene.render.model[i].id])
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
		r.DrawTextEx(data.file.font[0],"Congrats! You created your first node-raylib window!", r.Vector2(0, 0), 16, 0, r.BLACK);
		r.EndDrawing();
    }
    //CloseAudioDevice();--------------------------------------------------------------------------------------
	r.CloseWindow();
	//app.quit();
}
main();
//app.on('ready', main);//change this from RaylibDemo to main when engine fully ported from c