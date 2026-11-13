# MiniPlayer — ICC002 (2026/2)
Projeto integrador progressivo, em duplas, em C. Reprodução **simulada**.

## Compilação
`make` e `./build/miniplayer`.

## Testes
`make test`. **ATENÇÃO:** os testes estão preparados para falhar até que os stubs sejam implementados. Isso é intencional. Comece com `make build/test_musica && ./build/test_musica`.

## Contratos
- `void *carga` é genérico; a lista não conhece `t_musica`.
- A lista possui os nós, **não** as cargas, salvo quando `lse_destruir` recebe callback destruidor.
- Remover devolve a carga e libera apenas o nó.
- Pilha e fila reutilizam `lse_*`, sem manipular `t_elem`.
- Biblioteca possui as músicas; histórico e fila só as referenciam.
- Antes de liberar uma música, remover referências a ela de fila e histórico.

## Como documentar
Preencher `docs/arquitetura.md`, `docs/contratos.md`, `docs/diario-de-bordo.md` e `docs/relatorio-testes.md` a cada missão. Ver `GUIA_ESTUDANTE.md`.
