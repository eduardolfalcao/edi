#include "pch.h"
#include "../src/avl/bibliotecas/avl2.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
using namespace std;


class AvlTest : public ::testing::Test {
protected:

	void freeRecursively(struct noBstAvl* raiz) {
		if (raiz != NULL) {
			freeRecursively(raiz->esq);
			freeRecursively(raiz->dir);
			free(raiz);
		}
	}

	virtual void TearDown() {
		freeRecursively(avl->raiz);
	}

	virtual void SetUp() {
		avl = alocarAvl();
	}

	struct avl* avl = NULL;
};

//arvore descompensada à esquerda
void arvDescompensadaEsq(struct avl* avl) {
	inserir(avl, 4);
	inserir(avl, 2);
	inserir(avl, 5);
	inserir(avl, 1);
	inserir(avl, 3);
	//          4(D)
	// 	       /    \
	//      2(B)     5(E)
	//     /    \
	//   1(A)   3(C)
}

//arvore descompensada à esquerda
void arvDescompensadaDir(struct avl* avl) {
	inserir(avl, 2);
	inserir(avl, 1);
	inserir(avl, 4);
	inserir(avl, 3);
	inserir(avl, 5);
	//          2(B)
	// 	       /    \
	//      1(A)    4(D)
	//              /    \
	//            3(C)   5(E)
}

TEST_F(AvlTest, RotacaoDireita) {
	arvDescompensadaEsq(avl);
	EXPECT_EQ(avl->tam, 5);
	EXPECT_EQ(avl->raiz->val, 4);
	EXPECT_EQ(avl->raiz->balanco, -1);

	avl->raiz = rotacaoDireita(avl->raiz);

	EXPECT_EQ(avl->tam, 5);
	EXPECT_EQ(avl->raiz->val, 2);
	EXPECT_EQ(avl->raiz->balanco, 1);
}

TEST_F(AvlTest, RotacaoEsquerda) {
	arvDescompensadaDir(avl);
	EXPECT_EQ(avl->tam, 5);
	EXPECT_EQ(avl->raiz->val, 2);
	EXPECT_EQ(avl->raiz->balanco, 1);

	avl->raiz = rotacaoEsquerda(avl->raiz);

	EXPECT_EQ(avl->tam, 5);
	EXPECT_EQ(avl->raiz->val, 4);
	EXPECT_EQ(avl->raiz->balanco, -1);
}

//verifico o BF de todos os nos da arvore avl
void verificarBF(struct noBstAvl* raiz) {
	if (raiz != NULL) {
		EXPECT_TRUE(raiz->balanco >= -1 && raiz->balanco <= 1);
		verificarBF(raiz->esq);
		verificarBF(raiz->dir);
	}
}

TEST_F(AvlTest, InsercaoValoresCrescentes) {
	for (int i = 0; i <= 100; i++) {
		inserir(avl, i);
		verificarBF(avl->raiz);
	}
}

TEST_F(AvlTest, InsercaoValoresDecrescentes) {
	for (int i = 100; i >= 0; i--) {
		inserir(avl, i);
		EXPECT_TRUE(avl->raiz->balanco >= -1 && avl->raiz->balanco <= 1);
	}
}

TEST_F(AvlTest, RemocaoValoresAleatorios) {
	for (int i = 0; i < 1000; i++)
		inserir(avl, i);

	for (int i = 0; i < 100; i++) {
		int val = rand() % 100;
		remover(avl, val);	
		verificarBF(avl->raiz);
	}
}
