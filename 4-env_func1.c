#include "shell.h"

/**
 * _init_env - Initialize env
 * @var1: var1
 * @var: string var
 * @value: string value
 *  Return: 1,0
 */

int _init_env(information_struct *var1, char *var, char *value)
{
	char *var2 = NULL;
	list_struct *var3;
	char *var4;

	if (!var || !value)
		return (0);

	var2 = malloc(_string_length(var) + _string_length(value) + 2);
	if (!var2)
		return (1);
	_string_copy(var2, var);
	_string_concat(var2, "=");
	_string_concat(var2, value);
	var3 = var1->environ;
	while (var3)
	{
		var4 = begin_with(var3->struct_str, var);
		if (var4 && *var4 == '=')
		{
			free(var3->struct_str);
			var3->struct_str = var2;
			var1->struct_change_env = 1;
			return (0);
		}
		var3 = var3->struct_next;
	}
	node_end(&(var1->environ), var2, 0);
	free(var2);
	var1->struct_change_env = 1;
	return (0);
}

/**
 * populate_env - populates env
 * @var1: var1
 * Return: 0
 */
int populate_env(information_struct *var1)
{
	list_struct *var2 = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		node_end(&var2, environ[i], 0);
	var1->environ = var2;
	return (0);
}

/**
 * _set_env - set environ
 * @var1: var1
 *  Return: 1,0
 */
int _set_env(information_struct *var1)
{
	if (_init_env(var1, var1->struct_argv[1], var1->struct_argv[2]))
		return (0);

	if (var1->struct_argc != 3)
	{
		_put_estring("Wrong Data\n");
		return (1);
	}
	return (1);
}

/**
 * _get_env - get environ
 * @var1: contain arguments
 * @name: env var name
 *
 * Return: the value
 */
char *_get_env(information_struct *var1, const char *name)
{
	list_struct *var3 = var1->environ;
	char *var4;

	while (var3)
	{
		var4 = begin_with(var3->struct_str, name);
		if (var4 && *var4)
			return (var4);
		var3 = var3->struct_next;
	}
	return (NULL);
}
