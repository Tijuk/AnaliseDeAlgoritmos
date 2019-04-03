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

const perf = new Performance();

function swapWithNext(array, i) {
  let temp = array[i];
  array[i] = array[i+1];
  array[i+1] = temp;
}

function bubbleSort(array) {
  let updates = 1;
  let size = array.length;
  while(updates !== 0) {
    updates = 0;
    for(let i = 0; i < size - 1; i++) {
      perf.iterOn('bubbleSort');
      if(array[i] > array[i+1]) {
        swapWithNext(array, i,i+1)
        updates++;
      }
    }
    size--;
  }
}
