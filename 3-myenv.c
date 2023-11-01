#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_Pass *info)
{
	if (!info->environ || info->env_C)
	{
		info->environ = list_to_strings(info->env_L);
		info->env_C = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_Pass *info, char *var)
{
	list_String *node = info->env_L;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->st, var);
		if (p && *p == '=')
		{
			info->env_C = delete_node_at_index(&(info->env_L), i);
			i = 0;
			node = info->env_L;
			continue;
		}
		node = node->nx;
		i++;
	}
	return (info->env_C);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_Pass *info, char *var, char *value)
{
	char *buf = NULL;
	list_String *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env_L;
	while (node)
	{
		p = starts_with(node->st, var);
		if (p && *p == '=')
		{
			free(node->st);
			node->st = buf;
			info->env_C = 1;
			return (0);
		}
		node = node->nx;
	}
	add_node_end(&(info->env_L), buf, 0);
	free(buf);
	info->env_C = 1;
	return (0);
}
