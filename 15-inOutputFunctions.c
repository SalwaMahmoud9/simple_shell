#include "shell.h"

/**
 * hist_w - hist_w
 * @passInfo: var
 * Return: int
 */
int hist_w(info_Pass *passInfo)
{
	char *fn = hist_f(passInfo);
	list_String *n = NULL;
	ssize_t f;

	if (!fn)
		return (-1);

	f = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (f == -1)
		return (-1);
	for (n = passInfo->his_T; n; n = n->nx)
	{
		_putFD(n->st, f);
		_putF('\n', f);
	}
	_putF(BUFFER_FLUSH, f);
	close(f);
	return (1);
}

/**
 * add_hist - add_hist
 * @passInfo: var
 * @b: var
 * @lc: var
 * Return: int
 */
int add_hist(info_Pass *passInfo, char *b, int lc)
{
	list_String *n = NULL;

	if (passInfo->his_T)
		n = passInfo->his_T;
	plus_e_node(&n, b, lc);

	if (!passInfo->his_T)
		passInfo->his_T = n;
	return (0);
}

/**
 * hist_r - hist_r
 * @passInfo: var
 * Return: int
 */
int hist_r(info_Pass *passInfo)
{
	struct stat st;
	int ii, lt = 0;
	int lc = 0;
	char *b = NULL;
	char *fn = hist_f(passInfo);
	ssize_t f, len, fz = 0;

	if (!fn)
		return (0);

	f = open(fn, O_RDONLY);
	free(fn);
	if (f == -1)
		return (0);
	if (!fstat(f, &st))
		fz = st.st_size;
	if (fz < 2)
		return (0);
	b = malloc(sizeof(char) * (fz + 1));
	if (!b)
		return (0);
	len = read(f, b, fz);
	b[fz] = 0;
	if (len <= 0)
		return (free(b), 0);
	close(f);
	for (ii = 0; ii < fz; ii++)
		if (b[ii] == '\n')
		{
			b[ii] = 0;
			add_hist(passInfo, b + lt, lc++);
			lt = ii + 1;
		}
	if (lt != ii)
		add_hist(passInfo, b + lt, lc++);
	free(b);
	passInfo->his_C = lc;
	while (passInfo->his_C-- >= HISTORY_M)
		d_node_i(&(passInfo->his_T), 0);
	re_hist(passInfo);
	return (passInfo->his_C);
}

/**
 * re_hist - re_hist
 * @passInfo: var
 * Return: int
 */
int re_hist(info_Pass *passInfo)
{
	list_String *n = passInfo->his_T;
	int ii = 0;

	while (n)
	{
		n->no = ii++;
		n = n->nx;
	}
	return (passInfo->his_C = ii);
}

/**
 * hist_f - hist_f
 * @passInfo: var
 * Return: char
 */

char *hist_f(info_Pass *passInfo)
{
	char *b, *d;

	d = _getevFunc(passInfo, "HOME=");
	if (!d)
		return (NULL);
	b = malloc(sizeof(char) * (_lengthstring(d) + _lengthstring(HISTORY_F) + 2));
	if (!b)
		return (NULL);
	b[0] = 0;
	_stringcopy(b, d);
	_stringcat(b, "/");
	_stringcat(b, HISTORY_F);
	return (b);
}
