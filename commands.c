#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "commands.h"

int handle_builtin_commands(const char *user_input) {
    if (strncmp(user_input, "setenv ", 7) == 0) {
        return handle_setenv(user_input + 7);
    } else if (strncmp(user_input, "unsetenv ", 9) == 0) {
        return handle_unsetenv(user_input + 9);
    } else if (strncmp(user_input, "cd ", 3) == 0) {
        return handle_cd(user_input + 3);
    } else if (strcmp(user_input, "env") == 0) {
        print_environment();
        return 1;
    } else if (handle_alias(user_input)) {
        return 1;
    }

    return 0; // Not a built-in command
}

