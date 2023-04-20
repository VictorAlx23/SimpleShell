#include "shell.h"

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

	while (src[ind] != '\0' && ind < n - 1)
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
