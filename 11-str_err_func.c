#include "shell.h"

/**
 * put_file_desc - put file desc
 * @pc: print char
 * @filedesc: file desc
 * Return: 1/0
 */
int put_file_desc(char pc, int filedesc)
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
 * put_echar - put char
 * @pc: print char
 * Return: 0/1
 */
int put_echar(char pc)
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
 *print_file_desc - print file desc
 * @string: string
 * @filedesc: file desc
 * Return:No of char
 */
int print_file_desc(char *string, int filedesc)
{
	int i = 0;

	if (!string)
		return (i);
	while (*string)
	{
		i = i + put_file_desc(*string++, filedesc);
	}
	return (i);
}

/**
 *put_estring - put string
 * @string: string
 */
void put_estring(char *string)
{
	int ii = 0;

	if (!string)
		return;
	while (string[ii] != '\0')
	{
		put_echar(string[ii]);
		ii++;
	}
}
