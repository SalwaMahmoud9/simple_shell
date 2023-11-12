#include "shell.h"

/**
 * set_buffer - set_buffer
 * @passInfo: var
 * @b: var
 * @l: var
 * Return: ssize_t
 */
ssize_t set_buffer(info_Pass *passInfo, char **b, size_t *l)
{
	size_t l_p = 0;
	ssize_t r = 0;

	if (!*l) 
	{
		free(*b);
		*b = NULL;
		signal(SIGINT, loginHdl);
#if GET_LINE
		x = getline(b, &l_p, stdin);
#else
		x = _getline(passInfo, b, &l_p);
#endif
		if (x > 0)
		{
			if ((*b)[x - 1] == '\n')
			{
				(*b)[x - 1] = '\0'; /* remove trailing newline */
				x--;
			}
			passInfo->flag_C = 1;
			del_comm(*b);
			add_hist(passInfo, *b, passInfo->his_C++);
			/* if (_strchr(*b, ';')) is this a command chain? */
			{
				*l = x;
				passInfo->cm_B = b;
			}
		}
	}
	return (x);
}

/**
 * get_it - get_it
 * @passInfo: var
 * Return: ssize_t
 */
ssize_t get_it(info_Pass *passInfo)
{
	static char *b;
	static size_t ii, j, l;
	ssize_t x = 0;
	char **buf_p = &(passInfo->arg_G), *p;

	_putchar(BUFFER_FLUSH);
	x = set_buffer(passInfo, &b, &l);
	if (x == -1)
		return (-1);
	if (l)
	{
		j = ii;
		p = b + ii;

		chChain(passInfo, b, &j, ii, l);
		while (j < l)
		{
			if (iChain(passInfo, b, &j))
				break;
			j++;
		}

		ii = j + 1; 
		if (ii >= l)
		{
			ii = l = 0;
			passInfo->cm_BT = COMMAND_N;
		}

		*buf_p = p;
		return (_lengthstring(p));
	}

	*buf_p = b;
	return (x);
}

/**
 * readb - readb
 * @passInfo: var
 * @b: var
 * @ii: var
 * Return: ssize_t
 */
ssize_t readb(info_Pass *passInfo, char *b, size_t *ii)
{
	ssize_t x = 0;

	if (*ii)
		return (0);
	r = read(passInfo->fd_R, b, R_BUFFER_S);
	if (r >= 0)
		*ii = r;
	return (r);
}

/**
 * _getline - _getline
 * @passInfo: var
 * @pr: var
 * @lth: var
 * Return: int
 */
int _getline(info_Pass *passInfo, char **pr, size_t *lth)
{
	static char b[R_BUFFER_S];
	size_t k;
	ssize_t r = 0, s = 0;
	static size_t ii, l;
	char *p = NULL, *new_p = NULL, *c;

	p = *pr;
	if (p && lth)
		s = *lth;
	if (ii == l)
		ii = l = 0;

	r = readb(passInfo, b, &l);
	if (r == -1 || (r == 0 && l == 0))
		return (-1);

	c = _strchr(b + ii, '\n');
	k = c ? 1 + (unsigned int)(c - b) : l;
	new_p = _relocation(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, b + ii, k - ii);
	else
		_stringcpy(new_p, b + ii, k - ii + 1);

	s += k - ii;
	ii = k;
	p = new_p;

	if (lth)
		*lth = s;
	*pr = p;
	return (s);
}

/**
 * loginHdl - loginHdl
 * @sn: var
 * Return: void
 */
void loginHdl(__attribute__((unused))int sn)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}
