#include "pilha.h"
#include "lse.h"
#include <stddef.h>
struct pilha { t_lse *lista; };
/* M06: implementar apenas delegando para lse_*. */
t_pilha *pilha_criar(void) { return NULL; }
int pilha_empilhar(t_pilha *p, void *c) { (void)p; (void)c; return 0; }
void *pilha_desempilhar(t_pilha *p) { (void)p; return NULL; }
void *pilha_topo(const t_pilha *p) { (void)p; return NULL; }
void pilha_destruir(t_pilha *p, void (*d)(void *)) { (void)p; (void)d; }
