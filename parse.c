#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *file_path)
{
    struct stat file_stat;

    (void)info;

    if (!file_path || stat(file_path, &file_stat))
        return (0);

    if (S_ISREG(file_stat.st_mode))
    {
        return 1;
    }

    return 0;
}

/**
 * dup_chars - duplicates characters from a string
 * @src: the source string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to a new buffer containing the duplicated characters
 */
char *dup_chars(char *src, int start, int stop)
{
    static char buffer[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++)
    {
        if (src[i] != ':')
        {
            buffer[k++] = src[i];
        }
    }

    buffer[k] = '\0';
    return buffer;
}

/**
 * find_path - finds the given command in the PATH string
 * @info: the info struct
 * @path_str: the PATH string
 * @command: the command to find
 *
 * Return: full path of the command if found, or NULL
 */
char *find_path(info_t *info, char *path_str, char *command)
{
    int i = 0, current_pos = 0;
    char *path;

    if (!path_str)
        return NULL;

    if (_strlen(command) > 2 && starts_with(command, "./"))
    {
        if (is_cmd(info, command))
            return command;
    }

    while (1)
    {
        if (!path_str[i] || path_str[i] == ':')
        {
            path = dup_chars(path_str, current_pos, i);
            if (!*path)
                _strcat(path, command);
            else
            {
                _strcat(path, "/");
                _strcat(path, command);
            }

            if (is_cmd(info, path))
                return path;

            if (!path_str[i])
                break;

            current_pos = i;
        }
        i++;
    }

    return NULL;
}

