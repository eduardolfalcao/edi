#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void inicializar(int ** pilha, int capacidade){
    (*pilha) = (int*) calloc(capacidade, sizeof(int));
}

void duplicarCapacidade(int ** pilha, int* capacidade){
    (*pilha) = (int*)realloc((*pilha), 2 * (*capacidade) * sizeof(int));
    (*capacidade) = (*capacidade) * 2;
}

void empilhar(int** pilha, int valor, int * tamanho, int* capacidade){
    if((*tamanho) == (*capacidade)){
        duplicarCapacidade(pilha, capacidade);
    }
    (*pilha)[(*tamanho)] = valor;
    (*tamanho)++;
}

void desempilhar(int * tamanho){
    if((*tamanho)>0)
        (*tamanho)--;
}

int desempilharRetornando(int * pilha, int * tamanho){
    if ((*tamanho) > 0) {
        (*tamanho)--;
        return pilha[(*tamanho)];
    }
    else {
        return INT_MIN;
    }
}

int topo(int * pilha, int tamanho){
    if(tamanho == 0)
        return INT_MIN;
    else
        return pilha[tamanho-1];
}

bool vazia(int tamanho){
    if(tamanho==0)
        return true;
    else
        return false;
}

void imprimir(int * pilha, int * tamanho){
    printf("_\n");
    for(int i = (*tamanho) - 1; i >= 0; i--){
        printf("%d\n",pilha[i]);
    }
    printf("_\n\n");
}