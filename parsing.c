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


t_list *add_node(t_list *node, char *token, char **envcpy, t_list *head)
{
	t_list  *prev;

	prev = NULL;
	prev = node;
	node = malloc(sizeof(t_list));
	if (!node)
		free_env_and_list(envcpy, head);
	if (token != NULL)
		node->value = token;
	node->argc = 0;
	node->pipe = 0;
	node->prev = prev;
	prev->next = node;
	node->args = malloc(sizeof(char **));
	if (!node->args)
		free_env_and_list(envcpy, head);
	node->args[0] = NULL;
	node->input = STDIN_FILENO;
	node->output = STDOUT_FILENO;
	return (node);
}

t_list *add_head_node(t_list *node, t_list **head, char **envcpy)
{
	node = malloc(sizeof(t_list)); //protect malloc
	if (!node)
	{
		free_env(envcpy);
		exitmsg("node malloc failed");
	}
	node->args = malloc(sizeof(char **));
	if (!node->args)
	{
		free_env(envcpy);
		free(node);
		exitmsg("node malloc failed");
	}
	node->args[0] = NULL;
	node->argc = 0;
	node->pipe = 0;
	node->input = STDIN_FILENO;
	node->output = STDOUT_FILENO;
	node->prev = NULL;
	node->next = NULL;
	*head = node;
	return (node);
}

char **realloc_array(t_list *node, char *token, char **envcpy, t_list *head)
{
	char **array;
	int i;

	array = NULL;
	i = 0;
	array = malloc((node->argc + 2) * sizeof(char **));
	if (!array)
		free_env_and_list(envcpy, head);
	while (1)
	{
		array[i] = malloc(sizeof(char *));
		if (!array[i])
			free_array_and_env(array, envcpy, head);
		array[i] = node->args[i];
		node->args[i] = NULL;
		if (array[i] == NULL)
			break ;
		i++;
	}
	node->argc = i + 1;
	free(node->args);
	node->args = NULL;
	array[i] = token;
	array[i + 1] = NULL;
	return (array);
}

void init_parsecmd(t_list **node, t_list **head, int *argflag)
{
	*node = NULL;
	*head = NULL;
	*argflag = -1;
}

t_list *parsecmd(char *prompt, char **envcpy)
{
	t_list  *node;
	t_list  *head;
	char    *token;
	int     argflag;

	init_parsecmd(&node, &head, &argflag);
	token = ft_lexer(prompt, envcpy, head);
	node = add_head_node(node, &head, envcpy);
	while(token)
	{
		if (is_it_redirection(token) > 0 || is_it_log_operator(token) > 0)
		{
			argflag = -1;
			node = add_node(node, token, envcpy, head);
			node = add_node(node, NULL, envcpy, head);
			token = ft_lexer(NULL, envcpy, head);
		}
		if (argflag == -1)
			node->value = token;
		else
			node->args = realloc_array(node, token, envcpy, head);
		argflag++;
		token = ft_lexer(NULL, envcpy, head);
	}
	return (head);
}