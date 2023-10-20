#include "shell.h"

/**
 * get_path - get_path
 * @var1: var1
 * @path: path
 * @cmd: cmd
 *
 * Return: var2,cmd
 */
char *get_path(information_struct *var1, char *path, char *cmd)
{
	int i = 0, var4 = 0;
	char *var2;

	if (!path)
		return (NULL);
	if ((_string_length(cmd) > 2) && begin_with(cmd, "./"))
	{
		if (file_status(var1, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path[i] || path[i] == ':')
		{
			var2 = char_duplicate(path, var4, i);
			if (!*var2)
				_string_concat(var2, cmd);
			else
			{
				_string_concat(var2, "/");
				_string_concat(var2, cmd);
			}
			if (file_status(var1, var2))
				return (var2);
			if (!path[i])
				break;
			var4 = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * char_duplicate - char_duplicate
 * @path: path
 * @start: starting
 * @end: end
 *
 * Return: var2
 */
char *char_duplicate(char *path, int start, int end)
{
	static char var2[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < end; i++)
		if (path[i] != ':')
			var2[k++] = path[i];
	var2[k] = 0;
	return (var2);
}

/**
 * file_status - file_status
 * @var1: var1
 * @var2: var2
 *
 * Return: 1, 0
 */
int file_status(information_struct *var1, char *var2)
{
	struct stat st;

	(void)var1;
	if (!var2 || stat(var2, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
