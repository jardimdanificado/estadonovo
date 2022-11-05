//------------------------------------------
//KEYBOARD
//------------------------------------------

function keyDown()
{
	if (keyIsDown(LEFT_ARROW) || keyIsDown(65)) 
		player.position.x -= 0.1;
	if (keyIsDown(RIGHT_ARROW)|| keyIsDown(68))
		player.position.x += 0.1;
	if (keyIsDown(DOWN_ARROW) || keyIsDown(83))
		player.position.z += 0.1;
	if (keyIsDown(UP_ARROW)|| keyIsDown(87))
		player.position.z -= 0.1;
}

function keyPressed()
{
	if (keyCode == 71) 
	{
		console.log(sistema);
	}
	/*if (keyCode == 190)
		player.rendering.nextFrame();
	if (keyCode == 188)
		player.rendering.previousFrame();*/
}

//------------------------------------------
//MOUSE
//------------------------------------------

//function mouseClicked() 
//{
	
	//for(i = 0; i < resma.length; i++)
		//if(Check2DCollision(resma[i],{x:mouseX-4,y:mouseY-4,h:8,w:8}))
		//{
			//if(resma[i].playable == true)
		//		player = resma[i];
		//	else 
		//		player.text.say("o objeto selecionado nao pode ser controlado",2);
		//	return 0;
		//}
	//player.target.x = mouseX;
	//player.target.y = mouseY;
	//console.log(sistema)
//}

//------------------------------------------
//MAIN
//------------------------------------------

var sistema;
var player;
var camera;
var map;
var canvas;
function preload()
{
	//let temp = [];
	/*for(i=0;i<10;i++)
		temp.push("./data/image/test/" + i + ".png")
	data.image.load("idle",temp);*/
	//data.image.load("idle","./data/image/null.png")
	//data.image.load("null","./data/image/null.png");
	
	sistema = new Sistema();
	sistema.file.font.load("assets/font/acentos/KyrillaSansSerif-Bold.ttf");//sistema.file.font[0] as no name given
	sistema.file.font.load("assets/font/Mockery.ttf");//sistema.file.font[1] as no name given
	sistema.file.model.load('assets/models/map/level0/0.obj','map0');//single-file model import example
	sistema.file.model.load('assets/models/player/idle/1.obj','player-idle');
	//multi-file model(ANIMATION) import example
	sistema.file.model.load
	({
		...['1','2','3','4','5','6','7'],
		name:'player-walk',
		ext:'.obj',
		path:'assets/models/player/walk/'
	});
	sistema.file.image.load('assets/models/map/level0/texture_0.png','map0');//single-file image import example
}

function setup()
{
	//canvas
	
	sistema.setup();
	sistema.world.creature.new
	({
		name:'joao',
		color:{r:0,g:0,b:0,a:0},
		position:{x:0,y:0,z:0.5},
		rotation:{x:180,y:180,z:0},
		scale:{x:1,y:1,z:1},
		model:sistema.file.model['player-idle']
	});
	
	player = sistema.world.creature['joao'];
	sistema.render.scene.camera.target = player.position;
	map = 
	{
		name:'mapa0',
		color:{r:0,g:0,b:0,a:0},
		position:{x:0,y:0,z:0},
		rotation:{x:180,y:180,z:0},
		scale:{x:1,y:1,z:1},
		model:sistema.file.model['map0'],
		texture:sistema.file.image['map0']
	}
	
	sistema.render.scene.model.add(map);
	sistema.render.scene.model.add(player);
}

function draw() 
{
	sistema.gfx.clear();
	sistema.gfx.noStroke();
	keyDown();

	
	sistema.render.scene.render();
	image(sistema.gfx, 0, 0, sistema.screen.w, sistema.screen.h);
	
	//mouse
	push();
	stroke(0,0,0);
	strokeWeight(1);
	noFill();
	circle(mouseX,mouseY,6);
	pop();
}