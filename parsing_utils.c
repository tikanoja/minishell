#include "minishell.h"
#include <string.h>

int is_it_delim(char c, const char *delim)
{
    int i;

    i = 0;
    while (delim[i])
    {
        if (c == delim[i])
            return (1);
        i++;
    }
    return (0);
}

char *ft_strtok(char *str, const char *delim)
{
    static char *last_str;
    char *token;

    if (str != NULL)
        last_str = str;
    token = last_str;
    while (*last_str)
    {
        if (is_it_delim(*last_str, delim) == TRUE)
        {
            last_str++;
            token = last_str;
            continue ;
        }
        while (*last_str && is_it_delim(*last_str, delim) == FALSE)
            last_str++;
        if (is_it_delim(*last_str, delim) == TRUE)
        {
            *last_str = '\0';
            last_str++;
            break;
        }
    }
    if (*token == '\0')
        return (NULL);
    return (token);
}

int main(void)
{
    char str[39] = "hello  , 'please tokenize' me , please\0";
    char delim[3] = " ,";
    char *token;

    token = ft_strtok(str, delim);
    while (token != NULL)
    {
        printf("%s\n", token);
        token = ft_strtok(NULL, delim);
    }
    return (0);
}