#include "shell.h"

/**
* interact - returns true if shell is interactive mode
* @info: struct address
*
* Return: 1 if interactive mode, 0 otherwise
*/

int interact(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
* is_delimt - checks if character is a delimeter
* @ch: the char to check
* @delimt: the delimeter string
* Return: 1 if true, 0 if false
*/

int is_delimt(char ch, char *delimt)
{
	while (*delimt)
		if (*delimt++ == ch)
			return (1);
	return (0);
}

/**
* _isalphac - checks for alphabetic character
* @ch: The character to input
* Return: 1 if ch is alphabetic, 0 otherwise
*/

int _isalphac(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
* _astoi - converts a string to an integer
* @str: the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
*/

int _astoi(char *str)
{
	int index, sign = 1, flag_s = 0, output;
	unsigned int results = 0;

	for (index = 0; str[index] != '\0' && flag_s != 2; index++)
	{
		if (str[index] == '-')
			sign *= -1;
		if (str[index] >= '0' && str[index] <= '9')
		{
			flag_s = 1;
			results *= 10;
			results += (str[index] - '0');
		}
		else if (flag_s == 1)
		{
			flag_s = 2;
		}
	}
	if (sign == -1)
		output = -results;
	else
		output = results;
	return (output);
}
