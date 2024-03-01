#include "proshell.h"
/**
 * cj_strcat_cd - function that concatenates the msg for cd error
 * @dtsh: data relevant (directory)
 * @msg: message to print
 * @e: output message
 * @v_s: counter lines
 * Return: error message
 ****************************************************************/
char *cj_strcat_cd(project_shell *dtsh, char *msg, char *e, char *v_s)
{
char *bad_flag;

cj_strcpy(e, dtsh->av[0]);
cj_strcat(e, ": ");
cj_strcat(e, v_s);
cj_strcat(e, ": ");
cj_strcat(e, dtsh->args[0]);
cj_strcat(e, msg);
if (dtsh->args[1][0] == '-')
{
bad_flag = malloc(3);
bad_flag[0] = '-';
bad_flag[1] = dtsh->args[1][1];
bad_flag[2] = '\0';
cj_strcat(e, bad_flag);
free(bad_flag);
}
else
{
cj_strcat(e, dtsh->args[1]);
}

cj_strcat(e, "\n");
cj_strcat(e, "\0");
return (e);
}
/**
 * e_get_cd - error message for cd command in get_cd
 * @dtsh: data
 * Return: Error message
 **/
char *e_get_cd(project_shell *dtsh)
{
int lth, lth_id;
char *e, *v_s, *msg;

v_s = cj_itoa(dtsh->counter);
if (dtsh->args[1][0] == '-')
{
msg = ": Bad option ";
lth_id = 2;
}
else
{
msg = ": cannot cd to ";
lth_id = cj_strlen(dtsh->args[1]);
}

lth = cj_strlen(dtsh->av[0]) + cj_strlen(dtsh->args[0]);
lth += cj_strlen(v_s) + cj_strlen(msg) + lth_id + 5;
e = malloc(sizeof(char) * (lth + 1));

if (e == 0)
{
free(v_s);
return (NULL);
}

e = cj_strcat_cd(dtsh, msg, e, v_s);

free(v_s);

return (e);
}
/**
 * e_not_f - function that generates error message for command not found
 * @dtsh: data
 * Return: Error message
 */
char *e_not_f(project_shell *dtsh)
{
int lth;
char *e;
char *v_s;

v_s = cj_itoa(dtsh->counter);
lth = cj_strlen(dtsh->av[0]) + cj_strlen(v_s);
lth += cj_strlen(dtsh->args[0]) + 16;
e = malloc(sizeof(char) * (lth + 1));
if (e == 0)
{
free(e);
free(v_s);
return (NULL);
}
cj_strcpy(e, dtsh->av[0]);
cj_strcat(e, ": ");
cj_strcat(e, v_s);
cj_strcat(e, ": ");
cj_strcat(e, dtsh->args[0]);
cj_strcat(e, ": not found\n");
cj_strcat(e, "\0");
free(v_s);
return (e);
}
/**
 * e_exit_s - function that generstes error messages for exit in get_exit
 * @dtsh: data
 * Return: Error message
 **/
char *e_exit_s(project_shell *dtsh)
{
int length;
char *erros;
char *v_s;

v_s = cj_itoa(dtsh->counter);
length = cj_strlen(dtsh->av[0]) + cj_strlen(v_s);
length += cj_strlen(dtsh->args[0]) + cj_strlen(dtsh->args[1]) + 23;
erros = malloc(sizeof(char) * (length + 1));
if (erros == 0)
{
free(v_s);
return (NULL);
}
cj_strcpy(erros, dtsh->av[0]);
cj_strcat(erros, ": ");
cj_strcat(erros, v_s);
cj_strcat(erros, ": ");
cj_strcat(erros, dtsh->args[0]);
cj_strcat(erros, ": Dangerous number: ");
cj_strcat(erros, dtsh->args[1]);
cj_strcat(erros, "\n\0");
free(v_s);

return (erros);
}
