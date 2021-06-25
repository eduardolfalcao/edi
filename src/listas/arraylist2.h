#include <stdio.h>
#include <stdlib.h>

struct arraylist {
    int* vetor;
    int qtdade;
    int capacidade;
};

struct arraylist* inicializar(int capacidade) {
    struct arraylist* lista = (struct arraylist*)malloc(sizeof(struct arraylist));
    lista->vetor = (int*)calloc(capacidade, sizeof(int));
    lista->qtdade = 0;
    lista->capacidade = capacidade;
    return lista;
}

int obterElementoEmPosicao(struct arraylist* lista, int posicao) {
    //TODO
}

void duplicarCapacidade(struct arraylist* lista) {
    //TODO
}

void inserirElementoNoFim(struct arraylist* lista, int valor) {
    //TODO
}

void inserirElementoEmPosicao(struct arraylist* lista, int valor, int posicao) {
    //TODO
}

void atualizarElemento(struct arraylist* lista, int valor, int posicao) {
    //TODO
}

void removerElementoNoFim(struct arraylist* lista) {
    //TODO
}

void removerElementoEmPosicao(struct arraylist* lista, int posicao) {
    //TODO
}

void exibirLista(struct arraylist* lista) {
    printf("[");
    for (int i = 0; i < lista->qtdade; i++) {
        printf("%d", lista->vetor[i]);
        if (i < lista->qtdade - 1) {
            printf(", ");
        }
    }
    printf("]");
}