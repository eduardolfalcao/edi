#include <stdlib.h>
#include <limits.h>

void printV(int* v, int tamanho) {
    printf("[");
    for (int i = 0; i < tamanho - 1; i++) {
        printf("%d, ", v[i]);
    }
    printf("%d]", v[tamanho - 1]);
}

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

void troca(int* v, int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


//selectionSort in-Place
void selectionSortIP(int* v, int tamanho) {
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

        //ao fim do for, o elemento em iMenor deve ser 
        //trocado com o elemento da posicao i
        troca(v, i, iMenor);
    }
}

void bubbleSortV1(int* v, int n) {
    for (int varredura = 0; varredura < n; varredura++) {
        for (int i = 0; i < n - 1; i++) {
            if (v[i] > v[i + 1]) {
                int temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
            }
        }
    }
}

void bubbleSortV2(int* v, int n) {
    for (int varredura = 0; varredura < n - 1; varredura++) {
        for (int i = 0; i < n - 1; i++) {
            if (v[i] > v[i + 1]) {
                int temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
            }
        }
    }
}

void bubbleSortV3(int* v, int n) {
    for (int varredura = 0; varredura < n - 1; varredura++) {
        for (int i = 0; i < n - varredura - 1; i++) {
            if (v[i] > v[i + 1]) {
                int temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
            }
        }
    }
}

void bubbleSort(int* v, int n) {
    for (int varredura = 0; varredura < n - 1; varredura++) {
        bool trocou = false;
        for (int i = 0; i < n - varredura - 1; i++) {
            if (v[i] > v[i + 1]) {
                int temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
                trocou = true;
            }
        }
        if (trocou == false)
            return;
    }
}

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

void insertionSortIPV1(int* v, int tamanho) {
    for (int i = 1; i < tamanho; i++) {   //i = indice da carta a ser inserida ordenada
        int j;
        for (j = 0; j < i; j++) {     //j até i é são os limites do array ordenado
            if (v[j] > v[i]) {          //achamos a posicao da insercao
                for (int k = j; k < i; k++) {   //agora vamos abrir espaco
                    v[k + 1] = v[k];
                }
                break;
            }
        }
        v[j] = v[i];
    }
}

void insertionSortIPV2(int* v, int tamanho) {
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

void insertionSortIPV3(int* v, int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        for (int j = i; j > 0 && v[j - 1] > v[j]; j--) {
            int temp = v[j - 1];
            v[j - 1] = v[j];
            v[j] = temp;
        }
    }
}

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

void merge(int* v, int tamV, int* e, int tamE, int* d, int tamD) {
    int indexV = 0;
    int indexE = 0;
    int indexD = 0;
    while (indexE < tamE && indexD < tamD) {
        if (e[indexE] <= d[indexD]) {
            v[indexV] = e[indexE];
            indexE++;
        }
        else {
            v[indexV] = d[indexD];
            indexD++;
        }
        indexV++;
    }
    //ainda poderíamos ter elementos no vetor E que não foram copiados para V
    while (indexE < tamE) {
        v[indexV] = e[indexE];
        indexE++;
        indexV++;
    }
    //ainda poderíamos ter elementos no vetor D que não foram copiados para V
    while (indexD < tamD) {
        v[indexV] = d[indexD];
        indexD++;
        indexV++;
    }
}

void mergeSort(int* v, int tamV) {
    if (tamV > 1) {
        //primeiro quebramos o vetor em 2 vetores menores
        int meio = tamV / 2;

        int tamV1 = meio;
        int* v1 = (int*)malloc(tamV1 * sizeof(int));
        for (int i = 0; i < meio; i++) {
            v1[i] = v[i];
        }

        int tamV2 = tamV - meio;
        int* v2 = (int*)malloc(tamV2 * sizeof(int));
        for (int i = meio; i < tamV; i++) {
            v2[i - meio] = v[i];
        }

        mergeSort(v1, tamV1);
        mergeSort(v2, tamV2);
        merge(v, tamV, v1, tamV1, v2, tamV2);

        free(v1);
        free(v2);
    }
}

int particiona(int* v, int ini, int fim) {
    int pIndex = ini;
    int pivo = v[fim];
    for (int i = ini; i < fim; i++) {
        if (v[i] <= pivo) {
            troca(v, i, pIndex);
            pIndex++;
        }
    }
    troca(v, pIndex, fim);
    return pIndex;
}

void quickSort(int* v, int ini, int fim) {
    if (fim>ini) {
        int indexPivo = particiona(v, ini, fim);
        quickSort(v, ini, indexPivo - 1);
        quickSort(v, indexPivo + 1, fim);   //indexPivo já está no seu local
    }
}
