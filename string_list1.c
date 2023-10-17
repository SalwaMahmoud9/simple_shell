#include "shell.h"


/**
 * node_index - node index
 * @h_pt: pointer
 * @n: node
 * Return: index /-1
 */
ssize_t node_index(list_struct *h_pt, list_struct *n)
{
	size_t ii = 0;

	while (h_pt)
	{
		if (h_pt == n)
			return (ii);
		h_pt = h_pt->struct_next;
		ii++;
	}
	return (-1);
}

/**
 * node_end - node at end
 * @h_pt: pointer
 * @string: string
 * @num: index
 * Return: list size
 */
list_struct *node_end(list_struct **h_pt, const char *string, int num)
{
	list_struct *new_node;
	list_struct *n;

	if (!h_pt)
		return (NULL);

	n = *h_pt;
	new_node = malloc(sizeof(list_struct));
	if (!new_node)
		return (NULL);
	memory_set((void *)new_node, 0, sizeof(list_struct));
	new_node->struct_no = num;
	if (string)
	{
		new_node->struct_str = string_duplicate(string);
		if (!new_node->struct_str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (n)
	{
		while (n->struct_next)
			n = n->struct_next;
		n->struct_next = new_node;
	}
	else
		*h_pt = new_node;
	return (new_node);
}


/**
 * node_delete_with_index - delete index
 * @h_pt: pointer
 * @index: index
 * Return: 1/0
 */
int node_delete_with_index(list_struct **h_pt, unsigned int index)
{
	list_struct *n;
	list_struct *prev_node;
	unsigned int ii = 0;
	int check = 0;

	if (!h_pt || !*h_pt)
	{
		check = 0;
		return (check);
	}
	if (!index)
	{
		n = *h_pt;
		*h_pt = (*h_pt)->struct_next;
		free(n->struct_str);
		free(n);
		check = 1;
		return (check);
	}
	n = *h_pt;
	while (n)
	{
		if (ii == index)
		{
			prev_node->struct_next = n->struct_next;
			free(n->struct_str);
			free(n);
			check = 1;
			return (check);
		}
		ii++;
		prev_node = n;
		n = n->struct_next;
	}
	return (check);
}

/**
 * free_allnodes - free all nodes
 * @head_ptr: pointer
 * Return: no return
 */
void free_allnodes(list_struct **head_ptr)
{
	list_struct *n;
	list_struct *n_n;
	list_struct *h_pt;

	if (!*head_ptr || !head_ptr)
		return;
	h_pt = *head_ptr;
	n = h_pt;
	while (n)
	{
		n_n = n->struct_next;
		free(n->struct_str);
		free(n);
		n = n_n;
	}
	*head_ptr = NULL;
}

/**
 * strlist_print - string list print
 * @h: pointer
 * Return: size
 */
size_t strlist_print(const list_struct *h)
{
	size_t ii = 0;

	while (h)
	{
		string_print(h->struct_str ? h->struct_str : "(nil)");
		string_print("\n");
		h = h->struct_next;
		ii++;
	}
	return (ii);
}
