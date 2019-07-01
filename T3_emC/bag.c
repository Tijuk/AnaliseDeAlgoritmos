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

	for (i = 0; i < n; i++)
	{

		Item item;
		item.id = i;
		item.value = values[i];
		item.weight = weights[i];
		item.count = SET_OF_ITEM;
		item.original_count = SET_OF_ITEM;
		b.items[i] = item;
	}
	return b;
}

void printBag(Bag bag) {
	#ifdef DEBUG
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
	#endif
}
