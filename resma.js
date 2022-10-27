//resma.js is the eutimia's engine

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
//LIST
//------------------------------------------

var list = [];
list.action = [];
list.action.pending = [];
list.action.delete = function(unwanted)
{
	if(!isNaN(unwanted))
		unwanted = list.action.pending[unwanted];
	list.action.pending = list.action.pending.filter(function(item){return item !== unwanted;});
}
list.action.new = function(nAct,nData)
{
	list.action.pending.push({func:nAct,data:nData});
	console.log()
}
list.action.clear = function()
{
	list.action.pending = [];
}
list.action.solve = function(which)
{
	list.action.pending[which].func();
	list.action.pending.delete(which);
}
list.action.solveAll = function()
{
	for(i = 0;i < list.action.pending.length;i++)
		list.action.pending[i].func();
	list.action.clear();
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
	
	name;type;list;data;rendering;
	collision;// static,push,pull,free(push + pull),none
	x;y;w;h;speed;

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
				this.y = yy;
		if(typeof xx == 'number')
			this.x = xx;
	}
	
	Move = function(input)
	{
		let collisionFound = false;
		if(!input['queue'])
			input.queue = [];
		input.queue.push(this.name);
		
		let lposi =
		{
			x:this.x + input.x,
			y:this.y + input.y,
			h:this.h,
			w:this.w
		}
		for(i = 0; i < this.list.length;i++)
			if (Check2DCollision(lposi,this.list[i]) && !input.queue.includes(this.list[i].name))
			{
				collisionFound = true;
				if(this.list[i].collision != "static")
				{
					if (this.list[i].collision == "none")
					{
						this.x += input.x;
						this.y += input.y;
						input = ({x:input.x,y:input.y,queue:input.queue});
					}
					else
						for(i = 0; i < this.list.length;i++)
							if(this.list[i].collision != "pull" && !input.queue.includes(this.list[i].name) && Check2DCollision(lposi,this.list[i]))
							{
								var lspeed = this.list[i].Move({x:input.x/2,y:input.y/2,queue:input.queue});
								if(lspeed.x != 0 || lspeed.y != 0)
								{
									this.x += lspeed.x/4;
									this.y += lspeed.y/4;
									input = lspeed;
								}
								else
									input = {x:0,y:0,queue:input.queue};
							}
					input = {x:(lspeed.x/2),y:(lspeed.y/2),queue:input.queue};
				}
				else
					input = {x:0,y:0,queue:input.queue};
			}
		if(!collisionFound)
		{
			this.x += input.x;
			this.y += input.y;
		}
		return {x:input.x,y:input.y,queue:input.queue};
	}
	
	RenderingStartup = function()
	{
		this.rendering = [];
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
	}

	render = function()
	{
		image(data.image[this.rendering.currentAnimation][this.rendering.currentFrame],this.x, this.y, this.w, this.h);
	}
	
	constructor(name,type,collision,inlist,indata) 
	{
		if(inlist)
			this.list = inlist;
		else
			this.list = list;
		
		if(indata)
			this.data = indata;
		else
			this.data = data;
		
		this.RenderingStartup();
		
		for(let i = 0;i < this.list.length;i++)
			if(this.list[i].name === name)
			{
				console.log(name + " Already exists.");
				return {};
			}
		this.name = name;
		this.type = type;
		this.collision = collision;
		if(type === "player" || type === "creature")
		{
			this.xywh(0,0,0,0);
			this.speed = 1;
		}
		else
		{
			this.xywh(0,0,0,0);
			this.speed = 0;
		}
		this.list.push(this);
	}
}