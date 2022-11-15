//------------------------------------------
//SISTEMA
//------------------------------------------

class Estado
{
	map;
	scene;
	constructor(input)
	{
		this.map = {};
		this.map = [];
		this.scene = [];
		this.scene.reference = [];
		this.scene.grid = [];
		this.scene.grid = {size:{w:0,h:0}};
		let tempbackup = this;

		this.setup = function()
		{
			//Retry will wait the specified ms before executing the function the first time
			//so keep that in mind when using it, NEVER use Retry() for immediate needs
			Retry(this.scene.setMap,!this.map[0],100,this.map[0]);//retry setMap(),while !estado.map[0] each 1000 milliseconds, the last arg stands for the args for the function, totally optional
		}
		
		this.scene.setMap = function(map)
		{
			console.log(tempbackup)
			tempbackup.grid = [];
			tempbackup.grid.size = {x:map.map[0][0].length,y:map.map[0].length,z:map.map.length};
			//console.log(map)
			for(let zz = 0;zz<tempbackup.grid.size.z;zz++)
			{
				tempbackup.grid[zz] = [];
				for(let yy = 0;yy<tempbackup.grid.size.y;yy++)
				{	
					tempbackup.grid[zz][yy] = [];
					for(let xx = 0;xx<tempbackup.grid.size.x;xx++)
					{	
						tempbackup.grid[zz][yy][zz] = [];
						tempbackup.grid[zz][yy][xx] = {...map.reference[map.map[zz][yy][xx]]};
					}
				}
			}
		}
		
		this.map._pushToList = function(json)
		{
			this[input.split('/')[input.split('/').length-1].split('.')[0]] = json;
			this.push(json);
			console.log(json)
			for(let i=0;i<json.map.length;i++)
				for(let k=0;k<json.map[i].length;k++)
					json.map[i][k] = json.map[i][k].split('');
		}
		
		this.map.load = function(input)
		{
			fetch(input).then(response => response.text()).then(text => this._pushToList(JSON.parse(text)));
		}

		this.map.load(input);
		//this.scene.setMap(this.map[0]);
	}
}