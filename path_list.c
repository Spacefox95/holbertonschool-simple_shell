#include "main.h"

/**
 * free_path_list - function that free the linked list
 * @head: the head of the list
 */

void free_path_list(struct node *head)
{
	while (head != NULL)
	{
		struct node *temp = head;
		head = head->next;
		free(temp->dir);
		free(temp);
	}
}

/** 
 * create_path_dir_list - create a list of directories in the path
 * @path: the path
 * Return: NULL if fail, the first node otherwise
 */

struct node *create_path_dir_list(char *path)
{
	struct node *head = NULL;
	struct node *tail = NULL;
	char *token;

	if (path == NULL)
	{
		fprintf(stderr, "PATH environnement variable not found\n");
		return (NULL);
	}
	token = strtok(path, ":");
	while (token != NULL)
	{
		struct node *new_node = (struct node *) malloc(sizeof(struct node));
		if (new_node == NULL)
		{
			fprintf(stderr, "Memory allocation error\n");
			free_path_list(head);
			return (NULL);
		}
		new_node->dir = strdup(token);
		if (new_node->dir == NULL)
		{
			fprintf(stderr, "Memory allocation error\n");
			free_path_list(head);
			free(new_node);
			return (NULL);
		}
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
		token = strtok(NULL, ":");
	}
	return (head);
}

char *find_executable(struct node *path_list, const char *command)
{
	char *path;
	
	while (path_list != NULL) 
	{
		path = malloc(strlen(path_list->dir) + strlen(command) + 2);

		if (path == NULL) 
		{
			fprintf(stderr, "Memory allocation error\n");
			return (NULL);
		}

		sprintf(path, "%s/%s", path_list->dir, command);

		if (access(path, X_OK) == 0) 
		{
			return (path);
		}

		free(path);
		path_list = path_list->next;
	}

	return (NULL);
}