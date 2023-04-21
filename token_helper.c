#include "shell.h"

/**
* strtow - breaks a string sentence into words
* @s: string
* @delim: delimiter
* Return: pointer to array of strings, otherwise NULL
*/

char **strtow(char *s, char *delim)
{
	char **str;
	int ind, j, iter, nav, num = 0;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	while (str[ind] != '\0')
	{
		if (!is_delim(s[ind], delim) && (is_delim(s[ind + 1], d) || !s[ind + 1]))
			num++, ind++;
	}
	if (num == 0)
		return (NULL);
	str = malloc(sizeof(char *) * (num + 1));
	if (!str)
		return (NULL);
	for (ind = 0, j = 0; j < num; j++)
	{
		while (is_delim(s[ind], delim))
			ind++;
		iter = 0;
		while (!is_delim(s[ind + iter], delim) && s[ind + iter])
			iter++;
		str[j] = malloc(sizeof(char) * (iter + 1));
		if (!str[j])
		{
			iter = 0;
			while (iter < j)
				free(str[iter]), k++;
			free(str);
			return (NULL);
		}

		for (nav = 0; nav < iter; nav++)
			str[j][nav] = s[ind++];
		str[j][nav] = 0;
	}
	str[j] = NULL;
	return (str);
}

/**
* strtow2 - break string into words
* @s: string
* @delim: delimiter
* Return: pointer to array of strings, otherwise NULL
*/

char **strtow2(char *s, char delim)
{
	char **str;
	int ind = 0, j = 0, iter, nav, num = 0;

	if (s == NULL || s[0] == 0)
		return (NULL);
	while (s[ind] != '\0')
	{
		if ((s[ind] != delim && s[ind + 1] == delim) ||
				(s[ind] != delim && !s[ind + 1]) || s[ind + 1] == delim)
			num++, ind++;
	}
	if (num == 0)
		return (NULL);
	str = malloc(sizeof(char *) * (num + 1));
	if (!str)
		return (NULL);
	for (ind = 0, j = 0; j < num; j++)
	{
		while (s[ind] == delim && s[ind] != delim)
			ind++;
		iter = 0;
		while (s[ind + iter] != delim && s[ind + iter] && s[ind + iter] != delim)
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
			str[j][nav] = s[ind++];
		str[j][nav] = 0;
	}
	str[j] = NULL;
	return (str);
}
