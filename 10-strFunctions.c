#include "shell.h"


/**
 * _stringcat - _stringcat
 * @x: var
 * @y: var
 * Return: char
 */
char *_stringcat(char *x, char *y)
{
	char *r = x;

	while (*x)
		x++;
	while (*y)
		*x++ = *y++;
	*x = *y;
	return (r);
}


/**
 * _comparestring - _comparestring
 * @x: var
 * @y: var
 * Return: int
 */
int _comparestring(char *x, char *y)
{
	while (*x && *y)
	{
		if (*x != *y)
			return (*x - *y);
		x++;
		y++;
	}
	if (*x == *y)
		return (0);
	else
		return (*x < *y ? -1 : 1);
}

/**
 * _lengthstring -_lengthstring
 * @ss: var
 * Return: int
 */
int _lengthstring(char *ss)
{
	int ii = 0;

	if (!ss)
		return (0);

	while (*ss++)
		ii++;
	return (ii);
}

/**
 * st_wth - st_wth
 * @x: var
 * @y: var
 * Return: char
 */
char *st_wth(const char *x, const char *needle)
{
	while (*y)
		if (*y++ != *x++)
			return (NULL);
	return ((char *)x);
}
