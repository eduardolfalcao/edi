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

struct bst* alocarBst() {
    struct bst* bst = (struct bst*)malloc(sizeof(struct bst));
    bst->raiz = NULL;
    bst->tam = 0;
    return bst;
}

struct noBst* alocarNovoNo(int val) {
    struct noBst* novoNo = (struct noBst*)malloc(sizeof(struct noBst));
    novoNo->val = val;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

//recursiva
/*void inserirNoRec(struct noBst** raiz, struct noBst* novoNo) {
    if ((*raiz) == NULL)
        (*raiz) = novoNo;
    else if (novoNo->val <= (*raiz)->val)
        inserirNoRec(&((*raiz)->esq), novoNo);
    else
        inserirNoRec(&((*raiz)->dir), novoNo);
}*/

void inserirNoRec(struct noBst** raiz, struct noBst* novoNo) {
    if ((*raiz) == NULL)
        (*raiz) = novoNo;
    else if (novoNo->val <= (*raiz)->val)
        inserirNoRec(&(*raiz)->esq, novoNo);
    else
        inserirNoRec(&(*raiz)->dir, novoNo);
}

void inserirNoIt(struct noBst* raiz, struct noBst* novoNo) {
    struct noBst* noBstAux = raiz;
    struct noBst* noBstAux2 = NULL;
    while (noBstAux != NULL) {
        noBstAux2 = noBstAux;
        if (novoNo->val <= noBstAux->val)
            noBstAux = noBstAux->esq;
        else
            noBstAux = noBstAux->dir;
    }
    if (novoNo->val <= noBstAux2->val)
        noBstAux2->esq = novoNo;
    else
        noBstAux2->dir = novoNo;
}

void inserir(struct bst* bst, int val, bool rec) {
    if (bst->raiz == NULL) 
        bst->raiz = alocarNovoNo(val);
    else {
        if(rec == true)
            inserirNoRec(&(bst->raiz), alocarNovoNo(val));
        else
            inserirNoIt(bst->raiz, alocarNovoNo(val));
    }
    bst->tam++;
}

bool buscarRec(struct noBst* raiz, int val) {
    if (raiz == NULL)
        return false;
    else {
        if (val == raiz->val)
            return true;
        else if (val < raiz->val)
            return buscarRec(raiz->esq, val);
        else
            return buscarRec(raiz->dir, val);
    }
}

bool buscarIt(struct noBst* raiz, int v) {
    struct noBst* noBstAux = raiz;
    struct noBst* noBstAux2 = NULL;
    while (noBstAux != NULL) {
        noBstAux2 = noBstAux;
        if (v == noBstAux->val)
            return true;
        if (v < noBstAux->val)
            noBstAux = noBstAux->esq;
        else
            noBstAux = noBstAux->dir;
    }
    return false;
}

bool buscar(struct bst* bst, int val, bool rec) {
    if(rec == true)
        return buscarRec(bst->raiz, val);
    else
        return buscarIt(bst->raiz, val);
}

void navEmOrdem(struct noBst* raiz) {
    if (raiz != NULL) {
        navEmOrdem(raiz->esq);
        printf("%d, ", raiz->val);
        navEmOrdem(raiz->dir);
    }
}

void navPreOrdem(struct noBst* raiz) {
    if (raiz != NULL) {
        printf("%d, ", raiz->val);
        navPreOrdem(raiz->esq);        
        navPreOrdem(raiz->dir);
    }
}

void navPosOrdem(struct noBst* raiz) {
    if (raiz != NULL) {        
        navPosOrdem(raiz->esq);
        navPosOrdem(raiz->dir);
        printf("%d, ", raiz->val);
    }
}

int min(struct noBst* raiz) {
    if (raiz == NULL)
        return NULL;
    else if (raiz->esq == NULL)
        return raiz->val;
    else
        return min(raiz->esq);
}

int max(struct noBst* raiz) {
    if (raiz == NULL)
        return NULL;
    else if (raiz->dir == NULL)
        return raiz->val;
    else
        return max(raiz->dir);
}

int altura(struct noBst* raiz) {
    if (raiz == NULL) {
        return 0;
    }

    int hEsq = 0, hDir = 0;
    if (raiz->esq != NULL)
        hEsq = 1 + altura(raiz->esq);
    if (raiz->dir != NULL)
        hDir = 1 + altura(raiz->dir);
        
    if (hDir > hEsq)
        return hDir;
    else 
        return hEsq;
}

struct noBst* removerRec(struct noBst* raiz, int val) {
    if (raiz == NULL)
        return raiz;
    else if (val < raiz->val) {
        raiz->esq = removerRec(raiz->esq, val);
    }
    else if (val > raiz->val) {
        raiz->dir = removerRec(raiz->dir, val);
    }
    else {  //encontramos o nó a ser removido
        //caso 1: nó folha
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            raiz = NULL;
        }
        //caso 2: apenas 1 filho (na esq)
        else if ((raiz->esq != NULL && raiz->dir == NULL)) {
            struct noBst* noASerRemovido = raiz;
            raiz = raiz->esq;
            free(noASerRemovido);
        }
        //caso 2: apenas 1 filho (na dir)
        else if ((raiz->esq == NULL && raiz->dir != NULL)) {
            struct noBst* noASerRemovido = raiz;
            raiz = raiz->dir;
            free(noASerRemovido);
        }
        //caso 3: 2 filhos
        else {
            int menorValorDaSubArvDir = min(raiz->dir);
            raiz->val = menorValorDaSubArvDir;
            raiz->dir = removerRec(raiz->dir, menorValorDaSubArvDir);
        }
    }
    return raiz;
}

void remover(struct bst* bst, int val) {
    if (removerRec(bst->raiz, val) != NULL) {
        bst->tam--;
    }
}