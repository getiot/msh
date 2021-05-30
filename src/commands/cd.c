#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>

#include "../config.h"

int command_cd(char *path)
{
    if (path[0] == '~') {
        char *home_path;

        if ((home_path = getenv("HOME")) == NULL) {
            home_path = getpwuid(getuid())->pw_dir;
        }

        char new_path[MAX_PATH_LENGTH];
        strcpy(new_path, home_path);
        strcat(new_path, path + 1);
        path = new_path;
    }

    int error = chdir(path);
    if (error) {
        printf("Unable to change directory to \"%s\".\n", path);
    }
    return error;
}