#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_ARGS 32

int tokenize_input(char *user_input, char *args[]) {
    // Tokenize the user input into command and arguments
    int arg_count = 0;
    char *token = strtok(user_input, " ");
    while (token != NULL) {
        args[arg_count++] = token;
        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL; // Null-terminate the argument list
    return arg_count;
}

int execute_command(char *args[]) {
    // Execute the command using execvp
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    } else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            return -1; // Command doesn't exist
        }
    } else {
        wait(NULL); // Wait for the child to complete
    }
    return 0;
}

