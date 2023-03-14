#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct FilaArray {
    int frente;
    int tras;
    int elementos[10];
};

bool vazia(struct FilaArray* fila) {
    if (fila == NULL)
        return false;
    else if (fila->frente == -1 && fila->tras == -1)
        return true;
    else return false;
}

void enfileirar(struct FilaArray* fila, int val) {
    if (fila == NULL)
        return;
    //if (tamanho(fila) == sizeof(fila->elementos))   //fila cheia
    int n = sizeof(fila->elementos) / sizeof(int);
    if ((fila->tras+1)%n == fila->frente)   //fila cheia
        return;
    if (vazia(fila)) {                              //fila vazia
        fila->frente = 0;
        fila->tras = 0;
    } 
    else {
        fila->tras = (fila->tras + 1) % n;          //fila circular
    }
    fila->elementos[fila->tras] = val;
}

int desenfileirar(struct FilaArray* fila) {
    int val = INT_MIN;
    if (fila == NULL)
        return val;
    if (vazia(fila)) {   
        return val;
    }
    //se chegamos aqui, existe elemento para desempilhar
    val = fila->elementos[fila->frente];
    if (fila->frente == fila->tras) {   //fila com um elemento
        fila->frente = -1;
        fila->tras = -1;
    }
    else {
        int n = sizeof(fila->elementos) / sizeof(int);
        fila->frente = (fila->frente + 1) % n;    //fila circular
    }
    return val;
}

int tamanho(struct FilaArray* fila) {
    if (fila == NULL)
        return 0;
    if (fila->frente == -1 && fila->tras == -1)
        return 0;
    if (fila->frente <= fila->tras)
        return fila->tras - fila->frente + 1;
    else //fila->frente > fila->tras
        return (sizeof(fila->elementos) - fila->frente) + (fila->tras + 1);    
}

int frente(struct FilaArray* fila) {
    int val = INT_MIN;
    if (fila == NULL)
        return val;
    if (vazia(fila)) {   
        return val;
    }
    //se chegamos aqui, existe elemento na fila
    return fila->elementos[fila->frente];
}