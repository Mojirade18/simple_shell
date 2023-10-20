#include "shell.h"

/**
 * buffer_chained_commands - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @buffer_length: address of buffer length
 *
 * Return: bytes read
 */
ssize_t buffer_chained_commands(info_t *info, char **buffer, size_t *buffer_length)
{
    ssize_t bytes_read = 0;
    size_t buffer_position = 0;

    if (!*buffer_length) /* if nothing left in the buffer, fill it */
    {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, handle_interrupt);

#if USE_GETLINE
        bytes_read = getline(buffer, buffer_length, stdin);
#else
        bytes_read = custom_getline(info, buffer, buffer_length);
#endif

        if (bytes_read > 0)
        {
            if ((*buffer)[bytes_read - 1] == '\n')
            {
                (*buffer)[bytes_read - 1] = '\0'; /* remove trailing newline */
                bytes_read--;
            }
            info->linecount_flag = 1;
            remove_comments(*buffer);
            build_history_list(info, *buffer, info->histcount++);

            /* if (_strchr(*buffer, ';')) is this a command chain? */
            {
                *buffer_length = bytes_read;
                info->cmd_buffer = buffer;
            }
        }
    }
    return bytes_read;
}

/**
 * get_input_line - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input_line(info_t *info)
{
    static char *buffer; /* the ';' command chain buffer */
    static size_t buffer_start, buffer_end, buffer_length;
    ssize_t bytes_read = 0;
    char **buffer_ptr = &(info->argument), *position;

    _putchar(BUFFER_FLUSH);
    bytes_read = buffer_chained_commands(info, &buffer, &buffer_length);

    if (bytes_read == -1) /* EOF */
        return -1;

    if (buffer_length) /* we have commands left in the chain buffer */
    {
        buffer_end = buffer_start; /* init new iterator to current buffer position */
        position = buffer + buffer_start; /* get pointer for return */
        check_command_chain(info, buffer, &buffer_end, buffer_start, buffer_length);

        while (buffer_end < buffer_length) /* iterate to semicolon or end */
        {
            if (is_command_chain(info, buffer, &buffer_end))
                break;
            buffer_end++;
        }

        buffer_start = buffer_end + 1; /* increment past nulled ';' */
        if (buffer_start >= buffer_length) /* reached the end of the buffer? */
        {
            buffer_start = buffer_length = 0; /* reset position and length */
            info->cmd_buffer_type = CMD_NORMAL;
        }
        *buffer_ptr = position; /* pass back pointer to the current command position */
        return _strlen(position); /* return the length of the current command */
    }

    *buffer_ptr = buffer; /* not a chain, pass back buffer from _getline() */
    return bytes_read; /* return the length of the buffer from _getline() */
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @buffer_length: size
 *
 * Return: bytes read
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *buffer_length)
{
    ssize_t bytes_read = 0;

    if (*buffer_length)
        return 0;

    bytes_read = read(info->readfd, buffer, READ_BUFFER_SIZE);

    if (bytes_read >= 0)
        *buffer_length = bytes_read;

    return bytes_read;
}

/**
 * custom_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @buffer_ptr: address of pointer to buffer, preallocated or NULL
 * @buffer_length: size of preallocated buffer if not NULL
 *
 * Return: number of bytes read
 */
int custom_getline(info_t *info, char **buffer_ptr, size_t *buffer_length)
{
    static char buffer[READ_BUFFER_SIZE];
    static size_t buffer_start, buffer_length;
    size_t buffer_position;
    ssize_t bytes_read, bytes_written;
    char *position = NULL, *new_position = NULL, *character;

    position = *buffer_ptr;

    if (position && buffer_length)
        buffer_position = *buffer_length;

    if (buffer_start == buffer_length)
        buffer_start = buffer_length = 0;

    bytes_read = read_buffer(info, buffer, &buffer_length);

    if (bytes_read == -1 || (bytes_read == 0 && buffer_length == 0))
        return -1;

    character = _strchr(buffer + buffer_start, '\n');
    buffer_position = character ? 1 + (size_t)(character - buffer) : buffer_length;
    new_position = _realloc(position, buffer_length, position ? position + buffer_position : buffer_position + 1);

    if (!new_position) /* MALLOC FAILURE! */
        return position ? free(position), -1 : -1;

    if (position)
        _strncat(new_position, buffer + buffer_start, buffer_position - buffer_start);
    else
        _strncpy(new_position, buffer + buffer_start, buffer_position - buffer_start + 1);

    buffer_length += buffer_position - buffer_start;
    buffer_start = buffer_position;
    position = new_position;

    if (buffer_length)
        *buffer_length = buffer_length;

    *buffer_ptr = position;

    return buffer_length;
}

/**
 * handle_interrupt - blocks Ctrl-C
 * @signal_number: the signal number
 *
 * Return: void
 */
void handle_interrupt(__attribute__((unused))int signal_number)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUFFER_FLUSH);
}

