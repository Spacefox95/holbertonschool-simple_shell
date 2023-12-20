#include "main.h"

/**
 * print_env - print environment
 * Return: void
 */

void print_env(void)
{
	int ctr_env = 0;

	while (environ[ctr_env] != NULL)
	{
		printf("%s\n", environ[ctr_env]);
		ctr_env++;
	}
}
