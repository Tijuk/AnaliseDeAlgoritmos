function shuffle(array) {
  return array.sort(function() { return Math.random() - 0.5});
}

class Render {
	constructor() {
		this.steps = [];
		this.step = 0;
		this.container = document.getElementById('main');
		this.enabled = true;
	}

	disable() {
		this.enabled = false;
	}
	
	enable() {
		this.enabled = true;
	}
	
	
//	addStep(L,pivot,R, direction, k) {
//		if(this.enabled) {
//			console.log(L,pivot,R,direction);
//			this.steps.push(`<b>${++this.step}</b>: {k[${k}] - L[${L.length}] - R[${R.length}]} [ ${L.join(',')} ] [ <b><u>${pivot.join(',')}</u></b> ] [ ${R.join(',')} ] > <u>${direction}</u>`);
//		}
//	}
	
	addStep(L,pivot,R, direction, k, edge) {
		if(this.enabled) {
			//{e[${edge}] -  k[${k}] - L[${L.length}] - R[${R.length}]}<br>
//			console.log(L,pivot,R,direction);
			this.steps.push(`${++this.step}</b>: [ ${L.join(',')} ][ <b><u>${pivot}</u></b> ] [ ${R.join(',')} ] > <u>${direction}</u>`);
		}
	}

	result(value) {
		this.steps.push(`<h2><b>Resultado: ${value}</b></h2>`);
	}

	tab(size) {
		let ret = "";
		for(let i = 0; i < size; i++) {
			ret = ret + `\t`;
		}
		return ret;
	}

	reset() {
		this.steps = [];
		this.step = 0;
	}
	
	renderArray(array, level = 1) {
		if(typeof array == `object`) {
			if(!array[0]) return ``;
			if(typeof array[0] == `object`) {
				let ret = ``;
				array.forEach(e => {
					ret = ret + this.renderArray(e, 1);
				})
				return ret;
			}
			else {
				return `<div style="margin-left: ${level * 20}px;">[ ${array.join(`, `)} ]</div>`
			}
		}
	}

	multiRender(array) {
		let ret = '';
		array.forEach(e => {
			ret = ret + `\n<div class="step">${e}</div>`
		})
		return ret;
	}

	renderize() {
		let renderedArray = this.multiRender(this.steps);
		this.container.innerHTML = renderedArray;
	}
	
	resetError() {
		component.error.innerHTML = '';
	}
	
	error(message) {
		component.error.innerHTML = `
		<div class="errorMessage">
			<p>Error: ${message}</p>
		</div>
		`
	}
}

class Performance {
	constructor() {
		this.iterator = {
			linear: [],
			sort: []
		};
		this.lastIteraction = {
			linear: 0,
			sort: 0,
		};
		this.lastIteractionStart = {
			linear: 0,
			sort: 0,
		}
	}
	
	startTimerOn(iteraction, arraySize, selection) {
		const iter = this.iterator[selection];
		const size = arraySize - iter.length;
		if(!iter[iteraction]) {
			this.lastIteraction[selection] = 0;
			iter[iteraction] = [];
		}
		iter[iteraction].push({
			iteraction: this.lastIteraction[selection],
			arraySize,
			elapsedTime: 0,
		})
		this.lastIteractionStart[selection] = performance.now();
	}
	
	endTimer(iteraction, arraySize, selection) {
		const iter = this.iterator[selection];
		iter[iteraction][this.lastIteraction[selection]].elapsedTime = performance.now() - this.lastIteractionStart[selection];
		this.lastIteraction[selection]++;
	}
	
	result() {
		let a = {};
		Object.entries(this.iterator).forEach(([selection, iterator]) => {
			a[selection] = iterator.map( (iter) => {
				let sum = 0;
				iter.forEach(i => {
					sum += i.elapsedTime;
				})
				iter.unshift({
					iteraction: 'average',
					arraySize: iter[0].arraySize,
					elapsedTime: sum/10
				})
				//return iter;
				return {
					average: sum/10,
					arraySize: iter[0].arraySize
				}
			} )
		})
		return a;
	}
	
	randomArray(size, decimals = 2) {
		const pot = Math.pow(10,decimals);
		return Array.apply(null, Array(size)).map(i => Math.floor(Math.random() * 9 * pot)/pot);
	}
	
	arraysOf10randomArrays(from = 1000, to = 10000, decimals = 2) {
		const ret = [];
		if(from === 1000 && to === 10000) {
			for(let i = 0; i < constants.arraysPerRun; i++) {
				ret.push([]);
				for(let j = 0; j < 10; j++) {
					ret[i].push(this.randomArray((i+1)*(constants.arraySizeScale), decimals));
				}
			}
		} else {
			for(let i = from; i < to; i++) {
				ret.push([]);
				for(let j = 0; j < 10; j++) {
					ret[i-from].push(this.randomArray(i, decimals));
				}
			}
		}
		return ret;
	}
}


function intHalf(value) {
		return Math.floor(value/2);
	}

class Grid {
	constructor(array, peak, title) {
		this.max = peak
		this.array = array;
		this.title = title;
		this.scaling = 160;
	}
	
	createGrid() {
		let dis = this;
		let dots = this.array.map(function(v) { 
			let height = v/dis.max
			return dis.dot(height);
		}).join('');
		return `${this.title}<br><div class="gridContainer">${dots}</div>`;
	}
	
	dot(offset) {
		return `<div class="dot" style="margin-bottom: ${offset * this.scaling}px;"></div>`
	}
	
	scale
}


const render = new Render();