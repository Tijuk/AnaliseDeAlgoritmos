const Constants = require('./constants')
const Log = require('./log')
const Cheat = require('./cheat')

function max(a, b) {
    return a > b ? a : b
}

class Knapsack {
    constructor(bag) {
        this.bag = bag
        this.cache = this.createMatrix()
    }

    createMatrix() {
        const C = this.bag.size
        const L = this.bag.items.length
        return Array(L)
            .fill(0)
            .map(() => Array(C).fill(0))
    }

    maxOf(i, j) {
        // const a = this.cache[cacheIndex]
        // const otherCacheIndex = cacheIndex - this.bag.weightOf(itemIndex)
        // const b = this.cache[otherCacheIndex] + this.bag.valueOf(itemIndex)
        // if (b == undefined) return a
        // if (a > b) {
        //     return a
        // } else {
        //     this.bag.pickItem(itemIndex)
        //     return b
        // }
        const a =
            this.bag.valueOf(i) +
            this.cache[i - 1][j - this.bag.weightOf(i - 1)]
        console.log(a)

        const b = this.cache[i - 1][j]
        return max(a, b)
    }

    solve() {
        const bagSize = this.bag.size
        const numberOfItems = this.bag.items.length
        this.bag.sortByValueWeightRatio()
        let tV = 0
        let tW = 0
        Log.info(bagSize)
        for (let i = 0; i < numberOfItems; i++) {
            const numberOfThatItem = this.bag.amountOf(i)
            for (let j = 0; j < numberOfThatItem; j++) {
                const weightOf = this.bag.weightOf(i)
                console.log(weightOf)
                if (weightOf + tV > bagSize) {
                    break
                } else {
                    console.log('else')
                    this.bag.pickItem(i)
                    tV += this.bag.valueOf(i)
                    tW += weightOf
                }
            }
        }
        return { tV, tW }
    }

    solve2() {
        const data = []
        this.bag.items.forEach((_, i) => {
            data.push({
                name: this.bag.items[i],
                weight: this.bag.weightOf(i),
                value: this.bag.valueOf(i),
                pieces: 10,
            })
        })
        console.log(Cheat(data, this.bag.size))
        return Cheat(data, this.bag.size)
        const B = this.bag.size
        const n = this.bag.items.length
        // for (let i = 0; i < B; i++) {
        // 	for (let j = 0; j < n; j++) {
        // 		const weightOfJ = this.bag.weightOf(j)
        // 		if (weightOfJ <= i) {
        // 			this.cache[i] = this.maxOf(i, j)
        // 		}
        // 	}
        // }
        const K = this.cache
        const val = this.bag.values
        const wt = this.bag.weights
        // console.log(val, wt)
        this.cache.forEach(a => Log.success(a))
        for (let i = 1; i < n; i++) {
            for (let j = 1; j < B; j++) {
                if (wt[i - 1] <= j) {
                    const a = val[i - 1] + K[i - 1][j - wt[i - 1]]
                    const b = K[i - 1][j]
                    K[i][j] = max(a, b)
                } else {
                    K[i][j] = K[i - 1][j]
                }
            }
        }
        Log.info(this.bag.toString())
        return this.cache[n - 1][B - 1]
    }
}

module.exports = Knapsack
