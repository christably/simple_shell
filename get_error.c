#include "proshell.h"

/**
 * gerror - calls the error according the builtin, syntax or permission
 * @d: data structure that contains arguments
 * @ev: error value
 * Return: error
 */
int gerror(pro *d, int ev)
{
	char *error;

	switch (ev)
	{
	case -1:
		error = eenv(d);
		break;
	case 126:
		error = ep126(d);
		break;
	case 127:
		error = enf(d);
		break;
	case 2:
		if (christycmp("exit", d->args[0]) == 0)
			error = eesh(d);
		else if (christycmp("cd", d->args[0]) == 0)
			error = egd(d);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, christylen(error));
		free(error);
	}

	d->status = ev;
	return (ev);
}
