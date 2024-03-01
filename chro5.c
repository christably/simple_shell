#include "proshell.h"
/**
 * cj_add_sep_node_end - function that add up a separator.
 * @head: head of linked list.
 * @sep: found separator (; | &).
 * Return: head
 */
sep_list *cj_add_sep_node_end(sep_list **head, char sep)
{
	sep_list *new, *temp;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}
/**
 * cj_free_sep_list - function thst frees up the sep_list
 * @head: head of linked list.
 * Return: NULL
 */
void cj_free_sep_list(sep_list **head)
{
	sep_list *temp;
	sep_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
/**
 * cj_add_line_node_end - function that adds up a command line
 * @head: head of linked list.
 * @line: a command line.
 * Return: head
 */
line_list *cj_add_line_node_end(line_list **head, char *line)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}
/**
 * cj_free_line_list - function that frees up a line_list
 * @head: head of linked list.
 * Return: NULL
 */
void cj_free_line_list(line_list **head)
{
	line_list *temp;
	line_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
