#include "shell.h"
/**
 * _errastoi - converts a string to an integer
 *  @str: the string to be converted
 *  Return: 0 if no numbers in string, converted number otherwise
 *  -1 on error
 */
int _errastoi(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	while (str[index] != '\0')
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;
			result += (str[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
		index++;
	}
	return (result);
}
/**
 * prints_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
void prints_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_deci(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}
/**
 * print_deci - function printsa decimal (integer) number in (base 10)
 * @input_num: the input
 * @fd: the file decriptor to write to
 * Return: the number of characters printed
 */
int print_deci(int input_num, int fd)
{
	int (*__putchar)(char) = _putchar;
	int index, counts = 0;
	unsigned int _abs_, currents;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input_num < 0)
	{
		_abs_ = -input_num;
		__putchar('-');
		counts++;
	}
	else
		_abs_ = input_num;
	currents = _abs_;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (_abs_ / index)
		{
			__putchar('0' + currents / index);
			counts++;
		}
		currents %= index;
	}
	__putchar('0' + currents);
	counts++;

	return (counts);
}
/**
 * converts_num - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return:  string
 */
char *converts_num(long int num, int base, int flags)
{
	static char *arrays;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	arrays =  flags & CONVERT_LOWERCASE ? "0123456789abcdef" :
		"0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = arrays[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}
/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 * Return: Always 0;
 */
void remove_comments(char *buff)
{
	int index = 0;

	while (buff[index] != '\0')
	{
		if (buff[index] == '#' && (!index || buff[index - 1] == ' '))
		{
			buff[index] = '\0';
			break;
		}
		index++;
	}
}
