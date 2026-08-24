# ProcessFlow

Implementação 1 da disciplina de Infraestrutura de Software.

## Sistema operacional

Desenvolvido e testado em Linux (WSL - Ubuntu, rodando sobre Windows).

## Arquivos

- `main.c` — loop principal do programa (modo interativo e modo workflow), parser de comandos e execução das tarefas
- `task.h` / `task.c` — struct `Task` e funções para cadastrar e buscar tarefas
- `job.h` / `job.c` — struct `Job` e funções para gerenciar execuções em background
- `Makefile` — compilação, execução e testes
- `tests/test.pf` — arquivo de exemplo de workflow
- `evidencias.log` — log da sessão de desenvolvimento

## Como compilar

```bash
make build
```

## Como executar

```bash
./processflow
```

ou, para rodar um arquivo de workflow:

```bash
./processflow tests/test.pf
```

## Como testar

```bash
make test
```

Para limpar o executável gerado:

```bash
make clean
```