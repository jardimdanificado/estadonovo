//------------------------------------------
//UTIL
//------------------------------------------

function range(min, max) 
{
	let arr = [];
	for (var i = min; i < max ; i++) 
	{
		arr.push(i+"");
	}
  return arr;
}

//------------------------------------------
//KEYBOARD
//------------------------------------------

function keyDown()
{
	if (keyIsDown(LEFT_ARROW) || keyIsDown(65))
		player.rotation.y -= 6;
	if (keyIsDown(RIGHT_ARROW)|| keyIsDown(68))
		player.rotation.y += 6;
	if (keyIsDown(DOWN_ARROW) || keyIsDown(83))
		player.move(true);
	if (keyIsDown(UP_ARROW)|| keyIsDown(87))
		player.move(false);
}

function keyPressed()
{
	if (keyCode == 71)//G
	{
		console.log(sistema);
	}
	else if	(keyCode == 119)//F8
	{
		console.log(frameRate());
	}
	else if (keyCode == 83 || keyCode == DOWN_ARROW ) //S
	{
		player.model = sistema.file.model['player-walk'];
		player.currentProgression = -1;
		if(frameCount%10)
			sistema.render.scene.camera.update();
	}
	else if (keyCode == 87 || keyCode == UP_ARROW ) //W
	{
		player.model = sistema.file.model['player-walk'];
		player.currentProgression = 1;
		if(frameCount%10)
			sistema.render.scene.camera.update();
	}
}

function keyReleased()
{
	if (
		keyCode == 83 || 
		keyCode == 87 ||
 		keyCode == UP_ARROW || 
		keyCode == DOWN_ARROW 
	   ) 
	{
		player.model = sistema.file.model['player-idle'];
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
	sistema = new Sistema();
	sistema.file.font.load("assets/font/acentos/KyrillaSansSerif-Bold.ttf");//sistema.file.font[0] as no name given
	sistema.file.font.load("assets/font/Mockery.ttf");//sistema.file.font[1] as no name given
	sistema.file.model.load('assets/models/map/level0/0.obj','map0');//single-file model import example
	let arrayTemporario = range(1,24);//temp numbers array for animation initialization
	//multi-file model(ANIMATION) import example
	sistema.file.model.load
	({
		...arrayTemporario,
		name:'player-walk',
		ext:'.obj',
		path:'assets/models/player/walk/'
	});
	arrayTemporario = range(1,239);
	sistema.file.model.load
	({
		...arrayTemporario,
		name:'player-idle',
		ext:'.obj',
		path:'assets/models/player/idle/'
	});
	sistema.file.image.load('assets/models/map/level0/texture_0.png','map0');//single-file image import example
}

function setup()
{
	//canvas
	
	sistema.setup();

	delete sistema.setup();
	//delete sistema._cameraSetup();
	
	sistema.world.creature.new
	({
		name:'joao',
		color:{r:140,g:100,b:0,a:255},
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