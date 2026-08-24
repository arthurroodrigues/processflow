#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h> 
#include "task.h"

char diretorioatual[300] = "";

pid_t iniciar_task(Task *t) {
    char *args_exec[t->totalargs + 2];
    args_exec[0] = t->programa;
    for (int i = 0; i < t->totalargs; i++) {
        args_exec[i + 1] = t->args[i];
    }
    args_exec[t->totalargs + 1] = NULL;

    pid_t pid = fork();
        if (pid == 0) {
            if (strlen(diretorioatual) > 0) {
        if (chdir(diretorioatual) != 0) {
            perror("chdir");
            exit(1);
        }
    }
         if (t->modooutput == 1) {
            int fd = open(t->arquivooutput, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("open output");
                exit(1);
            }
            dup2(fd, 1);
            close(fd);
        } else if (t->modooutput == 2) {
            int fd = open(t->arquivooutput, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0) {
                perror("open append");
                exit(1);
            }
            dup2(fd, 1);
            close(fd);
        }

        if (strlen(t->arquivoinput) > 0) {
            int fd = open(t->arquivoinput, O_RDONLY);
            if (fd < 0) {
                perror("open input");
                exit(1);
            }
            dup2(fd, 0);
            close(fd);
        }
        execvp(t->programa, args_exec);
        perror("execvp");
        exit(1);
    }
    return pid;
}

int main(int argc, char *argv[]){
    char linha[300];
    FILE *entrada = stdin;
    int workflow = 0;
    if (argc > 2) {
        printf("Erro : número de argumentos inválido.\n");
        exit(1);
}

    if (argc > 1) {
        entrada = fopen(argv[1], "r");
        if (entrada == NULL) {
            printf("Erro : não foi possível abrir o workflow file.\n");
            exit(1);
        }
        workflow = 1;
    }
    while(1){
         if (workflow==0) {
            printf("processflow> ");
        }

        if (fgets(linha, sizeof(linha), entrada) == NULL) {
            break; // chegou no fim do arquivo, ou Ctrl-D no interativo
        }

        if (workflow) {
            printf("%s", linha); // imprime a linha lida (exigência do enunciado)
        }

        linha[strcspn(linha, "\n")] = 0;

        if (strcmp(linha, "exit") == 0){
            break;
        }
        
        char *tokens[30];
        int totaltokens=0;

        char *token=strtok(linha, " ");
        while (token!=NULL){
            tokens[totaltokens]=token;
            totaltokens++;
            token=strtok(NULL," ");

        }
        if (totaltokens == 0) {
            continue;
        }
        
        if (strcmp(tokens[0], "task") == 0) {
            char *nome = tokens[1];
            char *programa = tokens[2];
            int totalargs = totaltokens - 3;
            char **args = &tokens[3];

            cadastrartask(nome, programa, args, totalargs);
            printf("Task '%s' cadastrada\n", nome);
        }
        
        
    if (strcmp(tokens[0], "run") == 0 && totaltokens > 1 &&
    strcmp(tokens[1], "sequential") != 0 && strcmp(tokens[1], "parallel") != 0) {
        char *nometask = tokens[1];
        Task *t = buscartask(nometask);

        if (t == NULL) {
            printf("Erro: tarefa não existe.\n");
    }else {
        pid_t pid = iniciar_task(t);
        int status;
        waitpid(pid, &status, 0);
    }
}
    if (strcmp(tokens[0], "run") == 0 && totaltokens > 1 && strcmp(tokens[1], "sequential") == 0) {
        for (int i = 2; i < totaltokens; i++) {
            Task *t = buscartask(tokens[i]);
            if (t == NULL) {
                printf("Erro: tarefa '%s' não existe.\n", tokens[i]);
                continue;
            }
            pid_t pid = iniciar_task(t);
            int status;
            waitpid(pid, &status, 0);
            }
        }
    if (strcmp(tokens[0], "run") == 0 && totaltokens > 1 && strcmp(tokens[1], "parallel") == 0) {
        pid_t pids[20];
        int totalpids = 0;

        for (int i = 2; i < totaltokens; i++) {
            Task *t = buscartask(tokens[i]);
            if (t == NULL) {
                printf("Erro: tarefa '%s' não existe.\n", tokens[i]);
                continue;
            }
            pids[totalpids] = iniciar_task(t);
            totalpids++;
        }
        for (int i = 0; i < totalpids; i++) {
                int status;
                waitpid(pids[i], &status, 0);    
    }
    }
    if (strcmp(tokens[0], "workdir") == 0) {
        strcpy(diretorioatual, tokens[1]);
        printf("Diretório de trabalho alterado para: %s\n", diretorioatual);
}
    if (strcmp(tokens[0], "output") == 0) {
        char *nometask = tokens[1];
        Task *t = buscartask(nometask);
        if (t == NULL) {
            printf("Erro: tarefa não existe.\n");
        } else {
            strcpy(t->arquivooutput, tokens[2]);
            t->modooutput = 1;
            printf("Output redirecionado para '%s'.\n", tokens[2]);
    }
}

    if (strcmp(tokens[0], "append") == 0) {
        char *nometask = tokens[1];
        Task *t = buscartask(nometask);
        if (t == NULL) {
            printf("Erro: tarefa não existe.\n");
        } else {
            strcpy(t->arquivooutput, tokens[2]);
            t->modooutput = 2;
            printf("Output será anexado a '%s'.\n", tokens[2]);
    }
}

    if (strcmp(tokens[0], "input") == 0) {
        char *nometask = tokens[1];
        Task *t = buscartask(nometask);
        if (t == NULL) {
            printf("Erro: tarefa não existe.\n");
        } else {
            strcpy(t->arquivoinput, tokens[2]);
            printf("Input será lido de '%s'.\n", tokens[2]);
    }
}
}
    return 0;
}

