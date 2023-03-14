#include "bibliotecas/buscabinaria2.h"

//int vDesordenado[] = {10, 5, 1, 11, -12, 56, 0, 92, 44, 87, 3};
int vOrdenado[] = {-12, 0, 1, 3, 5, 10, 11, 44, 56, 87, 92};
int tamanho = 11;

int main() {

    /*printf("%d\n", busca(vOrdenado, tamanho, 11));  //6
    printf("%d\n", busca(vOrdenado, tamanho, 10));  //5
    printf("%d\n", busca(vOrdenado, tamanho, 3));   //3
    printf("%d\n", busca(vOrdenado, tamanho, 66));  //-1*/

    int ini = 0;
    int fim = tamanho - 1;

    printf("%d\n", buscaRec(vOrdenado, ini, fim, 11));
    printf("%d\n", buscaRec(vOrdenado, ini, fim, 10));
    printf("%d\n", buscaRec(vOrdenado, ini, fim, 3));
    printf("%d\n", buscaRec(vOrdenado, ini, fim, 66));

   return 0;
}