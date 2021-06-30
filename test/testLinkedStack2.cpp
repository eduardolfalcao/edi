//Para Windows (MS Visual Studio):
#include "pch.h"

//Para Linux:
//#include <gtest/gtest.h>

#include "../src/pilhas/bibliotecas/linkedstack2.h"

class LinkedListStackTest2 : public ::testing::Test {
protected:
	virtual void TearDown() {
		while (topo(pilha) != INT_MIN)
			desempilhar(pilha);

		if (pilha != NULL) {
			free(pilha);
			pilha = NULL;
		}
	}

	virtual void SetUp() {
		pilha = inicializar();
	}

	struct linkedstack* pilha;
};

TEST_F(LinkedListStackTest2, EmpilhamentoPilhaNula) {
	TearDown();

	int numQualquer = 123456;
	empilhar(&pilha, numQualquer);
	EXPECT_EQ(pilha->qtdade, 1);
	EXPECT_EQ(topo(pilha), numQualquer);
}

TEST_F(LinkedListStackTest2, EmpilhamentoPilhaVazia) {
	int numQualquer = 123456;
	empilhar(&pilha, numQualquer);
	EXPECT_EQ(pilha->qtdade, 1);
	EXPECT_EQ(topo(pilha), numQualquer);
}

TEST_F(LinkedListStackTest2, EmpilhamentoPilhaNaoVazia) {
	int numQualquer = 123456;
	empilhar(&pilha, numQualquer);
	EXPECT_EQ(topo(pilha), numQualquer);
	int outroNumQualquer = 7890;
	empilhar(&pilha, outroNumQualquer);
	EXPECT_EQ(pilha->qtdade, 2);
	EXPECT_EQ(topo(pilha), outroNumQualquer);
	//pra certificar que topo() nao remove da pilha
	EXPECT_EQ(topo(pilha), outroNumQualquer);
}

TEST_F(LinkedListStackTest2, DesempilhamentoPilhaNula) {
	TearDown();

	EXPECT_EQ(desempilharRetornando(pilha), INT_MIN);
}

TEST_F(LinkedListStackTest2, DesempilhamentoPilhaVazia) {
	desempilhar(pilha);
	EXPECT_EQ(pilha->qtdade, 0);
	EXPECT_EQ(desempilharRetornando(pilha), INT_MIN);
}

TEST_F(LinkedListStackTest2, DesempilhamentoPilhaNaoVazia) {
	int numQualquer = 123456;
	empilhar(&pilha, numQualquer);
	int outroNumQualquer = 7890;
	empilhar(&pilha, outroNumQualquer);
	desempilhar(pilha);
	EXPECT_EQ(pilha->qtdade, 1);
	EXPECT_EQ(desempilharRetornando(pilha), numQualquer);
}

TEST_F(LinkedListStackTest2, TopoPilhaNula) {
	TearDown();

	EXPECT_EQ(topo(pilha), INT_MIN);
}

TEST_F(LinkedListStackTest2, TopoPilhaVazia) {
	EXPECT_EQ(topo(pilha), INT_MIN);
}

TEST_F(LinkedListStackTest2, TopoPilhaNaoVazia) {
	int numQualquer = 123456;
	empilhar(&pilha, numQualquer);
	EXPECT_EQ(topo(pilha), numQualquer);
	int outroNumQualquer = 7890;
	empilhar(&pilha, outroNumQualquer);
	EXPECT_EQ(topo(pilha), outroNumQualquer);
}

TEST_F(LinkedListStackTest2, FuncVazioPilhaNula) {
	TearDown();

	EXPECT_TRUE(vazia(pilha));
}

TEST_F(LinkedListStackTest2, FuncVazioPilhaVazia) {
	EXPECT_TRUE(vazia(pilha));
}

TEST_F(LinkedListStackTest2, FuncVazioPilhaNaoVazia) {
	int numQualquer = 123456;
	empilhar(&pilha, numQualquer);
	EXPECT_FALSE(vazia(pilha));
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}