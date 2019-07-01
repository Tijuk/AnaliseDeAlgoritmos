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

/**
 * Um cache de tamanho [bag.size + 1] x [bag.n + 1], inicializado inteiramente com 0. Onde o primeiro item está na posicao [1][0].
 * De forma a facilitar as condições da primeira iteração
 */
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
 * Realiza um teste de redundancia, calculando o valor de formas diferentes, para garantir que todas chegam ao mesmo resultado
 */
void redundancy_test(Bag bag, int* combo);

/**
 * Função criada apenas para garantir o valor encontrado bate com a versão em cache
 */
int opt_recursive(Bag bag, int itemIndex, int weight);

void sub_opt(Bag bag, int itemIndex, int weight, int itemCount) {
	int totalWeight; // Peso Total ( Peso do Item x Contagem do Item )
	int totalValue; // Valor Total ( Valor do Item x Contagem do Item )
	int optionA, optionB;
	Item item = bag.items[itemIndex - 1];

	totalWeight = item.weight * itemCount;
	totalValue = item.value * itemCount;
	// Opção A: valor total + valor no cache do item anterior, no peso - peso dos items.
	optionA = cache[item.id][weight - totalWeight] + totalValue;

	// Opção B: valor no cache atual.
	optionB = cache[itemIndex][weight];

	// Salva no Cache o maior valor entre os 2.
	setCache(itemIndex, weight, maxOf(optionA, optionB));
}

/**
 * Função de Recorrencia
 * 
 * @param {Bag} bag: É a mochila.
 * @param {int} index: É o index do item observado atualmente.
 * @param {int} weight: É o peso na iteração atual.
 */
void opt(Bag bag, int itemIndex, int weight)
{
	int itemCount; // Contador de repetição dos items [ 0 .. 10]
	int totalWeight; // Peso Total ( Peso do Item x Contagem do Item )
	int totalValue; // Valor Total ( Valor do Item x Contagem do Item )
	int optionA, optionB;
	Item item = bag.items[itemIndex - 1];
	setCache(itemIndex, weight, cache[item.id][weight]);
	for (itemCount = 1; itemCount <= SET_OF_ITEM; itemCount++)
	{
		iteracoes++;
		totalWeight = item.weight * itemCount;
		totalValue = item.value * itemCount;
		if (totalWeight <= weight) // Se o peso total não estourar o peso máximo do sub-problema
		{
			// Opção A: valor total + valor no cache do item anterior, no peso - peso dos items.
			optionA = cache[item.id][weight - totalWeight] + totalValue;

			// Opção B: valor no cache atual.
			optionB = cache[itemIndex][weight];

			// Salva no Cache o maior valor entre os 2.
			setCache(itemIndex, weight, maxOf(optionA, optionB));
		} else {
			break;
		}
	}
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
	initCache(bag);
	for (itemIndex = 1; itemIndex <= bag.n; itemIndex++)
	{
		for (weight = 0; weight <= bag.size; weight++)
		{
			opt(bag, itemIndex, weight);
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
	for (itemIndex = bag.n; itemIndex > 0; itemIndex--) // Para cada item
	{
		item = bag.items[itemIndex - 1];
		for (itemCount = 0; itemCount <= SET_OF_ITEM; itemCount++) // Para cada repetição
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
	redundancy_test(bag, bestCombo);
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
	for (i = 1; i < bag.n + 1; i++)
	{
		__log("[ ");
		for (j = 1; j < bag.size + 1; j++)
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

/**
 * 
 */
void redundancy_test(Bag bag, int* combo) {
	int recursiveValue = opt_recursive(bag, bag.n, bag.size);
	int value = cache[bag.n][bag.size];
	int i;
	char message[500];
	int redundancyValue = 0;
	// Checagem de Redundancia para garantir que o somatório dos valores no combo são iguais ao valor máximo
	for (i = 0; i < bag.n; i++)
	{
		redundancyValue += combo[i] * bag.items[i].value;
	}
	if (redundancyValue != value || recursiveValue != value)
	{
		sprintf(message, "Redundancy Test: { %d } != { %d } != { %d }\n", value, redundancyValue, recursiveValue);
		log_error(message);
	}
	else
	{
		log_success("Redundancy Test: Passed");
	}
}

int opt_recursive(Bag bag, int itemIndex, int weight) {
	#ifndef ALLOW_RECURSIVE_TEST
		return cache[itemIndex][weight];
	#endif
	int itemCount; // Contador de repetição dos items [ 0 .. 10]
	int totalWeight; // Peso Total ( Peso do Item x Contagem do Item )
	int totalValue; // Valor Total ( Valor do Item x Contagem do Item )
	int optionA, optionB;
	Item item = bag.items[itemIndex - 1];
	if(itemIndex == 0 || weight == 0) {
		return 0;
	}
	int stored = opt_recursive(bag, itemIndex - 1, weight);
	// setCache(itemIndex, weight, cache[item.id][weight]);
	for (itemCount = 1; itemCount <= SET_OF_ITEM; itemCount++)
	{
		totalWeight = item.weight * itemCount;
		totalValue = item.value * itemCount;
		if (totalWeight <= weight) // Se o peso total não estourar o peso máximo do sub-problema
		{
			// Opção A: valor total + valor no cache do item anterior, no peso - peso dos items.
			optionA = opt_recursive(bag, item.id, weight-totalWeight) + totalValue;

			// Opção B: valor no cache atual.
			optionB = stored;

			stored = maxOf(optionA, optionB);
		} else {
			break;
		}
	}
	return stored;
}