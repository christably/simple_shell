#include "proshell.h"
/**
 * cj_strdup - function that duplicates a str in the heap memory.
 * @s: Type char pointer str
 * Return: the duplicated str
 */
char *cj_strdup(const char *s)
{
    char *new;
    size_t len;

    len = cj_strlen(s);
    new = malloc(sizeof(char) * (len + 1));
    if (new == NULL)
        return (NULL);
    cj_memcpy(new, s, len + 1);
    return (new);
}
/**
 * cj_strlen - function that returns the length of a string.
 * @s: Type char pointer
 * Return: string length
 */
int cj_strlen(const char *s)
{
    int len;

    for (len = 0; s[len] != 0; len++)
    {
    }
    return (len);
}
/**
 * compares_chars - function that compares chars of strings
 * @string: string input string.
 * @delim: delimiter.
 * Return: 1 else, 0 if not.
 */
int compares_chars(char string[], const char *delim)
{
    unsigned int x, y, z;

    x = 0;
    z = 0;
    while (string[x])
    {
        y = 0;
        while (delim[y])
        {
            if (string[x] == delim[y])
            {
                z++;
                break;
            }
            y++;
        }
        x++;
    }
    if (x == z)
        return (1);
    return (0);
}
/**
 * cj_strtok - function splits a string by some delimiter.
 * @string: input string.
 * @delim: delimiter.
 * Return: splited string
 */
char *cj_strtok(char string[], const char *delim)
{
    static char *split, *string_end;
    char *string_start;
    unsigned int u, bool;

    if (string != NULL)
    {
        if (compares_chars(string, delim))
            return (NULL);
        split = string; /*address dtorage*/
        u = cj_strlen(string);
        string_end = &string[u];
    }
    string_start = split;
    if (string_start == string_end)
        return (NULL);

    for (bool = 0; *split; split++)
    {
        /*finding function token*/
        if (split != string_start)
            if (*split && *(split - 1) == '\0')
                break;
        
        for (u = 0; delim[u]; u++)
        {
            if (*split == delim[u])
            {
                *split = '\0';
                if (split == string_start)
                    string_start++;
                break;
            }
        }
        if (bool == 0 && *split)
            bool = 1;
    }
    if (bool == 0)
        return (NULL);
    return (string_start);
}
/**
 * cj_isdigit - function that defines if string passed is a number
 * @s: input string
 * Return: 1 if string is a number else 0
 */
int cj_isdigit(const char *s)
{
    unsigned int u;

    u = 0;
    while (s[u])
    {
        if (s[u] < 48 || s[u] > 57)
            return (0);
        u++;
    }
    return (1);
}
