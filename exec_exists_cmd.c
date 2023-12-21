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

int find_cmd_path(char *cmd, struct node *path_list, char *work_buffer)
{
	struct node *current = path_list;

	if (cmd[0] == '/' || strncmp(cmd, "./", 2) == 0)
	{
		if (file_exist(cmd) == EXIT_SUCCESS)
		{
			return (EXIT_SUCCESS);
		}
	}


	while (current != NULL) 
	{
		if (sprintf(work_buffer, "%s/%s", current->dir, cmd) < 0) 
		{
			perror("Error constructing path");
			free(current);
			return (EXIT_FAILURE);
		}
		printf("Debug: Constructed path: %s\n", work_buffer);

		if (file_exist(work_buffer) == EXIT_SUCCESS)
		{
			return (EXIT_SUCCESS);
		}

		current = current->next;
	}
	free(current);
	return (EXIT_FAILURE);

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
	struct node *path_list = create_path_dir_list(_getenv("PATH"));
	work_buffer = malloc(1024);
	if (work_buffer == NULL)
		return (shell_error());

	if (strcpy(work_buffer, cmd) != work_buffer) /*init avec valeur reçue*/
	{
		free(work_buffer);
		return (shell_error());
	}
	if (find_cmd_path(cmd, path_list, work_buffer) == EXIT_FAILURE)
	{
		free_path_list(path_list);
		free(work_buffer);
		perror("Error finding command path");
		return (127); /* ret=127 si command not found */
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		free_path_list(path_list);
		free(work_buffer);
		return (shell_error());
	}
	if (child_pid == 0)
	{
		if (execve(work_buffer, argv, environ) == -1)
		{
			free_path_list(path_list);
			free(work_buffer);
			perror("./shell - not found");
			exit(EXIT_FAILURE);
		}
	}
	wait(&status);
	free_path_list(path_list);
	free(work_buffer);
	if (WEXITSTATUS(status))
		status = WEXITSTATUS(status);
	return (status);
}
