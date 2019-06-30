#include "knapsack.h"
#include <stdlib.h>

Knapsack _10knapsack(Bag bag) {
	Knapsack k;
	k.combo = (int*)malloc(sizeof(int) * bag.n);
	int i;
	for(i=0; i < bag.n; i++) {
		k.combo[i] = i;
	}
	k.value = -1;
	return k;
}