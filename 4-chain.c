#include "shell.h"


/**
 * checkChainF - checkChainF
 * @passInfo: var
 * @buff: var
 * @x: var
 * @ii: var
 * @l: var
 * Return: Void
 */
void checkChainF(info_Pass *passInfo, char *buff, size_t *x, size_t ii, size_t l)
{
	size_t jj = *x;

	if (passInfo->cm_BT == COMMAND_A)
	{
		if (passInfo->sta_S)
		{
			buff[ii] = 0;
			jj = l;
		}
	}
	if (passInfo->cm_BT == COMMAND_O)
	{
		if (!passInfo->sta_S)
		{
			buff[ii] = 0;
			jj = l;
		}
	}

	*x = jj;
}

/**
 * check_Chain - check_Chain
 * @passInfo: var
 * @buff: var
 * @x: var
 * Return: int
 */
int check_Chain(info_Pass *passInfo, char *buff, size_t *x)
{
	size_t jj = *x;

	if (buff[jj] == '|' && buff[jj + 1] == '|')
	{
		buff[jj] = 0;
		jj++;
		passInfo->cm_BT = COMMAND_O;
	}
	else if (buff[jj] == '&' && buff[jj + 1] == '&')
	{
		buff[jj] = 0;
		jj++;
		passInfo->cm_BT = COMMAND_A;
	}
	else if (buff[jj] == ';')
	{
		buff[jj] = 0;
		passInfo->cm_BT = COMMAND_CH;
	}
	else
		return (0);
	*x = jj;
	return (1);
}

/**
 * rep_Alias - rep_Alias
 * @passInfo: var
 * Return: int
 */
int rep_Alias(info_Pass *passInfo)
{
	int ii;
	char *x;
	list_String *n;

	for (ii = 0; ii < 10; ii++)
	{
		n = node_starts_with(passInfo->al_AI, passInfo->arg_V[0], '=');
		if (!n)
			return (0);
		free(passInfo->arg_V[0]);
		x = _strchr(n->st, '=');
		if (!x)
			return (0);
		x = _strdup(x + 1);
		if (!x)
			return (0);
		passInfo->arg_V[0] = x;
	}
	return (1);
}

/**
 * rep_String - rep_String
 * @xx: var
 * @yy: var
 * Return: int
 */
int rep_String(char **xx, char *yy)
{
	free(*xx);
	*xx = yy;
	return (1);
}

/**
 * rep_Variables - rep_Variables
 * @passInfo: var
 * Return: int
 */
int rep_Variables(info_Pass *passInfo)
{
	int ii = 0;
	list_String *n;

	for (ii = 0; passInfo->arg_V[ii]; ii++)
	{
		if (passInfo->arg_V[ii][0] != '$' || !passInfo->arg_V[ii][1])
			continue;

		if (!_strcmp(passInfo->arg_V[ii], "$?"))
		{
			rep_String(&(passInfo->arg_V[ii]),
				_strdup(convert_number(passInfo->sta_S, 10, 0)));
			continue;
		}
		if (!_strcmp(passInfo->arg_V[ii], "$$"))
		{
			rep_String(&(passInfo->arg_V[ii]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		n = node_starts_with(passInfo->env_L, &passInfo->arg_V[ii][1], '=');
		if (n)
		{
			rep_String(&(passInfo->arg_V[ii]),
				_strdup(_strchr(n->st, '=') + 1));
			continue;
		}
		rep_String(&passInfo->arg_V[ii], _strdup(""));

	}
	return (0);
}
