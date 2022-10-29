//resma.js is the eutimia's engine

//------------------------------------------
//DICTIONARY
//------------------------------------------

var dic = [];
dic.unplayable = ['wall','object','item','prop','door','furniture','tree','plant','other'];
dic.static = ['wall','door','tree'];
dic.free = ['plant','furniture','prop','item','object', ,'other'];
dic.none = ['appearence','ghost','visual','gas','effect','floor','tile'];
dic.living = ['player','creature','human'];

//------------------------------------------
//PRIMITIVES && BASICS
//------------------------------------------

class Vector2
{
	x;
	y;
	constructor(ix,iy)
	{
		x = ix;
		y = iy;
	}
}

class Position
{
	x;y;w;h;
	xywh = function(xx,yy,ww,hh)
	{
		if(hh)
			if(typeof hh == 'number')
				this.h = hh;
		if(ww)
			if(typeof ww == 'number')
				this.w = ww;
		if(yy)
			if(typeof yy == 'number')
			{
				this.y = yy;
			}
		if(typeof xx == 'number')
		{	
			this.x = xx;
		}
	}
	constructor(xx,yy,ww,hh)
	{
		this.x = xx;
		this.y = yy;
		this.w = ww;
		this.h = hh;
	}
}

function Check2DCollision(r1, r2)
{
	if
	(
		/*
  		    A.X < B.X + B.Width
    		A.X + A.Width > B.X
		    A.Y < B.Y + B.Height
		    A.Y + A.Height > B.Y
  		*/
		r1.x < r2.x + r2.w &&
    	r1.x + r1.w > r2.x &&
    	r1.y < r2.y + r2.h &&
    	r1.y + r1.h > r2.y
	)
	{
		return(true);
	}
	else 
	{
		return(false);
	}
}

//------------------------------------------
//resma
//------------------------------------------

var resma = [];
resma.action = [];
resma.action.pending = [];
resma.action.delete = function(unwanted)
{
	if(!isNaN(unwanted))
		unwanted = this.pending[unwanted];
	this.pending = this.pending.filter(function(item){return item !== unwanted;});
}
resma.action.new = function(nAct,nData)
{
	this.pending.push({func:nAct,data:nData});
	console.log()
}
resma.action.clear = function()
{
	this.pending = [];
}
resma.action.solve = function(which)
{
	this.pending[which].func();
	this.pending.delete(which);
}
resma.action.solveAll = function()
{
	for(i = 0;i < this.pending.length;i++)
		this.pending[i].func();
	this.clear();
}

//------------------------------------------
//DATA
//------------------------------------------

var data = [];
data.image = [];
data.image.load = function(iname,path)
{
	let localObject = [];
	localObject.name = iname;
	if(Array.isArray(path))
	{	
		for(i=0;i<path.length;i++)
			localObject.push(loadImage(path[i]));
	}
	else
		localObject.push(loadImage(path));
	data.image[iname] = localObject;
}
data.font = [];

//------------------------------------------
//FOLHA
//------------------------------------------

class Folha
{
	name;type;resma;data;rendering;
	collision;// static,free,none
	current;
	target;
	speed;playable;
	pending;

	xywh = function(xx,yy,ww,hh)
	{
		if(hh)
			if(typeof hh == 'number')
			{	
				this.current.h = hh;
				this.target.h = hh;
			}
		if(ww)
			if(typeof ww == 'number')
			{	
				this.current.w = ww;
				this.target.w = ww;
			}
		if(yy)
			if(typeof yy == 'number')
			{
				this.current.y = yy;
				this.target.y = yy;
			}
		if(typeof xx == 'number')
		{	
			this.current.x = xx;
			this.target.x = xx;
		}
	}

	toTargetMove = function()
	{
		let current = this.current;
		let target = this.target;
		current.x = round(current.x);
		current.y = round(current.y);
		let local = {x:round((current.x - target.x)/(abs(current.x - target.x))),y:round((current.y - target.y)/abs(current.y - target.y))}
	
		if(!isNaN(local.y))
			this.Move({x:0,y:ceil(local.y*-1)});
		if(!isNaN(local.x))
			this.Move({x:ceil(local.x*-1),y:0});
	}
	
	Move = function(input)
	{
		let collisionFound = false;
		if(!input['queue'])
			input.queue = [];
		input.queue.push(this.name);
		
		let lposi =
		{
			x:this.current.x + input.x,
			y:this.current.y + input.y,
			h:this.current.h,
			w:this.current.w
		}
		for(i = 0; i < this.resma.length;i++)
			if (Check2DCollision(lposi,this.resma[i].current) && !input.queue.includes(this.resma[i].name))
			{
				collisionFound = true;
				if(this.resma[i].collision != "static")
				{
					if (this.resma[i].collision == "none")
					{
						this.current.x += input.x;
						this.current.y += input.y;
						input = ({x:input.x,y:input.y,queue:input.queue});
					}
					else
						for(i = 0; i < this.resma.length;i++)
							if(!input.queue.includes(this.resma[i].name) && Check2DCollision(lposi,this.resma[i].current))
							{
								var lspeed = this.resma[i].Move({x:input.x/2,y:input.y/2,queue:input.queue});
								if(lspeed.x != 0 || lspeed.y != 0)
								{
									this.current.x += lspeed.x/4;
									this.current.y += lspeed.y/4;
									input = lspeed;
								}
								else
									input = {x:0,y:0,queue:input.queue};
							}
				}
				else
				{	
					input = {x:0,y:0,queue:input.queue};
				}
			}
		if(!collisionFound)
		{
			this.current.x += input.x;
			this.current.y += input.y;
		}
		return {x:input.x,y:input.y,queue:input.queue};
	}
	
	RenderingStartup = function()
	{
		this.rendering = [];
		this.rendering.autoFrame = true;
		this.rendering.reverse = false;
		this.rendering.framerate = 24;
		this.rendering.currentFrame = 0;
		this.rendering.currentAnimation = "null";
		var backup = this;
		this.rendering.update = function(animName,frame)
		{
			backup.rendering.currentFrame = frame;
			backup.rendering.currentAnimation = animName;
		}
		this.rendering.nextFrame = function()
		{
			if(backup.rendering.currentFrame +1 >= backup.data.image[backup.rendering.currentAnimation].length)
				 backup.rendering.currentFrame = 0;
			else
				backup.rendering.currentFrame += 1;
		}
		this.rendering.previousFrame = function()
		{
			if(backup.rendering.currentFrame -1 < 0)
				 backup.rendering.currentFrame = backup.data.image[backup.rendering.currentAnimation].length-1;
			else
				backup.rendering.currentFrame -= 1;
		}
		//rendering function
		this.rendering.render = function()
		{
			image(data.image[this.currentAnimation][this.currentFrame],backup.current.x, backup.current.y, backup.current.w, backup.current.h);
			
			if(this.autoFrame && (frameCount) % ceil(round(frameRate())/this.framerate) == 0)
			{
				if(this.reverse)
					this.previousFrame();
				else
					this.nextFrame();
			};
		}
	}

	TextStartup = function()
	{
		this.text = [];
		this.text.currentFont = data.font[0];
		this.text.fontSize = 12;
		this.text.canSay = true;
		this.text.msg = "";
		this.text.defaultTime = 2;
		this.text.framesLeft = 0;
		var backup = this;
		this.text.say = function(inputmsg,inputframes)
		{
			if(backup.text.canSay == false )
				return {};
			else if(inputmsg)
			{
				if(!inputframes)
					this.framesLeft = this.defaultTime * frameRate();
				else
					this.framesLeft = inputframes * frameRate();
				this.msg = inputmsg;
				return {};
			}
			else
				if(this.framesLeft > 0)
				{
					noStroke();
					fill("black");
					textFont(this.currentFont);
					textSize(this.fontSize);
					text(this.msg,backup.current.x-(((this.fontSize)*this.msg.length)/8)-1 ,backup.current.y-2);
					this.framesLeft--;
					if(this.framesLeft <= 0)
						this.msg = '';
				}
		}
	}
	
	constructor(name,type,inresma,indata) 
	{
		//check if custom resma/data provided
		if(inresma)
			this.resma = inresma;
		else
			this.resma = resma;
		if(indata)
			this.data = indata;
		else
			this.data = data;

		//check if a object with same name exists, 
		//if it exists constructor will return a empty object
		for(let i = 0;i < this.resma.length;i++)
			if(this.resma[i].name === name)
			{
				console.log(name + " Already exists.");
				return {};
			}
		this.current = new Position(0,0,0,0);
		this.target = new Position(0,0,0,0);
		//starts all text stuff for this folha
		this.TextStartup();
		
		//starts all rendering stuff for this folha
		this.RenderingStartup();

		//not-playable types check
		if(dic.living.includes(type))
			this.playable = true;
		else
			this.playable = false;

		if(!dic.living.includes(type))
		{
			this.target = this.current; 
		}
		
		//Collision types check
		if(dic.static.includes(type))
			this.collision = "static";
		else if(dic.none.includes(type))
			this.collision = "none";
		else
			this.collision = "free";
		
		this.name = name;
		this.type = type;

		this.current.xywh(0,0,0,0);
		this.speed = 1;
		this.resma.push(this);
	}
}