#include <stdlib.h>
#include <stdio.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedlist {
    struct no* cabeca;
    int qtdade;
};

struct linkedlist* inicializar() {
    //TODO
}

struct no* alocarNovoNo(int valor) {
    //TODO
}

void inserirElementoNoFim(struct linkedlist* lista, int valor) {
    //TODO
}

void inserirElementoNoInicio(struct linkedlist* lista, int valor) {
    //TODO
}

void inserirElementoEmPosicao(struct linkedlist* lista, int valor, int posicao) {
    //TODO
}

int obterElementoEmPosicao(struct linkedlist* lista, int posicao) {
    //TODO
}

void removerElementoEmPosicao(struct linkedlist* lista, int posicao) {
    //TODO
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