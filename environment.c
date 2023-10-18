#include "shell.h"

int myEnv(info_t *info) {
    printStringList(info->environment);
    return 0;
}

char *myGetenv(info_t *info, const char *name) {
    list_t *node = info->environment;
    char *ptr;

    while (node) {
        ptr = startsWith(node->str, name);
        if (ptr && *ptr)
            return ptr;
        node = node->next;
    }

    return NULL;
}

int mySetenv(info_t *info) {
    if (info->argc != 3) {
        ePuts("Incorrect number of arguments\n");
        return 1;
    }

    if (mySetEnvironmentVariable(info, info->args[1], info->args[2]))
        return 0;

    return 1;
}

int myUnsetenv(info_t *info) {
    int i;

    if (info->argc == 1) {
        ePuts("Too few arguments.\n");
        return 1;
    }

    for (i = 1; i <= info->argc; i++)
        myUnsetEnvironmentVariable(info, info->args[i]);

    return 0;
}

int populateEnvironmentList(info_t *info) {
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        addNodeEnd(&node, environ[i], 0);

    info->environment = node;
    return 0;
}

