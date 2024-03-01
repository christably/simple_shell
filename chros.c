#include "proshell.h"
/**
 * freee_data - functionn that frees data struct
 * @dtsh: data struct
 * Return: NULL
 **********************************/
void freee_data(project_shell *dtsh)
{
unsigned int w = 0;
while (dtsh->_environ[w])
{
free(dtsh->_environ[w]);
w++;
}

free(dtsh->_environ);
free(dtsh->pid);
}
/**
 * sett_data- function that initialize data struct
 * @dtsh: data
 * @av: argument vector
 * Return: NULL
 **********************************/
void sett_data(project_shell *dtsh, char **av)
{
unsigned int w = 0;

dtsh->av = av;
dtsh->input = NULL;
dtsh->args = NULL;
dtsh->status = 0;
dtsh->counter = 1;

for (w = 0; environ[w]; w++)
;

dtsh->_environ = malloc(sizeof(char *) * (w + 1));

for (w = 0; environ[w]; w++)
{
dtsh->_environ[w] = cj_strdup(environ[w]);
}

dtsh->_environ[w] = NULL;
dtsh->pid = cj_itoa(getpid());
}
/**
 * main - the entry or intialization point
 * @ac: function for argument count
 * @av: the argument vector
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	project_shell dtsh;
	(void) ac;

	signal(SIGINT, cj_get_sigint);
	sett_data(&dtsh, av);
	christy_s_loop(&dtsh);
	freee_data(&dtsh);
	if (dtsh.status < 0)
		return (255);
	return (dtsh.status);
}
