#include "shell.h"

/**
* get_env - string copy of the environment
* @_info: structure of information
* Return: 0 (success)
*/

char **get_env(info_t *_info)
{
	if (!_info->environs || _info->env_changed)
	{
		_info->environs = list_to_string(_info->envs);
		_info->env_changed = 0;
	}
	return (_info->environs);
}

/**
* _unsetenv - Removes an environment variable
* @_info: structure of information
* @item: variable property
* Return: 1 (deleted), 0 (not deleted)
*/

int _unsetenv(info_t *_info, char *item)
{
	list_t *head =  _info->envs;
	size_t ind = 0;
	char *ptr;

	if (!head || !item)
		return (0);

	while (head)
	{
		ptr = starts_with(head->strs, item);
		if (ptr && *ptr == '=')
		{
			_info->env_changed = delete_node_at_index(&(_info->envs), ind);
			ind = 0;
			head = _info->envs;
			continue;
		}
		head = head->next;
		ind++;
	}
	return (_info->env_changed);
}

/**
* _setenv - creat a new environment variable
* @_info: struct with information
* @_variable: variable property
* @var_data: variable value
* Return: 0(success)
*/

int _setenv(info_t *_info, char *_variable, char *var_data)
{
	char *ptr, *buffer = NULL;
	list_t *head;

	if (!_variable || !var_data)
		return (0);
	buffer = malloc(_strlen(_variable) + _strlen(var_data) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, _variable);
	_strcat(buffer, "=");
	_strcat(buffer, var_data);
	head = _info->envs;
	while (head)
	{
		ptr = starts_with(head->strs, _variable);
		if (ptr && *ptr == '=')
		{
			free(head->strs);
			head->strs = buffer;
			_info->env_changed = 1;
			return (0);
		}
		head = head->next;
	}
	addnodeend(&(_info->envs), buffer, 0);
	free(buffer);
	_info->env_changed = 1;
	return (0);
}
