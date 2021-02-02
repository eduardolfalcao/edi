#include "bibliotecas/linkedlist.h"

int tamanho;
struct no * lista;

int main() {

    inserirElementoNoFim(&lista,1,&tamanho);
    inserirElementoNoFim(&lista,2,&tamanho);
    inserirElementoNoFim(&lista,3,&tamanho);
    inserirElementoNoInicio(&lista,0,&tamanho);
    inserirElementoNoInicio(&lista,-1,&tamanho);
    inserirElementoEmPosicao(&lista,-2,0,&tamanho);
    inserirElementoEmPosicao(&lista,123,1,&tamanho);
    inserirElementoEmPosicao(&lista,456,7,&tamanho);
    
    imprimirLista(&lista);

    printf("\nlista.get(0):%d\n",obterElementoEmPosicao(&lista,0));
    printf("lista.get(2):%d\n",obterElementoEmPosicao(&lista,2));
    printf("lista.get(7):%d\n",obterElementoEmPosicao(&lista,7));
    printf("lista.get(20):%d\n",obterElementoEmPosicao(&lista,20));

    imprimirLista(&lista);
    printf("removendo na posicao 0\n");
    removerElementoEmPosicao(&lista,0,&tamanho);
    imprimirLista(&lista);
    printf("removendo na posicao 3\n");
    removerElementoEmPosicao(&lista,3,&tamanho);
    imprimirLista(&lista);
    printf("removendo na posicao 5\n");
    removerElementoEmPosicao(&lista,5,&tamanho);
    imprimirLista(&lista);
    return 0;
}