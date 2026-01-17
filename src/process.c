#include "process.h"

#include <stdio.h>
#include <string.h>

#include "memory.h"

static Process processes[MAX_PROCESSES];
static int next_pid = 1;

void process_init(void) {
    memset(processes, 0, sizeof(processes));
    next_pid = 1;
}

int process_create(const char *name) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (processes[i].pid == 0 || processes[i].state == PROCESS_TERMINATED) {
            Process *proc = &processes[i];
            proc->pid = next_pid++;
            strncpy(proc->name, name, PROCESS_NAME_LEN - 1);
            proc->name[PROCESS_NAME_LEN - 1] = '\0';
            proc->state = PROCESS_READY;
            proc->thread_count = 1;
            proc->threads[0].tid = 1;
            proc->threads[0].state = PROCESS_READY;
            proc->allocated_blocks = 0;
            return proc->pid;
        }
    }

    return -1;
}

Process *process_get(int pid) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (processes[i].pid == pid && processes[i].state != PROCESS_TERMINATED) {
            return &processes[i];
        }
    }
    return NULL;
}

void process_list(void) {
    printf("PID\tSTATE\tNAME\tTHREADS\tMEM BLOCKS\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (processes[i].pid != 0 && processes[i].state != PROCESS_TERMINATED) {
            const char *state = "READY";
            if (processes[i].state == PROCESS_RUNNING) {
                state = "RUNNING";
            } else if (processes[i].state == PROCESS_WAITING) {
                state = "WAITING";
            }
            printf("%d\t%s\t%s\t%d\t%d\n",
                   processes[i].pid,
                   state,
                   processes[i].name,
                   processes[i].thread_count,
                   processes[i].allocated_blocks);
        }
    }
}

void process_set_state(int pid, ProcessState state) {
    Process *proc = process_get(pid);
    if (!proc) {
        return;
    }
    proc->state = state;
    for (int i = 0; i < proc->thread_count; i++) {
        proc->threads[i].state = state;
    }
}

void process_free_memory(int pid) {
    Process *proc = process_get(pid);
    if (!proc) {
        return;
    }
    memory_free(pid);
    proc->allocated_blocks = 0;
}
