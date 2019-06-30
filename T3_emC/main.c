#include <stdio.h>
#include <stdlib.h>
#include "bag.h"
#include "log.h"
#include "test.h"
#include "constants.h"
#include "knapsack.h"

void printArray(int* values, int size) {
	int i = 0;
	printf("[");
	for(; i < size; i++) {
		if(i == 0) {
			printf("%d", values[i]);
		} else {
			printf(",%d", values[i]);
		}
		
	}
	printf("]\n");
}

void runSingleTest(int index) {
	TestInstance test = getTestInstance(index);
	bool testFailed = false;
	int i;
	printf("Running Test [ %d ]-----------------\n", index);
	Knapsack k = _10knapsack(test.bag);
	for(i = 0; i < test.bag.n; i++) {
		if(test.expectedCombo[i] != k.combo[i]) {
			testFailed = true;
		}
	}
	char message[500];
	if(testFailed == true) {
		sprintf(message, "Test [ %d ] failed", index);
		log_error(message);
		printf("Result:   ");
		printArray(k.combo, test.bag.n);
		printf("Expected: ");
		printArray(test.expectedCombo, test.bag.n);
		printf("Expected Value: ");
		sprintf(message, "{ %d }\n", test.expectedValue);
		green(message);
		printf("Received Value: ");
		sprintf(message, "{ %d }\n", k.value);
		red(message);
	} else {
		sprintf(message, "Test [ %d ] ran successfully", index);
		log_success(message);
	}
	printf("\n\n");
}

int main() {
	loadTests();
	// int weights[2] = {0,1};
	// int values[2] = {2,3};

	// Bag b = newBag(5, 2, weights, values);
	// printf("%d\n", b.n);
	// log_success("Batata");
	// log_error("Batata");
	// // hello("World");

	int index;
	for(index = 0; index < NUMBER_OF_TESTS; index++) {
		runSingleTest(index);
	}
	return 0;
}
