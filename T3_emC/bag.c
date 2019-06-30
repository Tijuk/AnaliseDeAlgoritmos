#include "bag.h"
#include <stdio.h>
Bag newBag(int size, int n, int* weights, int* values) {
	Bag b;
	b.size = size;
	b.n = n;
	b.weights = weights;
	b.values = values;
	return b;
}
