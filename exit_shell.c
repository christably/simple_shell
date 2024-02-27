#include "proshell.h"

/**
 * eshell - exits the shell
 *
 * @d: data relevant (status and args)
 * Return: 0 on success.
 */
int eshell(pro *d)
{
	unsigned int u;
	int i;
	int s;
	int b;

	if (d->args[1] != NULL)
	{
		u= atoii(d->args[1]);
		i = christigit(d->args[1]);
		s = christylen(d->args[1]);
		b = u > (unsigned int)INT_MAX;
		if (!i || s > 10 || b)
		{
			gerror(d, 2);
			d->status = 2;
			return (1);
		}
		d->status = (u % 256);
	}
	return (0);
}
