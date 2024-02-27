#include "proshell.h"

/**
 * spchar - swaps | and & for non-printed chars
 *
 * @log: input string
 * @bl: type of swap
 * Return: swapped string
 */
 char *spchar(char *log, int bl)
	int i;

	if (bl == 0)
	{
		for (i = 0; log[i]; i++)
		{
			if (log[i] == '|')
			{
				if (log[i + 1] != '|')
					log[i] = 16;
				else
					i++;
			}

			if (log[i] == '&')
			{
				if (log[i + 1] != '&')
					log[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; log[i]; i++)
		{
			log[i] = (log[i] == 16 ? '|' : log[i]);
			log[i] = (log[i] == 12 ? '&' : log[i]);
		}
	}
	return (log);
}

/**
 * an - add separators and command lines in the lists
 *
 * @h1: head of separator list
 * @h2: head of command lines list
 * @log: input string
 * Return: no return
 */
void an(sl **h1, ln **h2, char *log)
{
	int i;
	char *line;

	log = spchar(log, 0);

	for (i = 0; log[i]; i++)
	{
		if (log[i] == ';')
			asne(h1, log[i]);

		if (log[i] == '|' || log[i] == '&')
		{
			asne(h1, log[i]);
			i++;
		}
	}

	line = christytok(log, ";|&");
	do {
		line = spchar(line, 1);
		alne(h2, line);
		line = christytok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * gnxt - go to the next command line stored
 *
 * @ls: separator list
 * @ll: command line list
 * @d: data structure
 * Return: no return
 */
void gnxt(sl **ls, ln **ll, pro *d)
{
	int loop_sep;
	sl *ls_s;
	ln *ls_l;

	loop_sep = 1;
	ls_s = *ls;
	ls_l = *ll;

	while (ls_s != NULL && loop_sep)
	{
		if (d->status == 0)
		{
			if (ls_s->sep == '&' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '|')
				ls_l = ls_l->nxt, ls_s = ls_s->nxt;
		}
		else
		{
			if (ls_s->sep == '|' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '&')
				ls_l = ls_l->nxt, ls_s = ls_s->nxt;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->nxt;
	}

	*ls = ls_s;
	*ll = ls_l;
}

/**
 * sc - splits command lines 
 * @d: data structure
 * @log: input string
 * Return: 0 to exit, 1 to continue
 */
 int sc(pro *d, char *log)
{

	sl *h1, *ls;
	ln *h2, *ll;
	int loop;

	h1 = NULL;
	h2 = NULL;

	an(&h1, &h2, log);

	ls = h1;
	ll = h2;

	while (ll != NULL)
	{
		d->logt = ll->l;
		d->args = sp(d->log);
		loop = eline(d);
		free(d->args);

		if (loop == 0)
			break;

		gnxt(&ls, &ll, d);

		if (ll != NULL)
			ll = ll->nxt;
	}

	fsl(&h1);
	fll(&h2);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * sp - tokenizes the input string
 *
 * @log: input string.
 * Return: string splitted.
 */
char **sp(char *log)

{
	size_t bs;
	size_t i;
	char **ts;
	char *t;

	bs = TOK_BUFSIZE;
	ts = malloc(sizeof(char *) * (bs));
	if (ts == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	t = christytok(log, TOK_DELIM);
	ts[0] = t;

	for (i = 1; t != NULL; i++)
	{
		if (i == bs)
		{
			bs += TOK_BUFSIZE;
			ts = shellocdp(ts, i, sizeof(char *) * bs);
			if (ts == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		t = christytok(NULL, TOK_DELIM);
		ts[i] = t;
	}

	return (ts);
}
