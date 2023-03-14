#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <queue>
using namespace std;

void atualizar(struct noBst* no);
struct noBst* balancear(struct noBst* no);
struct noBst* rebalancearEsqEsq(struct noBst* no);
struct noBst* rebalancearEsqDir(struct noBst* no);
struct noBst* rebalancearDirDir(struct noBst* no);
struct noBst* rebalancearDirEsq(struct noBst* no);

struct noBst {
    int val;
    int altura;
    //int alturaEsq;
    //int alturaDir;
    int balanco;
    struct noBst* esq;
    struct noBst* dir;
};

struct noBst* alocarNovoNo(int val) {
    struct noBst* no = (struct noBst*)malloc(sizeof(struct noBst));
    no->val = val;
    no->altura = 0;
    no->balanco = 0;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

struct noBst* rotacaoDireita(struct noBst* arvore) {
    struct noBst* esq = arvore->esq;
    arvore->esq = esq->dir;
    esq->dir = arvore;
    atualizar(esq->dir);
    atualizar(esq);    
    return esq;
}

struct noBst* rotacaoEsquerda(struct noBst* arvore) {
    struct noBst* dir = arvore->dir;
    arvore->dir = arvore->dir->esq;
    dir->esq = arvore;
    atualizar(dir->esq);
    atualizar(dir);    
    return dir;
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

    atualizar(*raiz);
    (*raiz) = balancear(*raiz);
}

/*
* Objetivo: atualizar altura e fator de balanço do nó.
* Lembre que a altura das sub-árvores direita e esquerda 
* não vão mudar, por isso a implementação não é tão complicada.
*/
void atualizar(struct noBst* no) {
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

struct noBst* balancear(struct noBst* no) {
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

struct noBst* rebalancearEsqEsq(struct noBst* no) {
    return rotacaoDireita(no);
}

struct noBst* rebalancearEsqDir(struct noBst* no) {
    no->esq = rotacaoEsquerda(no->esq);
    return rebalancearEsqEsq(no);
}

struct noBst* rebalancearDirDir(struct noBst* no) {
    return rotacaoEsquerda(no);
}

struct noBst* rebalancearDirEsq(struct noBst* no) {
    no->dir = rotacaoDireita(no->dir);
    return rebalancearDirDir(no);
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
            //2 abordagens:
                //2.1: menorValorDaSubArvDir
                //2.2: maiorValorDaSubArvEsq
            if (raiz->esq->altura > raiz->dir->altura) {
                int maiorValorDaSubArvEsq = max(raiz->esq);
                raiz->val = maiorValorDaSubArvEsq;
                raiz->esq = remover(raiz->esq, maiorValorDaSubArvEsq, tamanho);
            }
            else {
                int menorValorDaSubArvDir = min(raiz->dir);
                raiz->val = menorValorDaSubArvDir;
                raiz->dir = remover(raiz->dir, menorValorDaSubArvDir, tamanho);
            }                        
        }
    }
    if (raiz != NULL) {
        atualizar(raiz);
        raiz = balancear(raiz);
    }
    return raiz;    
}

struct noBst* buscarArv(struct noBst* raiz, int val) {
    if (raiz == NULL)
        return NULL;
    else if (raiz->val == val)
        return raiz;
    else if (val < raiz->val)
        return buscarArv(raiz->esq, val);
    else
        return buscarArv(raiz->dir, val);
}

void imprimir(queue<struct noBst*> nosImpressao);

void imprimir(struct noBst* raiz) {
    queue<struct noBst*> nosImpressao;
    nosImpressao.push(raiz);
    imprimir(nosImpressao);
}

void imprimir(queue<struct noBst*> nosImpressao) {

    queue<struct noBst*> nosImpressaoProxNivel;

    while (!nosImpressao.empty()) {
        struct noBst* noImpressao = nosImpressao.front();
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