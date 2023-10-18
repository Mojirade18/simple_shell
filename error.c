#include "myshell.h"

void myEputs(char *str) {
    int i = 0;

    if (!str)
        return;

    while (str[i] != '\0') {
        myEputchar(str[i]);
        i++;
    }
}

int myEputchar(char c) {
    static int i;
    static char buf[MY_WRITE_BUF_SIZE];

    if (c == MY_BUF_FLUSH || i >= MY_WRITE_BUF_SIZE) {
        write(2, buf, i);
        i = 0;
    }

    if (c != MY_BUF_FLUSH)
        buf[i++] = c;

    return 1;
}

int myPutFd(char c, int fd) {
    static int i;
    static char buf[MY_WRITE_BUF_SIZE];

    if (c == MY_BUF_FLUSH || i >= MY_WRITE_BUF_SIZE) {
        write(fd, buf, i);
        i = 0;
    }

    if (c != MY_BUF_FLUSH)
        buf[i++] = c;

    return 1;
}

int myPutsFd(char *str, int fd) {
    int i = 0;

    if (!str)
        return 0;

    while (*str) {
        i += myPutFd(*str++, fd);
    }

    return i;
}

