function intRandom() {
	return Math.floor(100*Math.random());
}

function floatRandom() {
	let pot = Math.pow(10,4);
	return Math.floor(Math.random() * 9 * pot)/pot;
}

class Test {
	constructor() {
		this.failed = [];
		this.suppressErrorMessage = false;
		const dis = this;
		this.cases = {
			test1: function() {
				dis.executeTest('test1', [0,0,0,0,0,0], 3);
			},
			test2: function() {
				dis.executeTest('test2', [0, 0, 1, 5, 9, 10, 10, 10, 12, 16, 19, 22, 27, 27, 29, 30, 31, 31, 34, 35, 39, 41, 44, 47, 48, 48, 49, 54, 56, 56, 56, 59, 60, 64, 66, 66, 71, 71, 72, 78, 78, 87, 88, 90, 90, 90, 93, 94, 99, 99], 25);
			},
			test3: function() {
				dis.executeTest('test3', [-3,-2,-1,0,1,2,3], 0);
			},
			test4: function() {
				dis.executeTest('test4', (new Array(100)).fill(0).map(intRandom), -1);
			},
			test5: function() {
				dis.executeTest('test5', (new Array(100)).fill(0).map(floatRandom), -1);
			},
			test6: function() {
				dis.executeTest('test6', (new Array(10000)).fill(0).map(floatRandom), -1);
			},
			test7: function() {
				for(let i = 0; i< 10; i++) {
					dis.executeTest('test7', (new Array(10000)).fill(0).map(floatRandom), -1);
				}
				
			}
		}
	}
	
	suppress() {
		this.suppressErrorMessage = false;
	}
		
	doTest(key) {
		if(this.cases[key]) {
//			console.time(key);
			//console.log(`Running test ${key}`);
			this.cases[key]();
//			console.timeEnd(key);
		} else {
			console.error(`Test ${key} not found`);
		}
	}
	
	doAll() {
		this.failed = [];
		let dis = this;
		Object.keys(this.cases).forEach(function(key) {dis.doTest(key)});
		if(this.failed.length > 0) {
			console.error('Some tests failed', this.failed);
		} else {
			console.log('All tests ran sucessfully');
		}
	}

	executeTest(key, array, k) {
		let pos = k > 0 ? k : Math.floor(array.length/2);
		let linear = new LinearSelection();
		let sort = new SortSelection();
		let l = linear.findKthSmallest([...array], pos);
		let s = sort.findKthSmallest([...array], pos);
		// console.log(key, {array : array.sort(function(a,b){return a-b}), key, l,s, pos});
//		console.log(array);
		if(l !== s) {
			if(!this.suppressErrorMessage) {
				console.error(`Test ${key} failed with values L=[${l}] and S=[${s}]`);
			}
			this.failed.push(key);
		}
	}
}