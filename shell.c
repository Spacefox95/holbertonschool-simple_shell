#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
/*
 *
 *
 */

int file_exist(char *file)
{
	struct stat st;

	if (stat(file, &st) == 0)
	{
		return (0);
	}
	else
	{
		perror("Error");
		return (1);
	}

}

int execute_command(char *cmd)
{
	pid_t child_pid;
	int status;
	char *token;
	char *delim = " ";

	if (file_exist(cmd) == 1)
		return (1);

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		return (1);
	}
	if (child_pid == 0)
	{
		token = strtok(cmd, delim);
		while (token != NULL)
		{
			token = strtok(NULL, delim);
		}
		execve(cmd, (char *[]) {NULL}, (char *[]) {NULL});
		perror("Error");
		return (1);
	}
	else
	{
		wait(&status);
	}
	return (0);
}

int main(int argc, char **argv)
{
	char *input_buffer;
	size_t size_allocated;
	size_t char_read;
	int i;

	do {
		printf("#cisfun$ ");
		char_read = getline(&input_buffer, &size_allocated, stdin);

		if (char_read < 0)
		{
			fprintf(stderr, "getline failed\n");
			free(input_buffer);
			return (1);
		}

		if (char_read == SIZE_MAX)
		{
			free(input_buffer);
			putchar('\n');
			return (1);
		}
		input_buffer[char_read - 1] = 0;
		if (execute_command(input_buffer) == 1)
			printf("echec execute_command\n");

	} while (strcmp(input_buffer, "exit") != 0);
	free(input_buffer);
	return (0);
}
