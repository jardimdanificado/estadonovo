//------------------------------------------
//CACHE
//------------------------------------------

var ___RWECACHE = [];

//------------------------------------------
//VECTOR3
//------------------------------------------

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

//------------------------------------------
//VERTICE
//------------------------------------------

function RotateVerticeSelf( angle, vertice)
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

//------------------------------------------
//UTILS
//------------------------------------------

function GetLength(input)
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

function RetryWhileEach(func,condition,ms,opt)
{
	let temp = {};
	temp.interval = setInterval(
		function() 
		{
			if(!condition)
			{
				if(typeof opt !== 'undefined')
					func(opt);
				else
					func();
				temp.stop();
				let index = ___RWECACHE.indexOf(temp);
				if (index > -1)
				  ___RWECACHE.splice(index, 1);
			}
		}, ms
	);
	
	temp.stop = function()
	{
		clearInterval(temp.interval);
	}

	___RWECACHE.push(temp);
}

function Retry(func,condition,ms,opt)//just a wrapper
{
	RetryWhileEach(func,condition,ms,opt)
}

function Range(min, max) 
{
	let arr = [];
	for (var i = min; i < max ; i++) 
	{
		arr.push(i+"");
	}
  return arr;
}

//------------------------------------------
//MATH
//------------------------------------------

function Deg2Rad(angle)
{
	return(angle * PI/180);
}