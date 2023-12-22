#include "main.h"

/**
 * main - The main function of the shell.
 * Return: EXIT_SUCCESS on success or return code > 0 if error.
 */

int main(void)
{
	char *input_buffer = NULL, **myargv;
	size_t size_allocated;
	int char_read, ret = EXIT_SUCCESS;

	signal(SIGINT, SIG_IGN); /* ignore ctrl-C signal */
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
			return (ret); /* exit shell with ctrl-D or | */
		}

		input_buffer[char_read - 1] = 0; /* overwrite \n */
		if (strncmp(input_buffer, "env", 3) == 0)
		{
			print_env();
			continue;
		}
		if (strncmp(input_buffer, "exit", 4) == 0)
		{
			free(input_buffer);
			return (ret); /* ret= return code of last cmd before exit */
		}
		myargv = fill_args(input_buffer);
		if (myargv[0] != NULL)
			ret = execute_command(myargv);
		free(myargv);
	} while (1);
}
