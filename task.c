#include "task.h"
#include <string.h>
#include <stdio.h>

#define MAX_TASKS 100

Task listatasks[MAX_TASKS];

int totaltasks = 0;

void cadastrartask(char *nome, char *programa, char **args, int totalargs) {
    
    if (totaltasks >= MAX_TASKS) {
        printf("Erro: limite de tarefas atingido.\n");
        return;
    }

    if (totalargs > MAX_ARGS) {
        printf("Erro: limite de argumentos atingido.\n");
        return;
    }

    strcpy(listatasks[totaltasks].nome, nome);
    strcpy(listatasks[totaltasks].programa, programa);
    for (int i = 0; i < totalargs; i++) {
        listatasks[totaltasks].args[i] = args[i];
    }
    listatasks[totaltasks].totalargs = totalargs;
    totaltasks++;
}

Task *buscartask(char *nome) {
    for (int i=0; i<totaltasks; i++){
        if(strcmp(listatasks[i].nome,nome)==0){
            return &listatasks[i];
        }
    }
    return NULL;
}