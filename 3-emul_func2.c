#include "shell.h"

/**
 * _show_history - display history
 * @information: input variable
 *  Return: 0
 */

int _show_history(information_struct *information)
{
	linklist_print(information->struct_his);
	return (0);
}

/**
 * _shell_exit - exit shell
 * @information: input variable
 * Return: 1/-2
 */

int _shell_exit(information_struct *information)
{
	int checkout;

	if (information->struct_argv[1])
	{
		checkout = _str_to_int(information->struct_argv[1]);

		if (checkout == -1)
		{
			information->struct_status = 2;
			print_err(information, "Invalid No: ");
			_put_estring(information->struct_argv[1]);
			_put_echar('\n');
			return (1);
		}
		information->struct_num = _str_to_int(information->struct_argv[1]);
		return (-2);
	}
	else
	{
		information->struct_num = -1;
		return (-2);
	}
}
