#include "shell.h"

/**
 * buffer_read - read buffer
 * @information: input variable
 * @buffer: buffer
 * @i: size
 * Return: size
 */
ssize_t buffer_read(information_struct *information, char *buffer, size_t *i)
{
	ssize_t size_rr = 0;

	if (*i)
		return (0);
	size_rr = read(information->struct_f_r, buffer, BUFF_R);
	if (size_rr >= 0)
		*i = size_rr;
	return (size_rr);
}

/**
 * buffer_input - buffer input
 * @information: input variable
 * @buffer: buffer address
 * @length: length
 * Return: bytes
 */
ssize_t buffer_input(information_struct *information, char **buffer, size_t *length)
{

	size_t length_pt = 0;
	ssize_t size_rr = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handler_int);
#if G_L
		size_rr = getline(buffer, &length_pt, stdin);
#else
		size_rr = line_get(information, buffer, &length_pt);
#endif
		if (size_rr > 0)
		{
			if ((*buffer)[size_rr - 1] == '\n')
			{
				(*buffer)[size_rr - 1] = '\0';
				size_rr--;
			}
			information->struct_count_f = 1;
			remove_comments(*buffer);
			history_build(information, *buffer, information->struct_hist_c++);
			{
				*length = size_rr;
				information->struct_buff = buffer;
			}
		}
	}
	return (size_rr);
}

/**
 * input_get - get input
 * @information: input variable
 * Return: bytes
 */
ssize_t input_get(information_struct *information)
{
	static char *buffer;
	ssize_t size_rr = 0;
	char **buffer_pt = &(information->struct_arg);
	char *pr;
	static size_t i;
	static size_t j;
	static size_t length;

	string_print2(BUFF_F);
	size_rr = buffer_input(information, &buffer, &length);
	if (size_rr == -1)
		return (size_rr);
	if (length)
	{
		j = i;
		pr = buffer + i;

		chain_check(information, buffer, &j, i, length);
		while (j <= length - 1)
		{
			if (chain_status(information, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= length)
		{
			length = 0;
			i = 0;
			information->struct_buff_t = COM_N;
		}

		*buffer_pt = pr;
		return (string_length(pr));
	}

	*buffer_pt = buffer;
	return (size_rr);
}

/**
 * line_get - get line
 * @information: input variable
 * @ptr: address
 * @length: length
 * Return: s
 */
int line_get(information_struct *information, char **ptr, size_t *length)
{
	ssize_t s = 0;
	size_t k;
	ssize_t size_rr = 0;
	char *pr = NULL;
	char *new_pr = NULL;
	char *c;
	static size_t i;
	static size_t length1;
	static char buffer[BUFF_R];

	pr = *ptr;
	if (length && pr)
		s = *length;
	if (length1 == i)
	{
		i = 0;
		length1 = 0;
	}
	size_rr = buffer_read(information, buffer, &length1);
	if (size_rr == -1 || (size_rr == 0 && length1 == 0))
		return (-1);

	c = string_locate(buffer + i, '\n');
	if (c)
		k = 1 + (unsigned int)(c - buffer);
	else
		k = length1;

	new_pr = memory_loc(pr, s, s ? s + k : k + 1);
	if (!new_pr)
		return (pr ? free(pr), -1 : -1);
	if (!s)
		string_copy2(new_pr, buffer + i, k - i + 1);

	else
		string_concat2(new_pr, buffer + i, k - i);

	s += (k - i);
	i = k;
	pr = new_pr;

	if (length)
		*length = s;
	*ptr = pr;
	return (s);
}

/**
 * handler_int -  handle int
 * @sig_num: signal No.
 */
void handler_int(__attribute__((unused))int sig_num)
{
	string_print("\n");
	string_print("$ ");
	string_print2(BUFF_F);
}
