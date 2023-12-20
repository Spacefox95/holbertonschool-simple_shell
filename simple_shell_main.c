#include "main.h"

/**
 * main - The main function of the shell.
 * @argc: number of arguments
 * @argv: arguments
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */

int main(int argc, char *argv[])
{
	char *input_buffer = NULL, **myargv;
	size_t size_allocated;
	int char_read, ret = EXIT_SUCCESS;

	(void) argc;
	(void) argv;

	signal(SIGINT, SIG_IGN);
	do {
		if (isatty(STDIN_FILENO))
			printf("\033[0;39m#simple_shell(%d)$ ", getpid());

		fflush(stdin);
		char_read = getline(&input_buffer, &size_allocated, stdin);
		if (char_read == 1)
			continue;
		if (char_read == EOF)
		{
			free(input_buffer);
			if (isatty(STDIN_FILENO))
				putchar('\n');
			return (ret);   /* sortie du shell Ctrl-D */
		}

		input_buffer[char_read - 1] = 0; /* overwrite \n */
		if (strcmp(input_buffer, "env") == 0)
		{
			print_env();
			continue;
		}
		if (strcmp(input_buffer, "exit") == 0)
		{
			free(input_buffer);
			return (ret);  /* sortie du shell avec exit */
		}
		myargv = fill_args(input_buffer);
		ret = execute_command(myargv); /* ret=127 si command not found */
		free(myargv);

	} while (1);
}
