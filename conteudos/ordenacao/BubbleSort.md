# BubbleSort

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

Aprimoramento 3: se na primeira varredura nã houve nenhuma troca, então o array está ordenado, e podemos terminar o procedimento sem precisar fazer novas varreduras.

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

In-place, estável, O(n²) no pior caso, O(n) no melhor caso.