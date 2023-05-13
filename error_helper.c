#include "shell.h"

/**
*_eputs - function for printing a string
* @str: string
*/

void _eputs(char *str)
{
	int index;

	if (!str)
		return;

	for (index = 0; str[index] != '\0'; index++)
		_eputchar(str[index]);
}

/**
* _eputchar - writes a character to stderr
* @ch: character
* Return: 1 (success), -1 on error
*/

int _eputchar(char ch)
{
	static char buffer[WRITE_BUFF_SIZE];
	static int index;

	if (ch == BUFF_FLUSH || index >= WRITE_BUFF_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}
	if (ch != BUFF_FLUSH)
		buffer[index++] = ch;
	return (1);
}

/**
* putfd - write a character to fd
* @ch: character
* @fd: file descriptor
* Return: 1 (success), -1 (error)
*/

int putfd(char ch, int fd)
{
	static char buffer[WRITE_BUFF_SIZE];
	static int index;

	if (ch == BUFF_FLUSH || index >= WRITE_BUFF_SIZE)
	{
		write(fd, buffer, index);
		index = 0;
	}

	if (ch != BUFF_FLUSH)
		buffer[index++] = ch;
	return (1);
}

/**
* putsfd - function for printing a string
* @str: string
* @fd: filedescriptor
* Return: number of characters to be printed
*/

int putsfd(char *str, int fd)
{
	int index = 0;

	if (!str)
		return (0);

	while (*str)
		index += putfd(*str++, fd);
	return (index);
}
