/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:50:01 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 20:52:31 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_heredoc_env_open(int *i, int *j, char **input_opened, \
char input_env[1024])
{
	(*i) = 0;
	(*j) = 0;
	(*input_opened) = NULL;
	ft_bzero(input_env, 1024);
}

char	*free_heredoc_env_open(char **input, char *input_opened, \
t_list *current)
{
	free((*input));
	if (input_opened != NULL)
	{
		(*input) = ft_strdup(input_opened);
		if ((*input) == NULL)
			exit_gracefully(current);
	}
	else
		(*input) = NULL;
	free(input_opened);
	return ((*input));
}

void	heredoc_env_open_iterators(char *input, char *input_env, int *i, int *j)
{
	ft_bzero(input_env, (size_t)(*j));
	if (input[(*i)] == '$' || is_it_quote(input[(*i)]) == 0 || \
	is_it_whitespace(input[(*i)]) == 0)
		(*i)--;
	(*j) = 0;
	return ;
}

void	free_current_and_next(t_list *current)
{
	if (current->next)
		free(current->next->value);
	if (current->next)
		free(current->next);
	free(current->value);
	current->value = NULL;
	free(current);
	current = NULL;
}

void	fill_args_to_prev(t_list *crnt, t_list *prev, t_list **ret)
{
	int	i;

	i = 0;
	while (crnt->next && crnt->next->args && crnt->next->args[i])
	{
		if (prev == NULL)
		{
			prev = add_node(NULL, crnt->next->args[i], NULL, NULL);
			if (!prev)
				exit_gracefully(crnt);
			prev->next = *ret;
			if (*ret != NULL)
				(*ret)->prev = prev;
			crnt->prev = prev;
			*ret = crnt->prev;
		}
		else if (prev)
		{
			crnt->prev->args = realloc_array(crnt->prev, crnt->next->args[i]);
			if (!crnt->prev->args)
				exit_gracefully(crnt);
			free(crnt->next->args[i]);
		}
		i++;
	}
}
