#include "shell.h"

/**
 * sAliasFunc - sAliasFunc
 * @passInfo: info_Pass
 * @ch: char
 * Return: int
 */
int sAliasFunc(info_Pass *passInfo, char *ch)
{
	char *x;

	x = _strchr(ch, '=');
	if (!x)
		return (1);
	if (!*++x)
		return (unAliasFunc(passInfo, ch));

	unAliasFunc(passInfo, ch);
	return (add_node_end(&(passInfo->al_AI), ch, 0) == NULL);
}

/**
 * unAliasFunc - unAliasFunc
 * @passInfo: info_Pass
 * @ch: char
 * Return: int
 */
int unAliasFunc(info_Pass *passInfo, char *ch)
{
	char *x;
	char y;
	int rn;

	x = _strchr(ch, '=');
	if (!x)
		return (1);
	y = *x;
	*x = 0;
	rn = delete_node_at_index(&(passInfo->al_AI),
		get_node_index(passInfo->al_AI, node_starts_with(passInfo->al_AI, ch, -1)));
	*x = y;
	return (rn);
}

/**
 * _aliasFunc - _aliasFunc
 * @passInfo: info_Pass
 * Return: int
 */
int _aliasFunc(info_Pass *passInfo)
{
	int i = 0;
	char *x = NULL;
	list_String *listString_n = NULL;

	if (passInfo->arg_C == 1)
	{
		listString_n = passInfo->al_AI;
		while (listString_n)
		{
			pAliasFunc(listString_n);
			listString_n = listString_n->nx;
		}
		return (0);
	}
	for (i = 1; passInfo->arg_V[i]; i++)
	{
		x = _strchr(passInfo->arg_V[i], '=');
		if (x)
			sAliasFunc(passInfo, passInfo->arg_V[i]);
		else
			pAliasFunc(node_starts_with(passInfo->al_AI, passInfo->arg_V[i], '='));
	}

	return (0);
}

/**
 * _exitFunc - _exitFunc
 * @passInfo: info_Pass
 * Return: int
 */
int _exitFunc(info_Pass *passInfo)
{
	int exitVar;

	if (passInfo->arg_V[1])
	{
		exitVar = _erratoi(passInfo->arg_V[1]);
		if (exitVar == -1)
		{
			passInfo->sta_S = 2;
			print_error(passInfo, "error number: ");
			_eputs(passInfo->arg_V[1]);
			_eputchar('\n');
			return (1);
		}
		passInfo->error_N = _erratoi(passInfo->arg_V[1]);
		return (-2);
	}
	passInfo->error_N = -1;
	return (-2);
}
