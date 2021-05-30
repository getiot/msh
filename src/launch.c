#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "config.h"
#include "tio.h"

static bool is_running = 0;

int launch_process(char **args)
{
    pid_t pid = fork();
    if (pid == 0) {
        restore_tio();
        if (execvp(args[0], args) == -1) {
            perror("launch");
        }
        exit(EXIT_SUCCESS);
    }
    else if (pid < 0) {
        perror("launch");
    }
    else {
        int status;
        is_running = 1;
        printf("Start child process %s at PID %d...\n", args[0], pid);
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));

        is_running = 0;
        set_tio();
        return status;
    }
    return 1;
}

bool is_child_process_running()
{
    return is_running;
}

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}


char *get_executable_path(char *command)
{
    char *env_path = getenv("PATH");
    int path_length = 1;
    char *path_array[MAX_PATH_NUMBER];
    int current_path_index = 0;
    int current_position = 0;
    path_array[current_path_index] = malloc(MAX_PATH_LENGTH);
    
    for (int i=0; i<strlen(env_path); i++) {
        if (env_path[i] == ':') {
            path_array[current_path_index][current_position] = '\0';
            current_position = 0;
            current_path_index++;
            path_array[current_path_index] = malloc(MAX_PATH_LENGTH);
            continue;
        }
        path_array[current_path_index][current_position] = env_path[i];
        current_position++;
    }

    path_array[current_path_index][current_position] = 0;
    path_array[current_path_index + 1] = 0;
    path_length = current_path_index + 1;

    for (int i=0; i<path_length; i++) {
        char *path = path_array[i];
        char *executable_path = (char *)malloc(MAX_PATH_LENGTH);
        strcpy(executable_path, path);
        strcat(executable_path, "/");
        strcat(executable_path, command);

        if (is_regular_file(executable_path)) {
            return executable_path;
        }
        else {
            free(executable_path);
        }
    }

    for (int i=0; i<path_length; i++) {
        free(path_array[i]);
    }
    return NULL;
}

