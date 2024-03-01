#include "proshell.h"
/**
 * cj_swap_char - function that swaps | and & for non-printed chars
 * @input: input string input
 * @bool: type of swap
 * Return: the swapped string
 */
char *cj_swap_char(char *input, int bool)
{
    int z;

    if (bool == 0)
    {
        z = 0;
        while (input[z])
        {
            if (input[z] == '|')
            {
                if (input[z + 1] != '|')
                    input[z] = 16;
                else
                    z++;
            }

            if (input[z] == '&')
            {
                if (input[z + 1] != '&')
                    input[z] = 12;
                else
                    z++;
            }
            z++;
        }
    }
    else
    {
        z = 0;
        while (input[z])
        {
            input[z] = (input[z] == 16 ? '|' : input[z]);
            input[z] = (input[z] == 12 ? '&' : input[z]);
            z++;
        }
    }
    return input;
}
/**
 * cj_add_nodes - function that adds separators and command lines in the lists
 * @hhs: head of separator list
 * @hhl: head of command lines list
 * @input: input string input
 * Return: NULL
 */
void cj_add_nodes(sep_list **hhs, line_list **hhl, char *input)
{
    int z;
    char *line;

    input = cj_swap_char(input, 0);

    for (z = 0; input[z]; z++)
    {
        if (input[z] == ';')
            cj_add_sep_node_end(hhs, input[z]);

        if (input[z] == '|' || input[z] == '&')
        {
            cj_add_sep_node_end(hhs, input[z]);
            z++;
        }
    }

    line = cj_strtok(input, ";|&");
    do {
        line = cj_swap_char(line, 1);
        cj_add_line_node_end(hhl, line);
        line = cj_strtok(NULL, ";|&");
    } while (line != NULL);
}
/**
 * cj_go_next - function that goes to the next command line stored
 * @ll_s: separator list
 * @ll_l: command line list
 * @dtsh: data struct
 * Return: NULL
 */
void cj_go_next(sep_list **ll_s, line_list **ll_l, project_shell *dtsh)
{
    int loop_sep;
    sep_list *ls_s;
    line_list *ls_l;

    loop_sep = 1;
    ls_s = *ll_s;
    ls_l = *ll_l;

    while (ls_s != NULL && loop_sep)
    {
        if (dtsh->status == 0)
        {
            if (ls_s->separator == '&' || ls_s->separator == ';')
                loop_sep = 0;
            if (ls_s->separator == '|')
                ls_l = ls_l->next, ls_s = ls_s->next;
        }
        else
        {
            if (ls_s->separator == '|' || ls_s->separator == ';')
                loop_sep = 0;
            if (ls_s->separator == '&')
                ls_l = ls_l->next, ls_s = ls_s->next;
        }
        if (ls_s != NULL && !loop_sep)
            ls_s = ls_s->next;
    }

    *ll_s = ls_s;
    *ll_l = ls_l;
}
/**
 * cj_split_commands - function that splits command lines according to the separators
 * @dtsh: data struct
 * @input: input strin input
 * Return: 0 to exit, 1 to continue
 */
int cj_split_commands(project_shell *dtsh, char *input)
{
    sep_list *hhs, *ll_s;
    line_list *hhl, *ll_l;
    int loop;

    hhs = NULL;
    hhl = NULL;

    cj_add_nodes(&hhs, &hhl, input);

    ll_s = hhs;
    ll_l = hhl;

    while (ll_l != NULL)
    {
        dtsh->input = ll_l->line;
        dtsh->args = cj_split_line(dtsh->input);
        loop = cj_exec_line(dtsh);
        free(dtsh->args);

        if (loop == 0)
            break;

        cj_go_next(&ll_s, &ll_l, dtsh);

        if (ll_l != NULL)
            ll_l = ll_l->next;
    }

    cj_free_sep_list(&hhs);
    cj_free_line_list(&hhl);

    if (loop == 0)
        return 0;
    return 1;
}
/**
 * cj_split_line - function for the token the input string
 * @input: input string inlut
 * Return: string splitted.
 */
char **cj_split_line(char *input)
{
    size_t b;
    size_t z;
    char **tokens;
    char *token;

    b = TOK_BUFSIZE;
    tokens = malloc(sizeof(char *) * b);
    if (tokens == NULL)
    {
        write(STDERR_FILENO, ": allocation error\n", 18);
        exit(EXIT_FAILURE);
    }

    token = cj_strtok(input, TOK_DELIM);
    tokens[0] = token;

    for (z = 1; token != NULL; z++)
    {
        if (z == b)
        {
            b += TOK_BUFSIZE;
            tokens = cj_reallocdp(tokens, z, sizeof(char *) * b);
            if (tokens == NULL)
            {
                write(STDERR_FILENO, ": allocation error\n", 18);
                exit(EXIT_FAILURE);
            }
        }
        token = cj_strtok(NULL, TOK_DELIM);
        tokens[z] = token;
    }

    return tokens;
}
