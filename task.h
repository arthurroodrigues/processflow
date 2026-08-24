#ifndef TASK_H
#define TASK_H

#define MAX_ARGS 100

typedef struct Task{
    char nome[50];
    char programa[100];
    char args[MAX_ARGS][300];
    int totalargs;
    char arquivoinput[300];
    char arquivooutput[300];
    int modooutput;
} Task;

void cadastrartask(char *nome, char *programa, char *args[], int totalargs);

Task *buscartask(char *nome);

#endif