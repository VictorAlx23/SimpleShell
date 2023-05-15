#include "shell.h"

/**
* strtow - breaks a string sentence into words
* @str: string
* @delim: delimiter
* Return: pointer to array of strings, otherwise NULL
*/

char **strtow(char *str, char *delim)
{
	char **words;
	int index = 0, j, iter, nav, num = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (index = 0; str[index] != '\0'; index++)
	{
		if (!is_delim(str[index], delim) && (is_delim(str[index + 1],
						delim) || !str[index + 1]))
			num++;
	}
	if (num == 0)
		return (NULL);
	words = malloc(sizeof(char *) * (num + 1));
	if (!words)
		return (NULL);
	for (index = 0, j = 0; j < num; j++)
	{
		while (is_delim(str[index], delim))
			index++;
		iter = 0;
		while (!is_delim(str[index + iter], delim) && str[index + iter])
			iter++;
		words[j] = malloc(sizeof(char) * (iter + 1));
		if (!words[j])
		{
			iter = 0;
			while (iter < j)
				free(words[iter]), iter++;
			free(words);
			return (NULL);
		}
		for (nav = 0; nav < iter; nav++)
			words[j][nav] = str[index++];
		words[j][nav] = 0;
	} words[j] = NULL;
	return (words);
}

/**
* _strtow2 - break string into words
* @str: string
* @delim: delimiter
* Return: pointer to array of strings, otherwise NULL
*/

char **_strtow2(char *str, char delim)
{
	char **words;
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
	words = malloc(sizeof(char *) * (num + 1));
	if (!words)
		return (NULL);
	for (index = 0, j = 0; j < num; j++)
	{
		while (str[index] == delim && str[index] != delim)
			index++;
		iter = 0;
		while (str[index + iter] != delim && str[index + iter]
				&& str[index + iter] != delim)
			iter++;
		words[j] = malloc(sizeof(char) * (iter + 1));
		if (!words[j])
		{
			for (iter = 0; iter < j; iter++)
				free(words[iter]);
			free(words);
			return (NULL);
		}
		for (nav = 0; nav < iter; nav++)
			words[j][nav] = str[index++];
		words[j][nav] = 0;
	}
	words[j] = NULL;
	return (words);
}
