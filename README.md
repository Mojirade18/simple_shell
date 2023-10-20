# My Simple Shell (hsh)

My Simple Shell, or hsh, is a simple UNIX command language interpreter that reads commands from either a file or standard input and executes them.

## Features

- Provides a command prompt for user input.
- Creates child processes to execute commands.
- Handles built-in commands, aliases in the PATH, and local executable programs.
- Accepts command-line arguments.
- Provides a graceful exit mechanism.
- Works in both interactive and non-interactive modes.

## Compilation

To compile the shell, use the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
