#include <stdio.h>

#include "cli.h"
#include "kernel.h"

int main(void) {
    kernel_boot();
    printf("Type 'help' for commands.\n");
    cli_loop();
    return 0;
}
