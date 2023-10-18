#include "shell.h"

/**
 * change_dir - change directory
 * @information: input variable
 *  Return: 0
 */
int change_dir(information_struct *information)
{
	int chdir_var;
	char *directory, buff[1024], *x;

	x = getcwd(buff, 1024);

	if (!x)
		string_print("fail msg");
	if (!information->struct_argv[1])
	{
		directory = get_env(information, "HOME=");
			if (directory)
				chdir_var = chdir(directory);
			else
			{
				if (get_env(information, "PWD="))
				{
					directory = get_env(information, "PWD=");
					chdir_var = chdir(directory);
				}
				else
				{
					chdir_var = chdir("/");
				}
			}
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
		if (get_env(information, "OLDPWD="))
		{
			directory = get_env(information, "OLDPWD=");
			chdir_var = chdir(directory);
		}
		else
		{
			chdir_var = chdir("/");
		}
	}
	else
		chdir_var = chdir(information->struct_argv[1]);
	if (chdir_var == -1)
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
 * @information: input variable
 * @s: string
 * Return: 0/1
 */
int alias_unset(information_struct *information, char *s)
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
	r = node_delete_with_index(&(information->struct_als), node_index(information->struct_als, startwith_node(information->struct_als, s, -1)));
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
 * @information: input variable
 *  Return: 0
 */
int alias_mimics(information_struct *information)
{
	int i = 0;
	list_struct *n = NULL;
	char *p = NULL;

	if (information->struct_argc == 1)
	{
		n = information->struct_als;
		while (n)
		{
			alias_print(n);
			n = n->struct_next;
		}
		return (0);
	}
	for (i = 1; information->struct_argv[i]; i++)
	{
		p = string_locate(information->struct_argv[i], '=');
		if (!p)
		{
			alias_print(startwith_node(information->struct_als, information->struct_argv[i], '='));
		}
		else
		{
			alias_set(information, information->struct_argv[i]);
		}
	}

	return (0);
}
