#include "proshell.h"
/**
 * cj_is_cdir - function that checks for seperators ":" in the current working directory.
 * @path: pointer
 * @n: int pointer
 * Return: 1 for path else 0
 */
int cj_is_cdir(char *path, int *n)
{
	if (path[*n] == ':')
		return (1);

	while (path[*n] != ':' && path[*n])
	{
		*n += 1;
	}

	if (path[*n])
		*n += 1;

	return (0);
}
/**
 * cj_which - function that locates a command
 * @cmd: command or name of command
 * @_environ: environment variable
 * Return: command location
 */
char *cj_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dr;
	int len_dir, len_cmd, a;
	struct stat st;

	path = cj_getenv("PATH", _environ);
	if (path)
	{
		ptr_path = cj_strdup(path);
		len_cmd = cj_strlen(cmd);
		token_path = cj_strtok(ptr_path, ":");
		a = 0;
		while (token_path != NULL)
		{
			if (cj_is_cdir(path, &a))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = cj_strlen(token_path);
			dr = malloc(len_dir + len_cmd + 2);
			cj_strcpy(dr, token_path);
			cj_strcat(dr, "/");
			cj_strcat(dr, cmd);
			cj_strcat(dr, "\0");
			if (stat(dr, &st) == 0)
			{
				free(ptr_path);
				return (dr);
			}
			free(dr);
			token_path = cj_strtok(NULL, ":");
		}
		/*this frees tge pointer */
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}
/**
 * cj_is_executable - function that determines if variable is an executable
 * @dtsh: data structure
 * Return: integer
 */
int cj_is_executable(project_shell *dtsh)
{
	struct stat st;
	int a;
	char *input;

	input = dtsh->args[0];
	for (a = 0; input[a]; a++)
	{
		if (input[a] == '.')
		{
			if (input[a + 1] == '.')
				return (0);
			if (input[a + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[a] == '/' && a != 0)
		{
			if (input[a + 1] == '.')
				continue;
			a++;
			break;
		}
		else
			break;
	/* reflecting data arguments*/
	}
	if (a == 0)
		return (0);

	if (stat(input + a, &st) == 0)
	{
		return (a);
	}
	cj_get_error(dtsh, 127);
	return (-1);
}
/**
 * cj_check_error_cmd - function that verifies if user has permissions to accesss drectory.
 * @d: destination path of  directory
 * @dtsh: data structure
 * Return: 1 if error, else 0
 */
int cj_check_error_cmd(char *d, project_shell *dtsh)
{
	if (d == NULL)
	{
		cj_get_error(dtsh, 127);
		return (1);
	}

	if (cj_strcmp(dtsh->args[0], d) != 0)
	{
		if (access(d, X_OK) == -1)
		{
			cj_get_error(dtsh, 126);
			free(d);
			return (1);
		}
		free(d);
	}
	else
	{
		if (access(dtsh->args[0], X_OK) == -1)
		{
			cj_get_error(dtsh, 126);
			return (1);
		}
	}
	return (0);
}
/**
 * cj_cmd_exec - function that executes command lines
 * @dtsh: data
 * Return: 1 on success.
 */
int cj_cmd_exec(project_shell *dtsh)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *d;
	(void) wpd;

	exec = cj_is_executable(dtsh);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		d = cj_which(dtsh->args[0], dtsh->_environ);
		if (cj_check_error_cmd(d, dtsh) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			d = cj_which(dtsh->args[0], dtsh->_environ);
		else
			d = dtsh->args[0];
		execve(d + exec, dtsh->args, dtsh->_environ);
	}
	else if (pd < 0)
	{
		perror(dtsh->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	dtsh->status = state / 256;
	return (1);
}
