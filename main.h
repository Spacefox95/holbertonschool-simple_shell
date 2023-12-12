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

int main (int argc, char **argv);
int file_exist(char *file);
int execute_command(char *cmd);

#endif
