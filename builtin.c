#include "shell.h"

/**
 * exit_shell - Exits the shell with a given exit status
 * @info: Structure containing potential arguments.
 * Return: Exits the shell with a given exit status (0 if info->argv[0] != "exit")
 */
int exit_shell(info_t *info)
{
    int exit_status;

    if (info->argv[1]) /* If there is an exit argument */
    {
        exit_status = _erratoi(info->argv[1]);

        if (exit_status == -1)
        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            puts(info->argv[1]);
            putchar('\n');
            return 1;
        }

        info->err_num = exit_status;
        return -2;
    }

    info->err_num = -1;
    return -2;
}

/**
 * change_directory - Changes the current directory of the process
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int change_directory(info_t *info)
{
    char *current_dir, *dir;
    char buffer[1024];
    int chdir_ret;

    current_dir = getcwd(buffer, 1024);
    if (!current_dir)
        puts("TODO: >>getcwd failure emsg here<<\n");

    if (!info->argv[1])
    {
        dir = _getenv(info, "HOME=");
        if (!dir)
            chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    else if (strcmp(info->argv[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            puts(current_dir);
            putchar('\n');
            return 1;
        }

        puts(_getenv(info, "OLDPWD="));
        putchar('\n');
        chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
    }
    else
    {
        chdir_ret = chdir(info->argv[1]);
    }

    if (chdir_ret == -1)
    {
        print_error(info, "can't cd to ");
        puts(info->argv[1]);
        putchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }

    return 0;
}

/**
 * display_help - Displays help information (not yet implemented)
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int display_help(info_t *info)
{
    char **arguments = info->argv;
    puts("Help function is called. Function not yet implemented.\n");

    if (arguments)
        puts(*arguments); /* Temporary workaround to avoid unused variable warning */
    return 0;
}

