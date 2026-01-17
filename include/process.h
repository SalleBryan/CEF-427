#ifndef MINI_OS_PROCESS_H
#define MINI_OS_PROCESS_H

#include <stddef.h>

#define MAX_PROCESSES 32
#define MAX_THREADS 8
#define PROCESS_NAME_LEN 32

typedef enum {
    PROCESS_READY,
    PROCESS_RUNNING,
    PROCESS_WAITING,
    PROCESS_TERMINATED
} ProcessState;

typedef struct {
    int tid;
    ProcessState state;
} Thread;

typedef struct {
    int pid;
    char name[PROCESS_NAME_LEN];
    ProcessState state;
    int thread_count;
    Thread threads[MAX_THREADS];
    int allocated_blocks;
} Process;

void process_init(void);
int process_create(const char *name);
Process *process_get(int pid);
void process_list(void);
void process_set_state(int pid, ProcessState state);
void process_free_memory(int pid);

#endif
