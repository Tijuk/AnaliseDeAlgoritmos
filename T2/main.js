
async function doOnce(i,result) {
	const perf = new Performance();
	const promise = new Promise((resolve) => {
		const arrays = perf.arraysOf10randomArrays();
		const linearSelect = new LinearSelection();
		const sortSelect = new SortSelection();
		const arraysLength = arrays.length;
		let k = 0;
		for(let i = 0; i < arraysLength; i++) {	
			const arrayOf10RandomArrays = arrays[i];
			const arrayOf10Length = arrayOf10RandomArrays.length
			for(let j = 0; j < arrayOf10Length; j++) {
				let copyOfArray = [];
				const randomArray = arrayOf10RandomArrays[j];
				const arraySize = randomArray.length;
				const halfSize = intHalf(arraySize);

				// * Linear Selection
				copyOfArray = [...randomArray];
				//console.log(copyOfArray, halfSize);
				perf.startTimerOn(i,arraySize,SelectionTypes.linear);
				const linearSmallest = linearSelect.findKthSmallest(copyOfArray,halfSize);
				perf.endTimer(i,arraySize, SelectionTypes.linear);
				// * Sort Selection
				
				copyOfArray = [...randomArray];
				perf.startTimerOn(i,arraySize, SelectionTypes.sort);
				const sortSmallest = sortSelect.findKthSmallest(copyOfArray, halfSize);
				perf.endTimer(i,arraySize, SelectionTypes.sort);
				
				if(sortSmallest != linearSmallest) {
					//console.error(sortSmallest,linearSmallest);
				}
				let sorted = copyOfArray.sort(function(a,b) {return a < b})
			}
		}
		resolve('');
	});

	await promise.then((value) => {
//		console.log(perf.result());
//		console.log(JSON.stringify(perf.result()));
//		console.log(value);
	})
	result[i] = perf.result();
	return result;
	
}

async function doStuffManyTimes() {
	let results = {}
	let numTests = constants.reRuns;
	const sum = {
		linear: [],
		sort: [],
	}
	for(let i = 0; i < numTests; i++) {
		console.log('Iteração: ' + (i+1));
		results = await doOnce(i,results);
		Object.keys(results).forEach(function(res) {
			let result = results[res];
			Object.keys(result).forEach(function(selection) {
				result[selection].forEach(function(inArray, index) {
					if(!sum[selection][index]) {
						sum[selection][index] = [];
					}
					sum[selection][index].push(inArray.average);
				})
			})
			
		});
	}
	sum.linear = sum.linear.map(function(value) {
		return value.reduce(function(a,b) {
			return a+b;
		 })/numTests;
	})
	sum.sort = sum.sort.map(function(value) {
		return value.reduce(function(a,b) {
			return a+b;
		 })/numTests;
	})
	const peak = Math.max(...sum.linear, ...sum.sort);
	console.log(sum);
	HTMLHelper.hide(component.loading);
	component.grid.innerHTML = ''
	let grid = new Grid(sum.linear, peak,'Linear');
	component.grid.innerHTML += (grid.createGrid());
	grid = new Grid(sum.sort, peak, 'Sort');
	component.grid.innerHTML += (grid.createGrid());
}

function handleStepClick() {
	try {
		render.reset();
		render.resetError();
		render.enable();
		const inputValue = component.steps_input_array.value;
		inputValue.split(',').forEach(i => {
			console.warn(i);
			console.warn(regex.isANumber(i));
			if(regex.isANumber(i)) {
				throw 'Invalid character found in [ array ]';
			}
		})
		console.clear();
		const array = inputValue.split(',').map(Number);
		if(k_raw.length > 0 && !RegExp(/\w/g).test(k_raw)) {
			throw 'Invalid character found in [ k ]';
		}
		const k = k_raw.length > 0 ? parseInt(k_raw,10)-1 : Math.ceil(array.length/2);
		if(k > array.length) {
			throw 'Parameter K is bigger than the array size';
		}
		if( k < 0) {
			throw 'Parameter K is negative. [Use 1 for first element]';
		}
		const linearSelect = new LinearSelection();
		const smallest = linearSelect.findKthSmallest(array, k);

		render.result(smallest);
		render.renderize();
		render.reset();
	} catch(error) {
		console.error(error);
		render.error(error);

	}	
}

function handlePerfButtonClick() {
	try{
		render.reset();
		HTMLHelper.show(component.loading);
		HTMLHelper.show(component.grid);
		HTMLHelper.hide(component.inputsContainer);
		render.disable();
		doStuffManyTimes();
		
    } catch(error) {
      	console.error(error);
		render.error(error);
    }
}


// const tester = new Test();
// tester.doAll();

window.onload = function() {
    component.steps_show.addEventListener('click', () => { 
		HTMLHelper.toggleVisibility(component.inputsContainer)
		HTMLHelper.resetGrid();
		HTMLHelper.hide(component.grid);
	});
	component.steps.addEventListener('click', handleStepClick);
	component.perfButton.addEventListener('click', handlePerfButtonClick)
}
