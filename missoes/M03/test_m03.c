/* Testes aditivos da M03. Executar a partir da raiz com o Makefile incremental. */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "lse.h"

static const void *esperados[8];
static int visitas;
static int destruidos;

static void verificar_ordem(void *carga) {
    assert(visitas < 8);
    assert(carga == esperados[visitas]);
    visitas++;
}

static void destruir_int(void *carga) {
    assert(carga != NULL);
    free(carga);
    destruidos++;
}

static void teste_lista_vazia(void) {
    t_lse *l = lse_criar();
    assert(l != NULL);
    assert(lse_tamanho(l) == 0);
    assert(lse_primeiro(l) == NULL);

    visitas = 0;
    lse_percorrer(l, verificar_ordem);
    assert(visitas == 0);
    lse_destruir(l, NULL);
}

static void teste_encadeamento_e_percurso(void) {
    int a = 1, b = 2, c = 3;
    t_lse *l = lse_criar();
    assert(l != NULL);

    /* um elemento */
    assert(lse_inserir_inicio(l, &a) == 1);
    assert(lse_tamanho(l) == 1);
    assert(lse_primeiro(l) == &a);
    esperados[0] = &a;
    visitas = 0;
    lse_percorrer(l, verificar_ordem);
    assert(visitas == 1);

    /* tres elementos */
    assert(lse_inserir_inicio(l, &b) == 1);
    assert(lse_inserir_inicio(l, &c) == 1);
    assert(lse_tamanho(l) == 3);
    assert(lse_primeiro(l) == &c);
    esperados[0] = &c; esperados[1] = &b; esperados[2] = &a;
    visitas = 0;
    lse_percorrer(l, verificar_ordem);
    assert(visitas == 3);

    lse_destruir(l, NULL); 
}

static void teste_carga_generica(void) {
    int n1 = 10, n2 = 20;
    t_lse *li = lse_criar();
    assert(li != NULL);
    assert(lse_inserir_inicio(li, &n1) == 1);
    assert(lse_inserir_inicio(li, &n2) == 1);
    assert(lse_tamanho(li) == 2);
    assert(*(int *)lse_primeiro(li) == 20);
    esperados[0] = &n2; esperados[1] = &n1;
    visitas = 0;
    lse_percorrer(li, verificar_ordem);
    assert(visitas == 2);
    lse_destruir(li, NULL);

    typedef struct { int id; char titulo[16]; } faixa_t;
    faixa_t f1 = {11, "A"}, f2 = {22, "B"};
    t_lse *lf = lse_criar();
    assert(lf != NULL);
    assert(lse_inserir_inicio(lf, &f1) == 1);
    assert(lse_inserir_inicio(lf, &f2) == 1);
    assert(lse_tamanho(lf) == 2);
    assert(((faixa_t *)lse_primeiro(lf))->id == 22);
    esperados[0] = &f2; esperados[1] = &f1;
    visitas = 0;
    lse_percorrer(lf, verificar_ordem);
    assert(visitas == 2);
    lse_destruir(lf, NULL);
}

static void teste_destruicao_com_callback(void) {
    t_lse *l = lse_criar();
    assert(l != NULL);

    for (int i = 0; i < 3; i++) {
        int *p = malloc(sizeof *p);
        assert(p != NULL);
        *p = i;
        assert(lse_inserir_inicio(l, p) == 1);
    }
    assert(lse_tamanho(l) == 3);

    destruidos = 0;
    lse_destruir(l, destruir_int);
    assert(destruidos == 3); 
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