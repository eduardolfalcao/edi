#include "pch.h"
#include "../src/avl/bibliotecas/avl.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
using namespace std;


class AvlTest : public ::testing::Test {
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

//arvore descompensada à esquerda
void arvDescompensadaEsq(struct noBst** raiz, int * tamanho) {
	inserir(raiz, 4, tamanho);
	inserir(raiz, 2, tamanho);
	inserir(raiz, 5, tamanho);
	inserir(raiz, 1, tamanho);
	inserir(raiz, 3, tamanho);
	//          4(D)
	// 	       /    \
	//      2(B)     5(E)
	//     /    \
	//   1(A)   3(C)
}

//arvore descompensada à esquerda
void arvDescompensadaDir(struct noBst** raiz, int* tamanho) {
	inserir(raiz, 2, tamanho);
	inserir(raiz, 1, tamanho);
	inserir(raiz, 4, tamanho);
	inserir(raiz, 3, tamanho);
	inserir(raiz, 5, tamanho);
	//          2(B)
	// 	       /    \
	//      1(A)    4(D)
	//              /    \
	//            3(C)   5(E)
}

TEST_F(AvlTest, RotacaoDireita) {
	arvDescompensadaEsq(&raiz, &tamanho);
	EXPECT_EQ(tamanho, 5);
	EXPECT_EQ(raiz->val, 4);
	EXPECT_EQ(raiz->balanco, -1);

	raiz = rotacaoDireita(raiz);

	EXPECT_EQ(tamanho, 5);
	EXPECT_EQ(raiz->val, 2);
	EXPECT_EQ(raiz->balanco, 1);
}

TEST_F(AvlTest, RotacaoEsquerda) {
	arvDescompensadaDir(&raiz, &tamanho);
	EXPECT_EQ(tamanho, 5);
	EXPECT_EQ(raiz->val, 2);
	EXPECT_EQ(raiz->balanco, 1);

	raiz = rotacaoEsquerda(raiz);

	EXPECT_EQ(tamanho, 5);
	EXPECT_EQ(raiz->val, 4);
	EXPECT_EQ(raiz->balanco, -1);
}

TEST_F(AvlTest, InsercaoValoresCrescentes) {
	for (int i = 0; i <= 100; i++) {
		inserir(&raiz, i, &tamanho);
		EXPECT_TRUE(raiz->balanco>=-1 && raiz->balanco<=1);
	}
}

TEST_F(AvlTest, InsercaoValoresDecrescentes) {
	for (int i = 100; i >= 0; i--) {
		inserir(&raiz, i, &tamanho);
		EXPECT_TRUE(raiz->balanco >= -1 && raiz->balanco <= 1);
	}
}

TEST_F(AvlTest, RemocaoValoresAleatorios) {
	for (int i = 0; i < 1000; i++)
		inserir(&raiz, i, &tamanho);

	for (int i = 0; i < 100; i++) {
		int val = rand() % 100;
		raiz = remover(raiz, val, &tamanho);	
		EXPECT_TRUE(raiz->balanco >= -1 && raiz->balanco <= 1);
	}
}
