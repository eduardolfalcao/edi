//Para Windows (MS Visual Studio):
#include "pch.h"

//Para Linux:
//#include <gtest/gtest.h>

#include "../src/listas/bibliotecas/arraylist2.h"
#include <math.h>

class ArrayListTest2 : public ::testing::Test {
protected:
	virtual void TearDown() {
		free(lista->vetor);
		free(lista);
	}

	virtual void SetUp() {
		int capacidade = 5;
		lista = inicializar(capacidade);
	}
	struct arraylist* lista = NULL;
};

TEST_F(ArrayListTest2, InsercaoListaVaziaFim) {
	inserirElementoNoFim(lista, 10);
	EXPECT_EQ(lista->qtdade, 1);
	EXPECT_EQ(obterElementoEmPosicao(lista, 0), 10);
}

TEST_F(ArrayListTest2, InsercaoListaVaziaInicio) {
	int pos = 0;
	inserirElementoEmPosicao(lista, 10, pos);
	EXPECT_EQ(lista->qtdade, 1);
	EXPECT_EQ(obterElementoEmPosicao(lista, 0), 10);
}

TEST_F(ArrayListTest2, InsercaoListaNaoVaziaFimSemDuplicar) {
	int numElementos = lista->capacidade;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoFim(lista, i);
	}
	EXPECT_EQ(lista->qtdade, numElementos);
	for (int i = 0; i < numElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(lista, i), i);
	}
}

TEST_F(ArrayListTest2, InsercaoListaNaoVaziaFimDuplicando) {
	int numElementos = 2 * lista->capacidade;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoFim(lista, i);
	}
	EXPECT_EQ(lista->qtdade, numElementos);
	for (int i = 0; i < numElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(lista, i), i);
	}
}

TEST_F(ArrayListTest2, InsercaoListaNaoVaziaInicioSemDuplicar) {
	int numElementos = lista->capacidade;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoEmPosicao(lista, i, 0);
	}
	EXPECT_EQ(lista->qtdade, numElementos);
	for (int i = 0; i < numElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(lista, numElementos-1-i), i);
	}
}

TEST_F(ArrayListTest2, InsercaoListaNaoVaziaInicioDuplicando) {
	int numElementos = 2 * lista->capacidade;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoEmPosicao(lista, i, 0);
	}
	EXPECT_EQ(lista->qtdade, numElementos);
	for (int i = 0; i < numElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(lista, numElementos - 1 - i), i);
	}
}

TEST_F(ArrayListTest2, InsercaoaEmPosicaoMeioSemDuplicar) {
	int numElementos = lista->capacidade/2;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoEmPosicao(lista, i, i);
	}

	int pos = numElementos /2;
	int numQualquer = 123456;
	//essa insercao eh no meio mas nao causa duplicacao da lista
	inserirElementoEmPosicao(lista, numQualquer, pos);
	EXPECT_EQ(obterElementoEmPosicao(lista,  pos), numQualquer);
}

TEST_F(ArrayListTest2, InsercaoaEmPosicaoMeioDuplicando) {
	int numElementos = lista->capacidade;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoEmPosicao(lista, i, i);
	}

	int pos = numElementos / 2;
	int numQualquer = 123456;
	//essa insercao eh no meio e causa duplicacao da lista
	inserirElementoEmPosicao(lista, numQualquer, pos);
	EXPECT_EQ(obterElementoEmPosicao(lista, pos), numQualquer);
}

TEST_F(ArrayListTest2, RemocaoFim1) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoFim(lista, i);
	}
	EXPECT_EQ(lista->qtdade, numElementos);
	for (int i = 0; i < numElementos; i++) {
		removerElementoNoFim(lista);
		EXPECT_EQ(lista->qtdade, numElementos - i - 1);
	}
	EXPECT_EQ(lista->qtdade, 0);
}

TEST_F(ArrayListTest2, RemocaoFim2) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoFim(lista, i);
	}
	EXPECT_EQ(lista->qtdade, numElementos);
	for (int i = 0; i < numElementos; i++) {
		removerElementoEmPosicao(lista, numElementos - i - 1);
		EXPECT_EQ(lista->qtdade, numElementos - i - 1);
	}
	EXPECT_EQ(lista->qtdade, 0);
}

TEST_F(ArrayListTest2, RemocaoInicio) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoFim(lista, i);
	}
	EXPECT_EQ(lista->qtdade, numElementos);
	for (int i = 0; i < numElementos; i++) {
		removerElementoEmPosicao(lista, 0);
		EXPECT_EQ(lista->qtdade, numElementos - i - 1);
		if (lista->qtdade > 0)
			EXPECT_EQ(obterElementoEmPosicao(lista, 0), i + 1);
	}
	EXPECT_EQ(lista->qtdade, 0);
}

TEST_F(ArrayListTest2, RemocaoMeio) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		double tamDouble = (double)lista->qtdade;
		int pos = ceil(tamDouble / 2);
		inserirElementoEmPosicao(lista, i, pos);
	}
	EXPECT_EQ(lista->qtdade, numElementos);
	while (lista->qtdade > 0) {
		EXPECT_EQ(obterElementoEmPosicao(lista, ceil(lista->qtdade / 2)), lista->qtdade - 1);
		removerElementoEmPosicao(lista, ceil(lista->qtdade / 2));
	}
	EXPECT_EQ(lista->qtdade, 0);
}

TEST_F(ArrayListTest2, AtualizarElemento) {
	int numElementos = 100;
	for (int i = 0; i < numElementos; i++) {
		inserirElementoNoFim(lista, i);
	}
	int numQualquer = 123456;
	for (int i = 0; i < numElementos; i++) {
		atualizarElemento(lista, 123456, i);
	}
	for (int i = 0; i < numElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(lista, i), numQualquer);
	}
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
