#include "shell.h"


/**
 * del_comm - del_comm
 * @buff: var
 * Return: void
 */
void del_comm(char *buff)
{
	int ii;

	for (ii = 0; buff[ii] != '\0'; ii++)
		if (buff[ii] == '#' && (!ii || buff[ii - 1] == ' '))
		{
			buff[ii] = '\0';
			break;
		}
}

/**
 * p_err - p_err
 * @passInfo: var
 * @ch: var
 * Return: void
 */
void p_err(info_Pass *passInfo, char *ch)
{
	_eputs(passInfo->name_F);
	_eputs(": ");
	print_var(passInfo->error_C, STDERR_FILENO);
	_eputs(": ");
	_eputs(passInfo->arg_V[0]);
	_eputs(": ");
	_eputs(ch);
}

/**
 * print_var - print_var
 * @in: var
 * @t: var
 * Return: int
 */
int print_var(int in, int t)
{
	int (*__putchar)(char) = _putchar;
	int ii, c = 0;
	unsigned int _abs_, curr;

	if (t == STDERR_FILENO)
		__putchar = _eputchar;
	if (in < 0)
	{
		_abs_ = -in;
		__putchar('-');
		c++;
	}
	else
		_abs_ = in;
	curr = _abs_;
	for (ii = 1000000000; ii > 1; ii /= 10)
	{
		if (_abs_ / ii)
		{
			__putchar('0' + curr / ii);
			c++;
		}
		curr %= ii;
	}
	__putchar('0' + curr);
	c++;

	return (c);
}

/**
 * _atoierror - _atoierror
 * @ch: var
 * Return: int
 */
int _atoierror(char *ch)
{
	unsigned long int res = 0;
	int ii = 0;
	
	if (*ch == '+')
		ch++;
	for (ii = 0;  ch[ii] != '\0'; ii++)
	{
		if (ch[ii] >= '0' && ch[ii] <= '9')
		{
			res *= 10;
			res += (ch[ii] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * change_num - change_num
 * @num: var
 * @b: var
 * @flg: var
 * Return: char
 */
char *change_num(long int num, int b, int flg)
{
	static char *arr;
	static char buf[50];
	char sgn = 0;
	char *pnr;
	unsigned long n = num;

	if (!(flg & CONV_UNSI) && num < 0)
	{
		n = -num;
		sgn = '-';
	}
	arr = flg & CONV_LOWC ? "0123456789abcdef" : "0123456789ABCDEF";
	pnr = &buf[49];
	*pnr = '\0';

	do	{
		*--pnr = arr[n % b];
		n /= b;
	} while (n != 0);

	if (sgn)
		*--pnr = sgn;
	return (pnr);
}
