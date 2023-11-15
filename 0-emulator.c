#include "shell.h"

/**
 * _exitFunc - exitFunc
 * @passInfo: info_Pass
 * Return: int
 */
int _exitFunc(info_Pass *passInfo)
{
	int exitVar, returnCheck = -2, returnCheck1 = 1;

	if (passInfo->arg_V[1])
	{
		exitVar = _atoierror(passInfo->arg_V[1]);
		if (exitVar == -1)
		{
			passInfo->sta_S = 2;
			p_err(passInfo, "error number: ");
			_put(passInfo->arg_V[1]);
			_putC('\n');
			return (returnCheck1);
		}
		passInfo->error_N = _atoierror(passInfo->arg_V[1]);
		return (returnCheck);
	}
	passInfo->error_N = -1;
	return (returnCheck);
}

/**
 * _helpFunc - helpFunc
 * @passInfo: info_Pass
 * Return: int
 */
int _helpFunc(info_Pass *passInfo)
{
	char **var_arr;
	int valueZero = 0;

	var_arr = passInfo->arg_V;
	_puts("help \n");
	if (valueZero)
		_puts(*var_arr);
	return (valueZero);
}

/**
 * _historyFunc - _historyFunc
 * @passInfo: info_Pass
 * Return: int
 */
int _historyFunc(info_Pass *passInfo)
{
	int valueZero = 0;

	p_list(passInfo->his_T);
	return (valueZero);
}
