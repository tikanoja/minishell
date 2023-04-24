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
	if (ft_strncmp_casein(prompt, "echo\0", 4) == 0 &&\
	(is_it_whitespace(prompt[4]) || prompt[4] == '\0')) 
		return (1);
	else if (ft_strncmp_casein(prompt, "cd\0", 2) == 0 &&\
	(is_it_whitespace(prompt[2]) || prompt[2] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "pwd\0", 3) == 0 &&\
	(is_it_whitespace(prompt[3]) || prompt[3] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "export\0", 6) == 0 &&\
	(is_it_whitespace(prompt[6]) || prompt[6] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "unset\0", 5) == 0 &&\
	(is_it_whitespace(prompt[5]) || prompt[5] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "env\0", 3) == 0 &&\
	(is_it_whitespace(prompt[3]) || prompt[3] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "exit\0", 4) == 0 &&\
	(is_it_whitespace(prompt[4]) || prompt[4] == '\0'))
		return (1);
	return (0);
}

int is_it_redirection(char *prompt)
{
	if (ft_strncmp(prompt, "|\0", 1) == 0) 
		return (1);
	else if (ft_strncmp(prompt, "<<\0", 2) == 0)
		return (2);
	else if (ft_strncmp(prompt, ">>\0", 2) == 0)
		return (2);
	else if (ft_strncmp(prompt, "<\0", 1) == 0)
		return (1);
	else if (ft_strncmp(prompt, ">\0", 1) == 0)
		return (1);
	return (0);
}

int is_it_log_operator(char *prompt)
{
	if (ft_strncmp(prompt, "||\0", 2) == 0) 
		return (2);
	else if (ft_strncmp(prompt, "&&\0", 2) == 0)
		return (2);
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
	node->argc = 0;
	node->prev = prev;
	prev->next = node;
	node->args = malloc(sizeof(char **));
	node->args[0] = NULL;
	node->input = STDIN_FILENO;
	node->output = STDOUT_FILENO;
	return (node);
}

t_list *add_head_node(t_list *node, t_list **head)
{
	node = malloc(sizeof(t_list)); //protect malloc
	node->args = malloc(sizeof(char **)); //protect
	node->args[0] = NULL;
	node->argc = 0;
	node->input = STDIN_FILENO;
	node->output = STDOUT_FILENO;
	node->prev = NULL;
	node->next = NULL;
	*head = node;
	return (node);
}

char **realloc_array(t_list *node, char *token)
{
	char **array;
	int i;

	array = NULL;
	i = 0;
	array = malloc((node->argc + 2) * sizeof(char **));
	while (1)
	{
		array[i] = malloc(sizeof(char *));
		// if (!array[i]) 
		array[i] = node->args[i];
		if (array[i] == NULL)
			break ;
		i++;
	}
	array[i] = token;
	array[i + 1] = NULL;
	// i = 0; SOMEHOW SEGFAULT With >= 5 args!!!!
	// while (node->args[i] != NULL && node->prev != NULL)
	// {
	// 	free(node->args[i]);
	// 	i++;
	// }
	return (array);
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
	node = add_head_node(node, &head);
	// mallocprotect(head);
	while(token)
	{
		if (is_it_redirection(token) > 0 || is_it_log_operator(token) > 0)
		{
			argflag = -1;
			node = add_node(node, token);
			node = add_node(node, NULL);
			token = ft_lexer(NULL);
		}
		if (argflag == -1)
			node->value = token;
		else
		{
			node->args = realloc_array(node, token);
			// if (argflag == 0)
			//     node->args = malloc(sizeof(char **));
			// node->args[argflag] = malloc(sizeof(char *));
			// node->args[argflag + 1] = NULL;
			// node->args[argflag] = token;
			node->argc = argflag + 1;
		}
		argflag++;
		token = ft_lexer(NULL);
	}
	return (head);
}