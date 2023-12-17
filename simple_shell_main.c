#include "main.h"

/**
 * main - The main function of the shell.
 * @argc: number of arguments
 * @argv: arguments
 * @envp: environment
 * Return: 0 on success, 1 on failure.
 */

int main(int argc, char *argv[], char *envp[])
{
	char *input_buffer = NULL, **myargv;
	size_t size_allocated;
	int char_read, do_not_exit = 1;

	(void) argc;
	(void) argv;

	do {
		if (isatty(STDIN_FILENO))
			printf("#simple_shell$ ");

		char_read = getline(&input_buffer, &size_allocated, stdin);

		if (char_read == 1)
			continue;
		if (char_read == EOF)
		{
			free(input_buffer);
			if (isatty(STDIN_FILENO))
				putchar('\n');
			return (1);
		}

		input_buffer[char_read - 1] = 0;
		if (strcmp(input_buffer, "env") == 0)
		{
			print_env(envp);
			continue;
		}

		myargv = fill_args(input_buffer);
		do_not_exit = strcmp(input_buffer, "exit");

		if (do_not_exit != 0)
			execute_command(myargv);

		free(myargv);
	} while (do_not_exit != 0);
	free(input_buffer);
	return (0);
}
