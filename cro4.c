#include "proshell.h"
/**
 * cj_help - function; infomation for builtin help.
 * Return: NULL
 */
void ax_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";/*help builti-in */

	write(STDOUT_FILENO, help, cj_strlen(help));
	help = "\tDisplay information about builtin commands.\n ";/*help fun */
	write(STDOUT_FILENO, help, cj_strlen(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, cj_strlen(help));
}
/**
 * cj_help_alias - function data info for builtin alias.
 * Return: NULL
 */
void ax_help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";/*for alias function */

	write(STDOUT_FILENO, help, cj_strlen(help));
	help = "\tDefine or display aliases.\n ";/*defines alias function */
	write(STDOUT_FILENO, help, cj_strlen(help));
}
/**
 * cj_help_cd - function help data for builtin cd.
 * Return: NULL
 */
void ax_help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, cj_strlen(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, cj_strlen(help));
}
