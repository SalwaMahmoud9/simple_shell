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
	int i, j;
	char *xs = x;

	i = 0;
	j = 0;
	while (x[i] != '\0')
		i++;
	while (y[j] != '\0' && j < ln)
	{
		x[i] = y[j];
		i++;
		j++;
	}
	if (j < ln)
		x[i] = '\0';
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

	i = 0;
	while (y[i] != '\0' && i < ln - 1)
	{
		x[i] = y[i];
		i++;
	}
	if (i < ln)
	{
		j = i;
		while (j < ln)
		{
			x[j] = '\0';
			j++;
		}
	}
	return (xs);
}
