#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_Pass *info)
{
	char *buf, *dir;

	dir = _getevFunc(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_lengthstring(dir) + _lengthstring(HISTORY_F) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_stringcopy(buf, dir);
	_stringcat(buf, "/");
	_stringcat(buf, HISTORY_F);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_Pass *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_String *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->his_T; node; node = node->nx)
	{
		_putsfd(node->st, fd);
		_putfd('\n', fd);
	}
	_putfd(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_Pass *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->his_C = linecount;
	while (info->his_C-- >= HISTORY_M)
		d_node_i(&(info->his_T), 0);
	renumber_history(info);
	return (info->his_C);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_Pass *info, char *buf, int linecount)
{
	list_String *node = NULL;

	if (info->his_T)
		node = info->his_T;
	plus_e_node(&node, buf, linecount);

	if (!info->his_T)
		info->his_T = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_Pass *info)
{
	list_String *node = info->his_T;
	int i = 0;

	while (node)
	{
		node->no = i++;
		node = node->nx;
	}
	return (info->his_C = i);
}
