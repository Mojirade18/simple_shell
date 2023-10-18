#include "shell.h"

int isInteractive(info_t *info) {
    return (isatty(STDIN_FILENO) && info->fileDescriptor <= 2);
}

int isDelimiter(char character, char *delimiters) {
    while (*delimiters) {
        if (*delimiters++ == character) {
            return 1;
        }
    }
    return 0;
}

int isAlphabetic(int character) {
    if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z')) {
        return 1;
    } else {
        return 0;
    }
}

int stringToInteger(char *inputString) {
    int index, sign = 1, numberFlag = 0, output;
    unsigned int result = 0;

    for (index = 0; inputString[index] != '\0' && numberFlag != 2; index++) {
        if (inputString[index] == '-') {
            sign *= -1;
        }

        if (inputString[index] >= '0' && inputString[index] <= '9') {
            numberFlag = 1;
            result *= 10;
            result += (inputString[index] - '0');
        } else if (numberFlag == 1) {
            numberFlag = 2;
        }
    }

    if (sign == -1) {
        output = -result;
    } else {
        output = result;
    }

    return output;
}

