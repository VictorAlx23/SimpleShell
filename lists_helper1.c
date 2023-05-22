#include "shell.h"
/**
 * list_size - determine the length of a linked list
 * @h1: pointer to the first node
 * Return: list size
 */
size_t list_size(const list_t *h1)
{
	size_t index = 0;

	while (h1)
	{
		h1 = h1->next;
		index++;
	}
	return (index);
}
/**
 * list_to_string - returns an array of strings of the list->strs
 * @head: points to the first node
 * Return: array of strings
 */
char **list_to_string(list_t *head)
{
	list_t *node = head;
	size_t index = list_size(head), j;
	char **strs;
	char *str;

	if (!head || !index)
		return (NULL);
	strs = malloc(sizeof(char *) * (index + 1));
	if (!strs)
		return (NULL);
	for (index = 0; node; node = node->next, index++)
	{
		str = malloc(_strlen(node->strs) + 1);
		if (!str)
		{
			for (j = 0; j < index; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->strs);
		strs[index] = str;
	}
	strs[index] = NULL;
	return (strs);
}
/**
 * prints_list - prints all element of a given list_t linked list;
 * @h1: points to the first node
 * Return: list size
 */
size_t prints_list(const list_t *h1)
{
	size_t index = 0;

	while (h1)
	{
		_puts(converts_num(h1->nums, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h1->strs ? h1->strs : "(nil)");
		_puts("\n");
		h1 = h1->next;
		index++;
	}
	return (index);
}
/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: points to list head
 * @prefixm: string to match
 * @c1: the next character after the prefix to match
 * Return: Match node or null
 */
list_t *node_starts_with(list_t *node, char *prefixm, char c1)
{
	char *p1 = NULL;

	while (node)
	{
		p1 = starts_with(node->strs, prefixm);
		if (p1 && ((c1 == -1) || (*p1 == c1)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 * get_node_index - gets the index of a node
 * @head: points to list head
 * @node: points to the node
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
