#include "shell.h"


/**
 * length_list - length list
 * @h: pointer
 * Return: sizes
 */
size_t length_list(const list_struct *h)
{
	size_t ii = 0;

	while (h)
	{
		h = h->struct_next;
		ii++;
	}
	return (ii);
}

/**
 * convert_lis_to_str - convert list to string
 * @h_pt: pointer
 * Return: string
 */
char **convert_lis_to_str(list_struct *h_pt)
{
	char **strings;
	char *string;
	list_struct *n = h_pt;
	size_t i = length_list(h_pt);
	size_t j;

	if (!h_pt || !i)
		return (NULL);
	strings = malloc(sizeof(char *) * (i + 1));
	if (!strings)
		return (NULL);
	for (i = 0; n; n = n->struct_next, i++)
	{
		string = malloc(string_length(n->struct_str) + 1);
		if (!string)
		{
			for (j = 0; j <= i - 1; j++)
			{
				free(strings[j]);
			}
			free(strings);
			return (NULL);
		}

		string = string_copy(string, n->struct_str);
		strings[i] = string;
	}
	strings[i] = NULL;
	return (strings);
}


/**
 * linklist_print - link list print
 * @h: pointer
 * Return: size
 */
size_t linklist_print(const list_struct *h)
{
	size_t i = 0;

	while (h)
	{
		string_print(convert_no(h->struct_no, 10, 0));
		string_print2(':');
		string_print2(' ');
		string_print(h->struct_str ? h->struct_str : "(nil)");
		string_print("\n");
		h = h->struct_next;
		i++;
	}
	return (i);
}

/**
 * startwith_node - start with node
 * @n: pointer
 * @pref: string
 * @c: char
 * Return: n
 */
list_struct *startwith_node(list_struct *n, char *pref, char c)
{
	char *prr = NULL;

	while (n)
	{
		prr = begin_with(n->struct_str, pref);
		if (prr && ((c == -1) || (*prr == c)))
			return (n);
		n = n->struct_next;
	}
	return (NULL);
}

/**
 * node_put - node add
 * @h_pt: pointer
 * @string: string
 * @num: number
 * Return: n_he
 */
list_struct *node_put(list_struct **h_pt, const char *string, int num)
{
	list_struct *n_he;

	if (!h_pt)
	{
		return (NULL);
	}
	n_he = malloc(sizeof(list_struct));
	if (!n_he)
	{
		return (NULL);
	}
	memory_set((void *)n_he, 0, sizeof(list_struct));
	n_he->struct_no = num;
	if (string)
	{
		n_he->struct_str = string_duplicate(string);
		if (!n_he->struct_str)
		{
			free(n_he);
			return (NULL);
		}
	}
	n_he->struct_next = *h_pt;
	*h_pt = n_he;
	return (n_he);
}
