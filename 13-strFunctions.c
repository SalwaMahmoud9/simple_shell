#include "shell.h"

/**
 * **stringToWordCh - stringToWordCh
 * @sr: var
 * @ch: var
 * Return: char
 */
char **stringToWordCh(char *sr, char ch)
{
	int ii, jj;
	int x, y, noW = 0;
	char **z;

	if (sr == NULL || sr[0] == 0)
		return (NULL);
	for (ii = 0; sr[ii] != '\0'; ii++)
		if ((sr[ii] != ch && sr[ii + 1] == ch) ||
		    (sr[ii] != ch && !sr[ii + 1]) || sr[ii + 1] == ch)
			noW++;
	if (noW == 0)
		return (NULL);
	z = malloc((1 + noW) * sizeof(char *));
	if (!z)
		return (NULL);
	for (ii = 0, jj = 0; jj < noW; jj++)
	{
		while (sr[ii] == ch && sr[ii] != ch)
			ii++;
		x = 0;
		while (sr[ii + x] != ch && sr[ii + x] && sr[ii + x] != ch)
			x++;
		z[jj] = malloc((x + 1) * sizeof(char));
		if (!z[jj])
		{
			for (x = 0; x < jj; x++)
				free(z[x]);
			free(z);
			return (NULL);
		}
		for (y = 0; y < x; y++)
			z[jj][y] = sr[ii++];
		z[jj][y] = 0;
	}
	z[jj] = NULL;
	return (z);
}

/**
 * **stringToWord - stringToWord
 * @sr: var
 * @ch: var
 * Return: char
 */

char **stringToWord(char *sr, char *ch)
{
	int ii, jj;
	int x, y, noW = 0;
	char **z;

	if (sr == NULL || sr[0] == 0)
		return (NULL);
	if (!ch)
		ch = " ";
	for (ii = 0; sr[ii] != '\0'; ii++)
		if (!check_del(sr[ii], ch) && (check_del(sr[ii + 1], ch) || !sr[ii + 1]))
			noW++;

	if (noW == 0)
		return (NULL);
	z = malloc((1 + noW) * sizeof(char *));
	if (!z)
		return (NULL);
	for (ii = 0, jj = 0; jj < noW; jj++)
	{
		while (check_del(sr[ii], ch))
			ii++;
		x = 0;
		while (!check_del(sr[ii + x], ch) && sr[ii + x])
			x++;
		z[jj] = malloc((x + 1) * sizeof(char));
		if (!z[jj])
		{
			for (x = 0; x < jj; x++)
				free(z[x]);
			free(z);
			return (NULL);
		}
		for (y = 0; y < x; y++)
			z[jj][y] = sr[ii++];
		z[jj][y] = 0;
	}
	z[jj] = NULL;
	return (z);
}
