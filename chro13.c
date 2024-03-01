#include "proshell.h"
/**
 * cj_cd_shell - changes current directory to a different directory
 * @dtsh: data
 * Return: 1 on success
 */
int cj_cd_shell(project_shell *dtsh)
{
	char *d;
	int x, y, z;

	d = dtsh->args[1];

	if (d != NULL)
	{
		x = cj_strcmp("$HOME", d);
		y = cj_strcmp("~", d);
		z = cj_strcmp("--", d);
	}

	/* second if loop */
	if (d == NULL || !x || !y || !z)
	{
		cj_cd_to_home(dtsh);
		return (1);
	}

	if (cj_strcmp("-", d) == 0)
	{
		cj_cd_previous(dtsh);
		return (1);
	}

	/* final if loop;arguments */
	if (cj_strcmp(".", d) == 0 || cj_strcmp("..", d) == 0)
	{
		cj_cd_dot(dtsh);
		return (1);
	}

	/* infomation arguments */
	cj_cd_dot(dtsh);

	return (1);
}

