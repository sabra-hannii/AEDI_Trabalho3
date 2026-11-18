# Instalação segura — M04

Execute na raiz do projeto MiniPlayer:

```sh
unzip -n MiniPlayer_M04_Incremental.zip -d .
make -f missoes/M04/Makefile.incremental test_m04
```

**Atenção:** `unzip -n` não sobrescreve, mas pode deixar arquivos antigos se `missoes/M04/` já existir. Inspecione antes: `unzip -l MiniPlayer_M04_Incremental.zip`. Não use `unzip -o`. 

Para ativar `make test_m04` sem substituir o Makefile principal, acrescente **uma única vez**, ao final do Makefile existente:

```makefile
-include $(wildcard missoes/M*/Makefile.incremental)
```

Se não quiser editar o Makefile principal, o comando `make -f ...` funciona de modo independente. A instalação não modifica `src/`, `include/`, `tests/`, `docs/` ou o Makefile principal.

Se a compilação falhar por assinaturas incompatíveis, confira a interface existente em `include/lse.h` e os contratos do enunciado; não apague implementações anteriores.
