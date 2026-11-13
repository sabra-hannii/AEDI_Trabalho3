#include "fila.h"
#include "lse.h"
#include <stddef.h>
struct fila { t_lse *lista; };
/* M08: implementar apenas delegando para lse_*. */
t_fila *fila_criar(void) { return NULL; }
int fila_enfileirar(t_fila *f, void *c) { (void)f; (void)c; return 0; }
void *fila_desenfileirar(t_fila *f) { (void)f; return NULL; }
void *fila_frente(const t_fila *f) { (void)f; return NULL; }
void fila_destruir(t_fila *f, void (*d)(void *)) { (void)f; (void)d; }
