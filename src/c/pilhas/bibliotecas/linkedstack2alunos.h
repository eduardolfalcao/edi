#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedstack {
    struct no* topo;
    int qtdade;
};

struct linkedstack* inicializar() {
    struct linkedstack* stack = (struct linkedstack*)malloc(sizeof(struct linkedstack));
    stack->topo = NULL;
    stack->qtdade = 0;

    return stack;

}

struct no* alocarNovoNo(int valor) {
    struct no* no = (struct no*)malloc(sizeof(struct no));
    no->val = valor;

    return no;
}

//retornar true se a pilha for nula ou vazia
bool vazia(struct linkedstack* pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        return true;
    }
    return false;
}

//se a pilha estiver nula, instancie a pilha
//por causa da possibilidade de instanciacao usamos struct linkedstack**
void empilhar(struct linkedstack** pilha, int valor) {
    if (vazia(*pilha)) {
        *pilha = inicializar();
        (*pilha)->topo = alocarNovoNo(valor);
        (*pilha)->qtdade++;
    }
    else {
        struct no* noAux = (*pilha)->topo;

        (*pilha)->topo = alocarNovoNo(valor);
        (*pilha)->topo->prox = noAux;
        (*pilha)->qtdade++;


    }
}

//decrementar qtdade se a pilha não estiver nula ou vazia
void desempilhar(struct linkedstack* pilha) {
    if (!vazia(pilha)) {

        if (pilha->qtdade < 1) {
            pilha->topo->val = INT_MIN;
            pilha->topo = NULL;
            pilha->qtdade = 0;
        }
        else {
            struct no* noAnteriorAoTopo = pilha->topo->prox;
            //pilha->topo = NULL;
            pilha->topo = noAnteriorAoTopo;
            pilha->qtdade--;

        }




    }
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int desempilharRetornando(struct linkedstack* pilha) {
    int int_min = INT_MIN;
    if (vazia(pilha)) {
        return int_min;
    }
    else {
        if (pilha->qtdade == 1) {
            int valorRetirado = pilha->topo->val;

            pilha->topo == NULL;
            pilha->topo->val = INT_MIN;
            pilha->qtdade = 0;
            return valorRetirado;

        }
        else {
            struct no* noAnteriorAoTopo = pilha->topo->prox;
            struct no* elementoRetirado = pilha->topo;
            pilha->topo = NULL;
            pilha->topo = noAnteriorAoTopo;
            pilha->topo->prox = NULL;
            pilha->qtdade--;
            return elementoRetirado->val;


        }
    }

}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int topo(struct linkedstack* pilha) {

    int int_min = INT_MIN;

    if (vazia(pilha)) {
        return int_min;
    }
    return (*pilha).topo->val;
}

void exibirPilha(struct linkedstack* pilha) {
    //usamos o aux para percorrer a lista
    if (!vazia(pilha)) {
        struct no* aux = pilha->topo;
        //navega partindo do topo até chegar NULL
        printf("_\n");
        do {
            printf("%d\n", aux->val);
            aux = aux->prox;
        } while (aux != NULL);
        printf("_");
    }
    else {
        printf("A pilha está vazia!");
    }
}