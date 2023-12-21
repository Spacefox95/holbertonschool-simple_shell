#include "main.h"

/**
 * shell_error - print default error message
 *
 * Return: void
 */

int shell_error(void)
{
	perror("./shell - not found");
	return (EXIT_FAILURE);
}
