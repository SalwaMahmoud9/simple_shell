#include "shell.h"

/**
 * iChain - iChain
 * @passInfo: var
 * @bufr: var
 * @xx: var
 * Return: int
 */
int iChain(info_Pass *passInfo, char *bufr, size_t *xx)
{
	size_t x = *xx;

	if (bufr[x] == '|' && bufr[x + 1] == '|')
	{
		bufr[x] = 0;
		x++;
		passInfo->cm_BT = COMMAND_O;
	}
	else if (bufr[x] == '&' && bufr[x + 1] == '&')
	{
		bufr[x] = 0;
		x++;
		passInfo->cm_BT = COMMAND_A;
	}
	else if (bufr[x] == ';') /* found end of this command */
	{
		bufr[x] = 0; /* replace semicolon with null */
		passInfo->cm_BT = COMMAND_CH;
	}
	else
		return (0);
	*xx = x;
	return (1);
}

/**
 * chChain - chChain
 * @passInfo: var
 * @bufr: var
 * @xx: var
 * @yy: var
 * @ln: var
 * Return: Void
 */
void chChain(info_Pass *passInfo, char *bufr, size_t *xx, size_t yy, size_t ln)
{
	size_t x = *xx;

	if (passInfo->cm_BT == COMMAND_A)
	{
		if (passInfo->sta_S)
		{
			bufr[yy] = 0;
			x = ln;
		}
	}
	if (passInfo->cm_BT == COMMAND_O)
	{
		if (!passInfo->sta_S)
		{
			bufr[yy] = 0;
			x = ln;
		}
	}

	*xx = x;
}

/**
 * reAlias - reAlias
 * @passInfo: var
 * Return: int
 */
int reAlias(info_Pass *passInfo)
{
	int yy;
	list_String *nd;
	char *xx;

	for (yy = 0; yy < 10; yy++)
	{
		nd = node_starts_with(passInfo->al_AI, passInfo->arg_V[0], '=');
		if (!nd)
			return (0);
		free(passInfo->arg_V[0]);
		xx = _strchr(nd->st, '=');
		if (!xx)
			return (0);
		xx = _strdup(xx + 1);
		if (!xx)
			return (0);
		passInfo->arg_V[0] = xx;
	}
	return (1);
}

/**
 * reVar - reVar
 * @passInfo: var
 * Return: int
 */
int reVar(info_Pass *passInfo)
{
	int yy = 0;
	list_String *nd;

	for (yy = 0; passInfo->arg_V[yy]; yy++)
	{
		if (passInfo->arg_V[yy][0] != '$' || !passInfo->arg_V[yy][1])
			continue;

		if (!_strcmp(passInfo->arg_V[yy], "$?"))
		{
			reStr(&(passInfo->arg_V[yy]),
				_strdup(convert_number(passInfo->sta_S, 10, 0)));
			continue;
		}
		if (!_strcmp(passInfo->arg_V[yy], "$$"))
		{
			reStr(&(passInfo->arg_V[yy]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nd = node_starts_with(passInfo->env_L, &passInfo->arg_V[yy][1], '=');
		if (nd)
		{
			reStr(&(passInfo->arg_V[yy]),
				_strdup(_strchr(nd->st, '=') + 1));
			continue;
		}
		reStr(&passInfo->arg_V[yy], _strdup(""));

	}
	return (0);
}

/**
 * reStr - reStr
 * @o: var
 * @n: var
 * Return: int
 */
int reStr(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
