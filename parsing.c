#include "shell.h"
/**
* is_cmd - checks if a file is an executable command
* @_info: information structure
* @_path: file path
* Return: 1 if true, otherwise 0
*/

int is_cmd(info_t *_info, char *_path)
{
	struct stat _status;

	(void)_info;
	if (!_path || stat(_path, &_status))
		return (0);

	if (_status.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
* dup_chars - duplicate characters
* @str_path: path
* @begin: first index
* @end: stop index
* Return: pointer to a new string
*/

char *dup_chars(char *str_path, int begin, int end)
{
	int ind = 0, nav = 0;
	static char _buffer[1024];

	ind = begin;

	while (ind < end)
	{
		if (str_path[ind] != ':')
			_buffer[nav++] = str_path[ind];
		ind++;
	}
	_buffer[nav] = 0;
	return (_buffer);
}

/**
*find_path - finds cmd in PATH
* @_info: information structure
* @str_path: string path
* @_cmd: cmd to be found
* Return: full path of cmd, otherwise null
*/

char *find_path(info_t *_info, char *str_path, char *_cmd)
{
	int ind = 0, _position = 0;
	char *_path;

	if (!str_path)
		return (NULL);

	if ((_strlen(_cmd) > 2) && starts_with(_cmd, "./"))
	{
		if (is_cmd(_info, _cmd))
			return (_cmd);
	}
	while (1)
	{
		if (!str_path[ind] || str_path[ind] == ':')
		{
			_path = dup_chars(str_path, _position, ind);
			if (!*_path)
				_strcat(_path, _cmd);
			else
			{
				_strcat(_path, "/");
				_strcat(_path, _cmd);
			}
			if (is_cmd(_info, _path))
				return (_path);
			if (!str_path[ind])
				break;
			_position = ind;
		}
		ind++;
	}
	return (NULL);
}
