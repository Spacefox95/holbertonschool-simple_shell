#include "main.h"

/**
 * fill_args - Tokenizes a string into an array of arguments.
 * @input_buffer: The string to tokenize.
 * Return: The number of arguments filled into the array.
 */

char **fill_args(char *input_buffer)
{
	char *token;
	char **argv = NULL;
	int token_count = 0;

	while (*input_buffer == ' ' || *input_buffer == '\t')
		/* Go to the command input */
		input_buffer++;

	token = strtok(input_buffer, " "); /* Separate input into tokens */
	while (token != NULL)
	{
		argv = realloc(argv, (token_count + 1) * sizeof(char *));
		/* Allocate memory to save token */
		if (argv == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}

		argv[token_count] = token; /* Save token in argv */
		token = strtok(NULL, " \t\r\n");
		/* Free the token so it can check the next input */
		token_count++;
	}

	argv = realloc(argv, (token_count + 1) * sizeof(char *));
	if (argv == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	argv[token_count] = NULL;
	return (argv);
}
