#include "proshell.h"

/**
 * ghelp - function that retrieves help messages according builtin
 * @d: data structure (args and input)
 * Return: Return 0
*/
int ghelp(pro *d)
{

	if (d->args[1] == 0)
		myhp_gen();
	else if (christycmp(d->args[1], "setenv") == 0)
		myhp_setenv();
	else if (christycmp(d->args[1], "env") == 0)
		myhp_env();
	else if (christycmp(d->args[1], "unsetenv") == 0)
		myhp_unsetenv();
	else if (christycmp(d->args[1], "help") == 0)
		myhp();
	else if (christycmp(d->args[1], "exit") == 0)
		myhp_exit();
	else if (christycmp(d->args[1], "cd") == 0)
		myhp_cd();
	else if (christycmp(d->args[1], "alias") == 0)
		myhp_sis();
	else
		write(STDERR_FILENO, d->args[0],
		      christylen(d->args[0]));

	d->status = 0;
	return (1);
}
