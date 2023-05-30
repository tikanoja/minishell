/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 22:46:25 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 23:37:25 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_redir_print(int flag, t_list *current, t_list *head, int *status)
{
	ft_putstr_fd("shelly: syntax error near unexpected token `", 2);
	if (flag == 1)
		ft_putstr_fd(current->value, 2);
	else if (flag == 2)
		ft_putstr_fd(current->next->value, 2);
	else if (flag == 3)
		ft_putstr_fd(current->args[0], 2);
	ft_putstr_fd("'\n", 2);
	(*status) = 258;
	free_list(head);
	return (1);
}

int	double_redir_check(t_list *head, int *status)
{
	t_list	*current;

	current = head;
	if (ft_strncmp(current->value, "|", 1) == 0)
		return (double_redir_print(1, current, head, status));
	while (current) //jos joku hajoo ni is_it_redirection_no_pipe(current->value)
	{
		if (is_it_redirection_no_pipe(current->value) > 0 && \
		current->next && is_it_redirection_no_pipe(current->next->value) > 0)
			return (double_redir_print(2, current, head, status));
		else if (stnc(current->value, "<<", 2) == 0 && \
		current->next && is_it_redirection(current->next->value) > 0)
			return (double_redir_print(2, current, head, status));
		else if (current->args && \
		is_it_redirection_redir_check(current->args[0]) > 0)
			return (double_redir_print(3, current, head, status));
		current = current->next;
	}
	return (0);
}

void	exit_gracefully(t_list *current)
{
	free_env_and_list(g_envcpy, get_head_node(current));
}

void	exitmsg(char *msg)
{
	perror(msg);
	exit(1);
}
