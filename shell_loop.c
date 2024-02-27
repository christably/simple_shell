#include "proshell.h"

/**
 * wc - deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
 */
char *wc(char *in)
{
	int i, ut;

	ut = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				ut = i;
		}
	}

	if (ut != 0)
	{
		in = shelloc(in, i, ut + 1);
		in[ut] = '\0';
	}

	return (in);
}

/**
 * slll - Loop of shell
 * @d: data relevant
 *
 * Return: no return.
 */
void slll(pro *d)
{
	int loop, i;
	char *log;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		log = rline(&i);
		if (i != -1)
		{
			log = wc(log);
			if (log == NULL)
				continue;

			if (cse(d, log) == 1)
			{
				d->status = 2;
				free(log);
				continue;
			}
			log = rva(log, d);
			loop = sc(d, log);
			d->count += 1;
			free(log);
		}
		else
		{
			loop = 0;
			free(log);
		}
	}
}
