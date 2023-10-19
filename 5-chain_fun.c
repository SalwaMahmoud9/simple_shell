#include "shell.h"


/**
 * vars_rep - replace var
 * @information: input variable
 * Return: 1/0
 */
int vars_rep(information_struct *information)
{
	list_struct *n;
	int j = 0;

	for (j = 0; information->struct_argv[j]; j++)
	{

		if (!string_compare(information->struct_argv[j], "$?"))
		{
			str_rep(&(information->struct_argv[j]),
				string_duplicate(convert_no(information->struct_status, 10, 0)));
			continue;
		}
		if (!information->struct_argv[j][1] || information->struct_argv[j][0] != '$')
			continue;
		if (!string_compare(information->struct_argv[j], "$$"))
		{
			str_rep(&(information->struct_argv[j]),
				string_duplicate(convert_no(getpid(), 10, 0)));
			continue;
		}
		n = startwith_node(information->struct_env
			, &information->struct_argv[j][1], '=');
		if (n)
		{
			str_rep(&(information->struct_argv[j]),
				string_duplicate(string_locate(n->struct_str, '=') + 1));
			continue;
		}
		str_rep(&information->struct_argv[j], string_duplicate(""));

	}
	return (0);
}

/**
 * chain_check - check chain
 * @information: input variable
 * @buffer: buffer
 * @pr: pointer
 * @start: start
 * @length: length
 */
void chain_check(information_struct *information, char *buffer, size_t *pr, size_t start, size_t length)
{
	size_t i = *pr;

	if (information->struct_buff_t == COM_O)
	{
		if (!information->struct_status)
		{
			buffer[start] = 0;
			i = length;
		}
	}
	if (information->struct_buff_t == COM_A)
	{
		if (information->struct_status)
		{
			buffer[start] = 0;
			i = length;
		}
	}
	*pr = i;
}

/**
 * chain_status - chain status
 * @information: input variable
 * @buffer: the char buffer
 * @pr: address of current position in buffer
 * Return: 0/1
 */
int chain_status(information_struct *information, char *buffer, size_t *pr)
{
	size_t j = *pr;
	int check = 1;

	if (buffer[j + 1] == '&' && buffer[j] == '&')
	{
		buffer[j] = 0;
		j++;
		information->struct_buff_t = COM_A;
	}
	else if (buffer[j + 1] == '|' && buffer[j] == '|')
	{
		buffer[j] = 0;
		j++;
		information->struct_buff_t = COM_O;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		information->struct_buff_t = COM_C;
	}
	else
	{
		check = 0;
		return (check);
	}
	*pr = j;
	return (check);
}

/**
 * alias_rep - replace an aliases string
 * @information: input variable
 * Return: 1/0
 */
int alias_rep(information_struct *information)
{
	char *pr;
	list_struct *n;
	int j;
	int check = 1;

	for (j = 0; j <= 9; j++)
	{
		n = startwith_node(information->struct_als, information->struct_argv[0], '=');
		if (!n)
		{
			check = 0;
			return (check);
		}
		free(information->struct_argv[0]);
		pr = string_locate(n->struct_str, '=');
		if (!pr)
		{
			check = 0;
			return (check);
		}
		pr = string_duplicate(pr + 1);
		if (!pr)
		{
			check = 0;
			return (check);
		}
		information->struct_argv[0] = pr;
	}
	return (check);
}

/**
 * str_rep - replace string
 * @old: old string address
 * @new: new string address
 * Return: 1/0
 */
int str_rep(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
