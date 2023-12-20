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
		return (EXIT_SUCCESS);

	return (EXIT_FAILURE);
}

/**
 * find_cmd_path - finds full path of a command in PATH environment variable.
 * @cmd: The command to find
 * @work_buffer: The buffer to store the full path.
 * Return: 0 if the command is found, 1 otherwise.
 */

int find_cmd_path(char *cmd, char *work_buffer)
{
	struct node *path_list = create_path_dir_list();
	while (path_list != NULL)
	{
		if (sprintf(work_buffer, "%s/%s", path_list->dir, cmd) < 0)
		{
			free_path_list(path_list);
			return (1);
		}

		if (file_exist(work_buffer) == 0)
		{
			return (0);
		}

		path_list = path_list->next;
	}

	return (1);
}

/**
 * execute_command - Executes a command.
 * @envp: environment.
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
		return (shell_error());

	if (strcpy(work_buffer, cmd) != work_buffer) /*init avec valeur reçue*/
	{
		free(work_buffer);
		return (shell_error());
	}
	if (find_cmd_path(cmd, work_buffer) == EXIT_FAILURE)
	{
		free(work_buffer);
		perror("./shell");
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
			return (shell_error());
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		free(work_buffer);
	}
	return (EXIT_SUCCESS);
}
