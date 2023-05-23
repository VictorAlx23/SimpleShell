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
	int ind, nav;
	char *str = dest;

	ind = 0;
	nav = 0;
	while (dest[ind] != '\0')
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
	do {
		if (*str == ch)
			return (str);
	} while (*str != '\0');
	return (NULL);
}

/**
* _strncpy - string copy
* @dest: destination string
* @src: source string
* @num: number of characters to be copied
* Return: copied string
*/

char *_strncpy(char *dest, char *src, int num)
{
	char *str = dest;
	int ind = 0, nav = 0;

	while (src[ind] != '\0' && ind < num - 1)
	{
		dest[ind] = src[ind];
		ind++;
	}
	if (ind < num)
	{
		for (nav = ind; nav < num; nav++)
		{
			dest[nav] = '\0';
		}
	}
	return (str);
}
