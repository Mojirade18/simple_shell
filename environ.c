#include "shell.h"

/**
 * display_environment - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int display_environment(info_t *info)
{
    print_list(info->env);
    return (0);
}

/**
 * get_environment_variable - gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: environment variable name
 *
 * Return: the value 
 */
char *get_environment_variable(info_t *info, const char *name) {
    char *name_copy = NULL;
    list_t *node = NULL;
    char *value = NULL;

    if (info->env) {
        name_copy = malloc(strlen(name) + 1);
        if (name_copy == NULL) {
            /* Handle memory allocation failure */
            return NULL; /* Or do something else as needed */
        }
        strcpy(name_copy, name);
        node = node_starts_with(info->env, name_copy, 0);
    } else {
        return NULL; /* Return NULL if env is empty */
    }

    if (node) {
        char *p = strchr(node->str, '=');
        if (p) {
            value = strdup(p + 1);
        }
    }

    free(name_copy); /* Free the allocated memory */

    return value; /* Return the value if found, or NULL if not found */
}


/**
 * set_environment_variable - Initialize a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int set_environment_variable(info_t *info)
{
    if (info->argc != 3)
    {
        puts("Incorrect number of arguments\n");
        return (1);
    }
    if (set_environment_variable(info))
        return (0);
    return (1);
}

/**
 * unset_environment_variable - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int unset_environment_variable(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        fprintf(stderr, "Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= info->argc; i++)
        set_environment_variable(info);

    return (0);
}

/**
 * populate_environment_list - populates the environment linked list
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int populate_environment_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    info->env = node;
    return (0);
}

