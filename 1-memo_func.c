#include "shell.h"

/**
 * memory_free_pointer - free pointer
 * @pr: pointer address
 * Return: 1/0.
 */
int memory_free_pointer(void **pr)
{
	if (pr && *pr)
	{
		free(*pr);
		*pr = NULL;
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * memory_free - free string
 * @ss: strings
 */
void memory_free(char **ss)
{
	char **x = ss;

	if (!ss)
	{
		return;
	}

	while (*ss)
	{
		free(*ss++);
	}
	free(x);
}

/**
 * memory_loc - reallocate memory
 * @pr: pointer previous malloc
 * @osize: byte previous
 * @nsize: byte new
 * Return: pointer
 */
void *memory_loc(void *pr, unsigned int osize, unsigned int nsize)
{
	char *x;

	if (osize == nsize)
	{
		return (pr);
	}
	if (!nsize)
	{
		return (free(pr), NULL);
	}
	if (!pr)
	{
		return (malloc(nsize));
	}
	x = malloc(nsize);
	if (!x)
	{
		return (NULL);
	}
	if (osize >= nsize)
	{
		osize = nsize;
	}
	while (osize--)
	{
		x[osize] = ((char *)pr)[osize];
	}
	free(pr);
	return (x);
}

/**
 **memory_set - fill memory
 *@pr: pointer
 *@x: byte fill *pr
 *@y: n bytes
 *Return: pointer
 */
char *memory_set(char *pr, char x, unsigned int y)
{
	unsigned int j;

	for (j = 0; j < y; j++)
	{
		pr[j] = x;
	}
	return (pr);
}
