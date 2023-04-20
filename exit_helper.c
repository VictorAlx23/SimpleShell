#include "shell.h"

/**
* _strncat - string concatenation
* @src: source string
* @dest: destination string
* @n: number of bytes to be allocated for memory
* Return: concatenated string
*/

char *_strncat(char *dest, char *src, int n)
{
	int ind = 0, nav = 0;
	char *str = dest;

	while (dest[ind] != '\0)
		ind++;
	while (src[nav] != '\0' && nav < n)
	{
		dest[ind] = src[nav];
		ind++;
		nav++;
	}
	if (nav < n)
		dest[ind] = '\0';
	return (str);
}

/**
* _strchr - character locator
* @str: string
* @ch: target character
* Return: memory location of the string
*/

char *_strchr(char *str, char ch)
{
	while (*str != '\0')
	{
		if (*str == ch)
			return (str);
		str++;
	}
	return (NULL);
}
