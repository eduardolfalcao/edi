#include <stdio.h>
#include <stdlib.h>

//objetivo: encontrar índice onde val se encontra em v
int busca(int v[], int tamanho, int val) {
	for (int i = 0; i < tamanho; i++) {
		if (v[i] == val)
			return i;
	}
	return -1;
}