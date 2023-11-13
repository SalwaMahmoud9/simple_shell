#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>



#define GET_LINE 0
#define STRING_TOKE 0
#define BUFFER_FLUSH -1
#define CONV_LOWC	1
#define CONV_UNSI	2
#define COMMAND_N	0
#define COMMAND_O		1
#define COMMAND_A		2
#define COMMAND_CH	3
#define HISTORY_F	".shell_history"
#define R_BUFFER_S 1024
#define W_BUFFER_S 1024
#define HISTORY_M	4096


extern char **environ;


/**
 * struct listString - listString
 * @no: variable
 * @st: variable
 * @nx: variable
 */
typedef struct listString
{
	int no;
	char *st;
	struct listString *nx;
} list_String;

/**
 *struct infoPass - Info Pass
 *@arg_G: variable
 *@arg_V: variable
 *@string_P: variable
 *@arg_C: variable
 *@error_C: variable
 *@error_N: variable
 *@flag_C: variable
 *@name_F: variable
 *@env_L: variable
 *@environ: variable
 *@his_T: variable
 *@al_AI: variable
 *@env_C: variable
 *@sta_S: variable
 *@cm_B: variable
 *@cm_BT: variable
 *@fd_R: variable
 *@his_C: variable
 */
typedef struct infoPass
{
	char *arg_G;
	char **arg_V;
	char *string_P;
	int arg_C;
	unsigned int error_C;
	int error_N;
	int flag_C;
	char *name_F;
	list_String *env_L;
	list_String *his_T;
	list_String *al_AI;
	char **environ;
	int env_C;
	int sta_S;
	char **cm_B;
	int cm_BT;
	int fd_R;
	int his_C;
} info_Pass;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtinString - builtinString
 *@strType: variable
 *@f: variable
 */
typedef struct builtinString
{
	char *strType;
	int (*f)(info_Pass *);
} builtin_String;

/* emulator.c */
int _aliasFunc(info_Pass *);
int _changeDirFunc(info_Pass *);
int _exitFunc(info_Pass *);
int _helpFunc(info_Pass *);
int _historyFunc(info_Pass *);



/* myenv.c */
int popenvFunc(info_Pass *);
int _envFunc(info_Pass *);
int _stevFunc(info_Pass *);
int _unenvFunc(info_Pass *, char *);
int _stenvFunc(info_Pass *, char *, char *);
int _ustevFunc(info_Pass *);
char *_getevFunc(info_Pass *, const char *);
char **getenvFunc(info_Pass *);

/* chain.c */
void chChain(info_Pass *, char *, size_t *, size_t, size_t);
int reVar(info_Pass *);
int reStr(char **, char *);
int reAlias(info_Pass *);
int iChain(info_Pass *, char *, size_t *);


/* listString.c */
size_t getListLength(const list_String *);
size_t p_list(const list_String *);
size_t p_list_string(const list_String *);
char **list_strs(list_String *);
ssize_t node_index(list_String *, list_String *);
int d_node_i(list_String **, unsigned int);
void free_mylist(list_String **);
list_String *plus_e_node(list_String **, const char *, int);
list_String *plus_node(list_String **, const char *, int);
list_String *start_node(list_String *, char *, char);

/* genFunctions.c */
int active(info_Pass *);
int check_del(char, char *);
int _alpha(int);
int _atoi(char *);
int _atoierror(char *);
int print_var(int, int);
void p_err(info_Pass *, char *);
void del_comm(char *);
char *change_num(long int, int, int);


/* memoFunctions */
void *_relocation(void *, unsigned int, unsigned int);
void freePointer(char **);
char *_setmemory(char *, char, unsigned int);
int bfree(void **);


/* strFunctions.c */
int _lengthstring(char *);
int _comparestring(char *, char *);
int _putchar(char);
char *_stringcopy(char *, char *);
char *_stringduplicate(const char *);
char *st_wth(const char *, const char *);
char *_stringcat(char *, char *);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **stringToWord(char *, char *);
char **stringToWordCh(char *, char);
char *_stringcpy(char *, char *, int);
void _puts(char *);


/* errorFunctions.c */
int _putFD(char *st, int fd);
int _putF(char c, int fd);
int _putC(char);
void _put(char *);

/* inOutputFunctions.c */
int add_hist(info_Pass *info, char *buf, int linecount);
int hist_w(info_Pass *info);
int hist_r(info_Pass *info);
int re_hist(info_Pass *info);
char *hist_f(info_Pass *info);

/* pathFunctions.c */
char *dupplicate_ch(char *, int, int);
char *get_path(info_Pass *, char *, char *);
int cmmd_check(info_Pass *, char *);

/* infoFunctions.c */
void setInfo(info_Pass *, char **);
void freeInfo(info_Pass *, int);
void clearInfo(info_Pass *);

/* hshFunctions.c */
void get_cmd(info_Pass *);
void get_fork_cmd(info_Pass *);
int get_build_in(info_Pass *);
int hsh(info_Pass *, char **);

/* getlineFunctions.c */
ssize_t get_it(info_Pass *);
void loginHdl(int);
int _getline(info_Pass *, char **, size_t *);

#endif
