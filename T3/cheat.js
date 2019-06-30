function findBestPack(data, bagSize) {
    var totalValue = [[0]] // maximum pack value found so far
    var bestCombSoFar = [[0]] // best combination found so far
    var OPT = [0] // item index for 0 of item 0
    var encode = [1] // item encoding for 0 of item 0
    var choose = 0
    for (var j = 0; j < data.length; j++) {
        OPT[j + 1] = OPT[j] + data[j].pieces // item index for 0 of item j+1
        encode[j + 1] = encode[j] * (1 + data[j].pieces) // item encoding for 0 of item j+1
    }
    for (var j = 0; j < OPT[data.length]; j++) {
        totalValue[0][j + 1] = bestCombSoFar[0][j + 1] = 0 // best values and combos for empty pack: nothing
    }
    for (var w = 1; w <= bagSize; w++) {
        totalValue[w] = [0]
        bestCombSoFar[w] = [0]
        for (var j = 0; j < data.length; j++) {
            var maxItemCount = data[j].pieces // how many of these can we have?
            var itemIndexForZero = OPT[j] // what is the item index for 0 of these?
            for (var n = 1; n <= maxItemCount; n++) {
                var totalWeightOfItems = n * data[j].weight // how much do these items weigh?
                var canCarry = w >= totalWeightOfItems ? 1 : 0 // can we carry this many?
                var totalValueOfItems = canCarry * n * data[j].value // how much are they worth?
                var itemsNumber = itemIndexForZero + n // what is the item number for this many?
                var wN = w - canCarry * totalWeightOfItems // how much other stuff can we be carrying?
                var C = n * encode[j] + bestCombSoFar[wN][itemIndexForZero] // encoded combination
                totalValue[w][itemsNumber] = Math.max(
                    totalValue[w][itemsNumber - 1],
                    totalValueOfItems + totalValue[wN][itemIndexForZero]
                ) // best value
                choose = bestCombSoFar[w][itemsNumber] =
                    totalValue[w][itemsNumber] > totalValue[w][itemsNumber - 1]
                        ? C
                        : bestCombSoFar[w][itemsNumber - 1]
            }
        }
    }
    var best = []
    for (var j = data.length - 1; j >= 0; j--) {
        best[j] = Math.floor(choose / encode[j])
        choose -= best[j] * encode[j]
    }
    return best
}

module.exports = findBestPack

// function findBestPack(data, bagSize) {
//     var totalValue = [[0]] // maximum pack value found so far
//     var bestCombSoFar = [[0]] // best combination found so far
//     var OPT = [0] // item index for 0 of item 0
//     var encode = [1] // item encoding for 0 of item 0
//     var choose = 0
//     for (var j = 0; j < data.length; j++) {
//         OPT[j + 1] = OPT[j] + data[j].pieces // item index for 0 of item j+1
//         encode[j + 1] = encode[j] * (1 + data[j].pieces) // item encoding for 0 of item j+1
//     }
//     for (var j = 0; j < OPT[data.length]; j++) {
//         totalValue[0][j + 1] = bestCombSoFar[0][j + 1] = 0 // best values and combos for empty pack: nothing
//     }
//     for (var w = 1; w <= bagSize; w++) {
//         totalValue[w] = [0]
//         bestCombSoFar[w] = [0]
//         for (var j = 0; j < data.length; j++) {
//             var N = data[j].pieces // how many of these can we have?
//             var itemIndexForZero = OPT[j] // what is the item index for 0 of these?
//             for (var n = 1; n <= N; n++) {
//                 var totalWeightOfItems = n * data[j].weight // how much do these items weigh?
//                 var canCarry = w >= totalWeightOfItems ? 1 : 0 // can we carry this many?
//                 var totalValueOfItems = canCarry * n * data[j].value // how much are they worth?
//                 var itemsNumber = itemIndexForZero + n // what is the item number for this many?
//                 var wN = w - canCarry * totalWeightOfItems // how much other stuff can we be carrying?
//                 var C = n * encode[j] + bestCombSoFar[wN][itemIndexForZero] // encoded combination
//                 totalValue[w][itemsNumber] = Math.bagSize(totalValue[w][itemsNumber - 1], totalValueOfItems + totalValue[wN][itemIndexForZero]) // best value
//                 choose = bestCombSoFar[w][itemsNumber] = totalValue[w][itemsNumber] > totalValue[w][itemsNumber - 1] ? C : bestCombSoFar[w][itemsNumber - 1]
//             }
//         }
//     }
//     var best = []
//     for (var j = data.length - 1; j >= 0; j--) {
//         best[j] = Math.floor(choose / encode[j])
//         choose -= best[j] * encode[j]
//     }
//     var wgt = 0
//     var val = 0
//     for (var i = 0; i < best.length; i++) {
//         if (0 == best[i]) continue
//         wgt += best[i] * data[i].weight
//         val += best[i] * data[i].value
//     }
//     return best
// }

// module.exports = findBestPack
