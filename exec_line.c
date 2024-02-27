#include "proshell.h"

/**
 * eline - finds builtins and commands
 *
 * @: data relevant (args)
 * Return: 1 on success.
 */
int eline(pro *d)
{
	int (*builtin)(pro *d);

	if (d->args[0] == NULL)
		return (1);

	builtin = gbuilt(d->args[0]);

	if (builtin != NULL)
		return (builtin(d));

	return (cexec(d));
}
