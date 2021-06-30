//Para Windows (MS Visual Studio):
#include "pch.h"

//Para Linux:
//#include <gtest/gtest.h>

#include "../src/filas/bibliotecas/linkedqueue2.h"

class LinkedQueueTest2 : public ::testing::Test {
protected:
	virtual void TearDown() {
		while (!vazia(fila)) {
			desenfileirar(fila);
		}
		free(fila);
	}

	virtual void SetUp() {
		fila = inicializar();
	}

	struct linkedqueue* fila;
};

TEST_F(LinkedQueueTest2, EnfileiramentoFilaNula) {
	free(fila);
	fila = NULL;
	
	int numQualquer = 123456;
	enfileirar(&fila, numQualquer);
	EXPECT_EQ(fila->qtdade, 1);
	EXPECT_EQ(frente(fila), numQualquer);
}

TEST_F(LinkedQueueTest2, EnfileiramentoFilaVazia) {
	EXPECT_EQ(fila->qtdade, 0);
	int numQualquer = 123456;
	enfileirar(&fila, numQualquer);
	EXPECT_EQ(fila->qtdade, 1);
	EXPECT_EQ(frente(fila), numQualquer);
}

TEST_F(LinkedQueueTest2, EnfileiramentoFilaNaoVazia) {
	int numQualquer = 123456;
	enfileirar(&fila, numQualquer);
	int outroNumQualquer = 7890;
	enfileirar(&fila, outroNumQualquer);
	EXPECT_EQ(fila->qtdade, 2);
	EXPECT_EQ(frente(fila), numQualquer);
}

TEST_F(LinkedQueueTest2, DesenfileiramentoFilaNula) {
	free(fila);
	fila = NULL; 
	
	EXPECT_EQ(desenfileirar(fila), INT_MIN);
}

TEST_F(LinkedQueueTest2, DesenfileiramentoFilaVazia) {
	EXPECT_EQ(desenfileirar(fila), INT_MIN);
	EXPECT_EQ(fila->qtdade, 0);
	EXPECT_EQ(frente(fila), INT_MIN);
}

TEST_F(LinkedQueueTest2, DesenfileiramentoFilaNaoVazia) {
	int numQualquer = 123456;
	enfileirar(&fila, numQualquer);
	int outroNumQualquer = 7890;
	enfileirar(&fila, outroNumQualquer);
	EXPECT_EQ(desenfileirar(fila), numQualquer);
	EXPECT_EQ(fila->qtdade, 1);
	EXPECT_EQ(desenfileirar(fila), outroNumQualquer);
	EXPECT_EQ(fila->qtdade, 0);
}

TEST_F(LinkedQueueTest2, VaziaFilaNula) {
	free(fila);
	fila = NULL;

	EXPECT_TRUE(vazia(fila));
}

TEST_F(LinkedQueueTest2, VaziaFilaVazia) {
	EXPECT_TRUE(vazia(fila));
}

TEST_F(LinkedQueueTest2, VaziaFilaNaoVazia) {
	int numQualquer = 123456;
	enfileirar(&fila, numQualquer);
	EXPECT_FALSE(vazia(fila));
}

TEST_F(LinkedQueueTest2, TamanhoFilaVazia) {
	EXPECT_EQ(fila->qtdade, 0);
}

TEST_F(LinkedQueueTest2, TamanhoFilaNaoVazia) {
	EXPECT_EQ(fila->qtdade, 0);
	int numQualquer = 123456;
	enfileirar(&fila, numQualquer);
	EXPECT_EQ(fila->qtdade, 1);
	enfileirar(&fila, numQualquer);
	EXPECT_EQ(fila->qtdade, 2);
	int outroNumQualquer = 7890;
	enfileirar(&fila, outroNumQualquer);
	EXPECT_EQ(fila->qtdade, 3);
	EXPECT_EQ(desenfileirar(fila), numQualquer);
	EXPECT_EQ(fila->qtdade, 2);
}

TEST_F(LinkedQueueTest2, FrenteFilaNula) {
	free(fila);
	fila = NULL;

	EXPECT_EQ(frente(fila), INT_MIN);
}

TEST_F(LinkedQueueTest2, FrenteFilaVazia) {
	EXPECT_EQ(frente(fila), INT_MIN);
}

TEST_F(LinkedQueueTest2, FrenteFilaNaoVazia) {
	int numQualquer = 123456;
	enfileirar(&fila, numQualquer);
	EXPECT_EQ(frente(fila), numQualquer);
	EXPECT_EQ(frente(fila), numQualquer);
	EXPECT_EQ(frente(fila), numQualquer);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}