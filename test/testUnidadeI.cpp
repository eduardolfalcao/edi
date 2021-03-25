#include "pch.h"
#include "../src/provas/unidade1respaluno.h"

class Unidade1Test : public ::testing::Test {
protected:
	virtual void TearDown() {
		TearDownArrayList();
		TearDownDoublyLinkedList();
	}

	void TearDownArrayList() {
		tamanhoArrayList = 0;
		arrayList = NULL;
		capacidadeArrayList = 0;
	}

	void TearDownDoublyLinkedList() {
		struct no* aux;
		while (doublyLinkedList != NULL) {
			aux = doublyLinkedList;
			doublyLinkedList = doublyLinkedList->prox;
			free(aux);
		}
		tamanhoDoublyLinkedList = 0;
	}

	virtual void SetUp() {
		capacidadeArrayList = 10;
		inicializar(&arrayList, capacidadeArrayList);
	}

	int tamanhoArrayList = 0;
	int capacidadeArrayList = 0;
	int* arrayList = NULL;

	int tamanhoDoublyLinkedList = 0;
	struct no* doublyLinkedList = NULL;

};

TEST_F(Unidade1Test, InverterArrayListNumPar) {
	int qtdadeElementos = 10;
	for (int i = 1; i <= qtdadeElementos; i++) {
		inserirElementoNoFim(&arrayList, i, &tamanhoArrayList, &capacidadeArrayList);
	}
	inverterArrayList(arrayList, tamanhoArrayList);
	for (int i = 0; i < qtdadeElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(arrayList, i, tamanhoArrayList), qtdadeElementos - i);
	}
}

TEST_F(Unidade1Test, InverterArrayListNumImpar) {
	int qtdadeElementos = 11;
	for (int i = 1; i <= qtdadeElementos; i++) {
		inserirElementoNoFim(&arrayList, i, &tamanhoArrayList, &capacidadeArrayList);
	}
	inverterArrayList(arrayList, tamanhoArrayList);
	for (int i = 0; i < qtdadeElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(arrayList, i, tamanhoArrayList), qtdadeElementos - i);
	}
}

TEST_F(Unidade1Test, InverterDoublyLinkedListNumPar) {
	int qtdadeElementos = 10;
	for (int i = 1; i <= qtdadeElementos; i++) {
		inserirElementoNoFim(&doublyLinkedList, i, &tamanhoDoublyLinkedList);
	}
	inverterDoublyLinkedList(&doublyLinkedList, tamanhoDoublyLinkedList);
	for (int i = 0; i < qtdadeElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(&doublyLinkedList, i), qtdadeElementos-i);
	}	
}

TEST_F(Unidade1Test, InverterDoublyLinkedListNumImpar) {
	int qtdadeElementos = 11;
	for (int i = 1; i <= qtdadeElementos; i++) {
		inserirElementoNoFim(&doublyLinkedList, i, &tamanhoDoublyLinkedList);
	}
	inverterDoublyLinkedList(&doublyLinkedList, tamanhoDoublyLinkedList);
	for (int i = 0; i < qtdadeElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(&doublyLinkedList, i), qtdadeElementos - i);
	}
}

TEST_F(Unidade1Test, AdicionarOrdenadoViaBuscaBinaria) {
	//como a lista foi inicializada com 10, entao conseguimos 
	//adicionar um elemento sem precisar alocar mais espaco
	int qtdadeElementos = 9;
	for (int i = 1; i <= qtdadeElementos; i++) {
		inserirElementoNoFim(&arrayList, i*2, &tamanhoArrayList, &capacidadeArrayList);
	}
	insereOrdenado(arrayList, qtdadeElementos, rand() % (qtdadeElementos * 2));
	for (int i = 0; i < qtdadeElementos; i++) {		//na verdade, o tamanho do array 
		                                            //eh qtdadeElementos+1 (dps da insercao)
													//por isso que a seguinte comparacao 
													//eh possivel 
		EXPECT_TRUE(arrayList[i]<=arrayList[i+1]);
	}
}
