#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

///Arvore
struct bst {
    struct noBst* raiz;
    int tam;
};
/// No Arvore
struct noBst {
    int N_no; /// valores usados nas demais funções
    struct noBst* esq;
    struct noBst* dir;
};
/**
* Função/Estrutura que aloca um novo noBst
* Definição dos ponteiros esquerda e direita para o NULL
**/
struct noBst* alocarNovoNo(int N_no) {
    struct noBst* no = (struct noBst*)malloc(sizeof(struct noBst));
    no->N_no = N_no; /// auxiliar do para o NovoNo
    no->esq = NULL; /// alocar ponteiro esquerdo para NULL
    no->dir = NULL; /// alocar ponteiro direito para NULL

    return no;
};
/**
 * Funcao que aloca uma nova bst.
 **/
struct bst* alocarBst() {
    struct bst* arvore = (struct bst*)malloc(sizeof(struct bst));
    arvore->raiz = NULL;
    arvore->tam = 0;

    return arvore;
};
/**
 * Funcao recursiva para inserir novo no na arvore passada
 * atraves da raiz.
 **/
void inserirNoRec(struct noBst* raiz, struct noBst* novoNo) {
    /// no esquerdo não vazio
    if (novoNo->N_no <= raiz->N_no && raiz->esq != NULL) {
        raiz = raiz->esq;
        inserirNoRec(raiz, novoNo);
    }
    /// no direito não vazio
    else if (novoNo->N_no > raiz->N_no && raiz->dir != NULL) {
        raiz = raiz->dir;
        inserirNoRec(raiz, novoNo);
    }
    /// no esquerdo vazio
    else if (novoNo->N_no <= raiz->N_no && raiz->esq == NULL) {
        raiz->esq = novoNo;
        return;
    }
    /// no direito vazio
    else if (novoNo->N_no > raiz->N_no && raiz->dir == NULL) {
        raiz->dir = novoNo;
        return;
    }
}
/**
 * Funcao iterativa para inserir novo no na arvore passada
 * atraves da raiz.
 **/
void inserirNoIt(struct noBst* raiz, struct noBst* novoNo) {
    /// fica de forma iterativa
    /// função similar a forma recursiva
    /// diferença por que não chama a função
    while (raiz != NULL) {
        /// no esquerdo não vazio
        if (novoNo->N_no <= raiz->N_no && raiz->esq != NULL) {
            raiz = raiz->esq;
        }
        /// no direito não vazio
        else if (novoNo->N_no > raiz->N_no && raiz->dir != NULL) {
            raiz = raiz->dir;
        }
        /// no esquerdo vazio
        else if (novoNo->N_no <= raiz->N_no && raiz->esq == NULL) {
            raiz->esq = novoNo;
            return;
        }
        /// no direito vazio
        else if (novoNo->N_no > raiz->N_no && raiz->dir == NULL) {
            raiz->dir = novoNo;
            return;
        }
    }
}
/**
 * Fachada para função de insercao.
 **/
void inserir(struct bst* bst, int N_no, bool rec) {
    struct noBst* novoNo = alocarNovoNo(N_no);
    if (bst->tam == 0) {
        bst->raiz = novoNo;
    }
    else if (bst->tam != 0) {
        switch (rec) {
        case 0:
            inserirNoIt(bst->raiz, novoNo);
            break;
        case 1:
            inserirNoRec(bst->raiz, novoNo);
            break;
        }
    }
}
/**
 * Funcao recursiva para buscar v na arvore passada
 * atraves da raiz.
 **/
bool buscarRec(struct noBst* raiz, int N_no) {
    if (N_no == raiz->N_no) {
        return true;
    }
    else if (N_no < raiz->N_no && raiz->esq != NULL) {
        return buscarRec(raiz->esq, N_no);
    }
    else if (N_no > raiz->N_no && raiz->dir != NULL) {
        return buscarRec(raiz->dir, N_no);
    }
    else {
        return false;
    }
}
/**
 * Funcao iterativa para buscar v na arvore passada
 * atraves da raiz.
 **/
bool buscarIt(struct noBst* raiz, int N_no) {
    /// funcão parecida com a função busca recursiva
    while (raiz != NULL) {
        if (raiz->N_no == N_no) {
            return true;
        }
        else if (N_no < raiz->N_no) {
            raiz = raiz->esq;
        }
        else if (N_no > raiz->N_no) {
            raiz = raiz->dir;
        }
    }
    return false;
}
/**
 * Fachada para função de busca.
 **/
bool buscar(struct bst* bst, int N_no, bool rec) {
    bool achou = false;
    if (bst->raiz == NULL) {
        return false;
    }
    else if (bst->raiz != NULL) {
        switch (rec) {
        case 0:
            buscarIt(bst->raiz, N_no);
            break;
        case 1:
            buscarRec(bst->raiz, N_no);
            break;
        }
    }
}
/**
 * Funcao rec para navegacao em-ordem.
 **/
void navEmOrdem(struct noBst* raiz) {
    if (raiz == NULL) {
        return;
    }
    navEmOrdem(raiz->esq);
    printf("\n%d", raiz->N_no);
    navEmOrdem(raiz->dir);
}
/**
 * Funcao rec para navegacao pre-ordem.
 **/
void navPreOrdem(struct noBst* raiz) {
    if (raiz == NULL) {
        return;
    }
    printf("\n%d", raiz->N_no);
    navPreOrdem(raiz->esq);
    navPreOrdem(raiz->dir);
}
/**
 * Funcao rec para navegacao pos-ordem.
 **/
void navPosOrdem(struct noBst* raiz) {
    if (raiz == NULL) {
        return;
    }
    navPosOrdem(raiz->esq);
    navPosOrdem(raiz->dir);
    printf("\n%d", raiz->N_no);
}
/**
 * Funcao rec para obter valor minimo.
 **/
int min(struct noBst* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    else if (raiz->esq == NULL) {
        return raiz->N_no;
    }
    else {
        return min(raiz->esq);
    }
}
/**
 * Funcao rec para obter valor maximo.
 **/
int max(struct noBst* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    else if (raiz->dir == NULL) {
        return raiz->N_no;
    }
    else {
        return max(raiz->dir);
    }
}
/// altura da arvore
int altura(struct noBst* raiz) {
    if ((raiz == NULL) || (raiz->esq == NULL && raiz->dir == NULL)) {
        return 0;
    }
    
    int alt_esq = altura(raiz->esq);
    int alt_dir = altura(raiz->dir);
    

    /// altura da arvora no lado esquerdo
    if (raiz->esq != NULL) {
        alt_esq = altura(raiz->esq) + 1;
    }
    /// altura da arvore no lado direito
    if (raiz->dir != NULL) {
        alt_dir = altura(raiz->dir) + 1;
    }
    /// teste para ver qual era a maior altura
    /// teste esquerdo
    if (alt_esq > alt_dir) {
        return alt_esq;;
    }
    /// teste direito
    else {
        return alt_dir;
    }
}
/**
 * Funcao rec para remover da arvore no com valor especifico.
 **/
struct noBst* removerRec(struct noBst* raiz, int N_no) {
    /// teste para ver se a raiz não esta vazia
    if (raiz != NULL) {
        if (N_no < raiz->N_no) {
            raiz->esq = removerRec(raiz->esq, N_no);
        }
        else if (N_no > raiz->N_no) {
            raiz->dir = removerRec(raiz->dir, N_no);
        }
        else {
            if (raiz->esq == NULL && raiz->dir == NULL) {
                free(raiz);
                return NULL;
            }
            else if (raiz->esq != NULL && raiz->dir == NULL) {
                struct noBst* aux = raiz->esq;
                free(raiz);
                return aux;
            }
            else if (raiz->esq == NULL && raiz->dir != NULL) {
                struct noBst* aux = raiz->dir;
                free(raiz);
                return aux;
            }
            else {
                int minimo = min(raiz->dir);
                raiz->N_no = minimo;
                removerRec(raiz->dir, raiz->N_no);
            }
        }
        return raiz;
    }
    else {
        return raiz;
    }
}
/**
 * Fachada para funcao de remocao.
 */
void remover(struct bst* bst, int N_no) {
    struct noBst* val = (struct noBst*)malloc(sizeof(noBst));

    if (bst->raiz != NULL) {
        struct noBst* no = removerRec(bst->raiz, N_no);
        if (no != NULL) {
            bst->raiz = no;
        }
        bst->tam--;
    }
}
