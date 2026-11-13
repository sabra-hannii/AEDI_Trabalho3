# Guia do estudante — MiniPlayer

## 1. O desafio
Construir em duplas um gerenciador de biblioteca musical com reprodução simulada. O foco é aprender memória dinâmica, TADs genéricos, lista simplesmente encadeada, pilha, fila, testes e arquivos. Não é necessário tocar áudio real.

## 2. Como trabalhar
Cada missão apresenta problema, contratos e testes. Escrevam um teste que falha, implementem a função, executem os testes anteriores e atualizem a documentação. Alternem os papéis de quem codifica e quem revisa.

## 3. Estrutura de diretórios
- `include/`: interfaces públicas (`.h`).
- `src/`: implementações (`.c`). `t_elem` é interno a `lse.c`.
- `tests/`: executáveis de teste independentes.
- `docs/`: arquitetura, contratos, diário e relatório de testes.
- `data/`: dados para persistência futura.
- `build/`: binários gerados, ignorados no Git.

## 4. Compilar e executar
Requisitos: GCC, Make, terminal Linux. Comandos:
```bash
make
./build/miniplayer
make build/test_musica
./build/test_musica
make test
```
`make test` falhará enquanto houver stubs não implementados. **Não** desabilitem asserts para fazer testes passarem.

## 5. Documentação mínima por missão
1. Atualizar o `README.md` com o estado atual e como executar.
2. Descrever funções implementadas em `docs/contratos.md` (pré/pós-condições, retornos e propriedade de memória).
3. Registrar decisões e dificuldades no `docs/diario-de-bordo.md`.
4. Preencher `docs/relatorio-testes.md` com casos, entradas, resultados esperados/obtidos.
5. Atualizar `docs/arquitetura.md` quando mudar a organização dos módulos.

## 6. Documentar no código
Em cada função pública, registrar o propósito, parâmetros, retorno, erros e regras de propriedade da carga. Evitar comentários que apenas repitam uma instrução C.

## 7. Arquitetura e memória
- `t_elem` é **interno** à LSE; sua carga é `void *`.
- A LSE não sabe o que é música; comparações usam callbacks.
- Pilha e fila são composições da LSE; não duplicam código de encadeamento.
- Inserção guarda o ponteiro da carga, sem copiá-la.
- `lse_remover_inicio`/`lse_remover` liberam o nó e devolvem a carga.
- `lse_destruir(lista, NULL)` libera só nós; callback não nulo libera cada carga também.
- Evitar liberar músicas enquanto fila ou histórico guardam ponteiros para elas.

## 8. Critérios de qualidade
Compilar com avisos, verificar testes de casos normais e limites, evitar vazamentos e acessos inválidos, explicar invariantes e decisões. Não usar funções prontas de listas, pilhas ou filas.

## 9. Missões e datas
M01 11/11: memória e música; M02 13/11: TADs/contratos; M03 16/11: LSE/percurso; M04 18/11: inserção/remoção/busca; M05 23/11: ordenação/testes; M06 25/11: pilha; M07 27/11: histórico; M08 30/11: fila; M09 02/12: integração; M10 04/12: arquivos; M11 07/12: testes finais; M12 09/12: apresentação.

## 10. Entrega
Código, testes e documentação atualizados. Na apresentação, demonstrar o MiniPlayer, executar testes e explicar como pilha/fila reutilizam a LSE.
