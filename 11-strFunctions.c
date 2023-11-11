#include "shell.h"

/**
 * _putchar -_putchar
 * @c: var
 * Return: int
 */
int _putchar(char c)
{
	static char buf[W_BUFFER_S];
	static int ii;

	if (c == BUFFER_FLUSH || ii >= W_BUFFER_S)
	{
		write(1, buf, ii);
		ii = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[ii++] = c;
	return (1);
}

/**
 * _stringduplicate - _stringduplicate
 * @s: var
 * Return: char
 */
char *_stringduplicate(const char *s)
{
	char *res;
	int ln = 0;

	if (s == NULL)
		return (NULL);
	while (*s++)
		ln++;
	res = malloc(sizeof(char) * (ln + 1));
	if (!res)
		return (NULL);
	for (ln++; ln--;)
		res[ln] = *--s;
	return (res);
}

/**
 * _stringcopy - _stringcopy
 * @x: var
 * @y: var
 * Return: char
 */
char *_stringcopy(char *x, char *y)
{
	int ii = 0;

	if (x == y || y == 0)
		return (x);
	while (y[ii])
	{
		x[ii] = y[ii];
		ii++;
	}
	x[ii] = 0;
	return (x);
}

/**
 *_puts - _puts
 *@s: var
 * Return: void
 */
void _puts(char *s)
{
	int ii = 0;

	if (!s)
		return;
	while (s[ii] != '\0')
	{
		_putchar(s[ii]);
		ii++;
	}
}
