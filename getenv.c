#include "main.h"

/**
 * _getenv - function to get the value of an env variable
 * @name: name of the values
 * Return: pointer to the value of the variable, NULL il failed
 */

char *_getenv(const char *name)
{
	int i;
	size_t name_len;

	if (name == NULL || environ == NULL)
		return (NULL);

	name_len = strlen(name);

	for (i = 0 ; environ[i] != NULL ; i++)
	{
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			return (&environ[i][name_len + 1]);
		}
	}
	return (NULL);
}
