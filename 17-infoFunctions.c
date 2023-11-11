#include "shell.h"

/**
 * clear_info - initializes info_Pass struct
 * @info: struct address
 */
void clear_info(info_Pass *info)
{
	info->arg_G = NULL;
	info->arg_V = NULL;
	info->string_P = NULL;
	info->arg_C = 0;
}

/**
 * set_info - initializes info_Pass struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_Pass *info, char **av)
{
	int i = 0;

	info->name_F = av[0];
	if (info->arg_G)
	{
		info->arg_V = strtow(info->arg_G, " \t");
		if (!info->arg_V)
		{

			info->arg_V = malloc(sizeof(char *) * 2);
			if (info->arg_V)
			{
				info->arg_V[0] = _strdup(info->arg_G);
				info->arg_V[1] = NULL;
			}
		}
		for (i = 0; info->arg_V && info->arg_V[i]; i++)
			;
		info->arg_C = i;

		reAlias(info);
		reVar(info);
	}
}

/**
 * free_info - frees info_Pass struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_Pass *info, int all)
{
	freePointer(info->arg_V);
	info->arg_V = NULL;
	info->string_P = NULL;
	if (all)
	{
		if (!info->cm_B)
			free(info->arg_G);
		if (info->env_L)
			free_mylist(&(info->env_L));
		if (info->his_T)
			free_mylist(&(info->his_T));
		if (info->al_AI)
			free_mylist(&(info->al_AI));
		freePointer(info->environ);
			info->environ = NULL;
		bfree((void **)info->cm_B);
		if (info->fd_R > 2)
			close(info->fd_R);
		_putchar(BUFFER_FLUSH);
	}
}
