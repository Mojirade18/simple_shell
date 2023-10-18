#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *destination, char *source)
{
    int i = 0;

    if (destination == source || source == 0)
        return (destination);

    while (source[i])
    {
        destination[i] = source[i];
        i++;
    }

    destination[i] = 0;
    return (destination);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *original)
{
    int length = 0;
    char *duplicate;

    if (original == NULL)
        return (NULL);

    while (*original++)
        length++;

    duplicate = malloc(sizeof(char) * (length + 1));

    if (!duplicate)
        return (NULL);

    for (length++; length--;)
        duplicate[length] = *--original;

    return (duplicate);
}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
    int i = 0;

    if (!str)
        return;

    while (str[i] != '\0')
    {
        _putchar(str[i]);
        i++;
    }
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char character)
{
    static int index;
    static char buffer[WRITE_BUF_SIZE];

    if (character == BUF_FLUSH || index >= WRITE_BUF_SIZE)
    {
        write(1, buffer, index);
        index = 0;
    }

    if (character != BUF_FLUSH)
        buffer[index++] = character;

    return (1);
}

