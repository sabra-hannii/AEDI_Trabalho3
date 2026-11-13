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
