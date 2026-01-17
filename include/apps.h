#ifndef MINI_OS_APPS_H
#define MINI_OS_APPS_H

typedef void (*AppEntry)(void);

typedef struct {
    const char *name;
    AppEntry entry;
} App;

void apps_init(void);
const App *apps_lookup(const char *name);

#endif
