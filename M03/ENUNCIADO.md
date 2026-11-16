# MiniPlayer — Missão 03: Construção e percurso da lista

**ICC002 — Algoritmos e Estruturas de Dados I**  
**Data:** segunda-feira, 16/11/2026 | **Modalidade:** duplas | **Duração:** 2 horas-aula

## Situação-problema
Na M02, a dupla definiu a interface e os contratos do TAD Lista. Agora, o MiniPlayer precisa manter uma sequência dinâmica de cargas sem expor os nós à aplicação. Como criar nós, encadeá-los e visitar todos os elementos sem conhecer o tipo da carga?

## Objetivos
- Compreender `t_elem` como detalhe interno de `lse.c` e `t_lse` como tipo opaco.
- Alocar e encadear nós, atualizar `inicio` e `tamanho`.
- Percorrer a lista usando um callback sem expor `t_elem`.
- Escrever e executar testes de comportamento, incluindo casos-limite.
- Registrar contratos, invariantes e decisões de memória.

## Contratos a implementar
No arquivo **já existente** `src/lse.c`, preservar a implementação da M02 e implementar ou revisar:

1. `lse_tamanho(lista)`: para lista válida, retorna o número de nós; para `NULL`, adotar o contrato já documentado pela dupla.
2. `lse_primeiro(lista)`: devolve a carga do primeiro nó ou `NULL` se a lista estiver vazia.
3. `lse_inserir_inicio(lista, carga)`: cria um nó, aponta-o para o antigo primeiro, atualiza o início e incrementa o tamanho. Retorna 1 no sucesso e 0 na falha; `lista == NULL` deve falhar. A M03 permite carga `NULL` (um nó ainda é um nó), mas a dupla deve registrar essa decisão.
4. `lse_percorrer(lista, visitar)`: visita os nós em ordem do início ao fim; para lista vazia não invoca o callback. Para `lista == NULL` ou `visitar == NULL`, não faz nada.
5. `lse_destruir(lista, destruir_carga)`: libera todos os nós e a lista; se `destruir_carga != NULL`, chama-a uma vez para cada carga antes de liberar o nó. Não presume que a carga foi alocada dinamicamente.

**Alteração manual de interface:** acrescentar ao `include/lse.h` existente a declaração:

```c
typedef void(*t_lse_visitar)(void* carga);
void lse_percorrer(const t_lse *lista, t_visitar cb_visitar);
```

Não substituir o arquivo de cabeçalho: acrescentar apenas essa declaração se ainda não existir.

## Invariantes
- Lista vazia: `inicio == NULL` e `tamanho == 0`.
- Lista não vazia: `inicio != NULL` e `tamanho > 0`.
- O último nó tem `prox == NULL`.
- O número de nós alcançáveis a partir de `inicio` é igual a `tamanho`.
- Não existem ciclos na cadeia.

## Como executar os testes
Na raiz do repositório:

```sh
make -f missoes/M03/Makefile.incremental test_m03
```

Se a integração opcional `-include $(wildcard missoes/M*/Makefile.incremental)` já foi acrescentada ao Makefile principal, também é possível executar `make test_m03`.


**Importante:** o teste é aditivo; não modifica `src/`, `include/`, `tests/`, `docs/` ou o `Makefile` principal. O compilador pode falhar inicialmente por ausência da nova função de percurso: isso é esperado até a dupla declarar e implementar a operação.

## Testes obrigatórios
- Lista vazia: tamanho 0, primeiro `NULL`, percurso sem visitas.
- Inserção de um elemento: tamanho 1, primeiro correto, percurso com uma visita.
- Inserção de três elementos: percurso em ordem inversa à inserção (LIFO na cabeça).
- Independência da carga: testes com `int` e outro tipo, como `t_musica`.
- Destruição: liberar os nós sem liberar cargas automáticas; testar separadamente callback destrutor com cargas alocadas no heap.
- Robustez: `lse_inserir_inicio(NULL, ...)` falha sem causar acesso inválido.

## Documentação (não substituir arquivos)
Acrescentar seções identificadas como **M03** a `docs/arquitetura.md`, `docs/contratos.md`, `docs/diario-de-bordo.md` e `docs/relatorio-testes.md`. Registrar: desenho de encadeamento; contrato de `lse_percorrer`; decisão sobre carga `NULL`; resultados dos testes e problemas encontrados.

## Critérios de aceitação
- Código compila com `-std=c11 -Wall -Wextra -Wpedantic`.
- `make -f missoes/M03/Makefile.incremental test_m03` termina com sucesso.
- Os invariantes permanecem válidos após cada inserção.
- Nenhuma definição de `t_elem` é movida para `lse.h`.
- A dupla explica quem libera o nó e quem libera a carga.
- A documentação da M03 foi acrescentada sem apagar registros anteriores.

## Limites desta missão
Não implementar busca por chave, remoção por chave, inserção no fim ou inserção ordenada: essas operações pertencem às M04 e M05. `lse_remover_inicio` também pode ficar para a M04.
