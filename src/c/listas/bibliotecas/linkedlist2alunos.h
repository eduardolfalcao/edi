#pragma once
#include <stdio.h>
#include <stdlib.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedlist {
    struct no* cabeca;
    int qtdade;
};

struct linkedlist* inicializar() {
    struct linkedlist* lista;
    lista = (struct linkedlist*)malloc(sizeof(struct linkedlist));
    lista->qtdade = 0;
    return lista;
}

struct no* alocarNovoNo(int valor) {
    struct no* cabeca;
    cabeca = (struct no*)malloc(sizeof(struct no*));
    if (cabeca == NULL) {
        return NULL;
    }
    cabeca->val = valor;
    cabeca->prox = NULL;
    return cabeca;
}

void inserirElementoNoFim(struct linkedlist* lista, int valor) {
    if (lista->qtdade != 0) {
        struct no* aux = lista->cabeca;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = alocarNovoNo(valor);
        (lista->qtdade)++;
    }
    else if (lista->qtdade < 0) {
        printf("erro tamanho negativo");
    }
    else {
        (lista->qtdade)++;
        lista->cabeca = alocarNovoNo(valor);
    }
}

void inserirElementoNoInicio(struct linkedlist* lista, int valor) {
    if ((lista->qtdade) != 0) {
        struct no* aux;
        aux = (struct no*)malloc(sizeof(struct no));
        aux->val = valor;
        aux->prox = (lista->cabeca);
        (lista->cabeca) = aux;
        (lista->qtdade)++;
    }
    else {
        (lista->cabeca) = alocarNovoNo(valor);
        (lista->qtdade)++;
    }
}

void inserirElementoEmPosicao(struct linkedlist* lista, int valor, int posicao) {
    if (posicao > 0 && posicao < (lista->qtdade) && (lista->qtdade) > 0) {
        struct no* aux = lista->cabeca;
        struct no* tmp = (struct no*)malloc(sizeof(struct no));
        tmp->val = valor;
        tmp->prox = NULL;
        for (int i = 0; i < posicao - 1; i++) {
            if (aux->prox != NULL) {
                aux = aux->prox;
            }
        }
        tmp->prox = aux->prox;
        aux->prox = tmp;

        (lista->qtdade)++;
    }
    else if (posicao == lista->qtdade) {
        inserirElementoNoFim(lista, valor);
    }
    else if (posicao == 0) {
        inserirElementoNoInicio(lista, valor);
    }
}

int obterElementoEmPosicao(struct linkedlist* lista, int posicao) {
    if (posicao >= 0 && lista->cabeca != NULL) {
        struct no* aux = (lista->cabeca);
        for (int i = 0; i < posicao; i++) {
            if (aux->prox != NULL) {
                aux = aux->prox;
            }
        }
        return aux->val;
    }
}

void removerElementoEmPosicao(struct linkedlist* lista, int posicao) {
    if (posicao >= 0 && posicao < (lista->qtdade) && (lista->qtdade) > 0) {
        if (posicao == 0) {
            struct no* aux = lista->cabeca;
            (lista->cabeca) = (lista->cabeca)->prox;
            free(aux);
            (lista->qtdade)--;
        }
        else {
            struct no* aux = lista->cabeca;
            struct no* tmp;
            for (int i = 0; i < posicao; i++) {
                tmp = aux;
                aux = aux->prox;
                if (aux == NULL) {
                    return;
                }
            }
            tmp->prox = aux->prox;
            free(aux);
            (lista->qtdade)--;
        }
    }
}

void imprimirLista(struct linkedlist* lista) {
    //usamos o aux para percorrer a lista
    if (lista->cabeca != NULL) {
        struct no* aux = lista->cabeca;
        //navega partindo da cabeça até chegar NULL
        printf("[");
        do {
            printf("%d", aux->val);
            aux = aux->prox;
            if (aux != NULL) {
                printf(", ");
            }
        } while (aux != NULL);
        printf("]");
    }
    else {
        printf("A lista está vazia!");
    }
}