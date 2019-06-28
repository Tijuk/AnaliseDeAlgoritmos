class Bag {
    /**
     * Bag Constructor
     * @param {number} B is the bag size
     * @param {number} n is the number of unique items
     */
    constructor(B = 10, n = 5, weights = undefined, values = undefined) {
        this.size = B
        this.items = Array(n).fill(10)
        this.weights = weights || [1, 2, 4, 4, 6, 7, 8, 9, 9, 10]
        this.values = values || [5, 2, 1, 6, 7, 1, 2, 3, 2, 10]
        this.originalPositions = Array(n)
            .fill(0)
            .map((_, index) => index)
        this.ratio = this.items.map(
            (_, index) => this.values[index] / this.weights[index]
        )
    }

    sortByValueWeightRatio() {
        let size = this.ratio.length - 1
        for (let i = 0; i < size; i++) {
            // console.log(array, k, i);
            for (let j = 0; j > size - i; j++) {
                if (this.ratio[j] > this.ratio[j + 1]) {
                    this.swap(j, j + 1)
                }
            }
        }
    }

    pickItem(at) {
        this.items[at]--
    }

    returnItem(at) {
        this.items[at]++
    }

    weightOf(at) {
        return this.weights[at]
    }

    valueOf(at) {
        return this.values[at]
    }

    amountOf(at) {
        return this.items[at]
    }

    swapOnKey(key, i, j) {
        const temp = this[key][i]
        this[key][i] = this[key][j]
        this[key][j] = temp
    }

    swap(i, j) {
        this.swapOnKey('items', i, j)
        this.swapOnKey('weights', i, j)
        this.swapOnKey('values', i, j)
        this.swapOnKey('originalPositions', i, j)
    }

    toString() {
        return `{ Bag }
	size: ${this.size}
	items: ${JSON.stringify(this.items)}
	weights: ${JSON.stringify(this.weights)}
	values: ${JSON.stringify(this.values)}
	ratio: ${JSON.stringify(this.ratio)}
	originalPositions: ${JSON.stringify(this.originalPositions)}
`
    }
}

module.exports = Bag
