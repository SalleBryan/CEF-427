#include "kernel.h"

#include <stdio.h>

#include "apps.h"
#include "filesystem.h"
#include "memory.h"
#include "process.h"
#include "scheduler.h"

static bool kernel_running = false;

void kernel_boot(void) {
    printf("[Kernel] booting mini-os...\n");
    process_init();
    scheduler_init();
    memory_init();
    fs_init();
    apps_init();
    kernel_running = true;
}

void kernel_shutdown(void) {
    printf("[Kernel] shutting down.\n");
    kernel_running = false;
}

bool kernel_is_running(void) {
    return kernel_running;
}
