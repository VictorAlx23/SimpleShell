#include "shell.h"

/**
* get_history_file - returns a file history
* @_info: struct information
* Return: history file
*/

char *get_history_file(info_t *_info)
{
	char *buffer, *_directory;

	directory = _getenv(_info, "HOME=");
	if (!_directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(_directory) +
				_strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, _directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
* write_history - append or create a file
* @_info: struct information
* Return: 1 (success), otherwise -1
*/

int write_history(info_t *_info)
{
	list_t *head = NULL;
	ssize_t fd;
	char *name_file = get_history_file(_info);

	if (!name_file)
		return (-1);
	fd = open(name_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(name_file);
	if (fd == -1)
		return (-1);
	head = _info->history;
	while (head)
	{
		_putsfd(head->strs, fd);
		_putfd('\n', fd);
		head = head->next;
	}
	_putfd(BUFF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
* read_history - read file history
* @_info: struct information
* Return: histcount, otherwise 0
*/

int read_history(info_t *_info)
{
	int end = 0, int ind = 0, int lines = 0;
	ssize_t f_size = 0, fd, len;
	char *name_file = get_history_file(_info), *buffer = NULL;
	struct stat _st;

	if (!name_file)
		return (0);
	fd = open(name_file, O_RDONLY);
	free(name_file);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &_st))
		f_size = _st.st_size;
	if (f_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (1 + f_size));
	if (!buffer)
		return (0);
	len = read(fd, buffer, f_size);
	buffer[f_size] = 0;
	if (len <= 0)
		return (free(buffer), 0);
	close(fd);
	while (ind < f_size)
	{
		if (buffer[ind] == '\n')
		{
			buffer[ind] = 0, build_history_list(_info, buffer + end, lines++);
			end = ind + 1;
		} ind++;
	}
	if (end != ind)
		build_history_list(_info, buffer + end, lines++);
	free(buffer);
	_info->histcount = lines;
	while (_info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(_info->history), 0);
	renumber_history(_info);
	return (_info->histcount);
}

/**
* build_history_list - adding a node to the history list
* @_info: struct information
* @buffer: buffer
* @lines: line count
* Return: 0
*/

int build_history_list(info_t *_info, char *buffer, int lines)
{
	list_t *head = NULL;

	if (_info->history)
		head = _info->history;
	add_node_end(&head, buffer, lines);
	if (!_info->history)
		_info->history = head;
	return (0);
}

/**
* renumber_history - renumbering history list post changes
* @_info: struct info
* Return: histcount
*/

int renumber_history(info_t *_info)
{
	int count = 0;
	list_t *head = NULL;

	for (head = _info->history; head; head = head->next)
	{
		head->nums = count++;
	}
	return (_info->histcount = count);
}
