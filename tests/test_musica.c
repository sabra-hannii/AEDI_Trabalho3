#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "musica.h"
int main(void) {
    t_musica *m = musica_criar(1, "Teste", "Artista", 180);
    assert(m != NULL); /* Falha ate M01 ser implementada. */
    assert(m->id == 1 && strcmp(m->titulo, "Teste") == 0);
    assert(m->duracao == 180);
    musica_destruir(m);
    puts("test_musica: OK");
    return 0;
}
