# MiniPlayer — Missão 04: Inserção, busca e remoção

**ICC002 — Algoritmos e Estruturas de Dados I**  
**Data:** quarta-feira, 18/11/2026 | **Modalidade:** duplas | **Duração:** 2 horas-aula

## Situação-problema
Na M03, a lista passou a armazenar cargas genéricas, inserir no início e percorrer seus nós. Agora o MiniPlayer precisa acrescentar músicas ao fim da biblioteca, localizar uma música por identificador e removê-la sem corromper os encadeamentos.

## Objetivos
1. Implementar `lse_inserir_fim`, `lse_buscar`, `lse_remover` e `lse_remover_inicio`.
2. Usar callback de comparação para manter a lista independente de `t_musica`.
3. Preservar `inicio`, `tamanho` e os encadeamentos após operações nos casos-limite.
4. Separar a liberação do nó da responsabilidade sobre a carga.
5. Escrever, executar e explicar testes automatizados.

## Contratos e decisões
As assinaturas abaixo já constam do `include/lse.h` do kit inicial; **não substitua o cabeçalho existente**. Se a dupla alterou a interface, reconcilie manualmente com os contratos.

```c
int lse_inserir_fim(t_lse *lista, void *carga);
void *lse_buscar(const t_lse *lista, const void *chave,
                 t_comparador_lse comparar);
void *lse_remover(t_lse *lista, const void *chave,
                  t_comparador_lse comparar);
void *lse_remover_inicio(t_lse *lista);
```

- `lse_inserir_fim`: aloca um nó, liga-o ao final e incrementa `tamanho`; retorna `1` no sucesso e `0` em erro ou `lista == NULL`. A M04 **não** adiciona ponteiro `fim`: percorra a cadeia, com custo O(n).
- `lse_buscar`: percorre a lista e retorna a **primeira** carga para a qual `comparar(carga, chave) == 0`. Retorna `NULL` quando não encontra, ou quando `lista`/`comparar` é `NULL`. Não modifica a lista.
- `lse_remover`: remove apenas o **primeiro** nó correspondente; ajusta ligações e `tamanho`, libera **somente o nó** e devolve a carga. Retorna `NULL` quando não encontra ou os argumentos são inválidos.
- `lse_remover_inicio`: remove o primeiro nó e devolve sua carga; retorna `NULL` se a lista estiver vazia ou for `NULL`.
- A carga `NULL` é permitida pela decisão da M03. Como `NULL` também sinaliza ausência nas operações de busca e remoção, **não use cargas `NULL` nos cenários de busca/remoção da M04**. Documente essa ambiguidade e discuta como uma API futura poderia resolvê-la.
- A função de comparação **não deve alterar** as cargas ou a chave. Para músicas, compare por `id`, sem colocar código específico de música dentro de `lse.c`.

## Atividades da dupla
1. Desenhe uma lista vazia, uma com um nó e outra com três nós. Indique os ponteiros que mudam em cada remoção.
2. Escreva primeiro os testes para inserção no fim, busca por chave e remoção.
3. Implemente as operações no `src/lse.c` **já desenvolvido**. Preserve o código da M01–M03.
4. Execute os testes da M03 e da M04 para verificar regressões.
5. Acrescente uma seção **M04** aos documentos existentes: `arquitetura.md`, `contratos.md`, `diario-de-bordo.md`, `relatorio-testes.md`.

## Casos de teste mínimos
- Inserção no fim em lista vazia e não vazia; ordem preservada.
- Busca do primeiro, intermediário, último e inexistente; lista não se altera.
- Remoção do início, meio, fim, único elemento e chave inexistente.
- Remoção de chave duplicada: apenas a primeira ocorrência é retirada.
- Lista `NULL`, callback `NULL` e operações em lista vazia.
- Teste com `int` e com um registro semelhante a `t_musica`.
- Remoção seguida de reinserção; destruição sem liberar cargas automáticas.

## Execução
Na raiz do MiniPlayer:

```sh
make -f missoes/M04/Makefile.incremental test_m04
```

Se a inclusão automática já foi configurada no `Makefile` principal:

```sh
make test_m04
make test_m03
```

**Não** copie versões novas de `src/lse.c`, `include/lse.h` ou do `Makefile` principal. Este kit contém apenas arquivos em `missoes/M04/`.

## Critérios de aceitação
- Testes M03 e M04 aprovados, sem alterar asserções para mascarar defeitos.
- Encadeamento e tamanho corretos após todas as operações.
- `t_elem` permanece privado ao módulo da lista.
- Nenhuma função da lista depende do tipo `t_musica`.
- Remover um nó não libera a carga; a dupla sabe explicar quem deve liberá-la.
- Documentação cumulativa e commit identificável da M04.

**Próxima missão (23/11):** inserção ordenada e ampliação dos testes.
