/* M02: teste adicional, sem modificar arquivos existentes. */
#include <assert.h>
#include <stdio.h>
#include "lse.h"

static void teste_lista_vazia(void) {
    t_lse *l = lse_criar();
    assert(l != NULL && "lse_criar deve retornar uma lista valida");
    assert(lse_tamanho(l) == 0);
    assert(lse_primeiro(l) == NULL);
    lse_destruir(l, NULL);
}

int main(void) {
    teste_lista_vazia();
    puts("M02: teste de contrato passou.");
    return 0;
}
