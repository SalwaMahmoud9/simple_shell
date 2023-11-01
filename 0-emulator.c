#include "shell.h"

/**
 * _changeDirFunc - _changeDirFunc
 * @passInfo: info_Pass
 * Return: int
 */
int _changeDirFunc(info_Pass *passInfo)
{
	int chd;
	char *x, *dic, buffer1[1024];

	x = getcwd(buffer1, 1024);
	if (!x)
		_puts("failure \n");
	if (!passInfo->arg_V[1])
	{
		dic = _getenv(passInfo, "HOME=");
		if (!dic)
			chd = chdir((dic = _getenv(passInfo, "PWD=")) ? dic : "/");
		else
			chd = chdir(dic);
	}
	else if (_strcmp(passInfo->arg_V[1], "-") == 0)
	{
		if (!_getenv(passInfo, "OLDPWD="))
		{
			_puts(x);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(passInfo, "OLDPWD=")), _putchar('\n');
		chd = chdir((dic = _getenv(passInfo, "OLDPWD=")) ? dic : "/");
	}
	else
		chd = chdir(passInfo->arg_V[1]);
	if (chd == -1)
	{
		print_error(passInfo, "can't cd to ");
		_eputs(passInfo->arg_V[1]), _eputchar('\n');
	}
	else
	{
		_setenv(passInfo, "OLDPWD", _getenv(passInfo, "PWD="));
		_setenv(passInfo, "PWD", getcwd(buffer1, 1024));
	}
	return (0);
}

/**
 * pAliasFunc - pAliasFunc
 * @n_stringList: list_String
 * Return: int
 */
int pAliasFunc(list_String *n_stringList)
{
	char *x = NULL;
	char *y = NULL;

	if (n_stringList)
	{
		x = _strchr(n_stringList->st, '=');
		for (y = n_stringList->st; y <= x; y++)
			_putchar(*y);
		_putchar('\'');
		_puts(x + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _helpFunc - _helpFunc
 * @passInfo: info_Pass
 * Return: int
 */
int _helpFunc(info_Pass *passInfo)
{
	char **var_arr;

	var_arr = passInfo->arg_V;
	_puts("help \n");
	if (0)
		_puts(*var_arr);
	return (0);
}

/**
 * _historyFunc - _historyFunc
 * @passInfo: info_Pass
 * Return: int
 */
int _historyFunc(info_Pass *passInfo)
{
	print_list(passInfo->his_T);
	return (0);
}
