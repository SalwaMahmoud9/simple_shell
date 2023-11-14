#include "shell.h"


/**
 * getenvFunc - getenvFunc
 * @passInfo: var.
 * Return: char
 */
char **getenvFunc(info_Pass *passInfo)
{
	if (!passInfo->environ || passInfo->env_C)
	{
		passInfo->environ = list_strs(passInfo->env_L);
		passInfo->env_C = 0;
	}

	return (passInfo->environ);
}

/**
 * _unenvFunc - _unenvFunc
 * @passInfo: var
 * @v: var
 * Return: int
 */
int _unenvFunc(info_Pass *passInfo, char *v)
{
	size_t ii = 0;
	list_String *listString_n = passInfo->env_L;
	char *x;

	if (!listString_n || !v)
		return (0);

	while (listString_n)
	{
		x = st_wth(listString_n->st, v);
		if (x && *x == '=')
		{
			passInfo->env_C = d_node_i(&(passInfo->env_L), ii);
			ii = 0;
			listString_n = passInfo->env_L;
			continue;
		}
		listString_n = listString_n->nx;
		ii++;
	}
	return (passInfo->env_C);
}

/**
 * _stevFunc - _stevFunc
 * @passInfo: var
 * Return: int
 */
int _stevFunc(info_Pass *passInfo)
{
	if (passInfo->arg_C != 3)
	{
		_put("Incorrect number of arguements\n");
		return (1);
	}
	if (_stenvFunc(passInfo, passInfo->arg_V[1], passInfo->arg_V[2]))
		return (0);
	return (1);
}

/**
 * _ustevFunc - _ustevFunc
 * @passInfo: var
 * Return: int
 */
int _ustevFunc(info_Pass *passInfo)
{
	int ii;

	if (passInfo->arg_C == 1)
	{
		_put("Too few arguements.\n");
		return (1);
	}
	for (ii = 1; ii <= passInfo->arg_C; ii++)
		_unenvFunc(passInfo, passInfo->arg_V[ii]);

	return (0);
}
