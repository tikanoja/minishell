#include "minishell.h"

int	ft_strncmp_casein(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n < 1)
		return (0);
	while (i < n - 1 && s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] == s2[i])
		    i++;
        else if (s1[i] >= 65 && s1[i] <= 90 && s1[i] + 32 == s2[i])
            i++;
        else
            break ;
    }
    if (s1[i] >= 65 && s1[i] <= 90)
        return ((unsigned char)s1[i] + 32 - (unsigned char)s2[i]);
    else
	    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int is_it_builtin(char *prompt)
{
    if (ft_strncmp_casein(prompt, "echo", 4) == 0 &&\
    (is_it_whitespace(prompt[4]) || prompt[4] == '\0')) 
        return (1);
    else if (ft_strncmp_casein(prompt, "cd", 2) == 0 &&\
    (is_it_whitespace(prompt[2]) || prompt[2] == '\0'))
        return (1);
    else if (ft_strncmp_casein(prompt, "pwd", 3) == 0 &&\
    (is_it_whitespace(prompt[3]) || prompt[3] == '\0'))
        return (1);
    else if (ft_strncmp_casein(prompt, "export", 6) == 0 &&\
    (is_it_whitespace(prompt[6]) || prompt[6] == '\0'))
        return (1);
    else if (ft_strncmp_casein(prompt, "unset", 5) == 0 &&\
    (is_it_whitespace(prompt[5]) || prompt[5] == '\0'))
        return (1);
    else if (ft_strncmp_casein(prompt, "env", 3) == 0 &&\
    (is_it_whitespace(prompt[3]) || prompt[3] == '\0'))
        return (1);
    else if (ft_strncmp_casein(prompt, "exit", 4) == 0 &&\
    (is_it_whitespace(prompt[4]) || prompt[4] == '\0'))
        return (1);
    return (0);
}

t_tree *parsecmd(char *prompt)
{
    // t_tree  *node;
    char    *token;

    // node = NULL;
    token = ft_lexer(prompt);
    while(token)
    {
        // node = malloc(sizeof(t_tree));
        // // if fails free the bin tree (joku foreach joka luikauttaa free())
        // if (node == NULL)
        //     exit(1);
        if (is_it_builtin(token) == 1)
        {
            write(1, "YES\n", 4);
            // node->type = 3;
        }
        printf("%s\n", token);
        token = ft_lexer(NULL);
    }
    return (0);
}