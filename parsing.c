/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:24:33 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 23:37:25 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*add_node(t_list *node, char *token, char **g_envcpy, t_list *head)
{
	t_list	*prev;

	if (node == NULL)
		prev = NULL;
	else
		prev = node;
	node = ft_calloc(1, sizeof(t_list));
	if (!node)
		free_env_and_list(g_envcpy, head);
	if (token != NULL)
		node->value = ft_strdup(token);
	if (node->value == NULL)
		exit_gracefully(head);
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

char	**realloc_array(t_list *node, char *token)
{
	char	**array;
	int		i;

	array = NULL;
	i = 0;
	array = ft_calloc(node->argc + 2, sizeof(char **));
	if (!array)
		return (NULL);
	while (node->args && node->args[i])
	{
		array[i] = ft_strdup(node->args[i]);
		if (!array[i])
			return (NULL);
		free(node->args[i]);
		i++;
	}
	node->argc = i + 1;
	if (node->args)
		free(node->args);
	node->args = NULL;
	array[i] = ft_strdup(token);
	if (!array[i])
		return (NULL);
	array[i + 1] = NULL;
	return (array);
}

char	**realloc_array_parsecmd(t_list *node, char *token, char *prompt)
{
	char	**array;
	int		i;

	init_realloc_parsecmd(&array, &i);
	array = ft_calloc(node->argc + 2, sizeof(char **));
	if (!array)
		free_realloc_parsecmd(prompt, token, node);
	while (node->args && node->args[i])
	{
		array[i] = ft_strdup(node->args[i]);
		if (!array[i])
			free_realloc_parsecmd2(prompt, token, node, array);
		free(node->args[i]);
		i++;
	}
	node->argc = i + 1;
	if (node->args)
		free(node->args);
	node->args = NULL;
	array[i] = ft_strdup(token);
	if (!array[i])
		free_realloc_parsecmd3(prompt, token, node, array);
	array[i + 1] = NULL;
	return (array);
}

t_list	*parsecmd(char *prompt, char **g_envcpy)
{
	t_list	*node;
	t_list	*head;
	char	*token;
	int		argflag;

	init_parsecmd(&node, &head, &argflag);
	token = ft_lexer(prompt, g_envcpy, head);
	while (1)
	{
		if (token == NULL)
			break ;
		if (is_it_redirection_parsing(token) > 0 || \
		is_it_log_operator(token) > 0)
		{
			parse_redir(&argflag, &node, &token, &head);
			continue ;
		}
		if (argflag == -1)
			node = add_node(node, token, g_envcpy, head);
		else
			node->args = realloc_array_parsecmd(node, token, prompt);
		handle_parsing_end(&argflag, &token, &head);
	}
	free_token_and_prompt(&token, &prompt);
	return (get_head_node(node));
}
