/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:56:00 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 20:57:27 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	heredoc_loop(t_list *current, int pipefd[2], char *input, char *delim)
{
	while (1)
	{
		if (last_try_static_c(0) == 1)
		{
			free_list(get_head_node(current));
			close(pipefd[1]);
			run_minishell();
		}
		else
			input = readline(">");
		if (!input)
		{
			printf("\033[1A> ");
			break ;
		}
		if ((ft_strncmp(input, delim, ft_strlen(delim)) == 0 && \
		input[ft_strlen(delim)] == '\0'))
		{
			free(input);
			break ;
		}
		if (check_for_dollar(input) == 1)
			input = heredoc_env_open(input, current);
		write_input_to_pipe(input, pipefd[1]);
	}
}

t_list	*handle_heredoc(t_list *current)
{
	char	*delim;
	char	*input;
	int		pipefd[2];
	t_list	*prev;

	prev = current->prev;
	input = NULL;
	last_try_static_c(-1);
	signal(SIGINT, SIG_IGN);
	pipefd[0] = -1;
	if (check_heredoc_delim(current) != 1)
	{
		termios_handler(1);
		signal(SIGINT, heredoc_signal_c);
		delim = ft_strdup(current->next->value);
		if (delim == NULL || pipe(pipefd) == -1)
			exit_gracefully(current);
		heredoc_loop(current, pipefd, input, delim);
		close(pipefd[1]);
		init_signals();
		free(delim);
	}
	return (end_heredoc(current, prev, pipefd));
}
