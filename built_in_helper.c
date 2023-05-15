#include "shell.h"

/**
* _shellexit - exits the shell
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: exits with a given exit status
* (0) if info.argv[0] != "exit"
*/

int _shellexit(info_t *info)
{
	int exitchecks;

	if (info->argv[1])
	{
		exitchecks = _errastoi(info->argv[1]);
		if (exitchecks == -1)
		{
			info->status = 2;
			prints_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_nums = _errastoi(info->argv[1]);
		return (-2);
	}
	info->err_nums = -1;
	return (-2);
}

/**
* _shellcd - changes the current directory of the process
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/

int _shellcd(info_t *info)
{
	char *str, *dir, buffer[1024];
	int chdir_rets;

	str = getcwd(buffer, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenvs(info, "HOME=");
		if (!dir)
		chdir_rets = /* TODO: what should this be? */
		chdir((dir = _getenvs(info, "PWD=")) ? dir : "/");
		else
		chdir_rets = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenvs(info, "OLDPWD="))
		{
			_puts(str), _putchar('\n'), return (1);
		}
		_puts(_getenvs(info, "OLDPWD=")), _putchar('\n');
		chdir_rets =  /* TODO: what should this be? */
		chdir((dir = _getenvs(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_rets = chdir(info->argv[1]);
	if (chdir_rets == -1)
	{
		prints_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenvs(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
* _shellhelp - changes the current directory of the process
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/

int _shellhelp(info_t *info)
{
	char **_arg_arrays;

	_arg_arrays = info->argv;

	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*_arg_arrays);
	return (0);
}
