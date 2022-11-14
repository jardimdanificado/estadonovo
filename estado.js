//------------------------------------------
//SISTEMA
//------------------------------------------

function String2Matrix(input)
{
	let temp = input.split('\n');
	for(i=0;i<temp.length;i++)
		temp[i] = temp[i].split('');
	return(temp);
}

function Mapify(input)
{
	if(input.includes('//'))
	{
		let temp = input.split('//');
		let result = [];
		for(i=0;i<temp.length;i++)
			result.push(String2Matrix(temp[i]));
		return temp;
	}
	else
		return([String2Matrix(input)]);
}

function Refy(input)
{
	let temp = input.replace(' ','').split('\n');
	let result = [];
	for(i=0;i<temp.length;i++)
	{
		temp[i] = temp[i].split(':');
		result[temp[i][0]] = temp[i][1];
	}
	return(temp);
}

class Estado
{
	map;
	scene;
	constructor(input)
	{
		this.map = [];
		this.scene = [];
		this.scene.reference = [];
		this.scene.reference.add = function(input)
		{
			this.push(...input);
		}
		this.map.load = function(input)
		{
			if(typeof input == 'string')
			{
				let texto = {};
				fetch(input +'collision.txt')
					.then(response => response.text())
					.then(text => (texto.collision = Mapify(text)));
				fetch(input +'visual.txt')
					.then(response => response.text())
					.then(text => (texto.visual = Mapify(text)));
				fetch(input +'reference.txt')
					.then(response => response.text())
					.then(text => (texto.reference = Refy(text)));
				this.push(texto);
				this[input] = texto;
			}
			else
				for(let i=0;i<input.length;i++)
				{
					let texto = {};
					fetch('assets/map/' + input[i] + '.collision')
						.then(response => response.text())
						.then(text => (texto.collision = String2Matrix(text)));
					fetch('assets/map/' + input[i] + '.visual')
						.then(response => response.text())
						.then(text => (texto.visual = String2Matrix(text)));
					this.push(texto);
					this[input[i]] = texto;
				}
		}
		this.map.load(input);
		
	}
}