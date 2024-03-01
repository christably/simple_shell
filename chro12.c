#include "proshell.h"
/**
 * cj_cd_dot - changes pathway
 * @dtsh: data relevant
 * Return: NULL
 */
void cj_cd_dot(project_shell *dtsh)
{
char pwd[PATH_MAX];
char *d, *cp_pwd, *cp_strtok_pwd;

getcwd(pwd, sizeof(pwd));
cp_pwd = cj_strdup(pwd);
cj_set_env("OLDPWD", cp_pwd, dtsh);
	d = dtsh->args[1];
	if (cj_strcmp(".", d) == 0)
	{
		cj_set_env("PWD", cp_pwd, dtsh);
		free(cp_pwd);
		return;
	}
	if (cj_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	cj_rev_string(cp_strtok_pwd);
	cp_strtok_pwd = cj_strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = cj_strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			cj_rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		cj_set_env("PWD", cp_strtok_pwd, dtsh);
	}
	else
	{
		chdir("/");
		cj_set_env("PWD", "/", dtsh);
	}
	dtsh->status = 0;
	free(cp_pwd);
}
/**
 * cj_cd_to - functon that changes pathway to a directory given by user
 * @dtsh: data
 * Return: no return
 */
void cj_cd_to(project_shell *dtsh)
{
	char pwd[PATH_MAX];
	char *d, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	d = dtsh->args[1];
	if (chdir(d) == -1)
	{
		cj_get_error(dtsh, 2);
		return;
	}

	cp_pwd = cj_strdup(pwd);
	cj_set_env("OLDPWD", cp_pwd, dtsh);

	cp_dir = cj_strdup(d);
	cj_set_env("PWD", cp_dir, dtsh);

	free(cp_pwd);
	free(cp_dir);

	dtsh->status = 0;

	chdir(d);
}

/**
 * cj_cd_previous - changes to the previous directory
 * @dtsh: data relevant (environ)
 * Return: no return
 */
void cj_cd_previous(project_shell *dtsh)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = cj_strdup(pwd);

	p_oldpwd = cj_getenv("OLDPWD", dtsh->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = cj_strdup(p_oldpwd);

	cj_set_env("OLDPWD", cp_pwd, dtsh);

	if (chdir(cp_oldpwd) == -1)
		cj_set_env("PWD", cp_pwd, dtsh);
	else
		cj_set_env("PWD", cp_oldpwd, dtsh);

	p_pwd = cj_getenv("PWD", dtsh->_environ);

	write(STDOUT_FILENO, p_pwd, cj_strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	dtsh->status = 0;

	chdir(p_pwd);
}
/**
 * cj_cd_to_home - changes pathway to home directory
 * @dtsh: data
 * Return: no return
 */
void cj_cd_to_home(project_shell *dtsh)
{
char *p_pwd, *home;
char pwd[PATH_MAX];

getcwd(pwd, sizeof(pwd));
p_pwd = cj_strdup(pwd);

home = cj_getenv("HOME", dtsh->_environ);

if (home == NULL)
{
cj_set_env("OLDPWD", p_pwd, dtsh);
free(p_pwd);
return;
}

/* if loop argument */
if (chdir(home) == -1)
{
cj_get_error(dtsh, 2);
free(p_pwd);
return;
}

/* pathway arguments */
cj_set_env("OLDPWD", p_pwd, dtsh);
cj_set_env("PWD", home, dtsh);
free(p_pwd);
dtsh->status = 0;
}
