#include<stdio.h>
#include<stdlib.h>

int* lista; 
//qtdade de elementos no array
int tamanho = 0;

void inicializar(int capacidade){
    lista = calloc(capacidade, sizeof(int));
}

void duplicarCapacidade(){
    /*int novaLista[2*sizeof(lista)];
    for(int i = 0; i < sizeof(lista);i++){
        novaLista[i] = lista[i];
    }
    free(lista);
    lista = novaLista; */

    lista = (int*)realloc(lista,2*sizeof(lista)*sizeof(int));
}

void adicionarElementoNoFim(int elemento){
    if(sizeof(lista) == tamanho){
        duplicarCapacidade();
    }
    lista[tamanho] = elemento;
    tamanho++;
}

int obterElemento(int pos){
    if(pos>=0 && pos<tamanho){
        return lista[pos];
    } 
}

void adicionarElementoEmPosicao(int elemento, int pos){
    if(pos>=0 && pos<=tamanho){         //o índice é válido
        if(sizeof(lista) == tamanho){   //se capacidade do array for excedida
            duplicarCapacidade();       //duplique a capacidade
        }
        //[2,4,6,8,10]
        //insercao de 0 na posicao 0
        //[2,2,4,6,8,10,X,X,X,X]
        //i=0
        for(int i = tamanho; i >= pos ; i--){
            lista[i+1] = lista[i];
        }
        lista[pos] = elemento;
        tamanho++;
    }
}

void atualizarElemento(int valor, int posicao){
    if(posicao >= 0 && posicao < tamanho){    
        lista[posicao] = valor;
    }
}

int getTamanho(){
    return tamanho;
}

void removerElementoNoFim(){
    tamanho--;
}

void removerElementoEmPosicao(int posicao){
    //essa posição é válida?
    if(posicao >= 0 && posicao < tamanho){
        //tamanho = 5
        //[4,6,8,10,X,X,X,X,X,X]
        //          posicao = 4
        while(posicao < tamanho-1){
            lista[posicao] = lista[posicao+1];
            posicao++; 
        }
        tamanho--;
    }
}