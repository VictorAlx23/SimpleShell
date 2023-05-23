#include "shell.h"

/**
* _strcpy - function that copies a string
* @dest: destination string
* @src: source string
* Return: pointer to the destination string
*/

char *_strcpy(char *dest, char *src)
{
	int ind;

	if (dest == src || src == 0)
		return (dest);

	for (ind = 0; src[ind]; ind++)
	{
		dest[ind] = src[ind];
	}
	dest[ind] = 0;

	return (dest);
}

/**
* _putchar - prints a character
* @ch: character to be printed
* Return: 1 (success), otherwise -1
*/

int _putchar(char ch)
{
	static int ind;
	static char buffer[WRITE_BUFF_SIZE];

	if (ch == BUFF_FLUSH || ind >= WRITE_BUFF_SIZE)
	{
		write(1, buffer, ind);
		ind = 0;
	}
	if (ch != BUFF_FLUSH)
	{
		buffer[ind] = ch;
		ind++;
	}
	return (1);
}

/**
* _puts - prints an input string
* @str: string
*/

void _puts(char *str)
{
	int ind;

	if (!str)
		return;

	for (ind = 0; str[ind] != '\0'; ind++)
	{
		_putchar(str[ind]);
	}
}

/**
* _strdup - string duplicate
* @s: string
* Return: pointer to the memory address of the duplicated string
*/

char *_strdup(const char *s)
{
	char *dup;
	int len = 0;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	dup = malloc(sizeof(char) * (len + 1));

	if (!dup)
		return (NULL);
	for (len++; len--;)
	{
		dup[len] = *--s;
	}
	return (dup);
}
