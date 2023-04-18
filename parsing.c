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

int is_it_redirection(char *prompt)
{
    if (ft_strncmp(prompt, "|", 1) == 0 &&\
    (is_it_whitespace(prompt[1]) || prompt[1] == '\0')) 
        return (1);
    else if (ft_strncmp(prompt, "<", 1) == 0 &&\
    (is_it_whitespace(prompt[1]) || prompt[1] == '\0'))
        return (1);
    else if (ft_strncmp(prompt, ">", 1) == 0 &&\
    (is_it_whitespace(prompt[1]) || prompt[1] == '\0'))
        return (1);
    else if (ft_strncmp(prompt, "<<", 2) == 0 &&\
    (is_it_whitespace(prompt[2]) || prompt[2] == '\0'))
        return (1);
    else if (ft_strncmp(prompt, ">>", 2) == 0 &&\
    (is_it_whitespace(prompt[2]) || prompt[2] == '\0'))
        return (1);
    return (0);
}

int is_it_log_operator(char *prompt)
{
    if (ft_strncmp(prompt, "||", 2) == 0 &&\
    (is_it_whitespace(prompt[2]) || prompt[2] == '\0')) 
        return (1);
    else if (ft_strncmp(prompt, "&&", 2) == 0 &&\
    (is_it_whitespace(prompt[2]) || prompt[2] == '\0'))
        return (1);
    return (0);
}

char	*get_path(char **patharr, char *token)
{
	char	*tmp;
    char    *binarypath;
    int     i;

    i = 0;
	while (patharr[i])
	{
		tmp = ft_strjoin(patharr[i], "/");
        //protect
		binarypath = ft_strjoin(tmp, token);
        //protect
		if (access(binarypath, F_OK) == 0)
			break ;
		else
		{
			free(tmp);
			free(binarypath);
			i++;
		}
		if (!patharr[i])
			return (NULL);
	}
	free(tmp);
	return (binarypath);
}

int is_it_shell_command(char *token, char **envcpy)
{
    int i;
    char **patharr;
    char *pathcmd;

    i = 0;
    patharr = NULL;
    while(1)
    {
        if (ft_strncmp(envcpy[i], "PATH=", 5) == 0)
            break ;
        i++;
        if (envcpy[i] == NULL)
        {
            printf("missing path variable\n");
            //exit(1);
        }
    }
    patharr = ft_split(envcpy[i] + 5, ':');
    //protect
    pathcmd = get_path(patharr, token);
    //protect
    if (pathcmd == NULL)
        return (0);
    return (1); //jos ginostaa ni täst voi suoraa palauttaa oikee path binaryyn
}

t_list *add_node(t_list *node, char *token)
{
    t_list  *prev;

    prev = NULL;
    prev = node;
    node = malloc(sizeof(t_list)); //protect
    if (token != NULL)
        node->value = token;
    node->prev = prev;
    prev->next = node;
    return (node);
}

t_list *parsecmd(char *prompt)
{
    t_list  *node;
    t_list  *head;
    char    *token;
    int     argflag;

    node = NULL;
    head = NULL;
    argflag = -1;
    token = ft_lexer(prompt);
    node = malloc(sizeof(t_list)); //protect malloc (if head null just this, if not free list from head)
    head = node;
    while(token)
    {
        if (is_it_redirection(token) == 1 || is_it_log_operator(token) == 1)
        {
            argflag = -1;
            node = add_node(node, token);
            node = add_node(node, NULL);
            token = ft_lexer(NULL);
        }
        if (argflag == -1)
            node->value = token;
        else
            node->args[argflag] = token;
        argflag++;
        token = ft_lexer(NULL);
    }
    return (head);
}
/*
t_list *parsecmd(char *prompt, char **envcpy)
{
    t_list  *node;
    t_list  *head;
    t_list  *prev;
    char    *token;
    int     argflag;

    node = NULL;
    head = NULL;
    prev = NULL;
    argflag = -1;
    token = ft_lexer(prompt);
    while(token)
    {
        printf("token: %s\n", token);
        if (argflag == -1)
            node = malloc(sizeof(t_list));
        if (node == NULL)
        {
            if (head == NULL)
            {
                //free envcpy
                exit(1);
            }
            else if (head != NULL)
            {
                free_list(head);
                exit(1);
            }
        }
        //kaikki noi if elset omien ftioiden sisään
        if (head == NULL)
            head = node;
        if (prev != NULL && argflag == -1)
        {
            prev->next = node;
            node->prev = prev;
        }
        if (argflag >= 0 && is_it_redirection(token) == 0)
        {
            write(1, "ARG\n", 4);
            node->args[argflag] = token;
            argflag++;
        }
        else if (is_it_builtin(token) == 1) //seuraavat redir tai pipe asti on args
        {
            write(1, "BUILTIN\n", 8);
            // node->type = 3;
            node->value = token;
            argflag = 0;
        }
        else if (is_it_shell_command(token, envcpy) == 1)
        {
            write(1, "SHELL CMD\n", 10);
            node->value = token;
        }
        else if (is_it_redirection(token) == 1)
        {
            //palauta et onko < << > >> | ja avaa fd
            write(1, "REDIR\n", 6);
            token = ft_lexer(NULL);
            node->output = 1; // open fd & store int to node...
            argflag = -1;
        }
        else
            printf("minishell: command not found: %s\n", token);
        if (argflag == -1)
            prev = node;
        token = ft_lexer(NULL);
    }
    return (head);
}
*/