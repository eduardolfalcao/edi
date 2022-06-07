#include "pch.h"
#include "../src/bst/bibliotecas/bst2.h"

class BstTest2 : public ::testing::Test {
protected:

	void freeRecursively(struct noBst* raiz) {
		if (raiz != NULL) {
			freeRecursively(raiz->esq);
			freeRecursively(raiz->dir);
			free(raiz);
		}
	}

	virtual void TearDown() {
		freeRecursively(bst->raiz);
	}

	virtual void SetUp() {
		bst = alocarBst();
	}


	struct bst* bst = NULL;
};

TEST_F(BstTest2, InsercaoRecBSTVazia) {
	bool rec = true;
	EXPECT_EQ(bst->tam, 0);
	inserir(bst, 10, rec);
	EXPECT_EQ(bst->tam, 1);
}

TEST_F(BstTest2, InsercaoItBSTVazia) {
	bool rec = false;
	EXPECT_EQ(bst->tam, 0);
	inserir(bst, 10, rec);
	EXPECT_EQ(bst->tam, 1);
}

TEST_F(BstTest2, InsercaoRecBSTNaoVazia) {
	bool rec = true;
	inserir(bst, 10, rec);
	inserir(bst, 5, rec);
	inserir(bst, 15, rec);
	inserir(bst, 20, rec);
	EXPECT_EQ(bst->tam, 4);
}

TEST_F(BstTest2, InsercaoItBSTNaoVazia) {
	bool rec = false;
	inserir(bst, 10, rec);
	inserir(bst, 5, rec);
	inserir(bst, 15, rec);
	inserir(bst, 20, rec);
	EXPECT_EQ(bst->tam, 4);
}

TEST_F(BstTest2, BuscaBSTVaziaRec) {
	bool rec = true;
	int umValorQualquer = 123;
	EXPECT_FALSE(buscar(bst, umValorQualquer, rec));
}

TEST_F(BstTest2, BuscaBSTNaoVaziaRec) {
	bool rec = true;
	inserir(bst, 10, rec);
	inserir(bst, 5, rec);
	inserir(bst, 15, rec);
	inserir(bst, 20, rec);
	EXPECT_TRUE(buscar(bst, 5, rec));
	EXPECT_TRUE(buscar(bst, 10, rec));
	EXPECT_TRUE(buscar(bst, 15, rec));
	EXPECT_TRUE(buscar(bst, 20, rec));
	int umValorQualquer = 123;
	EXPECT_FALSE(buscar(bst, umValorQualquer, rec));
}

TEST_F(BstTest2, BuscaBSTVaziaIt) {
	bool rec = false;
	int umValorQualquer = 123;
	EXPECT_FALSE(buscar(bst, umValorQualquer, rec));
}

TEST_F(BstTest2, BuscaBSTNaoVaziaIt) {
	bool rec = false;
	inserir(bst, 10, rec);
	inserir(bst, 5, rec);
	inserir(bst, 15, rec);
	inserir(bst, 20, rec);
	EXPECT_TRUE(buscar(bst, 5, rec));
	EXPECT_TRUE(buscar(bst, 10, rec));
	EXPECT_TRUE(buscar(bst, 15, rec));
	EXPECT_TRUE(buscar(bst, 20, rec));
	int umValorQualquer = 123;
	EXPECT_FALSE(buscar(bst, umValorQualquer, rec));
}

TEST_F(BstTest2, BuscaEmOrdem) {
	bool rec = false;
	inserir(bst, 8, rec);
	inserir(bst, 5, rec);
	inserir(bst, 3, rec);
	inserir(bst, 6, rec);
	inserir(bst, 15, rec);
	inserir(bst, 10, rec);
	inserir(bst, 20, rec);
	std::cout << "Em ordem: ";
	navEmOrdem(bst->raiz);
	std::cout << std::endl;
}

TEST_F(BstTest2, BuscaPreOrdem) {
	bool rec = false;
	inserir(bst, 8, rec);
	inserir(bst, 5, rec);
	inserir(bst, 3, rec);
	inserir(bst, 6, rec);
	inserir(bst, 15, rec);
	inserir(bst, 10, rec);
	inserir(bst, 20, rec);
	std::cout << "pre ordem: ";
	navPreOrdem(bst->raiz);
	std::cout << std::endl;
}

TEST_F(BstTest2, BuscaPosOrdem) {
	bool rec = false;
	inserir(bst, 8, rec);
	inserir(bst, 5, rec);
	inserir(bst, 3, rec);
	inserir(bst, 6, rec);
	inserir(bst, 15, rec);
	inserir(bst, 10, rec);
	inserir(bst, 20, rec);
	std::cout << "pos ordem: ";
	navPosOrdem(bst->raiz);
	std::cout << std::endl;
}

TEST_F(BstTest2, MinBST) {
	EXPECT_EQ(min(bst->raiz), NULL);

	inserir(bst, 10, true);
	inserir(bst, 5, true);
	inserir(bst, 15, true);
	inserir(bst, 20, true);
	EXPECT_EQ(min(bst->raiz), 5);

	inserir(bst, -10, true);
	EXPECT_EQ(min(bst->raiz), -10);
}

TEST_F(BstTest2, MaxBST) {
	EXPECT_EQ(max(bst->raiz), NULL);

	inserir(bst, 10, true);
	inserir(bst, 5, true);
	inserir(bst, 15, true);
	inserir(bst, 20, true);
	EXPECT_EQ(max(bst->raiz), 20);

	inserir(bst, 100, true);
	EXPECT_EQ(max(bst->raiz), 100);
}

TEST_F(BstTest2, AlturaBST) {
	EXPECT_EQ(altura(bst->raiz), 0);

	inserir(bst, 10, true);
	EXPECT_EQ(altura(bst->raiz), 0);
	inserir(bst, 5, true);
	EXPECT_EQ(altura(bst->raiz), 1);
	inserir(bst, 15, true);
	EXPECT_EQ(altura(bst->raiz), 1);
	inserir(bst, 20, true);
	EXPECT_EQ(altura(bst->raiz), 2);
	inserir(bst, 100, true);
	EXPECT_EQ(altura(bst->raiz), 3);
}

TEST_F(BstTest2, Remover) {
	inserir(bst, 12, true);
	inserir(bst, 4, true);
	inserir(bst, 2, true);
	inserir(bst, 7, true);
	inserir(bst, 1, true);
	inserir(bst, 3, true);
	inserir(bst, 8, true);
	inserir(bst, 18, true);
	inserir(bst, 14, true);
	inserir(bst, 21, true);
	inserir(bst, 13, true);
	inserir(bst, 15, true);
	inserir(bst, 16, true);
	EXPECT_EQ(bst->tam, 13);

	//1, 2, 3, 4, 7, 8, 12, 13, 14, 15, 16, 18, 21 
	EXPECT_TRUE(buscar(bst, 12,true)); 
	remover(bst, 12);					//removendo no com 2 filhos: caso 3
	EXPECT_EQ(bst->tam, 12);
	EXPECT_TRUE(buscar(bst, 1, true));
	EXPECT_TRUE(buscar(bst, 2, true));
	EXPECT_TRUE(buscar(bst, 3, true));
	EXPECT_TRUE(buscar(bst, 4, true));
	EXPECT_TRUE(buscar(bst, 7, true));
	EXPECT_TRUE(buscar(bst, 8, true));
	EXPECT_FALSE(buscar(bst, 12, true));
	EXPECT_TRUE(buscar(bst, 13, true));
	EXPECT_TRUE(buscar(bst, 14, true));
	EXPECT_TRUE(buscar(bst, 15, true));
	EXPECT_TRUE(buscar(bst, 16, true));
	EXPECT_TRUE(buscar(bst, 18, true));
	EXPECT_TRUE(buscar(bst, 21, true));
	

	//1, 2, 3, 4, 7, 8, 12, 13, 14, 15, 16, 18, 21 
	remover(bst, 1);					//removendo no folha: caso 1
	EXPECT_EQ(bst->tam, 11);
	EXPECT_FALSE(buscar(bst, 1, true));
	EXPECT_TRUE(buscar(bst, 2, true));
	EXPECT_TRUE(buscar(bst, 3, true));
	EXPECT_TRUE(buscar(bst, 4, true));
	EXPECT_TRUE(buscar(bst, 7, true));
	EXPECT_TRUE(buscar(bst, 8, true));
	EXPECT_FALSE(buscar(bst, 12, true));
	EXPECT_TRUE(buscar(bst, 13, true));
	EXPECT_TRUE(buscar(bst, 14, true));
	EXPECT_TRUE(buscar(bst, 15, true));
	EXPECT_TRUE(buscar(bst, 16, true));
	EXPECT_TRUE(buscar(bst, 18, true));
	EXPECT_TRUE(buscar(bst, 21, true));

	//1, 2, 3, 4, 7, 8, 12, 13, 14, 15, 16, 18, 21 ]
	remover(bst, 15);				//removendo nó com apenas 1 filho (caso 2)
	EXPECT_EQ(bst->tam, 10);
	EXPECT_FALSE(buscar(bst, 1, true));
	EXPECT_TRUE(buscar(bst, 2, true));
	EXPECT_TRUE(buscar(bst, 3, true));
	EXPECT_TRUE(buscar(bst, 4, true));
	EXPECT_TRUE(buscar(bst, 7, true));
	EXPECT_TRUE(buscar(bst, 8, true));
	EXPECT_FALSE(buscar(bst, 12, true));
	EXPECT_TRUE(buscar(bst, 13, true));
	EXPECT_TRUE(buscar(bst, 14, true));
	EXPECT_FALSE(buscar(bst, 15, true));
	EXPECT_TRUE(buscar(bst, 16, true));
	EXPECT_TRUE(buscar(bst, 18, true));
	EXPECT_TRUE(buscar(bst, 21, true));
}