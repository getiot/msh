#ifndef __MSH_SHELL_H__
#define __MSH_SHELL_H__

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "config.h"
#include "shell.h"
#include "color.h"
#include "launch.h"
#include "commands/ls.h"
#include "commands/cd.h"

void process_input();
void free_input();
bool check_command(char *command);
bool exist_in_path();
bool start_with(char *prefix);
void get_current_folder(char *output);
void restart_input();
bool process_key(unsigned char c);
void line_loop();
int  input_loop();
void sigint_handler();

#endif