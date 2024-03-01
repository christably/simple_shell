#include "proshell.h"
/**
 * cj_check_env - function;that checks if the typed variable is an env variable
 * @hd: head of linked list
 * @in: input string input
 * @data: data structure
 * Return: NULL
 */
void cj_check_env(r_var **hd, char *in, project_shell *data)
{
	int row, chr, e, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (e = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = cj_strlen(_envr[row] + chr + 1);
				cj_add_rvar_node(hd, e, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[e] == _envr[row][chr])
				e++;
			else
				break;
		}
	}

	for (e = 0; in[e]; e++)
	{
		if (in[e] == ' ' || in[e] == '\t' || in[e] == ';' || in[e] == '\n')
			break;
	}

	cj_add_rvar_node(hd, e, NULL, 0);
}
/**
 * cj_check_vars - function thst check if the typed variable is $$ or $?
 * @hd: head of the linked list
 * @in: input string input
 * @st: Shell last status
 * @data: data structure
 * Return: NULL
 */
int cj_check_vars(r_var **hd, char *in, char *st, project_shell *data)
{
	int e, lst, lpd;

	lst = cj_strlen(st);
	lpd = cj_strlen(data->pid);

	for (e = 0; in[e]; e++)
	{
		if (in[e] == '$')
		{
			if (in[e + 1] == '?')
				cj_add_rvar_node(hd, 2, st, lst), e++;
			else if (in[e + 1] == '$')
				cj_add_rvar_node(hd, 2, data->pid, lpd), e++;
			else if (in[e + 1] == '\n')
				cj_add_rvar_node(hd, 0, NULL, 0);
			else if (in[e + 1] == '\0')
				cj_add_rvar_node(hd, 0, NULL, 0);
			else if (in[e + 1] == ' ')
				cj_add_rvar_node(hd, 0, NULL, 0);
			else if (in[e + 1] == '\t')
				cj_add_rvar_node(hd, 0, NULL, 0);
			else if (in[e + 1] == ';')
				cj_add_rvar_node(hd, 0, NULL, 0);
			else
				cj_check_env(hd, in + e, data);
		}
	}

	return (e);
}
/**
 * replace_inputs - function thst replaces string into variables
 * @head: head of the linked list
 * @input: input string inut
 * @new_input: new input string
 * @nlen: new length
 * Return: the replaced string
 */
char *replace_inputs(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int e, f, g;

	indx = *head;
	e = f = 0;
	while (f < nlen)
	{
		if (input[f] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[e] = input[f];
				f++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (g = 0; g < indx->len_var; g++)
					f++;
				e--;
			}
			else
			{
				for (g = 0; g < indx->len_val; g++)
				{
					new_input[e] = indx->val[g];
					e++;
				}
				f += (indx->len_var);
				e--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[e] = input[f];
			f++;
		}
	}

	return (new_input);
}
/**
 * rep_vari - function that calls functions to replace string with vars
 * @input: input string input
 * @dtsh: data struct
 * Return: the replaced string
 */
char *rep_vari(char *input, project_shell *dtsh)
{
	r_var *hd, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = cj_itoa(dtsh->status);
	hd = NULL;

	olen = cj_check_vars(&hd, input, status, dtsh);

	if (hd == NULL)
	{
		free(status);
		return (input);
	}

	indx = hd;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replace_inputs(&hd, input, new_input, nlen);

	free(input);
	free(status);
	cj_free_rvar_list(&hd);

	return (new_input);
}
