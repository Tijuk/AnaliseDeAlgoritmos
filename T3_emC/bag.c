#include "bag.h"
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

Bag newBag(int size, int n, int *weights, int *values)
{

	Bag b;
	b.size = size;
	b.n = n;
	b.items = (Item*)malloc(sizeof(Item) * n);
	int i;
	// printf("Bag Items [ %d ]\n", n);

	for (i = 0; i < n; i++)
	{
		// printf("Bag [ %d ]\n", i);

		Item item;
		item.id = i;
		item.value = values[i];
		item.weight = weights[i];
		item.count = SET_OF_ITEM;
		item.original_count = SET_OF_ITEM;
		// printf("%d <> %d <> %d\n", values[i], weights[i], 0);
		b.items[i] = item;
	}
	// printf("Bag  Return\n");

	// b.weights = weights;
	// b.values = values;
	return b;
}

void printBag(Bag bag) {
	printf("Bag: {\n\tsize: %d\n\tn: %d\n\tvalues: ", bag.size, bag.n);
	int i;
	printf("[");
	for(i = 0; i < bag.n; i++) {
		if(i == 0) {
			printf("%d", bag.items[i].value);
		} else {
			printf(",%d", bag.items[i].value);
		}
		
	}
	printf("]\n\tweights: [");
	for(i = 0; i < bag.n; i++) {
		if(i == 0) {
			printf("%d", bag.items[i].weight);
		} else {
			printf(",%d", bag.items[i].weight);
		}
		
	}
	printf("]\n");
	printf("]\n\tcount: [");
	for(i = 0; i < bag.n; i++) {
		if(i == 0) {
			printf("%d", bag.items[i].count);
		} else {
			printf(",%d", bag.items[i].count);
		}
		
	}
	printf("]\n");
}
