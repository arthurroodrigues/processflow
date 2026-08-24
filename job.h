#ifndef JOB_H
#define JOB_H
#include <sys/types.h> 

typedef struct {
    int id;
    pid_t pid;
    char status[20];
} Job;

void cadastrarjob(pid_t pid);
void listarjobs(void);
void esperarjob(int id);

#endif