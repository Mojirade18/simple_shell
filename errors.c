#include "shell.h"

/**
 * print_error_message - prints an error message to stderr
 * @message: the error message to be printed
 *
 * Return: Nothing
 */
void print_error_message(char *message)
{
    int index = 0;

    if (!message)
        return;
    while (message[index] != '\0')
    {
        write_error_character(message[index]);
        index++;
    }
}

/**
 * write_error_character - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_error_character(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * write_character_to_fd - writes the character c to the given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_character_to_fd(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * write_string_to_fd - writes an input string to the given file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int write_string_to_fd(char *str, int fd)
{
    int index = 0;

    if (!str)
        return (0);
    while (*str)
    {
        index += write_character_to_fd(*str++, fd);
    }
    return (index);
}

