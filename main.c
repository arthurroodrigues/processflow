#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include "task.h"

int main(){
    char linha[300];
    
    while(1){
        printf("processflow> ");
        fgets(linha,sizeof(linha),stdin);

        linha[strcspn(linha, "\n")]=0;

        if (strcmp(linha,"exit")==0){
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
        
        if (strcmp(tokens[0], "task") == 0) {
            char *nome = tokens[1];
            char *programa = tokens[2];
            int totalargs = totaltokens - 3;
            char **args = &tokens[3];

            cadastrartask(nome, programa, args, totalargs);
            printf("Task '%s' cadastrada\n", nome);
        }
        
        
    if (strcmp(tokens[0], "run") == 0) {
        char *nometask = tokens[1];
        Task *t = buscartask(nometask);

        if (t == NULL) {
            printf("Erro: tarefa não existe.\n");
    }else {
        
        char *args_exec[t->totalargs + 2];
        args_exec[0] = t->programa;
        for (int i = 0; i < t->totalargs; i++) {
            args_exec[i + 1] = t->args[i];
        }
        args_exec[t->totalargs + 1] = NULL;

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
        } else if (pid == 0) {
            execvp(t->programa, args_exec);
            perror("execvp");
            exit(1);
        } else {
            int status;
            waitpid(pid, &status, 0);
        }
    }
}
    
    }
    return 0;
}
