#include <gtest/gtest.h>
#include "../src/listas/linkedlist.h"
#include <math.h>

class LinkedListTest : public ::testing::Test {
protected:
	virtual void TearDown() {
		struct no* aux;
		while (lista != NULL) {
			aux = lista;
			lista = lista->prox;
			free(aux);
		}
		tamanho = 0;
	}

	int tamanho = 0;
	struct no* lista = NULL;
};

TEST_F(LinkedListTest, InsercaoListaVaziaFim) {
	inserirElementoNoFim(&lista, 10, &tamanho);
	EXPECT_EQ(tamanho, 1);
	EXPECT_EQ(obterElementoEmPosicao(&lista, 0), 10);
}

TEST_F(LinkedListTest, InsercaoListaVaziaInicio) {
	inserirElementoNoInicio(&lista, 10, &tamanho);
	EXPECT_EQ(tamanho, 1);
	EXPECT_EQ(obterElementoEmPosicao(&lista, 0), 10);
}

TEST_F(LinkedListTest, InsercaoListaNaoVaziaFim) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoFim(&lista, i, &tamanho);
	}
	EXPECT_EQ(tamanho, numElementos);
	for (int i = 0; i < numElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(&lista, i), i);
	}	
}

TEST_F(LinkedListTest, InsercaoListaNaoVaziaInicio) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoInicio(&lista, i, &tamanho);
	}
	EXPECT_EQ(tamanho, numElementos);
	for (int i = 0; i < numElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(&lista, i), numElementos-1-i);
	}
}

TEST_F(LinkedListTest, InsercaoEmPosicaoFim) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoEmPosicao(&lista, i, i, &tamanho);
	}
	EXPECT_EQ(tamanho, numElementos);
	for (int i = 0; i < numElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(&lista, i), i);
	}
}

TEST_F(LinkedListTest, InsercaoaEmPosicaoMeio) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoEmPosicao(&lista, i, i, &tamanho);
	}

	int pos = 50;
	inserirElementoEmPosicao(&lista, 9999, pos, &tamanho);
	EXPECT_EQ(obterElementoEmPosicao(&lista, pos), 9999);
}

TEST_F(LinkedListTest, InsercaoEmPosicaoInicio) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoEmPosicao(&lista, i, 0, &tamanho);
	}
	EXPECT_EQ(tamanho, numElementos);
	for (int i = 0; i < numElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(&lista, i), numElementos - 1 - i);
	}
}

//obterElementoEmPosicao já foi testado em todos os casos de teste

TEST_F(LinkedListTest, RemocaoFim) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoFim(&lista, i, &tamanho);
	}
	EXPECT_EQ(tamanho, numElementos);
	for (int i = 0; i < numElementos; i++) {
		removerElementoEmPosicao(&lista, numElementos-i-1, &tamanho);
		EXPECT_EQ(tamanho, numElementos-i-1);
	}
	EXPECT_EQ(tamanho,0);
}

TEST_F(LinkedListTest, RemocaoInicio) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoFim(&lista, i, &tamanho);
	}
	EXPECT_EQ(tamanho, numElementos);
	for (int i = 0; i < numElementos; i++) {
		removerElementoEmPosicao(&lista, 0, &tamanho);
		EXPECT_EQ(tamanho, numElementos - i - 1);
		if(tamanho>0)
			EXPECT_EQ(obterElementoEmPosicao(&lista, 0), i+1);
	}
	EXPECT_EQ(tamanho, 0);
}

TEST_F(LinkedListTest, RemocaoMeio) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		double tamDouble = (double)tamanho;
		int pos = ceil(tamDouble / 2);
		inserirElementoEmPosicao(&lista, i, pos, &tamanho);
	}
	EXPECT_EQ(tamanho, numElementos);
	while (tamanho > 0) {
		EXPECT_EQ(obterElementoEmPosicao(&lista, ceil(tamanho / 2)), tamanho-1);
		removerElementoEmPosicao(&lista, ceil(tamanho / 2), &tamanho);
	}
	EXPECT_EQ(tamanho, 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
