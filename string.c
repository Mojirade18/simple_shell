#include "shell.h"

/**
 * string_length - returns the length of a string
 * @s: the string whose length to check
 * Return: integer length of the string
 */
int string_length(char *s)
{
    int length = 0;

    if (!s)
        return 0;

    while (*s++)
        length++;

    return length;
}

/**
 * string_compare - performs lexicographic comparison of two strings.
 * @s1: the first string
 * @s2: the second string
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int string_compare(const char *s1, const char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return *s1 - *s2;

        s1++;
        s2++;
    }

    if (*s1 == *s2)
        return 0;
    else
        return *s1 < *s2 ? -1 : 1;
}

/**
 * string_starts_with - checks if a string starts with a prefix
 * @str: the string to search
 * @prefix: the prefix to find
 * Return: pointer to the next character of str after the prefix or NULL
 */
char *string_starts_with(const char *str, const char *prefix)
{
    while (*prefix)
    {
        if (*prefix++ != *str++)
            return NULL;
    }
    return (char *)str;
}

/**
 * string_concatenate - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 * Return: pointer to the destination buffer
 */
char *string_concatenate(char *destination, const char *source)
{
    char *result = destination;

    while (*destination)
        destination++;

    while (*source)
        *destination++ = *source++;

    *destination = *source;

    return result;
}

