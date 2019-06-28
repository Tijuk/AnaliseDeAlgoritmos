const Bag = require('./bag')
const Constants = require('./constants')
const Dynamic = require('./dynamic')
const Log = require('./log')

class Test {
    constructor() {
        this.enableLog = true
    }

    doTestOnExample(i) {
        const sample = Constants.examples[i]
        const bag = new Bag(sample.B, sample.n, sample.weights, sample.values)
        const dynamic = new Dynamic(bag)
        const result = dynamic.solve()
        let testSucceded = true
        sample.solution.some((value, index) => {
            if (result[index] !== value) {
                testSucceded = false
                return true
            }
        })
        if (testSucceded) {
            return true
        } else {
            return {
                expected: sample.solution,
                received: result,
            }
        }
    }

    doAllTests() {
        for (let i = 0; i < Constants.examples.length; i++) {
            Log.split()
            try {
                const result = this.doTestOnExample(i)
                if (result === true) {
                    if (this.enableLog) Log.success(`Test ${i}: succeded`)
                } else {
                    Log.error(`Test ${i}: failed`)
                    Log.error(`Expected: ${JSON.stringify(result.expected)}`)
                    Log.error(`Received: ${JSON.stringify(result.received)}`)
                }
            } catch (e) {
                Log.error(`Test ${i}: failed with error`)
                Log.catch(e)
                break
            }
        }
        Log.split()
    }
}

// Log.testColors()

module.exports = new Test()
