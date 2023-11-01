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
int _myexit(info_Pass *);
int _mycd(info_Pass *);
int _myhelp(info_Pass *);
int _myhistory(info_Pass *);
int _myalias(info_Pass *);

/* myenv.c */
char *_getenv(info_Pass *, const char *);
int _myenv(info_Pass *);
int _mysetenv(info_Pass *);
int _myunsetenv(info_Pass *);
int populate_env_list(info_Pass *);
char **get_environ(info_Pass *);
int _unsetenv(info_Pass *, char *);
int _setenv(info_Pass *, char *, char *);

/* chain.c */
int is_chain(info_Pass *, char *, size_t *);
void check_chain(info_Pass *, char *, size_t *, size_t, size_t);
int replace_alias(info_Pass *);
int replace_vars(info_Pass *);
int replace_string(char **, char *);

/* listString.c */
list_String *add_node(list_String **, const char *, int);
list_String *add_node_end(list_String **, const char *, int);
size_t print_list_str(const list_String *);
int delete_node_at_index(list_String **, unsigned int);
void free_list(list_String **);
size_t list_len(const list_String *);
char **list_to_strings(list_String *);
size_t print_list(const list_String *);
list_String *node_starts_with(list_String *, char *, char);
ssize_t get_node_index(list_String *, list_String *);

/* genFunctions.c */
int interactive(info_Pass *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int _erratoi(char *);
void print_error(info_Pass *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* memoFunctions */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);

/* strFunctions.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **strtow(char *, char *);
char **strtow2(char *, char);

/* errorFunctions.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *st, int fd);

/* inOutputFunctions.c */
char *get_history_file(info_Pass *info);
int write_history(info_Pass *info);
int read_history(info_Pass *info);
int build_history_list(info_Pass *info, char *buf, int linecount);
int renumber_history(info_Pass *info);

/* pathFunctions.c */
int is_cmd(info_Pass *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_Pass *, char *, char *);

/* infoFunctions.c */
void clear_info(info_Pass *);
void set_info(info_Pass *, char **);
void free_info(info_Pass *, int);

/* hshFunctions.c */
int hsh(info_Pass *, char **);
int find_builtin(info_Pass *);
void find_cmd(info_Pass *);
void fork_cmd(info_Pass *);

/* getlineFunctions.c */
ssize_t get_input(info_Pass *);
int _getline(info_Pass *, char **, size_t *);
void sigintHandler(int);

#endif