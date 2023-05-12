#include "shell.h"
/**
* _shellhistory - displays the history list, one command by line, preceded
* with line numbers, starting at 0.
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int _shellhistory(info_t *info)
{
	prints_list(info->history);
	return (0);
}
/**
* unstrset_alias - sets alias to string
* @info: parameter struct
* @strs: the string alias
*
* Return: Always 0 on success, 1 on error
*/
int unstrset_alias(info_t *info, char *strs)
{
	char *pn, ch;
	int rets;

	pn = _strchr(strs, '=');

	if (!pn)
		return (1);
	ch = *pn;
	*pn = 0;
	rets = delete_node_at_index(&(info->alias),
	get_node_index(info->alias, node_starts_with(info->alias, strs, -1)));
	*pn = ch;
	return (rets);
}
/**
* strset_alias - sets alias to string
* @info: parameter struct
* @strs: the string alias
*
* Return: Always 0 on success, 1 on error
*/
int strset_alias(info_t *info, char *strs)
{
	char *pn;

	pn = _strchr(strs, '=');

	if (!pn)
		return (1);
	if (!*++pn)
		return (unstrset_alias(info, strs));

	unstrset_alias(info, strs);
	return (addnodeend(&(info->alias), strs, 0) == NULL);
}
/**
* prints_alias - prints an alias string
* @node: the alias node
*
* Return: Always 0 on success, 1 on error
*/
int prints_alias(list_t *node)
{
	char *pn = NULL, *an = NULL;

	if (node)
	{
		pn = _strchr(node->strs, '=');
		for (an = node->strs; an <= pn; an++)
		_putchar(*an);
		_putchar('\'');
		_puts(pn + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
* _shalias - mimics the alias builtin (man alias)
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int _shalias(info_t *info)
{
	int index = 0;
	char *pn = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			prints_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (index = 1; info->argv[index]; index++)
	{
		pn = _strchr(info->argv[index], '=');
		if (pn)
			strset_alias(info, info->argv[index]);
		else
			prints_alias(node_starts_with(info->alias, info->argv[index], '='));
	}
	return (0);
}
