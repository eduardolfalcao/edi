//Para Windows (MS Visual Studio):
#include "pch.h"

//Para Linux:
//#include <gtest/gtest.h>

#include "../src/listas/bibliotecas/doublylinkedlist2.h"
#include <math.h>

class DoublyLinkedListTest2 : public ::testing::Test {
protected:
	virtual void TearDown() {
		struct no* aux;
		struct no* proxNo = lista->cabeca;
		while (proxNo != NULL) {
			aux = proxNo;
			proxNo = proxNo->prox;
			free(aux);
		}
		free(lista);
	}

	virtual void SetUp() {
		lista = inicializar();
	}

	struct doublylinkedlist* lista = NULL;
};

TEST_F(DoublyLinkedListTest2, InsercaoListaVaziaFim) {
	inserirElementoNoFim(lista, 10);
	EXPECT_EQ(lista->qtdade, 1);
	EXPECT_EQ(obterElementoEmPosicao(lista, 0), 10);
}

TEST_F(DoublyLinkedListTest2, InsercaoListaVaziaInicio) {
	inserirElementoNoInicio(lista, 10);
	EXPECT_EQ(lista->qtdade, 1);
	EXPECT_EQ(obterElementoEmPosicao(lista, 0), 10);
	EXPECT_EQ(lista->cabeca->val, 10);
	EXPECT_EQ(lista->cauda->val, 10);
}

TEST_F(DoublyLinkedListTest2, InsercaoListaNaoVaziaFim) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoFim(lista, i);
	}
	EXPECT_EQ(lista->qtdade, numElementos);
	for (int i = 0; i < numElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(lista, i), i);
	}	
	EXPECT_EQ(lista->cabeca->val, 0);
	EXPECT_EQ(lista->cauda->val, numElementos-1);
}

TEST_F(DoublyLinkedListTest2, InsercaoListaNaoVaziaInicio) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoInicio(lista, i);
	}
	EXPECT_EQ(lista->qtdade, numElementos);
	for (int i = 0; i < numElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(lista, i), numElementos-1-i);
	}
	EXPECT_EQ(lista->cabeca->val, numElementos - 1);
	EXPECT_EQ(lista->cauda->val, 0);
}

TEST_F(DoublyLinkedListTest2, InsercaoEmPosicaoFim) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoEmPosicao(lista, i, i);
	}
	EXPECT_EQ(lista->qtdade, numElementos);
	for (int i = 0; i < numElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(lista, i), i);
	}
	EXPECT_EQ(lista->cabeca->val, 0);
	EXPECT_EQ(lista->cauda->val, numElementos - 1);
}

TEST_F(DoublyLinkedListTest2, InsercaoaEmPosicaoMeio) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoEmPosicao(lista, i, i);
	}

	int pos = 50;
	inserirElementoEmPosicao(lista, 9999, pos);
	EXPECT_EQ(obterElementoEmPosicao(lista, pos), 9999);

	EXPECT_EQ(lista->cabeca->val, 0);
	EXPECT_EQ(lista->cauda->val, numElementos - 1);
}

TEST_F(DoublyLinkedListTest2, InsercaoEmPosicaoInicio) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoEmPosicao(lista, i, 0);
	}
	EXPECT_EQ(lista->qtdade, numElementos);
	for (int i = 0; i < numElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(lista, i), numElementos - 1 - i);
	}

	EXPECT_EQ(lista->cabeca->val, numElementos - 1);
	EXPECT_EQ(lista->cauda->val, 0);
}

//obterElementoEmPosicao já foi testado em todos os casos de teste

TEST_F(DoublyLinkedListTest2, RemocaoFim) {
	int numElementos = 5;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoFim(lista, i);
	}
	EXPECT_EQ(lista->qtdade, numElementos);
	for (int i = 0; i < numElementos; i++) {
		removerElementoEmPosicao(lista, numElementos-i-1);
		EXPECT_EQ(lista->qtdade, numElementos-i-1);
	}
	EXPECT_EQ(lista->qtdade,0);
	EXPECT_EQ(lista->cabeca, nullptr);
	EXPECT_EQ(lista->cauda, nullptr);
}

TEST_F(DoublyLinkedListTest2, RemocaoInicio) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoFim(lista, i);
	}
	EXPECT_EQ(lista->qtdade, numElementos);
	for (int i = 0; i < numElementos; i++) {
		removerElementoEmPosicao(lista, 0);
		EXPECT_EQ(lista->qtdade, numElementos - i - 1);
		if(lista->qtdade>0)
			EXPECT_EQ(obterElementoEmPosicao(lista, 0), i+1);
	}
	EXPECT_EQ(lista->qtdade, 0);
	EXPECT_EQ(lista->cabeca, nullptr);
	EXPECT_EQ(lista->cauda, nullptr);
}

TEST_F(DoublyLinkedListTest2, RemocaoMeio) {
	int numElementos = 10;
	for (int i = 0; i < numElementos; i++) {
		double tamDouble = (double)lista->qtdade;
		int pos = ceil(tamDouble / 2);
		inserirElementoEmPosicao(lista, i, pos);
	}
	EXPECT_EQ(lista->qtdade, numElementos);
	while (lista->qtdade > 0) {
		EXPECT_EQ(obterElementoEmPosicao(lista, ceil(lista->qtdade / 2)), lista->qtdade-1);
		removerElementoEmPosicao(lista, ceil(lista->qtdade / 2));
	}
	EXPECT_EQ(lista->qtdade, 0);
	EXPECT_EQ(lista->cabeca, nullptr);
	EXPECT_EQ(lista->cauda, nullptr);
}