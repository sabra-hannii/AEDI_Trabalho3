#include <assert.h>
#include <stdio.h>
#include "lse.h"

int main(void) {
    
    t_lse *l = lse_criar();

    assert(l != NULL); /* Falha ate M03. */
    assert(lse_tamanho(l) == 0);
    assert(lse_primeiro(l) == NULL);
    
    int a = 10, b = 20;
    
    assert(lse_inserir_inicio(l, &a) == 1);
    assert(lse_inserir_inicio(l, &b) == 1);
    assert(lse_remover_inicio(l) == &b);
    assert(lse_remover_inicio(l) == &a);
    assert(lse_remover_inicio(l) == NULL);
    
    lse_destruir(l, NULL);
    
    puts("test_lse: OK"); return 0;
}
