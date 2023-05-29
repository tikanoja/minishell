/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:49:10 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/30 02:30:23 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_assign_pipe(t_list *prev, int pipefd[2])
{
	if (prev)
	{
		if (prev->input != STDIN_FILENO)
			close(prev->input);
		prev->input = pipefd[0];
	}
}
t_list	*end_heredoc(t_list *current, t_list *prev, int pipefd[2])
{
	t_list	*ret;

	ret = NULL;
	heredoc_assign_pipe(prev, pipefd);
	if (current->next && current->next->next && prev)
	{
		prev->next = current->next->next;
		current->next->next->prev = prev;
		ret = current->next->next;
	}
	else if (prev && !current->next)
		prev->next = NULL;
	else if (current->next && current->next->next && !prev)
	{
		current->next->next->prev = NULL;
		ret = current->next->next;
	}
	else if (prev && current->next && !current->next->next)
		prev->next = NULL;
	fill_args_to_prev(current, prev, &ret, pipefd[0]);
	free_current_and_next(current);
	return (ret);
}

void	heredoc_signal_c(int signum __attribute__((unused)))
{
	close(0);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	write_input_to_pipe(char *input, int pipefd)
{
	ft_putstr_fd(input, pipefd);
	ft_putchar_fd('\n', pipefd);
	free(input);
}
