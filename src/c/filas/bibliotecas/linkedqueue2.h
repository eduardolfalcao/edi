#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedqueue {
    struct no* frente;
    struct no* tras;
    int qtdade;
};

struct linkedqueue* inicializar() {
    struct linkedqueue* fila = (struct linkedqueue*)malloc(sizeof(struct linkedqueue));
    fila->frente = NULL;
    fila->tras = NULL;
    fila->qtdade = 0;
    return fila;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));
    novoNo->val = valor;
    novoNo->prox = NULL;
    return novoNo;
}

bool vazia(struct linkedqueue* fila) {
    if (fila == NULL)
        return true;
    else if (fila->frente == NULL && fila->tras == NULL && fila->qtdade == 0)
        return true;
    else return false;
}

//se a fila estiver nula, instancie a fila
//por causa da possibilidade de instanciacao usamos struct linkedqueue**
void enfileirar(struct linkedqueue** fila, int val) {
    if ((*fila) == NULL) 
        (*fila) = inicializar();
    //alocar um novo nó para armazenar val
    struct no* novoNo = alocarNovoNo(val);
    if (vazia((*fila))) {                              //fila vazia               
        (*fila)->frente = novoNo;
        (*fila)->tras = novoNo;
    } 
    else {                                             //fila não vazia
        (*fila)->tras->prox = novoNo;
        (*fila)->tras = novoNo;
    }
    (*fila)->qtdade++;
}

//retorne a constante INT_MIN se a fila for nula ou vazia
//lembrem de desalocar o nó removido (free)
int desenfileirar(struct linkedqueue* fila) {
    if (vazia(fila)) {   
        return INT_MIN;
    }
    int val = fila->frente->val;
    //se chegamos aqui, existe elemento para desenfileirar
    if (fila->frente == fila->tras && fila->frente != NULL && fila->qtdade==1) {   
        //fila com um elemento
        free(fila->frente);
        fila->frente = NULL;
        fila->tras = NULL;
    }
    else {  //fila com mais de um elemento
        struct no* novoPrimeiroNo = fila->frente->prox;
        free(fila->frente);
        fila->frente = novoPrimeiroNo;
    }
    fila->qtdade--;
    return val;
}

//retorne a constante INT_MIN se a fila for nula ou vazia
int frente(struct linkedqueue* fila) {
    if (vazia(fila)) {   
        return INT_MIN;
    }
    //se chegamos aqui, existe elemento na fila
    return fila->frente->val;
}