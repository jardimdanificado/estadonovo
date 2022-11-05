//------------------------------------------
//SISTEMA.FILE
//------------------------------------------
function fileStartup()
{
	let file = [];
	file.model = [];
	file.image = [];
	file.font = [];
	
	file.model.getAnimLength = function (folderpath) 
	{
		let lfile;
		let found = false;
		let index = 0;
		while (found == false) 
		{
			lfile = new File(folderpath + index);
			if (lfile.exists()) 
			{
				index++;
			}
	
			else
				found = true;
		}
		return index;
	};
	file.model.load= function (filepath, iname) 
	{
		if (typeof filepath === 'object') 
		{
			if (iname) 
			{
				this[iname] = [];
				for (i = 0; i < filepath.length; i++) 
				{
					this[iname] = [];
					this[iname][filepath[i].split("/")[filepath[i].split("/").length - 1]] = [];
					for (k = 0; k < this.getAnimLength(filepath[i]); k++) 
					{
						this[iname][filepath[i].split("/")[filepath[i].split("/").length - 1]]
							.push(loadModel(filepath[i] + k + ".obj"));
					}
					this.push(this[iname]);
				}
			}
			else 
			{
				let lobj = [];
				for (i = 0; i < filepath.length; i++) 
				{
					lobj[filepath[i].split("/")[filepath[i].split("/").length - 1]] = [];
					for (k = 0; k < this.getAnimLength(filepath[i]); k++) 
					{
						lobj[filepath[i].split("/")[filepath[i].split("/").length - 1]]
							.push(loadModel(filepath[i] + k + ".obj"));
					}
				}
				this.push(lobj);
			}
		}
		else if (iname) 
		{
			this[iname] = loadModel(filepath);
			this.push(this[iname]);
		}
		else
			this.push(loadModel(filepath));
	};
	file.image.load = function (filepath, iname) 
	{
		if (typeof filepath === 'object') 
		{
			if (iname) 
			{
				this[iname] = [];
				for (i = 0; i < filepath.length; i++) 
				{
					this[iname] = [];
					this[iname][filepath[i].split("/")[filepath[i].split("/").length - 1]] = [];
					for (k = 0; k < this.getAnimLength(filepath[i]); k++) 
					{
						this[iname][filepath[i].split("/")[filepath[i].split("/").length - 1]]
							.push(loadModel(filepath[i] + k + ".png"));
					}
					this.push(this[iname]);
				}
			}
			else 
			{
				let lobj = [];
				for (i = 0; i < filepath.length; i++) 
				{
					lobj[filepath[i].split("/")[filepath[i].split("/").length - 1]] = [];
					for (k = 0; k < this.getAnimLength(filepath[i]); k++) 
						lobj[filepath[i].split("/")[filepath[i].split("/").length - 1]].push(loadModel(filepath[i] + k + ".png"));
				}
				this.push(lobj);
			}
		}
		else if (iname) 
		{
			this[iname] = loadImage(filepath);
			this.push(this[iname]);
		}
		else
			this.push(loadImage(filepath));
	}
	file.font.load = function (filepath, iname) 
	{
		if (iname) 
		{
			this[iname] = loadFont(filepath);
			this.push(this[iname]);
		}
		else
			this.push(loadFont(filepath));
	}
	return(file);
}
//------------------------------------------
//SISTEMA.WORLD
//------------------------------------------

function worldStartup()
{
	return
	({
		creature: [],
		plant: [],
		prop: [],
		item: []
	});
}

//------------------------------------------
//SISTEMA.RENDER
//------------------------------------------

function renderStartup()
{
	let render = [];
	render.scene = [];
	
	render.scene.background =
	{
		r: 1,
		g: 1,
		b: 1,
		a: 1
	};

	render.scene.model = [];
	render.scene.image = [];
	render.scene.text = [];
	render.scene.shape = [];
	
	render.scene.model.add = function(ref)
	{
		/*
	 	ref must follow this template:
	 	{
			name:'this model name',
			color:{r:0,g:0,b:0,a:0},
			position:{x:0,y:10,z:0},
			rotation:{x:180,y:180,z:0},
			scale:{x:10,y:10,z:10},
			model:sistema.file.model['model name'],
			texture:sistema.file.image['text name']//TEXTURE IS OPTIONAL
		}
		*/
		this[ref.name] = ref.model;
		this[ref.name].active = true;
		this[ref.name].color = ref.color;
		this[ref.name].position = ref.position; 
		this[ref.name].rotation = ref.rotation;
		this[ref.name].scale = ref.scale;
		if(ref.texture)
		{
			this[ref.name].texture = ref.texture;
		}
		this.push(this[ref.name]);
	}
	
	render.scene.text.add = function(ref)
	{
		/*
	 	ref must follow this template:
	 	{
			name:'this text name',
			color:{r:0,g:0,b:0,a:0},
			position:{x:0,y:10},
			fontSize:12,
	  		font:this.font['font name'],
			string:'this text content'
		}
		*/
		this[ref.name] = ref;
		this[ref.name].active = true;
		this.push(this[ref.name]);
	}
	
	render.scene.image.add = function(ref)
	{
		/* 	ref must follow this template:
	 	{
			name:'this image name',
			position:{x:0,y:10},
			rotation:{x:0,y:0},
			scale:{w:100,h:100},
			image:sistema.file.image['image name']
		}
		*/
		this[ref.name] = ref.image;
		this[ref.name].active = true;
		this[ref.name].position = ref.position; 
		this[ref.name].rotation = ref.rotation;
		this[ref.name].scale = ref.scale;
		this.push(this[ref.name]);
	}
	
	render.scene.shape.add = function(ref)
	{
		//ref must contains at least: name, color, position(vec2), scale(vec2 but use wh instead xy)
		/*
	 	ref must follow this template:
	 	{
			name:'this shape name',
			color:{r:0,g:0,b:0,a:0},
			position:{x:0,y:10},
			scale:{w:10,h:10},
			shape:circle//USE A REFERENCE TO A FUNCTION
		}
		*/
		this[ref.name] = ref;
		this[ref.name].active = true;
		this[ref.name].shape = ref.shape;
		this.push(this[ref.name]);
	}
	
	render.scene.render = function()
	{
		this.camera.setPosition(this.camera.position.x, this.camera.position.y, this.camera.position.z);
		clear(this.background.r,this.background.g,this.background.b,this.background.a);
		this.gfx.clear(this.background.r,this.background.g,this.background.b,this.background.a);
		noStroke();
		//MODEL RENDERING
		for(i=0;i<this.model.length;i++)
			if(this.model[i].active)
			{
				this.gfx.push(); // Start a new drawing state
				this.gfx.fill(this.model[i].color.r,this.model[i].color.g,this.model[i].color.b);
				this.gfx.translate(this.model[i].position.x, this.model[i].position.y, this.model[i].position.z);
				this.gfx.scale(this.model[i].scale.x, this.model[i].scale.y, this.model[i].scale.z);
				this.gfx.rotateX(this.model[i].rotation.x);
				this.gfx.rotateY(this.model[i].rotation.y);
				this.gfx.rotateZ(this.model[i].rotation.z);
				//strokeWeight(10);
				if(this.model[i].texture)
					this.gfx.texture(this.model[i].texture);
				this.gfx.model(this.model[i]);
				//console.log(this.model[i])
				this.gfx.pop();
			}
		//TEXT RENDERING
		for(i=0;i<this.text.length;i++)
			if(this.text[i].active)
			{
				this.gfx.push(); // Start a new drawing state
				this.gfx.fill(this.text[i].color.r,this.text[i].color.g,this.text[i].color.b,this.text[i].color.a);
				this.gfx.textFont(this.text[i].font);
				this.gfx.textSize(this.text[i].fontSize);
				this.gfx.textAlign(CENTER, CENTER);
				this.gfx.text(this.text[i].string, this.text[i].position.x, this.text[i].y);
				this.gfx.pop();
			}
		//IMAGE RENDERING
		for(i=0;i<this.image.length;i++)
			if(this.image[i].active)
				image(this.image[i], this.image[i].position.x, this.image[i].position.y, this.image[i].scale.w, this.image[i].scale.h);
		//SHAPE RENDERING
		for(i=0;i<this.shape.length;i++)
			if(this.shape[i].active)
			{
				fill(this.shape[i].color.r,this.shape[i].color.g,this.shape[i].color.b,this.shape[i].color.a);
				this.shape[i].shape(this.shape[i].position.x, this.shape[i].position.y, this.shape[i].scale.w, this.shape[i].scale.h);
			}
	}
	return render;
}
//------------------------------------------
//SISTEMA
//------------------------------------------

class Sistema
{
	title = "estado novo";
	screen = {w:windowWidth,h:windowHeight};
	vocabulary =
	{
		unplayable: ['wall','object','item','prop','door','furniture','tree','plant','other'],
		static: ['wall','door','tree'],
		free: ['plant','furniture','prop','item','object', ,'other'],
		none: ['appearence','ghost','visual','gas','effect','floor','tile'],
		living: ['player','creature','human']
	};
	file = fileStartup();
	world = worldStartup();
	render = renderStartup();

	canvas;
	gfx;
	setup = function()
	{
		this.canvas = createCanvas(sistema.screen.w, sistema.screen.h, P2D);//MAIN RENDERER USED FOR UI
		this.gfx = createGraphics(sistema.screen.w, sistema.screen.h, WEBGL);//SECONDARY RENDERER USED FOR ALL 3D STUFF, THIS IS RENDERED IN MAIN RENDERER AS A IMAGE
		this.render.scene.gfx = this.gfx;//reference to render be able to use 3D renderer
		this.render.scene.model.background = this.background;//scene background color
		//this applies NEAREST for all loaded images interpolation
		for(let i=0;i<this.file.image.length;i++)
			this.gfx._renderer.getTexture(this.file.image[i]).setInterpolation(NEAREST, NEAREST);
		this.gfx.perspective(PI / 3.0, sistema.screen.w / sistema.screen.h, 0.001, 1000);
		this.gfx.background(this.render.scene.background.r,this.render.scene.background.g,this.render.scene.background.b,this.render.scene.background.a);//this sets the 3D scene background color
		this.gfx.frameRate(60);//3D renderer framerate
		noCursor();//disable cursor in main renderer
		frameRate(60);//main renderer framerate
		this.gfx.angleMode(DEGREES);//set 3D renderer to use DEGREES instead RAD
		angleMode(DEGREES);
		this.render.scene.camera = this.gfx.createCamera();//create scene camera
		this.render.scene.camera.position = {x:0,y:0,z:0};//create scene camera position
		this.gfx.textureWrap(MIRROR,MIRROR);
		//this.render.scene.camera.setPosition(-8,-14,3);
		//this.render.scene.camera.lookAt(0, 0, 0);
	}
	constructor()
	{
		
	}
}