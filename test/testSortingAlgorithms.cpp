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
	int tamanho = 10;
	int nTestes = 1;
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

/*TEST_F(SortingAlgorithmsTest, SelectionSortOP) {	
	for (int i = 0; i < nTestes; i++) {
		SetUp();
		selectionSortTestInstance(v, tamanho, false);
		if(i != nTestes-1)	//evita executar free 2x no ultimo teste
			TearDown();
	}
}

TEST_F(SortingAlgorithmsTest, SelectionSortIP) {
	for (int i = 0; i < nTestes; i++) {
		SetUp();
		selectionSortTestInstance(v, tamanho, true);
		if (i != nTestes - 1)	//evita executar free 2x no ultimo teste
			TearDown();
	}
}

TEST_F(SortingAlgorithmsTest, BubbleSort) {
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
	for (int i = 0; i < nTestes; i++) {
		SetUp();
		insertionSortIPV5(v, tamanho);
		for (int i = 0; i < tamanho - 1; i++) {
			EXPECT_TRUE(v[i] <= v[i + 1]);
		}
		if (i != nTestes - 1)	//evita executar free 2x no ultimo teste
			TearDown();
	}
}*/

TEST_F(SortingAlgorithmsTest, MergeSort) {
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

TEST_F(SortingAlgorithmsTest, QuickSort) {
	for (int i = 0; i < nTestes; i++) {
		SetUp();
		quickSort(v, 0, tamanho-1);
		for (int i = 0; i < tamanho - 1; i++) {
			EXPECT_TRUE(v[i] <= v[i + 1]);
		}
		if (i != nTestes - 1)	//evita executar free 2x no ultimo teste
			TearDown();
	}
}

TEST_F(SortingAlgorithmsTest, CountingSort) {
	for (int i = 0; i < nTestes; i++) {
		SetUp();
		countingSort(&v, tamanho);
		for (int i = 0; i < tamanho - 1; i++) {
			EXPECT_TRUE(v[i] <= v[i + 1]);
		}
		if (i != nTestes - 1)	//evita executar free 2x no ultimo teste
			TearDown();
	}
}