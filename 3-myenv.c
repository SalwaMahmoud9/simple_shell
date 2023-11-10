#include "shell.h"

/**
 * popenvFunc - popenvFunc
 * @passInfo: var
 * Return: int
 */
int popenvFunc(info_Pass *passInfo)
{
	list_String *listString_n = NULL;
	size_t ii;

	for (ii = 0; environ[ii]; ii++)
		plus_e_node(&listString_n, environ[ii], 0);
	passInfo->env_L = listString_n;
	return (0);
}

/**
 * _getevFunc - _getevFunc
 * @passInfo: var
 * @name: var
 * Return: char
 */
char *_getevFunc(info_Pass *passInfo, const char *name)
{
	list_String *listString_n = passInfo->env_L;
	char *x;

	while (listString_n)
	{
		x = starts_with(listString_n->st, name);
		if (x && *x)
			return (x);
		listString_n = listString_n->nx;
	}
	return (NULL);
}

/**
 * _envFunc - _envFunc
 * @passInfo: var
 * Return: int
 */
int _envFunc(info_Pass *passInfo)
{
	p_list_string(passInfo->env_L);
	return (0);
}

/**
 * _stenvFunc - _stenvFunc
 * @passInfo: var
 * @v: var
 * @val: var
 * Return: int
 */
int _stenvFunc(info_Pass *passInfo, char *v, char *val)
{
	list_String *listString_n;
	char *buff = NULL;
	char *x;

	if (!v || !val)
		return (0);

	buff = malloc(_strlen(v) + _strlen(val) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, v);
	_strcat(buff, "=");
	_strcat(buff, val);
	listString_n = passInfo->env_L;
	while (listString_n)
	{
		x = starts_with(listString_n->st, v);
		if (x && *x == '=')
		{
			free(listString_n->st);
			listString_n->st = buff;
			passInfo->env_C = 1;
			return (0);
		}
		listString_n = listString_n->nx;
	}
	plus_e_node(&(passInfo->env_L), buff, 0);
	free(buff);
	passInfo->env_C = 1;
	return (0);
}
