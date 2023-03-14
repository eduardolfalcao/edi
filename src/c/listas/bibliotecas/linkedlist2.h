#include <stdlib.h>
#include <stdio.h>

struct no{
    int val;
    struct no *prox;
};

struct linkedlist {
    struct no* cabeca;
    int qtdade;
};

struct linkedlist* inicializar() {
    struct linkedlist* lista = (struct linkedlist*)malloc(sizeof(struct linkedlist));
    lista->cabeca = NULL;
    lista->qtdade = 0;
    return lista;
}

struct no* alocarNovoNo(int valor){
    struct no *novoNo;
    novoNo = (struct no *)malloc(sizeof(struct no));
    novoNo->val = valor;
    novoNo->prox = NULL;
    return novoNo;
}

void inserirElementoNoFim(struct linkedlist* lista, int valor){    
    //aloca espaço na memória e popula novoNo
    struct no *novoNo = alocarNovoNo(valor);

    if(lista->cabeca == NULL){
        //quando a lista é vazia, basta apontar o início para o novoNo
        lista->cabeca = novoNo;
    } else{
        //quando a lista não é vazia, precisamos encontrar o último nó
        //usamos a variável aux para percorrer a lista
        //fazemos isso para não perdermos a referência para o início da lista
        struct no *aux = lista->cabeca;

        //navega partindo da cabeça até chegar em no->prox == NULL
        while (aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novoNo;
    }
    lista->qtdade++;
}

void inserirElementoNoInicio(struct linkedlist* lista, int valor){
    //aloca espaço na memória e popula novoNo
    struct no *novoNo = alocarNovoNo(valor);

    if(lista->cabeca == NULL){
        //quando a lista é vazia, basta apontar o início para o novoNo
        lista->cabeca = novoNo;
    } else{
        //quando a lista não é vazia, precisamos apontar o prox de novoNo 
        //para o primeiro elemento, que é apontado pela cabeça
        //em seguida apontamos a cabeça da lista para o novoNo
        novoNo->prox = lista->cabeca;
        lista->cabeca = novoNo;
    }   //dá pra refatorar (diminuir linhas)

    lista->qtdade++;
}

void inserirElementoEmPosicao(struct linkedlist* lista, int valor, int posicao){
    //se a posicao==0, podemos reusar a função inserirElementoNoInicio
    if(posicao==0 || lista->cabeca == NULL){
        inserirElementoNoInicio(lista,valor);
        return;
    }

    //aloca espaço na memória e popula novoNo
    struct no *novoNo = alocarNovoNo(valor);
    //queremos usar o aux para encontrar o nó "antecessor a novoNo"
    struct no *aux = lista->cabeca;
    for(int i = 0; i < posicao-1 && aux->prox != NULL; i++){
            aux = aux->prox;
    }
    novoNo->prox = aux->prox;
    aux->prox = novoNo;
    lista->qtdade++;
}

int obterElementoEmPosicao(struct linkedlist* lista, int posicao){
    struct no *aux = lista->cabeca;
    for(int i = 0; i < posicao && aux->prox != NULL; i++){
            aux = aux->prox;
    }
    return aux->val;
}

void removerElementoEmPosicao(struct linkedlist* lista, int posicao){
    //guardo uma referência para a cabeça da lista
    struct no *aux = lista->cabeca;
    if(posicao==0 && lista->cabeca != NULL){
        lista->cabeca = lista->cabeca->prox;
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
    lista->qtdade--;
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