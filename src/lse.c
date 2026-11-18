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
/* Stubs intencionalmente incompletos; testes devem falhar ate implementacao. */
t_lse *lse_criar(void) { 

    t_lse* novaLista = (t_lse*) malloc(sizeof(t_lse));

    if(novaLista != NULL) {
        novaLista -> inicio = NULL;
        novaLista -> tamanho = 0;
    }

    return novaLista; 
} /* TODO M02/M03 */

int lse_tamanho(const t_lse *l) { 
    (void)l; 
    assert(l!=NULL);
    
    return l -> tamanho; 
} /* TODO M03 */


void *lse_primeiro(const t_lse *l) {
    (void)l; 
    
    return l -> inicio -> carga; 
    
} /* TODO M03 */



void lse_percorrer(const t_lse *lista, t_lse_visitar cb_visitar){   
    t_elem *atual = lista->inicio;
    while (atual !=NULL){
        cb_visitar(atual->carga);
        atual = atual->prox;
    }

}/* TODO M02/M03 */

t_elem* criar_elem_lse(void* carga){

    t_elem*novo = (sizeof(t_elem));
    novo->carga = carga;
    novo->prox = NULL;
    return novo;
}


int lse_inserir_inicio(t_lse *lista, void *c) { 
    t_elem *novo = lse_criar();
    if (novo == NULL){
        return 0;   
    }
    (void)lista; 
    (void)c; 
    if (lista->inicio == NULL){
        lista->inicio= novo;
    }else{
        novo->prox = lista->inicio;
        lista->inicio = novo;
    }
    lista->tamanho++;
    return 1; 

    
} 


int lse_inserir_fim(t_lse *lista, void *carga) {
    t_elem* novo = criar_elem_lse(carga);

    if(novo ==NULL)
        return 0;

    if(lista -> inicio == NULL) {
        lista -> inicio = novo;
    } else {
        t_elem* cam = lista -> inicio;
        while (cam -> prox != NULL) {
            cam = cam -> prox;
        }

        cam -> prox = novo;
    }

    lista -> tamanho++;

    return 1;
} /* TODO M04 */
void *lse_remover_inicio(t_lse *lista) { 

    if(lista -> tamanho == 0) {
        return NULL;
    }

    t_elem* prim = lista -> inicio;
    lista -> inicio = prim -> prox;

    void* carga = prim -> prox;
    free(prim);

    return NULL;
} /* TODO M04 */
void *lse_buscar(const t_lse *l, const void *ch, t_comparador cmp) { (void)l; (void)ch; (void)cmp; return NULL; } /* TODO M04 */
void *lse_remover(t_lse *l, const void *ch, t_comparador cmp) { (void)l; (void)ch; (void)cmp; return NULL; } /* TODO M04 */
int lse_inserir_ordenado(t_lse *l, void *c, t_comparador cmp) { (void)l; (void)c; (void)cmp; return 0; } /* TODO M05 */

void lse_destruir(t_lse *l, void (*destruir)(void *)) { 
    (void)l; 
    (void)destruir;

    if (l == NULL) {
        return;
    }

    t_elem *atual = l -> inicio;

    while(atual != NULL) {
        t_elem *proximo = atual -> prox;

        destruir(atual -> carga);
        free(atual);

        atual = proximo;
    }

    free(l);
}