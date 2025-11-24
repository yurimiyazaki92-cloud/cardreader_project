#include "inputhandling.h"
#include <stdio.h>

int input_int(const char *msg) {
    char buf[64];
    int value;

    while (1) {
        printf("%s", msg);

        if (!fgets(buf, sizeof(buf), stdin)) {
            clearerr(stdin);
            continue;
        }
        if (sscanf(buf, "%d", &value) == 1) {
            return value;
        }
        printf("Invalid input. Please enter a number.\n");
    }
}

