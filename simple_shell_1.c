#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ARGS 32

int main(void) {
    char *user_input = NULL;
    size_t bufsize = 0;

    while (1) {
        printf("#cisfun$ "); // Display the prompt
        ssize_t n = getline(&user_input, &bufsize, stdin); // Read a line of input

        if (n == -1) {
            if (feof(stdin)) {
                // Handle Ctrl+D (end of file)
                printf("\n");
                free(user_input);
                exit(EXIT_SUCCESS);
            } else {
                perror("getline");
                free(user_input);
                exit(EXIT_FAILURE);
            }
        }

        // Remove the trailing newline character
        if (n > 0 && user_input[n - 1] == '\n') {
            user_input[n - 1] = '\0';
        }

        // Tokenize the user input into command and arguments
        char *token;
        char *args[MAX_ARGS];
        int arg_count = 0;

        token = strtok(user_input, " ");
        while (token != NULL) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL; // Null-terminate the argument list

        // Execute the command using execve
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            free(user_input);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // In the child process
            if (execve(args[0], args, NULL) == -1) {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        } else {
            // In the parent process
            wait(NULL); // Wait for the child to complete
        }
    }

    free(user_input);
    return 0;
}

