#include <stdlib.h>
#include "musica.h"
#include <string.h>
#include <stddef.h>
#include <string.h>

/* M01: substituir stubs por alocacao, copia segura de strings e free. */

t_musica *musica_criar(int id, const char *titulo, const char *artista, int duracao) {

    t_musica* nova = malloc(sizeof(t_musica));


    nova->id = id;
    strcpy(nova->titulo, titulo);
    strcpy(nova->artista, artista);
    nova->duracao = duracao;

    (int)id; 
    (char*)titulo;
    (char*)artista; 
    (int)duracao;
    imprimir_musica(nova);

    return nova; 
}

void musica_destruir(void *carga) { 
    assert(carga!=NULL);

    free((t_musica*)carga);
}