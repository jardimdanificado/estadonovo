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