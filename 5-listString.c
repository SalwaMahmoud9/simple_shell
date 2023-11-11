#include "shell.h"

/**
 * free_mylist - free_mylist
 * @h_p: var
 * Return: void
 */
void free_mylist(list_String **h_p)
{
	list_String *n, *n_n, *h;

	if (!h_p || !*h_p)
		return;
	h = *h_p;
	n = h;
	while (n)
	{
		n_n = n->nx;
		free(n->st);
		free(n);
		n = n_n;
	}
	*h_p = NULL;
}

/**
 * plus_e_node - plus_e_node
 * @h: var
 * @st: var
 * @nu: var
 * Return: list_String
 */
list_String *plus_e_node(list_String **h, const char *st, int nu)
{
	list_String *n_n, *n;

	if (!h)
		return (NULL);

	n = *h;
	n_n = malloc(sizeof(list_String));
	if (!n_n)
		return (NULL);
	_setmemory((void *)n_n, 0, sizeof(list_String));
	n_n->no = nu;
	if (st)
	{
		n_n->st = _strdup(st);
		if (!n_n->st)
		{
			free(n_n);
			return (NULL);
		}
	}
	if (n)
	{
		while (n->nx)
			n = n->nx;
		n->nx = n_n;
	}
	else
		*h = n_n;
	return (n_n);
}

/**
 * plus_node - plus_node
 * @h: var
 * @st: var
 * @nu: var
 * Return: list_String
 */
list_String *plus_node(list_String **h, const char *st, int nu)
{
	list_String *n_h;

	if (!h)
		return (NULL);
	n_h = malloc(sizeof(list_String));
	if (!n_h)
		return (NULL);
	_setmemory((void *)n_h, 0, sizeof(list_String));
	n_h->no = nu;
	if (st)
	{
		n_h->st = _strdup(st);
		if (!n_h->st)
		{
			free(n_h);
			return (NULL);
		}
	}
	n_h->nx = *h;
	*h = n_h;
	return (n_h);
}

/**
 * p_list_string - p_list_string
 * @h: var
 * Return: size_t
 */
size_t p_list_string(const list_String *h)
{
	size_t ii = 0;

	while (h)
	{
		_puts(h->st ? h->st : "(nil)");
		_puts("\n");
		h = h->nx;
		ii++;
	}
	return (ii);
}

/**
 * d_node_i - d_node_i
 * @h: var
 * @ind: var
 * Return: int
 */
int d_node_i(list_String **h, unsigned int ind)
{
	list_String *n, *p_n;
	unsigned int i = 0;

	if (!h || !*h)
		return (0);

	if (!ind)
	{
		n = *h;
		*h = (*h)->nx;
		free(n->st);
		free(n);
		return (1);
	}
	n = *h;
	while (n)
	{
		if (i == ind)
		{
			p_n->nx = n->nx;
			free(n->st);
			free(n);
			return (1);
		}
		i++;
		p_n = n;
		n = n->nx;
	}
	return (0);
}
