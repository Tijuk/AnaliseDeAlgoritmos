#ifndef __KNAPSACK__H_
#define __KNAPSACK__H_

#include "constants.h"
#include "bag.h"


struct __knapsack {
	int* combo;
	int value;
};

typedef struct __knapsack Knapsack;

Knapsack _10knapsack(Bag bag);

#endif