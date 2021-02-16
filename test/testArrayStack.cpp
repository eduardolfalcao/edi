#include "pch.h"
#include "../src/pilhas/bibliotecas/arraystack.h"

class ArrayStackTest : public ::testing::Test {
protected:
	virtual void TearDown() {
		tamanho = 0;
		pilha = NULL;
		capacidade = 0;
	}

	virtual void SetUp() {
		capacidade = 5;
		inicializar(&pilha, capacidade);
	}

	int tamanho = 0;
	int capacidade = 0;
	int* pilha = NULL;
};

TEST_F(ArrayStackTest, EmpilhamentoPilhaVazia) {
	int numQualquer = 123456;
	empilhar(&pilha, numQualquer, &tamanho, &capacidade);
	EXPECT_EQ(tamanho, 1);
	EXPECT_EQ(topo(pilha,tamanho), numQualquer);
}

TEST_F(ArrayStackTest, EmpilhamentoPilhaNaoVazia) {
	int numQualquer = 123456;
	empilhar(&pilha, numQualquer, &tamanho, &capacidade);
	int outroNumQualquer = 7890;
	empilhar(&pilha, outroNumQualquer, &tamanho, &capacidade);
	EXPECT_EQ(tamanho, 2);
	EXPECT_EQ(topo(pilha, tamanho), outroNumQualquer);
}

TEST_F(ArrayStackTest, EmpilhamentoDobrandoCapacidade) {
	int numInsercoes = 2 * capacidade;
	for (int i = 0; i < numInsercoes; i++) {
		empilhar(&pilha, i, &tamanho, &capacidade);
	}
	EXPECT_EQ(tamanho, numInsercoes);
	EXPECT_EQ(topo(pilha, tamanho), numInsercoes - 1);
}

TEST_F(ArrayStackTest, DesempilhamentoPilhaVazia) {
	desempilhar(&tamanho);
	EXPECT_EQ(tamanho, 0);
	EXPECT_EQ(desempilharRetornando(pilha, &tamanho), INT_MIN);
}

TEST_F(ArrayStackTest, DesempilhamentoPilhaNaoVazia) {
	int numQualquer = 123456;
	empilhar(&pilha, numQualquer, &tamanho, &capacidade);
	int outroNumQualquer = 7890;
	empilhar(&pilha, outroNumQualquer, &tamanho, &capacidade);
	desempilhar(&tamanho);
	EXPECT_EQ(tamanho, 1);
	EXPECT_EQ(desempilharRetornando(pilha, &tamanho), numQualquer);
}

TEST_F(ArrayStackTest, TopoPilhaVazia) {
	EXPECT_EQ(topo(pilha, tamanho), INT_MIN);
}

TEST_F(ArrayStackTest, TopoPilhaNaoVazia) {
	int numQualquer = 123456;
	empilhar(&pilha, numQualquer, &tamanho, &capacidade);
	EXPECT_EQ(topo(pilha, tamanho), numQualquer);
	int outroNumQualquer = 7890;
	empilhar(&pilha, outroNumQualquer, &tamanho, &capacidade);
	EXPECT_EQ(topo(pilha, tamanho), outroNumQualquer);
}

TEST_F(ArrayStackTest, VazioPilhaVazia) {
	EXPECT_TRUE(vazio(tamanho));
}

TEST_F(ArrayStackTest, VazioPilhaNaoVazia) {
	int numQualquer = 123456;
	empilhar(&pilha, numQualquer, &tamanho, &capacidade);
	EXPECT_FALSE(vazio(tamanho));
}