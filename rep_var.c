#include "proshell.h"

/**
 * cenv - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: input string
 * @d: data structure
 * Return: no return
 */
void cenv(rv **h, char *in, pro *d)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = d->_env;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = christylen(_envr[row] + chr + 1);
				arvn(h, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	arvn(h, j, NULL, 0);
}

/**
 * cvars - check if the typed variable is $$ or $?
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @d: data structure
 * Return: no return
 */
 int cvars(rv **h, char *in, char *st, pro *d)
{
	int i, lst, lpd;

	lst = christylen(st);
	lpd = christylen(d->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				arvn(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				arvn(h, 2, d->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				arvn(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				arvn(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				arvn(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				arvn(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				arvn(h, 0, NULL, 0);
			else
				cenv(h, in + i, d);
		}
	}

	return (i);
}

/**
 * rlogg - replaces string into variables
 *
 * @h: head of the linked list
 * @log: input string
 * @nt: new input string (replaced)
 * @nn: new length
 * Return: replaced string
 */
char *rlogg(rv **h, char *log, char *nt, int nn)
{
	rv *indx;
	int i, j, k;

	indx = *h;
	for (j = i = 0; i < nn; i++)
	{
		if (log[j] == '$')
		{
			if (!(indx->lvr) && !(indx->lvl))
			{
				nt[i] = log[j];
				j++;
			}
			else if (indx->lvr && !(indx->lvl))
			{
				for (k = 0; k < indx->lvr; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->lvl; k++)
				{
					nt[i] = indx->val[k];
					i++;
				}
				j += (indx->lvr);
				i--;
			}
			indx = indx->nxt;
		}
		else
		{
			nt[i] = log[j];
			j++;
		}
	}

	return (nt);
}

/**
 * rva - calls functions to replace string into vars
 * @log: input string
 * @d: data structure
 * Return: replaced string
 */
char *rva(char *log, pro *d)
{
	rv *h, *indx;
	char *status, *nt;
	int ol, nl;

	status = aitoa(d->status);
	h = NULL;

	ol = cvars(&h, log, status, d);

	if (h == NULL)
	{
		free(status);
		return (log);
	}

	indx = h;
	nl = 0;

	while (indx != NULL)
	{
		nl += (indx->lvl - indx->lvr);
		indx = indx->nxt;
	}

	nl += ol;

	nt = malloc(sizeof(char) * (nl + 1));
	nt[nl] = '\0';

	nt = rlogg(&h, log, nt, nl);

	free(log);
	free(status);
	frl(&h);

	return (nt);
}
