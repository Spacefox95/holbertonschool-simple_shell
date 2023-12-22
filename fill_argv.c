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

	/* ignore heading spaces and tabs */
	while (*input_buffer == ' ' || *input_buffer == '\t')
		input_buffer++;

	token = strtok(input_buffer, " ");
	while (token != NULL)
	{
		/* get contiguous memory allocation simplifies code/freeing process */
		argv = realloc(argv, (token_count + 1) * sizeof(char *));
		if (argv == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}

		argv[token_count] = token;
		token = strtok(NULL, " ");
		token_count++;
	}
	/* alloc for end of argv NULL */
	argv = realloc(argv, (token_count + 1) * sizeof(char *));
	if (argv == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	argv[token_count] = NULL;
	return (argv);
}
