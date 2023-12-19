#include "main.h"

/*
 *
 */

struct node *create_path_dir_list(char *path)
{
	struct node *head = NULL;
	struct node *tail = NULL;

	char *dir = strtok(path, ":");
	struct node *new_node;

	while (dir != NULL)
	{
		new_node = malloc(sizeof(struct node));
		if (new_node == NULL)
		{
			fprintf(stderr, "memory allocation error\n");
			return (NULL);
		}
		new_node->dir = strdup(dir);
		new_node->next = NULL;

		if (head == NULL)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
		dir = strtok(NULL, ":");
	}
	return (head);
}
