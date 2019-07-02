# Relatorio T3

**Matéria:** INF1721 - Análise de Algoritmos  
**Período:** 2019.1  
**Professor:** Marco Molinaro  
**Turma**: 3WA  
**Grupo**: Alexandre Dias

# Problema de Knapsack

O problema 10-Knapsack é o seguinte: temos uma mochila de tamanho **B** e **n** itens, onde o item **i** tem tamanho **wi** e valor **vi**. Porém agora temos 10 unidades de cada item. O objetivo é selecionar uma quantidade de cada itens (de 0 a 10) de forma que caibam na mochila (i.e., soma dos tamanho é menor que B) e que obtenha valor máximo.

_Assuma que todos os dados **B**, **w1**, ..., **wn**, **v1**, ..., **vn** são inteiros não-negativos._

# Resolução do Problema

Para resolver o problema, dividiremos o problema em diversos sub-problemas.
Dado uma mochila de tamanho **B** e **n** itens, montaremos uma matrix com n linhas e B colunas.

Nessa matrix, cada entrada será um sub-problema de capacidade _w_, onde _w_ é o iterador da coluna.

Para cada sub-problema, consideraremos o valor ao adicionar a menor quantidade necessária para preencher a entrada (de forma que o peso não estoure o limite do sub-problema) ou a quantidade existente daquele item ( no caso, para todos os itens, o valor é 10 )

# Recorrencia

Para cada sub-problema, deveremos olhar no subproblema do item anterior para podermos definir o valor do atual sub-problema. Dessa forma utilizaremos uma função de recorrencia, porém, em formato de matrix para não termos que iterar por todos os sub-problemas a cada novo sub-problema.

## Expressão

a função **opt( i, w )** poderá retornar 3 "valores" distintos.

|       Caso        |          Retorno de opt( i,w )           |
| :---------------: | :--------------------------------------: |
|      _i = 0_      |                    0                     |
| _floor(w/wi) = 0_ |             opt( i - 1, w )              |
|    _otherwise_    | max{ opt( i - 1, w) , max { g( i,w ) } } |

onde _g( i,w )_ será uma função que retornará o **maior** valor de :  
**opt( i - 1, w - ( c _ wi ) ) + ( c _ vi )**  
para todos os valores de **C**, tal que seja C um conjunto de números naturais variando entre _0_ e _w/wi_

## Código

```.c

int opt(int itemIndex, int weight)
{
	int itemCount;   // Contador de repetição dos items [ 0 .. 10 ]
	int totalWeight; // Peso Total ( Peso do Item x Contagem do Item )
	int totalValue;  // Valor Total ( Valor do Item x Contagem do Item )
	int optionA, optionB, bestOption;
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
```

# Obtendo a melhor combinação

Após preencher a matriz de recorrencia (vulgo cache), devemos percorrer ela do final até o inicio, decodificando-a para decidirmos qual é a combinação para atingir o valor encontrado.

Para cada item, iremos percorrer até 10 vezes, testando o valor para saber se ele faz ou não parte da melhor combinação.

Devemos armazenar o valor do peso restante dentro da bolsa ( _peso_restante_ ), e ir atualizando conforme formos testando os itens.

```.c
int* extraiMelhorCombo() {
	int* combo = calloc(tamanho_da_mochila, sizeof(int)); // inicializa o vetor um vetor de zeros
	int peso_restante = tamanho_da_mochila;
	for(int i = B; i > 0; i--) { // para cada item
		for(int qtd = 0; qtd < 10; qtd++) { // para cada repetição do item
			peso_items = peso_restante - (item[i - 1].peso * qnt);
			if(cache[i][peso_restante] == cache[i-1][peso_items] + qnt * item[i].value) {
				/**
				* Se o valor do cache para (item,peso_restante) for igual ao cache
				* para (item_anterior, peso_items), atualiza-se o peso_restante e
				* para a iteração na repetição de items
				*/
				peso_restante = peso_items;
				break;
			} else {
				combo[i - 1]++;
			}
		}
	}
}

```

# Resultado dos Testes

**Passos para replicagem:**

- Em constants.h, garanta que STEP_BY_STEP, ALLOW_RECURSIVE_TEST estejam **UNDEFINED**
- Garanta que DEBUG está **DEFINED**
- Rode o comando run.bat

```.txt
Running [ 11 ] tests
Running Instancia [ 1 ] -=-=-=-=-=-=-=-=-=-
Bag: {
	size: 269
	n: 10
	values: [55,10,47,5,4,50,8,61,85,87]
	weights: [95,4,60,32,23,72,80,62,65,46]
	count: [10,10,10,10,10,10,10,10,10,10]
}
[ Success ]: Redundancy Test: Passed
[ Success ]: Test [ 1 ] ran successfully
Received Combo: [ 0, 9, 0, 0, 0, 0, 0, 0, 0, 5 ]
Expected Combo: [ 0, 9, 0, 0, 0, 0, 0, 0, 0, 5 ]
Received Value: { 525 }
Expected Value: { 525 }


Running Instancia [ 2 ] -=-=-=-=-=-=-=-=-=-
Bag: {
	size: 878
	n: 20
	values: [44,46,90,72,91,40,75,35,8,54,78,40,77,15,61,17,75,29,75,63]
	weights: [92,4,43,83,84,68,92,82,6,44,32,18,56,83,25,96,70,48,14,58]
	count: [10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10]
}
[ Success ]: Redundancy Test: Passed
[ Success ]: Test [ 2 ] ran successfully
Received Combo: [ 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 10, 7, 0, 0, 10, 0, 0, 0, 10, 0 ]
Expected Combo: [ 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 10, 7, 0, 0, 10, 0, 0, 0, 10, 0 ]
Received Value: { 2880 }
Expected Value: { 2880 }


Running Instancia [ 3 ] -=-=-=-=-=-=-=-=-=-
Bag: {
	size: 20
	n: 4
	values: [9,11,13,15]
	weights: [6,5,9,7]
	count: [10,10,10,10]
}
[ Success ]: Redundancy Test: Passed
[ Success ]: Test [ 3 ] ran successfully
Received Combo: [ 0, 4, 0, 0 ]
Expected Combo: [ 0, 4, 0, 0 ]
Received Value: { 44 }
Expected Value: { 44 }


Running Instancia [ 4 ] -=-=-=-=-=-=-=-=-=-
Bag: {
	size: 11
	n: 4
	values: [6,10,12,13]
	weights: [2,4,6,7]
	count: [10,10,10,10]
}
[ Success ]: Redundancy Test: Passed
[ Success ]: Test [ 4 ] ran successfully
Received Combo: [ 5, 0, 0, 0 ]
Expected Combo: [ 5, 0, 0, 0 ]
Received Value: { 30 }
Expected Value: { 30 }


Running Instancia [ 5 ] -=-=-=-=-=-=-=-=-=-
Bag: {
	size: 60
	n: 10
	values: [20,18,17,15,15,10,5,3,1,1]
	weights: [30,25,20,18,17,11,5,2,1,1]
	count: [10,10,10,10,10,10,10,10,10,10]
}
[ Success ]: Redundancy Test: Passed
[ Success ]: Test [ 5 ] ran successfully
Received Combo: [ 0, 0, 0, 0, 0, 0, 8, 10, 0, 0 ]
Expected Combo: [ 0, 0, 0, 0, 0, 0, 8, 10, 0, 0 ]
Received Value: { 70 }
Expected Value: { 70 }


Running Instancia [ 6 ] -=-=-=-=-=-=-=-=-=-
Bag: {
	size: 50
	n: 7
	values: [70,20,39,37,7,5,10]
	weights: [31,10,20,19,4,3,6]
	count: [10,10,10,10,10,10,10]
}
[ Success ]: Redundancy Test: Passed
[ Success ]: Test [ 6 ] ran successfully
Received Combo: [ 1, 0, 0, 1, 0, 0, 0 ]
Expected Combo: [ 1, 0, 0, 1, 0, 0, 0 ]
Received Value: { 107 }
Expected Value: { 107 }


Running Instancia [ 7 ] -=-=-=-=-=-=-=-=-=-
Bag: {
	size: 80
	n: 5
	values: [33,24,36,37,12]
	weights: [15,20,17,8,31]
	count: [10,10,10,10,10]
}
[ Success ]: Redundancy Test: Passed
[ Success ]: Test [ 7 ] ran successfully
Received Combo: [ 0, 0, 0, 10, 0 ]
Expected Combo: [ 0, 0, 0, 10, 0 ]
Received Value: { 370 }
Expected Value: { 370 }


Running Instancia [ 8 ] -=-=-=-=-=-=-=-=-=-
Bag: {
	size: 879
	n: 20
	values: [91,72,90,46,55,8,35,75,61,15,77,40,63,75,29,75,17,78,40,44]
	weights: [84,83,43,4,44,6,82,92,25,83,56,18,58,14,48,70,96,32,68,92]
	count: [10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10]
}
[ Success ]: Redundancy Test: Passed
[ Success ]: Test [ 8 ] ran successfully
Received Combo: [ 0, 0, 0, 10, 0, 0, 0, 0, 10, 0, 0, 7, 0, 10, 0, 0, 0, 10, 0, 0 ]
Expected Combo: [ 0, 0, 0, 10, 0, 0, 0, 0, 10, 0, 0, 7, 0, 10, 0, 0, 0, 10, 0, 0 ]
Received Value: { 2880 }
Expected Value: { 2880 }


Running Instancia [ 9 ] -=-=-=-=-=-=-=-=-=-
Bag: {
	size: 7
	n: 4
	values: [1,4,5,7]
	weights: [1,3,4,5]
	count: [10,10,10,10]
}
[ Success ]: Redundancy Test: Passed
[ Success ]: Test [ 9 ] ran successfully
Received Combo: [ 1, 2, 0, 0 ]
Expected Combo: [ 1, 2, 0, 0 ]
Received Value: { 9 }
Expected Value: { 9 }


Running Instancia [ 10 ] -=-=-=-=-=-=-=-=-=-
Bag: {
	size: 8
	n: 2
	values: [2,1]
	weights: [3,2]
	count: [10,10]
}
[ Success ]: Redundancy Test: Passed
[ Success ]: Test [ 10 ] ran successfully
Received Combo: [ 2, 1 ]
Expected Combo: [ 2, 1 ]
Received Value: { 5 }
Expected Value: { 5 }


Running Instancia [ 11 ] -=-=-=-=-=-=-=-=-=-
Bag: {
	size: 22
	n: 2
	values: [5,1]
	weights: [2,1]
	count: [10,10]
}
[ Success ]: Redundancy Test: Passed
[ Success ]: Test [ 11 ] ran successfully
Received Combo: [ 10, 2 ]
Expected Combo: [ 10, 2 ]
Received Value: { 52 }
Expected Value: { 52 }


[ Success ]: 11 of 11 tests passed

```
