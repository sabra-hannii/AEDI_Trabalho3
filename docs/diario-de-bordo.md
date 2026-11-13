# Diário de bordo
## Missão M01 — 11/11

- **Integrantes e papéis:**
  - SEBASTIAN LIMA GUEDES — CODIFICAÇÃO
  - DAVI TELES DE MORAES — REVISÃO

- **Objetivo:**  
  Substituir os stubs de `src/musica.c` por uma implementação do TAD `t_musica`: alocar com `malloc`, preencher os campos (id, título, artista, duração) e liberar com `free`.

- **O que implementamos:**
  1. `musica_criar`: aloca um `t_musica` com `malloc` e copia id, título, artista e duração para a struct.
  2. `musica_destruir`: valida a carga com `assert` e libera a memória com `free`.
  3. No kit inicial, as duas funções eram stubs (`musica_criar` devolvia `NULL`). Os arquivos `include/musica.h` e `tests/test_musica.c` não foram alterados, a não ser por linhas em branco.

- **Decisão técnica e justificativa:**  
  A assinatura `musica_destruir(void *carga)` foi mantida, para poder ser usada depois como callback de `lse_destruir`.

  A música é alocada no heap e devolvida por ponteiro, de modo que fila, histórico e lista possam apenas referenciá-la (a biblioteca é a dona).

- **Problema encontrado e solução:**

  Ao compilar, o `musica.c` apresentou os seguintes problemas:

  1. `musica_criar` chama `imprimir_musica(nova)`, função que não existe no projeto. Sem declaração, a ligação falha (`undefined reference to 'imprimir_musica'`).
  2. `musica_destruir` usa `assert`, mas falta `#include <assert.h>`.
  3. O retorno do `malloc` não é verificado. Com falha de memória, o programa acessaria `NULL`, e o contrato do header diz que a função "retorna NULL em falha".
  4. `strcpy` não limita o tamanho. Títulos ou artistas com 80 caracteres ou mais estouram os vetores `titulo[80]` e `artista[80]`. O Guia do Estudante pede cópia segura de strings.
  5. As linhas `(int)id;`, `(char*)titulo;` etc. não têm efeito (aviso `-Wunused-value`) e sobraram da remoção dos `(void)` do stub. Há também `#include <string.h>` duplicado.

  **Correção prevista:** remover a chamada a `imprimir_musica` e as linhas sem efeito, incluir `#include <assert.h>`, retornar `NULL` se `malloc` falhar, copiar as strings com `snprintf` ou `strncpy` mais terminador `'\0'`, e tratar entradas `NULL`.

- **Evidências de testes:**

  - **Kit original:** `test_musica` falha com `Assertion 'm != NULL' failed`, como esperado para o stub.
  - **Repositório atual:** `make build/test_musica` não conclui a ligação (`undefined reference to 'imprimir_musica'` e `assert`), então o `test_musica` ainda não chega a executar.
  - O `build/test_musica` versionado no Git é um binário antigo e não vale como evidência.

  A M01 está implementada, mas ainda não passa no teste.

- **Próxima ação:**  
  Aplicar as correções acima, recompilar com `make build/test_musica && ./build/test_musica` e registrar a saída `test_musica: OK`.

---
> Duplicar esta seção a cada missão e alternar os papéis na dupla.
