#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <queue>

struct avl
{
    struct noBstAvl* raiz;
    int tam;
};

struct noBstAvl
{
    int n;
    int altura_H;
    int balanco;
    struct noBstAvl* esq;
    struct noBstAvl* dir;
};


void inserir(struct avl* avl, int n);
void atualizar(struct noBstAvl* no);
struct noBstAvl* rotacaoEsquerda(struct noBstAvl* arvore);
struct noBstAvl* rotacaoDireita(struct noBstAvl* arvore);
struct noBstAvl* balancear(struct noBstAvl* no);
struct noBstAvl* rebalancearEsqEsq(struct noBstAvl* no);
struct noBstAvl* rebalancearEsqDir(struct noBstAvl* no);
struct noBstAvl* rebalancearDirDir(struct noBstAvl* no);
struct noBstAvl* rebalancearDirEsq(struct noBstAvl* no);


struct avl* alocarAvl()
{
    struct avl* Arvore = (struct avl*)malloc(sizeof(struct avl));
    Arvore->raiz = NULL;
    Arvore->tam = 0;
    return Arvore;
}
/// função de alocar no
struct noBstAvl* alocarNovoNo(int n)
{
    struct noBstAvl* NovoNo = (struct noBstAvl*)malloc(sizeof(struct noBstAvl));
    NovoNo->n = n;
    NovoNo->esq = NULL;
    NovoNo->dir = NULL;
    NovoNo->altura_H = 0;
    NovoNo->balanco = 0;
    return NovoNo;
}

struct noBstAvl* rotacaoEsquerda(struct noBstAvl* arvore)
{
    struct noBstAvl* novaRaiz = arvore->dir;
    arvore->dir = novaRaiz->esq;
    novaRaiz->esq = arvore;
    atualizar(arvore);
    atualizar(novaRaiz);
    return novaRaiz;
}

struct noBstAvl* rotacaoDireita(struct noBstAvl* arvore)
{
    struct noBstAvl* novaRaiz = arvore->esq;
    arvore->esq = novaRaiz->dir;
    novaRaiz->dir = arvore;
    atualizar(arvore);
    atualizar(novaRaiz);
    return novaRaiz;
}

void inserirNo(struct noBstAvl* raiz, struct noBstAvl* NovoNo)
{
    if (NovoNo->n <= raiz->n && raiz->esq != NULL)
    {
        inserirNo(raiz->esq, NovoNo);
    }
    else if (NovoNo->n <= raiz->n && raiz->esq == NULL)
    {
        raiz->esq = NovoNo;
    }

    else if (NovoNo->n > raiz->n && raiz->dir != NULL)
    {
        inserirNo(raiz->dir, NovoNo);
    }
    else if (NovoNo->n > raiz->n && raiz->dir == NULL)
    {
        raiz->dir = NovoNo;
    }
    atualizar(raiz);
    balancear(raiz);
}

void inserir(struct avl* avl, int n)
{
    struct noBstAvl* NovoNo = alocarNovoNo(n);
    if (avl->tam == 0)
    {
        avl->raiz = NovoNo;
    }
    else
    {
        inserirNo(avl->raiz, NovoNo);
    }
    avl->tam++;
}



void atualizar(struct noBstAvl* no)
{
    int hEsq = 0;
    int hDir = 0;
    /// teste de no vazio na direita
    if (no->dir != NULL)
    {
        hDir = no->dir->altura_H;
    }
    else
    {
        hDir = -1;
    }
    /// teste de no vazio na esquerda
    if (no->esq != NULL)
    {
        hEsq = no->esq->altura_H;
    }
    else
    {
        hEsq = -1;
    }
    /// teste de comparação de altura esquerda maior que direita
    if (hEsq > hDir)
    {
        no->altura_H = hEsq + 1;
    }
    else
    {
        no->altura_H = hDir + 1;
    }
    /// teste de comparação de altura direita maior que esquerda
    if (no->altura_H == 0)
    {
        no->balanco = 0;
    }
    else
    {
        no->balanco = hDir - hEsq;
    }
}

struct noBstAvl* balancear(struct noBstAvl* no)
{
    if (no->balanco == -2)
    {
        if (no->esq->balanco <= 0)
        {
            no = rebalancearEsqEsq(no);
            return no;
        }
        else
        {
            no = rebalancearEsqDir(no);
        }
    }
    if (no->balanco == 2)
    {
        if (no->dir->balanco <= 0)
        {
            no = rebalancearDirEsq(no);
            return no;
        }
        else
        {
            no = rebalancearDirDir(no);
            return no;
        }
    }
    else
    {
        return no;
    }
}

struct noBstAvl* rebalancearEsqEsq(struct noBstAvl* no)
{
    return rotacaoDireita(no);
}

struct noBstAvl* rebalancearDirDir(struct noBstAvl* no)
{
    return rotacaoEsquerda(no);
}

struct noBstAvl* rebalancearEsqDir(struct noBstAvl* no)
{
    no->esq = rotacaoEsquerda(no->esq);
    return rotacaoDireita(no);
}

struct noBstAvl* rebalancearDirEsq(struct noBstAvl* no)
{
    no->dir = rotacaoDireita(no->dir);
    return rotacaoEsquerda(no);
}

int max(struct noBstAvl* raiz)
{
    if (raiz == NULL)
    {
        return NULL;
    }
    if (raiz->dir != NULL)
    {
        return max(raiz->dir);
    }
    else
    {
        return raiz->n;
    }
}

int min(struct noBstAvl* raiz)
{
    if (raiz == NULL)
    {
        return NULL;
    }
    if (raiz->esq != NULL)
    {
        return min(raiz->esq);
    }
    else
    {
        return raiz->n;
    }
}

/// função de remoção de no
void remover(struct avl* avl, int n)
{
    if (removerNo(avl->raiz, n) != NULL)
    {
        avl->tam--;
    }
}
/// funcção de remoção de no em local especifico
struct noBstAvl* removerNo(struct noBstAvl* raiz, int n)
{
    if (raiz == NULL)
        return raiz;
    else
    {
        if (n < raiz->n)
        {
            raiz->esq = removerNo(raiz->esq, n);
        }
        else if (n > raiz->n)
        {
            raiz->dir = removerNo(raiz->dir, n);
        }
        else
        {
            if (raiz->esq == NULL && raiz->dir == NULL)
            {
                free(raiz);
                return NULL;
            }
            else if (raiz->esq != NULL && raiz->dir == NULL)
            {
                struct noBstAvl* aux = raiz->esq;
                free(raiz);
                return aux;
            }
            else if (raiz->esq == NULL && raiz->dir != NULL)
            {
                struct noBstAvl* aux = raiz->dir;
                free(raiz);
                return aux;
            }
            else
            {
                int maximo = max(raiz->dir);
                raiz->n = maximo;
                removerNo(raiz->dir, raiz->n);
            }
        }
        atualizar(raiz);
        raiz = balancear(raiz);
        return raiz;
    }
}

#endif // AVL_H_INCLUDED
