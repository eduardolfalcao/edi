#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <queue>
using namespace std;

void atualizar(struct noBstAvl* no);
struct noBstAvl* balancear(struct noBstAvl* no);
struct noBstAvl* rebalancearEsqEsq(struct noBstAvl* no);
struct noBstAvl* rebalancearEsqDir(struct noBstAvl* no);
struct noBstAvl* rebalancearDirDir(struct noBstAvl* no);
struct noBstAvl* rebalancearDirEsq(struct noBstAvl* no);

struct avl {
    struct noBstAvl* raiz;
    int tam;
};

struct noBstAvl {
    int val;
    int altura;
    int balanco;
    struct noBstAvl* esq;
    struct noBstAvl* dir;
};

struct avl* alocarAvl() {
    struct avl* avl = (struct avl*)malloc(sizeof(struct avl));
    avl->raiz = NULL;
    avl->tam = 0;
    return avl;
}

struct noBstAvl* alocarNovoNo(int val) {
    struct noBstAvl* no = (struct noBstAvl*)malloc(sizeof(struct noBstAvl));
    no->val = val;
    no->altura = 0;
    no->balanco = 0;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

struct noBstAvl* rotacaoDireita(struct noBstAvl* arvore) {
    struct noBstAvl* esq = arvore->esq;
    arvore->esq = esq->dir;
    esq->dir = arvore;
    atualizar(esq->dir);
    atualizar(esq);    
    return esq;
}

struct noBstAvl* rotacaoEsquerda(struct noBstAvl* arvore) {
    struct noBstAvl* dir = arvore->dir;
    arvore->dir = arvore->dir->esq;
    dir->esq = arvore;
    atualizar(dir->esq);
    atualizar(dir);    
    return dir;
}

void inserirNo(struct noBstAvl** raiz, int val) {
    if ((*raiz) == NULL) 
        (*raiz) = alocarNovoNo(val);
    else if (val <= (*raiz)->val) 
        inserirNo(&((*raiz)->esq), val);
    else 
        inserirNo(&((*raiz)->dir), val);

    atualizar(*raiz);
    (*raiz) = balancear(*raiz);
}

void inserir(struct avl* avl, int val) {
    if (avl->raiz == NULL)
        avl->raiz = alocarNovoNo(val);
    else
        inserirNo(&(avl->raiz), val);
    avl->tam++;
}

/*
* Objetivo: atualizar altura e fator de balanço do nó.
* Lembre que a altura das sub-árvores direita e esquerda 
* não vão mudar, por isso a implementação não é tão complicada.
*/
void atualizar(struct noBstAvl* no) {
    int altSubArvEsq = 0;
    int altSubArvDir = 0;

    if (no->esq != NULL)
        altSubArvEsq = no->esq->altura;
    if (no->dir != NULL)
        altSubArvDir = no->dir->altura;

    //se não há sub-árvore dir e esq, então a 
    //altura é 0 (em vez de 1)
    if (no->esq == NULL && no->dir == NULL)
        no->altura = 0;
    else
        no->altura = 1 + (altSubArvEsq > altSubArvDir ? altSubArvEsq : altSubArvDir);

    no->balanco = altSubArvDir - altSubArvEsq;
}

struct noBstAvl* balancear(struct noBstAvl* no) {
    if (no->balanco == -2) {         //desbalanceada à esquerda
        if (no->esq->balanco <= 0)    //esquerda-esquerda (caso 1)
            return rebalancearEsqEsq(no);
        else                         //esquerda-direita (caso 2)
            return rebalancearEsqDir(no);
    } else if (no->balanco == 2) {  //desbalanceada à direita
        if (no->dir->balanco >= 0)    //direita-direita (caso 3)
            return rebalancearDirDir(no);
        else                         //direita-esquerda (caso 4)
            return rebalancearDirEsq(no);
    }

    //balanco eh -1, 0, ou 1 (nao tem problema)
    return no;
}

struct noBstAvl* rebalancearEsqEsq(struct noBstAvl* no) {
    return rotacaoDireita(no);
}

struct noBstAvl* rebalancearEsqDir(struct noBstAvl* no) {
    no->esq = rotacaoEsquerda(no->esq);
    return rebalancearEsqEsq(no);
}

struct noBstAvl* rebalancearDirDir(struct noBstAvl* no) {
    return rotacaoEsquerda(no);
}

struct noBstAvl* rebalancearDirEsq(struct noBstAvl* no) {
    no->dir = rotacaoDireita(no->dir);
    return rebalancearDirDir(no);
}

int max(struct noBstAvl* raiz) {
    if (raiz == NULL)
        return NULL;
    else if (raiz->dir == NULL)
        return raiz->val;
    else 
        return max(raiz->dir);
}

int min(struct noBstAvl* raiz) {
    if (raiz == NULL)
        return NULL;
    else if (raiz->esq == NULL)
        return raiz->val;
    else
        return min(raiz->esq);
}

void emOrdem(struct noBstAvl* raiz) {
    if (raiz == NULL)
        return;
    else {
        emOrdem(raiz->esq);
        printf("%d, ", raiz->val);
        emOrdem(raiz->dir);
    }
}

void preOrdem(struct noBstAvl* raiz) {
    if (raiz == NULL)
        return;
    else { 
        printf("%d, ", raiz->val);
        preOrdem(raiz->esq);       
        preOrdem(raiz->dir);
    }
}

void posOrdem(struct noBstAvl* raiz) {
    if (raiz == NULL)
        return;
    else {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d, ", raiz->val);
    }
}

struct noBstAvl* removerNo(struct noBstAvl* raiz, int val) {
    if (raiz == NULL)
        return raiz;
    else if (val < raiz->val) {
        raiz->esq = removerNo(raiz->esq, val);
    }
    else if (val > raiz->val) {
        raiz->dir = removerNo(raiz->dir, val);
    }
    else {  //encontramos o nó a ser removido
        //caso 1: nó folha
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            raiz = NULL;
        }
        //caso 2: apenas 1 filho (na esq)
        else if ((raiz->esq != NULL && raiz->dir == NULL)) {
            struct noBstAvl* noASerRemovido = raiz;
            raiz = raiz->esq;
            free(noASerRemovido); 
        }
        //caso 2: apenas 1 filho (na dir)
        else if ((raiz->esq == NULL && raiz->dir != NULL)) {
            struct noBstAvl* noASerRemovido = raiz;
            raiz = raiz->dir;
            free(noASerRemovido);
        }
        //caso 3: 2 filhos
        else {
            //2 abordagens:
                //2.1: menorValorDaSubArvDir
                //2.2: maiorValorDaSubArvEsq
            if (raiz->esq->altura > raiz->dir->altura) {
                int maiorValorDaSubArvEsq = max(raiz->esq);
                raiz->val = maiorValorDaSubArvEsq;
                raiz->esq = removerNo(raiz->esq, maiorValorDaSubArvEsq);
            }
            else {
                int menorValorDaSubArvDir = min(raiz->dir);
                raiz->val = menorValorDaSubArvDir;
                raiz->dir = removerNo(raiz->dir, menorValorDaSubArvDir);
            }                        
        }
    }
    if (raiz != NULL) {
        atualizar(raiz);
        raiz = balancear(raiz);
    }
    return raiz;    
}

void remover(struct avl* avl, int val) {
    if (removerNo(avl->raiz, val) != NULL) {
        avl->tam--;
    }
}

struct noBstAvl* buscarArv(struct noBstAvl* raiz, int val) {
    if (raiz == NULL)
        return NULL;
    else if (raiz->val == val)
        return raiz;
    else if (val < raiz->val)
        return buscarArv(raiz->esq, val);
    else
        return buscarArv(raiz->dir, val);
}

void imprimir(queue<struct noBstAvl*> nosImpressao);

void imprimir(struct noBstAvl* raiz) {
    queue<struct noBstAvl*> nosImpressao;
    nosImpressao.push(raiz);
    imprimir(nosImpressao);
}

void imprimir(queue<struct noBstAvl*> nosImpressao) {

    queue<struct noBstAvl*> nosImpressaoProxNivel;

    while (!nosImpressao.empty()) {
        struct noBstAvl* noImpressao = nosImpressao.front();
        //add filhos na fila
        if(noImpressao != NULL){
            if (noImpressao->esq != NULL) 
                nosImpressaoProxNivel.push(noImpressao->esq);
            else
                nosImpressaoProxNivel.push(NULL);
            if (noImpressao->dir != NULL) 
                nosImpressaoProxNivel.push(noImpressao->dir);
            else
                nosImpressaoProxNivel.push(NULL);
        }
        nosImpressao.pop();

        if (noImpressao != NULL) {
            cout << to_string(noImpressao->val) << " | ";
        }
        else {
            cout << "N | ";
        }
    }
    cout << endl << endl;
    if(!nosImpressaoProxNivel.empty())
        imprimir(nosImpressaoProxNivel);
}