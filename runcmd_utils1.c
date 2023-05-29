/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:55:48 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 23:56:53 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_not_found_update_status(t_list *current, int *status)
{
	ft_putstr_fd("shelly: ", 2);
	ft_putstr_fd(current->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	(*status) = 127;
}

void	init_runcmd(t_list **current, int *status, pid_t *pid, t_list **head)
{
	*current = *head;
	(*status) = 0;
	(*pid) = 1;
}

int	execflag_check(t_list **current)
{
	if ((*current)->execflag == 1)
	{
		(*current) = (*current)->next;
		return (1);
	}
	return (0);
}

int	runcmd_directory_check(int *status, t_list **current)
{
	if (directory_check((*current)->value) != 0)
	{
		(*current)->execflag = 1;
		(*status) = 126;
	}
	else
	{
		(*current)->system_command = 1;
		return (1);
	}
	return (0);
}

int	end_runcmd(t_list **current, t_list **head, int status, pid_t pid)
{
	(*current) = (*head);
	close_all_fds((*current));
	while (pid > 0)
		pid = waitpid(-1, &status, 0);
	return (status);
}
