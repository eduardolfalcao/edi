#include <stdlib.h>
#include <stdio.h>

struct no {
    struct no* ant;
    int val;
    struct no* prox;
};

struct doublylinkedlist {
    struct no* cabeca;
    struct no* cauda;
    int qtdade;
};

struct doublylinkedlist* inicializar() {
    struct doublylinkedlist* lista = (struct doublylinkedlist*)malloc(sizeof(struct doublylinkedlist));
    lista->cabeca = NULL;
    lista->cauda = NULL;
    lista->qtdade = 0;

    return lista;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));
    novoNo->prox = NULL;
    novoNo->ant = NULL;
    novoNo->val = valor;

    return novoNo;
}

void inserirElementoNoInicio(struct doublylinkedlist* lista, int valor) {
    struct no* novoNo = alocarNovoNo(valor);
    if (lista->cabeca != NULL) {
        novoNo->prox = lista->cabeca;
        lista->cabeca->ant = novoNo;
        lista->cabeca = novoNo;
    }
    else {
        lista->cabeca = novoNo;
        lista->cauda = novoNo;
    }
    lista->qtdade++;
}

void inserirElementoNoFim(struct doublylinkedlist* lista, int valor) {
    struct no* novoNo = alocarNovoNo(valor);
    if (lista->qtdade != 0) {
        novoNo->ant = lista->cauda;
        lista->cauda->prox = novoNo;
        lista->cauda = novoNo;
    }
    else {
        lista->cauda = novoNo;
        lista->cabeca = novoNo;
    }
    lista->qtdade++;
}

void inserirElementoEmPosicao(struct doublylinkedlist* lista, int valor, int posicao) {
    if (posicao >= 0 && posicao <= lista->qtdade) {
        if (posicao == 0) {
            inserirElementoNoInicio(lista, valor);
        }
        else {
            if (lista->cabeca != NULL) {
                struct no* aux = lista->cabeca;
                struct no* novoNo = alocarNovoNo(valor);
                int count = 0;
                while (count < posicao && aux->prox != NULL) {
                    aux = aux->prox;
                    count++;
                }

                if (aux == lista->cauda) {
                    inserirElementoNoFim(lista, valor);
                }
                else {
                    aux->ant->prox = novoNo;
                    novoNo->prox = aux;
                    novoNo->ant = aux->ant;
                    aux->ant = novoNo;
                    lista->qtdade++;
                }
            }
        }
    }
}

int obterElementoEmPosicao(struct doublylinkedlist* lista, int posicao) {
    if (posicao >= 0 && posicao < lista->qtdade) {
        struct no* aux = lista->cabeca;
        int count = 0;
        while (count < posicao && aux->prox != NULL) {
            aux = aux->prox;
            count++;
        }
        return aux->val;
    }
    else {
        printf("\nPosicao invalida\n");
        return -1;
    }
}

void removerElementoEmPosicao(struct doublylinkedlist* lista, int posicao) {
    struct no* temp;
    struct no* aux = lista->cabeca;
    if (posicao >= 0 && lista->qtdade != 0) {
        if (lista->cabeca != NULL) {
            int count = 0;
            while (count < posicao && aux->prox != NULL) {
                aux = aux->prox;
                count++;
            }

            if (aux == lista->cabeca) {
                lista->cabeca = lista->cabeca->prox;
            }
            else {
                aux->ant->prox = aux->prox;
            }

            if (aux == lista->cauda) {
                lista->cauda = aux->ant;
            }
            else {
                aux->prox->ant = aux->ant;
            }
            free(aux);
            lista->qtdade--;
        }

    }
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