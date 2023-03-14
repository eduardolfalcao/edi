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
    struct doublylinkedlist* lista = (struct doublylinkedlist*)malloc(sizeof(struct doublylinkedlist));
    lista->cabeca = NULL;
    lista->cauda = NULL;
    lista->qtdade = 0;
    return lista;
}

struct no* alocarNovoNo(int valor){
    struct no *novoNo;
    novoNo = (struct no *)malloc(sizeof(struct no));
    novoNo->val = valor;
    novoNo->ant = NULL;
    novoNo->prox = NULL;
    return novoNo;
}

void inserirElementoNoInicio(struct doublylinkedlist* lista, int valor){
    //aloca espaço na memória e popula novoNo
    struct no *novoNo = alocarNovoNo(valor);   

    if(lista->cabeca == NULL){
        //quando a lista é vazia, basta apontar o cabeca e cauda para o novoNo
        lista->cauda = novoNo;
    } else{
        // LEMBRAR de atualizar o antigo nó cabeça, alterando seu ant 
        // de NULL para novoNo 
        lista->cabeca->ant = novoNo;

        //quando a lista não é vazia, precisamos apontar o prox de novoNo 
        //para o primeiro elemento, que é apontado pela cabeça
        //em seguida apontamos a cabeça da lista para o novoNo        
        novoNo->prox = lista->cabeca;
    }  
    //uma certeza: inserindo no início, a cabeça apontará para o novoNo
    lista->cabeca = novoNo;
    lista->qtdade++;
}

void inserirElementoNoFim(struct doublylinkedlist* lista, int valor){
    //aloca espaço na memória e popula novoNo
    struct no *novoNo = alocarNovoNo(valor);    

    if(lista->cabeca == NULL){
        //quando a lista é vazia, basta apontar o cabeca e cauda para o novoNo
        lista->cabeca = novoNo;        
    } else{
        //atualizamos o ponteiro novoNo->ant para o antigo último nó
        novoNo->ant = lista->cauda;
        //ponteiro prox do antigo último nó para o novoNo
        lista->cauda->prox = novoNo;
    }
    //uma certeza: inserindo no fim, a cauda apontará para o novoNo
    lista->cauda = novoNo;
    lista->qtdade++;
}

void inserirElementoEmPosicao(struct doublylinkedlist* lista, int valor, int posicao){
    //se a posicao==0, podemos reusar a função inserirElementoNoInicio
    if(posicao==0 || 
        (lista->cabeca == NULL && lista->cauda == NULL)){
        inserirElementoNoInicio(lista,valor);
        return;
    }

    //aloca espaço na memória e popula novoNo
    struct no* novoNo = alocarNovoNo(valor);
    
    //queremos usar o aux para encontrar o nó antecessor a novoNo
    struct no *aux = lista->cabeca;
    for(int i = 0; i < posicao-1 && aux->prox != NULL; i++){
            aux = aux->prox;
    }
    struct no * antecessor = aux;
    struct no * sucessor = aux->prox;
    novoNo->prox = sucessor;
    novoNo->ant = antecessor;
    
    if(sucessor != NULL){    
        sucessor->ant = novoNo;
    }
    else {  //novoNo é o último
        lista->cauda = novoNo;
    }
    
    antecessor->prox = novoNo;
    lista->qtdade++;
}

int obterElementoEmPosicao(struct doublylinkedlist* lista, int posicao){
    struct no *aux = lista->cabeca;
    for(int i = 0; i < posicao && aux->prox != NULL; i++){
            aux = aux->prox;
    }
    return aux->val;
}

void removerElementoEmPosicao(struct doublylinkedlist* lista, int posicao){
    //guardo uma referência para a cabeça da lista
    struct no *aux = lista->cabeca;
    if(posicao==0 && lista->qtdade > 0){
        if (lista->qtdade == 1) {
            lista->cauda = NULL;
            lista->cabeca = NULL;
        }
        else {
            lista->cabeca =  lista->cabeca->prox;
        }
        free(aux);
    }
    else {
        //queremos usar o aux para encontrar o nó antecessor do no a ser removido
        for (int i = 0; i < posicao - 1 && aux->prox != NULL; i++) {
            aux = aux->prox;
        }
        struct no* antecessor = aux;
        struct no* sucessor = aux->prox->prox;
        struct no* rem = aux->prox;
        antecessor->prox = sucessor;
        if (sucessor != NULL) {
            sucessor->ant = antecessor;
        }
        else {
            //removemos o último nó
            lista->cauda = antecessor;
        }
        free(rem);
    }
    if(lista->qtdade > 0)
        lista->qtdade--;
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