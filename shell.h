#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 32
#define MAX_COMMANDS 32

// Utility functions
int custom_getline(char **user_input);
int parse_commands(char *user_input, char *commands[]);
int parse_input(char *user_input, char *args[]);
int execute_command(char *args[]);
void print_environment();

// Built-in command functions
int handle_setenv(const char *command);
int handle_unsetenv(const char *command);
int handle_cd(const char *command);
int handle_builtin_commands(const char *user_input);

// Logical operator functions
int execute_with_logical_operator(char *args[]);

// Alias functions
int handle_alias(const char *user_input);

#endif

