/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_and_pipes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:22:06 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/30 18:25:52 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe_pipefd(t_list **node, int pipefd, int flag)
{
	if (flag == 1)
	{
		(*node)->output = pipefd;
		(*node)->pipe = 1;
	}
	else
	{
		(*node)->input = pipefd;
		(*node)->pipe = 1;
	}
}

void	handle_fd_redir(t_list **prev, t_list **next) //jos taa hajotti siirra takas;
{
	int		fd;

	fd = open((*next)->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1 && redir_directory_check((*next)->value, (*prev)) == 1)
	{	
		if ((*prev))
			(*prev)->execflag = 1;
		if ((*next)->next)
			(*next)->next->execflag = 1;
	}
	if (fd != -1 && (*prev) && (*prev)->execflag != 1)
	{
		if ((*prev)->output != STDOUT_FILENO)
			close((*prev)->output);
		(*prev)->output = fd;
	}
	else
		close(fd);
}

void	handle_failed_open(t_list **current, int fd)
{
	(*current)->execflag = 1;
	close(fd);
}
