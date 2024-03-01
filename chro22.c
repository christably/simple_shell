#include "proshell.h"
/**
 * cj_get_help - function that retrieves help messages
 * @dtsh: data structure
 * Return: Return 0
*/
int cj_get_help(project_shell *dtsh)
{

	if (dtsh->args[1] == 0)
		ax_help_general();
	else if (cj_strcmp(dtsh->args[1], "setenv") == 0)
		ax_help_setenv();
	else if (cj_strcmp(dtsh->args[1], "env") == 0)
		ax_help_env();
	else if (cj_strcmp(dtsh->args[1], "unsetenv") == 0)
		ax_help_unsetenv();
	else if (cj_strcmp(dtsh->args[1], "help") == 0)
		ax_help();
	else if (cj_strcmp(dtsh->args[1], "exit") == 0)
		ax_help_exit();
	else if (cj_strcmp(dtsh->args[1], "cd") == 0)
		ax_help_cd();
	else if (cj_strcmp(dtsh->args[1], "alias") == 0)
		ax_help_alias();
	else
		write(STDERR_FILENO, dtsh->args[0],
		      cj_strlen(dtsh->args[0]));

	dtsh->status = 0;
	return (1);
}
