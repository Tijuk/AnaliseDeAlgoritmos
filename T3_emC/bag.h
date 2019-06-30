#ifndef BAG__H_
#define BAG__H_


struct __bag {
int size;
	int n;
	int* weights;
	int* values;
};

typedef struct __bag Bag;

Bag newBag(int size, int n, int* weights, int* values);

#endif