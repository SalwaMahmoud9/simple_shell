#include "shell.h"

/**
 * print_err - prints an error
 * @var1: parameter
 * @var2: error type
 * Return: noReturn
 */
void print_err(information_struct *var1, char *var2)
{
	_put_estring(var1->struct_f_name);
	_put_estring(": ");
	print_dec(var1->struct_count, STDERR_FILENO);
	_put_estring(": ");
	_put_estring(var1->struct_argv[0]);
	_put_estring(": ");
	_put_estring(var2);
}

/**
 * print_dec - print decimal
 * @var1: input
 * @var2: file descriptor
 *
 * Return: number of char
 */
int print_dec(int var1, int var2)
{
	int (*__putchar)(char) = _string_print2;
	int i, count = 0;
	unsigned int _abs_, current;

	if (var2 == STDERR_FILENO)
		__putchar = _put_echar;
	if (var1 < 0)
	{
		_abs_ = -var1;
		__putchar('-');
		count++;
	}
	else
		_abs_ = var1;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_no - converter
 * @var2: argument var2
  * @num: number
 * @var1: var1
 *
 * Return: string
 */
char *convert_no(long int num, int var1, int var2)
{
	static char *arr;
	static char buff[50];
	char var3 = 0;
	char *var4;
	unsigned long n = num;

	if (!(var2 & CONV_UN) && num < 0)
	{
		n = -num;
		var3 = '-';

	}
	arr = var2 & CONV_LW ? "0123456789abcdef" : "0123456789ABCDEF";
	var4 = &buff[49];
	*var4 = '\0';

	do	{
		*--var4 = arr[n % var1];
		n /= var1;
	} while (n != 0);

	if (var3)
		*--var4 = var3;
	return (var4);
}

/**
 *_atoi -string to integer
 *@str: string
 *Return: 0/1
 */

int _atoi(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
