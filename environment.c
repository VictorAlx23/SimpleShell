#include "shell.h"
/**
 * _shellenv - prints the current enviroment
 * @info: structure containing potential arguments.
 * Used to maintain constant function prototype
 * Return: Always 0
 */
int _shellenv(info_t *info)
{
	prints_lists_str(info->env);
	return (0);
}
/**
 * _valenv - gets the value of an enviroment variable
 * @info: Structure containing potentialo arguments.
 * Used to maintain constant function prototype
 * @name: enviroment variable name
 * Return: Value of the environment
 */
char *_valenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = start_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}
/**
 * _shsetenv - initialises a new environment variable,
 * or modify an existing one
 * @info: structure containing potential arguments.
 * Used to maintain constant function prototype
 * Return: always 0
 */
int _shsetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("incorrect number of arguments.Check\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
/**
 * populate_env_lists - populate env linked list
 * @info: structure containing potential arguments.
 * Used to maintain constant function prototype
 * Return: Always 0
 */
int populate_env_lists(info_t *info)
{
	list_t *node = NULL;
	size_t index;

	index = 0;
	while (environs[index])
	{
		addnodeend(&node, environs[index], 0);
		index++;
	}
	info->env = node;
	return (0);
}