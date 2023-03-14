#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct no{
    int val;
    struct no *prox;
};

struct linkedstack {
    struct no* topo;
    int qtdade;
};

struct linkedstack* inicializar() {
    struct linkedstack* pilha = (struct linkedstack*)malloc(sizeof(struct linkedstack));
    pilha->topo = NULL;
    pilha->qtdade = 0;
    return pilha;
}

struct no* alocarNovoNo(int valor){
    struct no *novoNo = (struct no *)malloc(sizeof(struct no));
    novoNo->val = valor;
    novoNo->prox = NULL;
    return novoNo;
}

bool vazia(struct linkedstack* pilha) {
    if (pilha == NULL)
        return true;
    else if (pilha->topo == NULL && pilha->qtdade == 0)
        return true;
    else return false;
}

//se a pilha estiver nula, instancie a pilha
//por causa da possibilidade de instanciacao usamos struct linkedstack**
void empilhar(struct linkedstack** pilha, int valor){
    if ((*pilha) == NULL)
        (*pilha) = inicializar();
    
    //aloca espaço na memória e popula novoNo
    struct no* novoNo = alocarNovoNo(valor);
    if (vazia((*pilha))) {
        //quando a pilha é vazia, basta apontar o início para o novoNo
        (*pilha)->topo = novoNo;
    } else{
        //quando a pilha não é vazia, precisamos apontar o prox de novoNo 
        //para o primeiro elemento, que é apontado pelo topo
        //em seguida apontamos o topo da pilha para o novoNo
        novoNo->prox = (*pilha)->topo;
        (*pilha)->topo = novoNo;
    }   //dá pra refatorar (diminuir linhas)

    (*pilha)->qtdade++;
}

void desempilhar(struct linkedstack* pilha) {
    if (!vazia(pilha)) {
        //guardo uma referência para o topo da pilha
        //para poder desalocar o espaco da memoria
        struct no* aux = pilha->topo;
        pilha->topo = pilha->topo->prox;
        free(aux);
        pilha->qtdade--;
    }
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int desempilharRetornando(struct linkedstack* pilha) {
    if (!vazia(pilha)) {
        int val = pilha->topo->val;
        desempilhar(pilha);
        return val;
    }
    else {
        return INT_MIN;
    }
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int topo(struct linkedstack* pilha){
    if(!vazia(pilha))
        return pilha->topo->val;
    else 
        return INT_MIN;
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