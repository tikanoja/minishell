/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_frees.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:43:57 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 20:44:38 by jaurasma         ###   ########.fr       */
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
	if ((*prev) && next && (*next)->next)
	{
		(*prev)->next = (*next)->next;
		(*next)->next->prev = (*prev);
		(*ret) = (*next)->next;
	}
	else if (!prev && next && (*next)->next)
	{
		(*next)->next->prev = NULL;
		(*ret) = (*next)->next;
	}
	else if ((prev && next && !(*next)->next) || (prev && !next))
	{
		(*prev)->next = NULL;
		(*ret) = NULL;
	}	
}

t_list	*free_redirection_out(t_list *current, t_list *prev, t_list *next)
{
	t_list	*ret;
	int		i;

	ret = NULL;
	free_redir_out_handle_nodes(&i, &prev, &next, &ret);
	while (current->next && current->next->args && current->next->args[i])
	{
		if (prev == NULL)
		{
			prev = add_node(NULL, current->next->args[i], NULL, NULL);
			if (!prev)
				exit_gracefully(current);
			prev->next = ret;
			if (ret != NULL)
				ret->prev = prev;
			current->prev = prev;
			ret = current->prev;
		}
		else if (prev)
		{
			prev->args = realloc_array(prev, next->args[i]);
			if (!prev->args)
				exit_gracefully(current);
			free(current->next->args[i]);
		}
		i++;
	}
	free_redir_out_frees(current, next);
	return (ret);
}

t_list	*free_pipe(t_list *current, t_list *prev, t_list *next)
{
	if (prev && next)
	{
		prev->next = next;
		next->prev = prev;
	}
	else if (!prev && next)
		next->prev = NULL;
	else if (prev && !next)
		prev->next = NULL;
	free(current->value);
	free(current);
	if (next)
		return (next);
	else
		return (NULL);
}
