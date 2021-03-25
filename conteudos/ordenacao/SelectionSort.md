# SelectionSort

SelectionSort é um dos algoritmos de ordenação mais simples e intuitivo. 
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

Note, que na nossa ilutração, baixamos o nível de abstração: em vez de termos *Mão Esquerda* e *Mão Direita*, teremos *Array Original* e *Array Ordenado*.
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

Segue implementação do SelectionSort out-of-place.

```c
//selectionSort Out-of-Place
void selectionSortOP(int** v, int tamanho){
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

Apesar da implementação out-of-place ser um pouco mais simples, também é possível implementar o SelectionSort in-place.
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

Segue implementação do SelectionSort in-place.

```c
//selectionSort in-Place
void selectionSortIP(int* v, int tamanho) {
    for (int i = 0; i < (tamanho - 1); i++) {
        //tamanho - 1 pois qdo ordenamos n-1 elementos, 
        //o ultimo elemento ja estara na posicao correta

        int iMenor = i;     //procuraremos o menor elemento a partir do indice i                    
        for (int j = i+1; j < tamanho; j++) {
            //quando i = 0, j in {1,n}; ou seja, n-1 comparações
            //quando i = 1, j in {2,n}; ou seja, n-2 comparações
            //quando i = 2, j in {3,n}; ou seja, n-3 comparações
            //...
            //quando i = n-1, j in {n-1,n}; ou seja n-(n-1) = 1 comp
            //1 + 2 + 3 + ... + (n-3) + (n-2) + (n-1)
            //aplicaria a fórmula da PA
            //Sn = n(a1+an)/2
            //Sn = (n-1)*(1+n-1)/2 = (n-1)*n/2 = (n²-n)/2

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

A performance do SelectionSort é pior do todos os algoritmos de estruturas que estudamos até agora na disciplina.
Até agora, nosso pior caso era varrer um vetor do começo ao fim, o que nos remetia a *O(n)*.
Porém, no SelectionSort, nós varremos um vetor múltiplas vezes.
Na primeira vez visitamos n-1 índices do array, na segunda vez visitamos n-2 índices do array, na terceira vez visitamos n-3 índices do array, e este padrão se segue até que quase todo o array esteja ordenado, onde visitaremos 1 índice do array.
Logo, note que teremos (n-1) + (n-2) + (n-3) + ... + 1, que na verdade é uma P.A. de razão 1.
Resolvendo esta equação, vamos ter um polinômio de segundo grau na forma an² + bn + c.
**Por isso dizemos que o SelectionSort é O(n²), que é um desempenho muito pior do que O(n).**

Nota: embora análise de complexidade não seja um tópico de estudo dessa disciplina, sempre iremos discutir em alto nível o desempenho dos algoritmos, para entendermos por quais razões um algoritmo é considerado menos performático do que outro.