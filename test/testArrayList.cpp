//Para Windows (MS Visual Studio):
#include "pch.h"

//Para Linux:
//#include <gtest/gtest.h>

#include "../src/listas/bibliotecas/arraylist.h"
#include <math.h>

class ArrayListTest : public ::testing::Test {
protected:
	virtual void TearDown() {
		tamanho = 0;
		lista = NULL;
		capacidade = 0;
	}

	virtual void SetUp() {
		capacidade = 5;
		inicializar(&lista, capacidade);
	}

	int tamanho = 0;
	int capacidade = 0;
	int* lista = NULL;
};

TEST_F(ArrayListTest, InsercaoListaVaziaFim) {
	inserirElementoNoFim(&lista, 10, &tamanho, &capacidade);
	EXPECT_EQ(tamanho, 1);
	EXPECT_EQ(obterElementoEmPosicao(lista, 0, tamanho), 10);
}

TEST_F(ArrayListTest, InsercaoListaVaziaInicio) {
	int pos = 0;
	inserirElementoEmPosicao(&lista, 10, pos, &tamanho, &capacidade);
	EXPECT_EQ(tamanho, 1);
	EXPECT_EQ(obterElementoEmPosicao(lista, 0, tamanho), 10);
}

TEST_F(ArrayListTest, InsercaoListaNaoVaziaFimSemDuplicar) {
	int numElementos = capacidade;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoFim(&lista, i, &tamanho, &capacidade);
	}
	EXPECT_EQ(tamanho, numElementos);
	for (int i = 0; i < numElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(lista, i, tamanho), i);
	}
}

TEST_F(ArrayListTest, InsercaoListaNaoVaziaFimDuplicando) {
	int numElementos = 2*capacidade;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoFim(&lista, i, &tamanho, &capacidade);
	}
	EXPECT_EQ(tamanho, numElementos);
	for (int i = 0; i < numElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(lista, i, tamanho), i);
	}
}

TEST_F(ArrayListTest, InsercaoListaNaoVaziaInicioSemDuplicar) {
	int numElementos = capacidade;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoEmPosicao(&lista, i, 0, &tamanho, &capacidade);
	}
	EXPECT_EQ(tamanho, numElementos);
	for (int i = 0; i < numElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(lista, numElementos-1-i, tamanho), i);
	}
}

TEST_F(ArrayListTest, InsercaoListaNaoVaziaInicioDuplicando) {
	int numElementos = 2*capacidade;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoEmPosicao(&lista, i, 0, &tamanho, &capacidade);
	}
	EXPECT_EQ(tamanho, numElementos);
	for (int i = 0; i < numElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(lista, numElementos - 1 - i, tamanho), i);
	}
}

TEST_F(ArrayListTest, InsercaoaEmPosicaoMeioSemDuplicar) {
	int numElementos = capacidade/2;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoEmPosicao(&lista, i, i, &tamanho, &capacidade);
	}

	int pos = numElementos /2;
	int numQualquer = 123456;
	//essa insercao eh no meio mas nao causa duplicacao da lista
	inserirElementoEmPosicao(&lista, numQualquer, pos, &tamanho, &capacidade);
	EXPECT_EQ(obterElementoEmPosicao(lista,  pos, tamanho), numQualquer);
}

TEST_F(ArrayListTest, InsercaoaEmPosicaoMeioDuplicando) {
	int numElementos = capacidade;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoEmPosicao(&lista, i, i, &tamanho, &capacidade);
	}

	int pos = numElementos / 2;
	int numQualquer = 123456;
	//essa insercao eh no meio e causa duplicacao da lista
	inserirElementoEmPosicao(&lista, numQualquer, pos, &tamanho, &capacidade);
	EXPECT_EQ(obterElementoEmPosicao(lista, pos, tamanho), numQualquer);
}

TEST_F(ArrayListTest, RemocaoFim1) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoFim(&lista, i, &tamanho, &capacidade);
	}
	EXPECT_EQ(tamanho, numElementos);
	for (int i = 0; i < numElementos; i++) {
		removerElementoNoFim(&tamanho);
		EXPECT_EQ(tamanho, numElementos - i - 1);
	}
	EXPECT_EQ(tamanho, 0);
}

TEST_F(ArrayListTest, RemocaoFim2) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoFim(&lista, i, &tamanho, &capacidade);
	}
	EXPECT_EQ(tamanho, numElementos);
	for (int i = 0; i < numElementos; i++) {
		removerElementoEmPosicao(lista, numElementos - i - 1, &tamanho);
		EXPECT_EQ(tamanho, numElementos - i - 1);
	}
	EXPECT_EQ(tamanho, 0);
}

TEST_F(ArrayListTest, RemocaoInicio) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoFim(&lista, i, &tamanho, &capacidade);
	}
	EXPECT_EQ(tamanho, numElementos);
	for (int i = 0; i < numElementos; i++) {
		removerElementoEmPosicao(lista, 0, &tamanho);
		EXPECT_EQ(tamanho, numElementos - i - 1);
		if (tamanho > 0)
			EXPECT_EQ(obterElementoEmPosicao(lista, 0, tamanho), i + 1);
	}
	EXPECT_EQ(tamanho, 0);
}

TEST_F(ArrayListTest, RemocaoMeio) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		double tamDouble = (double)tamanho;
		int pos = ceil(tamDouble / 2);
		inserirElementoEmPosicao(&lista, i, pos, &tamanho, &capacidade);
	}
	EXPECT_EQ(tamanho, numElementos);
	while (tamanho > 0) {
		EXPECT_EQ(obterElementoEmPosicao(lista, ceil(tamanho / 2), tamanho), tamanho - 1);
		removerElementoEmPosicao(lista, ceil(tamanho / 2), &tamanho);
	}
	EXPECT_EQ(tamanho, 0);
}

TEST_F(ArrayListTest, AtualizarElemento) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoFim(&lista, i, &tamanho, &capacidade);
	}
	int numQualquer = 123456;
	for (int i = 0; i < numElementos; i++) {
		atualizarElemento(lista, 123456, i, tamanho);
	}
	for (int i = 0; i < numElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(lista, i, tamanho), numQualquer);
	}
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
