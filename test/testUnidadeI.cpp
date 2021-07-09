#include "pch.h"
#include "../src/provas/unidade1resp.h"

class Unidade1Test : public ::testing::Test {
protected:
	virtual void TearDown() {
		TearDownArrayList();
		TearDownDoublyLinkedList();
	}

	void TearDownArrayList() {
		free(listaAL->vetor);
		free(listaAL);
	}

	void TearDownDoublyLinkedList() {
		struct no* aux;
		struct no* proxNo = listaDLL->cabeca;
		while (proxNo != NULL) {
			aux = proxNo;
			proxNo = proxNo->prox;
			free(aux);
		}
		free(listaDLL);
	}

	virtual void SetUp() {
		listaAL = inicializarAL(10);
		listaDLL = inicializarDLL();
	}

	struct arraylist* listaAL = NULL;
	struct doublylinkedlist* listaDLL = NULL;
};

TEST_F(Unidade1Test, InverterArrayListNumPar) {
	int qtdadeElementos = 10;
	for (int i = 1; i <= qtdadeElementos; i++) {
		inserirElementoNoFim(listaAL, i);
	}
	inverterArrayList(listaAL);
	for (int i = 0; i < qtdadeElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(listaAL, i), qtdadeElementos - i);
	}
}

TEST_F(Unidade1Test, InverterArrayListNumImpar) {
	int qtdadeElementos = 11;
	for (int i = 1; i <= qtdadeElementos; i++) {
		inserirElementoNoFim(listaAL, i);
	}
	inverterArrayList(listaAL);
	for (int i = 0; i < qtdadeElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(listaAL, i), qtdadeElementos - i);
	}
}

TEST_F(Unidade1Test, InverterDoublyLinkedListNumPar) {
	int qtdadeElementos = 10;
	for (int i = 1; i <= qtdadeElementos; i++) {
		inserirElementoNoFim(listaDLL, i);
	}
	inverterDoublyLinkedList(listaDLL);
	for (int i = 0; i < qtdadeElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(listaDLL, i), qtdadeElementos-i);
	}	
}

TEST_F(Unidade1Test, InverterDoublyLinkedListNumImpar) {
	int qtdadeElementos = 11;
	for (int i = 1; i <= qtdadeElementos; i++) {
		inserirElementoNoFim(listaDLL, i);
	}
	inverterDoublyLinkedList(listaDLL);
	for (int i = 0; i < qtdadeElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(listaDLL, i), qtdadeElementos - i);
	}
}

TEST_F(Unidade1Test, AdicionarOrdenadoViaBuscaBinaria) {
	//como a lista foi inicializada com 10, entao conseguimos 
	//adicionar um elemento sem precisar alocar mais espaco
	int qtdadeElementos = 9;
	for (int i = 1; i <= qtdadeElementos; i++) {
		inserirElementoNoFim(listaAL, i*2);
	}
	insereOrdenado(listaAL, rand() % (qtdadeElementos * 2));
	for (int i = 0; i < qtdadeElementos; i++) {		//na verdade, o tamanho do array 
		                                            //eh qtdadeElementos+1 (dps da insercao)
													//por isso que a seguinte comparacao 
													//eh possivel 
		EXPECT_TRUE(listaAL->vetor[i] <= listaAL->vetor[i+1]);
	}
}
