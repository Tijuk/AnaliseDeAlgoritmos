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
	printf("Running Test [ %d ]-----------------\n", index+1);
	// printBag(test.bag);
	Knapsack k = _10knapsack(test.bag);
	for(i = 0; i < test.bag.n; i++) {
		if(test.expectedCombo[i] != k.combo[i]) {
			testFailed = true;
		}
	}
	if(test.expectedValue != k.value) {
		testFailed = true;
	}
	char message[500];
	if(testFailed == true) {
		sprintf(message, "Test [ %d ] failed", index+ 1);
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
		sprintf(message, "Test [ %d ] ran successfully", index + 1);
		log_success(message);
	}
	printf("\n\n");
}

int main() {
	loadTests();
	int index;
	printf("Running [ %d ] tests\n", NUMBER_OF_TESTS);
	for(index = 9; index < NUMBER_OF_TESTS; index++) {
		runSingleTest(index);
		// if(index == 4) break;
	}
	// runSingleTest(8);
	return 0;
}
