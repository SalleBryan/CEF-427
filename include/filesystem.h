#ifndef MINI_OS_FILESYSTEM_H
#define MINI_OS_FILESYSTEM_H

#define MAX_FILES 64
#define FILENAME_LEN 64

void fs_init(void);
int fs_create(const char *name);
void fs_list(void);

#endif
