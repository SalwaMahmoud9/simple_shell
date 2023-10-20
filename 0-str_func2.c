#include "shell.h"

/**
 **_string_concat2 - concatenates two strings
 *@str2: the first string
 *@str1: the second string
 *@n: the amount of bytes
 *Return: the concatenated string
 */
char *_string_concat2(char *str2, char *str1, int n)
{
	int i, j;
	char *str = str2;

	i = 0;
	j = 0;
	while (str2[i] != '\0')
		i++;
	while (str1[j] != '\0' && j < n)
	{
		str2[i] = str1[j];
		i++;
		j++;
	}
	if (j < n)
		str2[i] = '\0';
	return (str);
}

/**
 * _string_copy - copies a string
 * @str2: the str2
 * @str1: the str1
 *
 * Return: pointer to str2
 */
char *_string_copy(char *str2, char *str1)
{
	int i = 0;

	if (str2 == str1 || str1 == 0)
		return (str2);
	while (str1[i])
	{
		str2[i] = str1[i];
		i++;
	}
	str2[i] = 0;
	return (str2);
}

/**
 **_string_copy2 - copies a string
 *@str2: the str2 to be copied to
 *@str1: the str1
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_string_copy2(char *str2, char *str1, int n)
{
	int i, j;
	char *str = str2;

	i = 0;
	while (str1[i] != '\0' && i < n - 1)
	{
		str2[i] = str1[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			str2[j] = '\0';
			j++;
		}
	}
	return (str);
}

/**
 *_string_print - prints a string
 *@str: the string to be printed
 *
 * Return: No return
 */
void _string_print(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_string_print2(str[i]);
		i++;
	}
}

/**
 * _string_print2 - writes the string in stdout
 * @c: The string to write
 *
 * Return: 1
 */
int _string_print2(char c)
{
	static int i;
	static char buf[BUFF_W];

	if (c == BUFF_F || i >= BUFF_W)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUFF_F)
		buf[i++] = c;
	return (1);
}
