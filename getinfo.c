#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */
void clear_info(info_t *info)
{
    info->argument = NULL;
    info->arguments = NULL;
    info->path = NULL;
    info->argument_count = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
    int i = 0;
    info->filename = av[0];

    if (info->argument)
    {
        info->arguments = strtow(info->argument, " \t");
        if (!info->arguments)
        {
            info->arguments = malloc(sizeof(char *) * 2);
            if (info->arguments)
            {
                info->arguments[0] = _strdup(info->argument);
                info->arguments[1] = NULL;
            }
        }
        for (i = 0; info->arguments && info->arguments[i]; i++)
            ;
        info->argument_count = i;
        replace_alias(info);
        replace_vars(info);
    }
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
    ffree(info->arguments);
    info->arguments = NULL;
    info->path = NULL;
    
    if (all)
    {
        if (!info->command_buffer)
            free(info->argument);
        if (info->environment)
            free_list(&(info->environment));
        if (info->history)
            free_list(&(info->history));
        if (info->alias)
            free_list(&(info->alias));
        ffree(info->environ);
        info->environ = NULL;
        bfree((void **)info->command_buffer);
        if (info->readfd > 2)
            close(info->readfd);
        _putchar(BUF_FLUSH);
    }
}

