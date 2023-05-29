/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 22:46:25 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 22:48:45 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_redir_print(int flag, t_list *current, t_list *head)
{
	ft_putstr_fd("shelly: syntax error near unexpected token `", 2);
	if (flag == 1)
		ft_putstr_fd(current->value, 2);
	else if (flag == 2)
		ft_putstr_fd(current->next->value, 2);
	else if (flag == 3)
		ft_putstr_fd(current->args[0], 2);
	ft_putstr_fd("'\n", 2);
	free_list(head);
	return (1);
}

int	double_redir_check(t_list *head)
{
	t_list	*current;

	current = head;
	if (ft_strncmp(current->value, "|", 1) == 0)
		return (double_redir_print(1, current, head));
	while (current)
	{
		if (is_it_redirection_no_pipe(current->value) > 0 && \
		current->next && is_it_redirection_no_pipe(current->next->value) > 0)
			return (double_redir_print(2, current, head));
		else if (current->args && \
		is_it_redirection_redir_check(current->args[0]) > 0)
			return (double_redir_print(3, current, head));
		current = current->next;
	}
	return (0);
}

void	exit_gracefully(t_list *current)
{
	free_env_and_list(envcpy, get_head_node(current));
}

void	exitmsg(char *msg)
{
	perror(msg);
	exit(1);
}
