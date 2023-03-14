#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//retorna indice
int busca(int* v, int n, int val) {
    for (int i = 0; i < n; i++) {
        if (v[i] == val)
            return i;
    }
    return -1;
}

bool contem(int* v, int n, int val) {
    for (int i = 0; i < n; i++) {
        if (v[i] == val)
            return true;
    }
    return false;
}

