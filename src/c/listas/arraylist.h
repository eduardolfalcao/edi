#include <stdio.h>
#include <stdlib.h>

void inicializar(int** lista, int capacidade) {
	(*lista) = (int*) calloc(capacidade, sizeof(int));
}

int obterElementoEmPosicao(int* lista, int posicao, int tamanho) {
	//TODO
}

//sempre que surgir a necessidade de reatribuição, como eh o cado de duplicarCapacidade
//nós precisaremos de dereferencing, para que a variável original lista seja atualizada
//note que inserção é a operação que pode necessitar chamar duplicarCapacidade
void duplicarCapacidade(int** lista, int* capacidade) {
    (*lista) = (int*)realloc((*lista), 2 * (*capacidade) * sizeof(int));
    (*capacidade) = (*capacidade) * 2;
}

//como eu não consigo dinamicamente saber a qtdade de elementos alocado para meu ponteiro de lista
//então uso a variável capacidade para armazenar este valor
void inserirElementoNoFim(int** lista, int valor, int* tamanho, int* capacidade) {
	//TODO
}

void inserirElementoEmPosicao(int** lista, int valor, int posicao, int* tamanho, int* capacidade) {
	//TODO	
}


void atualizarElemento(int* lista, int valor, int posicao, int tamanho) {
	//TODO
}


void removerElementoNoFim(int* tamanho) {
	//TODO
}

void removerElementoEmPosicao(int* lista, int posicao, int* tamanho) {
	//TODO
}

void exibirLista(int* lista, int* tamanho) {
	printf("[");
	for (int i = 0; i < (*tamanho); i++) {
		printf("%d", lista[i]);
		if (i < (*tamanho) - 1) {
			printf(", ");
		}
	}
	printf("]");
}
