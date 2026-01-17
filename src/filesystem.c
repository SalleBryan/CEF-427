#include "filesystem.h"

#include <stdio.h>
#include <string.h>

static char files[MAX_FILES][FILENAME_LEN];
static int file_count = 0;

void fs_init(void) {
    memset(files, 0, sizeof(files));
    file_count = 0;
}

int fs_create(const char *name) {
    if (file_count >= MAX_FILES) {
        return -1;
    }

    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i], name) == 0) {
            return -1;
        }
    }

    strncpy(files[file_count], name, FILENAME_LEN - 1);
    files[file_count][FILENAME_LEN - 1] = '\0';
    file_count++;
    return 0;
}

void fs_list(void) {
    if (file_count == 0) {
        printf("(no files)\n");
        return;
    }

    for (int i = 0; i < file_count; i++) {
        printf("%s\n", files[i]);
    }
}
