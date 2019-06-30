const Constants = require('./constants')
const Log = require('./log')
const Cheat = require('./cheat')

function max(a, b) {
    return a > b ? a : b
}

class Knapsack {
    constructor(bag) {
        this.bag = bag
        // this.cache = this.createMatrix()
        this.opt = new Array()
        this.opt[0] = 0
        this.encode = new Array()
        this.encode[0] = 1
        this.bag.items.forEach((_, index) => {
            const amount = this.bag.amountOf(index)
            this.opt[index + 1] = this.opt[index] + amount
            this.encode[index + 1] = this.encode[index] * (1 + amount)
        })
    }

    initTotalValuesAndCombos() {
        const size = this.opt[this.bag.items.length]
        const zeroValue = [0]
        const zeroCombo = [0]
        for (let i = 0; i < size; i++) {
            zeroValue[i + 1] = 0
            zeroCombo[i + 1] = 0
        }

        return {
            value: [zeroValue],
            combo: [zeroCombo],
        }
    }

    solve() {
        const total = this.initTotalValuesAndCombos()
        let choose = 0
        const solution = []
        for (let w = 0; w < this.bag.size; w++) {
            total.value[w] = [0]
            total.combo[w] = [0]
            for (let i = 0; i < this.bag.items.length; i++) {
                const itemIndexForZero = this.opt[i]
                new Array(10).fill(0).forEach((_, n) => {
                    const totalWeight = n * this.bag.weightOf(i)
                    const canCarry = w >= totalWeight ? 1 : 0
                    const totalValueOfItems = canCarry * n * this.bag.valueOf(i)
                    const itemNumber = itemIndexForZero + n
                    const wN = w - canCarry * totalWeight
                    const C =
                        n * this.encode[i] + total.combo[wN][itemIndexForZero]
                    console.log({
                        n,
                        encode: this.encode[i],
                        total: total.combo,
                    })
                    const a = total.value[w][itemNumber - 1]
                    const b =
                        totalValueOfItems + total.value[wN][itemIndexForZero]
                    console.log({
                        totalWeight,
                        canCarry,
                        totalValueOfItems,
                        itemNumber,
                        wN,
                        C,
                    })
                    total.value[w][itemNumber] = Math.max(a, b)
                    total.combo[w][itemNumber] =
                        total.value[w][itemNumber] > a
                            ? C
                            : total.combo[w][itemNumber - 1]
                    choose = total.combo[w][itemNumber]
                })
            }
        }
        for (let j = this.bag.items.length - 1; j >= 0; j--) {
            solution[j] = Math.floor(choose / this.encode[j])
            choose -= solution[j] * this.encode[j]
        }
        return solution
    }

    // createMatrix() {
    //     const C = this.bag.size
    //     const L = this.bag.items.length
    //     return Array(L)
    //         .fill(0)
    //         .map(() => Array(C).fill(0))
    // }

    // maxOf(i, j) {
    //     // const a = this.cache[cacheIndex]
    //     // const otherCacheIndex = cacheIndex - this.bag.weightOf(itemIndex)
    //     // const b = this.cache[otherCacheIndex] + this.bag.valueOf(itemIndex)
    //     // if (b == undefined) return a
    //     // if (a > b) {
    //     //     return a
    //     // } else {
    //     //     this.bag.pickItem(itemIndex)
    //     //     return b
    //     // }
    //     const a =
    //         this.bag.valueOf(i) +
    //         this.cache[i - 1][j - this.bag.weightOf(i - 1)]
    //     console.log(a)

    //     const b = this.cache[i - 1][j]
    //     return max(a, b)
    // }

    // opt(i, w) {
    //     const wi = this.bag.weightOf(i)
    //     const vi = this.bag.valueOf(i)
    //     if (i == 0) {
    //         return 0
    //     } else {
    //         if (this.cache[i - 1][w] == 0) {
    //             this.cache[i - 1][w] = this.opt(i - 1, w)
    //         }
    //         if (wi > w) {
    //             return this.cache[i - 1][w]
    //         } else {
    //             if (this.cache[(i - 1, w - wi)] == 0) {
    //                 this.cache[(i - 1, w - wi)] = this.opt(i - 1, w - wi)
    //             }
    //             return max(this.opt(i - 1, w), vi + this.cache[(i - 1, w - wi)])
    //         }
    //     }
    // }

    // opt(i, w) {
    //     if (i == 0) {
    //         return 0
    //     } else if (this.bag.weightOf(i) > w) {
    //         return this.opt(i - 1, w)
    //     } else {
    //         const a = this.opt(i - 1, w)
    //         const b =
    //             this.bag.valueOf(i) + this.opt(i - 1, w - this.bag.weightOf(i))
    //         // console.log(i, a, b)
    //         return max(a, b)
    //     }
    // }

    // solve() {
    //     const n = this.bag.items.length
    //     const W = this.bag.size
    //     let last = 0
    //     for (let i = 0; i < n; i++) {
    //         for (let w = 1; w < W; w++) {
    //             last = this.opt(i, w)
    //         }
    //     }
    //     Log.info(this.bag.toString())
    //     return last
    // }

    solveGreedy() {
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
                if (weightOf + tW > bagSize) {
                    break
                } else {
                    this.bag.pickItem(i)
                    tV += this.bag.valueOf(i)
                    tW += weightOf
                }
            }
        }
        // console.log({ tV, tW })
        return this.bag.items.map(remaining => 10 - remaining)
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
