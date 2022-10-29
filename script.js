//------------------------------------------
//KEYBOARD
//------------------------------------------

function keyDown()
{
	if (keyIsDown(LEFT_ARROW) || keyIsDown(65)) 
		player.target.x -= player.speed;
	if (keyIsDown(RIGHT_ARROW)|| keyIsDown(68))
		player.target.x += player.speed;
	if (keyIsDown(DOWN_ARROW) || keyIsDown(83))
		player.target.y += player.speed;
	if (keyIsDown(UP_ARROW)|| keyIsDown(87))
		player.target.y -= player.speed;
}

function keyPressed()
{
	if (keyCode == 71) 
	{
		console.log(resma);
	}
	/*if (keyCode == 190)
		player.rendering.nextFrame();
	if (keyCode == 188)
		player.rendering.previousFrame();*/
}

//------------------------------------------
//MOUSE
//------------------------------------------

function mouseClicked() 
{
	
	for(i = 0; i < resma.length; i++)
		if(Check2DCollision(resma[i].current,{x:mouseX-4,y:mouseY-4,h:8,w:8}))
		{
			if(resma[i].playable == true)
				player = resma[i];
			else 
				player.text.say("o objeto selecionado nao pode ser controlado",2);
			return 0;
		}
	
	player.target.x = mouseX-(player.current.w/2);
	player.target.y = mouseY-(player.current.h/2);
	
}

//------------------------------------------
//MAIN
//------------------------------------------

var player;

function preload()
{
	//let temp = [];
	/*for(i=0;i<10;i++)
		temp.push("./data/image/test/" + i + ".png")
	data.image.load("idle",temp);*/
	data.image.load("idle","./data/image/null.png")
	data.image.load("null","./data/image/null.png");
	data.font[0] = loadFont("data/font/acentos/KyrillaSansSerif-Bold.ttf");
	data.font[1] = loadFont("data/font/Mockery.ttf");
}

function setup() 
{
	player = new Folha("jao","player");
	player.current.xywh(12,14,48,48);
	player.rendering.update("idle",0);
	
	let temp = [];
	for(i = 0; i < 20; i++)
	{	
		temp[i] = new Folha("box" + i,"box");
		temp[i].current.xywh(14 + (i*22), 100 ,16,16);
	}
	let temp4 = new Folha("abc","wall");
	temp4.current.xywh(440,100,16,16);
  	//createCanvas(displayWidth, displayHeight);
  	createCanvas(windowWidth, windowHeight, P2D);
	background(255);
	frameRate(60);
	noCursor();
}



function draw() 
{
	resma.action.solveAll();
	clear();
	
  	//fill("red");
	//rect(player.position.x, player.position.y,sistema.grid.default);
	for(i=0;i<resma.length;i++)
	{
		if(resma[i].current.x !== resma[i].target.x || resma[i].current.y !== resma[i].target.y)
			line(resma[i].current.x+(resma[i].current.w/2),resma[i].current.y+(resma[i].current.h/2),resma[i].target.x+(resma[i].current.w/2),resma[i].target.y+(resma[i].current.h/2))
		resma[i].rendering.render();
	}
	for(i=0;i<resma.length;i++)
	{
		resma[i].text.say();
		//if(resma[i].target.x != 0 || resma[i].target.y != 0)
		resma[i].toTargetMove();
	}
	
	keyDown();
	
	//mouse
	stroke(0, 0, 0);
	strokeWeight(0.5);
	noFill();
	circle(mouseX,mouseY,8);
}