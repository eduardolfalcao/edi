# SelectionSort

## Estratégia do algoritmo de acordo com seu nome

 - **selecionar** os menores valores e posicionar no final do vetor ordenado
   - selecionamos o menor valor do vetor e trocamos de posição com o primeiro elemento
   - selecionamos o segundo menor valor do vetor e trocamos de posição com o segundo elemento
- repetindo esse procedimento conseguimos ordenar um vetor com a estratégia da **seleção**

## Ilustração do funcionamento do algoritmo

Uma forma de explicá-lo é tomar como exemplo a forma como muitas pessoas ordenam cartas de baralho nas mãos.
Imagine um jogador com as seguintes cartas: 8, 2, 4, 3, 7 (não interessando o naipe). 
Uma forma de ordenar essas cartas seria transferir as cartas de menor valor da mão esquerda para a mão direita, uma por uma.
Veja o funcionamento ilustrado na tabela a seguir.

tempo | Mão Esquerda |  Mão Direita
:-------------------------:|:-------------------------:|:-------------------------:
t0 | 8, 2, 4, 3, 7 | VAZIO
t1 | 8, 4, 3, 7 | 2
t2 | 8, 4, 7 | 2, 3
t3 | 8, 7 | 2, 3, 4
t4 | 8 | 2, 3, 4, 7
t5 |  VAZIO | 2, 3, 4, 7, 8

A maneira mais simples de implementar este algoritmo é usando um array adicional, de mesmo tamanho. 
Neste caso, esta implementação seria **out-of-place**.
Para ficar mais claro, um algoritmo de ordenação é **in-place** quando usamos apenas algumas variáveis para viabilizar o algoritmo, mas essa quantidade de espaço requerida não muda com o tamanho do array.

Note, que na nossa ilustração, baixamos o nível de abstração: em vez de termos *Mão Esquerda* e *Mão Direita*, teremos *Array Original* e *Array Ordenado*.
Outro ponto a ser percebido é que toda vez que  o menor valor do *Array Original* for copiado para o *Array Ordenado* substituiremos seu valor no *Array Original* pelo maior valor de int que C puder reconhecer, representado aqui por *MAX*.
Desta forma, MAX não será escolhida nas próximas iterações visto que não será o menor valor.

tempo | Array Original |  Array Ordenado
:-------------------------:|:-------------------------:|:-------------------------:
t0 | 8, 2, 4, 3, 7 | VAZIO
t1 | 8, MAX, 4, 3, 7 | 2
t2 | 8, MAX, 4, MAX, 7 | 2, 3
t3 | 8, MAX, MAX, MAX, 7 | 2, 3, 4
t4 | 8, MAX, MAX, MAX, MAX | 2, 3, 4, 7
t5 |  MAX, MAX, MAX, MAX, MAX | 2, 3, 4, 7, 8

Apesar da ilustração e implementação da versão out-of-place ser um pouco mais simples, também é possível implementar o SelectionSort in-place.
Para isto, na primeira iteração, basta varrer o array procurando pelo menor elemento, e quando encontrar o menor elemento, trocamos de posição este elemento com o primeiro elemento do array.
Em seguida, fazemos algo semelhante, mas agora não precisamos varrer o array desde o início, pois o primeiro elemento já está ordenado. Em vez disso, ao encontrarmos o segundo menor elemento, trocamos ele de posição com o segundo elemento do array, i.e., o elemento no índice 1.
Fazemos isto sucessivamente, até procurarmos no penúltimo menor elemento do array, pois nesta situação, o último já estará ordenado. 

Segue ilustração. Note que a sequência em negrito já é a sub-sequência considerada ordenada:

tempo | Array Original |  Comentário
:-------------------------:|:-------------------------:|:-------------------------:
t0 | 8, 2, 4, 3, 7 | vamos trocar o menor elemento, 2, com o elemento no índice 0, 8
t1 | **2**, 8, 4, 3, 7 | vamos trocar o segundo menor elemento, 3, com o elemento no índice 1, 8 
t2 | **2, 3**, 4, 8, 7 | 4 é o terceiro menor elemento e já está na posição correta, por isso não precisaremos fazer nada
t3 | **2, 3, 4**, 8, 7 | vamos trocar o quarto e penúltimo menor elemento, 7, com o elemento no índice 3, 8
t4 | **2, 3, 4, 7**, 8 | note que quando ordenamos n-1 elementos, o último elemento estará naturalmente ordenado, por isso, não precisamos fazer mais nada
t5 |  **2, 3, 4, 7, 8** | 


## Código

Segue implementação do SelectionSort out-of-place.

```c
//selectionSort Out-of-Place
void selectionSort(int** v, int tamanho){
    int* ordenado = (int *) malloc(tamanho*sizeof(int));
    for(int i = 0; i < tamanho; i++){
        int iMenor = 0;
        for(int j = 0; j < tamanho; j++){
            if((*v)[j] < (*v)[iMenor]){
                iMenor = j;
            }
        }
        ordenado[i] = (*v)[iMenor];
        (*v)[iMenor] = INT_MAX;        
    }
    (*v) = ordenado;
}
```

Segue implementação do SelectionSort in-place.

```c
//selectionSort in-Place
void selectionSort(int* v, int tamanho) {
    for (int i = 0; i < (tamanho - 1); i++) {
        //tamanho - 1 pois qdo ordenamos n-1 elementos, 
        //o ultimo elemento ja estara na posicao correta

        int iMenor = i;     //procuraremos o menor elemento a partir do indice i                    
        for (int j = i+1; j < tamanho; j++) {
            //j = i + 1, pois nao precisamos comparar 
            //o valor no indice i com ele mesmo

            //nesse for vamos ate a ultima posicao, 
            //pois o menor elemento pode estar la 

            if (v[j] < v[iMenor]) {
                iMenor = j;
            }
        }

        //ao fim do for, o elemento em iMenor deve ser trocado com o elemento da posicao i
        troca(v, i, iMenor);
    }
}

//troca deve ser declarado antes de selectionSortIP
void troca(int* v, int i, int j){
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
```

## Análise Assintótica

```c
//selectionSort in-Place
void selectionSortIP(int* v, int tamanho) {
    for (int i = 0; i < (tamanho - 1); i++) {
        int iMenor = i;                         // essa inicialização/atribuição executa n-1 vezes              
        for (int j = i+1; j < tamanho; j++) {
            if (v[j] < v[iMenor]) {            // essa condicional executa n²/2 - n/2 vezes
                iMenor = j;
            }                                        
            //quando i=0, j assume os valores {1, 2, ..., n-1};  em suma, executa n-1 vezes
                //lembrando que j chega a assumir o valor n, porém esse valor não satisfaz a condicional de execução do laço, e portanto o <código> de dentro desse for não executará quando j=n
            //quando i=1, j assume os valores {2, ..., n-1}; em suma, executa n-2 vezes
            //quando i=2, j assume os valores {3, ..., n-1};  em suma, executa n-3 vezes
            //...
            //quando i=n-1, j assume os valores {n-1};  em suma, executa 1 vez
            //1 + 2 + 3 + ... + (n-3) + (n-2) + (n-1)
            // Fórmula geral da soma dos termos de uma PA: Sn = n(a1+an)/2
            // Sn-1 = (n-1) * (1+n-1)/2 = n * (n-1) / 2
        }       
        troca(v, i, iMenor);                // essa função executa n-1 vezes
    }
}

void troca(int* v, int i, int j){    //O(1)
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
```

A performance do SelectionSort é pior do que todos os algoritmos de estruturas que estudamos até agora na disciplina.
Até agora, nosso pior caso era varrer um vetor do começo ao fim, o que nos remetia a *O(n)*.
Porém, no SelectionSort, nós varremos um vetor múltiplas vezes.
Na primeira vez visitamos n-1 índices do array, na segunda vez visitamos n-2 índices do array, na terceira vez visitamos n-3 índices do array, e este padrão se segue até que quase todo o array esteja ordenado, onde visitaremos 1 índice do array.
Logo, note que teremos (n-1) + (n-2) + (n-3) + ... + 1, que na verdade é uma P.A. de razão 1.
Resolvendo esta equação, vamos ter um polinômio de segundo grau, o que nos confirma que o SelectionSort é O(n²).
Além disso, note que o SelectionSort não "consegue descobrir" que um vetor já está ordenado com o objetivo de evitar comparações desnecessárias.
Em outras palavras, não há situação específica que faça com que o SelectionSort execute menos instruções.
Por isso, também podemos afirmar que o SelectionSort é Ômega(n²).

## Resumo

In-place, instável, O(n²), Ômega(n²), portanto, Theta(n²).
