#include <stdlib.h>
#include <stdio.h>

struct no{
    struct no *ant;
    int val;
    struct no *prox;
};

struct doublylinkedlist {
    struct no* cabeca;
    struct no* cauda;
    int qtdade;
};

struct doublylinkedlist* inicializar() {
   //TODO
}

struct no* alocarNovoNo(int valor){
    //TODO
}

void inserirElementoNoInicio(struct doublylinkedlist* lista, int valor){
    //TODO
}

void inserirElementoNoFim(struct doublylinkedlist* lista, int valor){
    //TODO
}

void inserirElementoEmPosicao(struct doublylinkedlist* lista, int valor, int posicao){
    //TODO
}

int obterElementoEmPosicao(struct doublylinkedlist* lista, int posicao){
    //TODO
}

void removerElementoEmPosicao(struct doublylinkedlist* lista, int posicao){
    //TODO
}

void imprimirLista(struct no** cabeca) {
    //usamos o aux para percorrer a lista
    if ((*cabeca) != NULL) {
        struct no* aux = (*cabeca);
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