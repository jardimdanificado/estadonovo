//------------------------------------------
//KEYBOARD
//------------------------------------------

function keyDown()
{
	if (keyIsDown(LEFT_ARROW) || keyIsDown(65)) 
		player.Move({x:(-1)*player.speed,y:0});
	if (keyIsDown(RIGHT_ARROW)|| keyIsDown(68))
		player.Move({x:player.speed,y:0});
	if (keyIsDown(DOWN_ARROW) || keyIsDown(83))
		player.Move({x:0,y:player.speed});
	if (keyIsDown(UP_ARROW)|| keyIsDown(87))
		player.Move({x:0,y:(-1)*player.speed});
}

function keyPressed()
{
	if (keyCode == 71) 
	{
		console.log(list);
	}
	if (keyCode == 190)
		player.rendering.nextFrame();
	if (keyCode == 188)
		player.rendering.previousFrame();
}

//------------------------------------------
//MAIN
//------------------------------------------

var player;

function preload()
{
	data.image.load("idle",["./data/image/null.png","./data/image/crtbase.png"]);
	data.image.load("null","./data/image/null.png");
	data.font[0] = loadFont("data/font/Mockery.ttf");
}

function setup() 
{
	player = new Folha("jao","player","free");
	player.xywh(12,14,48,48);
	player.rendering.update("idle",0);
	let temp = [];
	for(i = 0; i < 20; i++)
	{	
		temp[i] = new Folha("box" + i,"box","free");
		temp[i].xywh(0 + (i*22), 100 ,16,16);
	}
	let temp4 = new Folha("abc","wall","static");
	temp4.xywh(440,100,16,16);
  	//createCanvas(displayWidth, displayHeight);
  	createCanvas(windowWidth, windowHeight, WEBGL);
	background(255);
	frameRate(60);
}

function draw() 
{
	list.action.solveAll();
	clear(255,255,255,255);
  	noStroke();
  	//fill("red");
	//rect(player.position.x, player.position.y,sistema.grid.default);
	for(i=0;i<list.length;i++)
	{
		list[i].render();
	}
  	//ellipse(mouseX, mouseY, 25, 25);
	keyDown();
	//fill("black");
	textFont(data.font[0]);
	textSize(40);
	text("testetesteteste",40,40);
}