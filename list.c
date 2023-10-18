#include "shell.h"

/**
 * list_length - determines the length of a linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t list_length(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        head = head->next;
        count++;
    }

    return count;
}

/**
 * list_to_strings - returns an array of strings from the list->str
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
    list_t *current = head;
    size_t size = list_length(head);
    char **strings;
    char *str;

    if (!head || size == 0)
        return NULL;

    strings = malloc(sizeof(char *) * (size + 1));
    if (!strings)
        return NULL;

    for (size_t i = 0; current; current = current->next, i++)
    {
        str = malloc(_strlen(current->str) + 1);
        if (!str)
        {
            for (size_t j = 0; j < i; j++)
                free(strings[j]);
            free(strings);
            return NULL;
        }

        str = _strcpy(str, current->str);
        strings[i] = str;
    }

    strings[size] = NULL;
    return strings;
}

/**
 * print_list - prints all elements of a list_t linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_list(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        _puts(convert_number(head->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(head->str ? head->str : "(nil)");
        _puts("\n");
        head = head->next;
        count++;
    }

    return count;
}

/**
 * node_starts_with - returns a node whose string starts with a prefix
 * @node: pointer to the list head
 * @prefix: string to match
 * @next_char: the next character after the prefix to match
 *
 * Return: matching node or NULL
 */
list_t *node_starts_with(list_t *node, char *prefix, char next_char)
{
    char *match = NULL;

    while (node)
    {
        match = starts_with(node->str, prefix);
        if (match && (next_char == -1 || *match == next_char))
            return node;
        node = node->next;
    }

    return NULL;
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to the list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
    size_t index = 0;

    while (head)
    {
        if (head == node)
            return index;

        head = head->next;
        index++;
    }

    return -1;
}

