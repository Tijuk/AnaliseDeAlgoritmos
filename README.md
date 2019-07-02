![Logo da PUC](https://exarandorum.files.wordpress.com/2015/01/brasaov.png)

Esse repositório possui 3 trabalhos para a disciplina **INF1721 - Análise de Algoritmos** oferecida pela PUC-Rio.  
Período: 2019.1  
Professor: [Marco Molinaro](http://www-di.inf.puc-rio.br/~mmolinaro/)  

# 1. Descrição de cada Trabalho

## 1.1 T1 - Mediana das Medianas

É um problema que deve implementar uma função que obtenha o k-ésimo elemento de um vetor com complexidade **O(n)**.  
Para isso, foi implementado uma busca utilizando o método de **Mediana das Medianas**.

## 1.2 T2 - ...

(Incompleto)

## 1.3 T3 - Algoritmo Dinâmico

É um problema onde é necessário implementar uma função que resolva uma variante do problema de [**Knapsack**](https://en.wikipedia.org/wiki/Knapsack_problem), utilizando algoritmo dinâmico.  
Nesse caso, queremos resolver a variante **Bounded Knapsack** mas com limite máximo de cada item fixo em 10.

# 2. Como rodar o programa

## 2.1 T1 - HTML

Ao clonar o repositório, dentro da pasta **T1**, existe um arquivo .html chamando [TrabalhoAlgoritmo.html](https://github.com/Tijuk/AnaliseDeAlgoritmos/blob/master/T1/TrabalhoAlgoritmo.html).  
Para iniciar a execução do programa, basta abrir o arquivo em um browser ( o browser que utilizei para o project, foi o Google Chrome ).  

*Tecnologias usadas: HTML, JS, Bootstrap*
*Pré-requisitos para rodar: qualquer browser (preferencialmente Google Chrome)*

## 2.2 T2 - Python(?)

...

## 2.3 T3 - C

### Para Windows
Ao clonar o repositório, dentro da pasta **T3_emC**, existe um arquivo .bat chamando [run.bat](https://github.com/Tijuk/AnaliseDeAlgoritmos/blob/master/T3_emC/run.bat).  
Para iniciar a execução, abra o terminal, navegue para a pasta **T3_emC** e rode o **run.bat**

### Para Unix (não testado)

1. Abra o terminal e vá para a pasta **T3_emC**
2. (apenas na primeira vez) Rode o seguinte código.
```.sh
echo gcc -o ./executable ./main.c ./bag.c ./log.c ./test.c ./knapsack.c > ./run_unix
echo ./executable >> ./run_unix
chmod +x ./run_unix
```
3. Rode ./run_unix

*Tecnologias usadas: gcc, C*
*Pré-requisitos para rodar: gcc*
