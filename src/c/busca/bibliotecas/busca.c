#include <stdio.h>
#include <math.h>

int buscaLinear(int* vetor, int tam, int valor) {
	for (int i = 0; i < tam; i++) {
		if (vetor[i] == valor)
			return i;
	}
	return -1;
}

//vetor jah estah ordenado
/*int buscaBinaria(int* vetor, int ini, int fim, int valor) {
	int tam = fim + 1;

	while (tam >= 1) {
		//procurar indice do meio
		int meio = ceil((fim + ini) / 2.0);

		if (vetor[meio] == valor)
			return meio;
		else if (valor < vetor[meio]) {
			//busca segue pela esquerda
			fim = meio - 1;
		}
		else {
			//busca segue pela esquerda
			ini = meio + 1;
		}
		tam = fim - ini + 1;
	}
	return -1;
}*/

int buscaBinaria(int* vetor, int ini, int fim, int valor) {
	int tam = fim - ini + 1;;
	if (tam >= 1) {
		//procurar indice do meio
		int meio = ceil((fim + ini) / 2.0);
		if (vetor[meio] == valor)
			return meio;
		else if (valor < vetor[meio]) {
			//busca segue pela esquerda
			fim = meio - 1;			
		}
		else {
			//busca segue pela direita
			ini = meio + 1;
		}
		return buscaBinaria(vetor, ini, fim, valor);
	}
	return -1;
}

int main() {
	int vetor[] = {1,2,3,4,5,6,7,8,9,10};
	printf("Busca binaria(3): %d\n", buscaBinaria(vetor, 0, 9, 3));
	printf("Busca binaria(4): %d\n", buscaBinaria(vetor, 0, 9, 4));
	printf("Busca binaria(9): %d\n", buscaBinaria(vetor, 0, 9, 9));
	return 0;
}