#include "shell.h"

/**
 * print_err - prints an error
 * @var1: parameter
 * @var2: error type
 * Return: noReturn
 */
void print_err(information_struct *var1, char *var2)
{
	put_estring(var1->struct_f_name);
	put_estring(": ");
	print_dec(var1->struct_count, STDERR_FILENO);
	put_estring(": ");
	put_estring(var1->struct_argv[0]);
	put_estring(": ");
	put_estring(var2);
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
	int (*__putchar)(char) = string_print2;
	int i, count = 0;
	unsigned int _abs_, current;

	if (var2 == STDERR_FILENO)
		__putchar = put_echar;
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
