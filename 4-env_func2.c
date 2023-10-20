#include "shell.h"

/**
 * _unset_env - unset environ
 * @var1: var1
 *  Return: 1,0
 */
int _unset_env(information_struct *var1)
{
	int i;

	if (var1->struct_argc == 1)
	{
		_put_estring("Wrong Data.\n");
		return (1);
	}
	for (i = 1; i <= var1->struct_argc; i++)
		_remove_env(var1, var1->struct_argv[i]);

	return (0);
}


/**
 * return_env - return environ data
 * @var1: var1
 * Return: var1->struct_env_copy
 */
char **return_env(information_struct *var1)
{
	if (!var1->struct_env_copy || var1->struct_change_env)
	{
		var1->struct_env_copy = convert_lis_to_str(var1->environ);
		var1->struct_change_env = 0;
	}

	return (var1->struct_env_copy);
}

/**
 * _remove_env - Remove environ
 * @var1: var1
 *  Return: var1->struct_change_env, 0
 * @var: string
 */
int _remove_env(information_struct *var1, char *var)
{
	list_struct *var2 = var1->environ;
	size_t i = 0;
	char *char1;

	if (!var2 || !var)
		return (0);

	while (var2)
	{
		char1 = begin_with(var2->struct_str, var);
		if (char1 && *char1 == '=')
		{
			var1->struct_change_env = node_delete_with_index(&(var1->environ), i);
			i = 0;
			var2 = var1->environ;
			continue;
		}
		var2 = var2->struct_next;
		i++;
	}
	return (var1->struct_change_env);
}

/**
 * _print_env - print environ
 * @var1: maintain constant function prototype.
 *
 * Return: 0
 */
int _print_env(information_struct *var1)
{
	strlist_print(var1->environ);
	return (0);
}
