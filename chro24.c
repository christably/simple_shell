#include "proshell.h"
/**
 * cj_get_sigint - function that handles prompt
 * @sig: Signal handler
 */
void cj_get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
/**
 * cj_read_line - function that reads the input string
 * @iff: it is the return value of getline function
 * Return: input string
 */
char *cj_read_line(int *iff)
{
	char *input = NULL;
	size_t bufsize = 0;

	*iff = getline(&input, &bufsize, stdin);

	return (input);
}
