#include "shell.h"
/**
 * addnode - it adds a node at the start of the list
 * @head: pointer address to the head node
 * @strs: strings field of the node
 * @nums: node index used by history
 * Return: list size
 */
list_t *addnode(list_t **head, const char *strs, int nums)
{
	list_t *n_head;

	if (!head)
		return (NULL);
	n_head = malloc(sizeof(list_t));
	if (!n_head)
		return (NULL);
	_memset((void *)n_head, 0, sizeof(list_t));
	n_head->nums = nums;
	if (strs)
	{
		n_head->strs = _strdup(strs);
		if (!n_head->strs)
		{
			free(n_head);
			return (NULL);
		}
	}
	n_head->next = *head;
	*head = n_head;
	return (n_head);
}
/**
 * addnodeend - adds a node to the end of a list
 * @head: pointer address to the head node
 * @strs: strings field of the node
 * @nums: node index used by history
 * Return: list size
 */
list_t *addnodeend(list_t **head, const char *strs, int nums)
{
	list_t *n_node, *node;

	if (!head)
		return (NULL);
	node = *head;
	n_node = malloc(sizeof(list_t));
	if (!n_node)
		return (NULL);
	_memset((void *)n_node, 0, sizeof(list_t));
	n_node->nums = nums;
	if (strs)
	{
		n_node->strs = _strdup(strs);
		if (!n_node->strs)
		{
			free(n_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = n_node;
	}
	else
		*head = n_node;
	return (n_node);
}
/**
 * printlist_str - prints only the string element of a list_t linked list
 * @h1: points to the first node
 * Return: list size
 */
size_t printlist_str(const list_t *h1)
{
	size_t index = 0;

	while (h1)
	{
		_puts(h1->strs ? h1->strs : "(nil)");
		_puts("\n");
		h1 = h1->next;
		index++;
	}
	return (index);
}
/**
 * delete_node_at_index - deletes a node at a given index
 * @head: points to the head node
 * @ind: index of the node to delete
 * Return: 1 on success, 0 on failure
 */

int delete_node_at_index(list_t **head, unsigned int ind)
{
	list_t *node, *pre_node;
	unsigned int index = 0;

	if (!head || !*head)
		return (0);
	if (!ind)
	{
		node = *head;
		*head = (*head)->next;
		free(node->strs);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (index == ind)
		{
			pre_node->next = node->next;
			free(node->strs);
			free(node);
			return (1);
		}
		index++;
		pre_node = node;
		node = node->next;
	}
	return (0);
}
/**
 * freelist - frees all the nodes of a given list
 * @headptr: pointer address to the head node
 * Return: Void
 */
void freelist(list_t **headptr)
{
	list_t *node, *n_node, *h;

	if (!headptr || !*headptr)
		return;
	h = *headptr;
	node = h;
	while (node)
	{
		n_node = node->next;
		free(node->strs);
		free(node);
		node = n_node;
	}
	*headptr = NULL;
}
