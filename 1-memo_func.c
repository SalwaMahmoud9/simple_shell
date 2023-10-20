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
 * _memory_loc - reallocate memory
 * @pr: pointer previous malloc
 * @osize: byte previous
 * @nsize: byte new
 * Return: pointer
 */
void *_memory_loc(void *pr, unsigned int osize, unsigned int nsize)
{
	char *x;

	if (!pr)
	{
		return (malloc(nsize));
	}
	if (!nsize)
	{
		return (free(pr), NULL);
	}
	if (osize == nsize)
	{
		return (pr);
	}
	x = malloc(nsize);
	if (!x)
	{
		return (NULL);
	}
	osize = osize < nsize ? osize : nsize;
	while (osize--)
	{
		x[osize] = ((char *)pr)[osize];
	}
	free(pr);
	return (x);
}

/**
 **_memory_set - fill memory
 *@pr: pointer
 *@x: byte fill *pr
 *@y: n bytes
 *Return: pointer
 */
char *_memory_set(char *pr, char x, unsigned int y)
{
	unsigned int j;

	for (j = 0; j < y; j++)
	{
		pr[j] = x;
	}
	return (pr);
}
