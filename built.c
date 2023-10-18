#include "shell.h"

int myExit(info_t *info) {
    int exitStatus;

    if (info->args[1]) { /* If there is an exit argument */
        exitStatus = myAtoi(info->args[1]);

        if (exitStatus == -1) {
            info->status = 2;
            printError(info, "Illegal number: ");
            ePuts(info->args[1]);
            ePutchar('\n');
            return 1;
        }

        info->errorNumber = myAtoi(info->args[1]);
        return -2;
    }

    info->errorNumber = -1;
    return -2;
}

int myCd(info_t *info) {
    char *currentDir, *directory, buffer[1024];
    int chdirResult;

    currentDir = getcwd(buffer, 1024);

    if (!currentDir)
        myPuts("TODO: >>getcwd failure emsg here<<\n");

    if (!info->args[1]) {
        directory = myGetenv(info, "HOME=");

        if (!directory)
            chdirResult = /* TODO: what should this be? */
            chdir((directory = myGetenv(info, "PWD=")) ? directory : "/");
        else
            chdirResult = chdir(directory);
    } else if (myStrcmp(info->args[1], "-") == 0) {
        if (!myGetenv(info, "OLDPWD=")) {
            myPuts(currentDir);
            myPutchar('\n');
            return 1;
        }

        myPuts(myGetenv(info, "OLDPWD="));
        myPutchar('\n');
        chdirResult = /* TODO: what should this be? */
        chdir((directory = myGetenv(info, "OLDPWD=")) ? directory : "/");
    } else {
        chdirResult = chdir(info->args[1]);
    }

    if (chdirResult == -1) {
        printError(info, "can't cd to ");
        ePuts(info->args[1]);
        ePutchar('\n');
    } else {
        mySetenv(info, "OLDPWD", myGetenv(info, "PWD="));
        mySetenv(info, "PWD", getcwd(buffer, 1024));
    }

    return 0;
}

int myHelp(info_t *info) {
    char **argArray = info->args;

    myPuts("Help call works. Function not yet implemented\n");

    if (0) {
        myPuts(*argArray); /* temp att_unused workaround */
    }

    return 0;
}

