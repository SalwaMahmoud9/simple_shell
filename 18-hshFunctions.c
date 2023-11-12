#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_Pass *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (active(info))
			_puts("$ ");
		_putC(BUFFER_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (active(info))
			_putchar('\n');
		free_info(info, 0);
	}
	hist_w(info);
	free_info(info, 1);
	if (!active(info) && info->sta_S)
		exit(info->sta_S);
	if (builtin_ret == -2)
	{
		if (info->error_N == -1)
			exit(info->sta_S);
		exit(info->error_N);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtinString command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtinString not found,
 *			0 if builtinString executed successfully,
 *			1 if builtinString found but not successful,
 *			-2 if builtinString signals exit()
 */
int find_builtin(info_Pass *info)
{
	int i, built_in_ret = -1;
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

	for (i = 0; builtintbl[i].strType; i++)
		if (_comparestring(info->arg_V[0], builtintbl[i].strType) == 0)
		{
			info->error_C++;
			built_in_ret = builtintbl[i].f(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_Pass *info)
{
	char *path = NULL;
	int i, k;

	info->string_P = info->arg_V[0];
	if (info->flag_C == 1)
	{
		info->error_C++;
		info->flag_C = 0;
	}
	for (i = 0, k = 0; info->arg_G[i]; i++)
		if (!check_del(info->arg_G[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getevFunc(info, "PATH="), info->arg_V[0]);
	if (path)
	{
		info->string_P = path;
		fork_cmd(info);
	}
	else
	{
		if ((active(info) || _getevFunc(info, "PATH=")
			|| info->arg_V[0][0] == '/') && is_cmd(info, info->arg_V[0]))
			fork_cmd(info);
		else if (*(info->arg_G) != '\n')
		{
			info->sta_S = 127;
			p_err(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_Pass *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->string_P, info->arg_V, getenvFunc(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->sta_S));
		if (WIFEXITED(info->sta_S))
		{
			info->sta_S = WEXITSTATUS(info->sta_S);
			if (info->sta_S == 126)
				p_err(info, "Permission denied\n");
		}
	}
}
