#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct no {
    int val;
    struct no* prox;
};

struct FilaLigada {
    struct no* frente;
    struct no* tras;
    int tamanho;
};

bool vazia(struct FilaLigada* fila) {
    if (fila == NULL)
        return true;
    else if (fila->frente == NULL && fila->tras == NULL && fila->tamanho==0)
        return true;
    else return false;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo;
    novoNo = (struct no*)malloc(sizeof(struct no));
    novoNo->val = valor;
    novoNo->prox = NULL;
    return novoNo;
}

void enfileirar(struct FilaLigada** fila, int val) {
    if (fila == NULL) {
        (*fila) = (struct FilaLigada*)malloc(sizeof(struct FilaLigada));
    }

    struct no* novoNo = alocarNovoNo(val);
    if (vazia(*fila)) {                         //fila vazia
        (*fila)->frente = novoNo;
        (*fila)->tras = novoNo;
    }   
    else {                                     //fila não-vazia
        (*fila)->tras->prox = novoNo;
        (*fila)->tras = novoNo;       
    }
    (*fila)->tamanho++;
}

int desenfileirar(struct FilaLigada** fila) {
    int val = INT_MIN;
    if (vazia(*fila)) {   
        return val;
    }
    //se chegamos aqui, existe elemento para desempilhar
    val = (*fila)->frente->val;
    if ((*fila)->frente == (*fila)->tras) {   //fila com um elemento
        free((*fila)->frente);                //como frente e tras sao iguais, basta desalocar um    
        (*fila)->frente = NULL;
        (*fila)->tras = NULL;
    }
    else {
        struct no* novoFrente = (*fila)->frente->prox;
        free((*fila)->frente);
        (*fila)->frente = novoFrente;        
    }
    (*fila)->tamanho--;
    return val;
}

int frente(struct FilaLigada* fila) {
    int val = INT_MIN;
    if (vazia(fila))
        return val;
    //se chegamos aqui, existe elemento na fila
    return fila->frente->val;
}