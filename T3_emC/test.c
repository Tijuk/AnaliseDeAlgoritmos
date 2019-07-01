#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "test.h"

TestInstance *allTests;

int expectedCombos[NUMBER_OF_TESTS][MAX_NUMBER_OF_ITEMS];
int expectedValues[NUMBER_OF_TESTS];

FILE* my_open(const char* path, const char* mode) {
	FILE *fp;
	fp = fopen(path, mode);
	if (fp == NULL)
	{
		printf("Error while opening the file.\n");
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	return fp;
}

void setExpectedCombos(char *str, int testIndex)
{
	char *token = strtok(str, ",");
	int index;
	for (index = 0; token != NULL; index++)
	{
		expectedCombos[testIndex][index] = atoi(token);
		token = strtok(NULL, ",");
	}
}

void loadExpected()
{
	FILE *fp;
	fp = my_open("./solutions", "r");
	int testIndex;
	char line[100];
	for (testIndex = 0; fscanf(fp, "%s", line) != EOF; testIndex++)
	{
		if(testIndex%2 == 0) {
			setExpectedCombos(line, testIndex/2);
		} else {
			expectedValues[testIndex/2] = atoi(line);
		}
	}
}

TestInstance loadOneTest(int index)
{
	char path[200];
	TestInstance t;
	FILE *fp;
	int left, right, lineIndex = 0;
	char line[500];
	int *values = (int *)malloc(sizeof(int) * MAX_NUMBER_OF_ITEMS);
	int *weights = (int *)malloc(sizeof(int) * MAX_NUMBER_OF_ITEMS);
	int size, n = 0;
	sprintf(path, "./instances/inst%d", index + 1);

	fp = my_open(path, "r");
	while (fscanf(fp, "%d\t%d", &left, &right) != EOF)
	{
		if (lineIndex == 0)
		{
			n = left;
			size = right;
		}
		else
		{
			values[lineIndex - 1] = left;
			weights[lineIndex - 1] = right;
		}
		lineIndex++;
	}

	t.bag = newBag(size, n, weights, values);
	
	t.expectedCombo = expectedCombos[index];
	t.expectedValue = expectedValues[index];
	free(fp);
	return t;
}

void loadTests()
{
	// printf("Here\n");
	loadExpected();
	// printf("Here\n");
	allTests = (TestInstance *)malloc(sizeof(TestInstance) * NUMBER_OF_TESTS);
	int i;
	// printf("Here\n");
	for (i = 0; i < NUMBER_OF_TESTS; i++)
	{
		// printf("out. Here [ %d ]\n",i);
		allTests[i] = loadOneTest(i);
	}
}

TestInstance getTestInstance(int testIndex)
{
	// printf("Here");
	return allTests[testIndex];
}