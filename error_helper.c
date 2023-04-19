#include "shell.h"

/**
*eputs - function for printing a string
* @s: string
*/

void eputs(char *s)
{
	int ind;

	if (!s)
		return;

	for (ind = 0; s[ind] != '\0'; ind++)
		eputchar(s[ind]);
}

/**
* eputchar - writes a character to stderr
* @ch: character
* Return: 1 (success), -1 on error
*/

int eputchar(char ch)
{
	static char buffer[WRITE_BUFF_SIZE];
	static int ind;

	if (ch == BUFF_FLUSH || ind >= WRITE_BUFF_SIZE)
	{
		write(2, buffer, ind);
		ind = 0;
	}
	if (ch != BUFF_FLUSH)
		buffer[ind++] = ch;
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
	static buffer[WRITE_BUFF_SIZE];
	static int ind;

	if (ch == BUFF_FLUSH || ind >= WRITE_BUFF_SIZE)
	{
		write(fd, buffer, ind);
		ind = 0;
	}

	if (ch != BUFF_FLUSH)
		buffer[ind++] = ch;
	return (1);
}

/**
* putsfd - function for printing a string
* @s: string
* @fd: filedescriptor
* Return: number of characters to be printed
*/

int putsfd(char *s, int fd)
{
	int ind;

	if (!s)
		return (0);

	while (*s)
		ind += putfd(*s++, fd);
	return (ind);
}
