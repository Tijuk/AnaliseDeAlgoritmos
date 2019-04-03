var render = new Render();

var container = document.getElementById('container');


const original = [75,36,79,27,96,25,20,81,29,20,-1,-7,9,70,52,49,7,1,0];

function bubbleSort(array) {

}

function sorted(array) {
	if(array.length > 1) {
		const pivot = array[0];
		const L = [];
		const R = [];
		for(let i = 1; i < array.length; i++) {
			let pushAr = (array[i] < pivot) ? L : R;
			pushAr.push(array[i]);
		}
		return sorted(L).concat(pivot).concat(sorted(R));
	} else {
		return array;
	}
}

function chunkify(arr, chunkSize = 5) {
	const chunks = [];
	for(let i = 0; i < arr.length; i++) {
		const chunkIndex = Math.floor(i/chunkSize);
		if(!chunks[chunkIndex]) {
			chunks.push([]);
		}
		chunks[chunkIndex].push(arr[i]);
		if(i%chunkSize == 0 || arr.length - i == 1) {
			// (chunkSize)th element of chunk || last element in array
			if(chunks[chunkIndex])
			chunks[chunkIndex] = sorted(chunks[chunkIndex]);
		}
	}
	return chunks;
}



function MedOfMed(array, chunkSize = 5) {
	const chunk = chunkify(array);
	let MOM = [];
	// console.log(chunk);
	const arraySize = array.length;
	for(let i = 0; i < arraySize/chunkSize; i++) {
		// console.log(i, chunk[i], Math.ceil((chunk[i].length - 1)/2), chunk[Math.ceil((chunk[i].length-1)/2)]);
		MOM.push(chunk[i][Math.ceil((chunk[i].length-1)/2)]);
	}
	MOM = sorted(MOM);
	const index = Math.ceil((MOM.length-1)/2)
	if(MOM[index]) {
		console.warn(MOM, index);
	}
	return MOM[index]
}

//console.log(chunk(original,5).map(e => sorted(e)));

function findKth(array, k) {
	if(array.length == 0) {
		steps = 0;
		return 0;
	}
	
	// console.log(array, k);
	const pivot = MedOfMed(array);
	const L = [];
	const R = [];
	for(let i = 0; i < array.length; i++) {
		if(array[i] < pivot) {
			L.push(array[i]);
		}
		if(array[i] > pivot) {
			R.push(array[i]);
		}
	}
	
	if(L.length == k - 1) {
		render.addStep(L,pivot,R, 'Fim');
		return pivot;
	} 
	if(L.length > k - 1) {
		render.addStep(L,pivot,R, 'Esquerda');
		return findKth(L, k);
	}
	if(L.length < k - 1) {
		render.addStep(L,pivot,R, 'Direita');
		return findKth(R, k - L.length - 1);
	}
}

// render.result(findKth(original, 3));

// render.renderize();

const input = document.getElementById('input');
const valorDeK = document.getElementById('input2');

document.getElementById('button').onclick = () => {
	const array = input.value.split(',').map(Number);
	const k = parseInt(valorDeK.value,10);
	render.result(findKth(array,k));
	render.renderize();
	render.reset();
}