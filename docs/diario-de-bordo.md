# Diário de bordo
## Missão M01 — 11/11

- **Integrantes e papéis:**
  - SEBASTIAN LIMA GUEDES — CODIFICAÇÃO
  - DAVI TELES DE MORAES — REVISÃO

- **Objetivo:**  
  Substituir os stubs de `src/musica.c` por uma implementação do TAD `t_musica`: alocar com `malloc`, preencher os campos (id, título, artista, duração) e liberar com `free`.

- **O que implementamos:**
  1. `musica_criar`: aloca um `t_musica` com `malloc`, copia id e duração, e copia título e artista com a função auxiliar `copiar_texto`, que limita o tamanho e sempre termina com `'\0'`. Devolve `NULL` se `titulo` ou `artista` forem `NULL` ou se o `malloc` falhar.
  2. `musica_destruir`: valida a carga com `assert` e libera a memória com `free`.
  3. No kit inicial, as duas funções eram stubs (`musica_criar` devolvia `NULL`). Os arquivos `include/musica.h` e `tests/test_musica.c` não foram alterados.

- **Decisão técnica e justificativa:**  
  A assinatura `musica_destruir(void *carga)` foi mantida, para poder ser usada depois como callback de `lse_destruir`.

  A música é alocada no heap e devolvida por ponteiro, de modo que fila, histórico e lista possam apenas referenciá-la (a biblioteca é a dona).

  As strings são copiadas com `strncpy` mais terminador `'\0'` explícito, porque `strcpy` estoura os vetores `titulo[80]` e `artista[80]` com textos grandes. Textos maiores são truncados em 79 caracteres.

- **Problema encontrado e solução:**

  A primeira versão do `musica.c` não compilava:

  1. `musica_criar` chamava `imprimir_musica(nova)`, função que não existe no projeto (`undefined reference to 'imprimir_musica'`). **Solução:** a chamada foi removida.
  2. `musica_destruir` usava `assert` sem `#include <assert.h>`. **Solução:** o include foi adicionado.

- **Evidências de testes:**

  - **Kit original:** `test_musica` falha com `Assertion 'm != NULL' failed`, como esperado para o stub.
  - **Teste extra de limites** (feito à parte, com AddressSanitizer e UBSan, sem erros): título e artista com 199 caracteres ficam truncados em 79, e `musica_criar(3, NULL, "x", 1)` devolve `NULL`.

- **Próxima ação:**  
  Seguir para a M02: definir contratos do TAD lista e implementar `lse_criar`, `lse_tamanho`, `lse_primeiro` e `lse_destruir`.

---
## Missão M02 — 13/11

- **Integrantes e papéis:**
  - DAVI TELES DE MORAES — CODIFICAÇÃO
  - SEBASTIAN LIMA GUEDES — REVISÃO

- **Objetivo:**
  Implementar em `src/lse.c` a criação de lista vazia, as consultas (`lse_tamanho`, `lse_primeiro`) e a destruição de lista, sem substituir o código da M01, e documentar contratos e invariantes da LSE.

- **O que implementamos:**
  1. `lse_criar`: aloca `t_lse` com `malloc`, inicializa `inicio = NULL` e `tamanho = 0`, e devolve `NULL` se a alocação falhar.
  2. `lse_tamanho`: devolve `l->tamanho` (0 para lista recém-criada).
  3. `lse_primeiro`: devolve a carga do primeiro nó ou `NULL` se a lista estiver vazia.
  4. `lse_destruir`: percorre os nós, libera cada um e depois libera a lista; o callback de destruição de carga é opcional.
  5. Em `include/lse.h`, removemos a definição de `struct lse` e de `t_elem`, mantendo só `typedef struct lse t_lse;`.

- **Decisão técnica e justificativa:**
  O `t_lse` é tipo opaco: a definição da struct e de `t_elem` fica só em `lse.c`, então a aplicação não enxerga nós nem campos. A carga é `void *`, e a lista não depende de `t_musica`. A lista possui os nós, mas não as cargas, a menos que `lse_destruir` receba um callback. Para `lista == NULL`, `lse_tamanho` e `lse_primeiro` falham por `assert` (violação de pré-condição), enquanto `lse_destruir(NULL, ...)` não faz nada.

- **Problema encontrado e solução:**
  1. A compilação falhava com `error: redefinition of 'struct lse'`, porque a struct estava definida em `lse.h` e de novo em `lse.c`. Isso também quebrava o tipo opaco. **Solução:** removemos a definição do `.h`.
  2. `lse_destruir` chamava `destruir(...)` sem checar se era `NULL`, então `lse_destruir(l, NULL)` travava. **Solução:** só chama o callback se ele não for `NULL`.
    
- **Evidências de testes:**
  - **Antes:** `make -f missoes/M02/Makefile.incremental test_m02` falhava na compilação (`redefinition of 'struct lse'`).
  - **Depois:** o teste compila e imprime `M02: teste de contrato passou.`
  - Rodamos também com AddressSanitizer e UBSan, sem erros ou vazamentos.
- **Próxima ação:**
  M03: implementar `lse_inserir_inicio` e `lse_percorrer` e rodar `test_m03`.

---

## Missão M03 — 16/11

- **Integrantes e papéis:**
  - SEBASTIAN LIMA GUEDES — CODIFICAÇÃO
  - DAVI TELES DE MORAES — REVISÃO

- **Objetivo:**
  Implementar a construção e o percurso da lista: `lse_inserir_inicio`, `lse_percorrer` e `lse_destruir` com callback opcional, mantendo `t_elem` privado em `lse.c`.

- **O que implementamos:**
  1. `criar_elem_lse`: função auxiliar (`static`) que aloca um nó com `malloc`, guarda a carga e devolve `NULL` se a alocação falhar.
  2. `lse_inserir_inicio`: cria o nó, aponta-o para o antigo primeiro, atualiza `inicio` e incrementa `tamanho`. Retorna 1 no sucesso e 0 se `lista == NULL` ou se faltar memória.
  3. `lse_percorrer`: visita os nós do início ao fim chamando `cb_visitar(carga)`; não faz nada se a lista ou o callback forem `NULL`.
  4. `lse_destruir` (feita na M02) já libera todos os nós e chama o callback, se existir, uma vez por carga.
  5. `t_lse_visitar` e `lse_percorrer` já estavam declarados no `lse.h`, então o cabeçalho não precisou mudar.
  6. Escrevemos os testes em `missoes/M03/test_m03.c`, que no kit eram um esqueleto com `assert(1==0)`.

- **Decisão técnica e justificativa:**
  O percurso usa callback para que a lista não conheça o tipo da carga e `t_elem` continue privado. Decidimos **permitir carga `NULL`** em `lse_inserir_inicio`, como o enunciado permite, porque um nó ainda é um nó; essa decisão cria uma ambiguidade em buscas e remoções, que tratamos na M04. **Quem libera o quê:** a lista libera os nós; a carga é liberada por quem a alocou, ou pelo callback passado a `lse_destruir`.

- **Problema encontrado e solução:**
  1. `criar_elem_lse` fazia `t_elem *novo = (sizeof(t_elem));`, atribuindo um número a um ponteiro, sem `malloc`. **Solução:** `malloc(sizeof(t_elem))` com verificação de `NULL`.
  2. `lse_inserir_inicio` chamava `lse_criar()` (que cria uma *lista*) em vez de criar um nó, e ignorava a carga recebida. **Solução:** usar `criar_elem_lse(carga)` e religar `novo->prox = lista->inicio`.


- **Evidências de testes:**
  - **Antes:** `make -f missoes/M03/Makefile.incremental test_m03` falhava na compilação (`redefinition of 'struct lse'`, corrigido na M02). Depois disso, o esqueleto do kit falhava de propósito com `assert(1==0)`.
  - **Depois:** `M03: todos os testes passaram.`
  - Testes cobertos: lista vazia (tamanho 0, primeiro `NULL`, percurso sem visitas), um elemento, três elementos em ordem inversa à inserção, carga `int` e carga em struct semelhante a `t_musica`, carga `NULL`, destruição sem callback e com callback (chamado 3 vezes para 3 cargas), `lse_inserir_inicio(NULL, ...)`, `lse_percorrer(NULL, ...)` e `lse_percorrer(l, NULL)`.
  - Regressão: `test_m02` continua passando.
  - Execução com AddressSanitizer e UBSan: sem erros nem vazamentos.

- **Próxima ação:**
  M04: corrigir `lse_remover_inicio` e `lse_remover`, revisar `lse_buscar` e `lse_inserir_fim`, e rodar `test_m04`.

---
