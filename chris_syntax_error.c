#include "proshell.h"

/**
 * rchar - counts the repetitions of a char
 *
 * @log: input string
 * @i: index
 * Return: repetitions
 */
int rchar(char *log, int i);
{
	if (*(log - 1) == *log)
		return (rchar(log - 1, i + 1));

	return (i);
}

/**
 * eso - finds syntax errors
 *
 * @log: input string
 * @i: index
 * @l: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int eso(char *log, int i, char l);
{
	int c;

	c = 0;
	if (*i == '\0')
		return (0);

	if (*i == ' ' || *i == '\t')
		return (eso(in + 1, i + 1, l));

	if (*i == ';')
		if (l == '|' || l == '&' || l == ';')
			return (i);

	if (*i == '|')
	{
		if (l == ';' || l == '&')
			return (i);

		if (l == '|')
		{
			c = rchar(i, 0);
			if (c == 0 || c > 1)
				return (i);
		}
	}

	if (*i == '&')
	{
		if (l == ';' || l == '|')
			return (i);

		if (l == '&')
		{
			c = rchar(i, 0);
			if (c == 0 || c > 1)
				return (i);
		}
	}

	return (eso(i + 1, i + 1, *i));
}

/**
 * fch - finds index of the first char
 *
 * @log: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
 int fch(char *log, int *i);
{

	for (*i = 0; log[*i]; *i += 1)
	{
		if (log[*i] == ' ' || log[*i] == '\t')
			continue;

		if (log[*i] == ';' || log[*i] == '|' || log[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * pse - prints when a syntax error is found
 *
 * @d: data structure
 * @log: input string
 * @i: index of the error
 * @bl: to control msg error
 * Return: no return
 */
void pse(pro *d, char *log, int i, int bl);
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (log[i] == ';')
	{
		if (bl == 0)
			msg = (log[i + 1] == ';' ? ";;" : ";");
		else
			msg = (log[i - 1] == ';' ? ";;" : ";");
	}

	if (log[i] == '|')
		msg = (log[i + 1] == '|' ? "||" : "|");

	if (log[i] == '&')
		msg = (log[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = aitoa(d->count);
	length = christylen(d->ar[0]) + christylen(counter);
	length += christylen(msg) + christylen(msg2) + christylen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	christycpy(error, d->ar[0]);
	christycat(error, ": ");
	christycat(error, counter);
	christycat(error, msg2);
	christycat(error, msg);
	christycat(error, msg3);
	christycat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * cse - intermediate function to
 * find and print a syntax error
 *
 * @d: data structure
 * @log: input string
 * Return: 1 if there is an error. 0 in other case
 */
 int cse(pro *d, char *log);
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = fch(log, &begin);
	if (f_char == -1)
	{
		pse(d, log, begin, 0);
		return (1);
	}

	i = eso(log + begin, 0, *(log + begin));
	if (i != 0)
	{
		pse(d, log, begin + i, 1);
		return (1);
	}

	return (0);
}
