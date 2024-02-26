#include "proshell.h"

/**
 * cmp_env_name - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * gv - get an environment variable
 * @nm: name of the environment variable
 * @env: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *gv(const char *nm, char **env)
{
	char *ptr_env;
	int i, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; env[i]; i++)
	{
		/* If name and env are equal */
		mov = cmp_env_name(env[i], nm);
		if (mov)
		{
			ptr_env = env[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - prints the evironment variables
 *
 * @d: data relevant.
 * Return: 1 on success.
 */
int _env(pro *d)
{
	int i, j;

	for (i = 0; d->_env[i]; i++)
	{

		for (j = 0; d->_env[i][j]; j++)
			;

		write(STDOUT_FILENO, d->_env[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	d->status = 0;

	return (1);
}
