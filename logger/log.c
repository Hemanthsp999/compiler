#include "log.h"
#include <stdio.h>

void log_info(char *error_msg) {
        printf("Debugging status: %s\n", error_msg);
        return;
}

void log_error(char *msg) {
        fprintf(stderr, "Debugging status: %s\n", msg);
        return;
}
