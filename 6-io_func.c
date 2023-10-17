#include "shell.h"

/**
 * history_build - build history
 * @var1: var1
 * @var3: var3
 * @l_count: l_count
 *
 * Return: 0
 */
int history_build(information_struct *var1, char *var3, int l_count)
{
	list_struct *var2 = NULL;

	if (!var1->struct_his)
		var1->struct_his = var2;

	if (var1->struct_his)
		var2 = var1->struct_his;
	node_end(&var2, var3, l_count);

	return (0);
}

/**
 * history_read - history_read
 * @var1: var1
 *
 * Return: var1->struct_hist_c, 0
 */
int history_read(information_struct *var1)
{
	int i, last = 0, l_count = 0;
	ssize_t fd, read_len, f_size = 0;
	struct stat st;
	char *var3 = NULL, *f_name = history_get_file(var1);

	if (!f_name)
		return (0);

	fd = open(f_name, O_RDONLY);
	free(f_name);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	var3 = malloc(sizeof(char) * (f_size + 1));
	if (!var3)
		return (0);
	read_len = read(fd, var3, f_size);
	var3[f_size] = 0;
	if (read_len <= 0)
		return (free(var3), 0);
	close(fd);
	for (i = 0; i < f_size; i++)
		if (var3[i] == '\n')
		{
			var3[i] = 0;
			history_build(var1, var3 + last, l_count++);
			last = i + 1;
		}
	if (last != i)
		history_build(var1, var3 + last, l_count++);
	free(var3);
	var1->struct_hist_c = l_count;
	while (var1->struct_hist_c-- >= HIST_M)
		node_delete_with_index(&(var1->struct_his), 0);
	history_renumbers(var1);
	return (var1->struct_hist_c);
}

/**
 * history_get_file - history_get_file
 * @var1: var1
 *
 * Return: var3, NULL
 */

char *history_get_file(information_struct *var1)
{
	char *var3, *dir;

	dir = get_env(var1, "HOME=");
	if (!dir)
		return (NULL);
	var3 = malloc(sizeof(char) * (string_length(dir) + string_length(HIST_F) + 2));
	if (!var3)
		return (NULL);
	var3[0] = 0;
	string_copy(var3, dir);
	string_concat(var3, "/");
	string_concat(var3, HIST_F);
	return (var3);
}

/**
 * history_write - history_write
 * @var1: var1
 *
 * Return: 1, -1
 */
int history_write(information_struct *var1)
{
	ssize_t fd;
	char *f_name = history_get_file(var1);
	list_struct *var2 = NULL;

	if (!f_name)
		return (-1);

	fd = open(f_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f_name);
	if (fd == -1)
		return (-1);
	for (var2 = var1->struct_his; var2; var2 = var2->struct_next)
	{
		put_file_desc('\n', fd);
		print_file_desc(var2->struct_str, fd);
	}
	put_file_desc(BUFF_F, fd);
	close(fd);
	return (1);
}

/**
 * history_renumbers - renumbers
 * @var1: var1
 *
 * Return: var1->struct_hist_c = i
 */
int history_renumbers(information_struct *var1)
{
	list_struct *var2 = var1->struct_his;
	int i = 0;

	while (var2)
	{
		var2->struct_no = i++;
		var2 = var2->struct_next;
	}
	return (var1->struct_hist_c = i);
}
