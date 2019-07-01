#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bag.h"
#include "log.h"
#include "test.h"
#include "constants.h"
#include "knapsack.h"

void printTestResult(int index, TestInstance test, Knapsack k, bool testFailed);
void printArray(int *values, int size, bool error);
void allTestResults(int *failedTests, int testFailed);

bool runSingleTest(int index)
{
	TestInstance test = getTestInstance(index);
	bool testFailed = false;
	int i;
	char header[500] = "Running Instancia [ %d ]";
	
	sprintf(header, header, index + 1);
	log_split(header, 10);

	printBag(test.bag);

	Knapsack k = _10knapsack(test.bag);
	for (i = 0; i < test.bag.n; i++)
	{
		if (test.expectedCombo[i] != k.combo[i])
		{
			testFailed = true;
		}
	}
	if (test.expectedValue != k.value)
	{
		testFailed = true;
	}
	printTestResult(index, test, k, testFailed);
	return testFailed;
}

int main()
{
#if STEP_BY_STEP > NUMBER_OF_TESTS
	printf("STEP_BY_STEP is set to [ %d ], which is higher than NUMBER_OF_TESTS [ %d ]\n", STEP_BY_STEP, NUMBER_OF_TESTS);
	exit(1);
#endif
	loadTests();
	int index;
	int *failedTests = calloc(NUMBER_OF_TESTS, sizeof(int));
	int testFailed = 0;
#ifdef STEP_BY_STEP
	printf("STEP_BY_STEP set to true, running only Test: [ %d ]\n", STEP_BY_STEP + 1);
	runSingleTest(STEP_BY_STEP);
#else
	printf("Running [ %d ] tests\n", NUMBER_OF_TESTS);
	for (index = 0; index < NUMBER_OF_TESTS; index++)
	{
		if (runSingleTest(index) == true)
		{
			testFailed++;
			failedTests[index] = 1;
		}
	}
	allTestResults(failedTests, testFailed);
	free(failedTests);
#endif

	return 0;
}

/**
 * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
 * 
 * 
 * 				HELPER FUNCTIONS
 * 
 * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
 */

void printArray(int *values, int size, bool error)
{
	int i = 0;
	char message[MAX_MESSAGE_SIZE];
	sprintf(message, "[");
	for (; i < size; i++)
	{
		if (i > MAX_MESSAGE_SIZE)
		{
			log_error("PrintArray: MAX_MESSAGE_SIZE value reached. Increase it's value at { constants.h }");
			exit(1);
		}
		if (i == 0)
		{
			sprintf(message, "%s%d", message, values[i]);
		}
		else
		{
			sprintf(message, "%s, %d", message, values[i]);
		}
	}
	sprintf(message, "%s]\n", message);
	if (error == true)
	{
		red(message);
	}
	else
	{
		green(message);
	}
}

void printTestResult(int index, TestInstance test, Knapsack k, bool testFailed)
{
	char message[500];
#ifdef DEBUG
	if (testFailed == true)
	{
		sprintf(message, "Test [ %d ] failed", index + 1);
		log_error(message);
	}
	else
	{
		sprintf(message, "Test [ %d ] ran successfully", index + 1);
		log_success(message);
	}
	printf("Received Combo: ");
	printArray(k.combo, test.bag.n, true);
	printf("Expected Combo: ");
	printArray(test.expectedCombo, test.bag.n, false);
	printf("Received Value: ");
	sprintf(message, "{ %d }\n", k.value);
	red(message);
	printf("Expected Value: ");
	sprintf(message, "{ %d }\n", test.expectedValue);
	green(message);
	printf("\n\n");

#else
	if (testFailed == true)
	{
		sprintf(message, "Test [ %d ] failed", index + 1);
		log_error(message);
		printf("Received Combo: ");
		printArray(k.combo, test.bag.n, true);
		printf("Expected Combo: ");
		printArray(test.expectedCombo, test.bag.n, false);
		printf("Received Value: ");
		sprintf(message, "{ %d }\n", k.value);
		red(message);
		printf("Expected Value: ");
		sprintf(message, "{ %d }\n", test.expectedValue);
		green(message);
		printf("\n\n");

	}
	#ifndef NO_PRINT_ON_SUCCESS
	else
	{
		sprintf(message, "Test [ %d ] ran successfully", index + 1);
		log_success(message);
		printf("\n\n");

	}
	#endif
#endif
}

void allTestResults(int *failedTests, int testFailed)
{
	int index;
	char message[500];
	char finalMessage[500];
	sprintf(message, "%d of %d tests passed", NUMBER_OF_TESTS - testFailed, NUMBER_OF_TESTS);
	if (testFailed == 0)
	{
		log_success(message);
	}
	else
	{
		log_error(message);
		message[0] = '\0';
		for (index = 0; index < NUMBER_OF_TESTS; index++)
		{
			if (failedTests[index] == 1)
			{
				if (message[0] == '\0')
				{
					sprintf(message, "%d", index + 1);
				}
				else
				{
					sprintf(message, "%s, %d", message, index + 1);
				}
			}
		}
		sprintf(finalMessage, "Failed Tests: [ %s ]", message);
		log_error(finalMessage);
	}
}