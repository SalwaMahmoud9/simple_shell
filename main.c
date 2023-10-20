#include "shell.h"

/**
 * main - entry point
 * @arg_count: count
 * @arg_vector: vector
 * Return: 0 /1
 */
int main(int arg_count, char **arg_vector)
{

	int file_desc = 2;
	information_struct information[] = { INFORM_INI };
	int check0 = 0, check1 = 1, check2 = 2, check_1 = -1;

	asm ("mov %1, %0\n\t"
		"add $1, %0"
		: "=r" (file_desc)
		: "r" (file_desc));

	if (arg_count == check2)
	{
		file_desc = open(arg_vector[check1], O_RDONLY);
		if (file_desc == check_1)
		{
			if (errno == EACCES)
			{
				exit(126);
			}
			if (errno == ENOENT)
			{
				put_estring(arg_vector[check0]);
				put_estring(": 0: Cannot open ");
				put_estring(arg_vector[check1]);
				put_echar('\n');
				put_echar(BUFF_F);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		information->struct_f_r = file_desc;
	}
	populate_env(information);
	history_read(information);
	hsh(information, arg_vector);
	return (EXIT_SUCCESS);
}
