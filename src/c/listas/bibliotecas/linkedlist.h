#include <stdlib.h>
#include <stdio.h>

struct no{
    int val;
    struct no *prox;
};

void imprimirLista(struct no **cabeca){
    //usamos o aux para percorrer a lista
    if((*cabeca) != NULL){
        struct no *aux = (*cabeca);
        //navega partindo da cabeça até chegar NULL
        printf("[");
        do{
            printf("%d", aux->val);
            aux = aux->prox;
            if(aux != NULL){
                printf(", ");
            }
        } while (aux != NULL);
        printf("]");
    } else{
         printf("A lista está vazia!");
    }    
}

struct no* alocarNovoNo(int valor){
    struct no *novoNo;
    novoNo = (struct no *)malloc(sizeof(struct no));
    novoNo->val = valor;
    novoNo->prox = NULL;
    return novoNo;
}

void inserirElementoNoFim(struct no **cabeca, int valor, int* tamanho){
    //aloca espaço na memória e popula novoNo
    struct no *novoNo = alocarNovoNo(valor);

    if((*cabeca) == NULL){
        //quando a lista é vazia, basta apontar o início para o novoNo
        (*cabeca) = novoNo;
    } else{
        //quando a lista não é vazia, precisamos encontrar o último nó
        //usamos a variável aux para percorrer a lista
        //fazemos isso para não perdermos a referência para o início da lista
        struct no *aux = (*cabeca);

        //navega partindo da cabeça até chegar em no->prox == NULL
        while (aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novoNo;
    }
    (*tamanho)++;
}

void inserirElementoNoInicio(struct no **cabeca, int valor, int* tamanho){
    //aloca espaço na memória e popula novoNo
    struct no *novoNo = alocarNovoNo(valor);

    if((*cabeca) == NULL){
        //quando a lista é vazia, basta apontar o início para o novoNo
        (*cabeca) = novoNo;
    } else{
        //quando a lista não é vazia, precisamos apontar o prox de novoNo 
        //para o primeiro elemento, que é apontado pela cabeça
        //em seguida apontamos a cabeça da lista para o novoNo
        novoNo->prox = (*cabeca);
        (*cabeca) = novoNo;
    }   //dá pra refatorar (diminuir linhas)

    (*tamanho)++;
}

void inserirElementoEmPosicao(struct no **cabeca, int valor, int posicao, int* tamanho){
    //se a posicao==0, podemos reusar a função inserirElementoNoInicio
    if(posicao==0 || (*cabeca) == NULL){
        inserirElementoNoInicio(cabeca,valor,tamanho);
        return;
    }

    //aloca espaço na memória e popula novoNo
    struct no *novoNo = alocarNovoNo(valor);
    //queremos usar o aux para encontrar o nó "antecessor a novoNo"
    struct no *aux = (*cabeca);
    for(int i = 0; i < posicao-1 && aux->prox != NULL; i++){
            aux = aux->prox;
    }
    novoNo->prox = aux->prox;
    aux->prox = novoNo;
    (*tamanho)++;
}

int obterElementoEmPosicao(struct no **cabeca, int posicao){
    struct no *aux = (*cabeca);
    for(int i = 0; i < posicao && aux->prox != NULL; i++){
            aux = aux->prox;
    }
    return aux->val;
}

void removerElementoEmPosicao(struct no **cabeca, int posicao, int* tamanho){
    //guardo uma referência para a cabeça da lista
    struct no *aux = (*cabeca);
    if(posicao==0 && (*cabeca) != NULL){                
        (*cabeca) = (*cabeca)->prox;
        free(aux);
    }
    else {
        //procuramos o antecessor do nó a ser removido
        for (int i = 0; i < posicao - 1 && aux->prox != NULL; i++) {
            aux = aux->prox;
        }
        struct no* rem = aux->prox;
        if(rem!=NULL)
            aux->prox = rem->prox;  //rem é null
        free(rem);
    }    
    (*tamanho)--;
}