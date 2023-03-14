#include <iostream>
#include <istream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int* pilha;
int tamanho = 0;

void inicializar(int capacidade)
{
    pilha = (int*)calloc(capacidade, sizeof(int));

}

void duplicar() {
    pilha = (int*)realloc(pilha, 2 * sizeof(pilha) * sizeof(int));
}

void empilhar(int N) {
    if (tamanho == sizeof(pilha))
        duplicar();

    pilha[tamanho] = N;
    tamanho++;
}

void desempilhar() {
    tamanho--;
}

int desempilharRetornando() {
    desempilhar();
    return pilha[tamanho];

}

int topo() {
    if (tamanho >= 1)
        return pilha[tamanho - 1];

    return  -1;
}

int getTamanho()
{
    return  tamanho;
}

void exibirPilha()
{
    printf("--\n");
    for (int i = tamanho - 1; i >= 0; i--)
        printf("%d\n", pilha[i]);
    printf("--\n");


}

void exibirPilhaNew()
{

    for (int i = tamanho - 1; i >= 0; i--)
        //for(int i=0;i>=tamanho-1;i--)

    {
        if (pilha[i] == 0)
            printf("correct\n");

        else
            printf("incorrect\n");
    }

}

bool vazia() {
    if (tamanho == 0)
        return true;
    else
        return  false;

}



int main() {
    int N, j = 0, cont = 0;
    char texto[1000];

    cout << "Digite o numero de expressoes: ";
    cin >> N;
    inicializar(N);

    for (int i = 0; i < N; i++) {
        cout << "Expressao n.: " << i + 1 << ":";
        cin.ignore();
        cin >> texto;

        while (texto[j] != '\0') {
            if (texto[j] == '(')
                cont++;
            if (texto[j] == ')' && cont == 0)
                cont = -1000;
            if (texto[j] == ')')
                cont--;

            j++;
        }
        if (cont == 0)
            empilhar(0);
        else
            empilhar(1);

        cont = 0;
        j = 0;
    }

    exibirPilhaNew();

    return 0;
}