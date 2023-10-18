#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"
#include "logical_operators.h"

int execute_with_logical_operator(char *args[]) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    } else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            return -1; // Command doesn't exist
        }
    } else {
        int status;
        wait(&status);
        return status;
    }
}

