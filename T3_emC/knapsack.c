#include "knapsack.h"
#include "log.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef DEBUG
	#define __log printf
// #elif STEP_BY_STEP
// 	#define __log printf
// 	#define __sbs printf
#else
	void __log(const char *fmt, ...)
	{
	}
#endif

int iteracoes = 0;
int **cache;

/**
 * Retorna o valor máximo entro 2 números
 */
int maxOf(int, int);

/**
 * Inicializa o cache
 */
void initCache(Bag);

/**
 * Libera o espaço da memória em que o cache está alocado
 */
void freeCache(Bag);

/**
 * Seta um valor no cache
 */
void setCache(int, int, int);

/**
 * Imprime na tela os valores do cache
 */
void exibeCache(Bag bag);

/**
 * Função de Recorrencia
 * 
 * @param {Item} item: É o item observado por último.
 * @param {int} index: É o index do item observado atualmente.
 * @param {int} weight: É o peso na iteração atual.
 * @param {int} count: É a quantidade de items do item observado.
 * 
 * @return {bool} returns (se o somatório dos pesos do item é maior que o peso da iteração atual)
 */
bool opt(Item item, int index, int weight, int count)
{
	int totalWeight = count * item.weight;
	int optionA, optionB;
	iteracoes++;
	if (totalWeight <= weight)
	{
		optionA = cache[item.id][weight - totalWeight] + count * item.value;
		optionB = cache[index][weight];
		setCache(index, weight, maxOf(optionA, optionB));
		return false;
	}
	return true;
}

/**
 * Função de gerar a matriz de Cache
 * 
 * @param {Bag} bag é a mochila utilizada.
 */
void generateCacheMatrix(Bag bag)
{
	int itemIndex, weight, totalWeight, itemCount, optionA, optionB;
	Item item;
	Knapsack k;
	initCache(bag);
	for (itemIndex = 1; itemIndex <= bag.n; itemIndex++)
	{
		item = bag.items[itemIndex - 1];
		for (weight = 0; weight <= bag.size; weight++)
		{
			setCache(itemIndex, weight, cache[item.id][weight]);
			for (itemCount = 1; itemCount <= SET_OF_ITEM; itemCount++)
			{
				if (opt(item, itemIndex, weight, itemCount) == true)
				{
					break;
				}
			}
		}
	}
}

/**
 * Função que calcula o combo de itens para se obter o maior valor
 * 
 * @param {Bag} bag é a mochila utilizada.
 * 
 * @return {int*} um array com a quantidade de cada item para se obter o maior valor.
 */
int *extractBestCombo(Bag bag)
{
	int itemIndex, weight, totalWeight, itemCount, v, optionA, optionB;
	Item item;
	int *bestCombo = calloc(bag.n, sizeof(int));
	weight = bag.size;
	for (itemIndex = bag.n; itemIndex > 0; itemIndex--)
	{
		item = bag.items[itemIndex - 1];
		for (itemCount = 0; itemCount <= SET_OF_ITEM; itemCount++)
		{
			totalWeight = weight - (item.weight * itemCount);
			iteracoes++;
			if (cache[itemIndex][weight] == cache[item.id][totalWeight] + itemCount * item.value)
			{
				weight = totalWeight;
				break;
			}
			else
			{
				bestCombo[item.id]++;
			}
		}
	}
	return bestCombo;
}

/**
 * Função que calcula o combo de itens para se obter o maior valor
 * 
 * @param {Bag} bag é a mochila utilizada.
 * @param {int*} bestCombo é o combo do melhor valor
 * 
 * @return {int} o valor do melhor combo
 */
int getBestValue(Bag bag, int *bestCombo)
{
	int i;
	int value = cache[bag.n][bag.size];
#ifdef DEBUG
	char message[500];
	int redundancyValue = 0;
	// Checagem de Redundancia para garantir que o somatório dos valores no combo são iguais ao valor máximo
	for (i = 0; i < bag.n; i++)
	{
		redundancyValue += bestCombo[i] * bag.items[i].value;
	}
	if (redundancyValue != value)
	{
		sprintf(message, "Redundancy Test: { %d } != { %d }\n", value, redundancyValue);
		log_error(message);
	}
	else
	{
		log_success("Redundancy Test: Passed");
	}
#endif
	return value;
}

Knapsack _10knapsack(Bag bag)
{
	Knapsack k;
	generateCacheMatrix(bag);
	k.combo = extractBestCombo(bag);
	k.value = getBestValue(bag, k.combo);
	// __log("ITERACOES: { %d }\n", iteracoes);
	// __log("N: { %d }\tB: { %d }\tN x B: { %d }\n", bag.n, bag.size, bag.n * bag.size * SET_OF_ITEM);
	exibeCache(bag);
	freeCache(bag);

	return k;
}

/**
 * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 * 
 * 
 * 
 * Helper functions
 * 
 * 
 * 
 * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 */

int maxOf(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

void initCache(Bag bag)
{
	int i, j;
	cache = (int **)malloc((bag.n + 1) * sizeof(int *));
	for (i = 0; i < bag.n + 1; i++)
	{
		cache[i] = (int *)malloc((bag.size + 1) * sizeof(int));
		for (j = 0; j < bag.size + 1; j++)
		{
			cache[i][j] = 0;
		}
	}
}

void freeCache(Bag bag)
{
	int i, j;
	for (i = 0; i < bag.n + 1; i++)
	{
		free(cache[i]);
	}
	free(cache);
	iteracoes = 0;
}

void setCache(int itemIndex, int weight, int value)
{
	// __log("Setting Cache at [%d][%d] to { %d }\n", weight, itemIndex, value);
	cache[itemIndex][weight] = value;
}

void exibeCache(Bag bag)
{
	#ifdef STEP_BY_STEP
	int i, j;
	__log("Cache: \n");
	for (i = 0; i < bag.n + 1; i++)
	{
		__log("[ ");
		for (j = 0; j < bag.size + 1; j++)
		{
			__log("%-2d", cache[i][j]);
			if (j < bag.size)
				__log(", ");
		}
		__log(" ]\n");
	}
	__log("\n");
	#endif
}