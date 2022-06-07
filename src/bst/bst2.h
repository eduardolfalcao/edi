#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct bst {
    struct noBst* raiz;
    int tam;
};

struct noBst {
    int val;
    struct noBst* esq;
    struct noBst* dir;
};

/**
 * Funcao que aloca uma nova bst.
 **/
struct bst* alocarBst() {
    //IMPLEMENTAR
}

/**
 * Funcao que aloca um novo noBst.
 **/
struct noBst* alocarNovoNo(int val) {
    //IMPLEMENTAR
}

/**
 * Funcao recursiva para inserir novo no na arvore passada
 * atraves da raiz.
 **/
void inserirNoRec(struct noBst** raiz, struct noBst* novoNo) {
    //IMPLEMENTAR
}

/**
 * Funcao iterativa para inserir novo no na arvore passada
 * atraves da raiz.
 **/
void inserirNoIt(struct noBst* raiz, struct noBst* novoNo) {
    //IMPLEMENTAR
}

/**
 * Fachada para função de insercao.
 **/
void inserir(struct bst* bst, int val, bool rec) {
    //IMPLEMENTAR
}

/**
 * Funcao recursiva para buscar v na arvore passada
 * atraves da raiz.
 **/
bool buscarRec(struct noBst* raiz, int val) {
    //IMPLEMENTAR
}

/**
 * Funcao iterativa para buscar v na arvore passada
 * atraves da raiz.
 **/
bool buscarIt(struct noBst* raiz, int v) {
    //IMPLEMENTAR
}

/**
 * Fachada para função de busca.
 **/
bool buscar(struct bst* bst, int val, bool rec) {
    //IMPLEMENTAR
}

/**
 * Funcao rec para navegacao em-ordem.
 **/
void navEmOrdem(struct noBst* raiz) {
    //IMPLEMENTAR
}

/**
 * Funcao rec para navegacao pre-ordem.
 **/
void navPreOrdem(struct noBst* raiz) {
    //IMPLEMENTAR
}

/**
 * Funcao rec para navegacao pos-ordem.
 **/
void navPosOrdem(struct noBst* raiz) {
    //IMPLEMENTAR
}

/**
 * Funcao rec para obter valor minimo.
 **/
int min(struct noBst* raiz) {
    //IMPLEMENTAR
}

/**
 * Funcao rec para obter valor maximo.
 **/
int max(struct noBst* raiz) {
    //IMPLEMENTAR
}

/**
 * Funcao rec para obter altura da arvore.
 **/
int altura(struct noBst* raiz) {
    //IMPLEMENTAR
}

/**
 * Funcao rec para remover da arvore no com valor especifico.
 **/
struct noBst* removerRec(struct noBst* raiz, int val) {
    //IMPLEMENTAR
}

/**
 * Fachada para funcao de remocao. 
 */
void remover(struct bst* bst, int val) {
    //IMPLEMENTAR
}