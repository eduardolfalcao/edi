# InsertionSort

## Estratégia do algoritmo de acordo com seu nome
 
 - Ordenação por inserção
 - Escolhe um elemento do vetor desordenado, e insere no vetor ordenado na posição correta (que mantenha o vetor ordenado)
 - Se no SelectionSort, a ideia é selecionar a menor carta da mão esquerda e trazer para o fim da mão direita, no InsertionSort a ideia é selecionar a próxima carta da mão esquerda e **inserir de modo ordenado na mão direita**.
 
## Ilustração do funcionamento do algoritmo

Imagine um jogador com as seguintes cartas: 8, 2, 4, 3, 7 (não interessando o naipe). 
Vamos aplicar a ideia do InsertionSort e ilustrar na tabela a seguir.

tempo | Mão Esquerda |  Mão Direita
:-------------------------:|:-------------------------:|:-------------------------:
t0 | 8, 2, 4, 3, 7 | VAZIO
t1 | 2, 4, 3, 7 | 8
t2 | 4, 3, 7 | 2, 8
t3 | 3, 7 | 2, 4, 8
t4 | 7 | 2, 3, 4, 8
t5 | VAZIO | 2, 3, 4, 7, 8

Não é muito difícil pensar no funcionamento in-place desse algoritmo.
Considere que os números em negrito já estão ordenados. 

tempo | Vetor |
:-------------------------:|:-------------------------:
t0 | **8**, 2, 4, 3, 7 |
t1 | **2, 8**, 4, 3, 7 |
t2 | **2, 4, 8**, 3, 7 |
t3 | **2, 3, 4, 8**, 7 |
t4 | **2, 3, 4, 7, 8** |

Agora uma ilustração com mais detalhes, que se aproxima mais da implementação.

tempo | Vetor | comentário
:-------------------------:|:-------------------------:|:-------------------------:
t0 | **8**,2,4,3,7 | [8] já está ordenado, e [2, 4, 3, 7] desordenado
t1 | **2,8**,4,3,7 | 2 é menor que 8, por isso trocamos 2 e 8; **[2,8]** já está ordenado, e [4, 3, 7] desordenado
t2 | **2,4,8**,3,7 | 4 é menor que 8, por isso trocamos 4 e 8
t3 | **2,4,8**,3,7 | 4 não é menor que 2, por isso não trocamos 4 e 2; **[2,4,8]** já está ordenado, e [3, 7] desordenado
t4 | **2,4,3,8**,7 | 3 é menor que 8, por isso trocamos 8 e 3;
t5 | **2,3,4,8**,7 | 3 é menor que 4, por isso trocamos 4 e 3;
t6 | **2,3,4,8**,7 | 3 não é menor que 2, por isso não trocamos 2 e 3; **[2,3,4,8]** já está ordenado, e [7] desordenado 
t7 | **2,3,4,7,8** | 7 é menor que 8, por isso trocamos 8 e 7; 
t7 | **2,3,4,7,8** | 7 é não menor que 4, por isso não trocamos 4 e 7; todo o array está ordenado: **[2,3,4,7,8]**

## Código

Agora vamos ver como ficou a implementação out-of-place desta abordagem.

```c
//insertionSort Out-of-Place
void insertionSort(int** v, int tamanho) {
    int* ordenado = (int*)malloc(tamanho * sizeof(int));
    ordenado[0] = (*v)[0];
    for (int i = 1; i < tamanho; i++) {     //i = indice da carta escolhida na mao esquerda        
        int j;
        for (j = 0; j < i; j++) {           //j eh a posicao correta na mao direita
            if(ordenado[j] > (*v)[i]) {     //achamos a posicao da insercao               
                for (int k = i; k > 0; k--) {   //agora vamos abrir espaco
                    ordenado[k] = ordenado[k-1];
                }
                break;
            }            
        }
        ordenado[j] = (*v)[i];        
    }
    (*v) = ordenado;
}
```

Agora vamos ver a implementação in-place.

```c
//insertionSort In-Place
void insertionSort(int* v, int tamanho) {
    for (int i = 1; i < tamanho; i++) {   //i = indice da carta a ser inserida ordenada
        for (int j = i; j > 0; j--) {
            if (v[j - 1] > v[j]) {
                int temp = v[j - 1];
                v[j - 1] = v[j];
                v[j] = temp;
            }
            else {
                break;
            }
        }
    }
}
```

Refatorando:

```c
//insertionSort In-Place
void insertionSort(int* v, int tamanho) {
    for (int i = 1; i < tamanho; i++) {   
        for (int j = i; j > 0 && v[j - 1] > v[j]; j--) {
            int temp = v[j - 1];
            v[j - 1] = v[j];
            v[j] = temp;
        }
    }
}
```

Na versão anterior, nós fazemos algo semelhante a um BubbleSort inverso - escolhemos um elemento e fazemos ele flutuar (para a esquerda, por isso chamei de inverso) para a posição correta:
- **2,4,8**,3,7
- **2,4,3,8**,7
- **2,3,4,8**,7

Uma outra versão que executa menos operações seria a seguinte:
- **2,4,8**,3,7
- guarda o valor 3 em uma variável, e.g., valor = v[3], e move todos os elementos maiores do que valor uma posição para a direita
  - 2,4,8,8,7
  - 2,4,4,8,7
- no final, atribui valor na última posição maior do que valor
  - 2,3,4,8,7

```c
//insertionSort In-Place
void insertionSort(int* v, int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        int valor = v[i];
        int j;
        for (j = i; j > 0 && v[j - 1] > valor; j--) {
            v[j] = v[j - 1];
        }
        v[j] = valor;
    }
}
```

## Análise Assintótica

```c
void insertionSort(int* v, int tamanho) {
    for (int i = 1; i < tamanho; i++) {                  // i assume os valores {1, 2, ..., n-1}  
        int valor = v[i];                                // essa inicialização/atribuição executa n-1 vezes
        int j;                                           // essa alocação executa n-1 vezes
        for (j = i; j > 0 && v[j - 1] > valor; j--) {    
            v[j] = v[j - 1];                            // essa atribuição executa n²/2 - n/2 vezes
            // quando i=1; j assume os valores {1}; em suma, executa 1 vezes
                //lembrando que j chega a assumir o valor 0, porém esse valor não satisfaz a condicional de execução do laço, e portanto o código de dentro desse for não executará quando j=0
            // quando i=2; j assume os valores {1, 2}; em suma, executa 2 vezes
            // quando i=3; j assume os valores {1, 2, 3}; em suma, executa 3 vezes
            //...
            // quando i=n-1; j assume os valores {1, 2, 3, ..., n-1}; em suma, executa n-1 vezes
            // Fórmula geral da soma dos termos de uma PA: Sn = n(a1+an)/2
            // Sn-1 = (n-1) * (1+n-1)/2 = n * (n-1) / 2
        }
        v[j] = valor;                                    // essa atribuição executa n-1 vezes
    }
}
```

No pior caso, o InsertionSort é proporcional ao tamanho do vetor ao quadrado, ou seja, O(n²).
No melhor caso, o InsertionSort é Ômega(n).
Isso acontece quando o vetor está ordenado.
Note que a condicional "v[j - 1] > valor" nunca será satisfeita, e dessa forma o trecho de código que possui complexidade quadrática (for interno) não executaria.

Porém, note que o InsertionSort é ligeiramente mais inteligente do que o BubbleSort.
Ele consegue detectar intervalos do vetor que estão ordenados, e evita esforço adicional nesses intervalos, enquanto o BubbleSort só consegue tirar proveito da identificação de que um vetor está completamente ordenado.
Por essa razão, o InsertionSort é um algoritmo utilizado em conjunto com outros algoritmos, como por exemplo o MergeSort, para melhorar ainda mais o desempenho deles.

## Resumo

In-place, estável, O(n²), Ômega(n).
