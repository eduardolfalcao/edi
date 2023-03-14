#include <stdio.h>
#include <stdlib.h>

//retorna indice
int buscaIt(int v[], int n, int val) {
    int ini = 0;
    int fim = n - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int vmeio = v[meio];
        if (val == vmeio)
            return meio;
        else if (val < vmeio)   //busca prossegue pelo sub-array esquerdo
            fim = meio - 1;
        else                      //busca prossegue pelo sub-array esquerdo
            ini = meio + 1;
    }
    return -1;
}

//retorna indice
int buscaRec(int v[], int ini, int fim, int val) {
    if (ini <= fim) {
        int meio = (ini + fim) / 2;
        if (val == v[meio])
            return meio;
        else if (val < v[meio])   //busca prossegue pelo sub-array esquerdo
            fim = meio - 1;
        else                      //busca prossegue pelo sub-array esquerdo
            ini = meio + 1;

        return buscaRec(v, ini, fim, val);
    }
    else
        return -1;

}
