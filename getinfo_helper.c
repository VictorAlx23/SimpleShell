#include "shell.h"
/**
* clears_info - initializes info_t struct
* @info: struct address
*/
void clears_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
* sets_info - initializes info_t struct
* @info: struct address
* @avs: argument vector
*/
void sets_info(info_t *info, char **avs)
{
	int index = 0;

	info->fname = avs[0];

	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");

		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (index = 0; info->argv && info->argv[index]; index++)
			info->argc = index;
		replace_alias(info);
		replace_vars(info);
	}
}
/**
* frees_info - frees info_t struct fields
* @info: struct address
* @all: true if freeing all fields
*/
void frees_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buff)
			free(info->arg);
		if (info->envs)
			freelist(&(info->envs));
		if (info->history)
			freelist(&(info->history));
		if (info->alias)
			freelist(&(info->alias));
		ffree(info->environs);
		info->environs = NULL;
		bfrees((void **)info->cmd_buff);
		if (info->readfd > 2)
		close(info->readfd);
		_putchar(BUFF_FLUSH);
	}
}
