#include "pch.h"
#include "../src/bst/bibliotecas/bst.h"
#include <math.h>


class BstTest : public ::testing::Test {
protected:

	void freeRecursively(struct noBst* raiz) {
		if (raiz != NULL) {
			freeRecursively(raiz->esq);
			freeRecursively(raiz->dir);
			free(raiz);
		}
	}

	virtual void TearDown() {
		freeRecursively(raiz);
	}

	int tamanho = 0;
	struct noBst* raiz = NULL;
};

TEST_F(BstTest, InsercaoBSTVazia) {
	EXPECT_EQ(tamanho, 0);
	inserir(&raiz, 10, &tamanho);
	EXPECT_EQ(tamanho, 1);
}

TEST_F(BstTest, InsercaoBSTNaoVazia) {
	inserir(&raiz, 10, &tamanho);
	inserir(&raiz, 5, &tamanho);
	inserir(&raiz, 15, &tamanho);
	inserir(&raiz, 20, &tamanho);
	EXPECT_EQ(tamanho, 4);
}

TEST_F(BstTest, BuscaBSTVazia) {
	int umValorQualquer = 123;
	EXPECT_FALSE(buscar(raiz, umValorQualquer));
}

TEST_F(BstTest, BuscaBSTNaoVazia) {
	inserir(&raiz, 10, &tamanho);
	inserir(&raiz, 5, &tamanho);
	inserir(&raiz, 15, &tamanho);
	inserir(&raiz, 20, &tamanho);
	EXPECT_TRUE(buscar(raiz, 5));
	EXPECT_TRUE(buscar(raiz, 10));
	EXPECT_TRUE(buscar(raiz, 15));
	EXPECT_TRUE(buscar(raiz, 20));
	int umValorQualquer = 123;
	EXPECT_FALSE(buscar(raiz, umValorQualquer));
}