/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:56:00 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/30 02:15:36 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*heredoc_env_open(char *input, t_list *current)
{
	char	input_env[1024];
	char	*open;
	int		i;
	int		j;

	init_heredoc_env_open(&i, &j, &open, input_env);
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] != '\'' && input[i + 1] != '\"')
		{
			i++;
			if (input[i] != '\'' && input[i] != '\"')
			{
				while (is_it_whitespace(input[i]) == 0 && \
				is_it_quote(input[i]) == 0 && input[i] && input[i] != '$')
					copy_and_move_ptrs(input_env, input, &i, &j);
				open = ft_strjoin_oe(open, ft_getenv(input_env));
				heredoc_env_open_iterators(input, input_env, &i, &j);
			}
		}
		else
			open = char_join(open, input[i], current);
		i++;
	}
	return (free_heredoc_env_open(&input, open, current));
}

void	heredoc_loop_child(t_list *current, int pipefd[2], char *delim)
{
	char	*input;

	close(pipefd[0]);
	signal(SIGINT, heredoc_signal_c);
	while (1)
	{
		input = readline(">");
		if (!input)
		{
			printf("\033[1A> ");
			break ;
		}
		if ((ft_strncmp(input, delim, ft_strlen(delim)) == 0 && input[ft_strlen(delim)] == '\0'))
		{
			free(input);
			break ;
		}
		if (check_for_dollar(input) == 1)
			input = heredoc_env_open(input, current);
		write(pipefd[1], input, ft_strlen(input));
		write(pipefd[1], "\n", 1);
		free(input);
	}
	close(pipefd[1]);
	exit(EXIT_SUCCESS);
}

t_list	*handle_heredoc(t_list *current)
{
	char	*delim;
	t_list	*prev;
	int		pipefd[2];
	pid_t	pid;

	prev = current->prev;
	signal(SIGINT, SIG_IGN);
	pipefd[0] = -1;
	if (check_heredoc_delim(current) != 1)
	{
		termios_handler(1);
		delim = ft_strdup(current->next->value);
		if (delim == NULL || pipe(pipefd) == -1)
			exit_gracefully(current);
		pid = fork();
		if (pid == -1)
			pid_failed();
		else if (pid == 0)
			heredoc_loop_child(current, pipefd, delim);
		else
			wait_for_child_doc(pipefd[1], pid);
		init_signals();
		free(delim);
	}
	return (end_heredoc(current, prev, pipefd));
}
