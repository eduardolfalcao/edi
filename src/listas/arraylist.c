#include <stdio.h>
#include <stdlib.h>

int* lista; 
int tamanho = 0;

void inicializar(int capacidade){
    lista = calloc(capacidade, sizeof(int));
}

int obterElemento(int posicao){
    if(posicao >= 0 && posicao < tamanho){
        return lista[posicao];
    }
}

/*void duplicarCapacidade(){
    int novaLista[2*sizeof(lista)];
    for(int i = 0; i<sizeof(lista); i++){
        novaLista[i] = lista[i];
    }
    free(lista);
    lista = novaLista;
}*/

void duplicarCapacidade(){
    lista = (int*)realloc(lista, 2*sizeof(lista)*sizeof(int));
}

void inserirElementoNoFim(int valor){
    if(tamanho == sizeof(lista)){
        duplicarCapacidade();
    }
    lista[tamanho] = valor;
    tamanho++;
}

void inserirElementoEmPosicao(int valor, int posicao){
    if(posicao >= 0 && posicao <= tamanho){    
        if(tamanho == sizeof(lista)){
            duplicarCapacidade();
        }

        for(int i = tamanho; i > posicao; i--){
            lista[i] = lista[i-1];
        }
        lista[posicao] = valor;
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
    if(posicao >= 0 && posicao < tamanho){    
        while(posicao < tamanho-1){
            lista[posicao] = lista[posicao+1];
            posicao++;
        }
        tamanho--;
    }
}

void exibirLista(){
    printf("[");
    for(int i = 0; i < tamanho; i++){
        printf("%d",lista[i]);
        if(i < tamanho-1){
            printf(", ");
        }
    }
    printf("]");
}

/*int main() {

    inicializar(10);

    inserirElementoNoFim(3);
    inserirElementoNoFim(5);
    inserirElementoNoFim(6);
    inserirElementoNoFim(2);
    inserirElementoNoFim(-2);

    printf("%d",obterElemento(2));

   return 0;
}*/

/*int main() {

    inicializar(5);

    inserirElementoNoFim(3);
    inserirElementoNoFim(5);
    inserirElementoNoFim(6);
    inserirElementoNoFim(2);
    inserirElementoNoFim(-2);
    inserirElementoNoFim(9);

    printf("%d",obterElemento(5));

   return 0;
}*/

/*int main() {
    inicializar(5);
    inserirElementoNoFim(3);
    inserirElementoNoFim(5);
    inserirElementoNoFim(6);
    inserirElementoNoFim(2);
    inserirElementoNoFim(-2);
    inserirElementoEmPosicao(4,0);
    exibirLista();
   return 0;
}*/

int main() {
    inicializar(5);
    inserirElementoNoFim(3);
    inserirElementoNoFim(5);
    inserirElementoNoFim(6);
    inserirElementoNoFim(2);
    inserirElementoNoFim(-2);
    removerElementoEmPosicao(0);
    exibirLista();
   return 0;
}