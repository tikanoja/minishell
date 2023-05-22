#include "minishell.h"

void exitmsg(char *msg)
{
	perror(msg);
	exit(1);
}

void free_list(t_list *head)
{
	t_list	*next;
	t_list	*current;
	int		i;

	current = head;
	i = 0;
	while (current != NULL)
	{
		i = 0;
		free(current->value);
		while (current->args && current->args[i])
		{
			free(current->args[i]);
			i++;
		}
		if (current->args)
			free(current->args);
		next = current->next;
		free(current);
		current = next;
	}
}

void free_env(char **env)
{
	int i;

	i = 0;
	while(env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void free_env_and_list(char **env, t_list *head)
{
	free_env(env);
	free_list(head);
	exitmsg("malloc failed in parsing");
}

void free_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void free_array_and_env(char **array, char **envcpy, t_list *head)
{
	free_array(array);
	free_env_and_list(envcpy, head);
}

void free_node(t_list *node)
{
	int i;

	i = 0;
	free(node->value);
	while (node->args[i])
	{
		free(node->args[i]);
		i++;
	}
	free(node->args);
	free(node);
}

int     assignment_check(char *str)
{
    int i;

    i = 0;
    if (str == NULL)
        return (0);
    while (str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

int is_it_redirection_no_pipe(char *prompt)
{
	if (ft_strncmp(prompt, "<<\0", 3) == 0)
		return (2);
	else if (ft_strncmp(prompt, ">>\0", 3) == 0)
		return (2);
	else if (ft_strncmp(prompt, "<\0", 2) == 0)
		return (1);
	else if (ft_strncmp(prompt, ">\0", 2) == 0)
		return (1);
	return (0);
}

int is_it_redirection_redir_check(char *prompt)
{
	if (ft_strncmp(prompt, "|", 1) == 0) 
		return (1);
	else if (ft_strncmp(prompt, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(prompt, ">>", 2) == 0)
		return (2);
	else if (ft_strncmp(prompt, "<", 1) == 0)
		return (1);
	else if (ft_strncmp(prompt, ">", 1) == 0)
		return (1);
	return (0);
}

int double_redir_check(t_list *head)
{
	t_list *current;
	current = head;

	while (current)
	{
		if (is_it_redirection_no_pipe(current->value) > 0 && current->next && is_it_redirection_no_pipe(current->next->value) > 0)
		{
			ft_putstr_fd("shelly: syntax error near unexpected token `", 2);
			ft_putstr_fd(current->next->value, 2);
			ft_putstr_fd("'\n", 2);
			free_list(head);
			return(1);
		}
		else if (current->args && is_it_redirection_redir_check(current->args[0]) > 0)
		{
			ft_putstr_fd("shelly: syntax error near unexpected token `", 2);
			ft_putstr_fd(current->args[0], 2);
			ft_putstr_fd("'\n", 2);
			free_list(head);
			return(1);
		}
		current = current->next;
	}
	return (0);
}