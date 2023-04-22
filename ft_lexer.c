#include "minishell.h"

int is_it_whitespace(char c)
{
    if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
        return (1);
    else
        return (0);
}


int check_token_end(char *str)
{
    str++;
    if (*str == '\0')
        return (1);
    else if (is_it_whitespace(*str) > 0)
        return (1);
    else if (is_it_redirection(str) > 0)
        return (1);
    else if (is_it_log_operator(str) > 0)
        return (1);
    return (0);
}

char get_next_quote(char quote)
{
    if (quote == '\'')
        return ('\'');
    else
        return ('\"');
}

//echo a"b">testing.c |grep b>" test"moi"'b'"'ing' ' '
int handle_quotes(char *str, char quote)
{
    int len;
    int quotes;

    quotes = 1; //0 on auki, 1 on kiinni
    len = 2;
    str++;
    while(1)
    {
        if (*str == '\0')
            break ;
        else if (*str == quote)
        {
            quotes++;
            if (check_token_end(str) > 0 && quotes % 2 == 0)
                break ;
            else if (str[1] == '\'' || str[1] == '\"')
            {
                quote = get_next_quote(str[1]);
                str++;
                str++;
                len++;
                len++;
                continue ;
            }
            // else
            //     continue ;
        }
        len++;
        str++;
    }
    // if (len == 3)
    //     len = 2;
    return (len);
}

int is_it_operator(char *str)
{
    if (is_it_redirection > 0)
        return (is_it_redirection(str));
    else if (is_it_log_operator > 0)
        return (is_it_log_operator(str));
    return (0);
}

int get_token_len(char *str)
{
    int len;
    len = 0;

    if (*str == '\'' || *str == '\"')
        return (handle_quotes(str, *str));
    else if (is_it_operator(str) > 0)
        return (is_it_operator(str));
    while(str[len] && is_it_whitespace(str[len]) == 0 &&\
    is_it_log_operator(&str[len]) == 0 && is_it_redirection(&str[len]) == 0&&\
    str[len] != '\'' && str[len] != '\"')
        len++;
    return (len);
}

char *ft_lexer(char *str)
{
    static char *last_str;
    char *token;
    int tokenlen;
    int i;

    token = NULL;
    tokenlen = 0;
    i = 0;
    if (str != NULL)
        last_str = str;
    while (*last_str && is_it_whitespace(*last_str)) //skip WS
        last_str++;
    if (*last_str == '\0')
        return (NULL);
    tokenlen = get_token_len(last_str); //how many chars
    token = malloc((tokenlen + 1) * sizeof(char));
    token[tokenlen] = '\0';
    while (i < tokenlen)
    {
        token[i] = last_str[i];
        i++;
    }
    i = 0;
    while (i < tokenlen)
    {
        last_str++;
        i++;
    }
    if (*token == '\0')
        return (NULL);
    return (token);
}

// int main(void)
// {
//     char str[420] = "VAR=msakkura && echo $VAR || echo 'Variable not set'";
//     char *token;

//     token = ft_lexer(str);
//     while (token != NULL)
//     {
//         printf("%s\n", token);
//         token = ft_lexer(NULL);
//     }
//     return (0);
// }