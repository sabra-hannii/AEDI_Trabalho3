# Relatório de testes

Todos os testes abaixo foram executados e passaram. Os comandos usados estão na seção **Memória**.

| ID | Missão | Função/contrato | Entrada/cenário | Resultado esperado | Resultado obtido | Status |
|---|---|---|---|---|---|---|
| T01 | M01 | `musica_criar` | dados válidos (`1, "Teste", "Artista", 180`) | ponteiro não nulo; `id`, `titulo` e `duracao` corretos | conforme (`test_musica: OK`) | OK |
| T02 | M01 | `musica_destruir` | música criada em T01 | memória liberada sem erro | conforme | OK |
| T03 | M02 | `lse_criar` | chamada sem argumentos | ponteiro não nulo | conforme | OK |
| T04 | M02 | `lse_tamanho` | lista recém-criada | retorna 0 | conforme | OK |
| T05 | M02 | `lse_primeiro` | lista recém-criada | retorna `NULL` | conforme | OK |
| T06 | M02 | `lse_destruir` | lista vazia, sem callback | sem erro | conforme (`M02: teste de contrato passou.`) | OK |
| T10 | M03 | `lse_inserir_inicio` | 1 elemento em lista vazia | retorna 1; tamanho 1; `lse_primeiro` = elemento | conforme | OK |
| T11 | M03 | `lse_inserir_inicio` | inserir a, b, c | retorna 1 a cada inserção; tamanho 3; `lse_primeiro` = c | conforme | OK |
| T12 | M03 | `lse_percorrer` | lista vazia | callback nunca chamado | conforme | OK |
| T13 | M03 | `lse_percorrer` | lista com c, b, a | callback chamado 3 vezes, na ordem c, b, a (inversa à inserção) | conforme | OK |
| T14 | M03 | `lse_inserir_inicio`, `lse_primeiro` | cargas `int` e struct na mesma lista | ponteiros e valores corretos, ordem inversa à inserção | conforme | OK |
| T15 | M03 | `lse_destruir` | 3 cargas no heap + callback `destruir_int` | callback chamado exatamente 3 vezes | conforme | OK |
| T16a | M03 | `lse_destruir` | `destruir_carga == NULL`, cargas em variáveis locais | cargas intactas; sem falha | falha de segmentação: `destruir(atual->carga)` chamava um ponteiro de função nulo (ver Problemas, Erro 01) | FALHOU |
| T16b | M03 | `lse_destruir` | `destruir_carga == NULL`, cargas em variáveis locais (reteste após a correção `if (destruir != NULL)`) | cargas intactas; sem falha | conforme | OK |
| T17 | M03 | `lse_inserir_inicio` | `lista == NULL` | retorna 0 | conforme | OK |
| T20 | M04 | `lse_inserir_fim` | lista vazia e depois não vazia (a, b, c) | retorna 1; ordem a, b, c; tamanho 1, 2, 3 | conforme | OK |
| T21 | M04 | `lse_buscar` | chaves do primeiro, do meio e do último | devolve o próprio ponteiro da carga; lista inalterada | conforme | OK |
| T22 | M04 | `lse_buscar` | chave ausente | retorna `NULL`; lista inalterada | conforme | OK |
| T23 | M04 | `lse_remover` | remover do meio, do fim, do início e o único elemento | devolve a carga; ligações e tamanho corretos a cada passo; lista fica vazia | conforme | OK |
| T24 | M04 | `lse_remover` | chave inexistente / lista vazia | retorna `NULL`; tamanho inalterado | conforme | OK |
| T25 | M04 | `lse_remover_inicio` | lista vazia; depois 3 elementos (dois com valor 5) até esvaziar | `NULL` na lista vazia; depois devolve a, b, c nessa ordem; volta a ficar vazia | conforme | OK |
| T26 | M04 | `lse_buscar`, `lse_remover` | lista com chave duplicada (7, 9, 7) | atuam só na primeira ocorrência | conforme | OK |
| T27 | M04 | `lse_remover`, `lse_inserir_fim`, `lse_inserir_inicio` | esvaziar a lista e reinserir; remover a cauda e inserir no fim; misturar início e fim | encadeamento íntegro; ordem correta | conforme | OK |
| T28 | M04 | `lse_buscar`, `lse_remover` | `t_musica` comparada por `id` | devolvem a carga correta | conforme | OK |
| T29 | M04 | `lse_inserir_fim`, `lse_buscar`, `lse_remover`, `lse_remover_inicio` | lista `NULL`; lista vazia; comparador `NULL` | 0 ou `NULL`, sem acesso inválido; lista intacta | conforme | OK |

## Casos-limite
- **Estrutura vazia:** coberta em T03 a T06 (`lse_criar`, `lse_tamanho`, `lse_primeiro`, `lse_destruir`), T12 (`lse_percorrer`), T24 (`lse_remover`) e T25 (`lse_remover_inicio`). Uma lista esvaziada por remoções volta a se comportar como lista nova (T25, T27).
- **Estrutura com um elemento:** coberta em T10 (`lse_inserir_inicio`), em T23 e T25 (remoção do único elemento, que deixa a lista vazia e consistente) e em T27 (reinserção depois de esvaziar).
- **Chave inexistente:** coberta em T22 (`lse_buscar`) e em T24 e T26 (`lse_remover` devolve `NULL` e não altera a lista).
- **Chave duplicada:** T26 confirma que `lse_buscar` e `lse_remover` atuam só na primeira ocorrência.
- **Argumentos inválidos:** T17 e T29 cobrem lista `NULL` e comparador `NULL`. `lse_destruir(NULL, ...)` também é aceito e não faz nada, conforme o contrato.
- **Falha de alocação (estratégia de simulação):** não foi testada de forma automática. As opções avaliadas para simular são:
  - embrulhar o `malloc` com `-Wl,--wrap=malloc`, com uma variável de controle que faz a N-ésima chamada devolver `NULL`;
  - limitar a memória do processo com `ulimit -v`.

  O comportamento esperado, conforme os contratos, é `lse_criar` devolver `NULL` e `lse_inserir_inicio` e `lse_inserir_fim` devolverem 0, sem alterar a lista.
- **Limitação conhecida:** `lse_primeiro` devolve `NULL` tanto para lista vazia quanto para um primeiro nó com carga `NULL` (ver "Carga `NULL`" nos contratos). Por isso os testes de `lse_buscar` e `lse_remover` não usam carga `NULL`, e só `lse_tamanho` diferencia os dois casos.

## Memória
**Ferramentas:** `gcc` com `-std=c11 -Wall -Wextra -Wpedantic -g`, `make` (Makefile principal e `Makefile.incremental` de cada missão) e AddressSanitizer/UBSan (`-fsanitize=address,undefined`) para diagnosticar acessos inválidos e vazamentos.

**Comandos de compilação e execução:**

```sh
make build/test_musica && ./build/test_musica                       # M01
make -f missoes/M02/Makefile.incremental test_m02                   # M02
make -f missoes/M03/Makefile.incremental test_m03                   # M03
make -f missoes/M04/Makefile.incremental test_m04                   # M04
```

**Verificação de memória (exemplo, M04):**

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude -fsanitize=address,undefined \
    missoes/M04/test_m04.c src/lse.c -o build/m04 && ./build/m04
```

## Problemas encontrados e corrigidos

### M01
Nenhum problema registrado.

### M02
Nenhum problema registrado.

### M03

**Erro 01 — Acesso de memória inválido em `lse_destruir`.**
A linha `destruir(atual->carga)` chamava a função `destruir`, recebida como parâmetro. O código não previa o caso `destruir == NULL`, e a chamada a um ponteiro de função nulo causava erro (falha de segmentação) quando os testes da M03 chamavam `lse_destruir(l, NULL)`.

**Correção:** adicionada a condição `if (destruir != NULL) {` antes da chamada ao callback, conforme o contrato (o parâmetro `destruir_carga` é opcional).

### M04
Nenhum problema registrado.