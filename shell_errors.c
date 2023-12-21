#include "main.h"

/**
 * shell_error - print default error message
 *
 * @cmd: command
 * @err: error
 *
 * Return: void
 */

int shell_error(char *cmd, int err)
{
<<<<<<< HEAD
	if (cmd == NULL)
		fprintf(stderr, "./hsh: %d: %s: %s\n", err, cmd, strerror(err));
	else if (err == 127)
		fprintf(stderr, "./hsh: %d: %s: %s\n", 1, cmd, "not found");
	else
		fprintf(stderr, "./hsh: %d: %s: %s\n", 1, cmd, strerror(err));

=======
	perror("./hsh");
>>>>>>> 566a91201b9646c789470b32cb842f80820405cc
	return (EXIT_FAILURE);
}
