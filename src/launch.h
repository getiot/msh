#ifndef __MSH_LAUNCH_H__
#define __MSH_LAUNCH_H__

int launch_process(char **args);
bool is_child_process_running();
char *get_executable_path(char *command);

#endif