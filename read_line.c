#include "proshell.h"
/**
 * rline - reads the input string.
 * @f: return value of getline function
 * Return: input string
 */
char *rline(int *f)
{
	char *input = NULL;
	size_t bufsize = 0;

	*f = getline(&input, &bufsize, stdin);

	return (input);
}
