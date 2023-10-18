#include "shell.h"

/**
 * info_free - free information
 * @information: input variable
 * @fields: fields
 */
void info_free(information_struct *information, int fields)
{
	memory_free(information->struct_argv);
	information->struct_path = NULL;
	information->struct_argv = NULL;
	if (fields)
	{
		if (information->struct_his)
			free_allnodes(&(information->struct_his));
		if (information->struct_env)
			free_allnodes(&(information->struct_env));
		if (!information->struct_buff)
			free(information->struct_arg);
		if (information->struct_als)
			free_allnodes(&(information->struct_als));
		memory_free(information->struct_env_copy);
			information->struct_env_copy = NULL;
		memory_free_pointer((void **)information->struct_buff);
		if (information->struct_f_r > 2)
			close(information->struct_f_r);
		string_print2(BUFF_F);
	}
}

/**
 * init_info - init information
 * @information: input variable
 */
void init_info(information_struct *information)
{
	information->struct_argc = 0;
	information->struct_arg = NULL;
	information->struct_argv = NULL;
	information->struct_path = NULL;

}

/**
 * info_set - init set
 * @information: struct address
 * @vect: vector
 */
void info_set(information_struct *information, char **vect)
{
	int i = 0;

	information->struct_f_name = vect[0];
	if (information->struct_arg)
	{
		information->struct_argv = string_split(information->struct_arg, " \t");
		if (!information->struct_argv)
		{
			information->struct_argv = malloc(sizeof(char *) * 2);
			if (information->struct_argv)
			{
				information->struct_argv[0] = string_duplicate(information->struct_arg);
				information->struct_argv[1] = NULL;
			}
		}
		for (i = 0; information->struct_argv[i] && information->struct_argv ; i++)
			;
		information->struct_argc = i;

		alias_rep(information);
		vars_rep(information);
	}
}
