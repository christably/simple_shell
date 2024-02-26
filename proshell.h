#ifndef _PROSHELL_H_
#define _PROSHELL_H_
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"
#define TRUE 1
#define PROMPT "Proshell $ "
#define ERR_MALLOC "Unable to allocate memory\n"
#define ERR_FORK "Unable to fork and create chris process\n"
#define ERR_PATH "No such file or directory\n"

/* Points to an array of pointers to strings called the "environment" */
extern char **env;

/**
 * struct prosellee - struct containing all data
 ** @count: lines count
 ** @ar: argument vector
 ** @pid: process ID
 ** @env: env var
 ** @args: tokens
 ** @status: shell status
 ** @log: command line
 **/
typedef struct prosey
{
  int count;
  char **ar;
  char **args;
  char *pid;
  int status;
  char *log;
  char **_env;
} pro;

/**
 * struct sls - single linked list
 ** @sep: ; | &
 ** @nxt: next node
 ** Description: single linked list to store separators
 **/
typedef struct sls
{
	char sep;
	struct sls *nxt;
} sl;

/**
 * struct lls - single linked list
 * @l: command line
 * @nxt: nxt node
 * Description: single linked list to store command lines
 */
typedef struct lls
{
	char *l;
	struct lls *nxt;
} ln;

/**
 * struct rvl - single linked list
 ** @lvr: length of variable
 ** @val: value of variable
 ** @lvl: length of value
 ** @nxt: next node
 ** Description: linked list for variable storage
 **/
typedef struct rvl
{
	int lvr;
	char *val;
	int lvl;
	struct rvl *nxt;
} rv;
/**
 * struct buil - Builtin struct for command args.
 * @nm: name of command built i.e cd, exit, env
 * @g: data type pointer function.
 */
typedef struct buil
{
	char *nm;
	int (*g)(pro *d);
} built;

/* alists.c */
sl *asne(sl **h, char sep);
void fsl(sl **h);
ln *alne(ln **h, char *l);
void fll(ln **h);

/* alists2.c */
rv *arvn(rv **h, int lvr, char *vr, int lvl);
void frl(rv **h);

/* astr func */
char *christycat(char *d, const char *s);
char *christycpy(char *d, char *s);
int christycmp(char *s1, char *s2);
char *christychr(char *s, char c);
int christyspn(char *s, char *a);

/* amem.c */
void shellcpy(void *n, const void *p, unsigned int s);
void *shelloc(void *p, unsigned int os, unsigned int ns);
char **shellocdp(char **p, unsigned int os, unsigned int ns);

/* astr2.c */
char *christydup(const char *s);
int christylen(const char *s);
int chirstychars(char s[], const char *d);
char *christytok(char s[], const char *d);
int christigit(const char *s);

/* astr3.c */
void christystring(char *s);

/* cse.c */
int rchar(char *log, int i);
int eso(char *log, int i, char l);
int fch(char *log, int *i);
void pse(pro *d, char *log, int i, int bl);
int cse(pro *d, char *log);

/* slll.c */
char *wc(char *in);
void slll(pro *d);

/* rline.c */
char *rline(int *f);

/* sp.c */
char *spchar(char *log, int bl);
void an(sl **h1, ln **h2, char *log);
void gnxt(sl **ls, ln **ll, pro *d);
int sc(pro *d, char *log);
char **sp(char *log);

/* rvv.c */
void cenv(rv **h, char *in, pro *d);
int cvars(rv **h, char *in, char *st, pro *d);
char *rlogg(rv **h, char *log, char *nt, int nn);
char *rva(char *log, pro *d);

/* gline.c */
void bl(char **lr, size_t *n, char *b, size_t j);
ssize_t gline(char **lptr, size_t *n, FILE *sm);

/* eline */
int eline(pro *d);

/* cexec.c */
int idir(char *ph, int *i);
char *wh(char *cd, char **env);
int iexec(pro *dsh);
int cecmd(char *dr, pro *d);
int cexec(pro *d);

/* enva.c */
char *gv(const char *nm, char **env);
int envi(pro *d);

/* envb.c */
char *cinfo(char *n, char *val);
void senv(char *n, char *val, pro *d);
int stenv(pro *d);
int setenvv(pro *d);

/* cd.c */
void cddt(pro *d);
void cdto(pro *d);
void cdps(pro *d);
void cdth(pro *d);

/* cd_shell.c */
int cds(pro *d);

/* gbuil.c */
int (*gbuilt(char *c))(pro *d);

/* _ex.c */
int eshell(pro *d);

/* astdlib.c */
int gleen(int n);
char *aitoa(int n);
int atoii(char *s);

/* aerror1.c */
char *sscd(pro *, char *, char *, char *);
char *egd(pro *d);
char *enf(pro *d);
char *eesh(pro *d);

/* aerror2.c */
char *egalias(char **args);
char *eenv(pro *d);
char *eyntax(char **args);
char *eperm(char **args);
char *ep126(pro *d);

/* grror.c */
int gerror(pro *d, int ev);

/* gsigint.c */
void gsigint(int sig);

/* ahelp.c */
void myhp_env(void);
void myhp_setenv(void);
void myhp_unsetenv(void);
void myhp_gen(void);
void myhp_exit(void);

/* ahelp2.c */
void myhp(void);
void myhp_sis(void);
void myhp_cd(void);

/* ghelp.c */
int ghelp(pro *d);

#endif
