#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct arraystack {
    int* elementos;
    int tamanho;    //tam do array
    int qtdade;     //qtdade de elementos no array
};

struct arraystack* inicializar(int tamArray){
    //TODO
}

void duplicarCapacidade(struct arraystack* pilha){
    //TODO
}

//se a pilha estiver nula, instancie a pilha com tamanho 10
//por causa da possibilidade de instanciacao usamos struct arraystack**
//se a pilha encher, duplique a capacidade do array
void empilhar(struct arraystack** pilha, int valor){
    //TODO
}

//retornar true se a pilha for nula ou vazia
bool vazio(struct arraystack* pilha) {
    //TODO
}

//decrementar qtdade se a pilha não estiver nula ou vazia
void desempilhar(struct arraystack* pilha){
    //TODO
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int desempilharRetornando(struct arraystack* pilha){
    //TODO
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int topo(struct arraystack* pilha){
    //TODO
}

void imprimir(struct arraystack* pilha){
    printf("_\n");
    for(int i = pilha->qtdade - 1; i >= 0; i--){
        printf("%d\n",pilha->elementos[i]);
    }
    printf("_\n\n");
}