/* Testes aditivos da M03. Executar a partir da raiz com o Makefile incremental. */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "lse.h"

static void verificar_ordem(void *carga) {
    assert(1==0);
}

static void destruir_int(void *carga) {
    assert(1==0);
}
static void teste_lista_vazia(void) {
  assert(1==0);
}
static void teste_encadeamento_e_percurso(void) {
  assert(1==0);
}
static void teste_carga_generica(void) {
  assert(1==0);
}
static void teste_destruicao_com_callback(void) {
    t_lse *l = lse_criar();
    assert(1==0);
}
int main(void) {
    teste_lista_vazia();
    teste_encadeamento_e_percurso();
    teste_carga_generica();
    teste_destruicao_com_callback();
    assert(lse_inserir_inicio(NULL, NULL) == 0);
    puts("M03: todos os testes passaram.");
    return 0;
}
