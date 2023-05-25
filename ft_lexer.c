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
    if (*str == '\0')
        return (1);
    else if (is_it_whitespace(*str) > 0)
        return (1);
    else if (is_it_redirection_parsing(str) > 0)
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

void init_handle_quotes(int *len, int *quotes)
{
    *len = 2;
    *quotes = 1;
}

void move_pointer(int *len, char **str)
{
    (*str)++;
    *len = *len + 1;
}

// int handle_quotes(char *str, char quote, int start)
// {
//     int len;
//     int quotes;

//     init_handle_quotes(&len, &quotes);
//     while (start > 0)
//     {
//         str++;
//         start--;
//     }
//     str++;
//     while(1)
//     {
//         if (*str == '\0')
//             break ;
//         else if (*str == quote)
//         {
//             quotes++;
//             if (check_token_end(str) > 0 && quotes % 2 == 0)
//                 break ;
//             else if (str[1] == '\'' || str[1] == '\"')
//             {
//                 quote = get_next_quote(str[1]);
//                 quotes++;
//                 str = str + 2;
//                 len = len + 2;
//                 continue ;
//             }
//         }
//         move_pointer(&len, &str);
//     }
//     return (len);
// }

int handle_quotes(char *str, char quote, int start) //jos taa ei skulaa ni tos ylhaal on bakup
{
    int len;
    int quotes;

    len = 0;
    quotes = 1;
    while (start > 0)
    {
        len++;
        start--;
    }
    len++;
    while(1)
    {
        if (str[len] == '\0')
        {
            len--;
            break ;
        }
        else if (str[len] == quote)
        {
            quotes++;
            if (check_token_end(&str[len + 1]) > 0 && quotes % 2 == 0)
                break ;
            else if (str[len + 1] == '\'' || str[len + 1] == '\"')
            {
                quote = get_next_quote(str[len + 1]);
                quotes++;
                len = len + 2;
                continue ;
            }
        }
        len++;
    }
    len++;
    printf("len: %d\n", len);
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
        return (handle_quotes(str, *str, 0));
    else if (is_it_operator(str) > 0)
        return (is_it_operator(str));
    else if (is_it_redirection_parsing(str) > 0)
        return (is_it_redirection_parsing(str));
    while(str[len] && is_it_whitespace(str[len]) == 0 &&\
    is_it_log_operator(&str[len]) == 0 &&\
    is_it_redirection_parsing(&str[len]) == 0)
    {
        if (str[len] == '\'' || str[len] == '\"')
        {
            len = len + handle_quotes(str, str[len], len);
            continue ;
        }
        len++;
    }
    return (len);
}

void fill_token(int tokenlen, char *token, char *last_str)
{
    int i;

    i = 0;
    token[tokenlen] = '\0';
    while (i < tokenlen)
    {
        token[i] = last_str[i];
        i++;
    }
}

char *ft_lexer(char *str, char **envcpy, t_list *head)
{
    static char *last_str;
    char *token;
    int tokenlen;

    token = NULL;
    tokenlen = 0;
    if (str != NULL)
        last_str = str;
    while (*last_str && is_it_whitespace(*last_str))
        last_str++;
    if (*last_str == '\0')
        return (NULL);
    tokenlen = get_token_len(last_str);
    token = ft_calloc((tokenlen + 1), sizeof(char));
    if (!token)
        free_env_and_list(envcpy, head);
    fill_token(tokenlen, token, last_str);
    last_str = last_str + tokenlen;
    if (*token == '\0')
        return (NULL);
    return (token);
}