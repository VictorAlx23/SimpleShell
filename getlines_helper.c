#include "shell.h"

/**
* input_buffer - buffers arrays of commands
* @_info: struct information
* @buffer: memory address of the buffer
* @length: variable length address
* Return: byte
*/

ssize_t input_buffer(info_t *_info, char **buffer, size_t *length)
{
	ssize_t i = 0;
	size_t j = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, s_Handler);
#if USE_GETLINE
		i = getlines(buffer, &j, stdin);
#else
		i = _getlines(_info, buffer, &j);
#endif
		if (i > 0)
		{
			if ((*buffer)[i - 1] == '\n')
			{
				(*buffer)[i - 1] = '\0';
				i--;
			}
			_info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(_info, *buffer, _info->histcount++);
			if (_strchr(*buffer, ';'))
			{
				*length = i;
				_info->cmd_buff = buffer;
			}
		}
	}
	return (i);
}

/**
* gets_input - gets an input line
* @_info: information struct
* Return: Bytes
*/

ssize_t gets_input(info_t *_info)
{
	static size_t ind, nav, _size;
	static char *buffer;
	ssize_t i = 0;
	char **buffer_ptr = &(_info->arg);
	char *ptr;

	_putchar(BUFF_FLUSH);
	i = input_buffer(_info, &buffer, &_size);
	if (i == -1)
		return (-1);
	if (_size)
	{
		nav = ind;
		ptr = buffer + ind;
		check_chains(_info, buffer, &nav, ind, _size);
		while (nav < _size)
		{
			if (is_chains(_info, buffer, &nav))
				break;
			nav++;
		}
		ind = nav + 1;
		if (ind >= _size)
		{
			ind = 0, _size = 0;
			_info->cmd_buff_type = CMD_NORM;
		}
		*buffer_ptr = ptr;
		return (_strlen(ptr));
	}
	*buffer_ptr = buffer;
	return (i);
}

/**
* read_buffer - reads a buffer
* @_info: information struct
* @buffer: buffer
* @_size: size
* Return: bytes
*/

ssize_t read_buffer(info_t *_info, char *buffer, size_t *_size)
{
	ssize_t i = 0;

	if (*_size)
		return (0);
	i = read(_info->readfd, buffer, READ_BUFF_SIZE);

	if (i >= 0)
		*_size = i;
	return (i);
}

/**
* _getlines - returns the next line in the from STDIN
* @_info: information struct
* @buff_ptr: buffer pointer
* @lengths: size of the malloced buff_ptr
* Return: line
*/

int _getlines(info_t *_info, char **buff_ptr, size_t lengths)
{
	static char buffer[READ_BUFF_SIZE];
	char *ptr = NULL, *n_ptr = NULL, *tmp;
	static size_t ind, length;
	ssize_t i = 0, b = 0;
	size_t nav;

	ptr = *buff_ptr;
	if (ptr && lengths)
		b = *lengths;
	if (ind == length)
		ind = length = 0;
	i = read_buffer(_info, buffer, &length);
	if (i == -1 || (i == 0 && length == 0))
		return (-1);
	tmp = strchr(buffer + ind, '\n');
	nav = tmp ? 1 + (unsigned int)(tmp - buffer) : length;
	n_ptr = realloc(ptr, b, b ? b + nav : nav + 1);

	if (!n_ptr)
		return (ptr ? free(ptr), -1 : -1);
	if (b)
		_strncat(n_ptr, buffer + ind, nav - ind);
	else
		_strncat(n_ptr, buffer + ind, nav - ind + 1);
	b += nav - ind;
	ind  = nav;
	ptr = n_ptr;

	if (_size)
		*_size = b;
	*buff_ptr = ptr;
	return (b);
}

/**
* s_Handler - copy blocker (ctrl-C)
* @num: signal number
*/

void s_Handler(__attribute__((unsed))int num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFF_FLUSH);
}
