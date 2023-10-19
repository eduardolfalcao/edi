# BubbleSort

## Estratégia do algoritmo de acordo com seu nome

 - fazer os maiores valores do vetor flutuarem para o final do vetor;
 - assim como bolhas de ar embaixo d'água flutuam mais rapidamente para a superfície de acordo com seu tamanho, os maiores valores do vetor devem "flutuar" mais rapidamente para o fim do vetor;
 - isso é tudo que precisamos lembrar para começar a estudar o bubblesort.

## Ilustração do funcionamento do algoritmo

Considere o seguinte array: **int v[7] = {2, 8, 6, 10, 4, 5, 3}**.

Nosso objetivo é reorganizar o array **v** em ordem crescente.
O que o BubbleSort propõe, é que varramos esse array da esquerda para direita, múltiplas vezes.
Em cada passada, iremos comparar os elementos vizinhos, e trocamos eles de posição caso o elemento da esquerda seja maior que o elemento da direita.
Isto deve ser feito até chegar ao fim do array (ou pelo menos até a parte do array que ainda está desordenada).

varredura | tempo | array |  
:-------------------------:|:-------------------------:|:-------------------------:
1 | t1 | **2, 8**, 6, 10, 4, 5, 3
1 | t2 | 2, **8, 6**, 10, 4, 5, 3
1 | t3 | 2, 6, **8, 10**, 4, 5, 3
1 | t4 | 2, 6, 8, **10, 4**, 5, 3
1 | t5 | 2, 6, 8, 4, **10, 5**, 3
1 | t6 | 2, 6, 8, 4, 5, **10, 3**
1 | t7 | 2, 6, 8, 4, 5, 3, **10**
||
2 | t1 | **2, 6**, 8, 4, 5, 3, **10**
2 | t2 | 2, **6, 8**, 4, 5, 3, **10**
2 | t3 | 2, 6, **8, 4**, 5, 3, **10**
2 | t4 | 2, 6, 4, **8, 5**, 3, **10**
2 | t5 | 2, 6, 4, 5, **8, 3**, **10**
2 | t6 | 2, 6, 4, 5, 3, **8, 10**
||
3 | t1 | **2, 6**, 4, 5, 3, **8, 10**
3 | t2 | 2, **6, 4**, 5, 3, **8, 10**
3 | t3 | 2, 4, **6, 5**, 3, **8, 10**
3 | t4 | 2, 4, 5, **6, 3**, **8, 10**
3 | t5 | 2, 4, 5, 3, **6, 8, 10**
||
4 | t1 | **2, 4**, 5, 3, **6, 8, 10**
4 | t2 | 2, **4, 5**, 3, **6, 8, 10**
4 | t3 | 2, 4, **5, 3**, **6, 8, 10**
4 | t4 | 2, 4, 3, **5, 6, 8, 10**
||
5 | t1 | **2, 4**, 3, **5, 6, 8, 10**
5 | t2 | 2, **4, 3**, **5, 6, 8, 10**
5 | t3 | 2, 3, **4, 5, 6, 8, 10**
||
6 | t1 | **2, 3**, **4, 5, 6, 8, 10**
6 | t2 | **2, 3, 4, 5, 6, 8, 10**

## Código

Uma primeira implementação para BubbleSort seria:

```c
void bubbleSort(int* v, int n){    
    for(int varredura = 0; varredura < n; varredura++){
        for(int i = 0; i < n-1; i++){
            if(v[i]>v[i+1]){
                int temp = v[i];
                v[i] = v[i+1];
                v[i+1] = temp;
            }
        }
    }
}
```

Aprimoramento 1: apenas n-1 varreduras são necessárias (vide tabela que construímos).

```c
void bubbleSort(int* v, int n){    
    for(int varredura = 0; varredura < n-1; varredura++){
        for(int i = 0; i < n-1; i++){
            if(v[i]>v[i+1]){
                int temp = v[i];
                v[i] = v[i+1];
                v[i+1] = temp;
            }
        }
    }
}
```

Aprimoramento 2: a medida em que a quantidade de varreduras aumenta, a parte final do array já estará ordenada. Logo, não precisamos varrer até n-1, mas apenas até n-varreduras-1.

```c
void bubbleSort(int* v, int n){    
    for(int varredura = 0; varredura < n-1; varredura++){
        for(int i = 0; i < n-varredura-1; i++){
            if(v[i]>v[i+1]){
                int temp = v[i];
                v[i] = v[i+1];
                v[i+1] = temp;
            }
        }
    }
}
```

Aprimoramento 3: se na primeira varredura não houve nenhuma troca, então o array está ordenado, e podemos terminar o procedimento sem precisar fazer novas varreduras.

```c
void bubbleSort(int* v, int n){    
    for(int varredura = 0; varredura < n-1; varredura++){
        bool trocou = false;
        for(int i = 0; i < n-varredura-1; i++){
            if(v[i]>v[i+1]){
                int temp = v[i];
                v[i] = v[i+1];
                v[i+1] = temp;
                trocou = true;
            }
        }
        if(trocou==false)
            return;
    }
}
```

## Análise Assintótica

```c
void bubbleSort(int* v, int n){    
    for(int varredura = 0; varredura < n-1; varredura++){
        bool trocou = false;                            // essa inicialização/atribuição executa n-1 vezes
        for(int i = 0; i < n-varredura-1; i++){
            <código>                                    // o trecho de código dentro do for executa n²/2 - n/2 vezes

            // quando varredura=0; i assume os valores {0, 1, 2, ..., n-0-2}; em suma, executa n-1 vezes
                //lembrando que i chega a assumir o valor n-1, porém esse valor não satisfaz a condicional de execução do laço, e portanto o <código> de dentro desse for não executará quando i=n-1
            // quando varredura=1; i assume os valores {0, 1, 2, ..., n-1-2}; em suma, executa n-2 vezes
            // quando varredura=2; i assume os valores {0, 1, 2, ..., n-2-2}; em suma, executa n-3 vezes
            // ...
            // quando varredura=n-2; i assume os valores {n-(n-2)-2}, ou seja, {0}; em suma, executa 1 vez
            // Fórmula geral da soma dos termos de uma PA: Sn = n(a1+an)/2
            // Sn-1 = (n-1) * (1+n-1)/2 = n * (n-1) / 2
        }
        if(trocou==false)                              // essa condição é verificada n-1 vezes
            return;
    }
}
```

No pior caso, o BubbleSort é proporcional ao tamanho do vetor ao quadrado, ou seja, O(n²).
No melhor caso, o BubbleSort é Ômega(n).
Isso acontece pois na primeira execução do for interno, iterando n-1 vezes, nenhuma troca aconteceria.
Dessa forma, a condicional que verifica a ocorrência de trocas perceberia que o vetor já estaria ordenado, e encerraria a ordenação sem precisar executar o for interno outras vezes.
Note, portanto, que o for externo só executaria a primeira iteração (varredura=0), executando uma única varredura no vetor.

Comparando situações de melhor caso (vetor já está ordenado), o BubbleSort é ligeiramente melhor do que o SelectionSort pois seu melhor caso é Ômega(n)  e o melhor caso do SelectionSort é Ômega(n²).

## Resumo

In-place, estável, O(n²), Ômega(n).
