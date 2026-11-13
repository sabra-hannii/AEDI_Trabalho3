# M02 — Pacote incremental e seguro

**Objetivo:** acrescentar recursos de M02 ao repositório existente, sem substituir código da M01 nem modificações locais.

## Regra de integridade
Este pacote contém **somente arquivos novos** dentro de `missoes/M02/`. Não inclui `src/`, `include/`, `tests/`, `docs/`, `Makefile` ou `README.md` na raiz. O código existente é sempre preservado. O teste compila o `src/lse.c` que já existe no projeto.

## Instalação recomendada
1. Na raiz do projeto, salve as alterações e crie um commit de segurança (`git status`, `git add -A`, `git commit -m "checkpoint antes da M02"`). Se não usar Git, faça uma cópia da pasta.
2. **Antes de extrair**, verifique se `missoes/M02/TESTE_INCREMENTAL_M02.c`, `missoes/M02/Makefile.incremental` ou `missoes/M02/GUIA_INCREMENTAL.md` já existem. Caso existam, **não substitua**; interrompa a instalação e compare as versões.
3. Execute a extração com a opção que nunca sobrescreve arquivos existentes: `unzip -n MiniPlayer_M02_Incremental.zip -d .` (a partir da raiz do projeto).
4. Confira as mudanças com `git status --short`.
5. Execute `make -f missoes/M02/Makefile.incremental test_m02`.

> `unzip -n` não sobrescreve arquivos, mas pode deixar de instalar arquivos que já existam. Portanto, confira a saída da extração; não considere a instalação concluída se algum arquivo for ignorado.

## Trabalho da dupla
- **Editar somente o código já existente**, de forma consciente, em `src/lse.c`: implementar criação de lista vazia, consultas e destruição de lista vazia.
- **Não substituir `lse.c` pelo de um novo kit**; a missão usa a versão atual da dupla.
- **Atualizar os documentos existentes**, acrescentando seções intituladas `M02` em `docs/contratos.md`, `docs/arquitetura.md`, `docs/diario-de-bordo.md` e `docs/relatorio-testes.md`. Nunca trocar o documento inteiro por um modelo.
- Registrar o resultado do teste antes e depois da implementação.
- Preservar `void *carga` e `t_elem` como detalhe interno da lista.

## Contratos desta missão
- `lse_criar`: devolve lista vazia alocada ou `NULL` em falha de memória.
- `lse_tamanho`: devolve 0 para lista recém-criada.
- `lse_primeiro`: devolve `NULL` para lista vazia.
- `lse_destruir`: libera uma lista vazia sem liberar cargas de terceiros.

## Critérios de aceitação
O teste passa sem alterações no teste, não há alterações involuntárias em arquivos anteriores, e a documentação registra contratos, invariantes e decisões de memória.

## Próximas missões
Adotar o mesmo padrão: um pacote com arquivos novos e únicos dentro de `missoes/Mxx/`, testes independentes e um Makefile suplementar. Modificações em `src/` e `include/` devem ser feitas pelos estudantes em seus arquivos atuais, nunca por extração de kits.
