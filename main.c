#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
#include "commands.h"
#include "logical_operators.h"
#include "alias.h"

int main(void) {
    char *user_input = NULL;

    while (1) {
        printf("$ "); // Display the prompt

        // Read a line of input using custom getline
        ssize_t n = custom_getline(&user_input);

        if (n == -1) {
            if (feof(stdin)) {
                // Handle Ctrl+D (end of file)
                printf("\n");
                free(user_input);
                exit(EXIT_SUCCESS);
            } else {
                perror("custom_getline");
                free(user_input);
                exit(EXIT_FAILURE);
            }
        }

        // Remove the trailing newline character
        if (n > 0 && user_input[n - 1] == '\n') {
            user_input[n - 1] = '\0';
        }

        if (handle_builtin_commands(user_input) == 0) {
            // If it's not a built-in command, execute it as a regular command
            char *commands[MAX_COMMANDS];
            int command_count = parse_commands(user_input, commands);

            for (int i = 0; i < command_count; i++) {
                char *args[MAX_ARGS];
                int arg_count = parse_input(commands[i], args);

                if (arg_count > 0) {
                    if (execute_with_logical_operator(args) == 0) {
                        if (execute_command(args) == -1) {
                            printf("Command not found: %s\n", args[0]);
                        }
                    }
                }
            }
        }
    }

    free(user_input);
    return 0;
}

