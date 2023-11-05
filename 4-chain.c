#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_Pass *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cm_BT = COMMAND_O;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cm_BT = COMMAND_A;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cm_BT = COMMAND_CH;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_Pass *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cm_BT == COMMAND_A)
	{
		if (info->sta_S)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cm_BT == COMMAND_O)
	{
		if (!info->sta_S)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_Pass *info)
{
	int i;
	list_String *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->al_AI, info->arg_V[0], '=');
		if (!node)
			return (0);
		free(info->arg_V[0]);
		p = _strchr(node->st, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->arg_V[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_Pass *info)
{
	int i = 0;
	list_String *node;

	for (i = 0; info->arg_V[i]; i++)
	{
		if (info->arg_V[i][0] != '$' || !info->arg_V[i][1])
			continue;

		if (!_strcmp(info->arg_V[i], "$?"))
		{
			replace_string(&(info->arg_V[i]),
				_strdup(convert_number(info->sta_S, 10, 0)));
			continue;
		}
		if (!_strcmp(info->arg_V[i], "$$"))
		{
			replace_string(&(info->arg_V[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env_L, &info->arg_V[i][1], '=');
		if (node)
		{
			replace_string(&(info->arg_V[i]),
				_strdup(_strchr(node->st, '=') + 1));
			continue;
		}
		replace_string(&info->arg_V[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
