#include "main.h"

/**
 * fill_args - Tokenizes a string into an array of arguments.
 * @input_buffer: The string to tokenize.
 * Return: The number of arguments filled into the array.
 */


char **fill_args(char *input_buffer)
{
	int i = 0;
	char *token;
	char **args = NULL;

	token = strtok(input_buffer, " ");
	while (token)
	{
		args = realloc(args, (i + 1) * sizeof(char *));
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}

	args = realloc(args, (i + 1) * sizeof(char *));
	args[i] = NULL;
	return (args);
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
		return (0);

	return (1);
}

/**
 * find_cmd_path - finds full path of a command in PATH environment variable.
 * @cmd: The command to find
 * @work_buffer: The buffer to store the full path.
 * Return: 0 if the command is found, 1 otherwise.
 */

int find_cmd_path(char *cmd, char *work_buffer)
{
	char *token;
	char *var_path;

	var_path = strdup(getenv("PATH"));
	if (var_path == NULL)
	{
		perror("./shell");
		return (1);
	}

	token = strtok(var_path, ":");

	while (token)
	{
		if (sprintf(work_buffer, "%s/%s", token, cmd) < 0)
		{
			free(var_path);
			return (1);
		}

		if (file_exist(work_buffer) == 0)
		{
			free(var_path);
			return (0);
		}
		token = strtok(NULL, ":");
	}
	free(var_path);
	return (1);
}

/**
 * execute_command - Executes a command.
 * @argv: The array of arguments for the command.
 * Return: 0 on success, 1 on failure.
 */


int execute_command(char **argv)
{
	pid_t child_pid;
	int status;
	char *cmd = argv[0], *work_buffer;

	work_buffer = malloc(1024);
	if (work_buffer == NULL)
	{
		perror("./shell");
		return (1);
	}
	/*init avec valeur reçue*/
	strcpy(work_buffer, cmd);
	/* Si la commande commence par un chemin (/ ou .) : exécution directe */
	if (cmd[0] != '/' && strncmp(cmd, "./", 2) > 0)
	{
		if (find_cmd_path(cmd, work_buffer) == 1)
		{
			free(work_buffer);
			perror("./shell");
			return (1);
		}
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("./shell");
		return (1);
	}
	if (child_pid == 0)
	{
		execve(work_buffer, argv, NULL);
		perror("./shell");
		return (1);
	}
	else
	{
		wait(&status);
		free(work_buffer);
	}
	return (0);
}
/**
 * main - The main function of the shell.
 * Return: 0 on success, 1 on failure.
 */

int main(void)
{
	char *input_buffer = NULL;
	char **myargv;
	size_t size_allocated;
	int char_read;
	int do_not_exit = 1;


	do {
		if (isatty(STDIN_FILENO))
			printf("#simple_shell$ ");

		char_read = getline(&input_buffer, &size_allocated, stdin);

		if (char_read == EOF)
		{
			free(input_buffer);
			if (isatty(STDIN_FILENO))
				putchar('\n');
			return (1);
		}

		input_buffer[char_read - 1] = 0;
		myargv = fill_args(input_buffer);

		do_not_exit = strcmp(input_buffer, "exit");

		if (do_not_exit != 0)
			execute_command(myargv);

		free(myargv);

	} while (do_not_exit != 0);
	free(input_buffer);
	return (0);
}

