#ifndef MINI_OS_MEMORY_H
#define MINI_OS_MEMORY_H

#define MEMORY_POOL_BLOCKS 128
#define MEMORY_BLOCK_SIZE 64

void memory_init(void);
int memory_allocate(int pid, int blocks);
void memory_free(int pid);
void memory_status(void);

#endif
