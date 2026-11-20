/* M04: testes incrementais. Não modificar asserções para ocultar defeitos. */
#include <assert.h>
#include <stdio.h>
#include "lse.h"
#include "musica.h"

static int comparar_int(const void *carga, const void *chave) {
    int a = *(const int *)carga, b = *(const int *)chave;
    return (a > b) - (a < b);
}
typedef struct { int id; char titulo[32]; } musica_t;
static int comparar_musica_id(const void *carga, const void *chave) {
    int a = ((const musica_t *)carga)->id;
    int b = *(const int *)chave;
    return (a > b) - (a < b);
}
static const void *esperados[8];
static int visitas;
static void verificar(void *carga) {
    assert(visitas < 8);
    assert(carga == esperados[visitas]);
    visitas++;
}
static void conferir(t_lse *l, int n) {
    assert(lse_tamanho(l) == n);
    visitas = 0;
    lse_percorrer(l, verificar);
    assert(visitas == n);
}
static void teste_inserir_fim_e_buscar(void) {
    int a=10,b=20,c=30,ausente=99;
    t_lse *l=lse_criar(); assert(l);

    /* inserção no fim em lista vazia */
    assert(lse_inserir_fim(l,&a)==1);
    esperados[0]=&a; conferir(l,1);

    /* inserção no fim em lista não vazia */
    assert(lse_inserir_fim(l,&b)==1);
    esperados[1]=&b; conferir(l,2);
    assert(lse_inserir_fim(l,&c)==1);
    esperados[2]=&c; conferir(l,3);

    /* busca */
    assert(lse_buscar(l,&a,comparar_int)==&a);
    assert(lse_buscar(l,&b,comparar_int)==&b);
    assert(lse_buscar(l,&c,comparar_int)==&c);

    /* busca de chave ausente */
    assert(lse_buscar(l,&ausente,comparar_int)==NULL);

    /* buscar não modifica a lista */
    conferir(l,3);
    lse_destruir(l,NULL);
}
static void teste_remover_cabeca_meio_cauda(void) {
    int a=10,b=20,c=30,d=40;
    t_lse *l=lse_criar(); assert(l);
    assert(lse_inserir_fim(l,&a)==1);
    assert(lse_inserir_fim(l,&b)==1);
    assert(lse_inserir_fim(l,&c)==1);
    assert(lse_inserir_fim(l,&d)==1);
    esperados[0]=&a; esperados[1]=&b; esperados[2]=&c; esperados[3]=&d;
    conferir(l,4);

    // remover do meio
    assert(lse_remover(l,&b,comparar_int)==&b);
    esperados[0]=&a; esperados[1]=&c; esperados[2]=&d;
    conferir(l,3);
    assert(lse_buscar(l,&b,comparar_int)==NULL);

    // remover do fim
    assert(lse_remover(l,&d,comparar_int)==&d);
    esperados[0]=&a; esperados[1]=&c;
    conferir(l,2);

    // remover do inicio
    assert(lse_remover(l,&a,comparar_int)==&a);
    esperados[0]=&c;
    conferir(l,1);

    // remover o único elemento
    assert(lse_remover(l,&c,comparar_int)==&c);
    conferir(l,0);

    // chave inexistente / lista vazia
    assert(lse_remover(l,&b,comparar_int)==NULL);
    conferir(l,0);

    lse_destruir(l,NULL);
}
static void teste_remover_inicio(void) {
    int a=5,b=5,c=8,ausente=99;
    t_lse *l=lse_criar(); assert(l);
    assert(lse_remover_inicio(l)==NULL);
    assert(lse_inserir_fim(l,&a)==1);
    assert(lse_inserir_fim(l,&b)==1);
    assert(lse_inserir_fim(l,&c)==1);

    esperados[0]=&a; esperados[1]=&b; esperados[2]=&c;
    conferir(l,3);

    /* a e b têm o mesmo valor (5), mas são cargas distintas */
    assert(lse_remover_inicio(l)==&a);
    esperados[0]=&b; esperados[1]=&c;
    conferir(l,2);

    assert(lse_remover_inicio(l)==&b);
    esperados[0]=&c;
    conferir(l,1);

    /* remover o único elemento */
    assert(lse_remover_inicio(l)==&c);
    conferir(l,0);

    /* lista voltou a ficar vazia */
    assert(lse_remover_inicio(l)==NULL);
    assert(lse_buscar(l,&ausente,comparar_int)==NULL);
    conferir(l,0);

    lse_destruir(l,NULL);
}

/* Chave duplicada */
static void teste_remover_chave_duplicada(void) {
    int a=7,b=7,c=9;
    t_lse *l=lse_criar(); assert(l);
    assert(lse_inserir_fim(l,&a)==1);
    assert(lse_inserir_fim(l,&c)==1);
    assert(lse_inserir_fim(l,&b)==1);

    assert(lse_buscar(l,&a,comparar_int)==&a);   
    assert(lse_remover(l,&a,comparar_int)==&a);  
    esperados[0]=&c; esperados[1]=&b;
    conferir(l,2);

    assert(lse_remover(l,&a,comparar_int)==&b);  
    esperados[0]=&c;
    conferir(l,1);
    assert(lse_remover(l,&a,comparar_int)==NULL);
    lse_destruir(l,NULL);
}

/* Remoção seguida de reinserção */
static void teste_remocao_e_reinsercao(void) {
    int a=1,b=2,c=3;
    t_lse *l=lse_criar(); assert(l);
    assert(lse_inserir_fim(l,&a)==1);
    assert(lse_inserir_fim(l,&b)==1);

    /* esvazia por completo e reinsere */
    assert(lse_remover(l,&a,comparar_int)==&a);
    assert(lse_remover(l,&b,comparar_int)==&b);
    conferir(l,0);
    assert(lse_inserir_fim(l,&c)==1);
    esperados[0]=&c; conferir(l,1);

    /* remove a cauda e reinsere no fim: o fim tem que ter sido atualizado */
    assert(lse_inserir_fim(l,&a)==1);
    assert(lse_remover(l,&a,comparar_int)==&a);
    assert(lse_inserir_fim(l,&b)==1);
    esperados[0]=&c; esperados[1]=&b;
    conferir(l,2);

    /* mistura início e fim */
    assert(lse_inserir_inicio(l,&a)==1);
    esperados[0]=&a; esperados[1]=&c; esperados[2]=&b;
    conferir(l,3);
    lse_destruir(l,NULL);
}
static void teste_generico_musicas(void) {
    t_musica a={11,"A","",0}, b={22,"B","",0};
    int chave=22;
    t_lse *l=lse_criar(); assert(l);
    assert(lse_inserir_fim(l,&a)==1);
    assert(lse_inserir_fim(l,&b)==1);
    assert(lse_buscar(l,&chave,comparar_musica_id)==&b);
    assert(lse_remover(l,&chave,comparar_musica_id)==&b);
    esperados[0]=&a; conferir(l,1);
    lse_destruir(l,NULL);
}

static void teste_argumentos_invalidos(void) {
    int x=1;
    assert(lse_inserir_fim(NULL,&x)==0);
    assert(lse_buscar(NULL,&x,comparar_int)==NULL);
    assert(lse_remover(NULL,&x,comparar_int)==NULL);
    assert(lse_remover_inicio(NULL)==NULL);

    t_lse *l=lse_criar(); assert(l);
    assert(lse_buscar(l,&x,comparar_int)==NULL);
    assert(lse_remover(l,&x,comparar_int)==NULL);
    assert(lse_inserir_inicio(l,&x)==1);
    assert(lse_remover(l,&x,NULL)==NULL);
    esperados[0]=&x; conferir(l,1);
    lse_destruir(l,NULL);
}

int main(void) {
    teste_inserir_fim_e_buscar();
    teste_remover_cabeca_meio_cauda();
    teste_remover_inicio();
    teste_remover_chave_duplicada();
    teste_remocao_e_reinsercao();
    teste_generico_musicas();
    teste_argumentos_invalidos();
    puts("M04: todos os testes passaram.");
    return 0;
}