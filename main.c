#include "shell.h"

/**
 * main - main entry point
 * @c: count
 * @v: vector
 * Return: int
 */
int main(int c, char **v)
{
	int fileD = 2;
	info_Pass info[] = { INFO_INIT };

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fileD)
		: "r" (fileD));

	if (c == 2)
	{
		fileD = open(v[1], O_RDONLY);
		if (fileD == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_put(v[0]);
				_put(": 0: Can't open ");
				_put(v[1]);
				_putC('\n');
				_putC(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->fd_R = fileD;
	}
	popenvFunc(info);
	hist_r(info);
	hsh(info, v);
	return (EXIT_SUCCESS);
}
