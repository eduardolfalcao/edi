#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct arrayqueue {
    int frente;
    int tras;
    int* elementos;
    int tamanho;    //tam do array
    int qtdade;     //qtdade de elementos no array    
};

struct arrayqueue* inicializar(int tamArray) {
    struct arrayqueue* fila = (struct arrayqueue*)malloc(sizeof(struct arrayqueue));
    fila->elementos = (int*)calloc(tamArray, sizeof(int));
    fila->tamanho = tamArray;
    fila->qtdade = 0;
    fila->frente = -1;
    fila->tras = -1;

    return fila;
}

//se a fila estiver nula, instancie a fila com tamanho 10
//por causa da possibilidade de instanciacao usamos struct arrayqueue**
//se a fila encher, simplesmente não enfileire
void enfileirar(struct arrayqueue** fila, int val) {
    struct arrayqueue* ref;
    if (*fila == NULL) {
        *fila = inicializar(10);
    }

    ref = *fila;
    if ((ref->tras + 1) % ref->tamanho != ref->frente) {
        ref->qtdade++;
        ref->tras = (ref->tras + 1) % ref->tamanho;
        ref->elementos[ref->tras] = val;
        if (ref->frente == -1) {
            ref->frente = 0;
        }
    }



}

//retorne a constante INT_MIN se a fila for nula ou vazia
int desenfileirar(struct arrayqueue* fila) {
    if (fila == NULL || (fila->tras == -1 && fila->frente == -1)) {
        return INT_MIN;
    }
    fila->frente = (fila->frente + 1) % fila->tamanho;
    fila->qtdade--;

    if (fila->qtdade == 1) {
        fila->frente = -1;
        fila->tras = -1;
    }

    return fila->elementos[fila->frente - 1];
}

//retorne a constante INT_MIN se a fila for nula ou vazia
int frente(struct arrayqueue* fila) {
    if (fila == NULL || (fila->tras == -1 && fila->frente == -1)) {
        return INT_MIN;
    }
    return fila->elementos[fila->frente];
}