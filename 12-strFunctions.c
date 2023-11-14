#include "shell.h"
/**
 **_strchr - _strchr
 *@xs: var
 *@yc: var
 *Return: char
 */
char *_strchr(char *xs, char yc)
{
	do {
		if (*xs == yc)
			return (xs);
	} while (*xs++ != '\0');

	return (NULL);
}

/**
 **_strncat - _strncat
 *@x: var
 *@y: var
 *@ln: var
 *Return: char
 */
char *_strncat(char *x, char *y, int ln)
{
	int ii, jj;
	char *xs = x;

	ii = 0;
	jj = 0;
	while (x[ii] != '\0')
		ii++;
	while (y[jj] != '\0' && jj < ln)
	{
		x[ii] = y[jj];
		ii++;
		jj++;
	}
	if (jj < ln)
		x[ii] = '\0';
	return (xs);
}

/**
 **_stringcpy - _stringcpy
 *@x: var
 *@y: var
 *@ln: var
 *Return: char
 */
char *_stringcpy(char *x, char *y, int ln)
{
	char *xs = x;
	int ii, jj;

	ii = 0;
	while (y[ii] != '\0' && ii < ln - 1)
	{
		x[ii] = y[ii];
		ii++;
	}
	if (ii < ln)
	{
		jj = ii;
		while (jj < ln)
		{
			x[jj] = '\0';
			jj++;
		}
	}
	return (xs);
}
