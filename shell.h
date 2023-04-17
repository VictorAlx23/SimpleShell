#ifndef _SHELL_H
#define _SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers*/
#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1

/* for command chaining*/
#define CMD_NORM 	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for converts_num() */
#define CONVERT_LOWERCASE 	1
#define CONVERT_UNSIGNED 	2

/* 1 if using system getlines() */
#define USE_GETLINES 0
#define USE_STRTOK 0

#define HIST_FILE  "simple_shell_history"
#define HIST_MAX  4096

extern char **environs;

/**
 * struct liststrs - singly linked list
 * @nums: the number field
 * @strs: string
 * @next: pointer to the next node
 */
typedef struct liststrs
{
	int nums;
	char *strs;
	struct liststrs *next;
} list_t;

/**
 * struct pass_info - contains pseudo-arguments to pass into a function
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getlines containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: argument count
 * @line_count: the error count
 * @err_nums: error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: program filename
 * @envs: linked list local copy of environs
 * @environs: custom modified copy of environs from LL envs
 * @history: history node
 * @alias: alias node
 * @env_changed: on if environs was changed
 * @status: return status of the last exec'd command
 * @cmd_buff: address of pointer to cmd_buff, on if chaining
 * @cmd_buff_type: CMD_type ||, &&,;
 * @readfd: the fd from which to read line input
 * @histcount: the history line numer count
 */
typedef struct pass_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_nums;
	int linecount_flag;
	char *fname;
	list_t *envs;
	list_t *history;
	list_t *alias;
	char **environs;
	int env_changed;
	int status;
	char **cmd_buff;
	int cmd_buff_type;
	int histcount;
	int readfd;
} info_t;

#define INFO_INIT\
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}
/**
 * struct built_in - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct built_in
{
	char *type;
	int (*func)(info_t *);
} built_in_table;

/* toem_shloop.c */
int hsh(info_t *, char **);
int find_built_in(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/*toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* toem_error.c */
void _eputs(char *);
int _eputchar(char *);
int _putsfd(char *strs, int fd);
int _putfd(char c, int fd);

/* loophsh.c */
int loophsh(char **);

/*toem_exit.c */
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);

/* toem_strings.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *strcat(char *, char *);

/* toem_strings1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_reallocs.c */
char *_mamset(char *, char, unsigned int);
void ffree(char **);
void *_reallocs(void *, unsigned int, unsigned int);

/* toem_getenvs.c */
char **get_env(info_t*);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);


/*toem_historys.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buff, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *addnode(list_t **, const char *, int);
list_t *addnodeend(list_t **, const char *, int);
size_t printlist_str(const list_t *h1);
int delete_node_at_index(list_t **head, unsigned int ind);
void freelist(list_t **headptr);

/* toem_lists1.c */
size_t list_size(const list_t *);
char **list_to_string(list_t *);
size_t prints_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/*toem_vars.c */
int is_chains(info_t *, char *, size_t *);
void check_chains(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_strings(char **, char *);

/* toem_memory.c */
int bfree(void **);

/* toem_astoi.c */
int interact(info_t *);
int is_delimt(char, char *);
int is_alpha(int);
int _astoi(char *);

/* toem_error1.c */
int _errastoi(char *);
void prints_error(info_t *, char *);
int print_deci(int, int);
char *converts_num(long int, int, int);
void remove_comments(char *);

/* toem_built_in.c */
int _shellexit(info_t *);
int _shellcd(info_t *);
int _shellhelp(info_t *);

/*toem_built_in1.c */
int _shellhistory(info_t *);
int _shellalias(info_t *);

/* toem_getlines.c */
ssize_t gets_input(info_t *);
int _getlines(info_t *, char **, size_t *);
void siginHandler(int);

/* _getinfo.c */
void clears_info(info_t *);
void sets_info(info_t *, char **);
void free_info(info_t *, int);

/* toem_environ.c */
char *_getenvs(info_t *, const char *);
int _shellenv(info_t *);
int _shsetenv(info_t *);
int _shunsetenv(info_t *);
int populate_env_list(info_t *);

#endif
