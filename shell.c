#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
/*
 *
 *
 */

/*int file_exist(char *file)
{
	struct stat st;

	if (stat(file, &st) == 0)
	{
		printf(" FOUND\n");
		return (0);
	}
	else
	{
		printf("%s NOT FOUND\n", file);
		perror("Error");
		return (-1);
	}

}

int execute_command(char *cmd)
{
	if (file_exist(cmd) == -1)
		return (-1);
	printf("execution %s\n", cmd);
	return(0);
}*/

int main (int argc, char **argv)
{
	char *input_buffer;
	size_t size_allocated;
	size_t char_read;
	int i;

	do {
		printf("$ ");
		char_read = getline(&input_buffer, &size_allocated, stdin);

		if (char_read < 0)
		{
			fprintf(stderr, "getline failed\n");
			free(input_buffer);
			return(-1);
		}

		if (char_read == SIZE_MAX)
		{
			free(input_buffer);
			putchar('\n');
			return(-2);
		}
		if (char_read != -1)
		{
			printf("%s\n", input_buffer);
			free(input_buffer);
		}
		/*for (i = 0; i < char_read; i++)
		  printf("%d ", input_buffer[i]);
		  putchar('\n');*/
		input_buffer[char_read - 1] = 0;
		/*if (execute_command(input_buffer) == -1)
			printf("echec execute_command\n");*/

	} while (strcmp(input_buffer, "exit") != 0);
	free(input_buffer);
	return (0);
}
