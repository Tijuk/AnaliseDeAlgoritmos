# Relatorio T3

**Matéria:** INF1721 - Análise de Algoritmos  
**Período:** 2019.1  
**Professor:** Marco Molinaro  
**Turma**: 3WA  
**Grupo**: Alexandre Dias  

# Problema de Knapsack

O problema 10-Knapsack é o seguinte: temos uma mochila de tamanho **B** e **n** itens, onde o item **i** tem tamanho **wi** e valor **vi**. Porém agora temos 10 unidades de cada item. O objetivo é selecionar uma quantidade de cada itens (de 0 a 10) de forma que caibam na mochila (i.e., soma dos tamanho é menor que B) e que obtenha valor máximo. 

*Assuma que todos os dados **B**, **w1**, ..., **wn**, **v1**, ..., **vn** são inteiros não-negativos.*

# Resolução do Problema

Para resolver o problema, dividiremos o problema em diversos sub-problemas.
Dado uma mochila de tamanho **B** e **n** itens, montaremos uma matrix com n linhas e B colunas.  

Nessa matrix, cada entrada será um sub-problema de capacidade *w*, onde *w* é o iterador da coluna.  

Para cada sub-problema, consideraremos o valor ao adicionar a menor quantidade necessária para preencher a entrada (de forma que o peso não estoure o limite do sub-problema) ou a quantidade existente daquele item ( no caso, para todos os itens, o valor é 10 )  

# Recorrencia

Para cada sub-problema, deveremos olhar no subproblema do item anterior para podermos definir o valor do atual sub-problema. Dessa forma utilizaremos uma função de recorrencia, porém, em formato de matrix para não termos que iterar por todos os sub-problemas a cada novo sub-problema.

```.c

// Sem Cache (Recursão)
void opt(int i, int w) {
	int a,b;
	int pesoTotal;
	int opt_i_menos_1 = opt(i - 1, w); // valor no item anterior
	int valor_de_retorno;
	// Atualiza o cache para o valor do item anterior naquele peso
	for(int qtd = 0; qtd < 10; qtd++) { // para cada repetição do item (max: 10)
		pesoTotal = item[i].peso * qtd;
		if(pesoTotal <= w) { // Peso total dos itens não estoura o peso do sub-problema
			a = opt(i - 1, w - pesoTotal) + qtd * item[i].valor;
			b = opt_i_menos_1;
			valor_de_retorno = max(a,b);
		} else {
			break;
		}
	}
	return valor_de_retorno;
}

// Com Cache
void opt(int i, int w) {
	int a,b;
	int pesoTotal;
	cache[i][w] = cache[i - 1][w];
	// Atualiza o cache para o valor do item anterior naquele peso
	for(int qtd = 0; qtd < 10; qtd++) { // para cada repetição do item (max: 10)
		pesoTotal = item[i].peso * qtd;
		if(pesoTotal <= w) { // Peso total dos itens não estoura o peso do sub-problema
			a = cache[i - 1][w - pesoTotal] + qtd * item[i].valor;
			b = cache[i][w];
			cache[i][w] = max(a,b);
		}
	}
}
```
  


# Obtendo a melhor combinação

Após preencher a matriz de recorrencia (vulgo cache), devemos percorrer ela do final até o inicio, decodificando-a para decidirmos qual é a combinação para atingir o valor encontrado.

  Para cada item, iremos percorrer até 10 vezes, testando o valor para saber se ele faz ou não parte da melhor combinação.

  Devemos armazenar o valor do peso restante dentro da bolsa ( *peso_restante* ), e ir atualizando conforme formor testando itens.

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