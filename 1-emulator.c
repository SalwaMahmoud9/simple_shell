#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_Pass *info)
{
	print_list(info->his_T);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_Pass *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->al_AI),
		get_node_index(info->al_AI, node_starts_with(info->al_AI, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_Pass *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->al_AI), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_String *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->st, '=');
		for (a = node->st; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtinString (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_Pass *info)
{
	int i = 0;
	char *p = NULL;
	list_String *node = NULL;

	if (info->arg_C == 1)
	{
		node = info->al_AI;
		while (node)
		{
			print_alias(node);
			node = node->nx;
		}
		return (0);
	}
	for (i = 1; info->arg_V[i]; i++)
	{
		p = _strchr(info->arg_V[i], '=');
		if (p)
			set_alias(info, info->arg_V[i]);
		else
			print_alias(node_starts_with(info->al_AI, info->arg_V[i], '='));
	}

	return (0);
}
