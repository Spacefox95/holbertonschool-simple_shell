#include "main.h"


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
		return (shell_error());

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
 * @envp: environment.
 * @argv: The array of arguments for the command.
 * Return: 0 on success, 1 on failure.
 */


int execute_command(char **argv, char **envp)
{
	pid_t child_pid;
	int status;
	char *cmd = argv[0], *work_buffer;

	work_buffer = malloc(1024);
	if (work_buffer == NULL)
		return (shell_error());
	if (strcpy(work_buffer, cmd) != work_buffer)/*init avec valeur reçue*/
	{
		free(work_buffer);
		return (shell_error());
	}
	if (cmd[0] != '/' && strncmp(cmd, "./", 2) > 0)/* / ./: exec direct*/
	{
		if (find_cmd_path(cmd, work_buffer) == 1)
		{
			free(work_buffer);
			return (shell_error());
		}
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		free(work_buffer);
		return (shell_error());
	}
	if (child_pid == 0)
	{
		if (execve(work_buffer, argv, envp) == -1)
		{
			free(work_buffer);
			exit (shell_error());
		}
	}
	else
	{
		wait(&status);
		free(work_buffer);
	}
	return (0);
}
