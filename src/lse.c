#include "lse.h"
#include <stddef.h>
#include <stdlib.h>

/* Representacao interna: NAO mover para lse.h. */
typedef struct elem {
    void *carga;
    struct elem *prox;
} t_elem;

struct lse {
    t_elem *inicio;
    t_elem *fim;
    int tamanho;
    /* M08 (otimizacao opcional): t_elem *fim; */
};
/* Stubs intencionalmente incompletos; testes devem falhar ate implementacao. */
t_lse *lse_criar(void) { 

    t_lse* novaLista = (t_lse*) malloc(sizeof(t_lse));

    if(novaLista != NULL) {
        novaLista -> inicio = NULL;
        novaLista -> fim = NULL;
        novaLista -> tamanho = 0;
    }

    return novaLista; 
} /* TODO M02/M03 */

int lse_tamanho(const t_lse *l) { 
    (void)l; 

    return l -> tamanho; 
} /* TODO M03 */


void *lse_primeiro(const t_lse *l) {
    (void)l; 
    
    return l -> inicio -> carga; 
    
} /* TODO M03 */


int lse_inserir_inicio(t_lse *l, void *c) { (void)l; (void)c; return 0; } /* TODO M04 */
int lse_inserir_fim(t_lse *l, void *c) { (void)l; (void)c; return 0; } /* TODO M04 */
void *lse_remover_inicio(t_lse *l) { (void)l; return NULL; } /* TODO M04 */
void *lse_buscar(const t_lse *l, const void *ch, t_comparador cmp) { (void)l; (void)ch; (void)cmp; return NULL; } /* TODO M04 */
void *lse_remover(t_lse *l, const void *ch, t_comparador cmp) { (void)l; (void)ch; (void)cmp; return NULL; } /* TODO M04 */
int lse_inserir_ordenado(t_lse *l, void *c, t_comparador cmp) { (void)l; (void)c; (void)cmp; return 0; } /* TODO M05 */

void lse_destruir(t_lse *l, void (*destruir)(void *)) { 
    (void)l; 
    (void)destruir;


    free(l);
}