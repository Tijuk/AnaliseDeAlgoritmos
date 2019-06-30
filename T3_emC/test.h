#ifndef __TEST_H_
#define __TEST_H_

#include "bag.h"
#include "constants.h"

struct __test
{
	Bag bag;
	int* expectedCombo;
	int expectedValue;
};

typedef struct __test TestInstance;

void loadTests();
TestInstance getTestInstance(int testIndex);


#endif