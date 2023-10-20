#include "shell.h"

/**
 *check_alpha - checks alphabetic character
 *@c: The character
 *Return: 0 if false and 1 if true
 */

int check_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * char_delim - checks if char is a delim
 * @c: char
 * @char2: delim
 * Return: 0 if false and 1 if true
 */
int char_delim(char c, char *char2)
{
	while (*char2)
		if (*char2++ == c)
			return (1);
	return (0);
}

/**
 * shell_status - check shell_status mode
 * @add: struct address
 *
 * Return: 1 , 0
 */
int shell_status(information_struct *add)
{
	return (isatty(STDIN_FILENO) && add->struct_f_r <= 2);
}

/**
 * str_to_int - converts string to integer
 * @str: string
 * Return: converted number
 */
int str_to_int(char *str)
{
	int i = 0;
	unsigned long int output = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			output *= 10;
			output += (str[i] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (output);
}


/**
 * remove_comments -remove comment
 * @var: string address
 *
 * Return: no return;
 */
void remove_comments(char *var)
{
	int i;

	for (i = 0; var[i] != '\0'; i++)
		if (var[i] == '#' && (!i || var[i - 1] == ' '))
		{
			var[i] = '\0';
			break;
		}
}
