# Contratos dos TADs
Para **cada função**, preencher:
- Nome e assinatura:
- Pré-condições:
- Pós-condições:
- Valor de retorno em sucesso/falha:
- Quem aloca/libera a memória:
- Invariantes preservadas:
- Testes associados:

## Invariantes da LSE
- `tamanho >= 0`.
- `tamanho == 0` se e somente se `inicio == NULL`.
- Há exatamente `tamanho` nós alcançáveis a partir de `inicio`.
- O último nó aponta para `NULL` e não há ciclos.

### `musica_criar` — M01
- **Assinatura:** `t_musica *musica_criar(int id, const char *titulo, const char *artista, int duracao);`
- **Pré-condições:** `titulo` e `artista` são strings C terminadas em `'\0'` (ou `NULL`, caso tratado como falha). `id` e `duracao` não são validados. A unidade de `duracao` não está fixada em `musica.h`; adotar segundos (os testes usam `180`).
- **Pós-condições:** em sucesso, existe um `t_musica` no heap com `id` e `duracao` copiados e `titulo`/`artista` copiados por valor. Textos com mais de 79 caracteres são **truncados**, e o vetor termina sempre em `'\0'`.
- **Retorno:** ponteiro para a nova música; `NULL` se `titulo == NULL`, `artista == NULL` ou `malloc` falhar.
- **Memória:** aloca um único bloco (`sizeof(t_musica)`); as strings não têm alocação própria. O chamador recebe a posse e deve liberar com `musica_destruir` (na prática, a biblioteca).
- **Invariantes:** `titulo[79] == '\0'` e `artista[79] == '\0'` após qualquer chamada bem-sucedida.
- **Testes:** `tests/test_musica.c`. O teste de limites (textos de 199 caracteres, `titulo == NULL`) citado no diário da M01 ainda não está versionado em `tests/`.

### `musica_destruir` — M01
- **Assinatura:** `void musica_destruir(void *carga);`
- **Pré-condições:** `carga != NULL` e aponta para um `t_musica` criado por `musica_criar` e ainda não destruído. Nenhuma fila ou histórico pode guardar referência a essa música.
- **Pós-condições:** a memória é liberada; qualquer ponteiro para a música passa a ser inválido.
- **Retorno:** `void`. `carga == NULL` é violação de pré-condição (`assert`).
- **Memória:** é o único ponto que libera um `t_musica`. A assinatura `void *` é intencional, para servir de callback de `lse_destruir`.
- **Invariantes:** nenhuma (o tipo não tem estado compartilhado).
- **Testes:** `tests/test_musica.c` (chamada normal).

---

## TAD `t_lse`

### `lse_criar` — M02
- **Assinatura:** `t_lse *lse_criar(void);`
- **Pré-condições:** nenhuma.
- **Pós-condições:** lista vazia (`inicio == NULL`, `tamanho == 0`).
- **Retorno:** ponteiro para a lista; `NULL` se `malloc` falhar.
- **Memória:** aloca apenas o `t_lse`. O chamador libera com `lse_destruir`.
- **Invariantes:** estabelece as invariantes da lista vazia.
- **Testes:** `tests/test_lse.c`; M02 `teste_lista_vazia`; M03 `teste_lista_vazia`.

### `lse_tamanho` — M02
- **Assinatura:** `int lse_tamanho(const t_lse *lista);`
- **Pré-condições:** `lista != NULL`.
- **Pós-condições:** lista inalterada.
- **Retorno:** número de nós (`>= 0`); `0` em lista recém-criada. Custo O(1).
- **Memória:** nenhuma alocação ou liberação.
- **Invariantes:** apenas lê `tamanho`; depende da invariante "nós alcançáveis == `tamanho`".
- **Testes:** `tests/test_lse.c`; M02; M03 (após cada inserção); M04 (`conferir`).

### `lse_primeiro` — M02
- **Assinatura:** `void *lse_primeiro(const t_lse *lista);`
- **Pré-condições:** `lista != NULL`.
- **Pós-condições:** lista inalterada; o nó **não** é removido.
- **Retorno:** carga do primeiro nó; `NULL` se a lista estiver vazia (ou se a carga do primeiro nó for `NULL`; ver "Carga `NULL`").
- **Memória:** nenhuma; a posse da carga não muda.
- **Invariantes:** apenas lê `inicio`.
- **Testes:** `tests/test_lse.c`; M02; M03 (`teste_encadeamento_e_percurso`, `teste_carga_generica`). Não há teste de lista válida com carga `NULL`.

### `lse_inserir_inicio` — M03
- **Assinatura:** `int lse_inserir_inicio(t_lse *lista, void *carga);`
- **Pré-condições:** `lista != NULL` para haver sucesso (`NULL` é tolerado e vira falha). `carga` pode ser qualquer ponteiro, inclusive `NULL`, e deve permanecer válida enquanto estiver na lista.
- **Pós-condições:** em sucesso, o novo nó é o primeiro e aponta para o antigo primeiro; `tamanho` aumenta em 1; a ordem relativa dos demais nós não muda. Em falha, a lista fica intacta.
- **Retorno:** `1` sucesso; `0` se `lista == NULL` ou se faltar memória para o nó. Custo O(1).
- **Memória:** aloca um nó; guarda o **ponteiro** da carga, sem copiá-la. O chamador continua dono da carga.
- **Invariantes:** preserva todas (lista vazia → `inicio` passa a ser o novo nó, que tem `prox == NULL`).
- **Testes:** `tests/test_lse.c`; M03 (`teste_encadeamento_e_percurso`, `teste_carga_generica` e `lse_inserir_inicio(NULL, NULL) == 0`); M04 (`teste_remocao_e_reinsercao`, `teste_argumentos_invalidos`).

### `lse_inserir_fim` — M04
- **Assinatura:** `int lse_inserir_fim(t_lse *lista, void *carga);`
- **Pré-condições:** as mesmas de `lse_inserir_inicio`.
- **Pós-condições:** em sucesso, o novo nó é o último (`prox == NULL`) e o antecessor aponta para ele; `tamanho` aumenta em 1; em lista vazia, `inicio` aponta para o novo nó. Em falha, a lista fica intacta.
- **Retorno:** `1` sucesso; `0` se `lista == NULL` ou sem memória. Custo O(n): a M04 não tem ponteiro `fim` e percorre a cadeia.
- **Memória:** aloca um nó; não copia a carga.
- **Invariantes:** preserva todas.
- **Testes:** M04 (`teste_inserir_fim_e_buscar`, `teste_remover_cabeca_meio_cauda`, `teste_remocao_e_reinsercao`, `teste_generico_musicas`, `teste_argumentos_invalidos`).

### `lse_remover_inicio` — M04
- **Assinatura:** `void *lse_remover_inicio(t_lse *lista);`
- **Pré-condições:** nenhuma (lista `NULL` ou vazia é tolerada).
- **Pós-condições:** se havia nós, o primeiro é desligado, `inicio` avança para o seguinte e `tamanho` diminui em 1. Em lista vazia ou `NULL`, nada muda.
- **Retorno:** carga do nó removido; `NULL` se `lista == NULL` ou lista vazia. Custo O(1).
- **Memória:** libera **somente o nó**. A carga é devolvida e a posse passa ao chamador.
- **Invariantes:** preserva todas; ao remover o único nó, `inicio == NULL` e `tamanho == 0`.
- **Testes:** `tests/test_lse.c`; M04 (`teste_remover_inicio`, `teste_argumentos_invalidos`).

### `lse_buscar` — M04
- **Assinatura:** `void *lse_buscar(const t_lse *lista, const void *chave, t_comparador comparar);`
- **Pré-condições:** `comparar != NULL`; `comparar(carga, chave)` devolve `0` se casam e não modifica nenhum dos argumentos. `chave` é opaca para a lista. O comparador recebe a carga de cada nó, inclusive `NULL` se houver.
- **Pós-condições:** lista inalterada.
- **Retorno:** a **primeira** carga (do início para o fim) com `comparar(carga, chave) == 0`; `NULL` se não houver, se `lista == NULL` ou se `comparar == NULL`. Custo O(n).
- **Memória:** nenhuma; a carga continua na lista e com o mesmo dono.
- **Invariantes:** não altera nenhuma.
- **Testes:** M04 (`teste_inserir_fim_e_buscar`, `teste_remover_chave_duplicada`, `teste_generico_musicas`, `teste_argumentos_invalidos`).

### `lse_remover` — M04
- **Assinatura:** `void *lse_remover(t_lse *lista, const void *chave, t_comparador comparar);`
- **Pré-condições:** as mesmas de `lse_buscar`.
- **Pós-condições:** remove **apenas o primeiro** nó correspondente. Se era o primeiro, `inicio` avança; caso contrário, o antecessor passa a apontar para o sucessor. `tamanho` diminui em 1. Se não houver correspondência, nada muda.
- **Retorno:** carga removida; `NULL` se não encontrou, se `lista == NULL` ou se `comparar == NULL`. Custo O(n).
- **Memória:** libera **somente o nó**; a carga volta ao chamador, que decide se a destrói.
- **Invariantes:** preserva todas; remover o último nó da cadeia deixa o novo último com `prox == NULL`.
- **Testes:** M04 (`teste_remover_cabeca_meio_cauda`, `teste_remover_chave_duplicada`, `teste_remocao_e_reinsercao`, `teste_generico_musicas`, `teste_argumentos_invalidos`).

### `lse_percorrer` — M03
- **Assinatura:** `void lse_percorrer(const t_lse *lista, t_lse_visitar cb_visitar);`
- **Pré-condições:** nenhuma (`lista == NULL` ou `cb_visitar == NULL` é tolerado). Durante o percurso, o callback **não pode inserir, remover nem destruir nós** da mesma lista, pois o percurso lê `prox` depois do callback (comportamento indefinido).
- **Pós-condições:** lista inalterada pela própria função.
- **Retorno:** `void`. Chama `cb_visitar(carga)` uma vez por nó, do início ao fim, inclusive para cargas `NULL`. Em lista vazia, não chama o callback. Custo O(n).
- **Memória:** nenhuma.
- **Invariantes:** não altera nenhuma.
- **Testes:** M03 (`teste_lista_vazia`, `teste_encadeamento_e_percurso`, `teste_carga_generica`); M04 (`conferir`).

### `lse_destruir` — M02/M03
- **Assinatura:** `void lse_destruir(t_lse *lista, void (*destruir_carga)(void *));`
- **Pré-condições:** `lista` pode ser `NULL` (nada acontece) e não pode ser usada depois da chamada. `destruir_carga` pode ser `NULL`. Se não for, deve aceitar qualquer carga que esteja na lista.
- **Pós-condições:** todos os nós e o `t_lse` são liberados. Com `destruir_carga != NULL`, ele é chamado **uma vez por nó**, do início ao fim, antes de liberar aquele nó.
- **Retorno:** `void`.
- **Memória:** libera nós e lista sempre; libera cargas **só via callback**. Não presume que a carga esteja no heap. Com `destruir_carga == NULL`, as cargas ficam intactas e continuam sob responsabilidade de quem as criou.
- **Invariantes:** a lista deixa de existir; não há invariante a preservar.
- **Testes:** `tests/test_lse.c`; M02; M03 (`teste_destruicao_com_callback`, destruição com `NULL`); M04 (todas terminam com `lse_destruir(l, NULL)`).

### `lse_inserir_ordenado` — M05 *(planejado; proposta de contrato)*
- **Assinatura:** `int lse_inserir_ordenado(t_lse *lista, void *carga, t_comparador comparar);`
- **Pré-condições:** `lista` e `comparar` não nulos; a lista já está ordenada de forma crescente segundo `comparar`.
- **Pós-condições:** o nó é inserido na posição que mantém a ordem; em empate, **depois** dos iguais já existentes (inserção estável); `tamanho` aumenta em 1.
- **Retorno:** `1` sucesso; `0` se argumento inválido ou sem memória.
- **Memória:** aloca um nó; não copia a carga.
- **Invariantes:** preserva todas, mais "ordenada segundo `comparar`".
- **Testes:** a escrever na M05. O stub atual devolve `0`.
