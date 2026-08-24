#include "job.h"
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_JOBS 50

Job listajobs[MAX_JOBS];
int totaljobs = 0;

void cadastrarjob(pid_t pid) {
    int id = totaljobs + 1;
    listajobs[totaljobs].id = id;
    listajobs[totaljobs].pid = pid;
    strcpy(listajobs[totaljobs].status, "Running");
    totaljobs++;

    printf("[%d] %d\n", id, pid);
}

void listarjobs(void) {
    for (int i = 0; i < totaljobs; i++) {
        int status;
        pid_t resultado = waitpid(listajobs[i].pid, &status, WNOHANG);

        if (resultado > 0) {
            strcpy(listajobs[i].status, "Done");
        }

        printf("[%d] %d  %s\n", listajobs[i].id, listajobs[i].pid, listajobs[i].status);
    }
}

void esperarjob(int id) {
    int achou = 0;

    for (int i = 0; i < totaljobs; i++) {
        if (listajobs[i].id == id) {
            achou = 1;
            int status;
            waitpid(listajobs[i].pid, &status, 0);
            strcpy(listajobs[i].status, "Done");
            printf("Job [%d] finalizado.\n", id);
        }
    }

    if (achou==0) {
        printf("Erro: job %d não existe.\n", id);
    }
}