#include "pch.h"
#include "../src/ordenacao/sortUtils.h"

class SortingAlgorithmsTest : public ::testing::Test {
protected:
	virtual void TearDown() {
		free(v);
	}

	virtual void SetUp() {
		v = (int*)malloc(tamanho * sizeof(int));
		for (int i = 0; i < tamanho; i++) {
			v[i] = rand() % 1000;
		}
	}

	int* v;
	int tamanho = 100;
};

void selectionSortTestInstance(int* v, int tamanho, bool inPlace) {
	if (inPlace == true) {
		selectionSortIP(v, tamanho);
	}
	else {
		selectionSortOP(&v, tamanho);
	}
	
	//printV(v, tamanho);
	for (int i = 0; i < tamanho - 1; i++) {
		EXPECT_TRUE(v[i] <= v[i + 1]);
	}
}

TEST_F(SortingAlgorithmsTest, SelectionSortOP) {
	int nTestes = 1000;
	for (int i = 0; i < nTestes; i++) {
		SetUp();
		selectionSortTestInstance(v, tamanho, false);
		if(i != nTestes-1)	//evita executar free 2x no ultimo teste
			TearDown();
	}
}

TEST_F(SortingAlgorithmsTest, SelectionSortIP) {
	int nTestes = 1000;
	for (int i = 0; i < nTestes; i++) {
		SetUp();
		selectionSortTestInstance(v, tamanho, true);
		if (i != nTestes - 1)	//evita executar free 2x no ultimo teste
			TearDown();
	}
}

TEST_F(SortingAlgorithmsTest, BubbleSort) {
	int nTestes = 1000;
	for (int i = 0; i < nTestes; i++) {
		SetUp();
		bubbleSort(v, tamanho);
		for (int i = 0; i < tamanho - 1; i++) {
			EXPECT_TRUE(v[i] <= v[i + 1]);
		}
		if (i != nTestes - 1)	//evita executar free 2x no ultimo teste
			TearDown();
	}
}

TEST_F(SortingAlgorithmsTest, InsertionSortOP) {
	int nTestes = 1000;
	for (int i = 0; i < nTestes; i++) {
		SetUp();
		insertionSortOP(&v, tamanho);	
		for (int i = 0; i < tamanho - 1; i++) {
			EXPECT_TRUE(v[i] <= v[i + 1]);
		}
		if (i != nTestes - 1)	//evita executar free 2x no ultimo teste
			TearDown();
	}
}

TEST_F(SortingAlgorithmsTest, InsertionSortIPV1) {
	int nTestes = 1000;
	for (int i = 0; i < nTestes; i++) {
		SetUp();
		insertionSortIPV1(v, tamanho);
		for (int i = 0; i < tamanho - 1; i++) {
			EXPECT_TRUE(v[i] <= v[i + 1]);
		}
		if (i != nTestes - 1)	//evita executar free 2x no ultimo teste
			TearDown();
	}
}

TEST_F(SortingAlgorithmsTest, InsertionSortIPV2) {
	int nTestes = 1000;
	for (int i = 0; i < nTestes; i++) {
		SetUp();
		insertionSortIPV2(v, tamanho);
		for (int i = 0; i < tamanho - 1; i++) {
			EXPECT_TRUE(v[i] <= v[i + 1]);
		}
		if (i != nTestes - 1)	//evita executar free 2x no ultimo teste
			TearDown();
	}
}

TEST_F(SortingAlgorithmsTest, InsertionSortIPV3) {
	int nTestes = 1000;
	for (int i = 0; i < nTestes; i++) {
		SetUp();
		insertionSortIPV3(v, tamanho);
		for (int i = 0; i < tamanho - 1; i++) {
			EXPECT_TRUE(v[i] <= v[i + 1]);
		}
		if (i != nTestes - 1)	//evita executar free 2x no ultimo teste
			TearDown();
	}
}

TEST_F(SortingAlgorithmsTest, InsertionSortIPV4) {
	int nTestes = 1000;
	for (int i = 0; i < nTestes; i++) {
		SetUp();
		insertionSortIPV4(v, tamanho);
		for (int i = 0; i < tamanho - 1; i++) {
			EXPECT_TRUE(v[i] <= v[i + 1]);
		}
		if (i != nTestes - 1)	//evita executar free 2x no ultimo teste
			TearDown();
	}
}

TEST_F(SortingAlgorithmsTest, InsertionSortIPV5) {
	int nTestes = 1000;
	for (int i = 0; i < nTestes; i++) {
		SetUp();
		insertionSortIPV5(v, tamanho);
		for (int i = 0; i < tamanho - 1; i++) {
			EXPECT_TRUE(v[i] <= v[i + 1]);
		}
		if (i != nTestes - 1)	//evita executar free 2x no ultimo teste
			TearDown();
	}
}

TEST_F(SortingAlgorithmsTest, MergeSort) {
	int nTestes = 1000;
	for (int i = 0; i < nTestes; i++) {
		SetUp();
		mergeSort(v, tamanho);
		for (int i = 0; i < tamanho - 1; i++) {
			EXPECT_TRUE(v[i] <= v[i + 1]);
		}
		if (i != nTestes - 1)	//evita executar free 2x no ultimo teste
			TearDown();
	}
}