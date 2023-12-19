#include "main.h"

/**
 * fill_args - Tokenizes a string into an array of arguments.
 * @input_buffer: The string to tokenize.
 * Return: The number of arguments filled into the array.
 */


char **fill_args(char *input_buffer)
{
	int i = 0, len;
	char *token;
	char **argv = NULL;

	token = strtok(input_buffer, " ");
	while (token)
	{
		argv = realloc(argv, (i + 1) * sizeof(char *));
		if (token[0] == '"')
			token++;
		len = strlen(token);
		if (token[len - 1] == '"')
			token[len - 1] = '\0';
		argv[i] = token;
		token = strtok(NULL, " ");
		i++;
	}

	argv = realloc(argv, (i + 1) * sizeof(char *));
	argv[i] = NULL;
	return (argv);
}
