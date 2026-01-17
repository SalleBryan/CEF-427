#include "memory.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "process.h"

static int owner[MEMORY_POOL_BLOCKS];

void memory_init(void) {
    memset(owner, 0, sizeof(owner));
}

int memory_allocate(int pid, int blocks) {
    if (blocks <= 0 || blocks > MEMORY_POOL_BLOCKS) {
        return -1;
    }

    int allocated = 0;
    for (int i = 0; i < MEMORY_POOL_BLOCKS && allocated < blocks; i++) {
        if (owner[i] == 0) {
            owner[i] = pid;
            allocated++;
        }
    }

    if (allocated < blocks) {
        for (int i = 0; i < MEMORY_POOL_BLOCKS; i++) {
            if (owner[i] == pid) {
                owner[i] = 0;
            }
        }
        return -1;
    }

    Process *proc = process_get(pid);
    if (proc) {
        proc->allocated_blocks += allocated;
    }

    return allocated;
}

void memory_free(int pid) {
    for (int i = 0; i < MEMORY_POOL_BLOCKS; i++) {
        if (owner[i] == pid) {
            owner[i] = 0;
        }
    }
}

void memory_status(void) {
    int used = 0;
    for (int i = 0; i < MEMORY_POOL_BLOCKS; i++) {
        if (owner[i] != 0) {
            used++;
        }
    }
    printf("[Memory] used blocks: %d/%d (block size %d bytes)\n",
           used,
           MEMORY_POOL_BLOCKS,
           MEMORY_BLOCK_SIZE);
}
