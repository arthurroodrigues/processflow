#include "task.h"
#include <string.h>
#include <stdio.h>

#define MAX_TASKS 100

Task listatasks[MAX_TASKS];

int total_tasks = 0;

void cadastrartask(char *nome, char *programa, char **args, int totalargs) {
    strcpy(listatasks[total_tasks].nome, nome);
    strcpy(listatasks[total_tasks].programa, programa);
    for (int i = 0; i < totalargs; i++) {
        listatasks[total_tasks].args[i] = args[i];
    }
    listatasks[total_tasks].totalargs = totalargs;
    total_tasks++;
}
