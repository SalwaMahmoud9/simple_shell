#include "shell.h"

/**
 * change_dir - change directory
 * @information: input variable
 *  Return: 0
 */
int change_dir(information_struct *information)
{
	int chdir_v;
	char *dic, buff[1024], *x;

	x = getcwd(buff, 1024);
	if (!x)
		string_print("fail msg");
	if (!information->struct_argv[1])
	{
		dic = get_env(information, "HOME=");
			if (dic)
				chdir_v = chdir(dic);
			else
				chdir_v = chdir((dic = get_env(information, "PWD=")) ? dic : "/");
	}
	else if (string_compare(information->struct_argv[1], "-") == 0)
	{
		if (!get_env(information, "OLDPWD="))
		{
			string_print(x);
			string_print2('\n');
			return (1);
		}
		string_print(get_env(information, "OLDPWD=")), string_print2('\n');
		chdir_v = chdir((dic = get_env(information, "OLDPWD=")) ? dic : "/");
	}
	else
		chdir_v = chdir(information->struct_argv[1]);
	if (chdir_v == -1)
	{
		print_err(information, "cannot go ");
		put_estring(information->struct_argv[1]), put_echar('\n');
	}
	else
	{
		init_env(information, "OLDPWD", get_env(information, "PWD="));
		init_env(information, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * alias_unset - unset alias
 * @inform: input variable
 * @s: string
 * Return: 0/1
 */
int alias_unset(information_struct *inform, char *s)
{
	int r;
	char *p;
	char c;

	p = string_locate(s, '=');
	if (!p)
	{
		return (1);
	}
	c = *p;
	*p = 0;
	r = node_delete_with_index(&(inform->struct_als),
		node_index(inform->struct_als, startwith_node(inform->struct_als, s, -1)));
	*p = c;
	return (r);
}

/**
 * alias_set - set alias
 * @information: input variable
 * @s: string
 * Return:0/1
 */
int alias_set(information_struct *information, char *s)
{
	char *p;

	p = string_locate(s, '=');
	if (!*++p)
	{
		return (alias_unset(information, s));
	}
	if (!p)
	{
		return (1);
	}
	alias_unset(information, s);
	return (node_end(&(information->struct_als), s, 0) == NULL);
}

/**
 * alias_print - print alias
 * @n: alias node
 * Return: 0/1
 */
int alias_print(list_struct *n)
{
	char *x = NULL;
	char *y = NULL;

	if (!n)
	{
		return (1);
	}
	else
	{
		x = string_locate(n->struct_str, '=');
		for (y = n->struct_str; y <= x; y++)
		{
			string_print2(*y);
		}
		string_print2('\'');
		string_print(x + 1);
		string_print("'\n");
		return (0);
	}
}

/**
 * alias_mimics - mimics alias
 * @inform: input variable
 *  Return: 0
 */
int alias_mimics(information_struct *inform)
{
	int i = 0;
	list_struct *n = NULL;
	char *p = NULL;

	if (inform->struct_argc == 1)
	{
		n = inform->struct_als;
		while (n)
		{
			alias_print(n);
			n = n->struct_next;
		}
		return (0);
	}
	for (i = 1; inform->struct_argv[i]; i++)
	{
		p = string_locate(inform->struct_argv[i], '=');
		if (!p)
		{
			alias_print(startwith_node(inform->struct_als
				, inform->struct_argv[i], '='));
		}
		else
			alias_set(inform, inform->struct_argv[i]);
	}

	return (0);
}