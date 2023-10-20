#include "shell.h"

/**
 * fill_memory - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @byte: the byte to fill *s with
 * @n: the number of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *fill_memory(char *s, char byte, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
        s[i] = byte;

    return s;
}

/**
 * free_string_array - frees an array of strings
 * @str_array: array of strings
 */
void free_string_array(char **str_array)
{
    char **ptr = str_array;

    if (!str_array)
        return;

    while (*str_array)
    {
        free(*str_array++);
    }
    free(ptr);
}

/**
 * custom_realloc - reallocates a block of memory
 * @ptr: pointer to the previous malloc'ed block
 * @old_size: byte size of the previous block
 * @new_size: byte size of the new block
 * Return: pointer to the reallocated block
 */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *p;

    if (!ptr)
        return malloc(new_size);

    if (!new_size)
        return free(ptr), NULL;

    if (new_size == old_size)
        return ptr;

    p = malloc(new_size);
    if (!p)
        return NULL;

    old_size = old_size < new_size ? old_size : new_size;

    while (old_size--)
    {
        p[old_size] = ((char *)ptr)[old_size];
    }
    free(ptr);
    return p;
}

