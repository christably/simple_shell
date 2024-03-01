#ifndef _PROSHELL_H_
#define _PROSHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;

/**
 * struct data - struct function that contains all data.
 * @av: the argument vector for functio
 * @input: the command line written by user
 * @args: the argument token of the command line
 * @status: shell last status
 * @counter: function to count lines
 * @_environ: the environment variable passed
 * @pid: the shell process identification
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} project_shell;

/**
 * struct sep_list_s - function for asingle linked list
 * @separator: ; | &
 * @next: next node
 * Description: the single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - struct function for single linked list
 * @line: the command line
 * @next: the next node for function
 * Description: a single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - function single linked list
 * @len_var: length of variable
 * @val: variable value
 * @len_val: value length
 * @next: next node
 * Description: a single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - struct builtin struct for command arguments.
 * @name: Command builtin names such as  i.e cd, exit, env
 * @f: data pointer function type
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(project_shell *dtsh);
} builtin_t;

char *cj_strcat_cd(project_shell *dtsh, char *msg, char *error, char *ver_s);
char *e_get_cd(project_shell *dtsh);
char *e_not_f(project_shell *dtsh);
char *e_exit_s(project_shell *dtsh);
char *cj_strdup(const char *s);
/* myhelper functions */
int cj_strlen(const char *s);
int compare_chars(char string[], const char *delim);
char *cj_strtok(char string[], const char *delim);
int cj_isdigit(const char *s);
void cj_rev_string(char *s);
/*function to navigate directory */
void cj_cd_dot(project_shell *dtsh);
void cj_cd_to(project_shell *dtsh);
void cj_cd_previous(project_shell *dtsh);
void cj_cd_to_home(project_shell *dtsh);
int cj_cd_shell(project_shell *dtsh);
int repeat_chars(char *input, int z);
int cj_e_s_p(char *input, int z, char lt);
int cj_first_char(char *input, int *z);
/*functions */
void p_x_e(project_shell *dtsh, char *input, int z, int bool);
int c_x_e(project_shell *dtsh, char *input);
int cj_exec_line(project_shell *dtsh);
int cj_exit_shell(project_shell *dtsh);
int (*cj_get_builtin(char *cmd))(project_shell *);
int cj_get_error(project_shell *dtsh, int ueval);
int cj_get_help(project_shell *dtsh);
void cj_bring_line(char **lptr, size_t *i, char *buffer, size_t k);
ssize_t cj_get_line(char **lptr, size_t *i, FILE *stream);
/* my function;argumentations */
void cj_get_sigint(int sig);
char *cj_read_line(int *iff);
char *cj_without_comment(char *in);
void christy_s_loop(project_shell *dsh);
char *cj_swap_char(char *input, int bool);
void cj_add_nodes(sep_list **hs, line_list **hl, char *input);
void cj_go_next(sep_list **l_s, line_list **l_l, project_shell *dtsh);
int cj_split_commands(project_shell *dtsh, char *input);
char **cj_split_line(char *input);
void ax_help_env(void);
/* more helper functions */
void ax_help_setenv(void);
void ax_help_unsetenv(void);
void ax_help_general(void);
void ax_help_exit(void);
void ax_help(void);
void ax_help_alias(void);
void ax_help_cd(void);
sep_list *cj_add_sep_node_end(sep_list **head, char sep);
void cj_free_sep_list(sep_list **head);
line_list *cj_add_line_node_end(line_list **head, char *line);
void cj_free_line_list(line_list **head);
/* node functions */
r_var *cj_add_rvar_node(r_var **head, int lvar, char *val, int lval);
void cj_free_rvar_list(r_var **head);
void cj_memcpy(void *newptr, const void *ptr, unsigned int size);
void *cj_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **cj_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);
int cj_get_len(int n);
char *cj_itoa(int n);
int cj_atoi(char *s);
char *cj_strcat(char *dest, const char *src);
char *cj_strcpy(char *dest, char *src);
int cj_strcmp(char *s1, char *s2);
/* functions more */
char *cj_strchr(char *s, char c);
int cj_strspn(char *s, char *accept);
void cj_check_env(r_var **h, char *in, project_shell *data);
int cj_check_vars(r_var **h, char *in, char *st, project_shell *data);
char *replace_inputs(r_var **head, char *input, char *new_input, int nlen);
char *rep_vari(char *input, project_shell *dtsh);
char *cj_copy_info(char *name, char *value);
void cj_set_env(char *name, char *value, project_shell *dtsh);
int cj_setenv(project_shell *dtsh);
int cj_unsetenv(project_shell *dtsh);
int cj_cmp_env_name(const char *nenv, const char *name);
char *cj_getenv(const char *name, char **_environ);
int cj_env(project_shell *dtsh);
int cj_is_cdir(char *path, int *n);
char *cj_which(char *cmd, char **_environ);
int cj_is_executable(project_shell *dtsh);
int cj_check_error_cmd(char *d, project_shell *dtsh);
/* other helper functions */
int cj_cmd_exec(project_shell *dtsh);
char *e_env(project_shell *dtsh);
char *e_path_126(project_shell *dtsh);

#endif
