#include "cli.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "apps.h"
#include "filesystem.h"
#include "kernel.h"
#include "memory.h"
#include "process.h"
#include "scheduler.h"

static void print_help(void) {
    printf("Commands:\n");
    printf("  help                  Show this help\n");
    printf("  ps                    List processes\n");
    printf("  create <name>         Create process\n");
    printf("  run <app>             Run built-in app (echo, calc, sleep)\n");
    printf("  schedule              Run round-robin scheduler tick\n");
    printf("  mem                   Show memory usage\n");
    printf("  alloc <pid> <blocks>  Allocate memory blocks\n");
    printf("  free <pid>            Free memory for process\n");
    printf("  touch <file>          Create a file\n");
    printf("  ls                    List files\n");
    printf("  exit                  Quit mini-os\n");
}

static void trim_newline(char *input) {
    size_t len = strlen(input);
    if (len == 0) {
        return;
    }
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
}

void cli_loop(void) {
    char input[128];

    while (kernel_is_running()) {
        printf("mini-os> ");
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }
        trim_newline(input);

        if (strcmp(input, "help") == 0) {
            print_help();
        } else if (strcmp(input, "ps") == 0) {
            process_list();
        } else if (strncmp(input, "create ", 7) == 0) {
            const char *name = input + 7;
            int pid = process_create(name);
            if (pid < 0) {
                printf("Failed to create process.\n");
            } else {
                scheduler_add(pid);
                printf("Created process '%s' with PID %d\n", name, pid);
            }
        } else if (strncmp(input, "run ", 4) == 0) {
            const char *app_name = input + 4;
            const App *app = apps_lookup(app_name);
            if (!app) {
                printf("Unknown app '%s'\n", app_name);
            } else {
                app->entry();
            }
        } else if (strcmp(input, "schedule") == 0) {
            scheduler_tick();
        } else if (strcmp(input, "mem") == 0) {
            memory_status();
        } else if (strncmp(input, "alloc ", 6) == 0) {
            int pid = 0;
            int blocks = 0;
            if (sscanf(input + 6, "%d %d", &pid, &blocks) == 2) {
                int allocated = memory_allocate(pid, blocks);
                if (allocated < 0) {
                    printf("Allocation failed.\n");
                } else {
                    printf("Allocated %d blocks to PID %d\n", allocated, pid);
                }
            } else {
                printf("Usage: alloc <pid> <blocks>\n");
            }
        } else if (strncmp(input, "free ", 5) == 0) {
            int pid = 0;
            if (sscanf(input + 5, "%d", &pid) == 1) {
                process_free_memory(pid);
                printf("Freed memory for PID %d\n", pid);
            } else {
                printf("Usage: free <pid>\n");
            }
        } else if (strncmp(input, "touch ", 6) == 0) {
            const char *name = input + 6;
            if (fs_create(name) == 0) {
                printf("Created file '%s'\n", name);
            } else {
                printf("Failed to create file.\n");
            }
        } else if (strcmp(input, "ls") == 0) {
            fs_list();
        } else if (strcmp(input, "exit") == 0) {
            kernel_shutdown();
        } else if (strlen(input) == 0) {
            continue;
        } else {
            printf("Unknown command. Type 'help'.\n");
        }
    }
}
