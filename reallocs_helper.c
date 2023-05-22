#include "shell.h"

/**
* _memset - sets memory bytes
* @str: string
* @byte: byte to fill with
* @n: number of bytes to filled
* Return: string pointer
*/

char *_memset(char *str, char byte, unsigned int n)
{
	unsigned int ind = 0;

	while (ind < n)
	{
		str[ind] = byte;
		ind++;
	}
	return (str);
}

/**
* ffree - function frees string of strings
* @ss: string of strings
*/

void ffree(char **ss)
{
	char **tmp = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(tmp);
}

/**
* _reallocs - reallocating blocks of memory
* @prev: previous memory pointer
* @prev_size: previous memory size
* @next_size: next memory size
* Return: pointe to new memory
*/

void *_reallocs(void *prev, unsigned int prev_size, unsigned int next_size)
{
	char *ptr;

	if (!prev)
		return (malloc(next_size));
	if (!next_size)
		return (free(prev), NULL);
	if (next_size == prev_size)
		return (prev);
	ptr = malloc(next_size);

	if (!ptr)
		return (NULL);
	prev_size = prev_size < next_size ? prev_size : next_size;

	while (prev_size--)
	{
		ptr[prev_size] = ((char *)prev)[prev_size];
	}
	free(prev);
	return (ptr);
}
