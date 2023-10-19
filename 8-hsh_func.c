#include "shell.h"

/**
 * hsh_func - shell loop
 * @var1: var1
 * @arg_vector: arg_vector
 *
 * Return: output
 */
int hsh_func(information_struct *var1, char **arg_vector)
{
	ssize_t r = 0;
	int output = 0;

	while (r != -1 && output != -2)
	{
		init_info(var1);
		if (shell_status(var1))
			string_print("$ ");
		put_echar(BUFF_F);
		r = input_get(var1);
		if (shell_status(var1))
			string_print2('\n');
		else if (r != -1)
		{
			info_set(var1, arg_vector);
			output = cmd_builtin_find(var1);
			if (output == -1)
				cmd_find(var1);
		}
		info_free(var1, 0);
	}
	history_write(var1);
	info_free(var1, 1);
	if (output == -2)
	{
		if (var1->struct_num == -1)
			exit(var1->struct_status);
		exit(var1->struct_num);
	}
	if (!shell_status(var1) && var1->struct_status)
		exit(var1->struct_status);

	return (output);
}

/**
 * cmd_builtin_find - cmd_builtin_find
 * @var1: var1
 *
 * Return: 0 if successful,
 *			1 if not successful,
 *			-2 if exit(),
 *			-1 if not found
 */
int cmd_builtin_find(information_struct *var1)
{
	int i, built_in_ret = -1;
	builtin_struct builtintbl[] = {
		{"exit", shell_exit},
		{"env", print_env},
		{"history", show_history},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{"cd", change_dir},
		{"alias", alias_mimics},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].struct_type; i++)
		if (string_compare(var1->struct_argv[0], builtintbl[i].struct_type) == 0)
		{
			var1->struct_count++;
			built_in_ret = builtintbl[i].struct_function(var1);
			break;
		}
	return (built_in_ret);
}

/**
 * cmd_find - cmd_find
 * @var1: var1
 *
 * Return: no return
 */
void cmd_find(information_struct *var1)
{
	char *path = NULL;
	int i, k;

	var1->struct_path = var1->struct_argv[0];
	if (var1->struct_count_f == 1)
	{
		var1->struct_count++;
		var1->struct_count_f = 0;
	}
	for (i = 0, k = 0; var1->struct_arg[i]; i++)
		if (!char_delim(var1->struct_arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = get_path(var1, get_env(var1, "PATH="), var1->struct_argv[0]);
	if (path)
	{
		var1->struct_path = path;
		cmd_f(var1);
	}
	else
	{
		if ((shell_status(var1) || get_env(var1, "PATH=")
			|| var1->struct_argv[0][0] == '/')
			&& file_status(var1, var1->struct_argv[0]))
			cmd_f(var1);
		else if (*(var1->struct_arg) != '\n')
		{
			var1->struct_status = 127;
			print_err(var1, "not found\n");
		}
	}
}

/**
 * cmd_f - cmd_f
 * @var1: var1
 *
 * Return: no return
 */
void cmd_f(information_struct *var1)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		return;
	}
	if (child_pid != 0)
	{
		wait(&(var1->struct_status));
		if (WIFEXITED(var1->struct_status))
		{
			var1->struct_status = WEXITSTATUS(var1->struct_status);
			if (var1->struct_status == 126)
				print_err(var1, "Wrong\n");
		}
	}
	else
	{
		if (execve(var1->struct_path, var1->struct_argv, return_env(var1)) == -1)
		{
			info_free(var1, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
}
