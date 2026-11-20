#include "lse.h"
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

/* Representacao interna: NAO mover para lse.h. */
typedef struct elem {
    void *carga;
    struct elem *prox;
} t_elem;

struct lse {
    t_elem *inicio;
    int tamanho;
    /* M08 (otimizacao opcional): t_elem *fim; */
};

t_lse *lse_criar(void) {
    t_lse *novaLista = (t_lse *) malloc(sizeof(t_lse));

    if (novaLista != NULL) {
        novaLista->inicio = NULL;
        novaLista->tamanho = 0;
    }

    return novaLista;
} /* TODO M02/M03 */

int lse_tamanho(const t_lse *l) {
    (void) l;
    assert(l != NULL);

    return l->tamanho;
} /* TODO M03 */

void *lse_primeiro(const t_lse *l) {
    assert(l != NULL);

    /* Se não tiver o primeiro, retorna vazio */
    if (l->inicio == NULL) {
        return NULL;
    }

    return l->inicio->carga;
} /* TODO M03 */

void lse_percorrer(const t_lse *lista, t_lse_visitar cb_visitar) {
    if (lista == NULL || cb_visitar == NULL) {
        return;
    }

    t_elem *atual = lista->inicio;
    while (atual != NULL) {
        cb_visitar(atual->carga);
        atual = atual->prox;
    }
} /* TODO M02/M03 */

t_elem *criar_elem_lse(void *carga) {
    t_elem *novo = malloc(sizeof(t_elem));

    novo->carga = carga;
    novo->prox = NULL;
    return novo;
}

int lse_inserir_inicio(t_lse *lista, void *carga) {
    if (lista == NULL) {
        return 0;
    }

    /* Criando um novo nó com a carga passado no argumento */
    t_elem *novo = criar_elem_lse(carga);

    novo->prox = lista->inicio;
    lista->inicio = novo;
    lista->tamanho++;
    return 1;
}

int lse_inserir_fim(t_lse *lista, void *carga) {
    if (lista == NULL) {
        return 0;
    }

    t_elem *novo = criar_elem_lse(carga);
    if (novo == NULL) {
        return 0;
    }

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        t_elem *cam = lista->inicio;
        while (cam->prox != NULL) {
            cam = cam->prox;
        }
        cam->prox = novo;
    }

    lista->tamanho++;
    return 1;
} /* TODO M04 */

void *lse_remover_inicio(t_lse *lista) {
    /* Se a lista não existir, ou o primeiro elemento não existir, retorna vazio */
    if (lista == NULL || lista->inicio == NULL) {
        return NULL;
    }

    t_elem *prim = lista->inicio;
    void *carga = prim->carga;

    lista->inicio = prim->prox;
    lista->tamanho--;
    free(prim);

    /* Retornando a carga do antigo primeiro elemento */
    return carga;
} /* TODO M04 */

void *lse_buscar(const t_lse *lista, const void *chave, t_comparador cmp) {
    /* Se a lista não existir, ou a função não existir, retorna vazio */
    if (lista == NULL || cmp == NULL) {
        return NULL;
    }

    t_elem *atual = lista->inicio;
    while (atual != NULL) {
        if (cmp(atual->carga, chave) == 0) {
            return atual->carga;
        }
        atual = atual->prox;
    }

    return NULL;
} /* TODO M04 */

void *lse_remover(t_lse *lista, const void *chave, t_comparador cmp) {
    if (lista == NULL || cmp == NULL) {
        return NULL;
    }

    t_elem *atual = lista->inicio;
    t_elem *ant = NULL;

    while (atual != NULL) {
        if (cmp(atual->carga, chave) == 0) {
            if (ant == NULL) {
                lista->inicio = atual->prox;
            } else {
                ant->prox = atual->prox;
            }

            void *carga = atual->carga;
            free(atual);
            lista->tamanho--;
            return carga;
        }
        ant = atual;
        atual = atual->prox;
    }

    return NULL;
} /* TODO M04 */

int lse_inserir_ordenado(t_lse *l, void *c, t_comparador cmp) {
    (void) l;
    (void) c;
    (void) cmp;
    return 0;
} /* TODO M05 */

void lse_destruir(t_lse *l, void (*destruir)(void *)) {
    (void) l;
    (void) destruir;

    if (l == NULL) {
        return;
    }

    t_elem *atual = l->inicio;

    while (atual != NULL) {
        t_elem *proximo = atual->prox;

        destruir(atual->carga);
        free(atual);

        atual = proximo;
    }

    free(l);
}