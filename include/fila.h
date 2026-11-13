#ifndef FILA_H
#define FILA_H
typedef struct fila t_fila;
t_fila *fila_criar(void);
int fila_enfileirar(t_fila *fila, void *carga);
void *fila_desenfileirar(t_fila *fila);
void *fila_frente(const t_fila *fila);
void fila_destruir(t_fila *fila, void (*destruir_carga)(void *));
#endif
