#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* PROTOTYPES */

int file_exist(char *file);
int execute_command(char *argv[]);
int fill_args(char *input_buffer, char ***argv);

#endif
