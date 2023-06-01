/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:25:14 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 23:37:25 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array_and_env(char **array, char **g_envcpy, t_list *head)
{
	free_array(array);
	free_env_and_list(g_envcpy, head);
}

void	free_node(t_list *node)
{
	int	i;

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

int	assignment_check(char *str)
{
	int	i;

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

int	is_it_redirection_no_pipe(char *prompt)
{
	if (ft_strncmp(prompt, "|\0", 2) == 0)
		return (2);
	else if (ft_strncmp(prompt, ">>\0", 3) == 0)
		return (2);
	else if (ft_strncmp(prompt, "<\0", 2) == 0)
		return (1);
	else if (ft_strncmp(prompt, ">\0", 2) == 0)
		return (1);
	return (0);
}

int	is_it_redirection_redir_check(char *prompt)
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
