#ifndef BAG__H_
#define BAG__H_

struct __item
{
	unsigned int id;
	unsigned int weight;
	unsigned int value;
	unsigned int count;
	unsigned int original_count;
};

struct __bag
{
	int size;
	int n;
	struct __item *items;
};

typedef struct __bag Bag;
typedef struct __item Item;

Bag newBag(int size, int n, int *weights, int *values);
void printBag(Bag bag);

#endif