#include "minishell.h"

int is_it_whitespace(char c)
{
    if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
        return (1);
    else
        return (0);
}

char *handle_quotes(char *last_str, char quote)
{
    char *token;

    last_str--;
    *last_str = '\0';
    last_str++;
    token = last_str;
    last_str++;
    while (*last_str != quote)
        last_str++;
    last_str++;
    *last_str = '\0';
    last_str++;
    return (token);
}

char *ft_lexer(char *str)
{
    static char *last_str;
    char *token;

    if (str != NULL)
        last_str = str;
    while (*last_str && is_it_whitespace(*last_str))
        last_str++;
    token = last_str;
    if (*last_str == '\'' || *last_str == '\"')
    {
        token = handle_quotes(last_str, *last_str);
        last_str = token + ft_strlen(token) + 1;
    } 
    else
    {
        while (*last_str && !is_it_whitespace(*last_str))
            last_str++;
        if (*last_str && is_it_whitespace(*last_str))
            *last_str++ = '\0';
    }
    if (*token == '\0')
        return (NULL);
    return (token);
}

// int main(void)
// {
//     char str[100] = "echo -n   'hei heii' \" moi     $ARG\" >> log.txt | echo -n   'moi taas ' \"   $ARG\"  \0";
//     char *token;

//     token = ft_lexer(str);
//     while (token != NULL)
//     {
//         printf("%s\n", token);
//         token = ft_lexer(NULL);
//     }
//     return (0);
// }