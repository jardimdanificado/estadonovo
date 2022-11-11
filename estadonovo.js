//------------------------------------------
//UTIL
//------------------------------------------

function getLength(input)
{
	let tempn=0;
	while(true)
	{
		if(input[tempn])
			tempn++;
		else
			return tempn;
	}
}

function deg2rad(angle)
{
	return(angle * PI/180);
}

function RotateVerticeSelf(angle, vertice)
{
    let NewVertice = {};
    NewVertice.y = vertice.y;
    NewVertice.x = vertice.x * cos(angle) - vertice.z * sin(angle);
    NewVertice.z = vertice.x * sin(angle) + vertice.z * cos(angle);
    return NewVertice;
}

function RotateVertice(pivot, angle, vertice)
{
    NewVertice = {};
    NewVertice.y = vertice.y;
    NewVertice.x = ((vertice.x - pivot.x) * cos(angle)) - ((vertice.z - pivot.z) * sin(angle)) + pivot.x;
    NewVertice.z = ((vertice.x - pivot.x) * sin(angle)) + ((vertice.z - pivot.z) * cos(angle)) + pivot.z;
    return NewVertice;
}

function range(min, max) 
{
	let arr = [];
	for (var i = min; i < max ; i++) 
	{
		arr.push(i+"");
	}
  return arr;
}

function Vector3Add(vec1,vec2)
{
	if(typeof vec2 === 'object')
		return({x:vec1.x+vec2.x,y:vec1.y+vec2.y,z:vec1.z+vec2.z});
	else
		return({x:vec1.x+vec2,y:vec1.y+vec2,z:vec1.z+vec2});
}

function Vector3Sub(vec1,vec2)
{
	if(typeof vec2 === 'object')
		return({x:vec1.x-vec2.x,y:vec1.y-vec2.y,z:vec1.z-vec2.z});
	else
		return({x:vec1.x-vec2,y:vec1.y-vec2,z:vec1.z-vec2});
}

function Vector3Div(vec1,vec2)
{
	if(typeof vec2 === 'object')
		return({x:vec1.x/vec2.x,y:vec1.y/vec2.y,z:vec1.z/vec2.z});
	else
		return({x:vec1.x/vec2,y:vec1.y/vec2,z:vec1.z/vec2});
}

function Vector3Mul(vec1,vec2)
{
	if(typeof vec2 === 'object')
		return({x:vec1.x*vec2.x,y:vec1.y*vec2.y,z:vec1.z*vec2.z});
	else
		return({x:vec1.x*vec2,y:vec1.y*vec2,z:vec1.z*vec2});
}

function Vector3Mod(vec1,vec2)
{
	if(typeof vec2 === 'object')
		return({x:vec1.x%vec2.x,y:vec1.y%vec2.y,z:vec1.z%vec2.z});
	else
		return({x:vec1.x%vec2,y:vec1.y%vec2,z:vec1.z%vec2});
}

function Vector3Min(v1, v2)
{
    let result = { x:0,y:0,z:0 };

    result.x = min([v1.x, v2.x]);
    result.y = min([v1.y, v2.y]);
    result.z = min([v1.z, v2.z]);

    return result;
}

// Get max value for each pair of components
function Vector3Max(v1,v2)
{
    let result = { x:0,y:0,z:0 };

    result.x = max([v1.x, v2.x]);
    result.y = max([v1.y, v2.y]);
    result.z = max([v1.z, v2.z]);
	//console.log (v1)
    return result;
}

function GetMeshBoundingBox(mesh)
{
    // Get min and max vertex to construct bounds (AABB)
    let minVertex = { x:0,y:0,z:0 };
    let maxVertex = { x:0,y:0,z:0 };

    if (mesh.vertices)
    {
        minVertex = mesh.vertices[0];
        maxVertex = mesh.vertices[0];
        for (let i = 1; i < mesh.vertices.length; i++)
        {
            minVertex = Vector3Min(minVertex, mesh.vertices[i]);
            maxVertex = Vector3Max(maxVertex, mesh.vertices[i]);
        }
    }
	//console.log(minVertex)
	//console.log(maxVertex)
    // Create the bounding box
    let box = {};
    box.min = minVertex;
    box.max = maxVertex;

    return box;
}

function CheckCollisionPointBox(point, box) 
{
	let result = 
	(
		point.x >= box.min.x &&
		point.x <= box.max.x &&
		point.y >= box.min.y &&
		point.y <= box.max.y &&
		point.z >= box.min.z &&
		point.z <= box.max.z
	);
	return(result);
}

function CheckCollisionBoxes(a, b) 
{
	let result =
	(
    	a.min.x <= b.max.x &&
	    a.max.x >= b.min.x &&
	    a.min.y <= b.max.y &&
	    a.max.y >= b.min.y &&
	    a.min.z <= b.max.z &&
	    a.max.z >= b.min.z
  	);
	return(result);
}

function move3D(position,rotation,speed)
{
	if(rotation.y >= 360)
		rotation.y -= 360;
	else if(rotation.y < 0)
		rotation.y += 360;
	
	let  valorZ, valorX;
	let giro = (rotation.y / 90);
	let resto = rotation.y - (90 * Math.trunc(giro));
	let restodoresto = 90 - resto;
	valorZ = speed - resto * (speed / 90);
	valorX = speed - (restodoresto * (speed / 90));
	
	if(giro>=3)
	{
		return{//if return is alone in a line it returns undefined
			x:position.x - valorZ,
			y:position.y,
			z:position.z - valorX
		}
	}
	else if(giro>=2)
	{
		return{		
			x:position.x - valorX,
			y:position.y,
			z:position.z + valorZ
		}
	}
	else if(giro>=1)
	{
		return{
			x:position.x + valorZ,
			y:position.y,
			z:position.z + valorX
		}
	}
	else if(giro<1)
	{
		return{		
			x:position.x + valorX,
			y:position.y,
			z:position.z - valorZ
		}
	}
}

//------------------------------------------
//KEYBOARD
//------------------------------------------

function keyDown()
{
	if (keyIsDown(LEFT_ARROW) || keyIsDown(65))
		player.rotation.y -= 6;
	if (keyIsDown(RIGHT_ARROW) || keyIsDown(68))
		player.rotation.y += 6;
	if (keyIsDown(DOWN_ARROW) || keyIsDown(83))
		if(player.boxCheckCollisions(move3D(player.position,player.rotation,player.speed)) === false)
			player.move(true);
	if (keyIsDown(UP_ARROW) || keyIsDown(87))
		if(player.boxCheckCollisions(move3D(player.position,player.rotation,player.speed*(-1))) === false)
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
			sistema.scene.camera.update();
	}
	else if (keyCode == 87 || keyCode == UP_ARROW ) //W
	{
		player.model = sistema.file.model['player-walk'];
		player.currentProgression = 1;
		if(frameCount%10)
			sistema.scene.camera.update();
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
	
	arrayTemporario = range(0,9);//PLEASE CHANGE THIS FROM 9 TO 10 TO INCLUDE THE FLOOR
	sistema.file.model.load
	({
		...arrayTemporario,
		name:'lvl0hitboxes',
		ext:'.obj',
		path:'assets/models/map/level0/hitbox/',
		visible: false
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
		position:{x:1,y:0,z:0},
		scale:{x:1,y:1,z:1},
		model:sistema.file.model['player-idle'],
		visible:true,
		collision: 'free'
	});
	
	player = sistema.world.creature['joao'];
	sistema.scene.camera.target = player.position;
	map = 
	{
		name:'mapa0',
		color:{r:0,g:0,b:0,a:0},
		position:{x:0,y:0,z:0},
		scale:{x:1,y:1,z:1},
		model:sistema.file.model['map0'],
		texture:sistema.file.image['map0'],
		visible:true,
		collision: 'none'//as this is only visual, no collision will be used
	}
	sistema.scene.model.add(map);
	sistema.scene.model.add(player);
	sistema.scene.model.addAllFrames(sistema.file.model['lvl0hitboxes']);
}

function draw() 
{
	sistema.gfx.clear();
	sistema.gfx.noStroke();
	keyDown();
	
	sistema.scene.render();
	image(sistema.gfx, 0, 0, sistema.screen.w, sistema.screen.h);
	
	//mouse
	push();
	stroke(0,0,0);
	strokeWeight(1);
	noFill();
	circle(mouseX,mouseY,6);
	pop();
	
}