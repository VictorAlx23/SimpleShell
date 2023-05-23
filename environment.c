#include "shell.h"

/**
 * _shellenv - prints the current enviroment
 * @info: structure containing potential arguments.
 * Used to maintain constant function prototype
 * Return: Always 0
 */

int _shellenv(info_t *info)
{
	printlist_str(info->envs);
	return (0);
}

/**
 * _getenvs - gets the value of an enviroment variable
 * @info: Structure containing potentialo arguments.
 * Used to maintain constant function prototype
 * @var_name: enviroment variable name
 * Return: Value of the environment
 */

char *_getenvs(info_t *info, const char *var_name)
{
	list_t *node = info->envs;
	char *pn;

	while (node)
	{
		pn = starts_with(node->strs, var_name);
		if (pn && *pn)
			return (pn);
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
		_eputs("incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
* _shunsetenv - Remove an environment variable
* @_info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/

int _shunsetenv(info_t *_info)
{
	int index;
	if (_info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (index = 1; index <= _info->argc; index++)
		_unsetenv(_info, _info->argv[index]);
	return (0);
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

	for (index = 0; environ[index]; index++)
		addnodeend(&node, environ[index], 0);
	info->envs = node;
	return (0);
}
