#include "shell.h"

/**
 * get_fork_cmd - get_fork_cmd
 * @passInfo: var
 * Return: void
 */
void get_fork_cmd(info_Pass *passInfo)
{
	pid_t chPid;

	chPid = fork();
	if (chPid == -1)
	{
		perror("Error:");
		return;
	}
	if (chPid == 0)
	{
		if (execve(passInfo->string_P, passInfo->arg_V, getenvFunc(passInfo)) == -1)
		{
			freeInfo(passInfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(passInfo->sta_S));
		if (WIFEXITED(passInfo->sta_S))
		{
			passInfo->sta_S = WEXITSTATUS(passInfo->sta_S);
			if (passInfo->sta_S == 126)
				p_err(passInfo, "Permission denied\n");
		}
	}
}

/**
 * hsh - hsh
 * @passInfo: var
 * @av: var
 * Return: int
 */
int hsh(info_Pass *passInfo, char **av)
{
	ssize_t sizeR = 0;
	int ret = 0;

	while (sizeR != -1 && ret != -2)
	{
		clearInfo(passInfo);
		if (active(passInfo))
			_puts("$ ");
		_putC(BUFFER_FLUSH);
		sizeR = get_it(passInfo);
		if (sizeR != -1)
		{
			setInfo(passInfo, av);
			ret = get_build_in(passInfo);
			if (ret == -1)
				get_cmd(passInfo);
		}
		else if (active(passInfo))
			_putchar('\n');
		freeInfo(passInfo, 0);
	}
	hist_w(passInfo);
	freeInfo(passInfo, 1);
	if (!active(passInfo) && passInfo->sta_S)
		exit(passInfo->sta_S);
	if (ret == -2)
	{
		if (passInfo->error_N == -1)
			exit(passInfo->sta_S);
		exit(passInfo->error_N);
	}
	return (ret);
}

/**
 * get_build_in - get_build_in
 * @passInfo: var
 * Return: int
 */
int get_build_in(info_Pass *passInfo)
{
	int ii, ret = -1;
	builtin_String builtintbl[] = {
		{"exit", _exitFunc},
		{"env", _envFunc},
		{"help", _helpFunc},
		{"history", _historyFunc},
		{"setenv", _stevFunc},
		{"unsetenv", _ustevFunc},
		{"cd", _changeDirFunc},
		{"alias", _aliasFunc},
		{NULL, NULL}
	};

	for (ii = 0; builtintbl[ii].strType; ii++)
		if (_comparestring(passInfo->arg_V[0], builtintbl[ii].strType) == 0)
		{
			passInfo->error_C++;
			ret = builtintbl[ii].f(passInfo);
			break;
		}
	return (ret);
}

/**
 * get_cmd - get_cmd
 * @passInfo: var
 * Return: void
 */
void get_cmd(info_Pass *passInfo)
{
	char *p = NULL;
	int ii, k;

	passInfo->string_P = passInfo->arg_V[0];
	if (passInfo->flag_C == 1)
	{
		passInfo->error_C++;
		passInfo->flag_C = 0;
	}
	for (ii = 0, k = 0; passInfo->arg_G[ii]; ii++)
		if (!check_del(passInfo->arg_G[ii], " \t\n"))
			k++;
	if (!k)
		return;

	p = get_path(passInfo, _getevFunc(passInfo, "PATH="), passInfo->arg_V[0]);
	if (p)
	{
		passInfo->string_P = p;
		get_fork_cmd(passInfo);
	}
	else
	{
		if ((active(passInfo) || _getevFunc(passInfo, "PATH=")
			|| passInfo->arg_V[0][0] == '/')
			&& cmmd_check(passInfo, passInfo->arg_V[0]))
			get_fork_cmd(passInfo);
		else if (*(passInfo->arg_G) != '\n')
		{
			passInfo->sta_S = 127;
			p_err(passInfo, "not found\n");
		}
	}
}
