#include "proshell.h"
/**
 * cj_get_builtin - function of builtin
 * @cmd: command argss
 * Return: function pointer of the builtin command
 */
int (*cj_get_builtin(char *cmd))(project_shell *)
{
builtin_t builtin[] =
{
{ "env", cj_env },
{ "exit", cj_exit_shell },
{ "setenv", cj_setenv },
{ "unsetenv", cj_unsetenv },
{ "cd", cj_cd_shell },
{ "help", cj_get_help },
{ NULL, NULL }
};
int z;

for (z = 0; builtin[z].name; z++)
{
if (cj_strcmp(builtin[z].name, cmd) == 0)
break;
}

return (builtin[z].f);
}
