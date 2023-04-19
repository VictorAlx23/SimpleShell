#include "shell.h"

/**
*_eputs - function for printing a string
* @s: string
*/

void _eputs(char *s)
{
	int ind;

	if (!s)
		return;

	for (ind = 0; s[ind] != '\0'; ind++)
		_eputchar(s[ind]);
}
