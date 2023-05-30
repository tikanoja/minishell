/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_frees.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:43:57 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/30 18:28:40 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirection_out_connect(t_list **prev, \
t_list **current, t_list **ret)
{
	(*prev)->next = *ret;
	if (*ret != NULL)
		(*ret)->prev = *prev;
	(*current)->prev = *prev;
	*ret = (*current)->prev;
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
			free(current->next->args[i]);
			if (current->execflag == 1)
				prev->execflag = 1;
			free_redirection_out_connect(&prev, &current, &ret);
		}
		else if (prev)
			realloc_redirection_out(prev, current, next, i);
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
