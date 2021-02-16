#include "pch.h"
#include "../src/pilhas/bibliotecas/linkedliststack.h"

class LinkedListStackTest : public ::testing::Test {
protected:
	virtual void TearDown() {
		while (topo(pilha) != INT_MIN) 
			desempilhar(&pilha, &tamanho);
		
		tamanho = 0;
		pilha = NULL;
	}

	int tamanho = 0;
	struct no* pilha = NULL;
};

TEST_F(LinkedListStackTest, EmpilhamentoPilhaVazia) {
	int numQualquer = 123456;
	empilhar(&pilha, numQualquer, &tamanho);
	EXPECT_EQ(tamanho, 1);
	EXPECT_EQ(topo(pilha), numQualquer);
}

TEST_F(LinkedListStackTest, EmpilhamentoPilhaNaoVazia) {
	int numQualquer = 123456;
	empilhar(&pilha, numQualquer, &tamanho);
	EXPECT_EQ(topo(pilha), numQualquer);
	EXPECT_EQ(topo(pilha), numQualquer);
	int outroNumQualquer = 7890;
	empilhar(&pilha, outroNumQualquer, &tamanho);
	EXPECT_EQ(tamanho, 2);
	EXPECT_EQ(topo(pilha), outroNumQualquer);
	EXPECT_EQ(topo(pilha), outroNumQualquer);
}

TEST_F(LinkedListStackTest, DesempilhamentoPilhaVazia) {
	desempilhar(&pilha,&tamanho);
	EXPECT_EQ(tamanho, 0);
	EXPECT_EQ(desempilharRetornando(&pilha, &tamanho), INT_MIN);
}

TEST_F(LinkedListStackTest, DesempilhamentoPilhaNaoVazia) {
	int numQualquer = 123456;
	empilhar(&pilha, numQualquer, &tamanho);
	int outroNumQualquer = 7890;
	empilhar(&pilha, outroNumQualquer, &tamanho);
	desempilhar(&pilha,&tamanho);
	EXPECT_EQ(tamanho, 1);
	EXPECT_EQ(desempilharRetornando(&pilha, &tamanho), numQualquer);
}

TEST_F(LinkedListStackTest, TopoPilhaVazia) {
	EXPECT_EQ(topo(pilha), INT_MIN);
}

TEST_F(LinkedListStackTest, TopoPilhaNaoVazia) {
	int numQualquer = 123456;
	empilhar(&pilha, numQualquer, &tamanho);
	EXPECT_EQ(topo(pilha), numQualquer);
	int outroNumQualquer = 7890;
	empilhar(&pilha, outroNumQualquer, &tamanho);
	EXPECT_EQ(topo(pilha), outroNumQualquer);
}

TEST_F(LinkedListStackTest, VazioPilhaVazia) {
	EXPECT_TRUE(vazio(pilha));
}

TEST_F(LinkedListStackTest, VazioPilhaNaoVazia) {
	int numQualquer = 123456;
	empilhar(&pilha, numQualquer, &tamanho);
	EXPECT_FALSE(vazio(pilha));
}