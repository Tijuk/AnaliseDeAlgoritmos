#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "test.h"

TestInstance *allTests;

int expectedCombos[NUMBER_OF_TESTS][MAX_NUMBER_OF_ITEMS];
int expectedValues[NUMBER_OF_TESTS];

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
	fp = fopen("./solutions", "r");
	if (fp == NULL)
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
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
	int left, right, line = 0;
	int *values = (int *)malloc(sizeof(int) * MAX_NUMBER_OF_ITEMS);
	int *weights = (int *)malloc(sizeof(int) * MAX_NUMBER_OF_ITEMS);
	int size, n = 0;
	sprintf(path, "./instances/inst%d", index + 1);
	fp = fopen(path, "r");
	if (fp == NULL)
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	while (fscanf(fp, "%d\t%d", &left, &right) != EOF)
	{
		if (line == 0)
		{
			n = left;
			size = right;
		}
		else
		{
			values[line - 1] = left;
			weights[line - 1] = right;
		}
		line++;
	}
	t.bag = newBag(size, n, weights, values);
	t.expectedCombo = expectedCombos[index];
	free(fp);
	return t;
}

void loadTests()
{
	loadExpected();
	allTests = (TestInstance *)malloc(sizeof(TestInstance) * NUMBER_OF_TESTS);
	int i;
	for (i = 0; i < NUMBER_OF_TESTS; i++)
	{
		allTests[i] = loadOneTest(i);
	}
}

TestInstance getTestInstance(int testIndex)
{
	return allTests[testIndex];
}