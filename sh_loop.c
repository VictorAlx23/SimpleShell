#include "shell.h"

/**
* hsh - shell loop function
* @_info: information structure
* @av: argument vector
* Return: 0 (success), otherwise 1 on error
*/

int hsh(info_t *_info, char **av)
{
	int r_built_in = 0;
	ssize_t i = 0;

	while (i != -1 && r_built_in != -2)
	{
		clears_info(_info);

		if (interact(_info))
			_puts("$");
		_eputchar(BUFF_FLUSH);
		i = gets_input(_info);

		if (i != -1)
		{
			sets_info(_info, av);
			r_built_in = find_built_in(_info);
			if (r_built_in == -1)
				find_cmd(_info);
		}
		else if (interact(_info))
			_putchar('\n');
		free_info(_info, 0);
	}
	write_history(_info);
	free_info(_info, 1);
	if (!interact(_info) && _info->status)
		exit(_info->status);
	if (r_built_in == -2)
	{
		if (_info->err_nums == -1)
			exit(_info->status);
		exit(_info->err_nums);
	}
	return (r_built_in);
}

/**
* find_built_in - find builtin command
* @_info: information structure
* Return: 0 (success), -1 if builtin not found, 1 if found but not success
* 2 if the builtin signal exit
*/

int find_built_in(info_t *_info)
{
	int nav, r_built_in = -1;

	built_in_table table[] = {
		{"exit", _shellexit},
		{"env", _shellenv},
		{"help", _shellhelp},
		{"history", _shellhistory},
		{"setenv", _shsetenv},
		{"unsetenv", _shunsetenv},
		{"cd", _shellcd},
		{"alias", _shellalias},
		{NULL, NULL}
	};

	for (nav = 0; table[nav].type; nav++)
	{
		if (_strcmp(_info->argv[0], table[nav].type) == 0)
		{
			_info->line_count++;
			r_built_in = table[nav].func(_info);
			break;
		}
	}
	return (r_built_in);
}

/**
* find_cmd - find a command in a PATH
* @_info: information structure
*/

void find_cmd(info_t *_info)
{
	int ind = 0, nav = 0;
	char *path = NULL;

	_info->path = _info->argv[0];
	if (_info->linecount_flag == 1)
	{
		_info->line_count++;
		_info->linecount_flag = 0;
	}
	while (_info->arg[ind])
	{
		if (!is_delim(_info->arg[ind], "\t\n"))
		{
			nav++;
			ind++;
		}
		if (!nav)
			return;
	}
	path = find_path(_info, _getenvs(_info, "PATH="), _info->argv[0]);

	if (path)
	{
		_info->path = path;
		fork_cmd(_info);
	}
	else
	{
		if ((interact(_info) || _getenvs(_info, "PATH=")
					|| _info->argv[0][0] == '/')
				&& is_cmd(_info, _info->argv[0]))
			fork_cmd(_info);
		else if (*(_info->arg) != '\n')
		{
			_info->status = 127;
			prints_error(_info, "not found\n");
		}
	}
}

/**
* fork_cmd - fork an executive thread to run cmd
* @_info: information struct
*/

void fork_cmd(info_t *_info)
{
	pid_t _childpid;

	_childpid = fork();

	if (_childpid == -1)
	{
		perror("Error:");
		return;
	}
	if (_childpid == 0)
	{
		if (execve(_info->path, _info->argv, get_environs(_info))
				== -1)
		{
			free_info(_info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(_info->status));
		if (WIFEXITED(_info->status))
		{
			_info->status = WEXITSTATUS(_info->status);
			if (_info->status == 126)
				prints_error(_info, "Permission denied\n");
		}
	}
}
