const samples = [
    {
        // 0
        B: 8,
        n: 2,
        weights: [3, 2],
        values: [2, 1],
        solution: [2, 1],
    },
    {
        // 1
        B: 50,
        n: 3,
        weights: [10, 20, 30],
        values: [60, 100, 120],
        solution: [5, 0, 0],
    },
    {
        // 2
        B: 22,
        n: 2,
        weights: [2, 1],
        values: [5, 1],
        solution: [10, 2],
    },
    {
        // 3
        B: 269,
        n: 10,
        weights: [55, 10, 47, 5, 4, 50, 8, 61, 85, 87],
        values: [95, 4, 60, 32, 23, 72, 80, 62, 65, 46],
        solution: [4, 4, 0, 1, 1, 0, 0, 0, 0, 0],
    },
    {
        // 4
        B: 878,
        n: 20,
        weights: [
            44,
            46,
            90,
            72,
            91,
            40,
            75,
            35,
            8,
            54,
            78,
            40,
            77,
            15,
            61,
            17,
            75,
            29,
            75,
            63,
        ],
        values: [
            92,
            4,
            43,
            83,
            84,
            68,
            92,
            82,
            6,
            44,
            32,
            18,
            56,
            83,
            25,
            96,
            70,
            48,
            14,
            58,
        ],
        solution: [10, 9, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    },
    {
        // 5
        B: 20,
        n: 4,
        weights: [9, 11, 13, 15],
        values: [6, 5, 9, 7],
        solution: [2, 0, 0, 0],
    },
    {
        // 6
        B: 11,
        n: 4,
        weights: [6, 10, 12, 13],
        values: [2, 4, 6, 7],
        solution: [1, 0, 0, 0],
    },
    {
        // 7
        B: 60,
        n: 10,
        weights: [20, 18, 17, 15, 15, 10, 5, 3, 1, 1],
        values: [30, 25, 20, 18, 17, 11, 5, 2, 1, 1],
        solution: [3, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    },
    {
        // 8
        B: 50,
        n: 7,
        weights: [70, 20, 39, 37, 7, 5, 10],
        values: [31, 10, 20, 19, 4, 3, 6],
        solution: [0, 2, 0, 0, 1, 0, 0],
    },
    {
        // 9
        B: 80,
        n: 5,
        weights: [33, 24, 36, 37, 12],
        values: [15, 20, 17, 8, 31],
        solution: [2, 0, 0, 0, 1],
    },
    {
        // 10
        B: 879,
        n: 20,
        weights: [
            91,
            72,
            90,
            46,
            55,
            8,
            35,
            75,
            61,
            15,
            77,
            40,
            63,
            75,
            29,
            75,
            17,
            78,
            40,
            44,
        ],
        values: [
            84,
            83,
            43,
            4,
            44,
            6,
            82,
            92,
            25,
            83,
            56,
            18,
            58,
            14,
            48,
            70,
            96,
            32,
            68,
            92,
        ],
        solution: [9, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    },
]

const examples = samples;

module.exports = {
    examples,
}
