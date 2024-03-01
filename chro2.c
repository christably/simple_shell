#include "proshell.h"
/**
 * e_env - function for the error info for env in get_env.
 * @dtsh: data
 * Return: error message
 */
char *e_env(project_shell *dtsh)
{
	int length;
	char *errors;
	char *v_s;
	char *msg;

	v_s = cj_itoa(dtsh->counter);
	msg = ": Unable to add/remove from environment\n";
	length = cj_strlen(dtsh->av[0]) + cj_strlen(v_s);
	length += cj_strlen(dtsh->args[0]) + cj_strlen(msg) + 4;
	errors = malloc(sizeof(char) * (length + 1));
	if (errors == 0)
	{
		free(errors);
		free(v_s);
		return (NULL);
	}

	cj_strcpy(errors, dtsh->av[0]);
	cj_strcat(errors, ": ");
	cj_strcat(errors, v_s);
	cj_strcat(errors, ": ");
	cj_strcat(errors, dtsh->args[0]);
	cj_strcat(errors, msg);
	cj_strcat(errors, "\0");
	free(v_s);

	return (errors);
}
/**
 * e_path_126 - function for error info for path and failure denied permission.
 * @dtsh: data
 * Return: error string.
 */
char *e_path_126(project_shell *dtsh)
{
	int length;
	char *v_s;
	char *errors;

	v_s = cj_itoa(dtsh->counter);
	length = cj_strlen(dtsh->av[0]) + cj_strlen(v_s);
	length += cj_strlen(dtsh->args[0]) + 24;
	errors = malloc(sizeof(char) * (length + 1));
	if (errors == 0)
	{
		free(errors);
		free(v_s);
		return (NULL);
	}
	cj_strcpy(errors, dtsh->av[0]);
	cj_strcat(errors, ": ");
	cj_strcat(errors, v_s);
	cj_strcat(errors, ": ");
	cj_strcat(errors, dtsh->args[0]);
	cj_strcat(errors, ": Permission denied\n");
	cj_strcat(errors, "\0");
	free(v_s);

	return (errors);
}
