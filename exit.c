#include "shell.h"

char *myStrncpy(char *destination, const char *source, int n) {
    int i, j;
    char *result = destination;

    i = 0;
    while (source[i] != '\0' && i < n - 1) {
        destination[i] = source[i];
        i++;
    }

    if (i < n) {
        j = i;
        while (j < n) {
            destination[j] = '\0';
            j++;
        }
    }

    return result;
}

char *myStrncat(char *destination, const char *source, int n) {
    int i, j;
    char *result = destination;

    i = 0;
    j = 0;
    while (destination[i] != '\0')
        i++;

    while (source[j] != '\0' && j < n) {
        destination[i] = source[j];
        i++;
        j++;
    }

    if (j < n)
        destination[i] = '\0';

    return result;
}

char *myStrchr(const char *str, int character) {
    do {
        if (*str == character)
            return (char *)str;
    } while (*str++ != '\0');

    return NULL;
}

