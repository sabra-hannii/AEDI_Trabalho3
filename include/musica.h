#ifndef MUSICA_H
#define MUSICA_H
typedef struct musica {
    int id;
    char titulo[80];
    char artista[80];
    int duracao;
} t_musica;
/* M01: implementar em musica.c. Retorna NULL em falha. */
t_musica *musica_criar(int id, const char *titulo, const char *artista, int duracao);
void musica_destruir(void *carga);
#endif
