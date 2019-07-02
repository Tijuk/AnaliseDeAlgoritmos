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

#define INITIALIZED_TYPE char
#define UNDEFINED 'u'
#define DEFINED 'd'

int iteracoes = 0;

/**
 * Um cache de tamanho [bag.size + 1] x [bag.n + 1], inicializado inteiramente com 0. Onde o primeiro item está na posicao [1][0].
 * De forma a facilitar as condições da primeira iteração
 */
int **cache;
INITIALIZED_TYPE **initialized;
Bag bag;

/**
 * Retorna o valor máximo entro 2 números
 */
int maxOf(int, int);

/**
 * Retorna o valor mínimo entro 2 números
 */
int minOf(int, int);

/**
 * Inicializa o cache
 */
void initCache();

/**
 * Libera o espaço da memória em que o cache está alocado
 */
void freeCache();

/**
 * Seta um valor no cache
 */
void setCache(int, int, int);

/**
 * Obtem um valor do cache.
 * Se a posição nao tiver sido iniciada ainda, será calculada utilizando a função de recorrencia (opt);
 */
int getCache(int itemIndex, int weight);

/**
 * Imprime na tela os valores do cache
 */
void exibeCache();

/**
 * Realiza um teste de redundancia, calculando o valor de formas diferentes, para garantir que todas chegam ao mesmo resultado
 */
void redundancy_test(int *combo);

/**
 * Função criada apenas para garantir o valor encontrado bate com a versão em cache
 */
int opt_recursive(int itemIndex, int weight);

/**
 * Função de Recorrencia
 * 
 * @param {Bag} bag: É a mochila.
 * @param {int} index: É o index do item observado atualmente.
 * @param {int} weight: É o peso na iteração atual.
 */
int opt(int itemIndex, int weight)
{
	int itemCount;   // Contador de repetição dos items [ 0 .. 10 ]
	int totalWeight; // Peso Total ( Peso do Item x Contagem do Item )
	int totalValue;  // Valor Total ( Valor do Item x Contagem do Item )
	int optionA, optionB, bestOption;
	iteracoes++;
	if (itemIndex == 0) // if (i = 0)
	{
		bestOption = 0; // opt(i,w) = 0
	}
	else
	{
		Item item = bag.items[itemIndex - 1];
		if (weight / item.weight == 0) // if( floor(w/wi) == 0 )
		{
			bestOption = getCache(item.id, weight); // opt(i,w) = opt(i - 1, w);
		}
		else // otherwise
		{
			bestOption = getCache(item.id, weight);
			int maxItems = minOf(weight / item.weight, SET_OF_ITEM);
			for (itemCount = 1; itemCount <= maxItems; itemCount++)
			{
				iteracoes++;
				totalWeight = item.weight * itemCount;
				totalValue = item.value * itemCount;
				if (totalWeight <= weight) // Se o peso total não estourar o peso máximo do sub-problema
				{
					// a(c) = opt(i - 1, w - (c * wi))
					optionA = getCache(item.id, weight - totalWeight) + totalValue;

					// opt(i,w) = max{ opt(i-1,w), a(c) }, onde c = todos os naturais entre 0 e w/wi
					bestOption = maxOf(optionA, bestOption);
				}
				else
				{
					break;
				}
			}
		}
	}
	setCache(itemIndex, weight, bestOption);
	return getCache(itemIndex, weight);
}

/**
 * Função de gerar a matriz de Cache
 * 
 * @param {Bag} bag é a mochila utilizada.
 */
void generateCacheMatrix()
{
	int itemIndex, weight, totalWeight, itemCount, optionA, optionB;
	Item item;
	initCache();
	opt(bag.n, bag.size);
}

/**
 * Função que calcula o combo de itens para se obter o maior valor
 * 
 * @param {Bag} bag é a mochila utilizada.
 * 
 * @return {int*} um array com a quantidade de cada item para se obter o maior valor.
 */
int *extractBestCombo()
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
int getBestValue(int *bestCombo)
{
	int i;
	int value = cache[bag.n][bag.size];
#ifdef DEBUG
	redundancy_test(bestCombo);
#endif
	return value;
}

Knapsack _10knapsack(Bag __bag)
{
	Knapsack k;
	bag = __bag;
	generateCacheMatrix();
	k.combo = extractBestCombo();
	k.value = getBestValue(k.combo);
	// __log("ITERACOES: { %d }\n", iteracoes);
	// __log("N: { %d }\tB: { %d }\tN x B: { %d }\n", bag.n, bag.size, bag.n * bag.size * SET_OF_ITEM);
	exibeCache();
	freeCache();

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

void initCache()
{
	int i, j;
	cache = (int **)malloc((bag.n + 1) * sizeof(int *));
	initialized = (INITIALIZED_TYPE **)malloc((bag.n + 1) * sizeof(INITIALIZED_TYPE *));
	for (i = 0; i < bag.n + 1; i++)
	{
		cache[i] = (int *)malloc((bag.size + 1) * sizeof(int));
		initialized[i] = (INITIALIZED_TYPE *)malloc((bag.size + 1) * sizeof(INITIALIZED_TYPE));
		for (j = 0; j < bag.size + 1; j++)
		{
			cache[i][j] = 0;
			initialized[i][j] = UNDEFINED;
		}
	}
}

void freeCache()
{
	int i, j;
	for (i = 0; i < bag.n + 1; i++)
	{
		free(initialized[i]);
		free(cache[i]);
	}
	free(cache);
	free(initialized);
	iteracoes = 0;
}

int getCache(int itemIndex, int weight)
{
	if (initialized[itemIndex][weight] == UNDEFINED)
	{
		initialized[itemIndex][weight] = DEFINED;

		return opt(itemIndex, weight);
	}
	return cache[itemIndex][weight];
}

void setCache(int itemIndex, int weight, int value)
{
	// __log("Setting Cache at [%d][%d] to { %d }\n", weight, itemIndex, value);
	initialized[itemIndex][weight] = DEFINED;
	cache[itemIndex][weight] = value;
}

void exibeCache()
{
#ifdef STEP_BY_STEP
	int i, j;
	__log("Cache: \n");
	for (i = 1; i < bag.n; i++)
	{
		__log("[");
		for (j = 1; j < bag.size + 1; j++)
		{
			if (j > 1)
				__log(",");

			if (cache[i][j] < 10)
			{
				__log(" ");
			}
			__log("%d", cache[i][j]);
		}
		__log(" ]\n");
	}
	__log("\n");
#endif
}

/**
 * 
 */
void redundancy_test(int *combo)
{
	int recursiveValue = opt_recursive(bag.n, bag.size);
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

int opt_recursive(int itemIndex, int weight)
{
#ifndef ALLOW_RECURSIVE_TEST
	return cache[itemIndex][weight];
#endif
	int itemCount;   // Contador de repetição dos items [ 0 .. 10]
	int totalWeight; // Peso Total ( Peso do Item x Contagem do Item )
	int totalValue;  // Valor Total ( Valor do Item x Contagem do Item )
	int optionA, optionB;
	Item item = bag.items[itemIndex - 1];
	iteracoes++;
	if (itemIndex == 0 || weight == 0)
	{
		return 0;
	}
	int stored = opt_recursive(itemIndex - 1, weight);
	// setCache(itemIndex, weight, cache[item.id][weight]);
	for (itemCount = 1; itemCount <= SET_OF_ITEM; itemCount++)
	{
		iteracoes++;
		totalWeight = item.weight * itemCount;
		totalValue = item.value * itemCount;
		if (totalWeight <= weight) // Se o peso total não estourar o peso máximo do sub-problema
		{
			// Opção A: valor total + valor no cache do item anterior, no peso - peso dos items.
			optionA = opt_recursive(item.id, weight - totalWeight) + totalValue;

			// Opção B: valor no cache atual.
			optionB = stored;

			stored = maxOf(optionA, optionB);
		}
		else
		{
			break;
		}
	}
	return stored;
}

int minOf(int a, int b)
{
	if (a > b)
		return b;
	return a;
}