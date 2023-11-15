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
	int x = 0, y = 1, z = 2, u = -1;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fileD)
		: "r" (fileD));

	if (c == z)
	{
		fileD = open(v[y], O_RDONLY);
		if (fileD == u)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_put(v[x]);
				_put(": 0: Can't open ");
				_put(v[y]);
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
