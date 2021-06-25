#include "pch.h"
#include "../src/bst/bibliotecas/bst-alunos.h"
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

/*TEST_F(BstTest, MinBST) {
	EXPECT_EQ(min(raiz), NULL);

	inserir(&raiz, 10, &tamanho);
	inserir(&raiz, 5, &tamanho);
	inserir(&raiz, 15, &tamanho);
	inserir(&raiz, 20, &tamanho);
	EXPECT_EQ(min(raiz), 5);

	inserir(&raiz, -10, &tamanho);
	EXPECT_EQ(min(raiz), -10);
}

TEST_F(BstTest, MaxBST) {
	EXPECT_EQ(max(raiz), NULL);

	inserir(&raiz, 10, &tamanho);
	inserir(&raiz, 5, &tamanho);
	inserir(&raiz, 15, &tamanho);
	inserir(&raiz, 20, &tamanho);
	EXPECT_EQ(max(raiz), 20);

	inserir(&raiz, 100, &tamanho);
	EXPECT_EQ(max(raiz), 100);
}*/

TEST_F(BstTest, AlturaBST) {
	EXPECT_EQ(altura(raiz), 0);

	inserir(&raiz, 10, &tamanho);
	EXPECT_EQ(altura(raiz), 0);
	inserir(&raiz, 5, &tamanho);
	EXPECT_EQ(altura(raiz), 1);
	inserir(&raiz, 15, &tamanho);
	EXPECT_EQ(altura(raiz), 1);
	inserir(&raiz, 20, &tamanho);
	EXPECT_EQ(altura(raiz), 2);
	inserir(&raiz, 100, &tamanho);
	EXPECT_EQ(altura(raiz), 3);
}

TEST_F(BstTest, EmOrdem) {
	inserir(&raiz, 12, &tamanho);
	inserir(&raiz, 4, &tamanho);
	inserir(&raiz, 2, &tamanho);
	inserir(&raiz, 7, &tamanho);
	inserir(&raiz, 1, &tamanho);
	inserir(&raiz, 3, &tamanho);
	inserir(&raiz, 8, &tamanho);
	inserir(&raiz, 18, &tamanho);
	inserir(&raiz, 14, &tamanho);
	inserir(&raiz, 21, &tamanho);
	inserir(&raiz, 13, &tamanho);
	inserir(&raiz, 15, &tamanho);
	inserir(&raiz, 16, &tamanho);
	printf("Em ordem: ");
	emOrdem(raiz);
	//aqui não temos teste, vou inspecionar olhando o print
	//deveria ser: 1, 2, 3, 4, 7, 8, 12, 13, 14, 15, 16, 18, 21 
}

TEST_F(BstTest, PreOrdem) {
	inserir(&raiz, 12, &tamanho);
	inserir(&raiz, 4, &tamanho);
	inserir(&raiz, 2, &tamanho);
	inserir(&raiz, 7, &tamanho);
	inserir(&raiz, 1, &tamanho);
	inserir(&raiz, 3, &tamanho);
	inserir(&raiz, 8, &tamanho);
	inserir(&raiz, 18, &tamanho);
	inserir(&raiz, 14, &tamanho);
	inserir(&raiz, 21, &tamanho);
	inserir(&raiz, 13, &tamanho);
	inserir(&raiz, 15, &tamanho);
	inserir(&raiz, 16, &tamanho);
	printf("Pre-ordem: ");
	preOrdem(raiz);
	//aqui não temos teste, vou inspecionar olhando o print
	//deveria ser: 12, 4, 2, 1, 3, 7, 8, 18, 14, 13, 15, 16, 21
}

TEST_F(BstTest, PosOrdem) {
	inserir(&raiz, 12, &tamanho);
	inserir(&raiz, 4, &tamanho);
	inserir(&raiz, 2, &tamanho);
	inserir(&raiz, 7, &tamanho);
	inserir(&raiz, 1, &tamanho);
	inserir(&raiz, 3, &tamanho);
	inserir(&raiz, 8, &tamanho);
	inserir(&raiz, 18, &tamanho);
	inserir(&raiz, 14, &tamanho);
	inserir(&raiz, 21, &tamanho);
	inserir(&raiz, 13, &tamanho);
	inserir(&raiz, 15, &tamanho);
	inserir(&raiz, 16, &tamanho);
	printf("Pos-ordem: ");
	posOrdem(raiz);
	//aqui não temos teste, vou inspecionar olhando o print
	//deveria ser: 1, 3, 2, 8, 7, 4, 13, 16, 15, 14, 21, 18, 12
}

TEST_F(BstTest, Remover) {
	inserir(&raiz, 12, &tamanho);
	inserir(&raiz, 4, &tamanho);
	inserir(&raiz, 2, &tamanho);
	inserir(&raiz, 7, &tamanho);
	inserir(&raiz, 1, &tamanho);
	inserir(&raiz, 3, &tamanho);
	inserir(&raiz, 8, &tamanho);
	inserir(&raiz, 18, &tamanho);
	inserir(&raiz, 14, &tamanho);
	inserir(&raiz, 21, &tamanho);
	inserir(&raiz, 13, &tamanho);
	inserir(&raiz, 15, &tamanho);
	inserir(&raiz, 16, &tamanho);

	//1, 2, 3, 4, 7, 8, 12, 13, 14, 15, 16, 18, 21 
	EXPECT_TRUE(buscar(raiz, 12)); //removendo no com 2 filhos: caso 3
	remover(raiz, 12, &tamanho);
	EXPECT_TRUE(buscar(raiz, 1));
	EXPECT_TRUE(buscar(raiz, 2));
	EXPECT_TRUE(buscar(raiz, 3));
	EXPECT_TRUE(buscar(raiz, 4));
	EXPECT_TRUE(buscar(raiz, 7));
	EXPECT_TRUE(buscar(raiz, 8));
	EXPECT_FALSE(buscar(raiz, 12));
	EXPECT_TRUE(buscar(raiz, 13));
	EXPECT_TRUE(buscar(raiz, 14));
	EXPECT_TRUE(buscar(raiz, 15));
	EXPECT_TRUE(buscar(raiz, 16));
	EXPECT_TRUE(buscar(raiz, 18));
	EXPECT_TRUE(buscar(raiz, 21));

	//1, 2, 3, 4, 7, 8, 12, 13, 14, 15, 16, 18, 21 
	remover(raiz, 1, &tamanho);	//removendo no folha: caso 1
	EXPECT_FALSE(buscar(raiz, 1));
	EXPECT_TRUE(buscar(raiz, 2));
	EXPECT_TRUE(buscar(raiz, 3));
	EXPECT_TRUE(buscar(raiz, 4));
	EXPECT_TRUE(buscar(raiz, 7));
	EXPECT_TRUE(buscar(raiz, 8));
	EXPECT_FALSE(buscar(raiz, 12));
	EXPECT_TRUE(buscar(raiz, 13));
	EXPECT_TRUE(buscar(raiz, 14));
	EXPECT_TRUE(buscar(raiz, 15));
	EXPECT_TRUE(buscar(raiz, 16));
	EXPECT_TRUE(buscar(raiz, 18));
	EXPECT_TRUE(buscar(raiz, 21));

	//1, 2, 3, 4, 7, 8, 12, 13, 14, 15, 16, 18, 21 
	remover(raiz, 15, &tamanho);	//removendo nó com apenas 1 filho (caso 2)
	EXPECT_FALSE(buscar(raiz, 1));
	EXPECT_TRUE(buscar(raiz, 2));
	EXPECT_TRUE(buscar(raiz, 3));
	EXPECT_TRUE(buscar(raiz, 4));
	EXPECT_TRUE(buscar(raiz, 7));
	EXPECT_TRUE(buscar(raiz, 8));
	EXPECT_FALSE(buscar(raiz, 12));
	EXPECT_TRUE(buscar(raiz, 13));
	EXPECT_TRUE(buscar(raiz, 14));
	EXPECT_FALSE(buscar(raiz, 15));
	EXPECT_TRUE(buscar(raiz, 16));
	EXPECT_TRUE(buscar(raiz, 18));
	EXPECT_TRUE(buscar(raiz, 21));
}