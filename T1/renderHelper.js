class Render {
	constructor() {
		this.steps = [];
		this.step = 0;
		this.container = document.getElementById('main');
	}

	addStep(L,pivot,R, direction) {
		this.steps.push(`<b>${++this.step}</b>: [ ${L.join(',')} ] [ <b><u>${pivot}</u></b> ] [ ${R.join(',')} ] > <u>${direction}</u>`);
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
}

class Performance {
  constructor() {
    this.iterator = {};
  }
  
  iterOn(key) {
    if(!this.iterator[key]) {
      this.resetKey(key) = 0;
    }
    this.iterator[key]++;
  }
  
  resetKey(key) {
    this.iterator[key] = 0;
  }
  
  result() {
    return this.iterator;
  }
}
