#include "main.h"

/**
 * shell_error - print default error message
 *
 * Return: void
 */

int shell_error(char *cmd, int err)
{
	if (cmd == NULL)
		fprintf(stderr, "./hsh: %d: %s: %s\n", err, cmd, strerror(err));
	else if (err == 127)
		fprintf(stderr, "./hsh: %d: %s: %s\n", 1, cmd, "not found");
	else
		fprintf(stderr, "./hsh: %d: %s: %s\n", 1, cmd, strerror(err));

	return (EXIT_FAILURE);
}
