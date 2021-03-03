#include "pch.h"
#include "../src/filas/bibliotecas/linkedqueue2.h"

class LinkedQueueTest : public ::testing::Test {
protected:
	virtual void TearDown() {
		while (!vazia(fila)) {
			desenfileirar(fila);
		}
		free(fila);
	}

	virtual void SetUp() {
		fila = (struct FilaLigada*)malloc(sizeof(struct FilaLigada));
		fila->frente = NULL;
		fila->tras = NULL;
		fila->tamanho = 0;
	}

	struct FilaLigada* fila;
};

TEST_F(LinkedQueueTest, EnfileiramentoFilaVazia) {
	EXPECT_EQ(fila->tamanho, 0);
	int numQualquer = 123456;
	enfileirar(&fila, numQualquer);
	EXPECT_EQ(fila->tamanho, 1);
	EXPECT_EQ(frente(fila), numQualquer);
}

TEST_F(LinkedQueueTest, EnfileiramentoFilaNaoVazia) {
	int numQualquer = 123456;
	enfileirar(&fila, numQualquer);
	int outroNumQualquer = 7890;
	enfileirar(&fila, outroNumQualquer);
	EXPECT_EQ(fila->tamanho, 2);
	EXPECT_EQ(frente(fila), numQualquer);
}

TEST_F(LinkedQueueTest, DesenfileiramentoFilaVazia) {
	desenfileirar(fila);
	EXPECT_EQ(fila->tamanho, 0);
	int error = INT_MIN;
	EXPECT_EQ(frente(fila), error);
}

TEST_F(LinkedQueueTest, DesenfileiramentoFilaNaoVazia) {
	int numQualquer = 123456;
	enfileirar(&fila, numQualquer);
	int outroNumQualquer = 7890;
	enfileirar(&fila, outroNumQualquer);
	desenfileirar(fila);
	EXPECT_EQ(fila->tamanho, 1);
	desenfileirar(fila);
	EXPECT_EQ(fila->tamanho, 0);
}

TEST_F(LinkedQueueTest, VaziaFilaVazia) {
	EXPECT_TRUE(vazia(fila));
}

TEST_F(LinkedQueueTest, VaziaFilaNaoVazia) {
	int numQualquer = 123456;
	enfileirar(&fila, numQualquer);
	EXPECT_FALSE(vazia(fila));
}

TEST_F(LinkedQueueTest, TamanhoFilaVazia) {
	EXPECT_EQ(fila->tamanho, 0);
}

TEST_F(LinkedQueueTest, TamanhoFilaNaoVazia) {
	EXPECT_EQ(fila->tamanho, 0);
	int numQualquer = 123456;
	enfileirar(&fila, numQualquer);
	EXPECT_EQ(fila->tamanho, 1);
	enfileirar(&fila, numQualquer);
	EXPECT_EQ(fila->tamanho, 2);
	int outroNumQualquer = 7890;
	enfileirar(&fila, outroNumQualquer);
	EXPECT_EQ(fila->tamanho, 3);
	desenfileirar(fila);
	EXPECT_EQ(fila->tamanho, 2);
}

TEST_F(LinkedQueueTest, FrenteFilaVazia) {
	EXPECT_EQ(frente(fila), INT_MIN);
}

TEST_F(LinkedQueueTest, FrenteFilaNaoVazia) {
	int numQualquer = 123456;
	enfileirar(&fila, numQualquer);
	EXPECT_EQ(frente(fila), numQualquer);
}