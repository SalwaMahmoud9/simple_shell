#include "shell.h"


/**
 * node_index - node_index
 * @h: var
 * @n: var
 * Return: ssize_t
 */
ssize_t node_index(list_String *h, list_String *n)
{
	size_t ii = 0;

	while (h)
	{
		if (h == n)
			return (ii);
		h = h->nx;
		ii++;
	}
	return (-1);
}

/**
 * list_strs - list_strs
 * @h: var
 * Return: char
 */
char **list_strs(list_String *h)
{
	list_String *n = h;
	size_t ii = getListLength(h), jj;
	char **strs;
	char *str;

	if (!h || !ii)
		return (NULL);
	strs = malloc(sizeof(char *) * (ii + 1));
	if (!strs)
		return (NULL);
	for (ii = 0; n; n = n->nx, ii++)
	{
		str = malloc(_lengthstring(n->st) + 1);
		if (!str)
		{
			for (jj = 0; jj < ii; jj++)
				free(strs[jj]);
			free(strs);
			return (NULL);
		}

		str = _stringcopy(str, n->st);
		strs[ii] = str;
	}
	strs[ii] = NULL;
	return (strs);
}

/**
 * getListLength - getListLength
 * @h: var
 * Return: size_t
 */
size_t getListLength(const list_String *h)
{
	size_t ii = 0;

	while (h)
	{
		h = h->nx;
		ii++;
	}
	return (ii);
}

/**
 * start_node - start_node
 * @n: var
 * @pre: var
 * @c: var
 * Return: list_String
 */
list_String *start_node(list_String *n, char *pre, char c)
{
	char *p = NULL;

	while (n)
	{
		p = st_wth(n->st, pre);
		if (p && ((c == -1) || (*p == c)))
			return (n);
		n = n->nx;
	}
	return (NULL);
}

/**
 * p_list - p_list
 * @h: var
 * Return: size_t
 */
size_t p_list(const list_String *h)
{
	size_t ii = 0;

	while (h)
	{
		_puts(change_num(h->no, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->st ? h->st : "(nil)");
		_puts("\n");
		h = h->nx;
		ii++;
	}
	return (ii);
}
