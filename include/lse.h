#ifndef LSE_H
#define LSE_H

/* Representacao opaca: t_elem e campos de t_lse ficam em lse.c. */

typedef struct lse t_lse;
typedef int (*t_comparador)(const void *carga, const void *chave);

t_lse *lse_criar(void);

int lse_tamanho(const t_lse *lista);

void *lse_primeiro(const t_lse *lista);

int lse_inserir_inicio(t_lse *lista, void *carga);
int lse_inserir_fim(t_lse *lista, void *carga);

void *lse_remover_inicio(t_lse *lista);
void *lse_buscar(const t_lse *lista, const void *chave, t_comparador comparar);
void *lse_remover(t_lse *lista, const void *chave, t_comparador comparar);

int lse_inserir_ordenado(t_lse *lista, void *carga, t_comparador comparar);

void lse_destruir(t_lse *lista, void (*destruir_carga)(void *));

#endif
