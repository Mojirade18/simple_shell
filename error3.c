#include "shell.h"

int myErrAtoi(char *str) {
    int i = 0;
    unsigned long int result = 0;

    if (*str == '+')
        str++;  // Skip the plus sign (if present)

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result *= 10;
            result += (str[i] - '0');
            if (result > INT_MAX)
                return -1;  // Overflow
        } else {
            return -1;  // Non-numeric character
        }
    }

    return result;
}

void printErrorMessage(info_t *info, const char *errorString) {
    myEputs(info->programName);
    myEputs(": ");
    myEputs(info->lineNumber);
    myEputs(": ");
    myEputs(info->commandName);
    myEputs(": ");
    myEputs(errorString);
}

int printDecimal(int number, int fd) {
    int (*putCharFunc)(char) = myPutchar;
    int i, count = 0;
    unsigned int absNumber, current;

    if (fd == STDERR_FILENO)
        putCharFunc = myEputchar;

    if (number < 0) {
        absNumber = -number;
        putCharFunc('-');
        count++;
    } else {
        absNumber = number;
    }

    current = absNumber;

    for (i = 1000000000; i > 1; i /= 10) {
        if (absNumber / i) {
            putCharFunc('0' + current / i);
            count++;
        }
        current %= i;
    }

    putCharFunc('0' + current);
    count++;

    return count;
}

char *convertNumber(long int num, int base, int flags) {
    static char *digitArray;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0) {
        n = -num;
        sign = '-';
    }

    digitArray = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do {
        *--ptr = digitArray[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;

    return ptr;
}

void removeComments(char *line) {
    int i;

    for (i = 0; line[i] != '\0'; i++) {
        if (line[i] == '#' && (!i || line[i - 1] == ' ')) {
            line[i] = '\0';
            break;
        }
    }
}

