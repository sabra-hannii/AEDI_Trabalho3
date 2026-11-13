#ifndef PILHA_H
#define PILHA_H
typedef struct pilha t_pilha;
t_pilha *pilha_criar(void);
int pilha_empilhar(t_pilha *pilha, void *carga);
void *pilha_desempilhar(t_pilha *pilha);
void *pilha_topo(const t_pilha *pilha);
void pilha_destruir(t_pilha *pilha, void (*destruir_carga)(void *));
#endif
