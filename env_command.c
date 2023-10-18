#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"

int handle_setenv(const char *command) {
    char *var = strtok(command, " ");
    char *value = strtok(NULL, " ");
    if (var == NULL || value == NULL) {
        return 0; // Invalid command syntax
    }

    if (setenv(var, value, 1) != 0) {
        return 0; // Failed to set environment variable
    }

    return 1; // Success
}

int handle_unsetenv(const char *command) {
    char *var = strtok(command, " ");
    if (var == NULL) {
        return 0; // Invalid command syntax
    }

    if (unsetenv(var) != 0) {
        return 0; // Failed to unset environment variable
    }

    return 1; // Success
}

