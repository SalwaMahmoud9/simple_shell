#include "shell.h"

/**
 * _putF - _putF
 * @ch: var
 * @f: var
 * Return: int
 */
int _putF(char ch, int f)
{
	static int ii;
	static char b[W_BUFFER_S];

	if (ch == BUFFER_FLUSH || ii >= W_BUFFER_S)
	{
		write(f, b, ii);
		ii = 0;
	}
	if (ch != BUFFER_FLUSH)
		b[ii++] = ch;
	return (1);
}

/**
 *_putFD - _putFD
 * @sr: var
 * @f: var
 * Return: int
 */
int _putFD(char *sr, int f)
{
	int ii = 0;

	if (!sr)
		return (0);
	while (*sr)
	{
		ii += _putF(*sr++, f);
	}
	return (ii);
}

/**
 * _putC - _putC
 * @ch: var
 * Return: int
 */
int _putC(char ch)
{
	static char b[W_BUFFER_S];
	static int ii;

	if (ch == BUFFER_FLUSH || ii >= W_BUFFER_S)
	{
		write(2, b, ii);
		ii = 0;
	}
	if (ch != BUFFER_FLUSH)
		b[ii++] = ch;
	return (1);
}


/**
 *_put - _put
 * @sr: var
 * Return: void
 */
void _put(char *sr)
{
	int ii = 0;

	if (!sr)
		return;
	while (sr[ii] != '\0')
	{
		_putC(sr[ii]);
		ii++;
	}
}
