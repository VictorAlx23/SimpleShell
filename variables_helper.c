#include "shell.h"
/**
* is_chains - test if current char in buffer is a chain delimeter
* @info: the parameter struct
* @buff: the char buffer
* @pn: address of current position in buf
*
* Return: 1 if chain delimeter, 0 otherwise
*/
int is_chains(info_t *info, char *buff, size_t *pn)
{
	size_t v = *pn;

	if (buff[v] == '|' && buff[v + 1] == '|')
	{
		buff[v] = 0;
		v++;
		info->cmd_buff_type = CMD_OR;
	}
	else if (buff[v] == '&' && buff[v + 1] == '&')
	{
		buff[v] = 0;
		v++;
		info->cmd_buff_type = CMD_AND;
	}
	else if (buff[v] == ';')
	{
		buff[v] = 0;
		info->cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*pn = v;
	return (1);
}
/**
* check_chains - checks we should continue chaining based on last status
* @info: the parameter struct
* @buff: the char buffer
* @pn: address of current position in buf
* @index: starting position in buf
* @length: length of buff
* Return: Void
*/
void check_chains(info_t *info, char *buff, size_t *pn,
		size_t index, size_t length)
{
	size_t v = *pn;

	if (info->cmd_buff_type == CMD_AND)
	{
		if (info->status)
		{
			buff[index] = 0;
			v = length;
		}
	}
	if (info->cmd_buff_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[index] = 0;
			v = length;
		}
	}
	*pn = v;
}
/**
* replaces_alias - replaces an aliases in the tokenized string
* @info: the parameter struct
* Return: 1 if replaced, 0 otherwise
*/
int replaces_alias(info_t *info)
{
	int index = 0;
	list_t *node;
	char *pn;

	while (index < 10)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		pn = _strchr(node->strs, '=');
		if (!pn)
			return (0);
		pn = _strdup(pn + 1);
		if (!pn)
			return (0);
		info->argv[0] = pn;
		index++;
	}
	return (1);
}
/**
* replaces_vars - replaces vars in the tokenized string
* @info: the parameter struct
* Return: 1 if replaced, 0 otherwise
*/
int replaces_vars(info_t *info)
{
	int index = 0;
	list_t *node;

	for (index = 0; info->argv[index]; index++)
	{
	if (info->argv[index][0] != '$' || !info->argv[index][1])
		continue;
	if (!_strcmp(info->argv[index], "$?"))
	{
		replace_strings(&(info->argv[index]),
		_strdup(converts_num(info->status, 10, 0)));
		continue;
	}
	if (!_strcmp(info->argv[index], "$$"))
	{
		replace_strings(&(info->argv[index]),
		_strdup(converts_num(getpid(), 10, 0)));
		continue;
	}
	node = node_starts_with(info->envs, &info->argv[index][1], '=');
	if (node)
	{
		replace_strings(&(info->argv[index]),
		_strdup(_strchr(node->strs, '=') + 1));
		continue;
	}
	replace_strings(&info->argv[index], _strdup(""));
	}
	return (0);
}
/**
* replace_strings - replaces string
* @old_s: address of old string
* @new_s: new string
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_strings(char **old_s, char *new_s)
{
	free(*old_s);
	*old_s = new_s;
	return (1);
}
