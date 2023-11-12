#include "shell.h"

/**
 * freeInfo - freeInfo
 * @passInfo: var
 * @a: var
 * Return: void
 */
void freeInfo(info_Pass *passInfo, int a)
{
	freePointer(passInfo->arg_V);
	passInfo->arg_V = NULL;
	passInfo->string_P = NULL;
	if (a)
	{
		if (!passInfo->cm_B)
			free(passInfo->arg_G);
		if (passInfo->env_L)
			free_mylist(&(passInfo->env_L));
		if (passInfo->his_T)
			free_mylist(&(passInfo->his_T));
		if (passInfo->al_AI)
			free_mylist(&(passInfo->al_AI));
		freePointer(passInfo->environ);
			passInfo->environ = NULL;
		bfree((void **)passInfo->cm_B);
		if (passInfo->fd_R > 2)
			close(passInfo->fd_R);
		_putchar(BUFFER_FLUSH);
	}
}

/**
 * setInfo - setInfo
 * @passInfo: var
 * @arV: var
 * Return: void
 */
void setInfo(info_Pass *passInfo, char **arV)
{
	int ii = 0;

	passInfo->name_F = arV[0];
	if (passInfo->arg_G)
	{
		passInfo->arg_V = stringToWord(passInfo->arg_G, " \t");
		if (!passInfo->arg_V)
		{

			passInfo->arg_V = malloc(sizeof(char *) * 2);
			if (passInfo->arg_V)
			{
				passInfo->arg_V[0] = _stringduplicate(passInfo->arg_G);
				passInfo->arg_V[1] = NULL;
			}
		}
		for (ii = 0; passInfo->arg_V && passInfo->arg_V[ii]; ii++)
			;
		passInfo->arg_C = ii;

		reAlias(passInfo);
		reVar(passInfo);
	}
}

/**
 * clearInfo - clearInfo
 * @passInfo: var
 * Return: void
 */
void clearInfo(info_Pass *passInfo)
{
	passInfo->arg_G = NULL;
	passInfo->arg_V = NULL;
	passInfo->string_P = NULL;
	passInfo->arg_C = 0;
}
