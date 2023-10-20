#include "shell.h"

/**
 * _put_file_desc - put file desc
 * @pc: print char
 * @filedesc: file desc
 * Return: 1/0
 */
int _put_file_desc(char pc, int filedesc)
{
	static char buffer[BUFF_W];
	static int i;

	if (i >= BUFF_W || pc == BUFF_F)
	{
		write(filedesc, buffer, i);
		i = 0;
	}
	if (pc != BUFF_F)
		buffer[i++] = pc;
	return (1);
}

/**
 * _put_echar - put char
 * @pc: print char
 * Return: 0/1
 */
int _put_echar(char pc)
{
	static char buffer[BUFF_W];
	static int i;

	if (pc == BUFF_F || i >= BUFF_W)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (pc != BUFF_F)
		buffer[i++] = pc;
	return (1);
}
/**
 *_print_file_desc - print file desc
 * @string: string
 * @filedesc: file desc
 * Return:No of char
 */
int _print_file_desc(char *string, int filedesc)
{
	int i = 0;

	if (!string)
		return (i);
	while (*string)
	{
		i = i + _put_file_desc(*string++, filedesc);
	}
	return (i);
}

/**
 *_put_estring - put string
 * @string: string
 */
void _put_estring(char *string)
{
	int ii = 0;

	if (!string)
		return;
	while (string[ii] != '\0')
	{
		_put_echar(string[ii]);
		ii++;
	}
}
