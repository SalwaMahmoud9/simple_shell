#include "shell.h"

/**
 **string_locate - locates a character in a string
 *@str: the string
 *@c: the character
 *Return: a pointer or NULL
 */
char *string_locate(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

/**
 * **string_split - splits a string into words
 * @str: the input string
 * @d: the character
 * Return: a pointer to an array of strings, or NULL
 */

char **string_split(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **ch;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!char_delim(str[i], d) && (char_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;
	if (numwords == 0)
		return (NULL);
	ch = malloc((1 + numwords) * sizeof(char *));
	if (!ch)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (char_delim(str[i], d))
			i++;
		k = 0;
		while (!char_delim(str[i + k], d) && str[i + k])
			k++;
		ch[j] = malloc((k + 1) * sizeof(char));
		if (!ch[j])
		{
			for (k = 0; k < j; k++)
				free(ch[k]);
			free(ch);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			ch[j][m] = str[i++];
		ch[j][m] = 0;
	}
	ch[j] = NULL;
	return (ch);
}

/**
 * **string_split2 - splits a string into words
 * @str: the input string
 * @d: the character
 * Return: a pointer to an array of strings, or NULL
 */
char **string_split2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **ch;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	ch = malloc((1 + numwords) * sizeof(char *));
	if (!ch)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		ch[j] = malloc((k + 1) * sizeof(char));
		if (!ch[j])
		{
			for (k = 0; k < j; k++)
				free(ch[k]);
			free(ch);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			ch[j][m] = str[i++];
		ch[j][m] = 0;
	}
	ch[j] = NULL;
	return (ch);
}
