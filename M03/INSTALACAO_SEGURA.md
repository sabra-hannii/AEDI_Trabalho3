# Instalação segura — M03

Este pacote contém **somente** `missoes/M03/`. Não inclui `src/`, `include/`, `Makefile` principal nem documentos existentes.

1. Antes de extrair, examine o conteúdo: `unzip -l MiniPlayer_M03_Incremental.zip`.
2. Extraia na raiz com `unzip -n MiniPlayer_M03_Incremental.zip -d .`. A opção `-n` impede sobrescrita, mas confira a saída para detectar nomes repetidos.
3. Leia `missoes/M03/ENUNCIADO.md`.
4. Edite **manualmente** os arquivos de implementação existentes; não copie uma implementação pronta.
5. Execute `make -f missoes/M03/Makefile.incremental test_m03`.

## Integração opcional no Makefile principal
Se a dupla já fez a integração de missões, basta `make test_m03`. Caso contrário, o comando com `-f` funciona sem nenhuma alteração no Makefile principal. Para habilitar a inclusão automática, acrescente **uma única vez** ao final do Makefile principal:

```makefile
-include $(wildcard missoes/M*/Makefile.incremental)
```

Não substitua o Makefile existente. Se `make test_m03` não encontrar a regra, use o comando explícito com `-f`.
