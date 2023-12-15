/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_frees2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:28:10 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/30 18:28:34 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir_out_frees(t_list *current, t_list *next)
{
	if (next)
	{
		free(next->value);
		next->value = NULL;
		if (next->args)
		{
			free(next->args);
			next->args = NULL;
		}
		free(next);
		next = NULL;
	}
	free(current->value);
	current->value = NULL;
	free(current);
	current = NULL;
}

void	free_redir_out_handle_nodes(int *i, t_list **prev, \
t_list **next, t_list **ret)
{
	(*i) = 0;
	if ((*prev) && (*next) && (*next)->next)
	{
		(*prev)->next = (*next)->next;
		(*next)->next->prev = (*prev);
		(*ret) = (*next)->next;
	}
	else if (!(*prev) && (*next) && (*next)->next)
	{
		(*next)->next->prev = NULL;
		(*ret) = (*next)->next;
	}
	else if (((*prev) && (*next) && !(*next)->next) || (*prev && !(*next)))
	{
		if (*prev)
			(*prev)->next = NULL;
		(*ret) = NULL;
	}
}

void	realloc_redirection_out(t_list *prev, t_list *current, \
t_list *next, int i)
{
	prev->args = realloc_array(prev, next->args[i]);
	if (!prev->args)
		exit_gracefully(current);
	free(current->next->args[i]);
}
