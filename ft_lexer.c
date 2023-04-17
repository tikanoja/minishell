#include "minishell.h"

int is_it_whitespace(char c)
{
    if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
        return (1);
    else
        return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
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

char    *ft_lexer_helper(char *last_str)
{
    char delim;

    if (*last_str == '=')
    {
        last_str++;
        delim = *last_str;
        last_str++;
        if (delim == '\'' || delim == '\"')
            while (*last_str != delim)
                last_str++;
    }
    last_str++;
    return (last_str);
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
            last_str = ft_lexer_helper(last_str);
        if (*last_str && is_it_whitespace(*last_str))
            *last_str++ = '\0';
    }
    if (*token == '\0')
        return (NULL);
    return (token);
}

// char *ft_lexer(char *str)
// {
//     static char *last_str;
//     char *token;

//     if (str != NULL)
//         last_str = str;
//     while (*last_str && is_it_whitespace(*last_str))
//         last_str++;
//     token = last_str;
//     if (*last_str == '\'' || *last_str == '\"')
//     {
//         token = handle_quotes(last_str, *last_str);
//         last_str = token + ft_strlen(token) + 1;
//     } 
//     else
//     {
//         while (*last_str && !is_it_whitespace(*last_str))
//             last_str++;
//         if (*last_str && is_it_whitespace(*last_str))
//             *last_str++ = '\0';
//     }
//     if (*token == '\0')
//         return (NULL);
//     return (token);
// }

int main(void)
{
    char str[420] = "VAR=msakkura && echo $VAR || echo 'Variable not set'";
    char *token;

    token = ft_lexer(str);
    while (token != NULL)
    {
        printf("%s\n", token);
        token = ft_lexer(NULL);
    }
    return (0);
}