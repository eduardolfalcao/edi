#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct noBst {
    int val;
    struct noBst* esq;
    struct noBst* dir;
};

struct noBst* alocarNovoNo(int val) {
    struct noBst* no = (struct noBst*)malloc(sizeof(struct noBst));
    no->val = val;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

void inserir(struct noBst** raiz, int val, int* tamanho) {
    if ((*raiz) == NULL) {
        (*raiz) = alocarNovoNo(val);
        (*tamanho)++;
    }
    else if (val <= (*raiz)->val) 
        inserir(&((*raiz)->esq), val, tamanho);
    else 
        inserir(&((*raiz)->dir), val, tamanho);
}

bool buscar(struct noBst* raiz, int val) {
    if (raiz == NULL)
        return false;
    else if (raiz->val == val)
        return true;
    else if (val < raiz->val)
        return buscar(raiz->esq, val);
    else 
        return buscar(raiz->dir, val);
}

int max(struct noBst* raiz) {
    if (raiz == NULL)
        return NULL;
    else if (raiz->dir == NULL)
        return raiz->val;
    else 
        return max(raiz->dir);
}

int min(struct noBst* raiz) {
    if (raiz == NULL)
        return NULL;
    else if (raiz->esq == NULL)
        return raiz->val;
    else
        return min(raiz->esq);
}

int altura(struct noBst* raiz) {
    if (raiz == NULL)
        return 0;
    int alturaSubArvoreEsquerda = 0;
    int alturaSubArvoreDireita = 0;

    if (raiz->esq != NULL)
        alturaSubArvoreEsquerda = 1 + altura(raiz->esq);  
    if (raiz->dir != NULL)
        alturaSubArvoreDireita = 1 + altura(raiz->dir);
    
    if (alturaSubArvoreEsquerda > alturaSubArvoreDireita)
        return alturaSubArvoreEsquerda;
    else
        return alturaSubArvoreDireita;
}

void emOrdem(struct noBst* raiz) {
    if (raiz == NULL)
        return;
    else {
        emOrdem(raiz->esq);
        printf("%d, ", raiz->val);
        emOrdem(raiz->dir);
    }
}

void preOrdem(struct noBst* raiz) {
    if (raiz == NULL)
        return;
    else { 
        printf("%d, ", raiz->val);
        preOrdem(raiz->esq);       
        preOrdem(raiz->dir);
    }
}

void posOrdem(struct noBst* raiz) {
    if (raiz == NULL)
        return;
    else {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d, ", raiz->val);
    }
}

struct noBst* remover(struct noBst* raiz, int val, int* tamanho) {
    if (raiz == NULL)
        return raiz;
    else if (val < raiz->val) {
        raiz->esq = remover(raiz->esq, val, tamanho);
    }
    else if (val > raiz->val) {
        raiz->dir = remover(raiz->dir, val, tamanho);
    }
    else {  //encontramos o nó a ser removido
        //caso 1: nó folha
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            raiz = NULL;
            (*tamanho)--;
        }
        //caso 2: apenas 1 filho (na esq)
        else if ((raiz->esq != NULL && raiz->dir == NULL)) {
            struct noBst* noASerRemovido = raiz;
            raiz = raiz->esq;
            free(noASerRemovido); 
            (*tamanho)--;
        }
        //caso 2: apenas 1 filho (na dir)
        else if ((raiz->esq == NULL && raiz->dir != NULL)) {
            struct noBst* noASerRemovido = raiz;
            raiz = raiz->dir;
            free(noASerRemovido);
            (*tamanho)--;
        }
        //caso 3: 2 filhos
        else {
            int menorValorDaSubArvDir = min(raiz->dir);
            raiz->val = menorValorDaSubArvDir;
            remover(raiz->dir, menorValorDaSubArvDir, tamanho);            
        }
    }
    return raiz;    
}