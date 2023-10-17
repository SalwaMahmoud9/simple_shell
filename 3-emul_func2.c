#include "shell.h"

/**
 * show_history - display history
 * @information: input variable
 *  Return: 0
 */

int show_history(information_struct *information)
{
	linklist_print(information->struct_his);
	return (0);
}

/**
 * shell_exit - exit shell
 * @information: input variable
 * Return: 1/-2
 */

int shell_exit(information_struct *information)
{
	int checkout;

	if (information->struct_argv[1])
	{
		checkout = str_to_int(information->struct_argv[1]);

		if (checkout != -1)
		{
			information->struct_num = str_to_int(information->struct_argv[1]);
			return (-2);
		}
		else
		{
			information->struct_status = 2;
			print_err(information, "Invalid No: ");
			put_estring(information->struct_argv[1]);
			put_echar('\n');
			return (1);
		}
	}
	else
	{
		information->struct_num = -1;
		return (-2);
	}
}
