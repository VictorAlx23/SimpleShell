#include "shell.h"

/**
* strtow - breaks a string sentence into words
* @str: string
* @delim: delimiter
* Return: pointer to array of strings, otherwise NULL
*/

char **strtow(char *str, char *delim)
{
	char **str;
	int index, j, iter, nav, num = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	while (str[index] != '\0')
	{
		if (!is_delim(str[index], delim && (is_delim(str[index + 1],
							delim) || !str[index + 1]))
			num++, index++;
	}
	if (num == 0)
		return (NULL);
	str = malloc(sizeof(char *) * (num + 1));
	if (!str)
		return (NULL);
	for (index = 0, j = 0; j < num; j++)
	{
		while (is_delim(str[index], delim))
			index++;
		iter = 0;
		while (!is_delim(str[index + iter], delim) && str[index + iter])
			iter++;
		str[j] = malloc(sizeof(char) * (iter + 1));
		if (!str[j])
		{
			iter = 0;
			while (iter < j)
				free(str[iter]), iter++;
			free(str);
			return (NULL);
		}

		for (nav = 0; nav < iter; nav++)
			str[j][nav] = str[index++];
		str[j][nav] = 0;
	}
	str[j] = NULL;
	return (str);
}

/**
* strtow2 - break string into words
* @str: string
* @delim: delimiter
* Return: pointer to array of strings, otherwise NULL
*/

char **strtow2(char *str, char delim)
{
	char **str;
	int index = 0, j = 0, iter, nav, num = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	while (str[index] != '\0')
	{
		if ((str[index] != delim && str[index + 1] == delim) ||
				(str[index] != delim && !str[index + 1]) || str[index + 1] == delim)
			num++, index++;
	}
	if (num == 0)
		return (NULL);
	str = malloc(sizeof(char *) * (num + 1));
	if (!str)
		return (NULL);
	for (index = 0, j = 0; j < num; j++)
	{
		while (str[index] == delim && str[index] != delim)
			index++;
		iter = 0;
		while (str[index + iter] != delim && str[index + iter]
				&& str[index + iter] != delim)
			iter++;
		str[j] = malloc(sizeof(char) * (iter + 1));
		if (!str[j])
		{
			for (iter = 0; iter < j; iter++)
				free(str[iter]);
			free(str);
			return (NULL);
		}
		for (nav = 0; nav < iter; nav++)
			str[j][nav] = str[index++];
		str[j][nav] = 0;
	}
	str[j] = NULL;
	return (str);
}
