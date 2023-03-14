#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct no{
    int val;
    struct no *prox;
};

void exibirPilha(struct no **pilha){
    //usamos o aux para percorrer a lista
    if((*pilha) != NULL){
        struct no *aux = (*pilha);
        //navega partindo do topo até chegar NULL
        printf("_\n");
        do{
            printf("%d\n", aux->val);
            aux = aux->prox;
        } while (aux != NULL);
        printf("_");
    } else{
         printf("A pilha está vazia!");
    }    
}

struct no* alocarNovoNo(int valor){
    struct no *novoNo;
    novoNo = (struct no *)malloc(sizeof(struct no));
    novoNo->val = valor;
    novoNo->prox = NULL;
    return novoNo;
}

void empilhar(struct no **pilha, int valor, int* tamanho){
    //aloca espaço na memória e popula novoNo
    struct no *novoNo = alocarNovoNo(valor);

    if((*pilha) == NULL){
        //quando a pilha é vazia, basta apontar o início para o novoNo
        (*pilha) = novoNo;
    } else{
        //quando a pilha não é vazia, precisamos apontar o prox de novoNo 
        //para o primeiro elemento, que é apontado pelo topo
        //em seguida apontamos o topo da pilha para o novoNo
        novoNo->prox = (*pilha);
        (*pilha) = novoNo;
    }   //dá pra refatorar (diminuir linhas)

    (*tamanho)++;
}

int topo(struct no *pilha){
    if(pilha != NULL)
        return pilha->val;
    else 
        return INT_MIN;
}

bool vazio(struct no* pilha) {
    if (pilha == NULL)
        return true;
    else
        return false;
}

void desempilhar(struct no **pilha, int* tamanho){
    //guardo uma referência para o topo da pilha
    struct no *aux = (*pilha);
    if((*pilha) != NULL){                
        (*pilha) = (*pilha)->prox;
        free(aux);
        (*tamanho)--;
    }    
}

int desempilharRetornando(struct no** pilha, int* tamanho) {
    //guardo uma referência para o topo da pilha
    struct no* aux = (*pilha);
    if ((*pilha) != NULL) {
        (*pilha) = (*pilha)->prox;
        int val = aux->val;
        free(aux);
        (*tamanho)--;
        return val;
    } else {
        return INT_MIN;
    }
}