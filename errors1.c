#include "shell.h"

/**
 * str_to_int - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in the string, converted number otherwise, -1 on error
 */
int str_to_int(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++;

    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return -1;
        }
        else
        {
            return -1;
        }
    }

    return (int)result;
}

/**
 * print_error - prints an error message
 * @info: the parameter and return info struct
 * @error_type: string containing the specified error type
 */
void print_error(info_t *info, char *error_type)
{
    error_puts(info->fname);
    error_puts(": ");
    print_d(info->line_count, STDERR_FILENO);
    error_puts(": ");
    error_puts(info->argv[0]);
    error_puts(": ");
    error_puts(error_type);
}

/**
 * print_decimal - prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 * Return: number of characters printed
 */
int print_decimal(int input, int fd)
{
    int (*output_char)(char) = _putchar;
    int i, count = 0;
    unsigned int absolute_value, current;

    if (fd == STDERR_FILENO)
        output_char = _eputchar;

    if (input < 0)
    {
        absolute_value = -input;
        output_char('-');
        count++;
    }
    else
    {
        absolute_value = input;
    }

    current = absolute_value;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (absolute_value / i)
        {
            output_char('0' + current / i);
            count++;
        }
        current %= i;
    }
    output_char('0' + current);
    count++;

    return count;
}

/**
 * int_to_str - converts a number to a string
 * @num: number to convert
 * @base: base of the number
 * @flags: argument flags
 * Return: converted string
 */
char *int_to_str(long int num, int base, int flags)
{
    static char *conversion_array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }

    conversion_array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = conversion_array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;

    return ptr;
}

/**
 * remove_comments - replaces the first instance of '#' with '\0' in a string
 * @buf: address of the string to modify
 */
void remove_comments(char *buf)
{
    int i;
    for (i = 0; buf[i] != '\0'; i++)
    {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
    }
}

