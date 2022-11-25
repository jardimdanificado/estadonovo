const r = require('raylib');
const fs = require('fs');
//const { app } = require('electron');

//ENGINE
//#include "maquina/maquina.h"
var mqq = require("./maquina");
var data;

function main()
{
	data = new mqq.Data();
	mqq.Start(data);

	data.scene.creature.push
	(
		{
			name:"joao451",
			type:"human",
			position:{x:0,y:0,z:0},
			speed:0.1,
			ray:{position:this.position, direction: {x:0,y:1,z:0}},
			alive:true,
			active:true,
			model:data.file.model["player"]
		}
	);

	function load()
	{
		data.file.loadModel("player-idle","data/models/player/idle/",false);
		data.file.loadModel("player-walk","data/models/player/walk/",false);
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
		data.file.loadModel("lvl0_chao0","data/models/map/level0/hitbox/chao.glb",true);
	}
	load();
    //start menu
    //MQMenu(data,0);
    data.scene.camera.target = {x:data.scene.creature[0].position.x,y:data.scene.creature[0].position.y,z:data.scene.creature[0].position.z};
    data.scene.camera.position = {x:0.4375, y:3.5, z:11.0625};
	//data.file.loadModel("player","data/guy.iqm",false);
	//console.log(data.scene.creature[0])
	data.scene.render.addCreature(data.scene.creature[0]);
	
    while(!r.WindowShouldClose()/* && data.session.exit == false*/)
    {
        data.session.frame++;
		//console.log(data.session.frame)
        r.UpdateCamera(data.scene.camera);
		r.BeginDrawing();
		r.ClearBackground(r.RAYWHITE);
		r.BeginMode3D(data.scene.camera);
		r.DrawText("Congrats! You created your first node-raylib window!", 120, 200, 20, r.LIGHTGRAY);
		//console.log(data.scene.render);
		
		r.DrawModelEx(
			data.file.model[data.scene.render.model[0].id].model[data.scene.render.model[0].frame], 
			data.scene.render.model[0].position, 
			r.Vector3(0,1,0), 
			data.scene.render.model[0].rotation.y, 
			data.scene.render.model[0].scale, 
			data.scene.render.model[0].color
		);	
		if(data.scene.render.model[0].frame == data.file.model[data.scene.render.model[0].id].model.length-1)
			data.scene.render.model[0].frame= 0;
		else
			data.scene.render.model[0].frame++;
		r.EndMode3D();
		r.EndDrawing();
		
        //TECLADO_MAIN(data);

        //MQGravit(data, 0);
        //MQRenderQueue(data);
    }
    //CloseAudioDevice();--------------------------------------------------------------------------------------
	r.CloseWindow();
	//app.quit();
}
main();
//app.on('ready', main);//change this from RaylibDemo to main when engine fully ported from c