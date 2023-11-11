#include "shell.h"

/**
 * _relocation - _relocation
 * @pn: var
 * @os: var
 * @ns: var
 * Return: void
 */
void *_relocation(void *pn, unsigned int os, unsigned int ns)
{
	char *ptr;

	if (!pn)
		return (malloc(ns));
	if (!ns)
		return (free(pn), NULL);
	if (ns == os)
		return (pn);

	ptr = malloc(ns);
	if (!ptr)
		return (NULL);

	os = os < ns ? os : ns;
	while (os--)
		ptr[os] = ((char *)pn)[os];
	free(pn);
	return (ptr);
}

/**
 * freePointer - freePointer
 * @pp: var
 * Return: void
 */
void freePointer(char **pp)
{
	char **x = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(x);
}

/**
 **_setmemory - _setmemory
 *@x: var
 *@y: var
 *@num: var
 *Return: char
 */
char *_setmemory(char *x, char y, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		x[i] = y;
	return (x);
}

/**
 * bfree - bfree
 * @p: var
 * Return: int
 */
int bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
