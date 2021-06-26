#include <stdlib.h>
#include <stdio.h>

struct no{
    struct no *ant;
    int val;
    struct no *prox;
};

struct no* alocarNovoNo(int valor){
    //TODO
}

void inserirElementoNoInicio(struct no **cabeca, int valor, int* tamanho){
    //TODO
}

void inserirElementoNoFim(struct no **cabeca, int valor, int* tamanho){
    //TODO
}

void inserirElementoEmPosicao(struct no **cabeca, int valor, int posicao, int* tamanho){
    //TODO
}

int obterElementoEmPosicao(struct no **cabeca, int posicao){
    //TODO
}

void removerElementoEmPosicao(struct no **cabeca, int posicao, int* tamanho){
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