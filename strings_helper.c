#include "shell.h"

/**
* _strlen - string length
* @str: string
* Return: length of string
*/

int _strlen(char *str)
{
	int len = 0;

	if (!str)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

/**
* _strcmp - compare two strings
* @str1: first string
* @str2: second string
* Return: if (str1 < str2) negative, zero if str1 == str2
* > 0 if str1 > str2
*/

int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
* _strcat - string concatenate
* @dest: destination string
* @src: source string
* Return: pointer to the destination string
*/

char *_strcat(char *dest, char *src)
{
	char *str = dest;

	while (*dest)
		dest++;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = *src;
	return (str);
}

/**
* starts_with - check if the needle string starts with the haystack string
* @haystack: haystack string (search from)
* @needle: string to find
* Return: memory address of the next character of haystack, otherwise
* NULL
*/

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
			return (NULL);
	}
	return ((char *)haystack);
}
