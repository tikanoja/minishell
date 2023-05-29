/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:24:33 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/26 15:32:14 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	is_it_builtin(char *prompt)
{
	if (ft_strncmp_casein(prompt, "echo\0", 4) == 0 && \
	(is_it_whitespace(prompt[4]) || prompt[4] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "cd\0", 2) == 0 && \
	(is_it_whitespace(prompt[2]) || prompt[2] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "pwd\0", 3) == 0 && \
	(is_it_whitespace(prompt[3]) || prompt[3] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "export\0", 6) == 0 && \
	(is_it_whitespace(prompt[6]) || prompt[6] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "unset\0", 5) == 0 && \
	(is_it_whitespace(prompt[5]) || prompt[5] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "env\0", 3) == 0 && \
	(is_it_whitespace(prompt[3]) || prompt[3] == '\0'))
		return (1);
	else if (ft_strncmp_casein(prompt, "exit\0", 4) == 0 && \
	(is_it_whitespace(prompt[4]) || prompt[4] == '\0'))
		return (1);
	return (0);
}

int	is_it_redirection(char *prompt)
{
	if (prompt == NULL)
		return (0);
	else if (ft_strncmp(prompt, "|\0", 2) == 0)
		return (1);
	else if (ft_strncmp(prompt, "<<\0", 3) == 0)
		return (2);
	else if (ft_strncmp(prompt, ">>\0", 3) == 0)
		return (2);
	else if (ft_strncmp(prompt, "<\0", 2) == 0)
		return (1);
	else if (ft_strncmp(prompt, ">\0", 2) == 0)
		return (1);
	return (0);
}

int	is_it_redirection_parsing(char *prompt)
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

int	is_it_log_operator(char *prompt)
{
	if (ft_strncmp(prompt, "||\0", 2) == 0)
		return (2);
	else if (ft_strncmp(prompt, "&&\0", 2) == 0)
		return (2);
	return (0);
}

t_list	*add_node(t_list *node, char *token, char **envcpy, t_list *head)
{
	t_list	*prev;

	if (node == NULL)
		prev = NULL;
	else
		prev = node;
	node = ft_calloc(1, sizeof(t_list));
	if (!node)
		free_env_and_list(envcpy, head);
	if (token != NULL)
		node->value = ft_strdup(token);
	node->args = NULL;
	node->argc = 0;
	node->pipe = 0;
	node->index = 0;
	node->execflag = 0;
	node->prev = prev;
	node->next = NULL;
	if (prev)
		prev->next = node;
	node->input = STDIN_FILENO;
	node->output = STDOUT_FILENO;
	return (node);
}

char	**realloc_array(t_list *node, char *token, char **envcpy, t_list *head)
{
	char	**array;
	int		i;

	array = NULL;
	i = 0;
	array = ft_calloc(node->argc + 2, sizeof(char **));
	if (!array)
		free_env_and_list(envcpy, head);
	while (node->args && node->args[i])
	{
		array[i] = ft_strdup(node->args[i]);
		free(node->args[i]);
		i++;
	}
	node->argc = i + 1;
	if (node->args)
		free(node->args);
	node->args = NULL;
	array[i] = ft_strdup(token);
	if (!array[i])
		exit_gracefully(head);
	array[i + 1] = NULL;
	return (array);
}

void	init_parsecmd(t_list **node, t_list **head, int *argflag)
{
	*node = NULL;
	*head = NULL;
	*argflag = -1;
}

void	remove_extra_node(t_list *head)
{
	t_list	*current;

	current = head;
	while (current)
	{
		if (is_it_redirection(current->value) > 0 && current->next->value == NULL)
		{
			free(current->next->args);
			free(current->next);
			current->next = NULL;
			break ;
		}
		current = current->next;
	}
}

t_list	*get_head_node(t_list *node)
{
	if (node == NULL)
		return (NULL);
	while (node->prev)
		node = node->prev;
	return (node);
}

t_list	*parsecmd(char *prompt, char **envcpy)
{
	t_list	*node;
	t_list	*head;
	char	*token;
	int		argflag;

	init_parsecmd(&node, &head, &argflag);
	token = ft_lexer(prompt, envcpy, head);
	node = NULL;
	while (1)
	{
		if (token == NULL)
			break ;
		if (is_it_redirection_parsing(token) > 0 || is_it_log_operator(token) > 0)
		{
			argflag = -1;
			node = add_node(node, token, envcpy, head);
			free(token);
			token = ft_lexer(NULL, envcpy, head);
			continue ;
		}
		if (argflag == -1)
			node = add_node(node, token, envcpy, head);
		else
			node->args = realloc_array(node, token, envcpy, head);
		argflag++;
		free(token);
		token = ft_lexer(NULL, envcpy, head);
	}
	free(prompt);
	if (token)
		free(token);
	return (get_head_node(node));
}
