#include "shell.h"

int myHistory(info_t *info) {
    printCommandList(info->history);
    return 0;
}

int unsetAlias(info_t *info, char *aliasString) {
    char *equalsPosition, originalChar;
    int ret;

    equalsPosition = _strchr(aliasString, '=');

    if (!equalsPosition)
        return 1;

    originalChar = *equalsPosition;
    *equalsPosition = '\0';

    ret = deleteNodeAtIndex(&(info->alias), getNodeIndex(info->alias, nodeStartsWith(info->alias, aliasString, -1)));

    *equalsPosition = originalChar;
    return ret;
}

int setAlias(info_t *info, char *aliasString) {
    char *equalsPosition;

    equalsPosition = _strchr(aliasString, '=');

    if (!equalsPosition)
        return 1;

    if (!*++equalsPosition)
        return unsetAlias(info, aliasString);

    unsetAlias(info, aliasString);

    return (addNodeEnd(&(info->alias), aliasString, 0) == NULL);
}

int printAlias(list_t *node) {
    char *equalsPosition = NULL, *aliasName = NULL;

    if (node) {
        equalsPosition = _strchr(node->str, '=');
        for (aliasName = node->str; aliasName <= equalsPosition; aliasName++)
            _putchar(*aliasName);

        _putchar('\'');
        _puts(equalsPosition + 1);
        _puts("'\n");
        return 0;
    }
    return 1;
}

int myAlias(info_t *info) {
    int i = 0;
    char *equalsPosition = NULL;
    list_t *node = NULL;

    if (info->argc == 1) {
        node = info->alias;
        while (node) {
            printAlias(node);
            node = node->next;
        }
        return 0;
    }

    for (i = 1; info->argv[i]; i++) {
        equalsPosition = _strchr(info->argv[i], '=');
        if (equalsPosition)
            setAlias(info, info->argv[i]);
        else
            printAlias(nodeStartsWith(info->alias, info->argv[i], '='));
    }
    return 0;
}

