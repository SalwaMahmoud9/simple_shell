#include "shell.h"

/**
 * begin_with - checks if substring in string
 * @str: the string to search
 * @subStr: the substring to find
 *
 * Return: address of substing in string or NULL
 */
char *begin_with(const char *str, const char *subStr)
{
	while (*subStr)
		if (*subStr++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * string_length - length of a string
 * @str: the string
 *
 * Return: length of string
 */
int string_length(char *str)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str++)
		i++;
	return (i);
}

/**
 * string_compare - comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: -1 if str1 < str2, 1 if str1 > str2, 0 if str1 == str2
 */
int string_compare(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * string_duplicate - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *string_duplicate(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * string_concat - concatenates two strings
 * @str2: the buffer2
 * @str1: the buffer1
 *
 * Return: pointer to str2 buffer
 */
char *string_concat(char *str2, char *str1)
{
	char *ret = str2;

	while (*str2)
		str2++;
	while (*str1)
		*str2++ = *str1++;
	*str2 = *str1;
	return (ret);
}
