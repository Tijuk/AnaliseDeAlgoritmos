class GenericSelection {
	constructor() {
		this.iteractions = 0;
	}
}

class LinearSelection extends GenericSelection{
	
	swapWithNext(array, at) {
		let temp = array[at];
		array[at] = array[at+1];
		array[at+1] = temp;
	}
	
	sort(chunk) {
		const chunkLength = chunk.length;
		for(let i = 0; i < chunkLength - 1; i++) {
			for(let j = i; j < chunkLength; j++) {
				if(chunk[i] > chunk[j]) {
					this.swapWithNext(chunk, i);
				}
			}
		}
	}
	
	chunkification(arr, from, to) { // O(|from-to|) + O(|from-to|²) => O(1)
		let chunk = [];
		for(let i = from; i < to; i++) {
			if(i >= arr.length) { // if chunk ends prematurly
				break;
			}
			chunk.push(arr[i]);
		}
		this.sort(chunk); // O(|from-to|²) => O(1)
		return chunk;
	}


	
	MedOfMed(array, chunkSize = 5) { // O(n)
		let MOM = [];
		const arraySize = array.length;
		for(let i = 0; i < arraySize/chunkSize; i++) { // i =  0 .. n/5 = 
			const chunk = this.chunkification(array, i, i+chunkSize); // i = 0 .. 5² => O(1)
			MOM.push(chunk[Math.ceil((chunk.length-1)/2)]);
		}
		const index = Math.ceil((MOM.length-1)/2)
		this.sort(MOM); // i = 0 .. n/5 => O(n/5)
		return MOM[index];//this.sorted(MOM)[index]
	}

	findKthSmallest(array, k) {
		if(this.iteractions > 10000000) {
			throw "Stuck in loop"
		}
		if(array.length == 1) {
			render.addStep([], array[0], [], 'fim', k, k);
			return array[0];
		}
		if(array.length < 1) {
			const message = `LinearSort: Empty array found`;
			console.error(message);
			throw message;
		}
		if(array.length < k) {
			const message = (`LinearSort: Array's Size is smaller than K [Ar: ${array.length}, K: ${k}]`);
			console.error(message);
			throw message;
		}

		const pivot = this.MedOfMed(array);
		let nPivots = -1;
		let pivots = [];
		const L = [];
		const R = [];
		for(let i = 0; i < array.length; i++) { // 1 .. n
			if(array[i] < pivot) {
				L.push(array[i]);
			} else if(array[i] > pivot) {
				R.push(array[i]);
			} else {
				if(nPivots >= 0) {
					pivots.push(array[i]);
				}
				nPivots++;

			}
		}
		let edge = k - nPivots;
		const L_size = L.length;
//		console.log({cond1: { value: (L_size + nPivots) > k, L_size, nPivots, Lsize_plus_nPivots: L_size + nPivots, k_1: k}, cond2: {value: L_size <= k, L_size, k_m1: k}});
//		console.warn({L_size, edge});
		if((L_size + nPivots) > k && L_size <= k) {
//			console.warn(L_size + nPivots, k+1,L_size, k);
//		   	console.log(L,pivot,R,'fim2');
			render.addStep(L, pivot, R, 'fim2', k, edge);
			return pivot; // O(1)
		}
		if(L_size == edge) {
//			console.log(L,pivot,R,'fim');
			render.addStep(L, pivot, R, 'fim', k, edge);
			return pivot; // O(1)

		} 
		else if(L_size > edge) {
			if(L_size <= 0) {
				render.addStep(L, pivot, R, 'fim3', k, edge);
				return pivot;
			}
			render.addStep(L, pivot, R, 'esquerda', k, edge);
			return this.findKthSmallest(L, k);
		}
		else if(L_size < edge) {
			render.addStep(L, pivot, R, 'direita', k, edge);
			return this.findKthSmallest(R, k - (L_size) - nPivots - 1);
		} else {
//			console.log({array, L,R,L_size, Llength: L.length, edge, k});
			console.error('glitch in the matrix');
		}
	}
	
}

class SortSelection extends GenericSelection{

	swapWithNext(array, i) {
	  let temp = array[i];
	  array[i] = array[i+1];
	  array[i+1] = temp;
	}

	bubbleSort(array) {
		let updates = 1;
		let size = array.length;
		while(updates !== 0) {
			updates = 0;
			for(let i = 0; i < size - 1; i++) {
				if(array[i] > array[i+1]) {
					this.swapWithNext(array, i,i+1)
					updates++;
				}
			}
			size--;
		}
		return array;
	}
	
	findKthSmallest(array, k) {
//		console.log(array);
		return this.bubbleSort(array)[k];
	}
}
