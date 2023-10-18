#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @memory: the pointer to the memory area
 * @byte: the byte to fill *memory with
 * @size: the amount of bytes to be filled
 * Return: (memory) a pointer to the memory area memory
 */
char *_memset(char *memory, char byte, unsigned int size)
{
    unsigned int i;

    for (i = 0; i < size; i++)
        memory[i] = byte;

    return memory;
}

/**
 * ffree - frees a string of strings
 * @str_array: string of strings
 */
void ffree(char **str_array)
{
    char **p = str_array;

    if (!str_array)
        return;

    while (*str_array)
        free(*str_array++);

    free(p);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to the previous malloc'ated block
 * @old_size: byte size of the previous block
 * @new_size: byte size of the new block
 * Return: pointer to the old block if successful, NULL if failed
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr;

    if (!ptr)
        return malloc(new_size);

    if (!new_size)
    {
        free(ptr);
        return NULL;
    }

    if (new_size == old_size)
        return ptr;

    new_ptr = malloc(new_size);

    if (!new_ptr)
        return NULL;

    old_size = old_size < new_size ? old_size : new_size;

    while (old_size--)
        new_ptr[old_size] = ((char *)ptr)[old_size];

    free(ptr);

    return new_ptr;
}

