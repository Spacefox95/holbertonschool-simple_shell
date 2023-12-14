#include "main.h"

/**
 * fill_args - Tokenizes a string into an array of arguments.
 * @input_buffer: The string to tokenize.
 * @argv: The array to fill with the tokenized arguments.
 * Return: The number of arguments filled into the array.
 */


int fill_args(char *input_buffer, char ***argv)
{
	char *token;
	int ctr = 0;

	*argv = NULL;

	token = strtok(input_buffer, " ");
	while (token != NULL)
	{
		/* ctr+1 : nombre allocs taille sizeof */
		(*argv) = realloc((*argv), (ctr + 1) * sizeof(char *));
		(*argv)[ctr] = token;
		ctr++;
		token = strtok(NULL, " ");
	}
	(*argv) = realloc((*argv), (ctr + 1) * sizeof(char *));
	(*argv)[ctr] = NULL;
	return (ctr);
}

/**
 * file_exist - Checks if a file exists.
 * @file: The name of the file to check.
 * Return: 0 if the file exists, 1 otherwise.
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
		perror("./shell");
		return (1);
	}

}

/**
 * execute_command - Executes a command.
 * @argv: The array of arguments for the command.
 * Return: 0 on success, 1 on failure.
 */


int execute_command(char *argv[])
{
	pid_t child_pid;
	int status;
	char *cmd = argv[0];

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
		execve(cmd, argv, NULL);
		perror("Error");
		return (1);
	}
	else
	{
		wait(&status);
	}
	return (0);
}

/**
 * main - The main function of the shell.
 *
 * Return: 0 on success, 1 on failure.
 */

int main(void)
{
	char *input_buffer = NULL;
	char **myargv = NULL;
	size_t size_allocated;
	size_t char_read;

	do {
		printf("#cisfun$ ");
		char_read = getline(&input_buffer, &size_allocated, stdin);

		if (char_read == 1)
			continue;
		if (char_read == -1 || char_read == EOF) 
		{
			free(input_buffer);
			perror("Error");
		}

		if (char_read == SIZE_MAX)
		{
			free(input_buffer);
			putchar('\n');
			return (1);
		}
		input_buffer[char_read - 1] = 0;
		fill_args(input_buffer, &myargv);

		if (execute_command(myargv) == 1)
		{
			printf("echec execute_command\n");
			free(myargv);
		}

	} 
	while (strcmp(input_buffer, "exit") != 0);
	free(input_buffer);
	return (0);
}
