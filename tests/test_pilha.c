#include <assert.h>
#include <stdio.h>
#include "pilha.h"
int main(void) {
    t_pilha *p = pilha_criar(); assert(p != NULL);
    int a=1,b=2; assert(pilha_empilhar(p,&a)); assert(pilha_empilhar(p,&b));
    assert(pilha_desempilhar(p)==&b); assert(pilha_desempilhar(p)==&a);
    assert(pilha_desempilhar(p)==NULL);
    pilha_destruir(p,NULL); puts("test_pilha: OK"); return 0;
}
