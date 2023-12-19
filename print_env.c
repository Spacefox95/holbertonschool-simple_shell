#include "main.h"

/**
 * print_env - print environment
 * @envp: environment
 * Return: void
 */

void print_env(char *envp[])
{
	int ctr_env = 0;

	while (envp[ctr_env] != NULL)
	{
		printf("%s\n", envp[ctr_env]);
		ctr_env++;
	}
}
