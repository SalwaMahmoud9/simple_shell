#include "shell.h"

/**
 * active - active
 * @infoPass: var
 * Return: int
 */
int active(info_Pass *infoPass)
{
	return (isatty(STDIN_FILENO) && infoPass->fd_R <= 2);
}

/**
 * check_del - check_del
 * @ch: var
 * @del: var
 * Return: int
 */
int check_del(char ch, char *del)
{
	while (*del)
		if (*del++ == ch)
			return (1);
	return (0);
}

/**
 *_atoi - _atoi
 *@ch: var
 *Return: int
 */
int _atoi(char *ch)
{
	unsigned int res = 0;
	int ii, sn = 1, fg = 0, op;

	for (ii = 0;  ch[ii] != '\0' && fg != 2; ii++)
	{
		if (ch[ii] == '-')
			sn *= -1;

		if (ch[ii] >= '0' && ch[ii] <= '9')
		{
			fg = 1;
			res *= 10;
			res += (ch[ii] - '0');
		}
		else if (fg == 1)
			fg = 2;
	}

	if (sn == -1)
		op = -res;
	else
		op = res;

	return (op);
}

/**
 *_alpha - _alpha
 *@ch: var
 *Return: var
 */

int _alpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}
