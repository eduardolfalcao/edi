# InsertionSort

InsertionSort não está entre os melhores algoritmos de ordenação, mas em cenários práticos é um pouco melhor do que os algoritmos já estudados, SelectionSort e BubbleSort.

No SelectionSort, a ideia é selecionar a menor carta da mão esquerda e trazer para o fim da mão direita.
A ideia do InsertionSort é selecionar a próxima carta da mão esquerda e **inserir de modo ordenado na mão direita**. 

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

Quando fui implementar o InsertionSort, primeiramente pensei em um algoritmo que torna a implementação um pouco mais complexa.
Vou citar aqui pra que vocês tenham em mente a abordagem mais complexa, e evitem seguir este caminho.

Primeiro vamos implementar este algoritmo usando um array adicional, de mesmo tamanho. 
Neste caso, esta implementação é **out-of-place**.

**Algoritmo Insertion-Sort (mais difícil de implementar):**

Premissa: assuma que **v** é o vetor desordenado e **ordenado** é o vetor adicional
1. Para cada elemento em **v** a partir do índice 1 (elemento a ser inserido em *ordenado*)
2. Encontre o local de inserção ordenada no vetor **ordenado**. Atribua local à variável j.
3. Desloque uma posição à direita todos os elementos a partir de local até o "fim" de **ordenado**
4. Adicione o elemento em **ordenado[j]**

tempo | Mão Esquerda |  Mão Direita
:-------------------------:|:-------------------------:|:-------------------------:
t0 | 8, 2, 4, 3, 7 | VAZIO
t1 | 2, 4, 3, 7 | 8
t1.1 | 2, 4, 3, 7 | 8, 8
t2 | 4, 3, 7 | 2, 8
t2.1 | 4, 3, 7 | 2, 8, 8
t3 | 3, 7 | 2, 4, 8
t3.1 | 3, 7 | 2, 4, 4, 8
t4 | 7 | 2, 3, 4, 8
t4.1 | 7 | 2, 3, 4, 8, 8
t5 | VAZIO | 2, 3, 4, 7, 8

Agora vamos ver como ficou a implementação out-of-place desta abordagem.

```c
//insertionSort Out-of-Place
void insertionSortOP(int** v, int tamanho) {
    int* ordenado = (int*)malloc(tamanho * sizeof(int));
    ordenado[0] = (*v)[0];
    for (int i = 1; i < tamanho; i++) {     //i = indice da carta escolhida na mao esquerda        
        int j;
        for (j = 0; j < i; j++) {           //j eh a posicao correta na mao direita
            if(ordenado[j] > (*v)[i]) {     //achamos a posicao da insercao               
                for (int k = j; k < i; k++) {   //agora vamos abrir espaco
                    ordenado[k + 1] = ordenado[k];
                }
                break;
            }            
        }
        ordenado[j] = (*v)[i];        
    }
    (*v) = ordenado;
}
```

Não é muito difícil transformar esta implementação em in-place.

tempo | Vetor |
:-------------------------:|:-------------------------:
t0 | **8**, 2, 4, 3, 7 |
t1 | **2, 8**, 4, 3, 7 |
t2 | **2, 4, 8**, 3, 7 |
t3 | **2, 3, 4, 8**, 7 |
t4 | **2, 3, 4, 7, 8** |

```c
//insertionSort In-Place
void insertionSortIP(int* v, int tamanho) {
    for(int i = 1; i < tamanho; i++){   //i = indice da carta a ser inserida ordenada
        int j;
        for(j = 0; j < i; j++){     //j até i é são os limites do array ordenado
             if(v[j] > v[i]) {          //achamos a posicao da insercao
                for (int k = j; k < i; k++) {   //agora vamos abrir espaco
                    v[k + 1] = v[k];
                }
                break;
             }
        }
        v[j] = v[i];
    }
}
```

No entanto, existe uma outra abordagem para implementar o mesmo algoritmo, bastando para isso juntar os passos 2 e 3 em um único passo.
Basta ir trocando o elemento sendo ordenado com os elementos à sua esquerda, caso o elemento na posição anterior (esquerda) seja maior do que o elemento sendo ordenado.
Desta forma, abrir espaço para a inserção acontece de forma iterativa, até que o elemento sendo ordenado encontre sua posição.
Vejamos a ilustração.

tempo | array | comentário
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

```c
//insertionSort In-Place
void insertionSortIP(int* v, int tamanho) {
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
void insertionSortIP(int* v, int tamanho) {
    for (int i = 1; i < tamanho; i++) {   
        for (int j = i; j > 0 && v[j - 1] > v[j]; j--) {
            int temp = v[j - 1];
            v[j - 1] = v[j];
            v[j] = temp;
        }
    }
}
```

ou

```c
//insertionSort In-Place
void insertionSortIPV4(int* v, int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        int j = i;
        while (j > 0 && v[j - 1] > v[j]) {
            int temp = v[j - 1];
            v[j - 1] = v[j];
            v[j] = temp;
            j--;
        }
    }
}
```

Na versão anterior, nós fazemos algo semelhante a um BubbleSort inverso:
- **2,4,8**,3,7
- **2,4,3,8**,7
- **2,3,4,8**,7

Uma outra versão que executa menos operações seria a seguinte:
- **2,4,8**,3,7
- guarda o valor 3 em uma variável: valor = v[3];
- 2,4,8,8,7
- 2,4,4,8,7
- 2,3,4,8,7

```c
//insertionSort In-Place
void insertionSortIPV5(int* v, int tamanho) {
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

- No melhor caso, um array ordenado, InsertionSort é O(n). O for interno nunca é executado.
- No pior caso, um array ordenado de forma decrescente, InsertionSort é O(n²).






