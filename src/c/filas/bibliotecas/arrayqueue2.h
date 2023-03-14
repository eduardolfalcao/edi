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
    fila->elementos = (int*)malloc(tamArray * sizeof(int));
    fila->tamanho = tamArray;
    fila->frente = -1;
    fila->tras = -1;
    fila->qtdade = 0;    
    return fila;
}

//se a fila estiver nula, instancie a fila com tamanho 10
//por causa da possibilidade de instanciacao usamos struct arrayqueue**
//se a fila encher, simplesmente não enfileire
void enfileirar(struct arrayqueue** fila, int val) {
    if ((*fila) == NULL)
        (*fila) = inicializar(10);
    if ((*fila)->qtdade == (*fila)->tamanho)   //fila cheia
        return;
    else if ((*fila)->qtdade == 0) {             //fila vazia
        (*fila)->frente = 0;
        (*fila)->tras = 0;
    } 
    else {
        (*fila)->tras = ((*fila)->tras + 1) % (*fila)->tamanho;   //fila circular
    }
    (*fila)->elementos[(*fila)->tras] = val;
    (*fila)->qtdade++;
}

//retorne a constante INT_MIN se a fila for nula ou vazia
int desenfileirar(struct arrayqueue* fila) {
    int val = INT_MIN;
    if (fila == NULL)
        return val;
    if (fila->qtdade == 0) {   
        return val;
    }
    //se chegamos aqui, existe elemento para desempilhar
    val = fila->elementos[fila->frente];
    if (fila->frente == fila->tras) {   //fila com um elemento
        fila->frente = -1;
        fila->tras = -1;
    }
    else {
        fila->frente = (fila->frente + 1) % fila->tamanho;    //fila circular
    }
    fila->qtdade--;
    return val;
}

//retorne a constante INT_MIN se a fila for nula ou vazia
int frente(struct arrayqueue* fila) {
    int val = INT_MIN;
    if (fila == NULL)
        return val;
    if (fila->qtdade == 0) {   
        return val;
    }
    //se chegamos aqui, existe elemento na fila
    return fila->elementos[fila->frente];
}