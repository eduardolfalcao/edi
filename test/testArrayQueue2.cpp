//Para Windows (MS Visual Studio):
#include "pch.h"

//Para Linux:
//#include <gtest/gtest.h>

#include "../src/filas/bibliotecas/arrayqueue2.h"

class ArrayQueueTest2 : public ::testing::Test {
protected:
	virtual void TearDown() {
		if (fila != NULL) {
			if (fila->elementos != NULL) {
				free(fila->elementos);
			}
			free(fila);
			fila = NULL;
		}
	}

	virtual void SetUp() {
		fila = inicializar(10);
	}

	struct arrayqueue* fila;
};

TEST_F(ArrayQueueTest2, EnfileiramentoFilaNula) {
	TearDown();

	int numQualquer = 123456;
	enfileirar(&fila, numQualquer);
	EXPECT_EQ(fila->qtdade, 1);
	EXPECT_EQ(frente(fila), numQualquer);
}

TEST_F(ArrayQueueTest2, EnfileiramentoFilaVazia) {
	EXPECT_EQ(fila->qtdade, 0);
	int numQualquer = 123456;
	enfileirar(&fila, numQualquer);
	EXPECT_EQ(fila->qtdade, 1);
	EXPECT_EQ(frente(fila), numQualquer);
}

TEST_F(ArrayQueueTest2, EnfileiramentoFilaNaoVazia) {
	int numQualquer = 123456;
	enfileirar(&fila, numQualquer);
	int outroNumQualquer = 7890;
	enfileirar(&fila, outroNumQualquer);
	EXPECT_EQ(fila->qtdade, 2);
	EXPECT_EQ(frente(fila), numQualquer);
}

TEST_F(ArrayQueueTest2, EnfileiramentoFilaCheia) {
	for (int i = 0; i < fila->tamanho; i++) {
		enfileirar(&fila, i);
	}
	EXPECT_EQ(fila->qtdade, fila->tamanho);
	enfileirar(&fila, 123);
	//fila cheia, não enfileiramos mais
	EXPECT_EQ(fila->qtdade, fila->tamanho);	
}

TEST_F(ArrayQueueTest2, DesenfileiramentoFilaNula) {
	TearDown();

	EXPECT_EQ(desenfileirar(fila), INT_MIN);
}

TEST_F(ArrayQueueTest2, DesenfileiramentoFilaVazia) {
	EXPECT_EQ(desenfileirar(fila), INT_MIN);
	EXPECT_EQ(fila->qtdade, 0);
}

TEST_F(ArrayQueueTest2, DesenfileiramentoFilaNaoVazia) {
	int numQualquer = 123456;
	enfileirar(&fila, numQualquer);
	int outroNumQualquer = 7890;
	enfileirar(&fila, outroNumQualquer);
	EXPECT_EQ(desenfileirar(fila), numQualquer);
	EXPECT_EQ(fila->qtdade, 1);
	EXPECT_EQ(desenfileirar(fila), outroNumQualquer);
	EXPECT_EQ(fila->qtdade, 0);
	EXPECT_EQ(desenfileirar(fila), INT_MIN);
	EXPECT_EQ(fila->qtdade, 0);
}

TEST_F(ArrayQueueTest2, FrenteFilaNula) {
	TearDown();

	EXPECT_EQ(frente(fila), INT_MIN);
}

TEST_F(ArrayQueueTest2, FrenteFilaVazia) {
	EXPECT_EQ(frente(fila), INT_MIN);
}

TEST_F(ArrayQueueTest2, FrenteFilaNaoVazia) {
	int numQualquer = 123456;
	enfileirar(&fila, numQualquer);
	EXPECT_EQ(frente(fila), numQualquer);
}


TEST_F(ArrayQueueTest2, EnfileiramentoDesenfileiramentoFilaCircular) {
	for (int i = 0; i < fila->tamanho; i++) {
		enfileirar(&fila, i);
	}
	desenfileirar(fila);
	EXPECT_EQ(fila->qtdade, fila->tamanho-1);
	desenfileirar(fila);
	EXPECT_EQ(fila->qtdade, fila->tamanho - 2);

	EXPECT_EQ(frente(fila), 2);

	enfileirar(&fila, 10);
	enfileirar(&fila, 11);

	for (int i = 2; i < fila->tamanho+2; i++) {
		EXPECT_EQ(frente(fila), i);
		desenfileirar(fila);		
	}
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}