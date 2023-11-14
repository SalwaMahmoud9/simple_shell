#include "shell.h"

/**
 * dupplicate_ch - dupplicate_ch
 * @stringPath: var
 * @x: var
 * @y: var
 * Return: char
 */
char *dupplicate_ch(char *stringPath, int x, int y)
{
	static char b[1024];
	int ii = 0, k = 0;

	for (k = 0, ii = x; ii < y; ii++)
		if (stringPath[ii] != ':')
			b[k++] = stringPath[ii];
	b[k] = 0;
	return (b);
}

/**
 * get_path - get_path
 * @passInfo: var
 * @stringPath: var
 * @cmd: var
 * Return: char
 */
char *get_path(info_Pass *passInfo, char *stringPath, char *cmd)
{
	int ii = 0, cp = 0;
	char *p;

	if (!stringPath)
		return (NULL);
	if ((_lengthstring(cmd) > 2) && st_wth(cmd, "./"))
	{
		if (cmmd_check(passInfo, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!stringPath[ii] || stringPath[ii] == ':')
		{
			p = dupplicate_ch(stringPath, cp, ii);
			if (!*p)
				_stringcat(p, cmd);
			else
			{
				_stringcat(p, "/");
				_stringcat(p, cmd);
			}
			if (cmmd_check(passInfo, p))
				return (p);
			if (!stringPath[ii])
				break;
			cp = ii;
		}
		ii++;
	}
	return (NULL);
}

/**
 * cmmd_check - cmmd_check
 * @passInfo: var
 * @p: var
 * Return: int
 */
int cmmd_check(info_Pass *passInfo, char *p)
{
	struct stat s;

	(void)passInfo;
	if (!p || stat(p, &s))
		return (0);

	if (s.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
