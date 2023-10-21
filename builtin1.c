#include "shell.h"

/**
 * display_history - Displays the history list, one command per line, preceded with line numbers, starting at 0.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int display_history(info_t *info)
{
    print_list(info->history);
    return 0;
}

/**
 * unset_alias - Unsets an alias by deleting it from the alias linked list.
 * @info: Structure containing potential arguments.
 * @alias: The alias to unset.
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *alias)
{
    char *equals_ptr, temp;
    int ret;

    equals_ptr = strchr(alias, '=');
    if (!equals_ptr)
        return 1;

    temp = *equals_ptr;
    *equals_ptr = 0;

    ret = delete_node_at_index(&(info->alias),
        get_node_index(info->alias, node_starts_with(info->alias, alias, -1)));

    *equals_ptr = temp;

    return ret;
}

/**
 * set_alias - Sets an alias to a given string.
 * @info: Structure containing potential arguments.
 * @alias: The alias string to set.
 * Return: Always 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *alias)
{
    char *equals_ptr;

    equals_ptr = strchr(alias, '=');
    if (!equals_ptr)
        return 1;

    if (!*++equals_ptr)
        return unset_alias(info, alias);

    unset_alias(info, alias);
    return add_node_end(&(info->alias), alias, 0) == NULL;
}

/**
 * print_single_alias - Prints a single alias string.
 * @node: The alias node.
 * Return: Always 0 on success, 1 on error.
 */
int print_single_alias(list_t *node)
{
    char *equals_ptr, *alias = NULL;

    if (node)
    {
        equals_ptr = strchr(node->str, '=');
        for (alias = node->str; alias <= equals_ptr; alias++)
            putchar(*alias);

        putchar('\'');
        puts(equals_ptr + 1);
        puts("'\n");
        return 0;
    }

    return 1;
}

/**
 * alias_builtin - Implements the alias builtin command (mimics the alias command).
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int alias_builtin(info_t *info)
{
    int i = 0;
    char *equals_ptr = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_single_alias(node);
            node = node->next;
        }
        return 0;
    }

    for (i = 1; info->argv[i]; i++)
    {
        equals_ptr = strchr(info->argv[i], '=');
        if (equals_ptr)
            set_alias(info, info->argv[i]);
        else
            print_single_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return 0;
}

