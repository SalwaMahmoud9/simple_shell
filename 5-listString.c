#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_String *add_node(list_String **head, const char *str, int num)
{
	list_String *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_String));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_String));
	new_head->no = num;
	if (str)
	{
		new_head->st = _strdup(str);
		if (!new_head->st)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->nx = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_String *add_node_end(list_String **head, const char *str, int num)
{
	list_String *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_String));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_String));
	new_node->no = num;
	if (str)
	{
		new_node->st = _strdup(str);
		if (!new_node->st)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->nx)
			node = node->nx;
		node->nx = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_String linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_String *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->st ? h->st : "(nil)");
		_puts("\n");
		h = h->nx;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_String **head, unsigned int index)
{
	list_String *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->nx;
		free(node->st);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->nx = node->nx;
			free(node->st);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->nx;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_String **head_ptr)
{
	list_String *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->nx;
		free(node->st);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
