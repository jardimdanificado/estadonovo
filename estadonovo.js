//------------------------------------------
//KEYBOARD
//------------------------------------------

function keyDown()
{
	if (keyIsDown(LEFT_ARROW) || keyIsDown(65)) 
		sistema.render.scene.camera.position.x--;
	if (keyIsDown(RIGHT_ARROW)|| keyIsDown(68))
		sistema.render.scene.camera.position.x++;
	if (keyIsDown(DOWN_ARROW) || keyIsDown(83))
		sistema.render.scene.camera.position.z++;
	if (keyIsDown(UP_ARROW)|| keyIsDown(87))
		sistema.render.scene.camera.position.z--;
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
	//data.font[0] = loadFont("data/font/acentos/KyrillaSansSerif-Bold.ttf");
	//data.font[1] = loadFont("data/font/Mockery.ttf");
	sistema = new Sistema();
	sistema.file.model.load('assets/models/map/level0/0.obj','map0');
	sistema.file.image.load('assets/models/map/level0/texture_0.png','map0');
}

function setup()
{
	//canvas
	sistema.setup();
	map = 
	{
		name:'mapa0',
		color:{r:0,g:0,b:0,a:0},
		position:{x:0,y:10,z:0},
		rotation:{x:180,y:180,z:0},
		scale:{x:10,y:10,z:10},
		model:sistema.file.model['map0'],
		texture:sistema.file.image['map0']
	}
	sistema.render.scene.model.add(map);
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