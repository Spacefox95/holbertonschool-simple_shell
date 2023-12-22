#include "main.h"

/**
 * main - The main function of the shell.
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */

int main(void)
{
	char *input_buffer = NULL, **myargv;
	size_t size_allocated;
	int char_read, ret = EXIT_SUCCESS;

	signal(SIGINT, SIG_IGN); /* Ignore the signal of process */
	do {
		if (isatty(STDIN_FILENO)) /* Check interactive mode */
			printf("\033[0;39m#simple_shell(%d)$ ", getpid());
		/* Display the prompt and the current process */

		fflush(stdin); /* Update stream */
		char_read = getline(&input_buffer, &size_allocated, stdin);
		/* Read the line from stream */
		if (char_read == 1)
			continue;
		if (char_read == EOF)
		{
			free(input_buffer);
			if (isatty(STDIN_FILENO))
				putchar('\n');
			return (ret);   /* Exit shell with Ctrl-D */
		}

		input_buffer[char_read - 1] = 0; /* Overwrite \n */
		if (strncmp(input_buffer, "env", 3) == 0) /* Print the environnement */
		{
			print_env();
			continue;
		}
		if (strncmp(input_buffer, "exit", 4) == 0)
		{
			free(input_buffer);
			return (ret);  /* Exit the shell with "exit" */
		}
		myargv = fill_args(input_buffer); /* Tokenize the input buffer */
		if (myargv[0] != NULL)
			ret = execute_command(myargv);
		/* Execute the command associated to the token */
		free(myargv);
	} while (1);
}
