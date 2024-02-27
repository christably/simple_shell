#include "proshell.h"

/**
 * gbuilt - builtin that pais the command in the arg
 * @c: command
 * Return: function pointer of the builtin command
 */
int (*gbuilt(char *c))(pro *)
{
	built builtin[] = {
		{ "env", _env },
		{ "exit", eshell },
		{ "setenv", stenv },
		{ "unsetenv", setenvv },
		{ "cd", cds },
		{ "help", ghelp },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (christycmp(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}

/**
 * gsigint - Handle the crtl + c call in prompt
 * @sig: Signal handler
 */
 void gsigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
