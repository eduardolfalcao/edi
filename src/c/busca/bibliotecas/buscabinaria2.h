#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool buscaIt(int v[], int n, int val) {
	int ini = 0;
	int fim = n - 1;
	while (ini <= fim) {
		int meio = (ini + fim) / 2;
		if (v[meio] == val) 				//caso1: val está no meio{}
			return true;
		else if (val < v[meio])			//caso2: val está à esquerda do meio
			fim = meio - 1;
		else                            //caso3: val está à direita do meio
			ini = meio + 1;
	}

	return false;

	/*//abrir um espaço, deslocando elementos para a direita
	for (int i = meio; i < (n-1); i++) {
		v[i + 1] = v[i];
	}
	v[meio] = val;

	return -1;*/
}

int buscaRec(int v[], int ini, int fim, int val) {
	if (ini <= fim){
		int meio = (ini + fim) / 2;
		if (v[meio] == val)				//caso1: val está no meio
			return meio;
		else if (val < v[meio])			//caso2: val está à esquerda do meio
			return buscaRec(v, ini, meio - 1, val);
		else                            //caso3: val está à direita do meio
			return buscaRec(v, meio+1, fim, val);
	}
	return -1;
}