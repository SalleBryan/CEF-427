#ifndef MINI_OS_SCHEDULER_H
#define MINI_OS_SCHEDULER_H

void scheduler_init(void);
void scheduler_add(int pid);
void scheduler_tick(void);

#endif
