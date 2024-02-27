#include "proshell.h"

/**
 * bl - assigns the line var for get_line
 * @lr: Buffer that store the input str
 * @b: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */
void bl(char **lr, size_t *n, char *b, size_t j)
{

	if (*lr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*lr = b;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lr = b;
	}
	else
	{
		christycpy(*lr, b);
		free(b);
	}
}
/**
 * gline - Read inpt from stream
 * @lptr: buffer that stores the input
 * @n: size of lineptr
 * @sm: stream to read from
 * Return: The number of bytes
 */
ssize_t gline(char **lptr, size_t *n, FILE *sm)
{
	int i;
	static ssize_t log;
	ssize_t retval;
	char *b;
	char t = 'z';

	if (log == 0)
		fflush(sm);
	else
		return (-1);
	log = 0;

	b = malloc(sizeof(char) * BUFSIZE);
	if (b == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && log == 0))
		{
			free(b);
			return (-1);
		}
		if (i == 0 && log != 0)
		{
			log++;
			break;
		}
		if (log >= BUFSIZE)
			b = shelloc(b, log, log + 1);
		b[log] = t;
		log++;
	}
	b[log] = '\0';
	bl(lptr, n, b, log);
	retval = log;
	if (i != 0)
		log = 0;
	return (retval);
}
