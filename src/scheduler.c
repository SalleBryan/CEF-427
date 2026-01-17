#include "scheduler.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "process.h"

static int queue[MAX_PROCESSES];
static int head = 0;
static int tail = 0;
static bool in_queue[MAX_PROCESSES + 1];

void scheduler_init(void) {
    memset(queue, 0, sizeof(queue));
    memset(in_queue, 0, sizeof(in_queue));
    head = 0;
    tail = 0;
}

void scheduler_add(int pid) {
    if (pid <= 0 || pid > MAX_PROCESSES) {
        return;
    }
    if (in_queue[pid]) {
        return;
    }
    queue[tail] = pid;
    tail = (tail + 1) % MAX_PROCESSES;
    in_queue[pid] = true;
}

void scheduler_tick(void) {
    if (head == tail) {
        printf("[Scheduler] no ready processes.\n");
        return;
    }

    int pid = queue[head];
    head = (head + 1) % MAX_PROCESSES;
    in_queue[pid] = false;

    Process *proc = process_get(pid);
    if (!proc) {
        printf("[Scheduler] process %d not found.\n", pid);
        return;
    }

    process_set_state(pid, PROCESS_RUNNING);
    printf("[Scheduler] running PID %d for 1 tick\n", pid);
    process_set_state(pid, PROCESS_READY);

    scheduler_add(pid);
}
