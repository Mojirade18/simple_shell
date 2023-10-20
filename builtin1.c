#include "shell.h"

/**
 * display_history - displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int display_history(info_t *info)
{
    print_history_list(info->history);
    return (0);
}

/**
 * remove_alias - removes an alias associated with a string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(info_t *info, char *str)
{
    char *equal_sign, character;
    int result;

    equal_sign = _strchr(str, '=');
    if (!equal_sign)
        return (1);
    character = *equal_sign;
    *equal_sign = 0;
    result = delete_node_at_index(&(info->alias),
        get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *equal_sign = character;
    return (result);
}

/**
 * create_alias - creates an alias for a string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int create_alias(info_t *info, char *str)
{
    char *equal_sign;

    equal_sign = _strchr(str, '=');
    if (!equal_sign)
        return (1);
    if (!*++equal_sign)
        return (remove_alias(info, str));

    remove_alias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias_string - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias_string(list_t *node)
{
    char *equal_sign_position = NULL, alias_string = NULL;

    if (node)
    {
        equal_sign_position = _strchr(node->str, '=');
        for (alias_string = node->str; alias_string <= equal_sign_position; alias_string++)
            _putchar(*alias_string);
        _putchar('\'');
        _puts(equal_sign_position + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * manage_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int manage_alias(info_t *info)
{
    int i = 0;
    char *equal_sign_position = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_alias_string(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; info->argv[i]; i++)
    {
        equal_sign_position = _strchr(info->argv[i], '=');
        if (equal_sign_position)
            create_alias(info, info->argv[i]);
        else
            print_alias_string(node_starts_with(info->alias, info->argv[i], '='));
    }
    return (0);
}

