#ifndef MINI_OS_KERNEL_H
#define MINI_OS_KERNEL_H

#include <stdbool.h>

void kernel_boot(void);
void kernel_shutdown(void);

bool kernel_is_running(void);

#endif
