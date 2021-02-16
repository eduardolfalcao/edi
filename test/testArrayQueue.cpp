#include "pch.h"
#include "../src/filas/bibliotecas/arrayqueue.h"

class ArrayQueueTest : public ::testing::Test {
protected:
	virtual void TearDown() {
		free(fila);
	}

	virtual void SetUp() {
		fila = (struct FilaArray*)malloc(sizeof(struct FilaArray));
		fila->frente = -1;
		fila->tras = -1;
	}

	struct FilaArray* fila;	
};

TEST_F(ArrayQueueTest, EnfileiramentoFilaVazia) {
	EXPECT_EQ(tamanho(fila), 0);
	int numQualquer = 123456;
	enfileirar(fila, numQualquer);
	EXPECT_EQ(tamanho(fila), 1);
	EXPECT_EQ(frente(fila), numQualquer);
}

TEST_F(ArrayQueueTest, EnfileiramentoFilaNaoVazia) {
	int numQualquer = 123456;
	enfileirar(fila, numQualquer);
	int outroNumQualquer = 7890;
	enfileirar(fila, outroNumQualquer);
	EXPECT_EQ(tamanho(fila), 2);
	EXPECT_EQ(frente(fila), numQualquer);
}

TEST_F(ArrayQueueTest, DesenfileiramentoFilaVazia) {
	desenfileirar(fila);
	EXPECT_EQ(tamanho(fila), 0);
}

TEST_F(ArrayQueueTest, DesenfileiramentoFilaNaoVazia) {
	int numQualquer = 123456;
	enfileirar(fila, numQualquer);
	int outroNumQualquer = 7890;
	enfileirar(fila, outroNumQualquer);
	desenfileirar(fila);
	EXPECT_EQ(tamanho(fila), 1);
	desenfileirar(fila);
	EXPECT_EQ(tamanho(fila), 0);
}

TEST_F(ArrayQueueTest, VaziaFilaVazia) {
	EXPECT_TRUE(vazia(fila));
}

TEST_F(ArrayQueueTest, VaziaFilaNaoVazia) {
	int numQualquer = 123456;
	enfileirar(fila, numQualquer);
	EXPECT_FALSE(vazia(fila));
}

TEST_F(ArrayQueueTest, TamanhoFilaVazia) {
	EXPECT_EQ(tamanho(fila), 0);
}

TEST_F(ArrayQueueTest, TamanhoFilaNaoVazia) {
	EXPECT_EQ(tamanho(fila), 0);
	int numQualquer = 123456;
	enfileirar(fila, numQualquer);
	EXPECT_EQ(tamanho(fila), 1);
	enfileirar(fila, numQualquer);
	EXPECT_EQ(tamanho(fila), 2);
	int outroNumQualquer = 7890;
	enfileirar(fila, outroNumQualquer);
	EXPECT_EQ(tamanho(fila), 3);
	desenfileirar(fila);
	EXPECT_EQ(tamanho(fila), 2);
}

TEST_F(ArrayQueueTest, FrenteFilaVazia) {
	EXPECT_EQ(frente(fila), INT_MIN);
}

TEST_F(ArrayQueueTest, FrenteFilaNaoVazia) {
	int numQualquer = 123456;
	enfileirar(fila, numQualquer);
	EXPECT_EQ(frente(fila), numQualquer);
}