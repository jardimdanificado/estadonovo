//------------------------------------------
//SISTEMA.FILE
//------------------------------------------

function fileStartup()
{
	let file = [];
	file.model = [];
	file.image = [];
	file.font = [];

	file.model.load= function (filepath, iname) 
	{
		if (typeof filepath === 'object') 
		{
			/*
   			when importing a animation
	 		ref must follow this template:
		 	{
				...['1','2','3','4','5','6','7'],
				name:'player-walk',
				ext:'.obj',
				path:'assets/models/player/walk/'
			}
			*/
			let lobj = [];
			let tempn = getLength(filepath);

			if(!filepath.ext)
				filepath.ext = '.obj';
			
			for (k = 0; k < tempn; k++)
			{
				lobj.push(loadModel(filepath.path + filepath[k] + filepath.ext));
				this.push(lobj[k]);
			}
			this[filepath.name] = lobj;
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
			/*
   			when importing a animation
	 		ref must follow this template:
		 	{
				...['1','2','3','4','5','6','7'],
				name:'player-walk',
				ext:'.obj',
				path:'assets/models/player/walk/'
			}
			*/
			let lobj = [];
			let tempn = getLength(filepath);

			if(!filepath.ext)
				filepath.ext = '.png';
			
			for (k = 0; k < tempn; k++)
			{
				lobj.push(loadImage(filepath.path + filepath[k] + filepath.ext));
				this.push(lobj[k]);
			}
			this[filepath.name] = lobj;
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
	let world = [];
	world.creature = [];
	world.plant = [];
	world.prop = [];
	world.item = [];

	world.creature.new = function(ref)
	{
		/*
	 	ref must follow this template:
	 	{
			name:'this creature name',
			color:{r:0,g:0,b:0,a:0},
			position:{x:0,y:10,z:0},
			rotation:{x:180,y:180,z:0},
			scale:{x:10,y:10,z:10},
			model:sistema.file.model['model name'],
			texture:sistema.file.image['text name']//TEXTURE IS OPTIONAL
		}
		*/
		
		if(!ref.age)
		{
			ref.age = 18;
		}
		if(!ref.speed)
		{
			ref.speed = 0.08;
		}

		ref.move = function(backwards)
		{
			if(this.rotation.y >= 360)
				this.rotation.y -= 360;
			else if(this.rotation.y < 0)
				this.rotation.y += 360;
			
			let  valorZ, valorX;
			let giro = (this.rotation.y / 90);
			let resto = this.rotation.y - (90 * Math.trunc(giro));
			let restodoresto = 90 - resto;
			
			if(backwards==false)
			{
				valorZ = this.speed - resto * (this.speed / 90);
				valorX = this.speed - (restodoresto * (this.speed / 90));
			}
			else
			{
				valorZ = (this.speed - resto * (this.speed / 90))*(-1);
				valorX = (this.speed - (restodoresto * (this.speed / 90)))*(-1);
			}
			
			if(giro>=3)
			{
				this.position.x -= valorZ;
				this.position.z -= valorX;
			}
			else if(giro>=2)
			{
				this.position.x -= valorX;
				this.position.z += valorZ;
			}
			else if(giro>=1)
			{
				this.position.x += valorZ;
				this.position.z += valorX;
			}
			else if(giro<1)
			{
				this.position.z -= valorZ;
				this.position.x += valorX;
			}
		}
		
		if(ref.name)
			world.creature[ref.name] = ref;
		
		world.push(ref);
	}
	
	return(world);
}

//------------------------------------------
//SISTEMA.RENDER
//------------------------------------------

function sceneStartup()
{
	let scene = [];
	scene.background =
	{
		r: 1,
		g: 1,
		b: 1,
		a: 1
	};

	scene.model = [];
	scene.image = [];
	scene.text = [];
	scene.shape = [];
	
	scene.model.add = function(ref)
	{
		/*
	 	ref must follow this template:
	 	{
			name:'this model name',
			color:{r:0,g:0,b:0,a:0},//COLOR IS OPTIONAL THE DEFAULT IS {r:0,g:255,b:0,a:255}
			position:{x:0,y:10,z:0},//POSITION iS OPTIONAL THE DEFAULT IS {x:0,y:0,z:0}
			rotation:{x:180,y:180,z:0},//ROTATION IS OPTIONAL THE DEFAULT IS {x:180,y:180,z:0}
			scale:{x:10,y:10,z:10},//SCALE S OPTIONAL THE DEFAULT IS {x:1,y:1,z:1}
			model:sistema.file.model['model name'],
			texture:sistema.file.image['text name']//TEXTURE IS OPTIONAL,
   			active: true, //active is optional DEFAULT IS TRUE
	  		visible: true // visible is optional DEFAULT IS TRUE
		}
		*/
		if(this[ref.name])
		{
			delete this[ref.name];
		}

		if(!ref.position)
			ref.position = {x:0,y:0,z:0};
		
		if(!ref.rotation)
			ref.rotation = {x:180,y:180,z:0};

		if(!ref.scale)
			ref.scale = {x:1,y:1,z:1};

		if(!ref.color)
			ref.color = {r:0,g:255,b:0,a:255};

		if(!ref.active)
			ref.active = true;

		if(!ref.visible)
			ref.visible = true;
		
		if(ref.model[0])
		{
			ref.currentFrame = 0;
			ref.currentProgression = 1;
		}

		ref.drawHitbox = function() 
		{
			scene.gfx.push();
	
			if(CheckCollisionBoxes(ref.hitbox,{min:{x:-2,y:-2,z:-2},max:{x:2,y:2,z:2}}))
			{
				console.log("colidiu");
			}
				
			scene.gfx.fill(0,255,0,100);
			scene.gfx.translate(this.hitbox.min.x,this.hitbox.min.y*(-1),this.hitbox.min.z);
			scene.gfx.box
			(
				0.1,0.1,0.1
			);
			scene.gfx.pop();
			
			scene.gfx.push();
			scene.gfx.translate(this.hitbox.max.x,this.hitbox.max.y*(-1),this.hitbox.max.z);
			scene.gfx.fill(255,0,0,100);
			scene.gfx.box
			(
				0.1,0.1,0.1
			);
			scene.gfx.pop();
		}
		
		ref.getHitbox = function()//this get the ref 
		{
			let tempb;
			
			if(!ref.model[0])
				tempb = (GetMeshBoundingBox(ref.model));
			else
				tempb = (GetMeshBoundingBox(ref.model[ref.currentFrame]))

			tempb.min = RotateVerticeSelf(this.rotation.y, tempb.min);
			tempb.max = RotateVerticeSelf(this.rotation.y, tempb.max);

			//if(tempb.min.x > tempb.max.x && tempb.min.y > tempb.max.y && tempb.min.z > tempb.max.z)
			tempb = {max:Vector3Max(tempb.min,tempb.max),min:Vector3Min(tempb.min,tempb.max)};
			tempb.min = Vector3Add(tempb.min,this.position);
			tempb.max = Vector3Add(tempb.max,this.position);
			return(tempb);
		}
		
		ref.updateHitbox = function()
		{
			let temp = this.getHitbox();
			hitbox.min = temp.min;
			hitbox.max = temp.max;
		}
		ref.hitbox = ref.getHitbox();
		
		this[ref.name] = ref;
		this.push(ref);
	}
	
	scene.text.add = function(ref)
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
	
	scene.image.add = function(ref)
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
		this[ref.name] = ref;
		this[ref.name].active = true;
		this.push(this[ref.name]);
	}
	
	scene.shape.add = function(ref)
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
	
	scene.render = function()
	{
		//CAMERA
		//this.camera.setPosition(this.camera.position.x, this.camera.position.y, this.camera.position.z);
 		if(frameCount%2000)//this just runs each 33 seconds
		{
			clear(this.background.r,this.background.g,this.background.b,this.background.a);
			this.gfx.clear(this.background.r,this.background.g,this.background.b,this.background.a);
			this.camera.update();
		}
		//MODEL RENDERING
		for(i=0;i<this.model.length;i++)
			if(this.model[i].active)
			{
				if(frameCount%floor(60/24)==0 || this.model[i].currentFrame > this.model[i].model.length)
				{
					if(this.model[i].model[0])//IF ANIMATED
					{
						if(this.model[i].currentFrame + this.model[i].currentProgression > this.model[i].model.length-1)
						{
							this.model[i].currentFrame = 0;
						}
						else if(this.model[i].currentFrame + this.model[i].currentProgression < 0)
						{
							this.model[i].currentFrame = this.model[i].model.length-1;
						}
						else
						{
							this.model[i].currentFrame += this.model[i].currentProgression;
						}
					}
				}
				
				this.gfx.push(); // Start a new drawing state
				this.gfx.translate(this.model[i].position.x, this.model[i].position.y, this.model[i].position.z);
				this.gfx.scale(this.model[i].scale.x, this.model[i].scale.y, this.model[i].scale.z);
				this.gfx.rotateX(this.model[i].rotation.x);
				this.gfx.rotateY(this.model[i].rotation.y);
				this.gfx.rotateZ(this.model[i].rotation.z);
				//strokeWeight(1);
				if(this.model[i].texture)
					this.gfx.texture(this.model[i].texture);
				else
					this.gfx.fill(this.model[i].color.r,this.model[i].color.g,this.model[i].color.b,this.model[i].color.a);
				
				if(!this.model[i].model.vertices)//IF ANIMATED
					this.gfx.model(this.model[i].model[this.model[i].currentFrame]);
				else 
					this.gfx.model(this.model[i].model);
				this.gfx.pop();

				if(this.model[i].hitbox)
				{
					this.model[i].drawHitbox();
					this.model[i].hitbox = this.model[i].getHitbox();
				}
				
				scene.gfx.box(4,4,4);//PLEASE REMOVE THIS
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
				image(this.image[i].image, this.image[i].position.x, this.image[i].position.y, this.image[i].scale.w, this.image[i].scale.h);
		//SHAPE RENDERING
		for(i=0;i<this.shape.length;i++)
			if(this.shape[i].active)
			{
				fill(this.shape[i].color.r,this.shape[i].color.g,this.shape[i].color.b,this.shape[i].color.a);
				this.shape[i].shape(this.shape[i].position.x, this.shape[i].position.y, this.shape[i].scale.w, this.shape[i].scale.h);
			}
	}
	return scene;
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
	scene = sceneStartup();
	
	//canvas
	canvas;//2D
	gfx;//3D
	
	setup = function()
	{
		this.canvas = createCanvas(sistema.screen.w, sistema.screen.h, P2D);//MAIN RENDERER USED FOR UI
		this.gfx = createGraphics(sistema.screen.w, sistema.screen.h, WEBGL);//SECONDARY RENDERER USED FOR ALL 3D STUFF, THIS IS RENDERED IN MAIN RENDERER AS A IMAGE
		this.scene.gfx = this.gfx;//reference to render be able to use 3D renderer
		this.scene.model.background = this.background;//scene background color
		//this applies NEAREST for all loaded images interpolation
		this.gfx.noSmooth();
		for(let i=0;i<this.file.image.length;i++)
			this.gfx._renderer.getTexture(this.file.image[i]).setInterpolation(NEAREST, NEAREST);
		this.gfx.perspective(PI / 3.0, sistema.screen.w / sistema.screen.h, 0.001, 1000);
		this.gfx.background(this.scene.background.r,this.scene.background.g,this.scene.background.b,this.scene.background.a);//this sets the 3D scene background color
		this.gfx.frameRate(60);//3D renderer framerate
		//noSmooth();
		
		noCursor();//disable cursor in main renderer
		frameRate(60);//main renderer framerate
		this.gfx.angleMode(DEGREES);//set 3D renderer to use DEGREES instead RAD
		angleMode(DEGREES);
		this.scene.camera = this.gfx.createCamera();//create scene camera
		this.scene.camera.position = {x:3,y:-10,z:10};//create scene camera position
		this.scene.camera.target = {x:0,y:0,z:0};//where the camera will look at
		this.scene.camera.update = function()
		{
			this.setPosition(this.position.x, this.position.y, this.position.z);
			this.lookAt(this.target.x,this.target.y,this.target.z);
		}
		this.scene.camera.update();
		this.gfx.textureWrap(CLAMP,CLAMP);	
		

	}
	constructor()
	{
		
	}
}