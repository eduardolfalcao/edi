#ifndef _LINKEDQUEUE_H_
#define _LINKEDQUEUE_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
//#include "LinkedQueue.h"

struct no {
    int val;
    struct no* prox;
};

struct linkedqueue {
    struct no* frente;
    struct no* tras;
    int qtdade;
};

// Declaração das funções

struct no* alocarNovoNo(int valor);

struct linkedqueue* inicializar();

bool vazia(struct linkedqueue* fila);

void enfileirar(struct linkedqueue** fila, int valor);

int desenfileirar(struct linkedqueue* fila);

int frente(struct linkedqueue* fila);

// Fim da declaração das funções

// Implementação das funções

struct no* alocarNovoNo(int valor) {
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));

    novoNo->val = valor;
    novoNo->prox = NULL;

    return novoNo;
}

struct linkedqueue* inicializar() {
    struct linkedqueue* fila = (struct linkedqueue*)malloc(sizeof(struct linkedqueue));

    fila->frente = NULL;
    fila->tras = NULL;
    fila->qtdade = 0;

    return fila;
}

bool vazia(struct linkedqueue* fila) {
    if (fila == NULL || fila->qtdade == 0) return true;
    else return false;
}

void enfileirar(struct linkedqueue** fila, int valor) {
    struct no* novoNo = alocarNovoNo(valor);

    if ((*fila) == NULL) (*fila) = inicializar();
    if ((*fila)->qtdade == 0) {
        // fila vazia: frente e trás incrementam uma posição
        (*fila)->tras = novoNo;
        (*fila)->frente = novoNo;
    }
    else {
        // fila não-vazia: somente trás incrementa uma posição e 'prox' do antigo 'tras' aponta para o novo 'tras'
        (*fila)->tras->prox = novoNo;
        (*fila)->tras = novoNo;
    }
    (*fila)->qtdade++;
}

int desenfileirar(struct linkedqueue* fila) {
    if (fila != NULL && fila->qtdade > 0) {
        struct no* aux = fila->frente;
        int aux_val = aux->val;

        if (fila->qtdade == 1) {
            fila->frente = fila->tras = NULL;
        }
        else {
            fila->frente = aux->prox;
        }

        fila->qtdade--;
        free(aux);

        return aux_val;

    }
    else return INT_MIN;
}

int frente(struct linkedqueue* fila) {
    if (fila != NULL && fila->qtdade > 0) return fila->frente->val;
    else return INT_MIN;
}

// Fim da implementação das funções

#endif // _LINKEDQUEUE_H_