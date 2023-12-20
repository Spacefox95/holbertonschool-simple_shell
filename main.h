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

/* GLOBAL VARIABLE */

extern char **environ;

/* LINKED LIST STRUCT */

struct node {
	char *dir;
	struct node *next;
};

/* PROTOTYPES */

int find_cmd_path(char *cmd, char *work_buffer);
int file_exist(char *file);
int execute_command(char *argv[]);
char **fill_args(char *input_buffer);
void print_env(void);
int shell_error(void);
char *_getenv(const char *name);
struct node *create_path_dir_list(char *path);
void free_path_list(struct node *head);

#endif
