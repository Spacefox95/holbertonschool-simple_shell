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
	char *var_path, *var_value_path;

	/*
	 *	Ne chercher si existe que dans les cas où commande commence par / ou ./
	 *	Si c'est le cas : chemin absolu, ne pas passer par PATH
	 */
	if ((cmd[0] == '/' || strncmp(cmd, "./", 2) == 0) &&
			file_exist(cmd) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);

	var_value_path = _getenv("PATH");
	if (var_value_path == NULL)  /* si pas de variable PATH : unset PATH */
		return (EXIT_FAILURE);
	if (strlen(var_value_path) == 0)	/* si PATH= */
		return (EXIT_FAILURE);

	var_path = strdup(var_value_path);
	if (var_path == NULL)
		return (EXIT_FAILURE);

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
		fprintf(stderr, "./hsh: 1: %s: not found\n", cmd);
		free(work_buffer);
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
			fprintf(stderr, "./hsh: 1: %s: not found\n", cmd);
			free(work_buffer);
			exit(127);
		}
		exit(EXIT_FAILURE);
	}
	wait(&status);
	free(work_buffer);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

