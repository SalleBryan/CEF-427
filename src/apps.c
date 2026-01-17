#include "apps.h"

#include <stdio.h>
#include <string.h>

static void app_echo(void) {
    char buffer[128];
    printf("Enter text: ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        printf("App output: %s", buffer);
    }
}

static void app_calc(void) {
    int a = 0;
    int b = 0;
    printf("Enter two integers: ");
    if (scanf("%d %d", &a, &b) == 2) {
        printf("Result: %d\n", a + b);
    } else {
        printf("Invalid input.\n");
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

static void app_sleep(void) {
    int ticks = 0;
    printf("Sleep ticks: ");
    if (scanf("%d", &ticks) == 1) {
        printf("Sleeping for %d ticks...\n", ticks);
        for (int i = 0; i < ticks; i++) {
            printf("tick %d\n", i + 1);
        }
    } else {
        printf("Invalid input.\n");
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

static const App app_table[] = {
    {"echo", app_echo},
    {"calc", app_calc},
    {"sleep", app_sleep},
};

void apps_init(void) {
    printf("[Apps] registered %zu apps\n", sizeof(app_table) / sizeof(app_table[0]));
}

const App *apps_lookup(const char *name) {
    size_t count = sizeof(app_table) / sizeof(app_table[0]);
    for (size_t i = 0; i < count; i++) {
        if (strcmp(app_table[i].name, name) == 0) {
            return &app_table[i];
        }
    }
    return NULL;
}
