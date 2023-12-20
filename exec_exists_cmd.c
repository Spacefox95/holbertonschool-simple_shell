#include "main.h"


/**
 * file_exist - Checks if a file exists.
 * @file: The name of the file to check.
 * Return: EXIT_SUCCESS if the file exists, EXIT_FAILURE otherwise.
 */


int file_exist(char *file)
{
	struct stat st;

	if (stat(file, &st) == 0)
		return (EXIT_SUCCESS);

	return (EXIT_FAILURE);
}

/**
 * find_cmd_path - finds full path of a command in PATH environment variable.
 * @cmd: The command to find
 * @work_buffer: The buffer to store the full path.
 * Return: EXIT_SUCCESS if the command is found, EXIT_FAILURE otherwise.
 */

int find_cmd_path(char *cmd, char *work_buffer)
{
	char *token;
	char *var_path;

	if (file_exist(cmd) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);

	var_path = strdup(_getenv("PATH"));
	if (var_path == NULL)
		return (shell_error());

	token = strtok(var_path, ":");
	while (token)
	{
		if (sprintf(work_buffer, "%s/%s", token, cmd) < 0)
		{
			free(var_path);
			return (EXIT_FAILURE);
		}

		if (file_exist(work_buffer) == EXIT_SUCCESS)
		{
			free(var_path);
			return (EXIT_SUCCESS);
		}
		token = strtok(NULL, ":");
	}
	free(var_path);
	return (EXIT_FAILURE);
}

/**
 * execute_command - Executes a command.
 * @argv: The array of arguments for the command.
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */

int execute_command(char **argv)
{
	pid_t child_pid;
	int status;
	char *cmd = argv[0], *work_buffer;

	work_buffer = malloc(1024);
	if (work_buffer == NULL)
		return (shell_error());

	if (strcpy(work_buffer, cmd) != work_buffer) /*init avec valeur reçue*/
	{
		free(work_buffer);
		return (shell_error());
	}
	if (find_cmd_path(cmd, work_buffer) == EXIT_FAILURE)
	{
		free(work_buffer);
		perror("./shell - not found");
		return (127); /* ret=127 si command not found */
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		free(work_buffer);
		return (shell_error());
	}
	if (child_pid == 0)
	{
		if (execve(work_buffer, argv, environ) == -1)
		{
			free(work_buffer);
			perror("./shell - not found");
			exit(127);
		}
		exit(EXIT_SUCCESS);
	}
	wait(&status);
	free(work_buffer);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}
