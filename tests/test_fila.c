#include <assert.h>
#include <stdio.h>
#include "fila.h"
int main(void) {
    t_fila *f = fila_criar(); assert(f != NULL);
    int a=1,b=2; assert(fila_enfileirar(f,&a)); assert(fila_enfileirar(f,&b));
    assert(fila_desenfileirar(f)==&a); assert(fila_desenfileirar(f)==&b);
    assert(fila_desenfileirar(f)==NULL);
    fila_destruir(f,NULL); puts("test_fila: OK"); return 0;
}
